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
 
#define nrn_init _nrn_init__Ca
#define _nrn_initial _nrn_initial__Ca
#define nrn_cur _nrn_cur__Ca
#define _nrn_current _nrn_current__Ca
#define nrn_jacob _nrn_jacob__Ca
#define nrn_state _nrn_state__Ca
#define _net_receive _net_receive__Ca 
#define rate rate__Ca 
#define states states__Ca 
 
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
#define gCabar _p[0]
#define eCa _p[1]
#define aomCa _p[2]
#define bomCa _p[3]
#define gammaohCa _p[4]
#define deltaohCa _p[5]
#define VhalfCam _p[6]
#define VhalfCah _p[7]
#define SCam _p[8]
#define SCah _p[9]
#define mCa _p[10]
#define hCa _p[11]
#define DmCa _p[12]
#define DhCa _p[13]
#define gCa _p[14]
#define iCa _p[15]
#define infmCa _p[16]
#define taumCa _p[17]
#define infhCa _p[18]
#define tauhCa _p[19]
#define v _p[20]
#define _g _p[21]
#define _ion_iCa	*_ppvar[0]._pval
#define _ion_diCadv	*_ppvar[1]._pval
 
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
 static void _hoc_alphamCa(void);
 static void _hoc_betamCa(void);
 static void _hoc_deltahCa(void);
 static void _hoc_gammahCa(void);
 static void _hoc_rate(void);
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
 "setdata_Ca", _hoc_setdata,
 "alphamCa_Ca", _hoc_alphamCa,
 "betamCa_Ca", _hoc_betamCa,
 "deltahCa_Ca", _hoc_deltahCa,
 "gammahCa_Ca", _hoc_gammahCa,
 "rate_Ca", _hoc_rate,
 0, 0
};
#define alphamCa alphamCa_Ca
#define betamCa betamCa_Ca
#define deltahCa deltahCa_Ca
#define gammahCa gammahCa_Ca
 extern double alphamCa( _threadargsprotocomma_ double );
 extern double betamCa( _threadargsprotocomma_ double );
 extern double deltahCa( _threadargsprotocomma_ double );
 extern double gammahCa( _threadargsprotocomma_ double );
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "gCabar_Ca", 0, 1e+09,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "gCabar_Ca", "mS/cm2",
 "eCa_Ca", "mV",
 "aomCa_Ca", "/s",
 "bomCa_Ca", "/s",
 "gammaohCa_Ca", "/s",
 "deltaohCa_Ca", "/s",
 "VhalfCam_Ca", "mV",
 "VhalfCah_Ca", "mV",
 "SCam_Ca", "mV",
 "SCah_Ca", "mV",
 0,0
};
 static double delta_t = 0.01;
 static double hCa0 = 0;
 static double mCa0 = 0;
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
 
#define _cvode_ieq _ppvar[2]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"Ca",
 "gCabar_Ca",
 "eCa_Ca",
 "aomCa_Ca",
 "bomCa_Ca",
 "gammaohCa_Ca",
 "deltaohCa_Ca",
 "VhalfCam_Ca",
 "VhalfCah_Ca",
 "SCam_Ca",
 "SCah_Ca",
 0,
 0,
 "mCa_Ca",
 "hCa_Ca",
 0,
 0};
 static Symbol* _Ca_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 22, _prop);
 	/*initialize range parameters*/
 	gCabar = 4;
 	eCa = 40;
 	aomCa = 100;
 	bomCa = 100;
 	gammaohCa = 10;
 	deltaohCa = 10;
 	VhalfCam = -10;
 	VhalfCah = 11;
 	SCam = 6;
 	SCah = 9;
 	_prop->param = _p;
 	_prop->param_size = 22;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 3, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_Ca_sym);
 	_ppvar[0]._pval = &prop_ion->param[3]; /* iCa */
 	_ppvar[1]._pval = &prop_ion->param[4]; /* _ion_diCadv */
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _Rod_Ca_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("Ca", 2.0);
 	_Ca_sym = hoc_lookup("Ca_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 22, 3);
  hoc_register_dparam_semantics(_mechtype, 0, "Ca_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "Ca_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 Ca /Users/danielsprague/BME_515/ProjModel/x86_64/Rod_Ca.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int rate(_threadargsprotocomma_ double);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[2], _dlist1[2];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {int _reset = 0; {
   rate ( _threadargscomma_ v ) ;
   DmCa = ( infmCa - mCa ) / taumCa ;
   DhCa = ( infhCa - hCa ) / tauhCa ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
 rate ( _threadargscomma_ v ) ;
 DmCa = DmCa  / (1. - dt*( ( ( ( - 1.0 ) ) ) / taumCa )) ;
 DhCa = DhCa  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tauhCa )) ;
  return 0;
}
 /*END CVODE*/
 static int states (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) { {
   rate ( _threadargscomma_ v ) ;
    mCa = mCa + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / taumCa)))*(- ( ( ( infmCa ) ) / taumCa ) / ( ( ( ( - 1.0 ) ) ) / taumCa ) - mCa) ;
    hCa = hCa + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tauhCa)))*(- ( ( ( infhCa ) ) / tauhCa ) / ( ( ( ( - 1.0 ) ) ) / tauhCa ) - hCa) ;
   }
  return 0;
}
 
double alphamCa ( _threadargsprotocomma_ double _lv ) {
   double _lalphamCa;
 _lalphamCa = 0.001 * aomCa * exp ( ( _lv - VhalfCam ) / ( 2.0 * SCam ) ) ;
   
return _lalphamCa;
 }
 
static void _hoc_alphamCa(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  alphamCa ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
double betamCa ( _threadargsprotocomma_ double _lv ) {
   double _lbetamCa;
 _lbetamCa = 0.001 * bomCa * exp ( - ( _lv - VhalfCam ) / ( 2.0 * SCam ) ) ;
   
return _lbetamCa;
 }
 
static void _hoc_betamCa(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  betamCa ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
double gammahCa ( _threadargsprotocomma_ double _lv ) {
   double _lgammahCa;
 _lgammahCa = 0.001 * gammaohCa * exp ( ( _lv - VhalfCah ) / ( 2.0 * SCah ) ) ;
   
return _lgammahCa;
 }
 
static void _hoc_gammahCa(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  gammahCa ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
double deltahCa ( _threadargsprotocomma_ double _lv ) {
   double _ldeltahCa;
 _ldeltahCa = 0.001 * deltaohCa * exp ( - ( _lv - VhalfCah ) / ( 2.0 * SCah ) ) ;
   
return _ldeltahCa;
 }
 
static void _hoc_deltahCa(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  deltahCa ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
static int  rate ( _threadargsprotocomma_ double _lv ) {
   double _la , _lb , _lc , _ld ;
 _la = alphamCa ( _threadargscomma_ _lv ) ;
   _lb = betamCa ( _threadargscomma_ _lv ) ;
   taumCa = 1.0 / ( _la + _lb ) ;
   infmCa = _la / ( _la + _lb ) ;
   _lc = gammahCa ( _threadargscomma_ _lv ) ;
   _ld = deltahCa ( _threadargscomma_ _lv ) ;
   tauhCa = 1.0 / ( _lc + _ld ) ;
   infhCa = _ld / ( _lc + _ld ) ;
    return 0; }
 
static void _hoc_rate(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r = 1.;
 rate ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ return 2;}
 
static void _ode_spec(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
     _ode_spec1 (_p, _ppvar, _thread, _nt);
  }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 2; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
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
 _ode_matsol_instance1(_threadargs_);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_Ca_sym, _ppvar, 0, 3);
   nrn_update_ion_pointer(_Ca_sym, _ppvar, 1, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  int _i; double _save;{
  hCa = hCa0;
  mCa = mCa0;
 {
   rate ( _threadargscomma_ v ) ;
   mCa = infmCa ;
   hCa = infhCa ;
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
 initmodel(_p, _ppvar, _thread, _nt);
 }
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   gCa = ( 0.001 ) * gCabar * mCa * hCa ;
   iCa = gCa * ( v - eCa ) ;
   }
 _current += iCa;

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
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ double _diCa;
  _diCa = iCa;
 _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
  _ion_diCadv += (_diCa - iCa)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_iCa += iCa ;
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
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
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
 {   states(_p, _ppvar, _thread, _nt);
  } }}

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(mCa) - _p;  _dlist1[0] = &(DmCa) - _p;
 _slist1[1] = &(hCa) - _p;  _dlist1[1] = &(DhCa) - _p;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/Users/danielsprague/BME_515/ProjModel/Rod_Ca.mod";
static const char* nmodl_file_text = 
  ": Rod  Photoreceptor Ca and Calcium  channel\n"
  ": Ref. Kourenny and  Liu 2002   ABME 30 : 1196-1203\n"
  ": Modification 2004-02-07\n"
  "NEURON \n"
  "{\n"
  "	SUFFIX Ca\n"
  "	\n"
  "	USEION Ca WRITE iCa VALENCE 2\n"
  "        RANGE gCabar,VhalfCam,SCam\n"
  "        RANGE VhalfCah,SCah\n"
  "        RANGE eCa,aomCa,bomCa\n"
  "        RANGE gammaohCa,deltaohCa\n"
  "\n"
  "\n"
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
  "       : Calcium channel \n"
  "       gCabar = 4 (mS/cm2) <0,1e9> :different from ABME paper\n"
  "       eCa =  40 (mV)\n"
  "       aomCa = 100  (/s)  : changed from 3.10/s, 20/s\n"
  "       bomCa = 100  (/s)\n"
  "       gammaohCa = 10 (/s)\n"
  "       deltaohCa =10 (/s)  \n"
  " \n"
  "       VhalfCam=-10.0 (mV)\n"
  "       VhalfCah=11 (mV)\n"
  "       SCam =6.0      (mV) \n"
  "       \n"
  "       SCah =9        (mV)   \n"
  "     \n"
  "}\n"
  "\n"
  "\n"
  "STATE\n"
  "{\n"
  "\n"
  "	mCa\n"
  "	hCa\n"
  "	\n"
  "}\n"
  "\n"
  "ASSIGNED\n"
  "{\n"
  "	gCa (mho/cm2)\n"
  "    \n"
  "	v (mV)\n"
  "	\n"
  "	iCa (mA/cm2)\n"
  "\n"
  "	infmCa\n"
  "	taumCa  (ms) \n"
  "	\n"
  "\n"
  "\n"
  "	infhCa\n"
  "	tauhCa (ms)\n"
  "\n"
  "\n"
  "\n"
  "}\n"
  "\n"
  "INITIAL\n"
  "{\n"
  "	rate(v)\n"
  "	mCa = infmCa\n"
  "	hCa = infhCa\n"
  "\n"
  "}\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "BREAKPOINT\n"
  "{\n"
  "	SOLVE states METHOD cnexp\n"
  "	gCa = (0.001)*gCabar*mCa*hCa\n"
  "	: g is in unit of S/cm2 ,i is in unit of mA/cm2 and v is in mV\n"
  "	\n"
  "	iCa = gCa*(v - eCa)\n"
  "	: the current is in the unit of mA/cm2\n"
  "	\n"
  "	\n"
  "}\n"
  "\n"
  "DERIVATIVE states\n"
  "{\n"
  "	rate(v)\n"
  "	mCa' = (infmCa - mCa)/taumCa\n"
  "	hCa'= (infhCa-hCa)/tauhCa\n"
  "\n"
  "\n"
  "}\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "FUNCTION alphamCa(v(mV))(/ms)\n"
  "{ \n"
  "	alphamCa = 0.001*aomCa*exp( (v - VhalfCam)/(2*SCam)   )\n"
  "}\n"
  "\n"
  "FUNCTION betamCa(v(mV))(/ms)\n"
  "{ \n"
  "	betamCa = 0.001*bomCa*exp( - ( v-VhalfCam)/(2*SCam) )\n"
  "}\n"
  "FUNCTION gammahCa(v(mV))(/ms)\n"
  "{ \n"
  "	gammahCa = 0.001*gammaohCa*exp( (v - VhalfCah)/(2*SCah))\n"
  "}\n"
  "\n"
  "FUNCTION deltahCa(v(mV))(/ms)\n"
  "{ \n"
  "	deltahCa = 0.001*deltaohCa*exp( - ( v-VhalfCah)/(2*SCah) )\n"
  "}\n"
  "\n"
  "\n"
  "PROCEDURE rate(v (mV))\n"
  "{\n"
  "        LOCAL a, b,c, d\n"
  "\n"
  "\n"
  "	a = alphamCa(v)\n"
  "	b = betamCa(v)\n"
  "	taumCa = 1/(a + b)\n"
  "	infmCa = a/(a + b)\n"
  "	\n"
  "	c = gammahCa(v)\n"
  "	d = deltahCa(v)\n"
  "	tauhCa = 1/(c + d)\n"
  "	infhCa = d/(c + d)\n"
  "\n"
  "}\n"
  "\n"
  ;
#endif
