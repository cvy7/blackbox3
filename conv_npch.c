/****************************************************************************
 *   Copyright (C) 2010-2024 by cvy7                                        *
 *                                                                          *
 *   This program is free software; you can redistribute it and/or modify   *
 *   it under the terms of the GNU General Public License as published by   *
 *   the Free Software Foundation; either version 2 of the License.         *
 *                                                                          *
 *   This program is distributed in the hope that it will be useful,        *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU General Public License for more details.                           *
 *                                                                          *
 *   You should have received a copy of the GNU General Public License      *
 *   along with this program; if not, write to the                          *
 *   Free Software Foundation, Inc.,                                        *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.              *
 ****************************************************************************/
//****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
//#include <sys/times.h>
//#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "conv_npch.h"
#include "osc.h"
#define MAX_RECS 32


//Исключает 0-ые данные из текстового лога
#define FORCY for(i=0;i<MAX_RECS;i++)
#define IFED(var) bacc=0;FORCY bacc|=var;if(bacc){

p5dot0(int data,FILE *textfile){
    float fdata=data/1.0;
    fprintf(textfile,"\t%5.0f;",fdata);
}

p4dot1(int data,FILE *textfile){
    float fdata=data/10.0;
    fprintf(textfile,"\t%4.1f;",fdata);
}

p3dot2(int data,FILE *textfile){
    float fdata=data/100.0;
    fprintf(textfile,"\t%3.2f;",fdata);
}

p2dot3(int data,FILE *textfile){
    float fdata=data/1000.0;
    fprintf(textfile,"\t%2.3f;",fdata);
}

int conv_print(tconv *conv, FILE *textfile, time_t time){
    int i,j,k,bacc;
    fprintf(textfile,"UTC %s", asctime(gmtime(&time)));
    fprintf(textfile,"var_name\\time***s=;\t");FORCY p5dot0(-i,textfile);
    //TCONV
    IFED(conv[i].freq       )fprintf(textfile,"\n(256)freq*********;\t");FORCY p3dot2(conv[i].freq,                    textfile);}
    IFED(conv[i].freqi      )fprintf(textfile,"\n(257)freqi********;\t");FORCY p3dot2(conv[i].freqi,                   textfile);}
    IFED(conv[i].set_u      )fprintf(textfile,"\n(258)set_u********;\t");FORCY p4dot1(conv[i].set_u,                   textfile);}
    IFED(conv[i].set_ui     )fprintf(textfile,"\n(259)set_ui*******;\t");FORCY p4dot1(conv[i].set_ui,                  textfile);}
    for(j=0;j<3;j++){
    IFED(conv[i].err_code[j])fprintf(textfile,"\n(26%d)err_code[%d]**;\t",j,j);FORCY p5dot0(conv[i].err_code[j],       textfile);}
    }
    //*********************************************************************************************************************
    IFED(conv[i].statusbits.ready       )fprintf(textfile,"\n(264.0)ready******;\t");FORCY p5dot0(conv[i].statusbits.ready,        textfile);}
    IFED(conv[i].statusbits.remote      )fprintf(textfile,"\n(264.1)remote*****;\t");FORCY p5dot0(conv[i].statusbits.remote,       textfile);}
    IFED(conv[i].statusbits.pot         )fprintf(textfile,"\n(264.3)pot********;\t");FORCY p5dot0(conv[i].statusbits.pot,          textfile);}
    IFED(conv[i].statusbits.pan         )fprintf(textfile,"\n(264.4)pan********;\t");FORCY p5dot0(conv[i].statusbits.pan,          textfile);}
    IFED(conv[i].statusbits.on          )fprintf(textfile,"\n(264.5)on(power=on;\t");FORCY p5dot0(conv[i].statusbits.on,           textfile);}
    IFED(conv[i].statusbits.w4on        )fprintf(textfile,"\n(264.6)w4on*******;\t");FORCY p5dot0(conv[i].statusbits.w4on,         textfile);}
    IFED(conv[i].statusbits.w4on_pulsed )fprintf(textfile,"\n(264.7)w4on_pulsed;\t");FORCY p5dot0(conv[i].statusbits.w4on_pulsed,  textfile);}
    IFED(conv[i].statusbits.wrk_wo_err  )fprintf(textfile,"\n(264.8)wrk_wo_err*;\t");FORCY p5dot0(conv[i].statusbits.wrk_wo_err,   textfile);}
    IFED(conv[i].statusbits.uf          )fprintf(textfile,"\n(264.9)uf(u/f=cons;\t");FORCY p5dot0(conv[i].statusbits.uf,           textfile);}
    IFED(conv[i].statusbits.r10         )fprintf(textfile,"\n(264.10)r10*******;\t");FORCY p5dot0(conv[i].statusbits.r10,          textfile);}
    //**********************************************************************************************************************
    for(j=0;j<2;j++){
    for(k=0;k<16;k++){
    uint32_t bit=(1<<k);
    IFED((conv[i].uvsbits[j] & bit))fprintf(textfile,"\n(26%d.%d)uvs(%d)***;\t",(5+j),k,(k+16*j));FORCY p5dot0((conv[i].uvsbits[j] & bit)?1:0,textfile);}
    }
    }
    j=2;
    for(k=0;k<4;k++){
    uint32_t bit=(1<<k);
    IFED((conv[i].uvsbits[j] & bit))fprintf(textfile,"\n(26%d.%d)uvs(%d)***;\t",(5+j),k,(k+16*j));FORCY p5dot0((conv[i].uvsbits[j] & bit)?1:0,textfile);}
    }
    //***********************************************************************************************************************

    IFED(conv[i].errbits_prev.err       ) fprintf(textfile,"\n(268.0)err********;\t");FORCY p5dot0(conv[i].errbits_prev.err,        textfile);}
    IFED(conv[i].errbits_prev.avost     ) fprintf(textfile,"\n(268.1)avost******;\t");FORCY p5dot0(conv[i].errbits_prev.avost,      textfile);}
    IFED(conv[i].errbits_prev.ixad_max  ) fprintf(textfile,"\n(268.2)ixad_max***;\t");FORCY p5dot0(conv[i].errbits_prev.ixad_max,   textfile);}
    IFED(conv[i].errbits_prev.iybd_max  ) fprintf(textfile,"\n(268.3)iybd_max***;\t");FORCY p5dot0(conv[i].errbits_prev.iybd_max,   textfile);}
    IFED(conv[i].errbits_prev.icd_max   ) fprintf(textfile,"\n(268.4)icd_max****;\t");FORCY p5dot0(conv[i].errbits_prev.icd_max,    textfile);}
    IFED(conv[i].errbits_prev.iod_max   ) fprintf(textfile,"\n(268.5)iod_max****;\t");FORCY p5dot0(conv[i].errbits_prev.iod_max,    textfile);}
    IFED(conv[i].errbits_prev.usw_gate_min) fprintf(textfile,"\n(268.6)usw_gate_mi;\t");FORCY p5dot0(conv[i].errbits_prev.usw_gate_min,textfile);}
    IFED(conv[i].errbits_prev.vpcb      ) fprintf(textfile,"\n(268.7)vpcb*******;\t");FORCY p5dot0(conv[i].errbits_prev.vpcb,       textfile);}
    IFED(conv[i].errbits_prev.err_dnt   ) fprintf(textfile,"\n(268.8)err_dnt****;\t");FORCY p5dot0(conv[i].errbits_prev.err_dnt,    textfile);}
    IFED(conv[i].errbits_prev.uvs       ) fprintf(textfile,"\n(268.9)uvs********;\t");FORCY p5dot0(conv[i].errbits_prev.uvs,        textfile);}
    IFED(conv[i].errbits_prev.eeprom    ) fprintf(textfile,"\n(268.10)eeprom****;\t");FORCY p5dot0(conv[i].errbits_prev.eeprom,     textfile);}
    IFED(conv[i].errbits_prev.qf        ) fprintf(textfile,"\n(268.11)qf********;\t");FORCY p5dot0(conv[i].errbits_prev.qf,         textfile);}
    IFED(conv[i].errbits_prev.ovl       ) fprintf(textfile,"\n(268.12)ovl*******;\t");FORCY p5dot0(conv[i].errbits_prev.ovl,        textfile);}
    IFED(conv[i].errbits_prev.vinp_min  ) fprintf(textfile,"\n(268.13)vinp_min**;\t");FORCY p5dot0(conv[i].errbits_prev.vinp_min,   textfile);}
    IFED(conv[i].errbits_prev.vinp_max  ) fprintf(textfile,"\n(268.14)vinp_max**;\t");FORCY p5dot0(conv[i].errbits_prev.vinp_max,   textfile);}
    IFED(conv[i].errbits_prev.cool      ) fprintf(textfile,"\n(268.15)cool******;\t");FORCY p5dot0(conv[i].errbits_prev.cool,       textfile);}
    //************************************************************************************************************************
    IFED(conv[i].errbits_volt.usab_max  ) fprintf(textfile,"\n(269.0)usab_max***;\t");FORCY p5dot0(conv[i].errbits_volt.usab_max,   textfile);}
    IFED(conv[i].errbits_volt.usab_min  ) fprintf(textfile,"\n(269.1)usab_min***;\t");FORCY p5dot0(conv[i].errbits_volt.usab_min,   textfile);}
    IFED(conv[i].errbits_volt.usbc_max  ) fprintf(textfile,"\n(269.2)usbc_max***;\t");FORCY p5dot0(conv[i].errbits_volt.usbc_max,   textfile);}
    IFED(conv[i].errbits_volt.usbc_min  ) fprintf(textfile,"\n(269.3)usbc_min***;\t");FORCY p5dot0(conv[i].errbits_volt.usbc_min,   textfile);}
    IFED(conv[i].errbits_volt.usca_max  ) fprintf(textfile,"\n(269.4)usca_max***;\t");FORCY p5dot0(conv[i].errbits_volt.usca_max,   textfile);}
    IFED(conv[i].errbits_volt.usca_min  ) fprintf(textfile,"\n(269.5)usca_min***;\t");FORCY p5dot0(conv[i].errbits_volt.usca_min,   textfile);}
    IFED(conv[i].errbits_volt.uxaab_max ) fprintf(textfile,"\n(269.6)uxaab_max**;\t");FORCY p5dot0(conv[i].errbits_volt.uxaab_max,   textfile);}
    IFED(conv[i].errbits_volt.uxaab_min ) fprintf(textfile,"\n(269.7)uxaab_min**;\t");FORCY p5dot0(conv[i].errbits_volt.uxaab_min,   textfile);}
    IFED(conv[i].errbits_volt.uxabc_max ) fprintf(textfile,"\n(269.8)uxabc_max**;\t");FORCY p5dot0(conv[i].errbits_volt.uxabc_max,   textfile);}
    IFED(conv[i].errbits_volt.uxabc_min ) fprintf(textfile,"\n(269.9)uxabc_min**;\t");FORCY p5dot0(conv[i].errbits_volt.uxabc_min,   textfile);}
    IFED(conv[i].errbits_volt.uxaca_max ) fprintf(textfile,"\n(269.10)uxaca_max*;\t");FORCY p5dot0(conv[i].errbits_volt.uxaca_max,   textfile);}
    IFED(conv[i].errbits_volt.uxaca_min ) fprintf(textfile,"\n(269.11)uxaca_min*;\t");FORCY p5dot0(conv[i].errbits_volt.uxaca_min,   textfile);}
    IFED(conv[i].errbits_volt.uybab_max ) fprintf(textfile,"\n(269.12)uybab_max*;\t");FORCY p5dot0(conv[i].errbits_volt.uybab_max,   textfile);}
    IFED(conv[i].errbits_volt.uybab_min ) fprintf(textfile,"\n(269.13)uybab_min*;\t");FORCY p5dot0(conv[i].errbits_volt.uybab_min,   textfile);}
    IFED(conv[i].errbits_volt.uybbc_max ) fprintf(textfile,"\n(269.14)uybbc_max*;\t");FORCY p5dot0(conv[i].errbits_volt.uybbc_max,   textfile);}
    IFED(conv[i].errbits_volt.uybbc_min ) fprintf(textfile,"\n(269.15)uybbc_min*;\t");FORCY p5dot0(conv[i].errbits_volt.uybbc_min,   textfile);}
    //****
    IFED(conv[i].errbits_volt.uybca_max ) fprintf(textfile,"\n(270.0)uybca_max**;\t");FORCY p5dot0(conv[i].errbits_volt.uybca_max,   textfile);}
    IFED(conv[i].errbits_volt.uybca_min ) fprintf(textfile,"\n(270.1)uybca_min**;\t");FORCY p5dot0(conv[i].errbits_volt.uybca_min,   textfile);}
    IFED(conv[i].errbits_volt.ucab_max  ) fprintf(textfile,"\n(270.2)ucab_max***;\t");FORCY p5dot0(conv[i].errbits_volt.ucab_max,    textfile);}
    IFED(conv[i].errbits_volt.ucab_min  ) fprintf(textfile,"\n(270.3)ucab_min***;\t");FORCY p5dot0(conv[i].errbits_volt.ucab_min,    textfile);}
    IFED(conv[i].errbits_volt.ucbc_max  ) fprintf(textfile,"\n(270.4)ucbc_max***;\t");FORCY p5dot0(conv[i].errbits_volt.ucbc_max,    textfile);}
    IFED(conv[i].errbits_volt.ucbc_min  ) fprintf(textfile,"\n(270.5)ucbc_min***;\t");FORCY p5dot0(conv[i].errbits_volt.ucbc_min,    textfile);}
    IFED(conv[i].errbits_volt.ucca_max  ) fprintf(textfile,"\n(270.6)ucca_max***;\t");FORCY p5dot0(conv[i].errbits_volt.ucca_max,    textfile);}
    IFED(conv[i].errbits_volt.ucca_min  ) fprintf(textfile,"\n(270.7)uybca_max**;\t");FORCY p5dot0(conv[i].errbits_volt.ucca_min,    textfile);}
    //*******************************************************************************************************************************************
    IFED(conv[i].errbits_pcb.u24V_max   ) fprintf(textfile,"\n(271.0)u24V_max***;\t");FORCY p5dot0(conv[i].errbits_pcb.u24V_max,     textfile);}
    IFED(conv[i].errbits_pcb.u24V_min   ) fprintf(textfile,"\n(271.1)u24V_min***;\t");FORCY p5dot0(conv[i].errbits_pcb.u24V_min,     textfile);}
    IFED(conv[i].errbits_pcb.u12V_max   ) fprintf(textfile,"\n(271.2)u12V_max***;\t");FORCY p5dot0(conv[i].errbits_pcb.u12V_max,     textfile);}
    IFED(conv[i].errbits_pcb.u12V_min   ) fprintf(textfile,"\n(271.3)u12V_min***;\t");FORCY p5dot0(conv[i].errbits_pcb.u12V_min,     textfile);}
    IFED(conv[i].errbits_pcb.u5V_max    ) fprintf(textfile,"\n(271.4)u5V_max****;\t");FORCY p5dot0(conv[i].errbits_pcb.u5V_max,      textfile);}
    IFED(conv[i].errbits_pcb.u5V_min    ) fprintf(textfile,"\n(271.5)u5V_min****;\t");FORCY p5dot0(conv[i].errbits_pcb.u5V_min,      textfile);}
    IFED(conv[i].errbits_pcb.u350V_max  ) fprintf(textfile,"\n(271.6)u350V_max**;\t");FORCY p5dot0(conv[i].errbits_pcb.u350V_max,    textfile);}
    IFED(conv[i].errbits_pcb.u350V_min  ) fprintf(textfile,"\n(271.7)u350V_min**;\t");FORCY p5dot0(conv[i].errbits_pcb.u350V_min,    textfile);}
    IFED(conv[i].errbits_pcb.u3V3_max   ) fprintf(textfile,"\n(271.8)u3V3_max***;\t");FORCY p5dot0(conv[i].errbits_pcb.u3V3_max,     textfile);}
    IFED(conv[i].errbits_pcb.u3V3_min   ) fprintf(textfile,"\n(271.9)u3V3_min***;\t");FORCY p5dot0(conv[i].errbits_pcb.u3V3_min,     textfile);}
    IFED(conv[i].errbits_pcb.ugate_max  ) fprintf(textfile,"\n(271.10)ugate_max*;\t");FORCY p5dot0(conv[i].errbits_pcb.ugate_max,    textfile);}
    IFED(conv[i].errbits_pcb.ugate_min  ) fprintf(textfile,"\n(271.11)ugate_min*;\t");FORCY p5dot0(conv[i].errbits_pcb.ugate_min,    textfile);}
    //*******************************************************************************************************************************************
    IFED(conv[i].errbits_qf.qf1         ) fprintf(textfile,"\n(272.0)qf1********;\t");FORCY p5dot0(conv[i].errbits_qf.qf1,           textfile);}
    IFED(conv[i].errbits_qf.qf2         ) fprintf(textfile,"\n(272.1)qf2********;\t");FORCY p5dot0(conv[i].errbits_qf.qf2,           textfile);}
    IFED(conv[i].errbits_qf.qf3         ) fprintf(textfile,"\n(272.2)qf3********;\t");FORCY p5dot0(conv[i].errbits_qf.qf3,           textfile);}
    IFED(conv[i].errbits_qf.qf4         ) fprintf(textfile,"\n(272.3)qf4********;\t");FORCY p5dot0(conv[i].errbits_qf.qf4,           textfile);}
    //*******************************************************************************************************************************************
    IFED(conv[i].errbits_ovl.ixaa       ) fprintf(textfile,"\n(273.0)ovl.ixaa***;\t");FORCY p5dot0(conv[i].errbits_ovl.ixaa,         textfile);}
    IFED(conv[i].errbits_ovl.ixab       ) fprintf(textfile,"\n(273.1)ovl.ixab***;\t");FORCY p5dot0(conv[i].errbits_ovl.ixab,         textfile);}
    IFED(conv[i].errbits_ovl.ixac       ) fprintf(textfile,"\n(273.2)ovl.ixac***;\t");FORCY p5dot0(conv[i].errbits_ovl.ixac,         textfile);}
    IFED(conv[i].errbits_ovl.iyba       ) fprintf(textfile,"\n(273.3)ovl.iyba***;\t");FORCY p5dot0(conv[i].errbits_ovl.iyba,         textfile);}
    IFED(conv[i].errbits_ovl.iybb       ) fprintf(textfile,"\n(273.4)ovl.iybb***;\t");FORCY p5dot0(conv[i].errbits_ovl.iybb,         textfile);}
    IFED(conv[i].errbits_ovl.iybc       ) fprintf(textfile,"\n(273.5)ovl.iybc***;\t");FORCY p5dot0(conv[i].errbits_ovl.iybc,         textfile);}
    IFED(conv[i].errbits_ovl.ica        ) fprintf(textfile,"\n(273.6)ovl.ica****;\t");FORCY p5dot0(conv[i].errbits_ovl.ica,          textfile);}
    IFED(conv[i].errbits_ovl.icb        ) fprintf(textfile,"\n(273.7)ovl.icb****;\t");FORCY p5dot0(conv[i].errbits_ovl.icb,          textfile);}
    IFED(conv[i].errbits_ovl.icc        ) fprintf(textfile,"\n(273.8)ovl.icc****;\t");FORCY p5dot0(conv[i].errbits_ovl.icc,          textfile);}
    //******************************************************************************************************************************************
    //TPL
    IFED(conv[i].di.ready_rev           ) fprintf(textfile,"\n(512.0)di.ready_re;\t");FORCY p5dot0(conv[i].di.ready_rev,             textfile);}
    IFED(conv[i].di.forvard             ) fprintf(textfile,"\n(512.1)di.forvard*;\t");FORCY p5dot0(conv[i].di.forvard,               textfile);}
    IFED(conv[i].di.reset               ) fprintf(textfile,"\n(512.2)di.reset***;\t");FORCY p5dot0(conv[i].di.reset,                 textfile);}
    IFED(conv[i].di.sel_f1              ) fprintf(textfile,"\n(512.3)di.sel_f1**;\t");FORCY p5dot0(conv[i].di.sel_f1,                textfile);}
    IFED(conv[i].di.sel_f2              ) fprintf(textfile,"\n(512.4)di.sel_f2**;\t");FORCY p5dot0(conv[i].di.sel_f2,                textfile);}
    IFED(conv[i].di.sel_f3              ) fprintf(textfile,"\n(512.5)di.sel_f3**;\t");FORCY p5dot0(conv[i].di.sel_f3,                textfile);}
    IFED(conv[i].di.remote              ) fprintf(textfile,"\n(512.6)di.remote**;\t");FORCY p5dot0(conv[i].di.remote,                textfile);}
    IFED(conv[i].di.rem_forvard         ) fprintf(textfile,"\n(512.7)di.rem_forv;\t");FORCY p5dot0(conv[i].di.rem_forvard,           textfile);}
    IFED(conv[i].di.air_sens            ) fprintf(textfile,"\n(512.8)di.air_sens;\t");FORCY p5dot0(conv[i].di.air_sens,              textfile);}
    IFED(conv[i].di.avost               ) fprintf(textfile,"\n(512.9)di.avost***;\t");FORCY p5dot0(conv[i].di.avost,                 textfile);}
    IFED(conv[i].di.qf1_on              ) fprintf(textfile,"\n(512.10)di.qf1_on*;\t");FORCY p5dot0(conv[i].di.qf1_on,                textfile);}
    IFED(conv[i].di.qf2_on              ) fprintf(textfile,"\n(512.11)di.qf2_on*;\t");FORCY p5dot0(conv[i].di.qf2_on,                textfile);}
    IFED(conv[i].di.qf3_on              ) fprintf(textfile,"\n(512.12)di.qf3_on*;\t");FORCY p5dot0(conv[i].di.qf3_on,                textfile);}
    IFED(conv[i].di.qf4_on              ) fprintf(textfile,"\n(512.13)di.qf4_on*;\t");FORCY p5dot0(conv[i].di.qf4_on,                textfile);}
    IFED(conv[i].di.rem_rev             ) fprintf(textfile,"\n(512.14)di.rem_rev;\t");FORCY p5dot0(conv[i].di.rem_rev,               textfile);}
    IFED(conv[i].di.di15                ) fprintf(textfile,"\n(512.15)di.di15***;\t");FORCY p5dot0(conv[i].di.di15,                  textfile);}
    //*******************************************************************************************************************************************
    IFED(conv[i].Do.err_ind             ) fprintf(textfile,"\n(513.0)Do.err_ind*;\t");FORCY p5dot0(conv[i].Do.err_ind,               textfile);}
    IFED(conv[i].Do.ready_on_ind        ) fprintf(textfile,"\n(513.1)Do.ready_on;\t");FORCY p5dot0(conv[i].Do.ready_on_ind,          textfile);}
    IFED(conv[i].Do.qf_off_inv          ) fprintf(textfile,"\n(513.2)Do.qf_off_i;\t");FORCY p5dot0(conv[i].Do.qf_off_inv,            textfile);}
    IFED(conv[i].Do.vuf_on              ) fprintf(textfile,"\n(513.3)Do.vuf_on**;\t");FORCY p5dot0(conv[i].Do.vuf_on,                textfile);}
    IFED(conv[i].Do.err_asu_inv         ) fprintf(textfile,"\n(513.4)Do.err_asu_;\t");FORCY p5dot0(conv[i].Do.err_asu_inv,           textfile);}
    IFED(conv[i].Do.on_asu              ) fprintf(textfile,"\n(513.5)Do.on_asu**;\t");FORCY p5dot0(conv[i].Do.on_asu,                textfile);}
    IFED(conv[i].Do.do6                 ) fprintf(textfile,"\n(513.6)Do.do6*****;\t");FORCY p5dot0(conv[i].Do.do6,                   textfile);}
    IFED(conv[i].Do.do7                 ) fprintf(textfile,"\n(513.7)Do.do7*****;\t");FORCY p5dot0(conv[i].Do.do7,                   textfile);}
    //*******************************************************************************************************************************************
    IFED(conv[i].uxaab                  )fprintf(textfile,"\n(626)pl->uxaab*****;\t");FORCY p4dot1(conv[i].uxaab,                    textfile);}
    IFED(conv[i].fixaab                 )fprintf(textfile,"\n(627)pl->fixaab****;\t");FORCY p4dot1(conv[i].fixaab,                   textfile);}
    IFED(conv[i].uxabc                  )fprintf(textfile,"\n(628)pl->uxabc*****;\t");FORCY p4dot1(conv[i].uxabc,                    textfile);}
    IFED(conv[i].fixabc                 )fprintf(textfile,"\n(629)pl->fixabc****;\t");FORCY p4dot1(conv[i].fixabc,                   textfile);}
    IFED(conv[i].uxaca                  )fprintf(textfile,"\n(630)pl->uxaca*****;\t");FORCY p4dot1(conv[i].uxaca,                    textfile);}
    IFED(conv[i].fixaca                 )fprintf(textfile,"\n(631)pl->fixaca****;\t");FORCY p4dot1(conv[i].fixaca,                   textfile);}

    IFED(conv[i].uybab                  )fprintf(textfile,"\n(632)pl->uybab*****;\t");FORCY p4dot1(conv[i].uybab,                    textfile);}
    IFED(conv[i].fiybab                 )fprintf(textfile,"\n(633)pl->fiybab****;\t");FORCY p4dot1(conv[i].fiybab,                   textfile);}
    IFED(conv[i].uybbc                  )fprintf(textfile,"\n(634)pl->uybbc*****;\t");FORCY p4dot1(conv[i].uybbc,                    textfile);}
    IFED(conv[i].fiybbc                 )fprintf(textfile,"\n(635)pl->fiybbc****;\t");FORCY p4dot1(conv[i].fiybbc,                   textfile);}
    IFED(conv[i].uybca                  )fprintf(textfile,"\n(636)pl->uybca*****;\t");FORCY p4dot1(conv[i].uybca,                    textfile);}
    IFED(conv[i].fiybca                 )fprintf(textfile,"\n(637)pl->fiybca****;\t");FORCY p4dot1(conv[i].fiybca,                   textfile);}

    IFED(conv[i].ucab                   )fprintf(textfile,"\n(638)pl->ucab******;\t");FORCY p4dot1(conv[i].ucab,                     textfile);}
    IFED(conv[i].ficab                  )fprintf(textfile,"\n(639)pl->ficab*****;\t");FORCY p4dot1(conv[i].ficab,                    textfile);}
    IFED(conv[i].ucbc                   )fprintf(textfile,"\n(640)pl->ucbc******;\t");FORCY p4dot1(conv[i].ucbc,                     textfile);}
    IFED(conv[i].ficbc                  )fprintf(textfile,"\n(641)pl->ficbc*****;\t");FORCY p4dot1(conv[i].ficbc,                    textfile);}
    IFED(conv[i].ucca                   )fprintf(textfile,"\n(642)pl->ucca******;\t");FORCY p4dot1(conv[i].ucca,                     textfile);}
    IFED(conv[i].ficca                  )fprintf(textfile,"\n(643)pl->ficca*****;\t");FORCY p4dot1(conv[i].ficca,                    textfile);}

    IFED(conv[i].usab                   )fprintf(textfile,"\n(644)pl->usab******;\t");FORCY p4dot1(conv[i].usab,                     textfile);}
    IFED(conv[i].fisab                  )fprintf(textfile,"\n(645)pl->fisab*****;\t");FORCY p4dot1(conv[i].fisab,                    textfile);}
    IFED(conv[i].usbc                   )fprintf(textfile,"\n(646)pl->usbc******;\t");FORCY p4dot1(conv[i].usbc,                     textfile);}
    IFED(conv[i].fisbc                  )fprintf(textfile,"\n(647)pl->fisbc*****;\t");FORCY p4dot1(conv[i].fisbc,                    textfile);}
    IFED(conv[i].usca                   )fprintf(textfile,"\n(648)pl->usca******;\t");FORCY p4dot1(conv[i].usca,                     textfile);}
    IFED(conv[i].fisca                  )fprintf(textfile,"\n(649)pl->fisca*****;\t");FORCY p4dot1(conv[i].fisca,                    textfile);}

    IFED(conv[i].uoab                   )fprintf(textfile,"\n(650)pl->uoab******;\t");FORCY p4dot1(conv[i].uoab,                     textfile);}
    IFED(conv[i].fioab                  )fprintf(textfile,"\n(651)pl->fioab*****;\t");FORCY p4dot1(conv[i].fioab,                    textfile);}
    IFED(conv[i].uobc                   )fprintf(textfile,"\n(652)pl->uobc******;\t");FORCY p4dot1(conv[i].uobc,                     textfile);}
    IFED(conv[i].fiobc                  )fprintf(textfile,"\n(653)pl->fiobc*****;\t");FORCY p4dot1(conv[i].fiobc,                    textfile);}
    IFED(conv[i].uoca                   )fprintf(textfile,"\n(654)pl->uoca******;\t");FORCY p4dot1(conv[i].uoca,                     textfile);}
    IFED(conv[i].fioca                  )fprintf(textfile,"\n(655)pl->fioca*****;\t");FORCY p4dot1(conv[i].fioca,                    textfile);}

    IFED(conv[i].ixaa                   )fprintf(textfile,"\n(656)pl->ixaa******;\t");FORCY p5dot0(conv[i].ixaa,                     textfile);}
    IFED(conv[i].ixab                   )fprintf(textfile,"\n(694)pl->ixab******;\t");FORCY p5dot0(conv[i].ixab,                     textfile);}
    IFED(conv[i].ixac                   )fprintf(textfile,"\n(695)pl->ixac******;\t");FORCY p5dot0(conv[i].ixac,                     textfile);}
    IFED(conv[i].ixad                   )fprintf(textfile,"\n(657)pl->ixad******;\t");FORCY p5dot0(conv[i].ixad,                     textfile);}

    IFED(conv[i].iyba                   )fprintf(textfile,"\n(658)pl->iyba******;\t");FORCY p5dot0(conv[i].iyba,                     textfile);}
    IFED(conv[i].iybb                   )fprintf(textfile,"\n(696)pl->iybb******;\t");FORCY p5dot0(conv[i].iybb,                     textfile);}
    IFED(conv[i].iybc                   )fprintf(textfile,"\n(697)pl->iybc******;\t");FORCY p5dot0(conv[i].iybc,                     textfile);}
    IFED(conv[i].iybd                   )fprintf(textfile,"\n(659)pl->iybd******;\t");FORCY p5dot0(conv[i].iybd,                     textfile);}

    IFED(conv[i].ica                    )fprintf(textfile,"\n(660)pl->ica*******;\t");FORCY p5dot0(conv[i].ica,                      textfile);}
    IFED(conv[i].icb                    )fprintf(textfile,"\n(698)pl->icb*******;\t");FORCY p5dot0(conv[i].icb,                      textfile);}
    IFED(conv[i].icc                    )fprintf(textfile,"\n(699)pl->icc*******;\t");FORCY p5dot0(conv[i].icc,                      textfile);}
    IFED(conv[i].icd                    )fprintf(textfile,"\n(661)pl->icd*******;\t");FORCY p5dot0(conv[i].icd,                      textfile);}

    IFED(conv[i].ioa                    )fprintf(textfile,"\n(662)pl->ioa*******;\t");FORCY p5dot0(conv[i].ioa,                      textfile);}
    IFED(conv[i].iob                    )fprintf(textfile,"\n(663)pl->iob*******;\t");FORCY p5dot0(conv[i].iob,                      textfile);}
    IFED(conv[i].ioc                    )fprintf(textfile,"\n(664)pl->ioc*******;\t");FORCY p5dot0(conv[i].ioc,                      textfile);}
    IFED(conv[i].iod                    )fprintf(textfile,"\n(665)pl->iod*******;\t");FORCY p5dot0(conv[i].iod,                      textfile);}

                                         fprintf(textfile,"\n(666)pl->iinp_max**;\t");FORCY p5dot0(conv[i].iinp_max,                 textfile);
                                         fprintf(textfile,"\n(667)pl->iinp_ovl**;\t");FORCY p5dot0(conv[i].iinp_ovl,                 textfile);
                                         fprintf(textfile,"\n(668)pl->ioutp_max*;\t");FORCY p5dot0(conv[i].ioutp_max,                textfile);
                                         fprintf(textfile,"\n(669)pl->ioutp_ovl*;\t");FORCY p5dot0(conv[i].ioutp_ovl,                textfile);
                                         fprintf(textfile,"\n(670)pl->t_ovl*****;\t");FORCY p4dot1(conv[i].t_ovl,                    textfile);

                                         fprintf(textfile,"\n(671)pl->t_gate1***;\t");FORCY p5dot0(conv[i].t_gate1,                  textfile);
                                         fprintf(textfile,"\n(672)pl->t_gate0***;\t");FORCY p5dot0(conv[i].t_gate0,                  textfile);

                                         fprintf(textfile,"\n(673)pl->shema**!*!;\t");FORCY p5dot0(conv[i].shema,                    textfile);
                                         fprintf(textfile,"\n(674)pl->t_logger**;\t");FORCY p5dot0(conv[i].t_logger,                 textfile);

                                         fprintf(textfile,"\n(675)->alfa_min_reg;\t");FORCY p4dot1(conv[i].alfa_min_reg,             textfile);
                                         fprintf(textfile,"\n(676)->alfa_max_reg;\t");FORCY p4dot1(conv[i].alfa_max_reg,             textfile);
                                         fprintf(textfile,"\n(677)->alfa_max****;\t");FORCY p4dot1(conv[i].alfa_max,                 textfile);
                                         fprintf(textfile,"\n(678)->alfa_paus***;\t");FORCY p4dot1(conv[i].alfa_paus,                textfile);
                                         fprintf(textfile,"\n(679)->alfa_imp****;\t");FORCY p4dot1(conv[i].alfa_imp,                 textfile);
                                         fprintf(textfile,"\n(680)alfa_test_plus;\t");FORCY p4dot1(conv[i].alfa_test_plus,           textfile);
                                         fprintf(textfile,"\n(681)alfa_test_minu;\t");FORCY p4dot1(conv[i].alfa_test_minus,          textfile);
                                         fprintf(textfile,"\n(713)->alfa_reg_out;\t");FORCY p4dot1(conv[i].alfa_reg_out,             textfile);

                                         fprintf(textfile,"\n(682.0)sco.sync_lin;\t");FORCY p5dot0(conv[i].sconfigbits.sync_lin,     textfile);
                                         fprintf(textfile,"\n(682.1)sco.en_alfa0;\t");FORCY p5dot0(conv[i].sconfigbits.en_alfa0,     textfile);

                                         fprintf(textfile,"\n(683)pl->freq******;\t");FORCY p3dot2(conv[i].freq_pl,                  textfile);
                                         fprintf(textfile,"\n(684)pl->tzp_minus*;\t");FORCY p5dot0(conv[i].tzp_minus,                textfile);
                                         fprintf(textfile,"\n(685)pl->tzp_plus**;\t");FORCY p5dot0(conv[i].tzp_plus,                 textfile);
                                         fprintf(textfile,"\n(686)pl->tdnt_min**;\t");FORCY p5dot0(conv[i].tdnt_min,                 textfile);
                                         fprintf(textfile,"\n(687)pl->tdnt_vu***;\t");FORCY p5dot0(conv[i].tdnt_vu,                  textfile);
                                         fprintf(textfile,"\n(688)pl->udnt_plus*;\t");FORCY p4dot1(conv[i].udnt_plus,                textfile);
                                         fprintf(textfile,"\n(689)pl->udnt_minus;\t");FORCY p4dot1(conv[i].udnt_minus,               textfile);
                                         fprintf(textfile,"\n(690)pl->idnt******;\t");FORCY p5dot0(conv[i].idnt,                     textfile);

                                         fprintf(textfile,"\n(700.0)dnt.da_plus*;\t");FORCY p5dot0(conv[i].dnt.da_plus,              textfile);
                                         fprintf(textfile,"\n(700.1)dnt.da_minus;\t");FORCY p5dot0(conv[i].dnt.da_minus,             textfile);
                                         fprintf(textfile,"\n(700.2)dnt.db_plus*;\t");FORCY p5dot0(conv[i].dnt.db_plus,              textfile);
                                         fprintf(textfile,"\n(700.3)dnt.db_minus;\t");FORCY p5dot0(conv[i].dnt.db_minus,             textfile);
                                         fprintf(textfile,"\n(700.4)dnt.da_plus*;\t");FORCY p5dot0(conv[i].dnt.dc_plus,              textfile);
                                         fprintf(textfile,"\n(700.5)dnt.da_minus;\t");FORCY p5dot0(conv[i].dnt.dc_minus,             textfile);

IFED(conv[i].statusbits_pl.wrk         ) fprintf(textfile,"\n(701.0)sbits_pl.wrk;\t");FORCY p5dot0(conv[i].statusbits_pl.wrk,        textfile);}
IFED(conv[i].statusbits_pl.reverse     ) fprintf(textfile,"\n(701.1)sbits_pl.rev;\t");FORCY p5dot0(conv[i].statusbits_pl.reverse,    textfile);}
IFED(conv[i].statusbits_pl.stest_rect  ) fprintf(textfile,"\n(701.2)s.stest_rect;\t");FORCY p5dot0(conv[i].statusbits_pl.stest_rect, textfile);}
IFED(conv[i].statusbits_pl.stest_fsm   ) fprintf(textfile,"\n(701.3)s.stest_fsm*;\t");FORCY p5dot0(conv[i].statusbits_pl.stest_fsm,  textfile);}
IFED(conv[i].statusbits_pl.err         ) fprintf(textfile,"\n(701.4)sbits_pl.err;\t");FORCY p5dot0(conv[i].statusbits_pl.err,        textfile);}
IFED(conv[i].statusbits_pl.s_i_lim     ) fprintf(textfile,"\n(701.5)s_pl.s_i_lim;\t");FORCY p5dot0(conv[i].statusbits_pl.s_i_lim,    textfile);}

IFED(conv[i].statusbits_pl.r6          ) fprintf(textfile,"\n(701.6)sbits_pl.r6*;\t");FORCY p5dot0(conv[i].statusbits_pl.r6,         textfile);}
IFED(conv[i].statusbits_pl.r7          ) fprintf(textfile,"\n(701.7)sbits_pl.r7*;\t");FORCY p5dot0(conv[i].statusbits_pl.r7,         textfile);}

                                         fprintf(textfile,"\n(702)pl->t_sample**;\t");FORCY p5dot0(conv[i].t_sample,                 textfile);
                                         fprintf(textfile,"\n(703)pl->uodf******;\t");FORCY p4dot1(conv[i].uodf,                     textfile);

                                         fprintf(textfile,"\n(704)pl->kpu_outp**;\t");FORCY p2dot3(conv[i].kpu_outp,                 textfile);
                                         fprintf(textfile,"\n(705)pl->kiu_outp**;\t");FORCY p2dot3(conv[i].kiu_outp,                 textfile);
                                         fprintf(textfile,"\n(706)pl->K_lim_iout;\t");FORCY p2dot3(conv[i].K_lim_iout,               textfile);
                                         fprintf(textfile,"\n(707)pl->set_u*****;\t");FORCY p4dot1(conv[i].set_u_pl,                 textfile);
   //***********************************************************************************************************************
   IFED(conv[i].errbits.err            ) fprintf(textfile,"\n(708.0)pl.err******;\t");FORCY p5dot0(conv[i].errbits.err,              textfile);}
   IFED(conv[i].errbits.avost          ) fprintf(textfile,"\n(708.1)pl.avost****;\t");FORCY p5dot0(conv[i].errbits.avost,            textfile);}
   IFED(conv[i].errbits.ixad_max       ) fprintf(textfile,"\n(708.2)pl.ixad_max*;\t");FORCY p5dot0(conv[i].errbits.ixad_max,         textfile);}
   IFED(conv[i].errbits.iybd_max       ) fprintf(textfile,"\n(708.3)pl.iybd_max*;\t");FORCY p5dot0(conv[i].errbits.iybd_max,         textfile);}
   IFED(conv[i].errbits.icd_max        ) fprintf(textfile,"\n(708.4)pl.icd_max**;\t");FORCY p5dot0(conv[i].errbits.icd_max,          textfile);}
   IFED(conv[i].errbits.iod_max        ) fprintf(textfile,"\n(708.5)pl.iod_max**;\t");FORCY p5dot0(conv[i].errbits.iod_max,          textfile);}
   IFED(conv[i].errbits.usw_gate_min   ) fprintf(textfile,"\n(708.6)pl.usw_gate_;\t");FORCY p5dot0(conv[i].errbits.usw_gate_min,     textfile);}
   IFED(conv[i].errbits.vpcb           ) fprintf(textfile,"\n(708.7)pl.vpcb*****;\t");FORCY p5dot0(conv[i].errbits.vpcb,             textfile);}
   IFED(conv[i].errbits.err_dnt        ) fprintf(textfile,"\n(708.8)pl.err_dnt**;\t");FORCY p5dot0(conv[i].errbits.err_dnt,          textfile);}
   IFED(conv[i].errbits.uvs            ) fprintf(textfile,"\n(708.9)pl.uvs******;\t");FORCY p5dot0(conv[i].errbits.uvs,              textfile);}
   IFED(conv[i].errbits.eeprom         ) fprintf(textfile,"\n(708.10)pl.eeprom**;\t");FORCY p5dot0(conv[i].errbits.eeprom,           textfile);}
   IFED(conv[i].errbits.qf             ) fprintf(textfile,"\n(708.11)pl.qf******;\t");FORCY p5dot0(conv[i].errbits.qf,               textfile);}
   IFED(conv[i].errbits.ovl            ) fprintf(textfile,"\n(708.12)pl.ovl*****;\t");FORCY p5dot0(conv[i].errbits.ovl,              textfile);}
   IFED(conv[i].errbits.vinp_min       ) fprintf(textfile,"\n(708.13)pl.vinp_min;\t");FORCY p5dot0(conv[i].errbits.vinp_min,         textfile);}
   IFED(conv[i].errbits.vinp_max       ) fprintf(textfile,"\n(708.14)pl.vinp_max;\t");FORCY p5dot0(conv[i].errbits.vinp_max,         textfile);}
   IFED(conv[i].errbits.cool           ) fprintf(textfile,"\n(708.15)pl.cool****;\t");FORCY p5dot0(conv[i].errbits.cool,             textfile);}
   //***********************************************************************************************************************
   IFED(conv[i].errbitsmk.err          ) fprintf(textfile,"\n(709.0)mk.err******;\t");FORCY p5dot0(conv[i].errbitsmk.err,            textfile);}
   IFED(conv[i].errbitsmk.avost        ) fprintf(textfile,"\n(709.1)mk.avost****;\t");FORCY p5dot0(conv[i].errbitsmk.avost,          textfile);}
   IFED(conv[i].errbitsmk.ixad_max     ) fprintf(textfile,"\n(709.2)mk.ixad_max*;\t");FORCY p5dot0(conv[i].errbitsmk.ixad_max,       textfile);}
   IFED(conv[i].errbitsmk.iybd_max     ) fprintf(textfile,"\n(709.3)mk.iybd_max*;\t");FORCY p5dot0(conv[i].errbitsmk.iybd_max,       textfile);}
   IFED(conv[i].errbitsmk.icd_max      ) fprintf(textfile,"\n(709.4)mk.icd_max**;\t");FORCY p5dot0(conv[i].errbitsmk.icd_max,        textfile);}
   IFED(conv[i].errbitsmk.iod_max      ) fprintf(textfile,"\n(709.5)mk.iod_max**;\t");FORCY p5dot0(conv[i].errbitsmk.iod_max,        textfile);}
   IFED(conv[i].errbitsmk.usw_gate_min ) fprintf(textfile,"\n(709.6)mk.usw_gate_;\t");FORCY p5dot0(conv[i].errbitsmk.usw_gate_min,   textfile);}
   IFED(conv[i].errbitsmk.vpcb         ) fprintf(textfile,"\n(709.7)mk.vpcb*****;\t");FORCY p5dot0(conv[i].errbitsmk.vpcb,           textfile);}
   IFED(conv[i].errbitsmk.err_dnt      ) fprintf(textfile,"\n(709.8)mk.err_dnt**;\t");FORCY p5dot0(conv[i].errbitsmk.err_dnt,        textfile);}
   IFED(conv[i].errbitsmk.uvs          ) fprintf(textfile,"\n(709.9)mk.uvs******;\t");FORCY p5dot0(conv[i].errbitsmk.uvs,            textfile);}
   IFED(conv[i].errbitsmk.eeprom       ) fprintf(textfile,"\n(709.10)mk.eeprom**;\t");FORCY p5dot0(conv[i].errbitsmk.eeprom,         textfile);}
   IFED(conv[i].errbitsmk.qf           ) fprintf(textfile,"\n(709.11)mk.qf******;\t");FORCY p5dot0(conv[i].errbitsmk.qf,             textfile);}
   IFED(conv[i].errbitsmk.ovl          ) fprintf(textfile,"\n(709.12)mk.ovl*****;\t");FORCY p5dot0(conv[i].errbitsmk.ovl,            textfile);}
   IFED(conv[i].errbitsmk.vinp_min     ) fprintf(textfile,"\n(709.13)mk.vinp_min;\t");FORCY p5dot0(conv[i].errbitsmk.vinp_min,       textfile);}
   IFED(conv[i].errbitsmk.vinp_max     ) fprintf(textfile,"\n(709.14)mk.vinp_max;\t");FORCY p5dot0(conv[i].errbitsmk.vinp_max,       textfile);}
   IFED(conv[i].errbitsmk.cool         ) fprintf(textfile,"\n(709.15)mk.cool****;\t");FORCY p5dot0(conv[i].errbitsmk.cool,           textfile);}
   //*******************************************************************************************************************************************
                                         fprintf(textfile,"\n(710.0)ms.err******;\t");FORCY p5dot0(conv[i].errmaskbits.err,            textfile);
                                         fprintf(textfile,"\n(710.1)mk.avost****;\t");FORCY p5dot0(conv[i].errmaskbits.avost,          textfile);
                                         fprintf(textfile,"\n(710.2)ms.ixad_max*;\t");FORCY p5dot0(conv[i].errmaskbits.ixad_max,       textfile);
                                         fprintf(textfile,"\n(710.3)ms.iybd_max*;\t");FORCY p5dot0(conv[i].errmaskbits.iybd_max,       textfile);
                                         fprintf(textfile,"\n(710.4)ms.icd_max**;\t");FORCY p5dot0(conv[i].errmaskbits.icd_max,        textfile);
                                         fprintf(textfile,"\n(710.5)ms.iod_max**;\t");FORCY p5dot0(conv[i].errmaskbits.iod_max,        textfile);
                                         fprintf(textfile,"\n(710.6)ms.usw_gate_;\t");FORCY p5dot0(conv[i].errmaskbits.usw_gate_min,   textfile);
                                         fprintf(textfile,"\n(710.7)ms.vpcb*****;\t");FORCY p5dot0(conv[i].errmaskbits.vpcb,           textfile);
                                         fprintf(textfile,"\n(710.8)ms.err_dnt**;\t");FORCY p5dot0(conv[i].errmaskbits.err_dnt,        textfile);
                                         fprintf(textfile,"\n(710.9)ms.uvs******;\t");FORCY p5dot0(conv[i].errmaskbits.uvs,            textfile);
                                         fprintf(textfile,"\n(710.10)ms.eeprom**;\t");FORCY p5dot0(conv[i].errmaskbits.eeprom,         textfile);
                                         fprintf(textfile,"\n(710.11)ms.qf******;\t");FORCY p5dot0(conv[i].errmaskbits.qf,             textfile);
                                         fprintf(textfile,"\n(710.12)ms.ovl*****;\t");FORCY p5dot0(conv[i].errmaskbits.ovl,            textfile);
                                         fprintf(textfile,"\n(710.13)ms.vinp_min;\t");FORCY p5dot0(conv[i].errmaskbits.vinp_min,       textfile);
                                         fprintf(textfile,"\n(710.14)ms.vinp_max;\t");FORCY p5dot0(conv[i].errmaskbits.vinp_max,       textfile);
                                         fprintf(textfile,"\n(710.15)ms.cool****;\t");FORCY p5dot0(conv[i].errmaskbits.cool,           textfile);
   //*******************************************************************************************************************************************
                                         fprintf(textfile,"\n(711)pl->usw_gate_m;\t");FORCY p3dot2(conv[i].usw_gate_min,               textfile);

}



int conv_npch(FILE *logfile,FILE *textfile,FILE *graficfile,FILE *oscfile,int osc_only){
    int rc;
if(!osc_only){
    tarhive *parhive=malloc(sizeof(tarhive));
    memset(parhive,0,sizeof(tarhive));

    fread(parhive, 1, sizeof(tarhive), logfile);
    fprintf(textfile,"(274)mk_version***;\t");p3dot2(parhive -> conv_start[0].mk_version,textfile);
    fprintf(textfile,"\n(275)sett_version*;\t");p3dot2(parhive -> conv_start[0].sett_version,textfile);
    fprintf(textfile,"\n(276)serial_num_pc;\t");p5dot0(parhive -> conv_start[0].serial_num_pcb,textfile);
    fprintf(textfile,"\n(277)complect*****;\t");p5dot0(parhive -> conv_start[0].complect,textfile);
    fprintf(textfile,"\n(608)fpga_version*;\t");p3dot2(parhive -> conv_start[0].fpga_version,textfile);
    fprintf(textfile,"\n%s",parhive->string_start);
    conv_print(parhive -> conv_start, textfile, parhive -> time_start);
    if(! parhive -> time_stop)  return -1; //Это означает что данные типа conv.bin -в них нет осциллограммы и данных о стопе
    fprintf(textfile,"\n%s",parhive->string_stop);
    conv_print(parhive -> conv_stop, textfile, parhive -> time_stop);
    rc=conv_npch_osc(parhive->osc, OSC_X,oscfile);
    if(rc) return -1;
}
else {
    toscarhive *poscarhive=malloc(sizeof(toscarhive));
    memset(poscarhive,0,sizeof(toscarhive));
    fread(poscarhive, 1, sizeof(toscarhive), logfile);
    rc=conv_npch_osc(poscarhive->osc, OSC_X,oscfile);
    if(rc) return -1;
}
rc=osc(OSC_X,OSC_Y, graficfile);
return  rc;
}
