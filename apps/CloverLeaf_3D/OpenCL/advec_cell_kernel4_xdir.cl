//
// auto-generated by ops.py
//

#ifdef OCL_FMA
#pragma OPENCL FP_CONTRACT ON
#else
#pragma OPENCL FP_CONTRACT OFF
#endif
#pragma OPENCL EXTENSION cl_khr_fp64:enable

#include "user_types.h"
#include "ops_opencl_reduction.h"

#ifndef MIN
#define MIN(a,b) ((a<b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b) ((a>b) ? (a) : (b))
#endif
#ifndef SIGN
#define SIGN(a,b) ((b<0.0) ? (a*(-1)) : (a))
#endif
#define OPS_READ 0
#define OPS_WRITE 1
#define OPS_RW 2
#define OPS_INC 3
#define OPS_MIN 4
#define OPS_MAX 5
#define ZERO_double 0.0;
#define INFINITY_double INFINITY;
#define ZERO_float 0.0f;
#define INFINITY_float INFINITY;
#define ZERO_int 0;
#define INFINITY_int INFINITY;
#define ZERO_uint 0;
#define INFINITY_uint INFINITY;
#define ZERO_ll 0;
#define INFINITY_ll INFINITY;
#define ZERO_ull 0;
#define INFINITY_ull INFINITY;
#define ZERO_bool 0;
#define OPS_ACC0(x,y,z) (x+xdim0_advec_cell_kernel4_xdir*(y)+xdim0_advec_cell_kernel4_xdir*ydim0_advec_cell_kernel4_xdir*(z))
#define OPS_ACC1(x,y,z) (x+xdim1_advec_cell_kernel4_xdir*(y)+xdim1_advec_cell_kernel4_xdir*ydim1_advec_cell_kernel4_xdir*(z))
#define OPS_ACC2(x,y,z) (x+xdim2_advec_cell_kernel4_xdir*(y)+xdim2_advec_cell_kernel4_xdir*ydim2_advec_cell_kernel4_xdir*(z))
#define OPS_ACC3(x,y,z) (x+xdim3_advec_cell_kernel4_xdir*(y)+xdim3_advec_cell_kernel4_xdir*ydim3_advec_cell_kernel4_xdir*(z))
#define OPS_ACC4(x,y,z) (x+xdim4_advec_cell_kernel4_xdir*(y)+xdim4_advec_cell_kernel4_xdir*ydim4_advec_cell_kernel4_xdir*(z))
#define OPS_ACC5(x,y,z) (x+xdim5_advec_cell_kernel4_xdir*(y)+xdim5_advec_cell_kernel4_xdir*ydim5_advec_cell_kernel4_xdir*(z))
#define OPS_ACC6(x,y,z) (x+xdim6_advec_cell_kernel4_xdir*(y)+xdim6_advec_cell_kernel4_xdir*ydim6_advec_cell_kernel4_xdir*(z))
#define OPS_ACC7(x,y,z) (x+xdim7_advec_cell_kernel4_xdir*(y)+xdim7_advec_cell_kernel4_xdir*ydim7_advec_cell_kernel4_xdir*(z))
#define OPS_ACC8(x,y,z) (x+xdim8_advec_cell_kernel4_xdir*(y)+xdim8_advec_cell_kernel4_xdir*ydim8_advec_cell_kernel4_xdir*(z))
#define OPS_ACC9(x,y,z) (x+xdim9_advec_cell_kernel4_xdir*(y)+xdim9_advec_cell_kernel4_xdir*ydim9_advec_cell_kernel4_xdir*(z))
#define OPS_ACC10(x,y,z) (x+xdim10_advec_cell_kernel4_xdir*(y)+xdim10_advec_cell_kernel4_xdir*ydim10_advec_cell_kernel4_xdir*(z))


//user function
inline void advec_cell_kernel4_xdir( __global double * restrict density1, __global double * restrict energy1, const __global double * restrict mass_flux_x, 
const __global double * restrict vol_flux_x, const __global double * restrict pre_vol, const __global double * restrict post_vol, __global double * restrict pre_mass, 
__global double * restrict post_mass, __global double * restrict advec_vol, __global double * restrict post_ener, const __global double * restrict ener_flux)

 {

  pre_mass[OPS_ACC6(0,0,0)] = density1[OPS_ACC0(0,0,0)] * pre_vol[OPS_ACC4(0,0,0)];
  post_mass[OPS_ACC7(0,0,0)] = pre_mass[OPS_ACC6(0,0,0)] + mass_flux_x[OPS_ACC2(0,0,0)] - mass_flux_x[OPS_ACC2(1,0,0)];
  post_ener[OPS_ACC9(0,0,0)] = ( energy1[OPS_ACC1(0,0,0)] * pre_mass[OPS_ACC6(0,0,0)] + ener_flux[OPS_ACC10(0,0,0)] - ener_flux[OPS_ACC10(1,0,0)])/post_mass[OPS_ACC7(0,0,0)];
  advec_vol[OPS_ACC8(0,0,0)] = pre_vol[OPS_ACC4(0,0,0)] + vol_flux_x[OPS_ACC3(0,0,0)] - vol_flux_x[OPS_ACC3(1,0,0)];
  density1[OPS_ACC0(0,0,0)] = post_mass[OPS_ACC7(0,0,0)]/advec_vol[OPS_ACC8(0,0,0)];
  energy1[OPS_ACC1(0,0,0)] = post_ener[OPS_ACC9(0,0,0)];

}



#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6
#undef OPS_ACC7
#undef OPS_ACC8
#undef OPS_ACC9
#undef OPS_ACC10



__kernel void ops_advec_cell_kernel4_xdir(
__global double* restrict arg0,
__global double* restrict arg1,
__global const double* restrict arg2,
__global const double* restrict arg3,
__global const double* restrict arg4,
__global const double* restrict arg5,
__global double* restrict arg6,
__global double* restrict arg7,
__global double* restrict arg8,
__global double* restrict arg9,
__global const double* restrict arg10,
const int base0,
const int base1,
const int base2,
const int base3,
const int base4,
const int base5,
const int base6,
const int base7,
const int base8,
const int base9,
const int base10,
const int size0,
const int size1,
const int size2 ){


  int idx_z = get_global_id(2);
  int idx_y = get_global_id(1);
  int idx_x = get_global_id(0);

  if (idx_x < size0 && idx_y < size1 && idx_z < size2) {
    advec_cell_kernel4_xdir(&arg0[base0 + idx_x * 1*1 + idx_y * 1*1 * xdim0_advec_cell_kernel4_xdir + idx_z * 1*1 * xdim0_advec_cell_kernel4_xdir * ydim0_advec_cell_kernel4_xdir],
                      &arg1[base1 + idx_x * 1*1 + idx_y * 1*1 * xdim1_advec_cell_kernel4_xdir + idx_z * 1*1 * xdim1_advec_cell_kernel4_xdir * ydim1_advec_cell_kernel4_xdir],
                      &arg2[base2 + idx_x * 1*1 + idx_y * 1*1 * xdim2_advec_cell_kernel4_xdir + idx_z * 1*1 * xdim2_advec_cell_kernel4_xdir * ydim2_advec_cell_kernel4_xdir],
                      &arg3[base3 + idx_x * 1*1 + idx_y * 1*1 * xdim3_advec_cell_kernel4_xdir + idx_z * 1*1 * xdim3_advec_cell_kernel4_xdir * ydim3_advec_cell_kernel4_xdir],
                      &arg4[base4 + idx_x * 1*1 + idx_y * 1*1 * xdim4_advec_cell_kernel4_xdir + idx_z * 1*1 * xdim4_advec_cell_kernel4_xdir * ydim4_advec_cell_kernel4_xdir],
                      &arg5[base5 + idx_x * 1*1 + idx_y * 1*1 * xdim5_advec_cell_kernel4_xdir + idx_z * 1*1 * xdim5_advec_cell_kernel4_xdir * ydim5_advec_cell_kernel4_xdir],
                      &arg6[base6 + idx_x * 1*1 + idx_y * 1*1 * xdim6_advec_cell_kernel4_xdir + idx_z * 1*1 * xdim6_advec_cell_kernel4_xdir * ydim6_advec_cell_kernel4_xdir],
                      &arg7[base7 + idx_x * 1*1 + idx_y * 1*1 * xdim7_advec_cell_kernel4_xdir + idx_z * 1*1 * xdim7_advec_cell_kernel4_xdir * ydim7_advec_cell_kernel4_xdir],
                      &arg8[base8 + idx_x * 1*1 + idx_y * 1*1 * xdim8_advec_cell_kernel4_xdir + idx_z * 1*1 * xdim8_advec_cell_kernel4_xdir * ydim8_advec_cell_kernel4_xdir],
                      &arg9[base9 + idx_x * 1*1 + idx_y * 1*1 * xdim9_advec_cell_kernel4_xdir + idx_z * 1*1 * xdim9_advec_cell_kernel4_xdir * ydim9_advec_cell_kernel4_xdir],
                      &arg10[base10 + idx_x * 1*1 + idx_y * 1*1 * xdim10_advec_cell_kernel4_xdir + idx_z * 1*1 * xdim10_advec_cell_kernel4_xdir * ydim10_advec_cell_kernel4_xdir]);
  }

}
