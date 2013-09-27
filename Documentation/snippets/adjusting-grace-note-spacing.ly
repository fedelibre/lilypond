%% DO NOT EDIT this file manually; it is automatically
%% generated from LSR http://lsr.dsi.unimi.it
%% Make any changes in LSR itself, or in Documentation/snippets/new/ ,
%% and then run scripts/auxiliar/makelsr.py
%%
%% This file is in the public domain.
\version "2.17.27"

\header {
  lsrtags = "rhythms, tweaks-and-overrides"

  texidoc = "
The space given to grace notes can be adjusted using the
@code{spacing-increment} property of @code{Score.GraceSpacing}.

"
  doctitle = "Adjusting grace note spacing"
} % begin verbatim


graceNotes = {
  \grace { c4 c8 c16 c32 }
  c8
}

\relative c'' {
  c8
  \graceNotes
  \override Score.GraceSpacing.spacing-increment = #2.0
  \graceNotes
  \revert Score.GraceSpacing.spacing-increment
  \graceNotes
}
