%% Do not edit this file; it is auto-generated from LSR http://lsr.dsi.unimi.it
%% This file is in the public domain.
\version "2.11.62"

\header {
  lsrtags = "chords"

  texidoces = "
Las alteraciones y los signos «más» pueden aparecer antes o
después de los números, según el valor de las propiedades
@code{figuredBassAlterationDirection} y
@code{figuredBassPlusDirection}.

"
  doctitlees = "Cambiar las posiciones de las alteraciones del bajo cifrado"

  texidoc = "
Accidentals and plus signs can appear before or after the numbers,
depending on the @code{figuredBassAlterationDirection} and
@code{figuredBassPlusDirection} properties.

"
  doctitle = "Changing the positions of figured bass alterations"
} % begin verbatim
\figures {
  <6\+> <5+> <6 4-> r
  \set figuredBassAlterationDirection = #RIGHT
  <6\+> <5+> <6 4-> r
  \set figuredBassPlusDirection = #RIGHT
  <6\+> <5+> <6 4-> r
  \set figuredBassAlterationDirection = #LEFT
  <6\+> <5+> <6 4-> r
}
