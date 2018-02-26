#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

/*======== void add_point() ==========
Inputs:   struct matrix * points
         int x
         int y
         int z 
Returns: 
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point( struct matrix * points, double x, double y, double z) {
  if(points->lastcol == points->cols)
    grow_matrix(points,points->lastcol+1);

  points->m[points->lastcol][0] = x;
  points->m[points->lastcol][1] = y;
  points->m[points->lastcol][2] = z;
  points->m[points->lastcol][3] = 1;
 
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns: 
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should use add_point
====================*/
void add_edge( struct matrix * points, 
	       double x0, double y0, double z0, 
	       double x1, double y1, double z1) {
  add_point(points, x0, y0, z0);
  add_point(points, x1, y1, z1);
  
}

/*======== void draw_lines() ==========
Inputs:   struct matrix * points
         screen s
         color c 
Returns: 
Go through points 2 at a time and call draw_line to add that line
to the screen
====================*/
void draw_lines( struct matrix * points, screen s, color c) {
  int i = 0;
  while(i < points->lastcol){
    draw_line(points->m[i][0], points->m[i][1], points->m[i+1][0], points->m[i+1][1], s, c);
    i += 2;
  }
}



void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
  
  int x = x0;
  int y = y0;

  //if (x0,y0) is to the right of (x1,y1) then switch
  if (x0 > x1){
    x = x1;
    x1 = x0;

    y = y1;
    y1 = y0;

  }

  int A = y1 - y;
  int B = x - x1;

  //Octant 2
  if (A > 0 && A >= -B){
    int d = A + 2 * B;
    while (y <= y1){
      plot (s, c, x, y);
      if (d < 0){
        x++;
        d += 2 * A;
    }
      y++;
      d += 2 * B;
    }
  }

  
  //Octant 1
  else if (A >= 0 && A < -B){
    int d = 2 * A + B;
    while (x <= x1){
      plot(s, c, x, y);
      if (d > 0){
        y++;
        d += 2 * B;
     }
      x++;
      d += 2 * A;
    }
  }

  //Octant 8
  else if (A < 0 && A >= B){
    int d = 2 * A - B;
    while (x <= x1){
      plot(s, c, x, y);
      if (d < 0){
        y--;
        d -= 2 * B;
      }
      x++;
      d += 2 * A;
    }
  }

  //Octant 7
  else{
    int d = A - 2 * B;
    while (y >= y1){
      plot(s, c, x, y);
      if (d > 0){
        x++;
        d += 2 * A;
      }
      y--;
      d -= 2 * B;
    }
  }
} //end draw_line
