\version "1.3.120";

instrument = "Orchestra"
% instrument = ""

\include "header.ly"
\include "global.ly"

\include "paper16.ly"

\include "bassi.ly"
\include "clarinetti.ly"
\include "corni.ly"
\include "fagotti.ly"
\include "flauti.ly"
\include "oboi.ly"
\include "timpani.ly"
\include "trombe.ly"
\include "viole.ly"
\include "violino-1.ly"
\include "violino-2.ly"


legniGroup =  \context StaffGroup = legni_group <
	\flautiStaff
	\oboiStaff
	\clarinettiStaff
	\fagottiStaff
>

ottoniGroup =  \context StaffGroup = otonni_group <
	\corniStaff
	\trombeStaff
>

timpaniGroup =  \context StaffGroup = timpani_group <
	\timpaniStaff
	% Force a staff bracket (?)
	\context Staff = timpany \End
>

violiniGroup =  \context GrandStaff = violini_group <
	\violinoIStaff
	\violinoIIStaff
>

archiGroup =  \context StaffGroup = archi_group <
	\violiniGroup
	\violeGroup
	\bassiGroup
>


\score{
	<
		\legniGroup
		\ottoniGroup
		\timpaniGroup
		\archiGroup
	>
	\header{
		instrument = "";
	}
	\include "coriolan-paper.ly"
%	\include "coriolan-midi.ly"
}



%%
%% Hopefully, this can be junked when part-combiner+midi+dynamics work ok.
%%
\score{
	<
	\global
	\context Staff=flauti <
		\property Staff.midiInstrument = #"flute"
		\flautoI
		\flautoII
	>
	\context Staff=oboi <
		\property Staff.midiInstrument = #"oboe"
		\oboeI
		\oboeII
	>
	\context Staff=clarinetti <
		\property Staff.midiInstrument = #"clarinet"
		\property Staff.transposing = #-2
		\clarinettoI
		\clarinettoII
	>
	\context Staff=fagotti <
		\property Staff.midiInstrument = #"bassoon"
		\fagottoI
		\fagottoII
	>
	\context Staff=corni <
		\property Staff.midiInstrument = #"french horn"
		\property Staff.transposing = #3
		\cornoI
		\cornoII
	>
	\context Staff=trombe <
		\property Staff.midiInstrument = #"trumpet"
		\tromboI
		\tromboII
	>
	\context Staff=timpani <
		\property Staff.midiInstrument = #"timpani"
		\timpani
	>
	\context Staff=violini <
		\property Staff.midiInstrument = #"violin"
		\violinoI
		\violinoII
	>
	\context Staff=violi <
		\property Staff.midiInstrument = #"viola"
		\violaI
		\violaII
	>
	\context Staff=violoncello <
		\property Staff.midiInstrument = #"cello"
		\violoncello
	>
	\context Staff=contrabasso <
		\property Staff.midiInstrument = #"contrabass"
        	\property Staff.transposing = #-12
		\contrabasso
	>
	>
	\include "coriolan-midi.ly"
}
