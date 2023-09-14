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
#include "gd.h"
#include <gdfontg.h>
#include <gdfontl.h>
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


gdImagePtr im=NULL;
int x_curr,y_curr;
int color;

void set_color(int c){
    color=c;
}

void set_0(int x,int y){
    x_curr=x;
    y_curr=y;
}

void draw_grid(int x,int y){
    int i,j;
    double xl,yl,xinc,yinc,xinc2,yinc2;
    xl=1;
    xinc=(double)x/10.0;
    set_color(0xffffff);
    for(i=0;i<10;i++){
        gdImageDashedLine (im, xl, 0, xl, y, color);
        xl=xl+xinc;
    }
    gdImageDashedLine (im, x-1, 0, x-1, y, color);
    yl=1;
    yinc=y/8.0;
    for(i=0;i<8;i++){
        gdImageDashedLine (im, 0, yl, x, yl, color);
        yl=yl+yinc;
    }
    gdImageDashedLine (im, 0, y-1, x, y-1, color);
    xl=1;
    yl=1;
    xinc=(double)x/50.0;
    yinc2=(double)y/100.0;
    yinc=(double)y/2.;
    for(j=0;j<3;j++){
        for(i=0;i<51;i++){
            gdImageLine (im, xl, yl-yinc2, xl, yl+yinc2, color);
            xl=xl+xinc;
        }
        xl=1;
        yl=yl+yinc;
    }
    xl=1;
    yl=1;
    yinc=(double)y/40.0;
    xinc2=(double)x/100.0;
    xinc=(double)x/2.;
    for(j=0;j<3;j++){
        for(i=0;i<41;i++){
            gdImageLine (im, xl-xinc2, yl, xl+xinc2, yl, color);
            yl=yl+yinc;
        }
        yl=1;
        xl=xl+xinc;
    }
}

int draw_init(int x,int y,FILE *graficfile){
    if(!graficfile) return -1;
    im = gdImageCreateTrueColor(x, y);
    set_color(0);
    gdImageFilledRectangle(im, 0, 0, x, y, color);
    draw_grid(x,y);
}

int drawstr(char *str){
    gdFontPtr lfont, gfont;
    lfont = gdFontGetLarge();
    gfont = gdFontGetGiant();
gdImageString (im, gfont, x_curr, y_curr, str, color);
return 0;
}

int drawto(int x, int y){
gdImageLine (im, x_curr, y_curr, x, y, color);
x_curr=x;y_curr=y;
}

int draw_close(FILE *graficfile){
    if(!im) return -1;
    if(!graficfile) return -1;
    gdImagePng(im, graficfile);
    fclose(graficfile);

    gdImageDestroy(im);
}
