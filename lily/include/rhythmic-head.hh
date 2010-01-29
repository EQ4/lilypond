/*
  This file is part of LilyPond, the GNU music typesetter.

  Copyright (C) 1997--2010 Han-Wen Nienhuys <hanwen@xs4all.nl>

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

#ifndef RHYTHMIC_HEAD_HH
#define RHYTHMIC_HEAD_HH

#include "grob-interface.hh"
#include "lily-proto.hh"

class Rhythmic_head
{
public:
  static int duration_log (Grob *);
  static void set_dots (Grob *, Item *);
  static Item *get_stem (Grob *);
  static Item *get_dots (Grob *);
  static int dot_count (Grob *);
  DECLARE_SCHEME_CALLBACK (after_line_breaking, (SCM));
  DECLARE_GROB_INTERFACE();
};

#endif // RHYTHMIC_HEAD_HH
