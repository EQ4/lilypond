/*
  dot-column.hh -- declare Dot_column Dot_column

  source file of the GNU LilyPond music typesetter

  (c)  1997--2000 Han-Wen Nienhuys <hanwen@cs.uu.nl>
*/


#ifndef DOT_COLUMN_HH
#define DOT_COLUMN_HH

#include "axis-group-item.hh"


/**
  Group dots.  This is needed because, the dots have to be aligned per voice
 */
class Dot_column : public Axis_group_item
{
  static int compare (Dots * const&,Dots * const&);
  void add_dots (Dots*);
public:
  VIRTUAL_COPY_CONS (Score_element);
  void add_head (Rhythmic_head*);
  Dot_column ();

protected:
  virtual void after_line_breaking ();
};
#endif // DOT_COLUMN_HH
