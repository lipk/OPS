//
// auto-generated by ops.py
//
#include "./OpenACC/tea_leaf_common.h"

#define OPS_GPU

int xdim0_initialise_chunk_kernel_zero;


#undef OPS_ACC0


#define OPS_ACC0(x,y) (x+xdim0_initialise_chunk_kernel_zero*(y))

//user function
inline
void initialise_chunk_kernel_zero(double *var) {
  *var = 0.0;
}


#undef OPS_ACC0



void initialise_chunk_kernel_zero_c_wrapper(
  double *p_a0,
  int x_size, int y_size) {
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0)
  #pragma acc loop
  #endif
  for ( int n_y=0; n_y<y_size; n_y++ ){
    #ifdef OPS_GPU
    #pragma acc loop
    #endif
    for ( int n_x=0; n_x<x_size; n_x++ ){
      initialise_chunk_kernel_zero(  p_a0 + n_x*1*1 + n_y*xdim0_initialise_chunk_kernel_zero*1*1 );

    }
  }
}
