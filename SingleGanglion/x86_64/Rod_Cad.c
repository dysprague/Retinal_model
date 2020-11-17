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
 
#define nrn_init _nrn_init__Cad
#define _nrn_initial _nrn_initial__Cad
#define nrn_cur _nrn_cur__Cad
#define _nrn_current _nrn_current__Cad
#define nrn_jacob _nrn_jacob__Cad
#define nrn_state _nrn_state__Cad
#define _net_receive _net_receive__Cad 
#define state state__Cad 
 
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
#define depth _p[0]
#define taur _p[1]
#define Cainf _p[2]
#define entryF _p[3]
#define Ca _p[4]
#define Cai _p[5]
#define Cao _p[6]
#define DCa _p[7]
#define iCa _p[8]
#define drive_channel _p[9]
#define v _p[10]
#define _g _p[11]
#define _ion_iCa	*_ppvar[0]._pval
#define _ion_Cai	*_ppvar[1]._pval
#define _ion_Cao	*_ppvar[2]._pval
#define _style_Ca	*((int*)_ppvar[3]._pvoid)
 
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
 "setdata_Cad", _hoc_setdata,
 0, 0
};
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "depth_Cad", "um",
 "taur_Cad", "ms",
 "Cainf_Cad", "mM",
 "Ca_Cad", "mM",
 0,0
};
 static double Ca0 = 0;
 static double delta_t = 1;
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
static void _ode_map(int, double**, double**, double*, Datum*, double*, int);
static void _ode_spec(_NrnThread*, _Memb_list*, int);
static void _ode_matsol(_NrnThread*, _Memb_list*, int);
 
#define _cvode_ieq _ppvar[4]._i
 static void _ode_synonym(int, double**, Datum**);
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"Cad",
 "depth_Cad",
 "taur_Cad",
 "Cainf_Cad",
 "entryF_Cad",
 0,
 0,
 "Ca_Cad",
 0,
 0};
 static Symbol* _Ca_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 12, _prop);
 	/*initialize range parameters*/
 	depth = 10;
 	taur = 20;
 	Cainf = 5e-05;
 	entryF = 1;
 	_prop->param = _p;
 	_prop->param_size = 12;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 5, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_Ca_sym);
 nrn_check_conc_write(_prop, prop_ion, 1);
 nrn_check_conc_write(_prop, prop_ion, 0);
 nrn_promote(prop_ion, 3, 0);
 	_ppvar[0]._pval = &prop_ion->param[3]; /* iCa */
 	_ppvar[1]._pval = &prop_ion->param[1]; /* Cai */
 	_ppvar[2]._pval = &prop_ion->param[2]; /* Cao */
 	_ppvar[3]._pvoid = (void*)(&(prop_ion->dparam[0]._i)); /* iontype for Ca */
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _thread_mem_init(Datum*);
 static void _thread_cleanup(Datum*);
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _Rod_Cad_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("Ca", 2.0);
 	_Ca_sym = hoc_lookup("Ca_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 5);
  _extcall_thread = (Datum*)ecalloc(4, sizeof(Datum));
  _thread_mem_init(_extcall_thread);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 1, _thread_mem_init);
     _nrn_thread_reg(_mechtype, 0, _thread_cleanup);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 12, 5);
  hoc_register_dparam_semantics(_mechtype, 0, "Ca_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "Ca_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "Ca_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "#Ca_ion");
  hoc_register_dparam_semantics(_mechtype, 4, "cvodeieq");
 	nrn_writes_conc(_mechtype, 0);
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_synonym(_mechtype, _ode_synonym);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 Cad /Users/danielsprague/BME_515/ProjModel/x86_64/Rod_Cad.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double FARADAY = 96485.3;
static int _reset;
static char *modelname = "decay of internal calcium concentration";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
 
#define _deriv1_advance _thread[0]._i
#define _dith1 1
#define _recurse _thread[2]._i
#define _newtonspace1 _thread[3]._pvoid
extern void* nrn_cons_newtonspace(int);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist2[1];
  static int _slist1[1], _dlist1[1];
 static int state(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {int _reset = 0; {
   drive_channel = - ( 10000.0 ) * iCa / ( 2.0 * FARADAY * depth ) ;
   if ( drive_channel <= 0. ) {
     drive_channel = 0. ;
     }
   DCa = entryF * drive_channel / 2.0 + ( Cainf - Ca ) / taur ;
   Cai = Ca ;
   Cao = 2.0 ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
 drive_channel = - ( 10000.0 ) * iCa / ( 2.0 * FARADAY * depth ) ;
 if ( drive_channel <= 0. ) {
   drive_channel = 0. ;
   }
 DCa = DCa  / (1. - dt*( ( ( ( - 1.0 ) ) ) / taur )) ;
 Cai = Ca ;
 Cao = 2.0 ;
  return 0;
}
 /*END CVODE*/
 
static int state (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {int _reset=0; int error = 0;
 { double* _savstate1 = _thread[_dith1]._pval;
 double* _dlist2 = _thread[_dith1]._pval + 1;
 int _counte = -1;
 if (!_recurse) {
 _recurse = 1;
 {int _id; for(_id=0; _id < 1; _id++) { _savstate1[_id] = _p[_slist1[_id]];}}
 error = nrn_newton_thread(_newtonspace1, 1,_slist2, _p, state, _dlist2, _ppvar, _thread, _nt);
 _recurse = 0; if(error) {abort_run(error);}}
 {
   drive_channel = - ( 10000.0 ) * iCa / ( 2.0 * FARADAY * depth ) ;
   if ( drive_channel <= 0. ) {
     drive_channel = 0. ;
     }
   DCa = entryF * drive_channel / 2.0 + ( Cainf - Ca ) / taur ;
   Cai = Ca ;
   Cao = 2.0 ;
   {int _id; for(_id=0; _id < 1; _id++) {
if (_deriv1_advance) {
 _dlist2[++_counte] = _p[_dlist1[_id]] - (_p[_slist1[_id]] - _savstate1[_id])/dt;
 }else{
_dlist2[++_counte] = _p[_slist1[_id]] - _savstate1[_id];}}}
 } }
 return _reset;}
 
static int _ode_count(int _type){ return 1;}
 
static void _ode_spec(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  iCa = _ion_iCa;
  Cai = _ion_Cai;
  Cai = _ion_Cai;
  Cao = _ion_Cao;
     _ode_spec1 (_p, _ppvar, _thread, _nt);
  _ion_Cai = Cai;
  _ion_Cao = Cao;
 }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 1; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 static void _ode_synonym(int _cnt, double** _pp, Datum** _ppd) { 
	double* _p; Datum* _ppvar;
 	int _i; 
	for (_i=0; _i < _cnt; ++_i) {_p = _pp[_i]; _ppvar = _ppd[_i];
 _ion_Cai =  Ca ;
 _ion_Cao =  2.0 ;
 }}
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _ode_matsol1 (_p, _ppvar, _thread, _nt);
 }
 
static void _ode_matsol(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  iCa = _ion_iCa;
  Cai = _ion_Cai;
  Cai = _ion_Cai;
  Cao = _ion_Cao;
 _ode_matsol_instance1(_threadargs_);
 }}
 
static void _thread_mem_init(Datum* _thread) {
   _thread[_dith1]._pval = (double*)ecalloc(2, sizeof(double));
   _newtonspace1 = nrn_cons_newtonspace(1);
 }
 
static void _thread_cleanup(Datum* _thread) {
   free((void*)(_thread[_dith1]._pval));
   nrn_destroy_newtonspace(_newtonspace1);
 }
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_Ca_sym, _ppvar, 0, 3);
   nrn_update_ion_pointer(_Ca_sym, _ppvar, 1, 1);
   nrn_update_ion_pointer(_Ca_sym, _ppvar, 2, 2);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  int _i; double _save;{
  Ca = Ca0;
 {
   Ca = Cainf ;
   Cao = 2.0 ;
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
  iCa = _ion_iCa;
  Cai = _ion_Cai;
  Cai = _ion_Cai;
  Cao = _ion_Cao;
 initmodel(_p, _ppvar, _thread, _nt);
  _ion_Cai = Cai;
  _ion_Cao = Cao;
  nrn_wrote_conc(_Ca_sym, (&(_ion_Cao)) - 2, _style_Ca);
}
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt, double _v){double _current=0.;v=_v;{
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
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
double _dtsav = dt;
if (secondorder) { dt *= 0.5; }
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
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
  iCa = _ion_iCa;
  Cai = _ion_Cai;
  Cai = _ion_Cai;
  Cao = _ion_Cao;
 {  _deriv1_advance = 1;
 derivimplicit_thread(1, _slist1, _dlist1, _p, state, _ppvar, _thread, _nt);
_deriv1_advance = 0;
     if (secondorder) {
    int _i;
    for (_i = 0; _i < 1; ++_i) {
      _p[_slist1[_i]] += dt*_p[_dlist1[_i]];
    }}
 } {
   }
  _ion_Cai = Cai;
  _ion_Cao = Cao;
}}
 dt = _dtsav;
}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(Ca) - _p;  _dlist1[0] = &(DCa) - _p;
 _slist2[0] = &(Ca) - _p;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/Users/danielsprague/BME_515/ProjModel/Rod_Cad.mod";
static const char* nmodl_file_text = 
  "TITLE decay of internal calcium concentration\n"
  ":\n"
  ": Internal calcium concentration due to calcium currents and pump.\n"
  ": Differential equations.\n"
  ":\n"
  ": Simple model of ATPase pump with 3 kinetic constants (Destexhe 92)\n"
  ":     Cai + P <-> CaP -> Cao + P  (k1,k2,k3)\n"
  ": A Michaelis-Menten approximation is assumed, which reduces the complexity\n"
  ": of the system to 2 parameters: \n"
  ":       kt = <tot enzyme concentration> * k3  -> TIME CONSTANT OF THE PUMP\n"
  ":	kd = k2/k1 (dissociation constant)    -> EQUILIBRIUM CALCIUM VALUE\n"
  ": The values of these parameters are chosen assuming a high affinity of \n"
  ": the pump to calcium and a low transport capacity (cfr. Blaustein, \n"
  ": TINS, 11: 438, 1988, and references therein).  \n"
  ":\n"
  ": Units checked using \"modlunit\" -> factor 10000 needed in ca entry\n"
  ":\n"
  ": VERSION OF PUMP + DECAY (decay can be viewed as simplified buffering)\n"
  ":\n"
  ": All variables are range variables\n"
  ":\n"
  ":\n"
  ": This mechanism was published in:  Destexhe, A. Babloyantz, A. and \n"
  ": Sejnowski, TJ.  Ionic mechanisms for intrinsic slow oscillations in\n"
  ": thalamic relay neurons. Biophys. J. 65: 1538-1552, 1993)\n"
  ":\n"
  ": Written by Alain Destexhe, Salk Institute, Nov 12, 1992\n"
  ":\n"
  ": This file was modified by Yiota Poirazi (poirazi@LNC.usc.edu) on April 18, 2001 to account for the sharp\n"
  ": Ca++ spike repolarization observed in: Golding, N. Jung H-Y., Mickus T. and Spruston N\n"
  ": \"Dendritic Calcium Spike Initiation and Repolarization are controlled by distinct potassium channel\n"
  ": subtypes in CA1 pyramidal neurons\". J. of Neuroscience 19(20) 8789-8798, 1999.\n"
  ":\n"
  ":  factor 10000 is replaced by 10000/18 needed in ca entry\n"
  ":  taur --rate of calcium removal-- is replaced by taur*7 (7 times faster) \n"
  "\n"
  ": Xiaodong Liu 2003-12-08 Calcium Dynamics for Rod inner segment\n"
  "\n"
  "INDEPENDENT {t FROM 0 TO 1 WITH 1 (ms)}\n"
  "\n"
  "NEURON {\n"
  "	SUFFIX Cad\n"
  "	USEION Ca READ iCa, Cai WRITE Cai,Cao VALENCE 2	\n"
  "        RANGE Ca, depth, Cainf, taur, entryF\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "	(molar) = (1/liter)			: moles do not appear in units\n"
  "	(mM)	= (millimolar)\n"
  "	(um)	= (micron)\n"
  "	(mA)	= (milliamp)\n"
  "	(msM)	= (ms mM)\n"
  "	FARADAY = (faraday) (coulomb)\n"
  "}\n"
  "\n"
  "\n"
  "PARAMETER {\n"
  "	depth	= 10	(um)		: depth of shell\n"
  "	taur	= 20	(ms)		: rate of calcium removal\n"
  "	Cainf	= 5e-5  (mM)		: 2uM\n"
  "	Cai		(mM)\n"
  "	Cao     = 2     (mM)\n"
  "	entryF  = 1\n"
  "}\n"
  "\n"
  "STATE {\n"
  "	Ca		(mM) \n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "	Ca = Cainf\n"
  "	Cao=2\n"
  "	\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	iCa		(mA/cm2)\n"
  "	drive_channel	(mM/ms)\n"
  "}\n"
  "	\n"
  "BREAKPOINT {\n"
  "	SOLVE state METHOD derivimplicit\n"
  "}\n"
  "\n"
  "DERIVATIVE state { \n"
  "\n"
  "	drive_channel =  - (10000) * iCa / (2 * FARADAY * depth)\n"
  "	if (drive_channel <= 0.) { drive_channel = 0.  }   : cannot pump inward \n"
  "         \n"
  "	:ca' = drive_channel + (cainf-ca)/taur\n"
  "        :Ca' = drive_channel/18 + (Cainf -Ca)/taur*7\n"
  "	Ca' = entryF*drive_channel/2 + (Cainf-Ca)/taur\n"
  "	\n"
  "        Cai = Ca\n"
  "	Cao=2 :mM\n"
  "}\n"
  ;
#endif
