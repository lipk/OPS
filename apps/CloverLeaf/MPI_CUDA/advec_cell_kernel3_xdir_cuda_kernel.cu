//
// auto-generated by ops.py on 2014-03-17 15:34
//

__constant__ int xdim0_advec_cell_kernel3_xdir;
__constant__ int xdim1_advec_cell_kernel3_xdir;
__constant__ int xdim2_advec_cell_kernel3_xdir;
__constant__ int xdim3_advec_cell_kernel3_xdir;
__constant__ int xdim4_advec_cell_kernel3_xdir;
__constant__ int xdim5_advec_cell_kernel3_xdir;
__constant__ int xdim6_advec_cell_kernel3_xdir;
__constant__ int xdim7_advec_cell_kernel3_xdir;

#define OPS_ACC0(x,y) (x+xdim0_advec_cell_kernel3_xdir*(y))
#define OPS_ACC1(x,y) (x+xdim1_advec_cell_kernel3_xdir*(y))
#define OPS_ACC2(x,y) (x+xdim2_advec_cell_kernel3_xdir*(y))
#define OPS_ACC3(x,y) (x+xdim3_advec_cell_kernel3_xdir*(y))
#define OPS_ACC4(x,y) (x+xdim4_advec_cell_kernel3_xdir*(y))
#define OPS_ACC5(x,y) (x+xdim5_advec_cell_kernel3_xdir*(y))
#define OPS_ACC6(x,y) (x+xdim6_advec_cell_kernel3_xdir*(y))
#define OPS_ACC7(x,y) (x+xdim7_advec_cell_kernel3_xdir*(y))

//user function
__device__

inline void advec_cell_kernel3_xdir( const double *vol_flux_x, const double *pre_vol, const int *xx,
                              const double *vertexdx,
                              const double *density1, const double *energy1 ,
                              double *mass_flux_x, double *ener_flux) {

  double sigma, sigmat, sigmav, sigmam, sigma3, sigma4;
  double diffuw, diffdw, limiter;
  double one_by_six = 1.0/6.0;


  int upwind,donor,downwind,dif;





  if(vol_flux_x[OPS_ACC0(0,0)] > 0.0) {
    upwind   = -2;
    donor    = -1;
    downwind = 0;
    dif      = donor;
  }
  else if (xx[OPS_ACC2(1,0)] < x_max+2-2) {
    upwind   = 1;
    donor    = 0;
    downwind = -1;
    dif      = upwind;
  } else {
    upwind   = 0;
    donor    = 0;
    downwind = -1;
    dif      = upwind;
  }


  sigmat = fabs(vol_flux_x[OPS_ACC0(0,0)])/pre_vol[OPS_ACC1(donor,0)];
  sigma3 = (1.0 + sigmat)*(vertexdx[OPS_ACC3(0,0)]/vertexdx[OPS_ACC3(dif,0)]);
  sigma4 = 2.0 - sigmat;

  sigma = sigmat;
  sigmav = sigmat;

  diffuw = density1[OPS_ACC4(donor,0)] - density1[OPS_ACC4(upwind,0)];
  diffdw = density1[OPS_ACC4(downwind,0)] - density1[OPS_ACC4(donor,0)];

  if( (diffuw*diffdw) > 0.0)
    limiter=(1.0 - sigmav) * SIGN(1.0 , diffdw) *
    MIN( MIN(fabs(diffuw), fabs(diffdw)),
    one_by_six * (sigma3*fabs(diffuw) + sigma4 * fabs(diffdw)));
  else
    limiter=0.0;

  mass_flux_x[OPS_ACC6(0,0)] = (vol_flux_x[OPS_ACC0(0,0)]) * ( density1[OPS_ACC4(donor,0)] + limiter );

  sigmam = fabs(mass_flux_x[OPS_ACC6(0,0)])/( density1[OPS_ACC4(donor,0)] * pre_vol[OPS_ACC1(donor,0)]);
  diffuw = energy1[OPS_ACC5(donor,0)] - energy1[OPS_ACC5(upwind,0)];
  diffdw = energy1[OPS_ACC5(downwind,0)] - energy1[OPS_ACC5(donor,0)];

  if( (diffuw*diffdw) > 0.0)
    limiter = (1.0 - sigmam) * SIGN(1.0,diffdw) *
    MIN( MIN(fabs(diffuw), fabs(diffdw)),
    one_by_six * (sigma3 * fabs(diffuw) + sigma4 * fabs(diffdw)));
  else
    limiter=0.0;

  ener_flux[OPS_ACC7(0,0)] = mass_flux_x[OPS_ACC6(0,0)] * ( energy1[OPS_ACC5(donor,0)] + limiter );
}



#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6
#undef OPS_ACC7


__global__ void ops_advec_cell_kernel3_xdir(
const double* __restrict arg0,
const double* __restrict arg1,
const int* __restrict arg2,
const double* __restrict arg3,
const double* __restrict arg4,
const double* __restrict arg5,
double* __restrict arg6,
double* __restrict arg7,
int size0,
int size1 ){


  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1 + idx_y * 1 * xdim0_advec_cell_kernel3_xdir;
  arg1 += idx_x * 1 + idx_y * 1 * xdim1_advec_cell_kernel3_xdir;
  arg2 += idx_x * 1 + idx_y * 0 * xdim2_advec_cell_kernel3_xdir;
  arg3 += idx_x * 1 + idx_y * 0 * xdim3_advec_cell_kernel3_xdir;
  arg4 += idx_x * 1 + idx_y * 1 * xdim4_advec_cell_kernel3_xdir;
  arg5 += idx_x * 1 + idx_y * 1 * xdim5_advec_cell_kernel3_xdir;
  arg6 += idx_x * 1 + idx_y * 1 * xdim6_advec_cell_kernel3_xdir;
  arg7 += idx_x * 1 + idx_y * 1 * xdim7_advec_cell_kernel3_xdir;

  if (idx_x < size0 && idx_y < size1) {
    advec_cell_kernel3_xdir(arg0, arg1, arg2, arg3,
                   arg4, arg5, arg6, arg7);
  }

}

// host stub function
void ops_par_loop_advec_cell_kernel3_xdir(char const *name, ops_block Block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5, ops_arg arg6, ops_arg arg7) {

  ops_arg args[8] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7};

  sub_block_list sb = OPS_sub_block_list[Block->index];
  //compute localy allocated range for the sub-block
  int ndim = sb->ndim;
  int start_add[ndim*8];

  int s[ndim];
  int e[ndim];

  for ( int n=0; n<ndim; n++ ){
    s[n] = sb->istart[n];e[n] = sb->iend[n]+1;
    if (s[n] >= range[2*n]) {
      s[n] = 0;
    }
    else {
      s[n] = range[2*n] - s[n];
    }
    if (e[n] >= range[2*n+1]) {
      e[n] = range[2*n+1] - sb->istart[n];
    }
    else {
      e[n] = sb->sizes[n];
    }
  }

  for ( int i=0; i<8; i++ ){
    for ( int n=0; n<ndim; n++ ){
      start_add[i*ndim+n] = s[n];
    }
  }


  int x_size = e[0]-s[0];
  int y_size = e[1]-s[1];

  int xdim0 = args[0].dat->block_size[0]*args[0].dat->dim;
  int xdim1 = args[1].dat->block_size[0]*args[1].dat->dim;
  int xdim2 = args[2].dat->block_size[0]*args[2].dat->dim;
  int xdim3 = args[3].dat->block_size[0]*args[3].dat->dim;
  int xdim4 = args[4].dat->block_size[0]*args[4].dat->dim;
  int xdim5 = args[5].dat->block_size[0]*args[5].dat->dim;
  int xdim6 = args[6].dat->block_size[0]*args[6].dat->dim;
  int xdim7 = args[7].dat->block_size[0]*args[7].dat->dim;


  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(10,"advec_cell_kernel3_xdir");
  ops_timers_core(&c1,&t1);

  if (OPS_kernels[10].count == 0) {
    cudaMemcpyToSymbol( xdim0_advec_cell_kernel3_xdir, &xdim0, sizeof(int) );
    cudaMemcpyToSymbol( xdim1_advec_cell_kernel3_xdir, &xdim1, sizeof(int) );
    cudaMemcpyToSymbol( xdim2_advec_cell_kernel3_xdir, &xdim2, sizeof(int) );
    cudaMemcpyToSymbol( xdim3_advec_cell_kernel3_xdir, &xdim3, sizeof(int) );
    cudaMemcpyToSymbol( xdim4_advec_cell_kernel3_xdir, &xdim4, sizeof(int) );
    cudaMemcpyToSymbol( xdim5_advec_cell_kernel3_xdir, &xdim5, sizeof(int) );
    cudaMemcpyToSymbol( xdim6_advec_cell_kernel3_xdir, &xdim6, sizeof(int) );
    cudaMemcpyToSymbol( xdim7_advec_cell_kernel3_xdir, &xdim7, sizeof(int) );
  }



  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, (y_size-1)/OPS_block_size_y + 1, 1);
  dim3 block(OPS_block_size_x,OPS_block_size_y,1);



  int dat0 = args[0].dat->size;
  int dat1 = args[1].dat->size;
  int dat2 = args[2].dat->size;
  int dat3 = args[3].dat->size;
  int dat4 = args[4].dat->size;
  int dat5 = args[5].dat->size;
  int dat6 = args[6].dat->size;
  int dat7 = args[7].dat->size;

  char *p_a[8];

  //set up initial pointers
  int base0 = dat0 * 1 * 
  (start_add[ndim+0] * args[0].stencil->stride[0] - args[0].dat->offset[0]);
  base0 = base0  + dat0 * args[0].dat->block_size[0] * 
  (start_add[ndim+1] * args[0].stencil->stride[1] - args[0].dat->offset[1]);
  p_a[0] = (char *)args[0].data_d + base0;

  //set up initial pointers
  int base1 = dat1 * 1 * 
  (start_add[ndim+0] * args[1].stencil->stride[0] - args[1].dat->offset[0]);
  base1 = base1  + dat1 * args[1].dat->block_size[0] * 
  (start_add[ndim+1] * args[1].stencil->stride[1] - args[1].dat->offset[1]);
  p_a[1] = (char *)args[1].data_d + base1;

  //set up initial pointers
  int base2 = dat2 * 1 * 
  (start_add[ndim+0] * args[2].stencil->stride[0] - args[2].dat->offset[0]);
  base2 = base2  + dat2 * args[2].dat->block_size[0] * 
  (start_add[ndim+1] * args[2].stencil->stride[1] - args[2].dat->offset[1]);
  p_a[2] = (char *)args[2].data_d + base2;

  //set up initial pointers
  int base3 = dat3 * 1 * 
  (start_add[ndim+0] * args[3].stencil->stride[0] - args[3].dat->offset[0]);
  base3 = base3  + dat3 * args[3].dat->block_size[0] * 
  (start_add[ndim+1] * args[3].stencil->stride[1] - args[3].dat->offset[1]);
  p_a[3] = (char *)args[3].data_d + base3;

  //set up initial pointers
  int base4 = dat4 * 1 * 
  (start_add[ndim+0] * args[4].stencil->stride[0] - args[4].dat->offset[0]);
  base4 = base4  + dat4 * args[4].dat->block_size[0] * 
  (start_add[ndim+1] * args[4].stencil->stride[1] - args[4].dat->offset[1]);
  p_a[4] = (char *)args[4].data_d + base4;

  //set up initial pointers
  int base5 = dat5 * 1 * 
  (start_add[ndim+0] * args[5].stencil->stride[0] - args[5].dat->offset[0]);
  base5 = base5  + dat5 * args[5].dat->block_size[0] * 
  (start_add[ndim+1] * args[5].stencil->stride[1] - args[5].dat->offset[1]);
  p_a[5] = (char *)args[5].data_d + base5;

  //set up initial pointers
  int base6 = dat6 * 1 * 
  (start_add[ndim+0] * args[6].stencil->stride[0] - args[6].dat->offset[0]);
  base6 = base6  + dat6 * args[6].dat->block_size[0] * 
  (start_add[ndim+1] * args[6].stencil->stride[1] - args[6].dat->offset[1]);
  p_a[6] = (char *)args[6].data_d + base6;

  //set up initial pointers
  int base7 = dat7 * 1 * 
  (start_add[ndim+0] * args[7].stencil->stride[0] - args[7].dat->offset[0]);
  base7 = base7  + dat7 * args[7].dat->block_size[0] * 
  (start_add[ndim+1] * args[7].stencil->stride[1] - args[7].dat->offset[1]);
  p_a[7] = (char *)args[7].data_d + base7;


  ops_H_D_exchanges_cuda(args, 8);


  //call kernel wrapper function, passing in pointers to data
  ops_advec_cell_kernel3_xdir<<<grid, block >>> (  (double *)p_a[0], (double *)p_a[1],
           (int *)p_a[2], (double *)p_a[3],
           (double *)p_a[4], (double *)p_a[5],
           (double *)p_a[6], (double *)p_a[7],x_size, y_size);

  if (OPS_diags>1) cutilSafeCall(cudaDeviceSynchronize());
  ops_set_dirtybit_cuda(args, 8);

  //Update kernel record
  ops_timers_core(&c2,&t2);
  OPS_kernels[10].count++;
  OPS_kernels[10].time += t2-t1;
  OPS_kernels[10].transfer += ops_compute_transfer(dim, range, &arg0);
  OPS_kernels[10].transfer += ops_compute_transfer(dim, range, &arg1);
  OPS_kernels[10].transfer += ops_compute_transfer(dim, range, &arg2);
  OPS_kernels[10].transfer += ops_compute_transfer(dim, range, &arg3);
  OPS_kernels[10].transfer += ops_compute_transfer(dim, range, &arg4);
  OPS_kernels[10].transfer += ops_compute_transfer(dim, range, &arg5);
  OPS_kernels[10].transfer += ops_compute_transfer(dim, range, &arg6);
  OPS_kernels[10].transfer += ops_compute_transfer(dim, range, &arg7);
}
