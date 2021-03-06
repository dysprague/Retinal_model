/* Created by Language version: 7.7.0 */
/* VECTORIZED */
#define NRN_VECTORIZED 1
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
 
#define nrn_init _nrn_init__Kca
#define _nrn_initial _nrn_initial__Kca
#define nrn_cur _nrn_cur__Kca
#define _nrn_current _nrn_current__Kca
#define nrn_jacob _nrn_jacob__Kca
#define nrn_state _nrn_state__Kca
#define _net_receive _net_receive__Kca 
 
#define _threadargscomma_ _p, _ppvar, _thread, _nt,
#define _threadargsprotocomma_ double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt,
#define _threadargs_ _p, _ppvar, _thread, _nt
#define _threadargsproto_ double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 /* Thread safe. No static _p or _ppvar. */
 
#define t _nt->_t
#define dt _nt->_dt
#define eKca _p[0]
#define gKcabar _p[1]
#define Cahalf _p[2]
#define mKcaCa _p[3]
#define Cai _p[4]
#define DmKcaCa _p[5]
#define iKca _p[6]
#define gKca _p[7]
#define v _p[8]
#define _g _p[9]
#define _ion_Cai	*_ppvar[0]._pval
#define _ion_iKca	*_ppvar[1]._pval
#define _ion_diKcadv	*_ppvar[2]._pval
 
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
 static Datum* _extcall_thread;
 static Prop* _extcall_prop;
 /* external NEURON variables */
 /* declaration of user functions */
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
 _extcall_prop = _prop;
 }
 static void _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range(int);
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 hoc_retpushx(1.);
}
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 "setdata_Kca", _hoc_setdata,
 0, 0
};
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "eKca_Kca", "mV",
 "gKcabar_Kca", "mS/cm2",
 "Cahalf_Kca", "uM",
 0,0
};
 static double mKcaCa0 = 0;
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
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"Kca",
 "eKca_Kca",
 "gKcabar_Kca",
 "Cahalf_Kca",
 0,
 0,
 "mKcaCa_Kca",
 0,
 0};
 static Symbol* _Ca_sym;
 static Symbol* _Kca_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 10, _prop);
 	/*initialize range parameters*/
 	eKca = -80;
 	gKcabar = 5;
 	Cahalf = 0.32;
 	_prop->param = _p;
 	_prop->param_size = 10;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 3, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_Ca_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[0]._pval = &prop_ion->param[1]; /* Cai */
 prop_ion = need_memb(_Kca_sym);
 	_ppvar[1]._pval = &prop_ion->param[3]; /* iKca */
 	_ppvar[2]._pval = &prop_ion->param[4]; /* _ion_diKcadv */
 
}
 static void _initlists();
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _Rod_Kca_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("Ca", 2.0);
 	ion_reg("Kca", 1.0);
 	_Ca_sym = hoc_lookup("Ca_ion");
 	_Kca_sym = hoc_lookup("Kca_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 10, 3);
  hoc_register_dparam_semantics(_mechtype, 0, "Ca_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "Kca_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "Kca_ion");
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 Kca /Users/danielsprague/BME_515/ProjModel/x86_64/Rod_Kca.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_Ca_sym, _ppvar, 0, 1);
   nrn_update_ion_pointer(_Kca_sym, _ppvar, 1, 3);
   nrn_update_ion_pointer(_Kca_sym, _ppvar, 2, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  int _i; double _save;{
  mKcaCa = mKcaCa0;
 {
   double _lCas ;
 _lCas = Cai * 1000.0 ;
   mKcaCa = 1.0 / ( 1.0 + pow( ( Cahalf / _lCas ) , 4.0 ) ) ;
   }

}
}

static void nrn_init(_NrnThread* _nt, _Memb_list* _ml, int _type){
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
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
  Cai = _ion_Cai;
 initmodel(_p, _ppvar, _thread, _nt);
 }
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   double _lCas ;
 _lCas = Cai * 1000.0 ;
   mKcaCa = 1.0 / ( 1.0 + pow( ( Cahalf / _lCas ) , 4.0 ) ) ;
   gKca = ( 0.001 ) * gKcabar * pow( mKcaCa , 4.0 ) ;
   iKca = gKca * ( v - eKca ) ;
   }
 _current += iKca;

} return _current;
}

static void nrn_cur(_NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
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
  Cai = _ion_Cai;
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ double _diKca;
  _diKca = iKca;
 _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
  _ion_diKcadv += (_diKca - iKca)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_iKca += iKca ;
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
  }
 
}
 
}

static void nrn_jacob(_NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
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
 
}
 
}

static void nrn_state(_NrnThread* _nt, _Memb_list* _ml, int _type) {

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/Users/danielsprague/BME_515/ProjModel/Rod_Kca.mod";
static const char* nmodl_file_text = 
  ":Calcium Activated Potassium Channels\n"
  "\n"
  "NEURON \n"
  "{\n"
  "	SUFFIX Kca\n"
  "	USEION Ca READ Cai VALENCE 2\n"
  "	USEION Kca WRITE iKca VALENCE 1\n"
  "	RANGE infmKcaV,taumKcaV,eKca,gKcabar,Cahalf\n"
  "}\n"
  "\n"
  "UNITS\n"
  "{\n"
  "	(mA) = (milliamp)\n"
  "	(mV) = (millivolt)\n"
  "	(mS) = (millimho)\n"
  "	(mol)= (1)\n"
  "	(M)  = (mol/liter)\n"
  "	(uM) = (micro M)\n"
  "}\n"
  "\n"
  "PARAMETER\n"
  "{\n"
  "       \n"
  " \n"
  "       :Ca-dependent K current\n"
  "       eKca=-80 (mV)\n"
  "       gKcabar = 5 (mS/cm2)\n"
  "       Cai\n"
  "	Cahalf=0.32 (uM)	 \n"
  " \n"
  "\n"
  "}\n"
  "\n"
  "STATE\n"
  "{\n"
  "\n"
  "	:mKcaV\n"
  "	mKcaCa\n"
  "	\n"
  "}\n"
  "\n"
  "ASSIGNED\n"
  "{\n"
  "	iKca (mA/cm^2)\n"
  "	v (mV)\n"
  "           :Ca-dependent potassium channel, Kca\n"
  "	:infmKcaV\n"
  "	:taumKcaV  (ms)\n"
  "	gKca (mho/cm2)\n"
  "\n"
  "}\n"
  "\n"
  "INITIAL\n"
  "{      LOCAL Cas\n"
  "	:rate(v)\n"
  "	Cas=Cai*1000 :uM\n"
  "\n"
  "	:mKcaV= infmKcaV\n"
  "        :Cas=Cai\n"
  "        mKcaCa=1/(1+(Cahalf/Cas)^4)\n"
  "}\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "BREAKPOINT\n"
  "{\n"
  "	LOCAL Cas\n"
  "	:SOLVE states METHOD cnexp\n"
  "	Cas=Cai*1000 :uM\n"
  "	mKcaCa=1/(1+(Cahalf/Cas)^4 )\n"
  "	:gKca=(0.001)*gKcabar*(mKcaV^2)*mKcaCa\n"
  "        gKca=(0.001)*gKcabar*mKcaCa^4\n"
  "	iKca=gKca*(v-eKca) \n"
  "	: the current is in the unit of mA/cm2\n"
  "	\n"
  "}\n"
  "\n"
  ;
#endif
