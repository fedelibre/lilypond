/*
  music-list.cc -- implement Music_list, Chord, Voice

  source file of the GNU LilyPond music typesetter

  (c) 1997 Han-Wen Nienhuys <hanwen@stack.nl>
*/


#include "music.hh"
#include "debug.hh"
#include "music-list.hh"

Music_list::Music_list(Music_list const&s)
{
    multi_level_i_ = s.multi_level_i_;   
    for (iter(s.music_p_list_.top(), i); i.ok(); i++)
	add(i->clone());
}

IMPLEMENT_STATIC_NAME(Music_list);
IMPLEMENT_STATIC_NAME(Chord);
IMPLEMENT_STATIC_NAME(Voice);
IMPLEMENT_IS_TYPE_B1(Music_list, Music);
IMPLEMENT_IS_TYPE_B1(Voice,Music_list);
IMPLEMENT_IS_TYPE_B1(Chord,Music_list);

MInterval
Chord::time_int()const
{
    MInterval m;
    for (iter(music_p_list_.top(), i); i.ok(); i++)
	m.unite(i->time_int());
    return m;
}
void
Chord::translate(Moment m)
{
    for (iter(music_p_list_.top(), i); i.ok(); i++)
	i->translate(m); 
}

Chord::Chord()
{

}

Voice::Voice()
{
    offset_mom_ =0;
}

MInterval
Voice::time_int() const
{
    Moment last=0;
    for (iter(music_p_list_.top(), i); i.ok(); i++)
	last += i->time_int().length();
    return  offset_mom_ + MInterval(0,last);
}

void
Voice::translate(Moment dt)
{
    offset_mom_ += dt;
}


Music_list::Music_list()
{
    multi_level_i_ = 0;
}

void
Music_list::add(Music*m_p)
{
    if (!m_p)
	return;

    m_p->parent_music_l_ = this;
    music_p_list_.bottom().add(m_p);
}

void
Music_list::transpose(Melodic_req const*rq)
{
    for (iter(music_p_list_.top(),i); i.ok(); i++)
	i->transpose(rq);    
}

void
Music_list::do_print()const
{
#ifndef NPRINT
    for (iter(music_p_list_.top(),i); i.ok(); i++)
	i->print();
#endif 
}

IMPLEMENT_IS_TYPE_B1(Voice_element, Chord);
IMPLEMENT_STATIC_NAME(Voice_element);

Voice_element::Voice_element()
{
    multi_level_i_ =0;
}
