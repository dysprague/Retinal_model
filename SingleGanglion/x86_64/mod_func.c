#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;

extern void _A2hh_k_reg(void);
extern void _A2hh_na_reg(void);
extern void _Bip_Ca_reg(void);
extern void _Bip_Cad_reg(void);
extern void _Bip_Ka_reg(void);
extern void _Bip_Kv_reg(void);
extern void _Bip_ih_reg(void);
extern void _Cone_CPR_reg(void);
extern void _Cone_Kv_reg(void);
extern void _Cone_ih_reg(void);
extern void _Ganglion_hh_reg(void);
extern void _IinjLT_reg(void);
extern void _IinjLTDim_reg(void);
extern void _IinjLT_cone_reg(void);
extern void _Rod_Ca_reg(void);
extern void _Rod_Cad_reg(void);
extern void _Rod_Clca_reg(void);
extern void _Rod_Kca_reg(void);
extern void _Rod_Kv_reg(void);
extern void _Rod_Kx_reg(void);
extern void _Rod_ih_reg(void);
extern void _Rod_leak_reg(void);
extern void _gap_reg(void);
extern void _syn_bip_gan_reg(void);
extern void _syn_rod_bip_reg(void);

void modl_reg(){
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");

    fprintf(stderr," A2hh_k.mod");
    fprintf(stderr," A2hh_na.mod");
    fprintf(stderr," Bip_Ca.mod");
    fprintf(stderr," Bip_Cad.mod");
    fprintf(stderr," Bip_Ka.mod");
    fprintf(stderr," Bip_Kv.mod");
    fprintf(stderr," Bip_ih.mod");
    fprintf(stderr," Cone_CPR.mod");
    fprintf(stderr," Cone_Kv.mod");
    fprintf(stderr," Cone_ih.mod");
    fprintf(stderr," Ganglion_hh.mod");
    fprintf(stderr," IinjLT.mod");
    fprintf(stderr," IinjLTDim.mod");
    fprintf(stderr," IinjLT_cone.mod");
    fprintf(stderr," Rod_Ca.mod");
    fprintf(stderr," Rod_Cad.mod");
    fprintf(stderr," Rod_Clca.mod");
    fprintf(stderr," Rod_Kca.mod");
    fprintf(stderr," Rod_Kv.mod");
    fprintf(stderr," Rod_Kx.mod");
    fprintf(stderr," Rod_ih.mod");
    fprintf(stderr," Rod_leak.mod");
    fprintf(stderr," gap.mod");
    fprintf(stderr," syn_bip_gan.mod");
    fprintf(stderr," syn_rod_bip.mod");
    fprintf(stderr, "\n");
  }
  _A2hh_k_reg();
  _A2hh_na_reg();
  _Bip_Ca_reg();
  _Bip_Cad_reg();
  _Bip_Ka_reg();
  _Bip_Kv_reg();
  _Bip_ih_reg();
  _Cone_CPR_reg();
  _Cone_Kv_reg();
  _Cone_ih_reg();
  _Ganglion_hh_reg();
  _IinjLT_reg();
  _IinjLTDim_reg();
  _IinjLT_cone_reg();
  _Rod_Ca_reg();
  _Rod_Cad_reg();
  _Rod_Clca_reg();
  _Rod_Kca_reg();
  _Rod_Kv_reg();
  _Rod_Kx_reg();
  _Rod_ih_reg();
  _Rod_leak_reg();
  _gap_reg();
  _syn_bip_gan_reg();
  _syn_rod_bip_reg();
}
