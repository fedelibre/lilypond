/*
  bar.cc -- implement Bar

  source file of the GNU LilyPond music typesetter

  (c)  1997--1999 Han-Wen Nienhuys <hanwen@cs.uu.nl>
*/

#include "dimension-cache.hh"
#include "bar.hh"
#include "string.hh"
#include "molecule.hh"
#include "paper-def.hh"
#include "lookup.hh"
#include "debug.hh"


Bar::Bar ()
{
  set_elt_property ("breakable", SCM_BOOL_T);
}


Real
Bar::get_bar_size () const
{
  // Never called!
  return 0;
}


Molecule*
Bar::do_brew_molecule_p () const
{
  String s = ly_scm2string (get_elt_property ("glyph"));
  Molecule *output
    = new Molecule (lookup_l ()->bar (s, get_bar_size (), paper_l ()));
  
  return output;
}



void
Bar::do_pre_processing ()
{
  SCM def = remove_elt_property ("default-glyph");
  SCM g = get_elt_property ("glyph");
  if (!gh_string_p (g) && gh_string_p (def))
    {
      set_elt_property ("glyph", def);
      g = get_elt_property ("glyph");
    }

  SCM breakdir = gh_int2scm (break_status_dir ());
  
  if (gh_string_p (g))
    {
      g = scm_eval (gh_list (ly_symbol2scm ("break-barline"),
			     g,
			     breakdir,
			     SCM_UNDEFINED));
    }
  else
    {
      g = SCM_UNDEFINED;
    }
  
#if 0  
  if (remove_elt_property ("at-line-start") == SCM_BOOL_T	// UGR.
      && (break_status_dir () == RIGHT) && (type_str_ == ""))
    {
      type_str_ = "|";
    }
#endif
  
  if (!gh_string_p (g))
    {
      set_elt_property ("transparent", SCM_BOOL_T);
      set_empty (X_AXIS);      
    }
  else
    set_elt_property ("glyph", g);
}
  

