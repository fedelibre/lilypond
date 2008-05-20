%% Do not edit this file; it is auto-generated from LSR http://lsr.dsi.unimi.it
%% This file is in the public domain.
\version "2.11.46"

\header {
  lsrtags = "rhythms, expressive-marks, staff-notation, tweaks-and-overrides"

  texidoc = "
By default, metronome and rehearsal marks are printed above the staff. 
To place them below the staff simply set the @code{side-axis} and
@code{direction} properties of @code{MetronomeMark} or
@code{RehearsalMark} appropriately.

"
  doctitle = "Printing metronome and rehearsal marks below the staff"
} % begin verbatim
{
  % Metronome marks below the staff

  \override Score.MetronomeMark #'side-axis = #Y
  \override Score.MetronomeMark #'direction = #DOWN
  \tempo 8. = 120
  c''1

  % Rehearsal marks below the staff

  \override Score.RehearsalMark #'side-axis = #Y
  \override Score.RehearsalMark #'direction = #DOWN
  \mark \default
  c''1
}
