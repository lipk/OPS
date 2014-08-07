//
<<<<<<< HEAD
// auto-generated by ops.py on 2014-07-31 11:59
=======
// auto-generated by ops.py on 2014-07-10 14:54
>>>>>>> 901c039... Initial setup, mostly working for single node
//

#include "./OpenACC/clover_leaf_common.h"

#define OPS_GPU

int xdim0_advec_mom_kernel1_y_nonvector;
int xdim1_advec_mom_kernel1_y_nonvector;
int xdim2_advec_mom_kernel1_y_nonvector;
int xdim3_advec_mom_kernel1_y_nonvector;
int xdim4_advec_mom_kernel1_y_nonvector;

#define OPS_ACC0(x,y) (x+xdim0_advec_mom_kernel1_y_nonvector*(y))
#define OPS_ACC1(x,y) (x+xdim1_advec_mom_kernel1_y_nonvector*(y))
#define OPS_ACC2(x,y) (x+xdim2_advec_mom_kernel1_y_nonvector*(y))
#define OPS_ACC3(x,y) (x+xdim3_advec_mom_kernel1_y_nonvector*(y))
#define OPS_ACC4(x,y) (x+xdim4_advec_mom_kernel1_y_nonvector*(y))

//user function

inline void advec_mom_kernel1_y_nonvector( const double *node_flux, const double *node_mass_pre,
                       double *mom_flux,
                       const double *celldy, const double *vel1) {





  double sigma, wind, width;
  double vdiffuw, vdiffdw, auw, adw, limiter;
  int upwind, donor, downwind, dif;
  double advec_vel_temp;

  if( (node_flux[OPS_ACC0(0,0)]) < 0.0) {
    upwind = 2;
    donor = 1;
    downwind = 0;
    dif = donor;
  } else {
    upwind = -1;
    donor = 0;
    downwind = 1;
    dif = upwind;
  }

  sigma = fabs(node_flux[OPS_ACC0(0,0)])/node_mass_pre[OPS_ACC1(0,donor)];
  width = celldy[OPS_ACC3(0,0)];
  vdiffuw = vel1[OPS_ACC4(0,donor)] - vel1[OPS_ACC4(0,upwind)];
  vdiffdw = vel1[OPS_ACC4(0,downwind)] - vel1[OPS_ACC4(0,donor)];
  limiter = 0.0;
  if(vdiffuw*vdiffdw > 0.0) {
    auw = fabs(vdiffuw);
    adw = fabs(vdiffdw);
    wind = 1.0;
    if(vdiffdw <= 0.0) wind = -1.0;
    limiter=wind*MIN(width*((2.0-sigma)*adw/width+(1.0+sigma)*auw/celldy[OPS_ACC3(0,dif)])/6.0,MIN(auw,adw));
  }
  advec_vel_temp= vel1[OPS_ACC4(0,donor)] + (1.0 - sigma) * limiter;
  mom_flux[OPS_ACC2(0,0)] = advec_vel_temp * node_flux[OPS_ACC0(0,0)];
}



#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4


void advec_mom_kernel1_y_nonvector_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  double *p_a3,
  double *p_a4,
  int x_size, int y_size) {
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1,p_a2,p_a3,p_a4)
  #pragma acc loop
  #endif
  for ( int n_y=0; n_y<y_size; n_y++ ){
    #ifdef OPS_GPU
    #pragma acc loop
    #endif
    for ( int n_x=0; n_x<x_size; n_x++ ){
      advec_mom_kernel1_y_nonvector(  p_a0 + n_x*1 + n_y*xdim0_advec_mom_kernel1_y_nonvector*1,
           p_a1 + n_x*1 + n_y*xdim1_advec_mom_kernel1_y_nonvector*1, p_a2 + n_x*1 + n_y*xdim2_advec_mom_kernel1_y_nonvector*1,
           p_a3 + n_x*0 + n_y*xdim3_advec_mom_kernel1_y_nonvector*1, p_a4 + n_x*1 + n_y*xdim4_advec_mom_kernel1_y_nonvector*1 );

    }
  }
}
