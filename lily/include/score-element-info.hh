/*
  score-element-info.hh -- declare Score_element_info

  source file of the GNU LilyPond music typesetter

  (c)  1997--1998 Han-Wen Nienhuys <hanwen@cs.uu.nl>
*/


#ifndef STAFFELEMINFO_HH
#define STAFFELEMINFO_HH

#include "scalar.hh"
#include "lily-proto.hh"
#include "parray.hh"

/**
  Data container for broadcasts 
  */
struct Score_element_info {
    Score_element * elem_l_;
    Music *req_l_;
    Link_array<Engraver> origin_grav_l_arr_;

    Score_element_info (Score_element*, Music*);
    Score_element_info();
};


#endif // STAFFELEMINFO_HH
