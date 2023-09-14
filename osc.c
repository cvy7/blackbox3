/****************************************************************************
 *   Copyright (C) 2010-2014 by cvy7                                        *
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
#include <sys/times.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "conv_npch.h"
#include "draw.h"
#include "osc.h"


#define  N_CH 15
#define  N_CH_SUMM 32
#define  LA_MAX_CH 8
#define  STR_LEN 511
#define  OSC_MAX_X 32768
int ch[N_CH_SUMM][OSC_MAX_X];
char ch_descr[N_CH_SUMM][128];
int la_on=0;
int ch_last=0;

int osc(int x,int y, FILE *graficfile){
int xc,yc,nc;
int y0=y/2;
int y1;
int color[N_CH+1]={0x00ffff00,0x0000ffff,0x00ff00ff,0x000000ff,
                 0x00ffff7f,0x007fffff,0x00ff7fff,0x007f7fff,
                 0x00ffff00,0x0000ffff,0x00ff00ff,0x000000ff,
                 0x00ffff00,0x0000ffff,0x00ff00ff,0x00ff0000
                };
draw_init(x,y,graficfile);
for(nc=0;nc<(ch_last+1);nc++){//аналоговые каналы
    set_color(color[nc]);
    set_0(10,nc*20);
    drawstr(ch_descr[nc]);
    set_0(0,y0);
    for(xc=0;xc<x;xc++){
        yc=y0-ch[nc][xc];
        drawto(xc, yc);
    }
}
if(la_on){//Каналы ЛА
    for(nc=0;nc<LA_MAX_CH;nc++){//аналоговые каналы
        set_color(color[N_CH]);
        set_0(10,(ch_last+nc+1)*20);
        drawstr(ch_descr[ch_last+nc+1]);
        y0=(double)y/(double)LA_MAX_CH*(double)(nc+1);
        y1=y0-(double)y/(double)LA_MAX_CH*0.9;
        set_0(0,y0);
        for(xc=0;xc<x;xc++){
            yc=ch[nc+N_CH][xc]?y1:y0;
            drawto(xc, yc);
        }
    }
}
draw_close(graficfile);
return  0;
}

int conv_npch_osc(tosc *osc, int osc_x, FILE *oscfile){
int i,j,nch,pos,start;
double op1,op2;
tchan chan[N_CH_SUMM]={0};
char str[STR_LEN];
if(!oscfile) return -1;
nch=0;
start=0;
memset(ch_descr,0,sizeof (char)*N_CH_SUMM*128);
for(i=0;i<1023;i++){
memset(str,0,STR_LEN);
if(!fgets(str,STR_LEN,oscfile)) break;
for(pos=0;pos<STR_LEN;pos++){
    if (str[pos]=='#') break;//Это коментарий - новую строку
    if (str[pos]=='{') {//Это начало блока данных - новую строку
        start=1;
        break;
    }
    if (!start) break;
        if(str[pos]=='a' && str[pos+1]=='i'){
            if(!chan[nch].op1) {
                chan[nch].op1=1;
                chan[nch].index1=atoi(&str[pos+3]);//не анализируется - какие будут скобки
                strncpy(ch_descr[nch],&str[pos],128);
                ch_last=nch;
            }//для простоты
            else {
                chan[nch].op2=1;
                chan[nch].index2=atoi(&str[pos+3]);
            }
        }
        if(str[pos]=='i' && str[pos+1]=='a'){
            if(!chan[nch].op1) {
                chan[nch].op1=2;
                chan[nch].index1=atoi(&str[pos+3]);
                strncpy(ch_descr[nch],&str[pos],128);
                ch_last=nch;
            }
            else {
                chan[nch].op2=2;
                chan[nch].index2=atoi(&str[pos+3]);
            }
        }
        if(str[pos]=='g' && str[pos+1]=='b'){
            if(!chan[nch].op1) {
                chan[nch].op1=3;
                chan[nch].index1=atoi(&str[pos+3]);
                strncpy(ch_descr[nch],&str[pos],128);
                la_on=1;
                nch++;
                break;
            }
        }
        if(str[pos]=='*'){
            chan[nch].multipl=atof(&str[pos+1]);
            nch++;
            break;
        }
        if(str[pos]=='}'){
            goto oscc;
            break;
        }

    }
if(nch>=N_CH_SUMM) break;
}
oscc:
memset(ch,0,sizeof(int)*N_CH_SUMM*OSC_MAX_X);
for(i=0;i<(ch_last+1);i++) {
    printf("\n ch=%d op1=%d index1=%d op2=%d index2=%d multipl=%f",i,chan[i].op1,chan[i].index1,chan[i].op2,chan[i].index2,chan[i].multipl);
   // printf("\n%s",ch_descr[i]);
}
if(la_on){
    for(i=(ch_last+1);i<(ch_last+1+LA_MAX_CH);i++){
         printf("\n ch_la=%d op1=%d index1=%d",i,chan[i].op1,chan[i].index1);
    }
}
printf("\n");
for(j=0;j<N_CH_SUMM;j++){
    uint64_t bitmask=1;
    bitmask=bitmask<<chan[j].index1;
    for(i=0;i<osc_x;i++){
        ch[j][i]=osc[i].ia[j];
    if(!chan[j].op1) return 0;
    else if(chan[j].op1==3){//логический анализатор -каналы должны идти после аналоговых
           /*osc[i].gb[0]=0;//иначе будет работать неправильно
            osc[i].gb[1]=0;
            osc[i].gb[2]=3;*/
            uint64_t osbits=osc[i].gb[2];
            osbits<<=16;
            osbits|=osc[i].gb[1];
            osbits<<=16;
            osbits|=osc[i].gb[0];
            if(osbits & bitmask) ch[N_CH+j-ch_last-1][i]=1;
            //la_on=1;
        }
    else {//аналоговые каналы идут первыми
        op1=op2=0;
        if(chan[j].op1==1) op1=osc[i].ai[chan[j].index1];
        if(chan[j].op2==1) op2=osc[i].ai[chan[j].index2];
        if(chan[j].op1==2) op1=osc[i].ia[chan[j].index1];
        if(chan[j].op2==2) op2=osc[i].ia[chan[j].index2];
        ch[j][i]=(op1-op2)*chan[j].multipl;
        //ch_last=j;
        }
    }
}
return 0;
}

