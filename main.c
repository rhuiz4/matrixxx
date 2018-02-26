#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  screen s;
  color c;
  struct matrix *edges;

  edges = new_matrix(4, 4);
  
  printf("Testing Matrix and Draw Functions:\n");
  
  printf("\nAdding points (100,100) and (200,200)\n");
  add_point(edges, 100, 100, 0);
  add_point(edges, 200, 200, 0);
  print_matrix(edges);

  printf("\nAdding edge (300,300) - (400,400)\n");
  add_edge(edges, 300, 300, 0, 400, 400, 0);
  print_matrix(edges);

  printf("\nIdentity Matrix:\n");
  struct matrix *identity = new_matrix(4,4);
  ident(identity);
  print_matrix(identity);

  printf("\nMultiplying Identity Matrix:\n");
  matrix_mult(identity, edges);
  print_matrix(edges);

  printf("\nMultiplying 4x4 Matrix to itself:\n");
  matrix_mult(edges, edges);
  print_matrix(edges);




  
  printf("Making Image...\n");

  struct matrix *image = new_matrix(4,4);

  
  int i;
  for (i = 0; i < 50; i++){
    add_edge(image, 50+i, 50, 0, 250+i, 450, 0);
  }
  for (i = 0; i < 50; i++){
    add_edge(image, 250+i, 50, 0, 250+i, 450, 0);
  }
   
  c.red = 255;
  
  draw_lines(image, s, c);
  display(s);
  free_matrix( edges );
  free_matrix( image );
  free_matrix( identity );
}
