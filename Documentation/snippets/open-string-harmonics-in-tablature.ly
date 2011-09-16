% DO NOT EDIT this file manually; it is automatically
% generated from Documentation/snippets/new
% Make any changes in Documentation/snippets/new/
% and then run scripts/auxiliar/makelsr.py
%
% This file is in the public domain.
%% Note: this file works from version 2.14.0
\version "2.14.0"

\header {
%% Translation of GIT committish: 70f5f30161f7b804a681cd080274bfcdc9f4fe8c
  texidoces = "
Referencia para armónicos sobre cuerdas al aire (armónicos naturales):

"
  doctitlees = "Referencia para armónicos sobre cuerdas al aire"

%% Translation of GIT committish: f86f00c1a8de0f034ba48506de2801c074bd5422
  texidocde = "
Referenz für Flageolett von offenen Saiten:
"
  doctitlede = "Referenz für Flageolett von offenen Saiten"

%% Translation of GIT committish: 40bf2b38d674c43f38058494692d1a0993fad0bd
  texidocfr = "
Table des harmoniques sur corde à vide (harmoniques naturelles):

"
  doctitlefr = "Table des harmoniques sur corde à vide"



  lsrtags = "fretted-strings"
  texidoc = "
Reference for open-string harmonics:
"
  doctitle = "Reference for open-string harmonics"
} % begin verbatim


openStringHarmonics = {
  %first harmonic
  \harmonicByFret #12 e,2\6_\markup{"1st harm."}
  \harmonicByRatio #1/2 e,\6
  %second harmonic
  \harmonicByFret #7 e,\6_\markup{"2nd harm. - - - -"}
  \harmonicByRatio #1/3 e,\6
  \harmonicByFret #19 e,\6
  \harmonicByRatio #2/3 e,\6
  %\harmonicByFret #19 < e,\6 a,\5 d\4 >
  %\harmonicByRatio #2/3 < e,\6 a,\5 d\4 >
  %third harmonic
  \harmonicByFret #5 e,\6_\markup{"3rd harm. - - - -"}
  \harmonicByRatio #1/4 e,\6
  \harmonicByFret #24 e,\6
  \harmonicByRatio #3/4 e,\6
  \break
  %fourth harmonic
  \harmonicByFret #4 e,\6_\markup{"4th harm. - - - - - - - - - - - - -"}
  \harmonicByRatio #1/5 e,\6
  \harmonicByFret #9 e,\6
  \harmonicByRatio #2/5 e,\6
  \harmonicByFret #16 e,\6
  \harmonicByRatio #3/5 e,\6
  %fifth harmonic
  \harmonicByFret #3 e,\6_\markup{"5th harm."}
  \harmonicByRatio #1/6 e,\6
  \break
  %sixth harmonic
  \harmonicByFret #2.7 e,\6_\markup{"6th harm."}
  \harmonicByRatio #1/7 e,\6
  %seventh harmonic
  \harmonicByFret #2.3 e,\6_\markup{"7th harm."}
  \harmonicByRatio #1/8 e,\6
  %eighth harmonic
  \harmonicByFret #2 e,\6_\markup{"8th harm."}
  \harmonicByRatio #1/9 e,\6
}

\score {
  <<
    \new Staff {
      \new Voice {
        \clef "treble_8"
        \openStringHarmonics
      }
    }
    \new TabStaff {
      \new TabVoice {
        \openStringHarmonics
      }
    }
  >>
}
