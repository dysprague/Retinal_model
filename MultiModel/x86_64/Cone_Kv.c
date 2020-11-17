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
 
#define nrn_init _nrn_init__Kv_cone
#define _nrn_initial _nrn_initial__Kv_cone
#define nrn_cur _nrn_cur__Kv_cone
#define _nrn_current _nrn_current__Kv_cone
#define nrn_jacob _nrn_jacob__Kv_cone
#define nrn_state _nrn_state__Kv_cone
#define _net_receive _net_receive__Kv_cone 
#define rate rate__Kv_cone 
#define states states__Kv_cone 
 
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
#define gKvbar _p[0]
#define eKv _p[1]
#define gKv _p[2]
#define mKv _p[3]
#define hKv _p[4]
#define DmKv _p[5]
#define DhKv _p[6]
#define iKv _p[7]
#define infmKv _p[8]
#define taumKv _p[9]
#define infhKv _p[10]
#define tauhKv _p[11]
#define v _p[12]
#define _g _p[13]
#define _ion_iKv	*_ppvar[0]._pval
#define _ion_diKvdv	*_ppvar[1]._pval
 
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
 static void _hoc_alphahKv(void);
 static void _hoc_alphamKv(void);
 static void _hoc_betahKv(void);
 static void _hoc_betamKv(void);
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
 "setdata_Kv_cone", _hoc_setdata,
 "alphahKv_Kv_cone", _hoc_alphahKv,
 "alphamKv_Kv_cone", _hoc_alphamKv,
 "betahKv_Kv_cone", _hoc_betahKv,
 "betamKv_Kv_cone", _hoc_betamKv,
 "rate_Kv_cone", _hoc_rate,
 0, 0
};
#define alphahKv alphahKv_Kv_cone
#define alphamKv alphamKv_Kv_cone
#define betahKv betahKv_Kv_cone
#define betamKv betamKv_Kv_cone
 extern double alphahKv( _threadargsprotocomma_ double );
 extern double alphamKv( _threadargsprotocomma_ double );
 extern double betahKv( _threadargsprotocomma_ double );
 extern double betamKv( _threadargsprotocomma_ double );
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "gKvbar_Kv_cone", 0, 1e+09,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "gKvbar_Kv_cone", "mS/cm2",
 "eKv_Kv_cone", "mV",
 "gKv_Kv_cone", "mho/cm2",
 0,0
};
 static double delta_t = 0.01;
 static double hKv0 = 0;
 static double mKv0 = 0;
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
"Kv_cone",
 "gKvbar_Kv_cone",
 "eKv_Kv_cone",
 0,
 "gKv_Kv_cone",
 0,
 "mKv_Kv_cone",
 "hKv_Kv_cone",
 0,
 0};
 static Symbol* _Kv_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 14, _prop);
 	/*initialize range parameters*/
 	gKvbar = 2;
 	eKv = -80;
 	_prop->param = _p;
 	_prop->param_size = 14;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 3, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_Kv_sym);
 	_ppvar[0]._pval = &prop_ion->param[3]; /* iKv */
 	_ppvar[1]._pval = &prop_ion->param[4]; /* _ion_diKvdv */
 
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

 void _Cone_Kv_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("Kv", 1.0);
 	_Kv_sym = hoc_lookup("Kv_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 14, 3);
  hoc_register_dparam_semantics(_mechtype, 0, "Kv_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "Kv_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 Kv_cone /Users/danielsprague/BME_515/ProjModel/x86_64/Cone_Kv.mod\n");
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
   DmKv = ( infmKv - mKv ) / taumKv ;
   DhKv = ( infhKv - hKv ) / tauhKv ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
 rate ( _threadargscomma_ v ) ;
 DmKv = DmKv  / (1. - dt*( ( ( ( - 1.0 ) ) ) / taumKv )) ;
 DhKv = DhKv  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tauhKv )) ;
  return 0;
}
 /*END CVODE*/
 static int states (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) { {
   rate ( _threadargscomma_ v ) ;
    mKv = mKv + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / taumKv)))*(- ( ( ( infmKv ) ) / taumKv ) / ( ( ( ( - 1.0 ) ) ) / taumKv ) - mKv) ;
    hKv = hKv + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tauhKv)))*(- ( ( ( infhKv ) ) / tauhKv ) / ( ( ( ( - 1.0 ) ) ) / tauhKv ) - hKv) ;
   }
  return 0;
}
 
double alphamKv ( _threadargsprotocomma_ double _lv ) {
   double _lalphamKv;
 _lalphamKv = ( 0.001 ) * 5.0 * ( 100.0 - _lv ) / ( exp ( ( 100.0 - _lv ) / 42.0 ) - 1.0 ) ;
   
return _lalphamKv;
 }
 
static void _hoc_alphamKv(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  alphamKv ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
double betamKv ( _threadargsprotocomma_ double _lv ) {
   double _lbetamKv;
 _lbetamKv = ( 0.001 ) * 9.0 * exp ( - ( _lv - 20.0 ) / 40.0 ) ;
   
return _lbetamKv;
 }
 
static void _hoc_betamKv(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  betamKv ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
double alphahKv ( _threadargsprotocomma_ double _lv ) {
   double _lalphahKv;
 _lalphahKv = ( 0.001 ) * 0.15 * exp ( - _lv / 22.0 ) ;
   
return _lalphahKv;
 }
 
static void _hoc_alphahKv(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  alphahKv ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
double betahKv ( _threadargsprotocomma_ double _lv ) {
   double _lbetahKv;
 _lbetahKv = ( 0.001 ) * 0.4125 / ( exp ( ( 10.0 - _lv ) / 7.0 ) + 1.0 ) ;
   
return _lbetahKv;
 }
 
static void _hoc_betahKv(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  betahKv ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
static int  rate ( _threadargsprotocomma_ double _lv ) {
   double _la , _lb ;
 _la = alphamKv ( _threadargscomma_ _lv ) ;
   _lb = betamKv ( _threadargscomma_ _lv ) ;
   taumKv = 1.0 / ( _la + _lb ) ;
   infmKv = _la / ( _la + _lb ) ;
   _la = alphahKv ( _threadargscomma_ _lv ) ;
   _lb = betahKv ( _threadargscomma_ _lv ) ;
   tauhKv = 1.0 / ( _la + _lb ) ;
   infhKv = _la / ( _la + _lb ) ;
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
   nrn_update_ion_pointer(_Kv_sym, _ppvar, 0, 3);
   nrn_update_ion_pointer(_Kv_sym, _ppvar, 1, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  int _i; double _save;{
  hKv = hKv0;
  mKv = mKv0;
 {
   rate ( _threadargscomma_ v ) ;
   mKv = infmKv ;
   hKv = infhKv ;
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
   gKv = ( 0.001 ) * gKvbar * mKv * mKv * mKv * hKv ;
   iKv = gKv * ( v - eKv ) ;
   }
 _current += iKv;

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
 	{ double _diKv;
  _diKv = iKv;
 _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
  _ion_diKvdv += (_diKv - iKv)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_iKv += iKv ;
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
 _slist1[0] = &(mKv) - _p;  _dlist1[0] = &(DmKv) - _p;
 _slist1[1] = &(hKv) - _p;  _dlist1[1] = &(DhKv) - _p;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/Users/danielsprague/BME_515/ProjModel/Cone_Kv.mod";
static const char* nmodl_file_text = 
  ": Rod Photoreceptor Kv channel\n"
  "\n"
  "NEURON \n"
  "{\n"
  "	SUFFIX Kv_cone\n"
  "	\n"
  "	USEION Kv WRITE iKv VALENCE 1\n"
  "	\n"
  "        RANGE gKv,gKvbar, eKv\n"
  "\n"
  "}\n"
  "\n"
  "UNITS\n"
  "{\n"
  "	(mA) = (milliamp)\n"
  "	(mV) = (millivolt)\n"
  "	(mS) = (millimho)\n"
  "	\n"
  "}\n"
  "\n"
  "PARAMETER\n"
  "{\n"
  "        : potassium rectifier\n"
  "        gKvbar = 2.0 (mS/cm2) <0,1e9>\n"
  "        eKv = -80 (mV)\n"
  "       \n"
  "        \n"
  "\n"
  "}\n"
  "\n"
  "STATE\n"
  "{\n"
  "	mKv\n"
  "	hKv\n"
  "	\n"
  "}\n"
  "\n"
  "ASSIGNED\n"
  "{\n"
  "	v (mV)\n"
  "	\n"
  "	iKv (mA/cm2)\n"
  "              \n"
  "          : potussium rectifier, K\n"
  "	infmKv\n"
  "	taumKv  (ms)\n"
  "	infhKv\n"
  "	tauhKv  (ms)\n"
  "           \n"
  "     \n"
  "	gKv (mho/cm2)\n"
  "	\n"
  "}\n"
  "\n"
  "INITIAL\n"
  "{\n"
  "	rate(v)\n"
  "	mKv = infmKv\n"
  "	hKv  = infhKv\n"
  "}\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "BREAKPOINT\n"
  "{\n"
  "	SOLVE states METHOD cnexp\n"
  "	gKv = (0.001)*gKvbar*mKv*mKv*mKv *hKv\n"
  "	iKv = gKv*(v - eKv)\n"
  "}\n"
  "\n"
  "DERIVATIVE states\n"
  "{\n"
  "	rate(v)\n"
  "	mKv' = (infmKv - mKv)/taumKv\n"
  "	hKv' =  (infhKv - hKv )/tauhKv\n"
  "\n"
  "}\n"
  "\n"
  "\n"
  "UNITSOFF\n"
  "\n"
  "FUNCTION alphamKv(v(mV)) (/ms)\n"
  "{ \n"
  "	alphamKv = (0.001)*5*(100-v)/( exp( (100-v)/42) -1 )\n"
  "	:alter from orginal settings where it is in the unit of 1/s\n"
  "}\n"
  "\n"
  "FUNCTION  betamKv (v(mV)) (/ms)\n"
  "{\n"
  "	\n"
  "	betamKv = (0.001)*9*exp (- (v-20) /40 )\n"
  "}\n"
  "\n"
  "\n"
  "FUNCTION alphahKv (v(mV)) (/ms)\n"
  "{\n"
  "	alphahKv = (0.001)*0.15 *exp (-v/22)\n"
  "}\n"
  "\n"
  "FUNCTION betahKv (v(mV)) (/ms)\n"
  "{ \n"
  "	betahKv = (0.001)*0.4125/( exp ( ( 10-v)/7 ) +1 )\n"
  "\n"
  "}\n"
  "\n"
  "UNITSON\n"
  "\n"
  "PROCEDURE rate(v (mV))\n"
  "{\n"
  "        LOCAL a, b\n"
  "\n"
  "	\n"
  "	a = alphamKv(v)\n"
  "	b = betamKv(v)\n"
  "	taumKv = 1/(a + b)\n"
  "	infmKv = a/(a + b)\n"
  "	\n"
  "	a = alphahKv(v)\n"
  "	b = betahKv(v)\n"
  "	tauhKv = 1/(a + b)\n"
  "	infhKv = a/(a + b)\n"
  "	\n"
  "\n"
  "}\n"
  "\n"
  ;
#endif
