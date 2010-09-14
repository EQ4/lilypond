\version "2.13.31"

\header {
  texidoc = "
The @code{\\path} markup command supports the @code{filled}
property to toggle its fill.
"
}

\markup {
  \override #'(filled . #t) {
    \path #0.2 #'((moveto 1 1)
		  (lineto 1 6)
		  (curveto 3 8 5 6 1 1)
		  (closepath))
  }
}