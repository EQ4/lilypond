/*
  translator.hh -- declare Translator

  source file of the GNU LilyPond music typesetter

  (c)  1997--2003 Han-Wen Nienhuys <hanwen@cs.uu.nl>
*/


#ifndef TRANSLATOR_HH
#define TRANSLATOR_HH

#include "global-ctor.hh"
#include "string.hh"
#include "lily-proto.hh"
#include "virtual-methods.hh"
#include "lily-guile.hh"
#include "input.hh"
#include "smobs.hh"

#define get_property(x) internal_get_property(ly_symbol2scm(x))


#define TRANSLATOR_DECLARATIONS(NAME)			\
public:							\
  NAME();\
  VIRTUAL_COPY_CONS (Translator);				\
  static SCM static_description_;			\
  virtual SCM static_translator_description () const;	\
  virtual SCM translator_description () const;

/*
  Translate music into grobs.
*/
class Translator
{
  void init ();
public:
  Music_output_def * output_def_;
  
  bool is_alias (SCM) const;
  Translator (Translator const &);

  
  Translator_group * daddy_trans_ ;
  void removal_processing ();
  /**
    ask daddy for a feature
    */
  Music_output_def *get_output_def () const;

  SCM internal_get_property (SCM symbol) const;
  
  virtual Moment now_mom () const;  

  /*
    ugh: bubbled up.
   */
  SCM definition_;
  SCM properties_scm_;
  SCM trans_group_list_;

  virtual SCM get_simple_trans_list ();
public:
  DECLARE_SMOBS (Translator, dummy);
private:
  /*
    ugh: bubbled up from Translator_group. 
   */

protected:			// should be private.
  SCM simple_trans_list_;

  // ugr.
  //   friend SCM Translator_group::get_simple_trans_list ();


public:
  Global_translator * top_translator () const;
  TRANSLATOR_DECLARATIONS(Translator);
  virtual bool try_music (Music *req);
  virtual void stop_translation_timestep ();
  virtual void start_translation_timestep ();
  virtual void do_announces () ;
  virtual void initialize () ;
  virtual void finalize ();
};


/**
  A macro to automate administration of translators.
 */
#define ADD_THIS_TRANSLATOR(T)				\
SCM T::static_description_ = SCM_EOL;\
static void  _ ## T ## _adder () {\
      T *t = new T;\
      T::static_description_ = t->static_translator_description ();\
      scm_permanent_object (T::static_description_);\
      add_translator (t);\
}\
SCM T::translator_description() const\
{ \
  return static_description_;\
}\
ADD_GLOBAL_CTOR (_ ## T ## _adder);




#define ENTER_DESCRIPTION(classname,desc,grobs,accepted,acked,read,write)						\
ADD_THIS_TRANSLATOR (classname);\
SCM												\
classname::static_translator_description () const \
{												\
  SCM  static_properties= SCM_EOL;								\
  /*  static_properties= acons (name ,gh_str02scm (Translator::name (self_scm ())),		\
			      static_properties_);						\
  */												\
  static_properties= scm_acons (ly_symbol2scm ("grobs-created"),				\
			      parse_symbol_list (grobs), static_properties);	\
			      									\
  static_properties= scm_acons (ly_symbol2scm ("description"),					\
			      scm_makfrom0str (desc), static_properties);				\
												\
  static_properties= scm_acons (ly_symbol2scm ("interfaces-acked"),				\
			      parse_symbol_list (acked), static_properties);			\
  static_properties= scm_acons (ly_symbol2scm ("events-accepted"),				\
			      parse_symbol_list (accepted), static_properties);			\
  												\
  static_properties= scm_acons (ly_symbol2scm ("properties-read"),				\
			      parse_symbol_list (read), static_properties);			\
												\
  static_properties= scm_acons (ly_symbol2scm ("properties-written"),				\
				parse_symbol_list (write), static_properties);			\
												\
  return static_properties;									\
}



void add_translator (Translator*trans);

Translator*get_translator (SCM s);
DECLARE_UNSMOB(Translator,translator);
#endif // TRANSLATOR_HH
