//
// auto-generated by ops.py on 2014-03-17 15:34
//

__constant__ int xdim0_calc_dt_kernel_min;

#define OPS_ACC0(x,y) (x+xdim0_calc_dt_kernel_min*(y))

//user function
__device__

void calc_dt_kernel_min(const double* dt_min ,
                    double* dt_min_val) {
  *dt_min_val = MIN(*dt_min_val, dt_min[OPS_ACC0(0,0)]);

}



#undef OPS_ACC0


__global__ void ops_calc_dt_kernel_min(
const double* __restrict arg0,
double* __restrict arg1,
int size0,
int size1 ){

  double arg1_l[1];
  for (int d=0; d<1; d++) arg1_l[d] = INFINITY_double;

  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1 + idx_y * 1 * xdim0_calc_dt_kernel_min;

  if (idx_x < size0 && idx_y < size1) {
    calc_dt_kernel_min(arg0, arg1_l);
  }
  for (int d=0; d<1; d++)
    ops_reduction<OPS_MIN>(&arg1[d+blockIdx.x + blockIdx.y*gridDim.x],arg1_l[d]);

}

// host stub function
void ops_par_loop_calc_dt_kernel_min(char const *name, ops_block Block, int dim, int* range,
 ops_arg arg0, ops_arg arg1) {

  ops_arg args[2] = { arg0, arg1};

  sub_block_list sb = OPS_sub_block_list[Block->index];
  //compute localy allocated range for the sub-block
  int ndim = sb->ndim;
  int start_add[ndim*2];

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

  for ( int i=0; i<2; i++ ){
    for ( int n=0; n<ndim; n++ ){
      start_add[i*ndim+n] = s[n];
    }
  }


  int x_size = e[0]-s[0];
  int y_size = e[1]-s[1];

  int xdim0 = args[0].dat->block_size[0]*args[0].dat->dim;


  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(29,"calc_dt_kernel_min");
  ops_timers_core(&c1,&t1);

  if (OPS_kernels[29].count == 0) {
    cudaMemcpyToSymbol( xdim0_calc_dt_kernel_min, &xdim0, sizeof(int) );
  }


  double *arg1h = (double *)arg1.data;

  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, (y_size-1)/OPS_block_size_y + 1, 1);
  dim3 block(OPS_block_size_x,OPS_block_size_y,1);

  int nblocks = ((x_size-1)/OPS_block_size_x+ 1)*((y_size-1)/OPS_block_size_y + 1);
  int maxblocks = nblocks;
  int reduct_bytes = 0;
  int reduct_size = 0;

  reduct_bytes += ROUND_UP(maxblocks*1*sizeof(double));
  reduct_size = MAX(reduct_size,sizeof(double)*1);

  reallocReductArrays(reduct_bytes);
  reduct_bytes = 0;

  arg1.data = OPS_reduct_h + reduct_bytes;
  arg1.data_d = OPS_reduct_d + reduct_bytes;
  for (int b=0; b<maxblocks; b++)
  for (int d=0; d<1; d++) ((double *)arg1.data)[d+b*1] = INFINITY_double;
  reduct_bytes += ROUND_UP(maxblocks*1*sizeof(double));


  mvReductArraysToDevice(reduct_bytes);
  int dat0 = args[0].dat->size;

  char *p_a[2];

  //set up initial pointers
  int base0 = dat0 * 1 * 
  (start_add[ndim+0] * args[0].stencil->stride[0] - args[0].dat->offset[0]);
  base0 = base0  + dat0 * args[0].dat->block_size[0] * 
  (start_add[ndim+1] * args[0].stencil->stride[1] - args[0].dat->offset[1]);
  p_a[0] = (char *)args[0].data_d + base0;


  ops_H_D_exchanges_cuda(args, 2);

  int nshared = 0;
  int nthread = OPS_block_size_x*OPS_block_size_y;

  nshared = MAX(nshared,sizeof(double)*1);

  nshared = MAX(nshared*nthread,reduct_size*nthread);

  //call kernel wrapper function, passing in pointers to data
  ops_calc_dt_kernel_min<<<grid, block, nshared >>> (  (double *)p_a[0], (double *)arg1.data_d,x_size, y_size);

  mvReductArraysToHost(reduct_bytes);
  for ( int b=0; b<maxblocks; b++ ){
    for ( int d=0; d<1; d++ ){
      arg1h[d] = MIN(arg1h[d],((double *)arg1.data)[d+b*1]);
    }
  }
  arg1.data = (char *)arg1h;

  if (OPS_diags>1) cutilSafeCall(cudaDeviceSynchronize());
  ops_set_dirtybit_cuda(args, 2);

  //Update kernel record
  ops_timers_core(&c2,&t2);
  OPS_kernels[29].count++;
  OPS_kernels[29].time += t2-t1;
  OPS_kernels[29].transfer += ops_compute_transfer(dim, range, &arg0);
}
