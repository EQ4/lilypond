\version "2.16.0"

#(ly:set-option 'warning-as-error #f)
#(ly:expect-warning (_ "margins do not fit with line-width, setting default values"))

\header {
  texidoc = "Margin values must fit the line-width, that means: paper-width =
line-width + left-margin + right-margin.  In case they do not, default margins
are set and a warning is printed."
}

someNotes = \relative c' { \repeat unfold 40 { c4 d e f } }

\paper {
  left-margin = 20 \mm
  right-margin = 40 \mm
  line-width = 100 \mm
}

\book {
  \score { \someNotes }
}
