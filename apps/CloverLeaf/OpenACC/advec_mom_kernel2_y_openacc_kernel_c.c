//
<<<<<<< HEAD
// auto-generated by ops.py on 2014-07-31 11:59
=======
// auto-generated by ops.py on 2014-07-10 14:54
>>>>>>> 901c039... Initial setup, mostly working for single node
//

#include "./OpenACC/clover_leaf_common.h"

#define OPS_GPU

int xdim0_advec_mom_kernel2_y;
int xdim1_advec_mom_kernel2_y;
int xdim2_advec_mom_kernel2_y;
int xdim3_advec_mom_kernel2_y;

#define OPS_ACC0(x,y) (x+xdim0_advec_mom_kernel2_y*(y))
#define OPS_ACC1(x,y) (x+xdim1_advec_mom_kernel2_y*(y))
#define OPS_ACC2(x,y) (x+xdim2_advec_mom_kernel2_y*(y))
#define OPS_ACC3(x,y) (x+xdim3_advec_mom_kernel2_y*(y))

//user function

inline void advec_mom_kernel2_y( double *vel1, const double *node_mass_post,
                        const double *node_mass_pre, const double *mom_flux) {

  vel1[OPS_ACC0(0,0)] = ( vel1[OPS_ACC0(0,0)] * node_mass_pre[OPS_ACC2(0,0)]  +
    mom_flux[OPS_ACC3(0,-1)] - mom_flux[OPS_ACC3(0,0)] ) / node_mass_post[OPS_ACC1(0,0)];
}



#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3


void advec_mom_kernel2_y_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  double *p_a3,
  int x_size, int y_size) {
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1,p_a2,p_a3)
  #pragma acc loop
  #endif
  for ( int n_y=0; n_y<y_size; n_y++ ){
    #ifdef OPS_GPU
    #pragma acc loop
    #endif
    for ( int n_x=0; n_x<x_size; n_x++ ){
      advec_mom_kernel2_y(  p_a0 + n_x*1 + n_y*xdim0_advec_mom_kernel2_y*1,
           p_a1 + n_x*1 + n_y*xdim1_advec_mom_kernel2_y*1, p_a2 + n_x*1 + n_y*xdim2_advec_mom_kernel2_y*1,
           p_a3 + n_x*1 + n_y*xdim3_advec_mom_kernel2_y*1 );

    }
  }
}
