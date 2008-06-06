%% Do not edit this file; it is auto-generated from LSR http://lsr.dsi.unimi.it
%% This file is in the public domain.
\version "2.11.48"

\header {
  lsrtags = "pitches"

  texidoc = "
In early 20th century works, starting with Schoenberg, Berg and Webern
(the \"Second\" Viennese school), every pitch in the twelve-tone scale
has to be regarded as equal, without any hierarchy such as the
classical (tonal) degrees. Therefore, these composers print one
accidental for each note, even at natural pitches, to emphasize their
new approach to music theory and language.

This snippet shows how to achieve such notation rules. 

"
  doctitle = "Dodecaphonic-style accidentals for each note including naturals"
} % begin verbatim
webernAccidentals = {
  % the 5s are just "a value different from any accidental"
  \set Staff.keySignature = #'((0 . 5) (1 . 5) (2 . 5) (3 . 5)
                               (4 . 5) (5 . 5) (6 . 5))
  \set Staff.extraNatural = ##f
  #(set-accidental-style 'forget)
}

\score {
  {
    \webernAccidentals
    c'4 dis' cis' cis'
    c'4 dis' cis' cis'
    c'4 c' dis' des'
  }
  \layout {
    \context {
    \Staff
    \remove "Key_engraver"
    }
  }
}
