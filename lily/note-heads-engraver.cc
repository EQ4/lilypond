/*
  head-grav.cc -- part of GNU LilyPond

  (c)  1997--2000 Han-Wen Nienhuys <hanwen@cs.uu.nl>
*/

#include "rhythmic-head.hh"
#include "paper-def.hh"
#include "musical-request.hh"
#include "dots.hh"
#include "dot-column.hh"
#include "staff-symbol-referencer.hh"
#include "item.hh"
#include "score-engraver.hh"
#include "warn.hh"

/**
  make balls and rests
 */
class Note_heads_engraver : public Engraver
{
  Link_array<Item> note_p_arr_;
  Link_array<Item> dot_p_arr_;
  Link_array<Note_req> note_req_l_arr_;
  Moment note_end_mom_;
public:
  VIRTUAL_COPY_CONS(Translator);
  Note_heads_engraver();
  
protected:
  virtual void do_post_move_processing ();
  virtual bool do_try_music (Music *req_l) ;
  virtual void process_acknowledged ();
  virtual void acknowledge_element (Score_element_info) ;
  void deprecated_process_music();
  virtual void do_pre_move_processing();
};





Note_heads_engraver::Note_heads_engraver()
{
}

bool
Note_heads_engraver::do_try_music (Music *m) 
{
  if (Note_req * n =dynamic_cast <Note_req *> (m))
    {
      note_req_l_arr_.push (n);
      note_end_mom_  = note_end_mom_ >? now_mom () + m->length_mom ();
      
      return true;
    }
  else if (dynamic_cast<Busy_playing_req*> (m))
    {
      return now_mom () < note_end_mom_;
    }
  return false;
  
}

void
Note_heads_engraver::process_acknowledged ()
{
  deprecated_process_music ();
}

void
Note_heads_engraver::acknowledge_element (Score_element_info)
{
  //deprecated_process_music ();
}

void
Note_heads_engraver::deprecated_process_music()
{
  if (note_p_arr_.size ())
    return ;
  
  for (int i=0; i < note_req_l_arr_.size (); i++)
    {
      Item *note_p  = new Item (get_property ("NoteHead"));
      
      Staff_symbol_referencer::set_interface (note_p);


      
      Music * req = note_req_l_arr_[i];
      
      Duration dur   = *unsmob_duration (req->get_mus_property ("duration"));
      note_p->set_elt_property ("duration-log",
				gh_int2scm (dur.duration_log () <? 2));

      if (dur.dot_count ())
	{
	  Item * d = new Item (get_property ("Dots"));
	  Rhythmic_head::set_dots (note_p, d);
	  
	  if (dur.dot_count ()
	      != gh_scm2int (d->get_elt_property ("dot-count")))
	    d->set_elt_property ("dot-count", gh_int2scm (dur.dot_count ()));

	  d->set_parent (note_p, Y_AXIS);
	  announce_element (d,0);
	  dot_p_arr_.push (d);
	}

      note_p->set_elt_property("staff-position",  gh_int2scm (unsmob_pitch (req->get_mus_property ("pitch"))->steps ()));

      announce_element (note_p,req);
      note_p_arr_.push (note_p);
    }
}
 
void
Note_heads_engraver::do_pre_move_processing()
{
  for (int i=0; i < note_p_arr_.size (); i++)
    {
      typeset_element (note_p_arr_[i]);
    }
  note_p_arr_.clear ();
  for (int i=0; i < dot_p_arr_.size (); i++)
    {
      typeset_element (dot_p_arr_[i]);
    }
  dot_p_arr_.clear ();
  
  note_req_l_arr_.clear ();
}

void
Note_heads_engraver::do_post_move_processing ()
{
  /* TODO:make this settable?
   */
  if (note_end_mom_ > now_mom())
    {
      Score_engraver * e = 0;
      Translator * t  =  daddy_grav_l ();
      for (; !e && t;  t = t->daddy_trans_l_)
	{
	  e = dynamic_cast<Score_engraver*> (t);
	}

      if (!e)
	programming_error ("No score engraver!");
      else
	e->forbid_breaks ();	// guh. Use properties!
    }
}



ADD_THIS_TRANSLATOR(Note_heads_engraver);

