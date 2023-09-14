#ifndef DRAW_H
#define DRAW_H
int draw_init(int x,int y,FILE *graficfile);
void set_color(int c);
void set_0(int x,int y);
int drawstr(char *str);
int drawto(int x, int y);
int draw_close(FILE *graficfile);
#endif // DRAW_H
