/*
  music-iterator.cc -- implement {Music,Chord,Voice}_iterator

  source file of the GNU LilyPond music typesetter

  (c) 1997 Han-Wen Nienhuys <hanwen@stack.nl>
*/

#include "music-list.hh"
#include "music-iterator.hh"
#include "register.hh"
#include "register-group.hh"
#include "interpreter.hh"

IMPLEMENT_STATIC_NAME(Music_iterator);
IMPLEMENT_IS_TYPE_B(Music_iterator);

Register_group_register * 
Music_iterator::get_req_acceptor_l()
{
    assert(report_to_reg_l_);
    if (report_to_reg_l_->interpreter_l() )
	return report_to_reg_l_;

    report_to_reg_l_ =  report_to_reg_l_->get_default_interpreter();
    return report_to_reg_l_;
}

void
Music_iterator::construct_children()
{

}

Music_iterator::~Music_iterator(){
}

Moment
Music_iterator::next_moment()const
{
    return 0;
}

void
Music_iterator::next(Moment)
{
    first_b_ = false;
}

bool
Music_iterator::ok()const
{
    return first_b_;
}

Music_iterator*
Music_iterator::static_get_iterator_p(Music *m,
				      Register_group_register *report_l)
{
    Music_iterator * p =0;
    if (m->is_type_b( Change_reg::static_name()))
	p = new Change_iterator((Change_reg*)m);
    else if (m->is_type_b( Voice_element::static_name()))
	p = new Voice_element_iterator( (Voice_element*) m);
    else if (m->is_type_b( Chord::static_name())) 
	p =  new Chord_iterator( (Chord*) m);
    else if (m->is_type_b( Voice::static_name())) 
	p =  new Voice_iterator(  (Voice*) m);
    else if (m->is_type_b( Request::static_name() ))
	p =  new Request_iterator(  (Request*) m );
    
     if ( m->is_type_b( Music_list::static_name())) {
	Music_list* ml = (Music_list*) m;
	if (ml -> type_str_ != "") {
	    p->report_to_reg_l_ =
		report_l->find_get_reg_l(ml-> type_str_, ml->id_str_);
	    
	} 
    } 
     if (! p->report_to_reg_l_ )
	p ->report_to_reg_l_ = report_l;
    
    return p;
}

Music_iterator*
Music_iterator::get_iterator_p(Music*m)const
{
    Music_iterator*p = static_get_iterator_p(m,report_to_reg_l_);
    p->daddy_iter_l_ = (Music_iterator*)this;
    p->construct_children();
    return p;
}

Music_iterator::Music_iterator()
{
    daddy_iter_l_ =0;
    report_to_reg_l_ = 0;
    first_b_ = true;
}

/* ************** */

Chord_iterator::Chord_iterator(Chord const *chord_C)
{
    chord_C_ = chord_C;
}

void
Chord_iterator::construct_children()
{
    int j =0;
    for(iter(chord_C_->music_p_list_.top(), i); i.ok(); j++, i++) {
	
	Music_iterator * mi =  get_iterator_p( i.ptr());
	report_to_reg_l_ = mi->report_to_reg_l_->ancestor_l( chord_C_->multi_level_i_ );
	children_p_list_.bottom().add( mi );
    }
}

void
Chord_iterator::next(Moment until)
{
    for (iter(children_p_list_.top(), i); i.ok(); ) {
	if  (i->next_moment() == until) {
	    i->next(until);
	}
	if (!i->ok()) 
	    i.del();
	else
	    i++;
    }
    Music_iterator::next(until);

    assert(!ok() || next_moment() > until);
}

IMPLEMENT_STATIC_NAME(Chord_iterator);
IMPLEMENT_IS_TYPE_B1(Chord_iterator,Music_iterator);

Moment
Chord_iterator::next_moment()const
{
    Moment next_ = INFTY;
    for (iter(children_p_list_.top(), i); i.ok(); i++) 
	next_ = next_ <? i->next_moment() ;
    return next_;
}



bool
Chord_iterator::ok()const
{
    return children_p_list_.size();
}

/* ************** */

Voice_iterator::Voice_iterator(Voice const*v)
    : PCursor<Music*> ( v->music_p_list_)
{
    here_mom_ = v->offset_mom_;
    voice_C_ = v;
    iter_p_ =0;
}

void
Voice_iterator::construct_children()
{
    if (ok()) {
	
	iter_p_ = Music_iterator::get_iterator_p( ptr() );	
	report_to_reg_l_ = 
	    iter_p_->report_to_reg_l_->ancestor_l( voice_C_ ->multi_level_i_ );
    }
}

void
Voice_iterator::next_element()
{
    delete iter_p_ ;
    iter_p_ =0;
    here_mom_ += ptr()->time_int().length();
    PCursor<Music*>::next();
    construct_children();
}

Voice_iterator::~Voice_iterator()
{
    delete iter_p_;
}

IMPLEMENT_STATIC_NAME(Voice_iterator);
IMPLEMENT_IS_TYPE_B1(Voice_iterator,Music_iterator);

void
Voice_iterator::next(Moment until)
{
    while (ok()) {
	Moment local_until = until - here_mom_;
	while ( iter_p_ && iter_p_->ok() ) {
	    Moment here = iter_p_->next_moment();
	    if (here != local_until)
		return;
	    iter_p_->next(local_until);
	}
	if (!iter_p_)
	    iter_p_ = Music_iterator::get_iterator_p( ptr() );
	else if (!iter_p_->ok() )
	    next_element();
    }
    Music_iterator::next(until);
    assert(!ok() || next_moment() > until);
}

Moment
Voice_iterator::next_moment()const
{
    return iter_p_->next_moment() + here_mom_;
}

bool
Voice_iterator::ok()const
{
    return PCursor<Music*>::ok();
}

/* ***************** */

Request_iterator::Request_iterator(Request const*c)
{
    req_l_ = (Request*)c;
}

void
Request_iterator::next(Moment m)
{
    if ( !daddy_iter_l_->report_to_reg_l_->
	 interpreter_l()->interpret_request_b(req_l_) )
	req_l_->warning("Junking request: " + String(req_l_->name()));

    
    Music_iterator::next(m);
}

IMPLEMENT_STATIC_NAME(Request_iterator);
IMPLEMENT_IS_TYPE_B1(Request_iterator, Music_iterator);

/* ****************** */

Change_iterator::Change_iterator(Change_reg * ch)
{
    change_l_ = ch;
}

IMPLEMENT_STATIC_NAME(Change_iterator);
IMPLEMENT_IS_TYPE_B1(Change_iterator,Music_iterator);

/*
  TODO: pop/pushgroup
 */
void
Change_iterator::next(Moment mom)
{
    Register_group_register *group_l =
	report_to_reg_l_->find_get_reg_l(change_l_->type_str_, 
					 change_l_->id_str_);

    report_to_reg_l_->daddy_reg_l_->remove_register_p(report_to_reg_l_);
    group_l->add(report_to_reg_l_);

    Music_iterator::next(mom);
}



/* ******************** */

IMPLEMENT_STATIC_NAME(Voice_element_iterator);
IMPLEMENT_IS_TYPE_B1(Voice_element_iterator,Chord_iterator);

void
Voice_element_iterator::construct_children()
{
    if ( daddy_iter_l_ 
	 && daddy_iter_l_->is_type_b(Voice_iterator::static_name() )) {
	report_to_reg_l_ = daddy_iter_l_-> get_req_acceptor_l();
    } else if (daddy_iter_l_
	       && daddy_iter_l_-> is_type_b( Chord_iterator::static_name() )) {

	get_req_acceptor_l();
    }
    Chord_iterator::construct_children();
}

Voice_element_iterator::Voice_element_iterator(Voice_element*el_l)
    : Chord_iterator(el_l)
{
    
}
