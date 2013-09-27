%% DO NOT EDIT this file manually; it is automatically
%% generated from LSR http://lsr.dsi.unimi.it
%% Make any changes in LSR itself, or in Documentation/snippets/new/ ,
%% and then run scripts/auxiliar/makelsr.py
%%
%% This file is in the public domain.
\version "2.17.27"

\header {
  lsrtags = "chords, keyboards, tweaks-and-overrides, workaround"

  texidoc = "
Sometimes it is better to use stems from the upper staff for creating
cross-staff chords, because no problems with automatic beam collision
avoidance then arise.  If the stems from the lower staff were used in
the following example, it would be necessary to change the automatic
beam collision avoidance settings so that it doesn't detect collisions
between staves using @code{\\override Staff.Beam.collision-voice-only
= ##t}

"
  doctitle = "Cross-staff chords - beaming problems workaround"
} % begin verbatim


\new PianoStaff <<
  \new Staff = up
    \relative c' {
      <<
        { r4
          \override Stem.cross-staff = ##t
          \override Stem.length = #19 % this is in half-spaces,
              % so it makes stems 9.5 staffspaces long
          \override Stem.Y-offset = #-6 % stems are normally lengthened
              % upwards, so here we must lower the stem by the amount
              % equal to the lengthening - in this case (19 - 7) / 2
              % (7 is default stem length)
          e e e }
        { s4
          \change Staff = "bottom"
          \override NoteColumn.ignore-collision = ##t
          c, c c
        }
      >>
    }
  \new Staff = bottom
    \relative c' {
      \clef bass
      \voiceOne
      g8 a g a g a g a
    }
>>
