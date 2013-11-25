//
// auto-generated by ops.py on 2013-11-25 14:14
//

__constant__ int xdim0_reset_field_kernel2;
__constant__ int xdim1_reset_field_kernel2;
__constant__ int xdim2_reset_field_kernel2;
__constant__ int xdim3_reset_field_kernel2;

#define OPS_ACC0(x,y) (x+xdim0_reset_field_kernel2*(y))
#define OPS_ACC1(x,y) (x+xdim1_reset_field_kernel2*(y))
#define OPS_ACC2(x,y) (x+xdim2_reset_field_kernel2*(y))
#define OPS_ACC3(x,y) (x+xdim3_reset_field_kernel2*(y))

//user function
__device__

inline void reset_field_kernel2( double *xvel0, const double *xvel1,
                        double *yvel0, const double *yvel1) {

  xvel0[OPS_ACC0(0,0)]  = xvel1[OPS_ACC1(0,0)] ;
  yvel0[OPS_ACC2(0,0)]  = yvel1[OPS_ACC3(0,0)] ;

}



#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3


__global__ void ops_reset_field_kernel2(
double* __restrict arg0,
const double* __restrict arg1,
double* __restrict arg2,
const double* __restrict arg3,
int size0,
int size1 ){


  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1 + idx_y * 1 * xdim0_reset_field_kernel2;
  arg1 += idx_x * 1 + idx_y * 1 * xdim1_reset_field_kernel2;
  arg2 += idx_x * 1 + idx_y * 1 * xdim2_reset_field_kernel2;
  arg3 += idx_x * 1 + idx_y * 1 * xdim3_reset_field_kernel2;

  if (idx_x < size0 && idx_y < size1) {
    reset_field_kernel2(arg0, arg1, arg2, arg3);
  }

}

// host stub function
void ops_par_loop_reset_field_kernel2(char const *name, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3) {

  ops_arg args[4] = { arg0, arg1, arg2, arg3};


  int x_size = range[1]-range[0];
  int y_size = range[3]-range[2];

  int xdim0 = args[0].dat->block_size[0];
  int xdim1 = args[1].dat->block_size[0];
  int xdim2 = args[2].dat->block_size[0];
  int xdim3 = args[3].dat->block_size[0];

  ops_timing_realloc(76);
  if (OPS_kernels[76].count == 0) {
    cudaMemcpyToSymbol( xdim0_reset_field_kernel2, &xdim0, sizeof(int) );
    cudaMemcpyToSymbol( xdim1_reset_field_kernel2, &xdim1, sizeof(int) );
    cudaMemcpyToSymbol( xdim2_reset_field_kernel2, &xdim2, sizeof(int) );
    cudaMemcpyToSymbol( xdim3_reset_field_kernel2, &xdim3, sizeof(int) );
  }



  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, (y_size-1)/OPS_block_size_y + 1, 1);
  dim3 block(OPS_block_size_x,OPS_block_size_y,1);




  char *p_a[4];


  //set up initial pointers
  p_a[0] = &args[0].data_d[
  + args[0].dat->size * args[0].dat->block_size[0] * ( range[2] * 1 - args[0].dat->offset[1] )
  + args[0].dat->size * ( range[0] * 1 - args[0].dat->offset[0] ) ];

  p_a[1] = &args[1].data_d[
  + args[1].dat->size * args[1].dat->block_size[0] * ( range[2] * 1 - args[1].dat->offset[1] )
  + args[1].dat->size * ( range[0] * 1 - args[1].dat->offset[0] ) ];

  p_a[2] = &args[2].data_d[
  + args[2].dat->size * args[2].dat->block_size[0] * ( range[2] * 1 - args[2].dat->offset[1] )
  + args[2].dat->size * ( range[0] * 1 - args[2].dat->offset[0] ) ];

  p_a[3] = &args[3].data_d[
  + args[3].dat->size * args[3].dat->block_size[0] * ( range[2] * 1 - args[3].dat->offset[1] )
  + args[3].dat->size * ( range[0] * 1 - args[3].dat->offset[0] ) ];


  ops_halo_exchanges_cuda(args, 4);


  //call kernel wrapper function, passing in pointers to data
  ops_reset_field_kernel2<<<grid, block >>> (  (double *)p_a[0], (double *)p_a[1],
           (double *)p_a[2], (double *)p_a[3],x_size, y_size);

  ops_set_dirtybit_cuda(args, 4);
  OPS_kernels[76].count++;
}
