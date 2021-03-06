/*
  This file is part of LilyPond, the GNU music typesetter.

  Copyright (C) 1997--2014 Han-Wen Nienhuys <hanwen@xs4all.nl>

  LilyPond is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  LilyPond is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with LilyPond.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "paper-column.hh"

#include "axis-group-interface.hh"
#include "bar-line.hh"
#include "break-align-interface.hh"
#include "font-interface.hh"
#include "grob-array.hh"
#include "lookup.hh"
#include "lookup.hh"
#include "moment.hh"
#include "output-def.hh"
#include "paper-score.hh"
#include "pointer-group-interface.hh"
#include "rhythmic-head.hh"
#include "separation-item.hh"
#include "skyline-pair.hh"
#include "spaceable-grob.hh"
#include "spring.hh"
#include "string-convert.hh"
#include "system.hh"
#include "text-interface.hh"
#include "warn.hh"

Grob *
Paper_column::clone () const
{
  return new Paper_column (*this);
}

void
Paper_column::do_break_processing ()
{
  Item::do_break_processing ();
}

int
Paper_column::get_rank (Grob const *me)
{
  return dynamic_cast<Paper_column const *> (me)->rank_;
}

void
Paper_column::set_rank (int rank)
{
  rank_ = rank;
}

System *
Paper_column::get_system () const
{
  return system_;
}

void
Paper_column::set_system (System *s)
{
  system_ = s;
}

Paper_column *
Paper_column::get_column () const
{
  return (Paper_column *) (this);
}

Paper_column::Paper_column (SCM l)
  : Item (l)
{
  system_ = 0;
  rank_ = -1;
}

Paper_column::Paper_column (Paper_column const &src)
  : Item (src)
{
  system_ = 0;
  rank_ = src.rank_;
}

int
Paper_column::compare (Grob *const &a,
                       Grob *const &b)
{
  return sign (dynamic_cast<Paper_column *> (a)->rank_
               - dynamic_cast<Paper_column *> (b)->rank_);
}

bool
Paper_column::less_than (Grob *const &a,
                         Grob *const &b)
{
  Paper_column *pa = dynamic_cast<Paper_column *> (a);
  Paper_column *pb = dynamic_cast<Paper_column *> (b);

  return pa->rank_ < pb->rank_;
}

Moment
Paper_column::when_mom (Grob *me)
{
  SCM m = me->get_property ("when");
  if (Moment *when = Moment::unsmob (m))
    return *when;
  return Moment (0);
}

bool
Paper_column::is_musical (Grob *me)
{
  SCM m = me->get_property ("shortest-starter-duration");
  Moment s (0);
  if (Moment::unsmob (m))
    s = *Moment::unsmob (m);
  return s != Moment (0);
}

bool
Paper_column::is_used (Grob *me)
{
  extract_grob_set (me, "elements", elts);
  if (elts.size ())
    return true;

  extract_grob_set (me, "bounded-by-me", bbm);
  if (bbm.size ())
    return true;

  if (Paper_column::is_breakable (me))
    return true;

  if (to_boolean (me->get_property ("used")))
    return true;

  if (scm_is_pair (me->get_property ("labels")))
    return true;

  return false;
}

bool
Paper_column::is_breakable (Grob *me)
{
  return scm_is_symbol (me->get_property ("line-break-permission"));
}

Real
Paper_column::minimum_distance (Grob *left, Grob *right)
{
  Drul_array<Grob *> cols (left, right);
  Drul_array<Skyline> skys = Drul_array<Skyline> (Skyline (RIGHT), Skyline (LEFT));

  for (LEFT_and_RIGHT (d))
    {
      Skyline_pair *sp = Skyline_pair::unsmob (cols[d]->get_property ("horizontal-skylines"));
      if (sp)
        skys[d] = (*sp)[-d];
    }

  skys[RIGHT].merge (Separation_item::conditional_skyline (right, left));

  return max (0.0, skys[LEFT].distance (skys[RIGHT]));
}

Interval
Paper_column::break_align_width (Grob *me, SCM align_sym)
{
  Grob *p = me->get_parent (X_AXIS);

  if (is_musical (me))
    {
      me->programming_error ("tried to get break-align-width of a musical column");
      return Interval (0, 0) + me->relative_coordinate (p, X_AXIS);
    }

  Grob *align = 0;
  if (align_sym == ly_symbol2scm ("staff-bar")
      || align_sym == ly_symbol2scm ("break-alignment"))
    align
      = Pointer_group_interface::find_grob (me, ly_symbol2scm ("elements"),
                                            (align_sym == ly_symbol2scm ("staff-bar")
                                             ? Bar_line::non_empty_barline
                                             : Break_alignment_interface::has_interface));
  else
    {
      extract_grob_set (me, "elements", elts);
      for (vsize i = 0; i < elts.size (); i++)
        {
          if (elts[i]->get_property ("break-align-symbol") == align_sym)
            {
              align = elts[i];
              break;
            }
        }
    }

  if (!align)
    return Interval (0, 0) + me->relative_coordinate (p, X_AXIS);

  return align->extent (p, X_AXIS);
}

/*
  Loop through elements of a PaperColumn, find all grobs implementing specified
  interface and return their combined extent.
*/
Interval
Paper_column::get_interface_extent (Grob *column, SCM iface, Axis a)
{
  Interval extent = Interval (0, 0);
  extract_grob_set (column, "elements", elts);

  for (vsize i = 0; i < elts.size (); i++)
    if (elts[i]->internal_has_interface (iface))
      extent.unite (robust_relative_extent (elts[i], elts[i], a));

  return extent;
}

/*
  Print a:
  - vertical line,
  - the rank number,
  - rank moment,
  - blue arrow representing ideal distance,
  - red arrow representing minimum distance
  to aid debugging.  To turn this on, simply add
  \override Score.PaperColumn #'stencil = #ly:paper-column::print
  \override Score.NonMusicalPaperColumn #'stencil = #ly:paper-column::print
  to your score.
  Also, as of 2013-10-16 there's a switch in Frescobaldi that turns this on.
*/
MAKE_SCHEME_CALLBACK (Paper_column, print, 1);
SCM
Paper_column::print (SCM p)
{
  Paper_column *me = dynamic_cast<Paper_column *> (Grob::unsmob (p));

  string r = ::to_string (Paper_column::get_rank (me));

  Moment *mom = Moment::unsmob (me->get_property ("when"));
  string when = mom ? mom->to_string () : "?/?";

  Font_metric *musfont = Font_interface::get_default_font (me);
  SCM properties = Font_interface::text_font_alist_chain (me);
  SCM scm_mol = Text_interface::interpret_markup (me->layout ()->self_scm (),
                                                  properties,
                                                  ly_string2scm (r));
  SCM when_mol = Text_interface::interpret_markup (me->layout ()->self_scm (),
                                                   properties,
                                                   ly_string2scm (when));
  Stencil t = *Stencil::unsmob (scm_mol);
  t.scale (1.2, 1.4);
  t.add_at_edge (Y_AXIS, DOWN, *Stencil::unsmob (when_mol), 0.1);
  t.align_to (X_AXIS, LEFT);
  // compensate for font serifs and half letter-distance
  t.translate (Offset (-0.1, 0));
  t.align_to (Y_AXIS, DOWN);

  Stencil l = Lookup::filled_box (Box (Interval (0, 0.02),
                                       Interval (-8, -1)));

  Real small_pad = 0.15;
  Real big_pad = 0.35;

  // number of printed arrows from *both* loops
  int j = 0;

  for (SCM s = me->get_object ("ideal-distances");
       scm_is_pair (s); s = scm_cdr (s))
    {
      Spring *sp = Spring::unsmob (scm_caar (s));
      if (!Grob::unsmob (scm_cdar (s))
          || !Grob::unsmob (scm_cdar (s))->get_system ())
        continue;

      j++;

      Stencil arrowhead (musfont->find_by_name ("arrowheads.open.01"));
      // initial scaling; it will also scale with font-size.
      arrowhead.scale (1, 1.66);
      Real head_len = arrowhead.extent (X_AXIS).length ();

      SCM stil = Text_interface::interpret_markup (me->layout ()->self_scm (),
                                                   properties,
                                                   ly_string2scm (String_convert::form_string ("%5.2lf", sp->distance ())));
      Stencil *number_stc = Stencil::unsmob (stil);
      number_stc->scale (1, 1.1);
      Real num_height = number_stc->extent (Y_AXIS).length ();
      Real num_len = number_stc->extent (X_AXIS).length ();
      number_stc->align_to (Y_AXIS, DOWN);

      // arrow's y-coord relative to the top of l stencil:
      Real y = -2.5;
      y -= j * (num_height + small_pad + big_pad);
      // horizontally center number on the arrow, excluding arrowhead.
      Offset num_off = Offset ((sp->distance () - num_len - head_len) / 2,
                               y + small_pad);

      vector<Offset> pts;
      pts.push_back (Offset (0, y));

      Offset p2 (sp->distance (), y);
      pts.push_back (p2);

      Stencil id_stencil = Lookup::points_to_line_stencil (0.1, pts);
      id_stencil.add_stencil (arrowhead.translated (p2));
      id_stencil.add_stencil (number_stc->translated (num_off));
      // use a lighter shade of blue so it will remain legible on black background.
      id_stencil = id_stencil.in_color (0.2, 0.4, 1);
      l.add_stencil (id_stencil);
    }

  for (SCM s = me->get_object ("minimum-distances");
       scm_is_pair (s); s = scm_cdr (s))
    {
      Real dist = scm_to_double (scm_cdar (s));
      Grob *other = Grob::unsmob (scm_caar (s));
      if (!other || other->get_system () != me->get_system ())
        continue;

      j++;

      Stencil arrowhead (musfont->find_by_name ("arrowheads.open.01"));
      // initial scaling; it will also scale with font-size.
      arrowhead.scale (1, 1.66);
      Real head_len = arrowhead.extent (X_AXIS).length ();

      SCM stil = Text_interface::interpret_markup (me->layout ()->self_scm (),
                                                   properties,
                                                   ly_string2scm (String_convert::form_string ("%5.2lf", dist)));
      Stencil *number_stc = Stencil::unsmob (stil);
      number_stc->scale (1, 1.1);
      Real num_height = number_stc->extent (Y_AXIS).length ();
      Real num_len = number_stc->extent (X_AXIS).length ();
      number_stc->align_to (Y_AXIS, UP);

      // arrow's y-coord relative to the top of l stencil:
      Real y = -3;
      y -= j * (num_height + small_pad + big_pad);
      // horizontally center number on the arrow, excluding arrowhead.
      Offset num_off = Offset ((dist - num_len - head_len) / 2,
                               y - small_pad);

      vector<Offset> pts;
      pts.push_back (Offset (0, y));

      Offset p2 (dist, y);
      pts.push_back (p2);

      Stencil id_stencil = Lookup::points_to_line_stencil (0.1, pts);
      id_stencil.add_stencil (arrowhead.translated (p2));
      id_stencil.add_stencil (number_stc->translated (num_off));
      // use a lighter shade of red so it will remain legible on black background.
      id_stencil = id_stencil.in_color (1, 0.25, 0.25);
      l.add_stencil (id_stencil);
    }
  t.add_stencil (l);
  return t.smobbed_copy ();
}

/*
  This is all too hairy. We use bounded-by-me to make sure that some
  columns are kept "alive". Unfortunately, when spanners are suicided,
  this falls apart again, because suicided spanners are still in
  bounded-by-me

  THIS IS BROKEN KLUDGE. WE SHOULD INVENT SOMETHING BETTER.
*/
MAKE_SCHEME_CALLBACK (Paper_column, before_line_breaking, 1);
SCM
Paper_column::before_line_breaking (SCM grob)
{
  Grob *me = Grob::unsmob (grob);

  SCM bbm = me->get_object ("bounded-by-me");
  Grob_array *ga = Grob_array::unsmob (bbm);
  if (!ga)
    return SCM_UNSPECIFIED;

  vector<Grob *> &array (ga->array_reference ());

  for (vsize i = array.size (); i--;)
    {
      Grob *g = array[i];

      if (!g || !g->is_live ())
        /* UGH . potentially quadratic. */
        array.erase (array.begin () + i);
    }

  return SCM_UNSPECIFIED;
}

/* FIXME: This is a hack that we use to identify columns that used to
   contain note-heads but whose note-heads were moved by one of the ligature
   engravers. Once the ligature engravers are fixed to behave nicely, this
   function can be removed.
*/
bool
Paper_column::is_extraneous_column_from_ligature (Grob *me)
{
  if (!is_musical (me))
    return false;

  // If all the note-heads that I think are my children actually belong
  // to another column, then I am extraneous.
  extract_grob_set (me, "elements", elts);
  bool has_notehead = false;
  for (vsize i = 0; i < elts.size (); i++)
    {
      if (Rhythmic_head::has_interface (elts[i]))
        {
          has_notehead = true;
          if (dynamic_cast<Item *> (elts[i])->get_column () == me)
            return false;
        }
    }
  return has_notehead;
}

ADD_INTERFACE (Paper_column,
               "@code{Paper_column} objects form the top-most X@tie{}parents"
               " for items.  There are two types of columns: musical and"
               " non-musical, to which musical and non-musical objects are"
               " attached respectively.  The spacing engine determines the"
               " X@tie{}positions of these objects.\n"
               "\n"
               "They are numbered, the first (leftmost) is column@tie{}0."
               "  Numbering happens before line breaking, and columns are not"
               " renumbered after line breaking.  Since many columns go"
               " unused, you should only use the rank field to get ordering"
               " information.  Two adjacent columns may have non-adjacent"
               " numbers.",

               /* properties */
               "between-cols "
               "bounded-by-me "
               "full-measure-extra-space "
               "grace-spacing "
               "labels "
               "line-break-system-details "
               "line-break-penalty "
               "line-break-permission "
               "maybe-loose "
               "page-break-penalty "
               "page-break-permission "
               "page-turn-penalty "
               "page-turn-permission "
               "rhythmic-location "
               "shortest-playing-duration "
               "shortest-starter-duration "
               "spacing "
               "used "
               "when ");

