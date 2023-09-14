#ifndef OSC_H
#define OSC_H
typedef struct {
   int op1;
   int index1;
   int op2;
   int index2;
double multipl;
} tchan;

int osc(int x,int y, FILE *graficfile);
int conv_npch_osc(tosc *osc, int osc_x, FILE *oscfile);
#endif // OSC_H
