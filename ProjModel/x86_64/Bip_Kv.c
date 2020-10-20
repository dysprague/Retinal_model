/* Created by Language version: 7.7.0 */
/* NOT VECTORIZED */
#define NRN_VECTORIZED 0
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "scoplib_ansi.h"
#undef PI
#define nil 0
#include "md1redef.h"
#include "section.h"
#include "nrniv_mf.h"
#include "md2redef.h"
 
#if METHOD3
extern int _method3;
#endif

#if !NRNGPU
#undef exp
#define exp hoc_Exp
extern double hoc_Exp(double);
#endif
 
#define nrn_init _nrn_init__IKv
#define _nrn_initial _nrn_initial__IKv
#define nrn_cur _nrn_cur__IKv
#define _nrn_current _nrn_current__IKv
#define nrn_jacob _nrn_jacob__IKv
#define nrn_state _nrn_state__IKv
#define _net_receive _net_receive__IKv 
#define evaluate_fct evaluate_fct__IKv 
#define states states__IKv 
 
#define _threadargscomma_ /**/
#define _threadargsprotocomma_ /**/
#define _threadargs_ /**/
#define _threadargsproto_ /**/
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 static double *_p; static Datum *_ppvar;
 
#define t nrn_threads->_t
#define dt nrn_threads->_dt
#define gkvbar _p[0]
#define m_inf _p[1]
#define h_inf _p[2]
#define tau_m _p[3]
#define tau_h _p[4]
#define m_exp _p[5]
#define h_exp _p[6]
#define m _p[7]
#define h _p[8]
#define ek _p[9]
#define Dm _p[10]
#define Dh _p[11]
#define ik _p[12]
#define _g _p[13]
#define _ion_ek	*_ppvar[0]._pval
#define _ion_ik	*_ppvar[1]._pval
#define _ion_dikdv	*_ppvar[2]._pval
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 
#if defined(__cplusplus)
extern "C" {
#endif
 static int hoc_nrnpointerindex =  -1;
 /* external NEURON variables */
 /* declaration of user functions */
 static void _hoc_evaluate_fct(void);
 static void _hoc_states(void);
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 
#define NMODL_TEXT 1
#if NMODL_TEXT
static const char* nmodl_file_text;
static const char* nmodl_filename;
extern void hoc_reg_nmodl_text(int, const char*);
extern void hoc_reg_nmodl_filename(int, const char*);
#endif

 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _p = _prop->param; _ppvar = _prop->dparam;
 }
 static void _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range(int);
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 hoc_retpushx(1.);
}
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 "setdata_IKv", _hoc_setdata,
 "evaluate_fct_IKv", _hoc_evaluate_fct,
 "states_IKv", _hoc_states,
 0, 0
};
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "gkvbar_IKv", "mho/cm2",
 0,0
};
 static double delta_t = 1;
 static double h0 = 0;
 static double m0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(_NrnThread*, _Memb_list*, int);
static void nrn_state(_NrnThread*, _Memb_list*, int);
 static void nrn_cur(_NrnThread*, _Memb_list*, int);
static void  nrn_jacob(_NrnThread*, _Memb_list*, int);
 
static int _ode_count(int);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"IKv",
 "gkvbar_IKv",
 0,
 "m_inf_IKv",
 "h_inf_IKv",
 "tau_m_IKv",
 "tau_h_IKv",
 "m_exp_IKv",
 "h_exp_IKv",
 0,
 "m_IKv",
 "h_IKv",
 0,
 0};
 static Symbol* _k_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 14, _prop);
 	/*initialize range parameters*/
 	gkvbar = 0.000318;
 	_prop->param = _p;
 	_prop->param_size = 14;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 3, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_k_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[0]._pval = &prop_ion->param[0]; /* ek */
 	_ppvar[1]._pval = &prop_ion->param[3]; /* ik */
 	_ppvar[2]._pval = &prop_ion->param[4]; /* _ion_dikdv */
 
}
 static void _initlists();
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _Bip_Kv_reg() {
	int _vectorized = 0;
  _initlists();
 	ion_reg("k", -10000.);
 	_k_sym = hoc_lookup("k_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 0);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 14, 3);
  hoc_register_dparam_semantics(_mechtype, 0, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "k_ion");
 	hoc_register_cvode(_mechtype, _ode_count, 0, 0, 0);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 IKv /Users/danielsprague/BME_515/ProjModel/x86_64/Bip_Kv.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int evaluate_fct(double);
static int states();
 
static int  states (  ) {
   evaluate_fct ( _threadargscomma_ v ) ;
   m = m + m_exp * ( m_inf - m ) ;
   h = h + h_exp * ( h_inf - h ) ;
   
/*VERBATIM*/
	return 0;
  return 0; }
 
static void _hoc_states(void) {
  double _r;
   _r = 1.;
 states (  );
 hoc_retpushx(_r);
}
 
static int  evaluate_fct (  double _lv ) {
   double _lam , _lbm , _lah , _lbh ;
 _lam = ( 400.0 ) / ( ( exp ( - ( _lv - 15.0 ) / 36.0 ) ) + 1.0 ) ;
   _lbm = ( exp ( ( - _lv / 13.0 ) ) ) ;
   tau_m = 1.0 / ( _lam + _lbm ) ;
   m_inf = _lam * tau_m ;
   m_exp = 1.0 - exp ( - dt / tau_m ) ;
   _lah = 0.0003 * ( exp ( ( - _lv / 7.0 ) ) ) ;
   _lbh = ( ( 80.0 ) / ( ( exp ( - ( _lv + 115.0 ) / 15.0 ) ) + 1.0 ) ) + 0.02 ;
   tau_h = 1.0 / ( _lah + _lbh ) ;
   h_inf = _lah * tau_h ;
   h_exp = 1.0 - exp ( - dt / tau_h ) ;
    return 0; }
 
static void _hoc_evaluate_fct(void) {
  double _r;
   _r = 1.;
 evaluate_fct (  *getarg(1) );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ hoc_execerror("IKv", "cannot be used with CVODE"); return 0;}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_k_sym, _ppvar, 0, 0);
   nrn_update_ion_pointer(_k_sym, _ppvar, 1, 3);
   nrn_update_ion_pointer(_k_sym, _ppvar, 2, 4);
 }

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  h = h0;
  m = m0;
 {
   m = 0.0345 ;
   h = 0.8594 ;
   }
  _sav_indep = t; t = _save;

}
}

static void nrn_init(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v = _v;
  ek = _ion_ek;
 initmodel();
 }}

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   ik = gkvbar * m * m * m * h * ( v - ek ) ;
   }
 _current += ik;

} return _current;
}

static void nrn_cur(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
  ek = _ion_ek;
 _g = _nrn_current(_v + .001);
 	{ double _dik;
  _dik = ik;
 _rhs = _nrn_current(_v);
  _ion_dikdv += (_dik - ik)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ik += ik ;
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
  }
 
}}

static void nrn_jacob(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) += _g;
  }else
#endif
  {
     _nd = _ml->_nodelist[_iml];
	NODED(_nd) += _g;
  }
 
}}

static void nrn_state(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v=_v;
{
  ek = _ion_ek;
 { error =  states();
 if(error){fprintf(stderr,"at line 54 in file Bip_Kv.mod:\n	SOLVE states\n"); nrn_complain(_p); abort_run(error);}
 } }}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
_first = 0;
}

#if NMODL_TEXT
static const char* nmodl_filename = "/Users/danielsprague/BME_515/ProjModel/Bip_Kv.mod";
static const char* nmodl_file_text = 
  "\n"
  "INDEPENDENT {t FROM 0 TO 1 WITH 1 (ms)}\n"
  "\n"
  "NEURON {\n"
  "	SUFFIX IKv\n"
  "	USEION k READ ek WRITE ik\n"
  "	RANGE gkvbar\n"
  "	RANGE m_inf, h_inf\n"
  "	RANGE tau_m, tau_h\n"
  "	RANGE m_exp, h_exp\n"
  "\n"
  "}\n"
  "\n"
  "\n"
  "UNITS {\n"
  "	(molar) = (1/liter)\n"
  "	(mM) = (millimolar)\n"
  "	(mA) = (milliamp)\n"
  "	(mV) = (millivolt)\n"
  "\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "	gkvbar	= 0.000318	(mho/cm2)\n"
  "	ek		(mV)\n"
  "	dt              (ms)\n"
  "	v               (mV)\n"
  "\n"
  "}\n"
  "\n"
  "STATE {\n"
  "	m h \n"
  "}\n"
  "\n"
  "INITIAL {\n"
  ": The initial values were determined at a resting value of -66.3232 mV in a single-compartment\n"
  ": at -60 mV\n"
  "        m = 0.0345\n"
  "        h = 0.8594\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	 ik	(mA/cm2)\n"
  "       m_inf \n"
  "	 h_inf\n"
  "	 tau_m \n"
  "	 tau_h\n"
  "	 m_exp \n"
  "       h_exp\n"
  "\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE states\n"
  "	ik = gkvbar * m*m*m *h* (v - ek)\n"
  "\n"
  "}\n"
  "\n"
  "PROCEDURE states() {	: exact when v held constant\n"
  "	evaluate_fct(v)\n"
  "	m = m + m_exp * (m_inf - m)\n"
  "	h = h + h_exp * (h_inf - h)\n"
  "\n"
  "	VERBATIM\n"
  "	return 0;\n"
  "	ENDVERBATIM\n"
  "\n"
  "}\n"
  "\n"
  "UNITSOFF\n"
  "\n"
  "PROCEDURE evaluate_fct(v(mV)) { LOCAL am,bm,ah,bh\n"
  "	\n"
  ":IA channel\n"
  "\n"
  " am = (400) / ((exp(-(v-15)/36)) + 1)\n"
  " bm = (exp((-v/13)))\n"
  " tau_m = 1 / (am + bm)\n"
  " m_inf = am * tau_m\n"
  " m_exp = 1 - exp(-dt/tau_m)\n"
  "\n"
  " ah = 0.0003 * (exp((-v/7)))\n"
  " bh = ((80) / ((exp(-(v+115)/15)) + 1))+0.02\n"
  " tau_h = 1 / (ah + bh)\n"
  " h_inf = ah * tau_h\n"
  " h_exp = 1 - exp(-dt/tau_h)\n"
  "\n"
  "}\n"
  "\n"
  "UNITSON\n"
  ;
#endif
