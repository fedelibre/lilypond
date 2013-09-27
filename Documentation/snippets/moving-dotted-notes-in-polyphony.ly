%% DO NOT EDIT this file manually; it is automatically
%% generated from LSR http://lsr.dsi.unimi.it
%% Make any changes in LSR itself, or in Documentation/snippets/new/ ,
%% and then run scripts/auxiliar/makelsr.py
%%
%% This file is in the public domain.
\version "2.17.27"

\header {
  lsrtags = "rhythms, simultaneous-notes, tweaks-and-overrides"

  texidoc = "
When a dotted note in the upper voice is moved to avoid a collision
with a note in another voice, the default is to move the upper note to
the right.  This behaviour can be over-ridden by using the
@code{prefer-dotted-right} property of @code{NoteCollision}.

"
  doctitle = "Moving dotted notes in polyphony"
} % begin verbatim


\new Staff \relative c' <<
  { f2. f4
    \override Staff.NoteCollision.prefer-dotted-right = ##f
    f2. f4
    \override Staff.NoteCollision.prefer-dotted-right = ##t
    f2. f4
  }
  \\
  { e4 e e e e e e e e e e e}
>>
