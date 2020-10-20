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
 
#define nrn_init _nrn_init__IinjLTDim
#define _nrn_initial _nrn_initial__IinjLTDim
#define nrn_cur _nrn_cur__IinjLTDim
#define _nrn_current _nrn_current__IinjLTDim
#define nrn_jacob _nrn_jacob__IinjLTDim
#define nrn_state _nrn_state__IinjLTDim
#define _net_receive _net_receive__IinjLTDim 
 
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
#define del _p[0]
#define ton _p[1]
#define toff _p[2]
#define num _p[3]
#define amp _p[4]
#define ssI _p[5]
#define i _p[6]
#define Ncount _p[7]
#define ival _p[8]
#define on _p[9]
#define tally _p[10]
#define tr _p[11]
#define Part1 _p[12]
#define Part2 _p[13]
#define Part3 _p[14]
#define ssInA _p[15]
#define ampnA _p[16]
#define v _p[17]
#define _g _p[18]
#define _tsav _p[19]
#define _nd_area  *_ppvar[0]._pval
 
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

 extern Prop* nrn_point_prop_;
 static int _pointtype;
 static void* _hoc_create_pnt(_ho) Object* _ho; { void* create_point_process();
 return create_point_process(_pointtype, _ho);
}
 static void _hoc_destroy_pnt();
 static double _hoc_loc_pnt(_vptr) void* _vptr; {double loc_point_process();
 return loc_point_process(_pointtype, _vptr);
}
 static double _hoc_has_loc(_vptr) void* _vptr; {double has_loc_point();
 return has_loc_point(_vptr);
}
 static double _hoc_get_loc_pnt(_vptr)void* _vptr; {
 double get_loc_point_process(); return (get_loc_point_process(_vptr));
}
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _extcall_prop = _prop;
 }
 static void _hoc_setdata(void* _vptr) { Prop* _prop;
 _prop = ((Point_process*)_vptr)->_prop;
   _setdata(_prop);
 }
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 0,0
};
 static Member_func _member_func[] = {
 "loc", _hoc_loc_pnt,
 "has_loc", _hoc_has_loc,
 "get_loc", _hoc_get_loc_pnt,
 0, 0
};
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "toff", 0, 1e+09,
 "ton", 0, 1e+09,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "del", "ms",
 "ton", "ms",
 "toff", "ms",
 "amp", "pA",
 "ssI", "pA",
 "i", "nA",
 0,0
};
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
 static void _hoc_destroy_pnt(_vptr) void* _vptr; {
   destroy_point_process(_vptr);
}
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"IinjLTDim",
 "del",
 "ton",
 "toff",
 "num",
 "amp",
 "ssI",
 0,
 "i",
 0,
 0,
 0};
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
  if (nrn_point_prop_) {
	_prop->_alloc_seq = nrn_point_prop_->_alloc_seq;
	_p = nrn_point_prop_->param;
	_ppvar = nrn_point_prop_->dparam;
 }else{
 	_p = nrn_prop_data_alloc(_mechtype, 20, _prop);
 	/*initialize range parameters*/
 	del = 1000;
 	ton = 8000;
 	toff = 1000;
 	num = 2;
 	amp = 18.8704;
 	ssI = 40;
  }
 	_prop->param = _p;
 	_prop->param_size = 20;
  if (!nrn_point_prop_) {
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 3, _prop);
  }
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
 
#define _tqitem &(_ppvar[2]._pvoid)
 static void _net_receive(Point_process*, double*, double);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _IinjLTDim_reg() {
	int _vectorized = 1;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init,
	 hoc_nrnpointerindex, 1,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 20, 3);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
  hoc_register_dparam_semantics(_mechtype, 2, "netsend");
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_size[_mechtype] = 1;
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 IinjLTDim /Users/danielsprague/BME_515/ProjModel/x86_64/IinjLTDim.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
 
static void _net_receive (_pnt, _args, _lflag) Point_process* _pnt; double* _args; double _lflag; 
{  double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   _thread = (Datum*)0; _nt = (_NrnThread*)_pnt->_vnt;   _p = _pnt->_prop->param; _ppvar = _pnt->_prop->dparam;
  if (_tsav > t){ extern char* hoc_object_name(); hoc_execerror(hoc_object_name(_pnt->ob), ":Event arrived out of order. Must call ParallelContext.set_maxstep AFTER assigning minimum NetCon.delay");}
 _tsav = t;   if (_lflag == 1. ) {*(_tqitem) = 0;}
 {
   if ( _lflag  == 1.0 ) {
     if ( on  == 0.0 ) {
       Ncount = Ncount + 1.0 ;
       ival = ampnA ;
       on = 1.0 ;
       net_send ( _tqitem, _args, _pnt, t +  ton , 1.0 ) ;
       }
     else {
       ival = 0.0 ;
       on = 0.0 ;
       if ( tally > 0.0 ) {
         net_send ( _tqitem, _args, _pnt, t +  toff , 1.0 ) ;
         tally = tally - 1.0 ;
         }
       }
     }
   } }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  int _i; double _save;{
 {
   i = 0.0 ;
   ssInA = 0.001 * ssI ;
   ampnA = amp * 0.001 ;
   ival = 0.0 ;
   tally = num ;
   Ncount = 0.0 ;
   if ( tally > 0.0 ) {
     net_send ( _tqitem, (double*)0, _ppvar[1]._pvoid, t +  del , 1.0 ) ;
     on = 0.0 ;
     tally = tally - 1.0 ;
     }
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
 _tsav = -1e20;
#if EXTRACELLULAR
 _nd = _ml->_nodelist[_iml];
 if (_nd->_extnode) {
    _v = NODEV(_nd) +_nd->_extnode->_v[0];
 }else
#endif
 {
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
 v = _v;
 initmodel(_p, _ppvar, _thread, _nt);
}
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   double _ltau1 , _ltau2 , _ltau3 , _lt1 , _lt2 , _lt3 , _ltt , _lPhotoI ;
 tr = t - del - ( ton + toff ) * ( Ncount - 1.0 ) + dt ;
   if ( on  == 1.0 ) {
     _ltau1 = 0.140104647 ;
     _ltau2 = 0.596464897 ;
     _ltau3 = 0.590572966 ;
     _lt1 = 0.230595125 ;
     _lt2 = 0.691774291 ;
     _lt3 = 0.035251144 ;
     _ltt = tr / 1000.0 ;
     Part1 = - exp ( - ( _ltt - _lt1 ) / _ltau1 ) ;
     Part2 = exp ( - ( _ltt - _lt2 ) / _ltau2 ) ;
     Part3 = - exp ( - ( _ltt - _lt3 ) / _ltau3 ) ;
     _lPhotoI = ( Part1 + Part2 + Part3 ) ;
     if ( _lPhotoI >= 0.0 ) {
       i = ssInA - ival * ( Part1 + Part2 + Part3 ) ;
       }
     else {
       i = ssInA ;
       }
     }
   else {
     i = ssInA + ival ;
     }
   }
 _current += i;

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
#if EXTRACELLULAR
 _nd = _ml->_nodelist[_iml];
 if (_nd->_extnode) {
    _v = NODEV(_nd) +_nd->_extnode->_v[0];
 }else
#endif
 {
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
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
 	}
 _g = (_g - _rhs)/.001;
 _g *=  1.e2/(_nd_area);
 _rhs *= 1.e2/(_nd_area);
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) += _rhs;
  }else
#endif
  {
	NODERHS(_nd) += _rhs;
  }
  if (_nt->_nrn_fast_imem) { _nt->_nrn_fast_imem->_nrn_sav_rhs[_ni[_iml]] += _rhs; }
#if EXTRACELLULAR
 if (_nd->_extnode) {
   *_nd->_extnode->_rhs[0] += _rhs;
 }
#endif
 
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
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) -= _g;
  }else
#endif
  {
	NODED(_nd) -= _g;
  }
  if (_nt->_nrn_fast_imem) { _nt->_nrn_fast_imem->_nrn_sav_d[_ni[_iml]] -= _g; }
#if EXTRACELLULAR
 if (_nd->_extnode) {
   *_nd->_extnode->_d[0] += _g;
 }
#endif
 
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
static const char* nmodl_filename = "/Users/danielsprague/BME_515/ProjModel/IinjLTDim.mod";
static const char* nmodl_file_text = 
  "COMMENT\n"
  "  IinjLT.mod\n"
  "  Generates a train of photocurrent injections\n"
  "  User specifies duration of each Iinj, interpulse interval (ton and toff),\n"
  "  and number of pulses.\n"
  "  6/30/2003 RARE LAB\n"
  "           ___            ___            _ _\n"
  "          /   \\          /   \\            |\n"
  " delay    |    \\   toff  |    \\           | amp\n"
  "__________|     \\________|     \\_______  _|_\n"
  "            ton\n"
  "            \n"
  "   num:      1              2          ...\n"
  "ENDCOMMENT\n"
  "\n"
  "\n"
  "NEURON {\n"
  "	POINT_PROCESS IinjLTDim\n"
  "	RANGE del, ton, toff, num, amp,ssI,i\n"
  "	ELECTRODE_CURRENT i\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "	(pA) = (picoamp)\n"
  "        (nA) = (nanoamp)\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "	del  = 1000 (ms)\n"
  "	ton  = 8000 (ms) <0, 1e9>	: duration of ON phase\n"
  "	toff = 1000 (ms) <0, 1e9>	: duration of OFF phase\n"
  "	num  = 2			: how many to deliver\n"
  "	amp  = 18.87043569 (pA) : absolute amplitude of the light induced current\n"
  "        ssI  = 40 (pA)     : steady-state current (dark current)\n"
  "        \n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "        Ncount     : counter of the number of the flashes/injections\n"
  "	ival (nA)\n"
  "	i (nA)\n"
  "	on\n"
  "	tally			: how many more to deliver\n"
  "	tr (ms)   : the relative time in each flash \n"
  "        Part1\n"
  "        Part2\n"
  "        Part3\n"
  "        ssInA (nA)\n"
  "        ampnA (nA)\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "	i = 0\n"
  "        ssInA=0.001*ssI\n"
  "        ampnA=amp*0.001\n"
  "	ival = 0\n"
  "	tally = num\n"
  "        Ncount=0\n"
  "	if (tally > 0) {\n"
  "		net_send(del, 1)\n"
  "		on = 0\n"
  "		tally = tally - 1\n"
  "	}\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "	LOCAL tau1,tau2,tau3,t1,t2,t3,tt,PhotoI\n"
  ": printf(\"%g\\n\", t)\n"
  "        tr=t-del-(ton+toff)*(Ncount-1)+dt\n"
  "        if (on ==1) { \n"
  "tau1=0.140104647\n"
  "tau2=0.596464897\n"
  "tau3=0.590572966\n"
  "t1=0.230595125\n"
  "t2=0.691774291\n"
  "t3=0.035251144\n"
  "\n"
  "  \n"
  "        tt=tr/1000\n"
  "       	Part1=-exp(- (tt-t1 )/tau1 ) \n"
  "   	Part2= exp(- (tt-t2 )/tau2 )\n"
  "   	Part3=-exp(- (tt-t3 )/tau3 )\n"
  "   	PhotoI=( Part1+Part2+Part3)\n"
  "       if (PhotoI>=0) {\n"
  "       i=ssInA-ival*( Part1+Part2+Part3)\n"
  "        } else {\n"
  "       i=ssInA\n"
  "	}\n"
  "        \n"
  "        } else {\n"
  "        i = ssInA+ival\n"
  "        }\n"
  "         \n"
  "}\n"
  "\n"
  "NET_RECEIVE (w) {\n"
  "	: ignore any but self-events with flag == 1\n"
  "	if (flag == 1) {\n"
  "		if (on == 0) {\n"
  "			: turn it on\n"
  "                        Ncount=Ncount+1\n"
  "			ival = ampnA\n"
  "			on = 1\n"
  "			: prepare to turn it off\n"
  "			net_send(ton, 1)\n"
  "		} else {\n"
  "			: turn it off\n"
  "			ival = 0\n"
  "			on = 0\n"
  "			if (tally > 0) {\n"
  "				: prepare to turn it on again\n"
  "				net_send(toff, 1)\n"
  "				tally = tally - 1\n"
  "			}\n"
  "		}\n"
  "	}\n"
  "}\n"
  ;
#endif
