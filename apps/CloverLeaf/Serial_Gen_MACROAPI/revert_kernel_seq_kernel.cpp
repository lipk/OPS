//
// auto-generated by ops.py on 2013-11-04 16:48
//

#include "lib.h"
//user function
#include "revert_kernel.h"

// host stub function
void ops_par_loop_revert_kernel(char const *name, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3) {

  char *p_a[4];
  int  offs[4][2];
  int  count[dim];

  ops_arg args[4] = { arg0, arg1, arg2, arg3};


  for ( int i=0; i<4; i++ ){
    if (args[i].stencil!=NULL) {
      offs[i][0] = 1;  //unit step in x dimension
      offs[i][1] = ops_offs_set(range[0],range[2]+1, args[i]) - ops_offs_set(range[1],range[2], args[i]);
      //stride in y as x stride is 0
      if (args[i].stencil->stride[0] == 0) {
        offs[i][0] = 0;
        offs[i][1] = args[i].dat->block_size[0];
      }
      //stride in x as y stride is 0
      else if (args[i].stencil->stride[1] == 0) {
        offs[i][0] = 1;
        offs[i][1] = -( range[1] - range[0] );
      }
    }
  }

  //set up initial pointers
  p_a[0] = (char *)args[0].data
  + args[0].dat->size * args[0].dat->block_size[0] * ( range[2] * args[0].stencil->stride[1] - args[0].dat->offset[1] )
  + args[0].dat->size * ( range[0] * args[0].stencil->stride[0] - args[0].dat->offset[0] );

  p_a[1] = (char *)args[1].data
  + args[1].dat->size * args[1].dat->block_size[0] * ( range[2] * args[1].stencil->stride[1] - args[1].dat->offset[1] )
  + args[1].dat->size * ( range[0] * args[1].stencil->stride[0] - args[1].dat->offset[0] );

  p_a[2] = (char *)args[2].data
  + args[2].dat->size * args[2].dat->block_size[0] * ( range[2] * args[2].stencil->stride[1] - args[2].dat->offset[1] )
  + args[2].dat->size * ( range[0] * args[2].stencil->stride[0] - args[2].dat->offset[0] );

  p_a[3] = (char *)args[3].data
  + args[3].dat->size * args[3].dat->block_size[0] * ( range[2] * args[3].stencil->stride[1] - args[3].dat->offset[1] )
  + args[3].dat->size * ( range[0] * args[3].stencil->stride[0] - args[3].dat->offset[0] );


  xdim0 = args[0].dat->block_size[0];
  xdim1 = args[1].dat->block_size[0];
  xdim2 = args[2].dat->block_size[0];
  xdim3 = args[3].dat->block_size[0];

  for ( int n_y=range[2]; n_y<range[3]; n_y++ ){
    for ( int n_x=range[0]; n_x<range[1]; n_x++ ){
      //call kernel function, passing in pointers to data

      revert_kernel(  (double *)p_a[0], (double *)p_a[1], (double *)p_a[2],
           (double *)p_a[3] );


      //shift pointers to data x direction
      p_a[0]= p_a[0] + (args[0].dat->size * offs[0][0]);
      p_a[1]= p_a[1] + (args[1].dat->size * offs[1][0]);
      p_a[2]= p_a[2] + (args[2].dat->size * offs[2][0]);
      p_a[3]= p_a[3] + (args[3].dat->size * offs[3][0]);
    }

    //shift pointers to data y direction
    p_a[0]= p_a[0] + (args[0].dat->size * offs[0][1]);
    p_a[1]= p_a[1] + (args[1].dat->size * offs[1][1]);
    p_a[2]= p_a[2] + (args[2].dat->size * offs[2][1]);
    p_a[3]= p_a[3] + (args[3].dat->size * offs[3][1]);
  }
}
