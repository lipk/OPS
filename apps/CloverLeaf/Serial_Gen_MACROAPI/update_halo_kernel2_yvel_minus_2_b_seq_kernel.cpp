//
// auto-generated by ops.py on 2013-11-04 15:57
//

#include "lib.h"
//user function
#include "update_halo_kernel.h"

// host stub function
void ops_par_loop_update_halo_kernel2_yvel_minus_2_b(char const *name, int dim, int* range,
 ops_arg arg0, ops_arg arg1) {

  char *p_a[2];
  int  offs[2][2];
  int  count[dim];

  ops_arg args[2] = { arg0, arg1};


  for ( int i=0; i<2; i++ ){
    if (args[i].stencil!=NULL) {
      offs[i][0] = 1;  //unit step in x dimension
      offs[i][1] = ops_offs_set(range[0],range[2]+1, args[i]) - ops_offs_set(range[1],range[2], args[i]) +1;
      //stride in y as x stride is 0
      if (args[i].stencil->stride[0] == 0) {
        offs[i][0] = 0;
        offs[i][1] = args[i].dat->block_size[0];
      }
      //stride in x as y stride is 0
      else if (args[i].stencil->stride[1] == 0) {
        offs[i][0] = 1;
        offs[i][1] = -( range[1] - range[0] ) +1;
      }
    }
  }
  //set up initial pointers
  for ( int i=0; i<2; i++ ){
    if (args[i].argtype == OPS_ARG_DAT) {
      p_a[i] = (char *)args[i].data //base of 2D array
      +
      //y dimension -- get to the correct y line
      args[i].dat->size * args[i].dat->block_size[0] * ( range[2] * args[i].stencil->stride[1] - args[i].dat->offset[1] )
      +
      //x dimension - get to the correct x point on the y line
      args[i].dat->size * ( range[0] * args[i].stencil->stride[0] - args[i].dat->offset[0] );
    }
    else if (args[i].argtype == OPS_ARG_GBL) {
      p_a[i] = (char *)args[i].data;
    }
  }

  int total_range = 1;
  for ( int m=0; m<dim; m++ ){
    //number in each dimension
    count[m] = range[2*m+1]-range[2*m];
    total_range *= count[m];
  }
  //extra in last to ensure correct termination
  count[dim-1]++;


  xdim0 = args[0].dat->block_size[0];
  xdim1 = args[1].dat->block_size[0];

  for ( int nt=0; nt<total_range; nt++ ){
    //call kernel function, passing in pointers to data

    update_halo_kernel2_yvel_minus_2_b(  (double *)p_a[0], (double *)p_a[1] );

    //decrement counter
    count[0]--;

    //max dimension with changed index
    int m = 0;
    while ( (count[m]==0) ){
      count[m] = range[2*m+1]-range[2*m]; // reset counter
      m++;                                // next dimension
      count[m]--;                         // decrement counter
    }

    //shift pointers to data
    p_a[0]= p_a[0] + (args[0].dat->size * offs[0][m]);
    p_a[1]= p_a[1] + (args[1].dat->size * offs[1][m]);
  }

}
