/*========== my_main.c ==========

  This is the only file you need to modify in order
  to get a working mdl project (for now).

  my_main.c will serve as the interpreter for mdl.
  When an mdl script goes through a lexer and parser, 
  the resulting operations will be in the array op[].

  Your job is to go through each entry in op and perform
  the required action from the list below:

  push: push a new origin matrix onto the origin stack
  pop: remove the top matrix on the origin stack

  move/scale/rotate: create a transformation matrix 
                     based on the provided values, then 
		     multiply the current top of the
		     origins stack by it.

  box/sphere/torus: create a solid object based on the
                    provided values. Store that in a 
		    temporary matrix, multiply it by the
		    current top of the origins stack, then
		    call draw_polygons.

  line: create a line based on the provided values. Store 
        that in a temporary matrix, multiply it by the
	current top of the origins stack, then call draw_lines.

  save: call save_extension with the provided filename

  display: view the image live
  
  jdyrlandweaver
  =========================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "parser.h"
#include "symtab.h"
#include "y.tab.h"

#include "matrix.h"
#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "stack.h"

void my_main() {

  int i;
  struct matrix *tmp;
  struct stack *s;
  screen t;
  color g;
  
  s = new_stack();
  tmp = new_matrix(4, 1000);
  clear_screen( t );

  for (i=0;i<lastop;i++) {  
    switch (op[i].opcode) {
    case PUSH:
      push(s);
      break; 
    case POP:
      pop(s);
      break;
    case MOVE:
      /*reference
	fgets(line, sizeof(line), f);
      //printf("MOVE\t%s", line);
      sscanf(line, "%lf %lf %lf",
	     xvals, yvals, zvals);
      //printf("%lf %lf %lf\n", 
      // 	xvals[0], yvals[0], zvals[0]);
      tmp = make_translate( xvals[0], yvals[0], zvals[0]);
      matrix_mult(peek(systems), tmp);
      copy_matrix(tmp, peek(systems));
       */
      break;
    case SCALE:
      /*reference 
	fgets(line, sizeof(line), f);
      //printf("SCALE\t%s", line);
      sscanf(line, "%lf %lf %lf",
	     xvals, yvals, zvals);
      // printf("%lf %lf %lf\n", 
      // 	xvals[0], yvals[0], zvals[0]); 
      tmp = make_scale( xvals[0], yvals[0], zvals[0]);      
      matrix_mult(peek(systems), tmp);
      copy_matrix(tmp, peek(systems));
       */
      break;
    case ROTATE:
      /*reference
	fgets(line, sizeof(line), f);
      //printf("Rotate\t%s", line);
      sscanf(line, "%c %lf",
	     &axis, &theta);      
      // printf("%c %lf\n", 
      // 	axis, theta); 
      theta = theta * (M_PI / 180);
      if ( axis == 'x' )
	tmp = make_rotX( theta );
      else if ( axis == 'y' )
	tmp = make_rotY( theta );
      else 
	tmp = make_rotZ( theta );
      matrix_mult(peek(systems), tmp);
      copy_matrix(tmp, peek(systems));
       */
      break;
    case BOX:
      /*reference
fgets(line, sizeof(line), f);
      //printf("BOX\t%s", line);

      sscanf(line, "%lf %lf %lf %lf %lf %lf",
	     xvals, yvals, zvals,
	     xvals+1, yvals+1, zvals+1);
      add_box(edges, xvals[0], yvals[0], zvals[0],
	      xvals[1], yvals[1], zvals[1]);

      matrix_mult(peek(systems), edges);
      draw_polygons(edges, s, c);
      edges->lastcol = 0;
      */
      break;
    case SPHERE:
      /*reference
fgets(line, sizeof(line), f);
      //printf("SPHERE\t%s", line);

      sscanf(line, "%lf %lf %lf %lf",
	     xvals, yvals, zvals, &r);
      add_sphere( edges, xvals[0], yvals[0], zvals[0], r, step);
      matrix_mult(peek(systems), edges);
      draw_polygons(edges, s, c);
      edges->lastcol = 0;
      */
      break;
    case TORUS:
      /*reference
fgets(line, sizeof(line), f);
      //printf("torus\t%s", line);

      sscanf(line, "%lf %lf %lf %lf %lf",
	     xvals, yvals, zvals, &r, &r1);
      add_torus( edges, xvals[0], yvals[0], zvals[0], r, r1, step);
      matrix_mult(peek(systems), edges);
      draw_polygons(edges, s, c);
      edges->lastcol = 0;
      */
      break;
    case LINE:
      /*reference
fgets(line, sizeof(line), f);
      //printf("LINE\t%s", line);

      sscanf(line, "%lf %lf %lf %lf %lf %lf",
	     xvals, yvals, zvals,
	     xvals+1, yvals+1, zvals+1);
      //printf("%lf %lf %lf %lf %lf %lf",
	     xvals[0], yvals[0], zvals[0],
	     xvals[1], yvals[1], zvals[1]) 
      add_edge(edges, xvals[0], yvals[0], zvals[0],
	       xvals[1], yvals[1], zvals[1]); 
*/
      break;
    case SAVE:
      /*reference
fgets(line, sizeof(line), f);
      *strchr(line, '\n') = 0;
      //printf("SAVE\t%s\n", line);
      save_extension(s, line);
      */
      break;
    case DISPLAY:
      display(s);
      break;

      /*push: push a new origin matrix onto the origin stack
  pop: remove the top matrix on the origin stack

  move/scale/rotate: create a transformation matrix 
                     based on the provided values, then 
		     multiply the current top of the
		     origins stack by it.

  box/sphere/torus: create a solid object based on the
                    provided values. Store that in a 
		    temporary matrix, multiply it by the
		    current top of the origins stack, then
		    call draw_polygons.

  line: create a line based on the provided values. Store 
        that in a temporary matrix, multiply it by the
	current top of the origins stack, then call draw_lines.

  save: call save_extension with the provided filename

  display: view the image live*/
    }
  }
}
