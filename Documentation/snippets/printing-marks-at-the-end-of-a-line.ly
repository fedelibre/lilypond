%% Do not edit this file; it is automatically
%% generated from LSR http://lsr.dsi.unimi.it
%% This file is in the public domain.
\version "2.13.4"

\header {
%% Translation of GIT committish: c2e8b1d6d671dbfc138f890cbc7e9882b7be2761
  texidocfr = "
Les indications textuelles peuvent être imprimées à la fin d'une ligne 
plutôt qu'en tête de la suivante.  Pensez alors à aligner l'extrémité 
droite de l'indication sur la barre de mesure.

"
  doctitlefr = "Indication texuelle en fin de ligne"


  lsrtags = "text"

  texidoc = "
Marks can be printed at the end of the current line, instead of the
beginning of the following line.  In such cases, it might be preferable
to align the right end of the mark with the bar line.

"
  doctitle = "Printing marks at the end of a line"
} % begin verbatim

\relative c'' {
  g2 c
  d,2 a'
  \once \override Score.RehearsalMark #'break-visibility = #end-of-line-visible
  \once \override Score.RehearsalMark #'self-alignment-X = #RIGHT
  \mark "D.C. al Fine"
  \break
  g2 b,
  c1 \bar "||"
}

