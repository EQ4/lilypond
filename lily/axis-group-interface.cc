/*   
  axis-group-interface.cc --  implement Axis_group_interface
  
  source file of the GNU LilyPond music typesetter
  
  (c) 2000 Han-Wen Nienhuys <hanwen@cs.uu.nl>
  
 */
#include "hara-kiri-group-spanner.hh"
#include "axis-group-interface.hh"
#include "score-element.hh"

void
Axis_group_interface::add_element (Score_element*me,Score_element *e)
{
  for (SCM ax = me->get_elt_property ("axes"); ax != SCM_EOL ; ax = gh_cdr (ax))
    {
      Axis a = (Axis) gh_scm2int (gh_car (ax));
      
      if (!e->parent_l (a))
	e->set_parent (me, a);
    }

  Pointer_group_interface::add_element (me, "elements", e);
  me->add_dependency (e);
}

bool
Axis_group_interface::axis_b (Score_element*me,Axis a )
{
  /*
    urg. FIXME, check for Hara_kiri_group_spanner shouldn't be necessary?

    
   */
  return me->has_extent_callback_b (group_extent_callback_proc, a) ||
    (me->has_extent_callback_b (Hara_kiri_group_spanner::y_extent_proc, a));
}

Interval
Axis_group_interface::relative_group_extent (Axis a, Score_element *common, SCM elts)
{
  Interval r;
  for (SCM s = elts; gh_pair_p (s); s = gh_cdr (s))
    {
      Score_element * se = unsmob_element (gh_car (s));
      Interval dims = se->extent (common, a);
      if (!dims.empty_b ())
	r.unite (dims);
    }
  return r;
}

MAKE_SCHEME_CALLBACK(Axis_group_interface,group_extent_callback,2);
SCM
Axis_group_interface::group_extent_callback (SCM element_smob, SCM scm_axis)
{
  Score_element *me = unsmob_element (element_smob);
  Axis a = (Axis) gh_scm2int (scm_axis);

  Score_element * common =(Score_element*) me;

  for (SCM s = me->get_elt_property ("elements"); gh_pair_p (s); s = gh_cdr (s))
    {
      Score_element * se = unsmob_element (gh_car (s));
      common = se->common_refpoint (common, a);
    }

  Real my_coord = me->relative_coordinate (common, a);
  Interval r (relative_group_extent (a, common, me->get_elt_property ("elements")));

  return ly_interval2scm (r - my_coord);
}



void
Axis_group_interface::set_axes (Score_element*me,Axis a1, Axis a2)
{
  // set_interface () ?
  SCM sa1= gh_int2scm (a1);
  SCM sa2 = gh_int2scm (a2);

  SCM axes = me->get_elt_property ("axes");
  
  if (!gh_pair_p (axes)
      || scm_memq (sa1, axes) == SCM_BOOL_F
      || scm_memq (sa2, axes) == SCM_BOOL_F)
    {
      SCM ax = gh_cons (sa1, SCM_EOL);
      if (a1 != a2)
	ax= gh_cons (sa2, ax);
      me->set_elt_property ("axes", ax);
    }

  if (a1 != X_AXIS && a2 != X_AXIS)
    me->set_extent_callback (SCM_EOL, X_AXIS);
  if (a1 != Y_AXIS && a2 != Y_AXIS)
    me->set_extent_callback (SCM_EOL, Y_AXIS);

  /*
    why so convoluted ? (fixme/documentme?) 
   */
  if (me->has_extent_callback_b (Score_element::molecule_extent_proc, a1))
    me->set_extent_callback (Axis_group_interface::group_extent_callback_proc,a1);
  if (me->has_extent_callback_b (Score_element::molecule_extent_proc, a2))
    me->set_extent_callback (Axis_group_interface::group_extent_callback_proc,a2);
}

Link_array<Score_element> 
Axis_group_interface::get_children (Score_element*me)
{
  Link_array<Score_element> childs;
  childs.push (me) ;

  if (!has_interface (me))
    return childs;
  
  for (SCM ep = me->get_elt_property ("elements"); gh_pair_p (ep); ep = gh_cdr (ep))
    {
      Score_element* e = unsmob_element (gh_car (ep));
      if (e)
	childs.concat (Axis_group_interface::get_children (e));
    }
  
  return childs;
}

bool
Axis_group_interface::has_interface (Score_element*me)
{
  return me && me->has_interface (ly_symbol2scm ("axis-group-interface"));
}



void
Axis_group_interface::set_interface (Score_element*me)
{
  if (!has_interface (me))
    {
      me->set_interface (ly_symbol2scm ("axis-group-interface"));      
    }
}
