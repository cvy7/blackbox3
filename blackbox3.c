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
#include "osc.h"
#include "draw.h"

int ch[16][32768];
void usage(){
    printf("\n");
    printf("=================================================\n");
    printf("|   usage:                                      |\n");
    printf("| blackbox3 -f arhxxx_xxx.bin -o oscfile        |\n");
    printf("| blackbox3 -fosc fpga_ram.bin -o oscfile       |\n");
    printf("=================================================\n");
}

int main(int argc, char *argv[])
{
    char *filename=0;
    char *filenameosc=0;
    char *outfilename=0;
    FILE *logfile=0;
    FILE *oscfile=0;
    FILE *textfile=0;
    FILE *graficfile=0;
    int  len=0,rc=0,osc_only=0;
    printf("\n");
    printf("=================================================\n");
    printf("|    Blackbox3 backend                          |\n");
    printf("|                                               |\n");
    printf("|            (" __DATE__ " " __TIME__ ")              |\n");
    printf("=================================================\n");

    // Parsing / checking parameter
    int i,j;
    for(i = 1; i < argc; i++)
    {
        if (strcmp (argv[i], "-f") == 0)
        {
            i++;
            if (i < argc)
                filename = argv[i];
        }
        else
        if (strcmp (argv[i], "-o") == 0)
        {
            i++;
            if (i < argc)
                filenameosc = argv[i];
        }
        if (strcmp (argv[i], "-fosc") == 0)
        {
            i++;
            osc_only=1;
            if (i < argc)
                filename = argv[i];
        }
    }
    if(filename) logfile=fopen(filename,"rb");
    else {usage();return 0;}
    if(filenameosc) oscfile=fopen(filenameosc,"r");
    if(!logfile) {
        printf("File %s don't open\n",filename);
        return -1;
    }
    if(!oscfile) {
        printf("File osc instructions: %s don't open\n",filenameosc);
    }

    outfilename=malloc(FILENAME_MAX);
    strcpy(outfilename,filename);
    len=strlen(outfilename);
    if(!osc_only){
    outfilename[len-4]=0;
    strcat(outfilename,".csv");
    textfile=fopen(outfilename,"w+");
    if(!textfile) {
        printf("File %s don't open for write\n",outfilename);
        return -1;
    }
    }
    outfilename[len-4]=0;
    strcat(outfilename,".png");
    graficfile=fopen(outfilename,"wb+");
    if(!graficfile) {
        printf("File %s don't open for write\n",outfilename);
        return -1;
    }

    rc=conv_npch(logfile,textfile,graficfile,oscfile,osc_only);
    if(logfile) fclose(logfile);
    if(textfile)fclose(textfile);
    if(oscfile) fclose(oscfile);
    if(rc) fclose(graficfile);
}    
