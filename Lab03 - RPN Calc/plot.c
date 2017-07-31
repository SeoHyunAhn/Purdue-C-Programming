/*
 Implement the program plot that will plot the rpn function passed as a parameter.
  */
#include <stdio.h>
#include <stdlib.h>

#include "rpn.h"

#define MAXCOLS 80
#define MAXROWS 40

char plot[MAXROWS][MAXCOLS];

void clearPlot()
{
  for (int i = 0; i < MAXROWS; i++) {
    for (int j = 0; j < MAXCOLS; j++) {
      plot[i][j] = ' ';
    }
  }
}

void printPlot()
{
  for (int i = MAXROWS; i >= 0 ; i--) {
    for (int j = 0; j < MAXCOLS; j++) {
      printf("%c", plot[i][j]);
    }
    printf("\n");
  }
}

void plotXY(int x, int y, char c) {
  if ( x <0 || x>=MAXCOLS || y < 0 || y >=MAXROWS) return;
  plot[y][x]=c;
}

void createPlot( char * funcFile, double minX, double maxX) {
  int nvals = MAXCOLS;
  double yy[MAXCOLS];
    double xx[MAXCOLS];
  clearPlot();
    int i=0, j=0;
  // Evaluate function and store in vector yy
double minY;
double maxY;
double x;

for(;i<MAXCOLS;i++){
    x=minX+(maxX-minX)*i/MAXCOLS;
    yy[i]=rpn_eval(funcFile, x);
    xx[i];
}
    minY=yy[0];
    maxY=yy[0];

for ( ; j < MAXCOLS; j++) {
    if (yy[j] < minY)
      minY = yy[j];
    if (yy[j] > maxY)
      maxY = yy[j];
  }
  //Plot x and yaxis

  for (int a=0 ; a < MAXCOLS; a++) {
      if(minY<0)
          plotXY(a,20, '_');
      else
          plotXY(a, 0, '_');
      plotXY(40,a,'|');
  }
    for (int b=0; b<MAXCOLS; b++) {
        int x = b; // X plotted value
        int y = (int) ((yy[b] - minY) * MAXROWS / (maxY - minY)); // Y plotted value
        plotXY(x, y, '*');
    }
  printPlot();

}

int main(int argc, char ** argv)
{
  printf("RPN Plotter.\n");
  
  if (argc < 4) {
    printf("Usage: plot func-file xmin xmax\n");
    exit(1);
  }
  // Get arguments
  
double minX=atof(argv[2]);
double maxX=atof(argv[3]);
char *funcname=argv[1];
createPlot(funcname, minX, maxX);
  //createPlot(funcName, xmin, xmax);
}
