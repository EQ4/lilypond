%% DO NOT EDIT this file manually; it is automatically
%% generated from LSR http://lsr.di.unimi.it
%% Make any changes in LSR itself, or in Documentation/snippets/new/ ,
%% and then run scripts/auxiliar/makelsr.py
%%
%% This file is in the public domain.
\version "2.18.0"

\header {
  lsrtags = "repeats, tweaks-and-overrides"

  texidoc = "
A @code{|:} bar line can be printed at the beginning of a piece.

"
  doctitle = "Printing a repeat sign at the beginning of a piece"
} % begin verbatim

\relative c'' {
  \bar ".|:"
  \repeat volta 2 {
    c1
    d1
    d4 e f g
  }
}
