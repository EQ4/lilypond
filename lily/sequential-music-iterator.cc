/*
  Sequential_music_iterator.cc -- implement Sequential_music_iterator

  source file of the GNU LilyPond music typesetter

  (c)  1997--2000 Han-Wen Nienhuys <hanwen@cs.uu.nl>
*/
#include "grace-iterator.hh"
#include "translator-group.hh"
#include "debug.hh"
#include "sequential-music-iterator.hh"
#include "music-list.hh"
#include "request-chord-iterator.hh"


void
Sequential_music_iterator::do_print() const
{
  if (iter_p_)
    iter_p_->print();
}

Sequential_music_iterator::Sequential_music_iterator ()
{
  cursor_ = 0;
  here_mom_ = 0;
  iter_p_ =0;
}

void
Sequential_music_iterator::construct_children()
{
  cursor_ = dynamic_cast<Music_sequence const*> (music_l_)->music_list ();
  
  while (gh_pair_p (cursor_ ))
    {
      start_next_element();
      if (!iter_p_->ok()) 
	{
	  leave_element();
	}
      else 
	{
	  set_sequential_music_translator();
	  break;
	}
    }
}

void 
Sequential_music_iterator::leave_element()
{
  delete iter_p_;
  iter_p_ =0;
  Moment elt_time = unsmob_music (gh_car (cursor_))->length_mom ();
  here_mom_ += elt_time;
  cursor_ =gh_cdr (cursor_);
}

void
Sequential_music_iterator::start_next_element()
{
  assert (!iter_p_);
  iter_p_ = get_iterator_p (unsmob_music (gh_car (cursor_)));
}

void
Sequential_music_iterator::set_sequential_music_translator()
{
  Translator_group  * child_report = child_report = iter_p_->report_to_l ();
  if (dynamic_cast<Grace_iterator*> (iter_p_))
    child_report = child_report->daddy_trans_l_;
    
  if (report_to_l()->depth_i () < child_report->depth_i ())
    set_translator (child_report);
}

Sequential_music_iterator::~Sequential_music_iterator()
{
  if (iter_p_)
    {
      if (iter_p_->ok ())
	music_l_->origin ()->warning (_ ("Must stop before this music ends"));
      delete iter_p_;
      iter_p_ = 0;
    }
}

void
Sequential_music_iterator::do_process_and_next (Moment until)
{
  if (!iter_p_)
    return;

  while (1) 
    {
      Moment local_until = until - here_mom_;
      while (iter_p_->ok()) 
	{
	  Moment here = iter_p_->next_moment();
	  if (here != local_until)
	    goto loopexit;
	    
	  iter_p_->process_and_next (local_until);
	}
      
      if (!iter_p_->ok()) 
	{
	  set_sequential_music_translator();
	  leave_element();
	  
	  if (gh_pair_p (cursor_))
	    start_next_element();
	  else 
	    goto loopexit;
	}
    }

loopexit:

  Music_iterator::do_process_and_next (until);
}

Moment
Sequential_music_iterator::next_moment() const
{
  return iter_p_->next_moment() + here_mom_;
}


bool
Sequential_music_iterator::ok() const
{
  return iter_p_;
}

Music_iterator*
Sequential_music_iterator::try_music_in_children (Music *m) const
{ 
  return iter_p_ ? iter_p_->try_music (m) : 0;
}

Music*
Sequential_music_iterator::get_next_music ()
{
  if (cursor_ && gh_pair_p (cursor_))
    return unsmob_music (gh_car (cursor_));
  return 0;
}
