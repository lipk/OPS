//
// auto-generated by ops.py on 2014-03-17 15:34
//

__constant__ int xdim0_update_halo_kernel2_yvel_plus_4_b;
__constant__ int xdim1_update_halo_kernel2_yvel_plus_4_b;

#define OPS_ACC0(x,y) (x+xdim0_update_halo_kernel2_yvel_plus_4_b*(y))
#define OPS_ACC1(x,y) (x+xdim1_update_halo_kernel2_yvel_plus_4_b*(y))

//user function
__device__

inline void update_halo_kernel2_yvel_plus_4_b(double *yvel0, double *yvel1, const int* fields) {
  if(fields[FIELD_XVEL0] == 1) yvel0[OPS_ACC0(0,0)] = yvel0[OPS_ACC0(-4,0)];
  if(fields[FIELD_XVEL1] == 1) yvel1[OPS_ACC1(0,0)] = yvel1[OPS_ACC1(-4,0)];
}



#undef OPS_ACC0
#undef OPS_ACC1


__global__ void ops_update_halo_kernel2_yvel_plus_4_b(
double* __restrict arg0,
double* __restrict arg1,
const int* __restrict arg2,
int size0,
int size1 ){


  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1 + idx_y * 1 * xdim0_update_halo_kernel2_yvel_plus_4_b;
  arg1 += idx_x * 1 + idx_y * 1 * xdim1_update_halo_kernel2_yvel_plus_4_b;

  if (idx_x < size0 && idx_y < size1) {
    update_halo_kernel2_yvel_plus_4_b(arg0, arg1, arg2);
  }

}

// host stub function
void ops_par_loop_update_halo_kernel2_yvel_plus_4_b(char const *name, ops_block Block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2) {

  ops_arg args[3] = { arg0, arg1, arg2};

  sub_block_list sb = OPS_sub_block_list[Block->index];
  //compute localy allocated range for the sub-block
  int ndim = sb->ndim;
  int start_add[ndim*3];

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

  for ( int i=0; i<3; i++ ){
    for ( int n=0; n<ndim; n++ ){
      start_add[i*ndim+n] = s[n];
    }
  }


  int x_size = e[0]-s[0];
  int y_size = e[1]-s[1];

  int xdim0 = args[0].dat->block_size[0]*args[0].dat->dim;
  int xdim1 = args[1].dat->block_size[0]*args[1].dat->dim;


  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(58,"update_halo_kernel2_yvel_plus_4_b");
  ops_timers_core(&c1,&t1);

  if (OPS_kernels[58].count == 0) {
    cudaMemcpyToSymbol( xdim0_update_halo_kernel2_yvel_plus_4_b, &xdim0, sizeof(int) );
    cudaMemcpyToSymbol( xdim1_update_halo_kernel2_yvel_plus_4_b, &xdim1, sizeof(int) );
  }


  int *arg2h = (int *)arg2.data;

  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, (y_size-1)/OPS_block_size_y + 1, 1);
  dim3 block(OPS_block_size_x,OPS_block_size_y,1);

  int consts_bytes = 0;

  consts_bytes += ROUND_UP(15*sizeof(int));

  reallocConstArrays(consts_bytes);

  consts_bytes = 0;
  arg2.data = OPS_consts_h + consts_bytes;
  arg2.data_d = OPS_consts_d + consts_bytes;
  for (int d=0; d<15; d++) ((int *)arg2.data)[d] = arg2h[d];
  consts_bytes += ROUND_UP(15*sizeof(int));
  mvConstArraysToDevice(consts_bytes);
  int dat0 = args[0].dat->size;
  int dat1 = args[1].dat->size;

  char *p_a[3];

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


  ops_H_D_exchanges_cuda(args, 3);


  //call kernel wrapper function, passing in pointers to data
  ops_update_halo_kernel2_yvel_plus_4_b<<<grid, block >>> (  (double *)p_a[0], (double *)p_a[1],
           (int *)arg2.data_d,x_size, y_size);

  if (OPS_diags>1) cutilSafeCall(cudaDeviceSynchronize());
  ops_set_dirtybit_cuda(args, 3);

  //Update kernel record
  ops_timers_core(&c2,&t2);
  OPS_kernels[58].count++;
  OPS_kernels[58].time += t2-t1;
  OPS_kernels[58].transfer += ops_compute_transfer(dim, range, &arg0);
  OPS_kernels[58].transfer += ops_compute_transfer(dim, range, &arg1);
}
