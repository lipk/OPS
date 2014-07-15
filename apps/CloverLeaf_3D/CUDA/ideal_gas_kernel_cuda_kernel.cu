//
// auto-generated by ops.py on 2014-07-15 13:58
//

__constant__ int xdim0_ideal_gas_kernel;
__constant__ int ydim0_ideal_gas_kernel;
__constant__ int xdim1_ideal_gas_kernel;
__constant__ int ydim1_ideal_gas_kernel;
__constant__ int xdim2_ideal_gas_kernel;
__constant__ int ydim2_ideal_gas_kernel;
__constant__ int xdim3_ideal_gas_kernel;
__constant__ int ydim3_ideal_gas_kernel;

#define OPS_ACC0(x,y,z) (x+xdim0_ideal_gas_kernel*(y)+xdim0_ideal_gas_kernel*ydim0_ideal_gas_kernel*(z))
#define OPS_ACC1(x,y,z) (x+xdim1_ideal_gas_kernel*(y)+xdim1_ideal_gas_kernel*ydim1_ideal_gas_kernel*(z))
#define OPS_ACC2(x,y,z) (x+xdim2_ideal_gas_kernel*(y)+xdim2_ideal_gas_kernel*ydim2_ideal_gas_kernel*(z))
#define OPS_ACC3(x,y,z) (x+xdim3_ideal_gas_kernel*(y)+xdim3_ideal_gas_kernel*ydim3_ideal_gas_kernel*(z))

//user function
__device__

void ideal_gas_kernel( const double *density, const double *energy,
                     double *pressure, double *soundspeed) {

  double sound_speed_squared, v, pressurebyenergy, pressurebyvolume;

  v = 1.0 / density[OPS_ACC0(0,0,0)];
  pressure[OPS_ACC2(0,0,0)] = (1.4 - 1.0) * density[OPS_ACC0(0,0,0)] * energy[OPS_ACC1(0,0,0)];

  pressurebyenergy = (1.4 - 1.0) * density[OPS_ACC0(0,0,0)];
  pressurebyvolume = -1.0*density[OPS_ACC0(0,0,0)] * pressure[OPS_ACC2(0,0,0)];
  sound_speed_squared = v*v*(pressure[OPS_ACC2(0,0,0)] * pressurebyenergy-pressurebyvolume);
  soundspeed[OPS_ACC3(0,0,0)] = sqrt(sound_speed_squared);
}



#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3


__global__ void ops_ideal_gas_kernel(
const double* __restrict arg0,
const double* __restrict arg1,
double* __restrict arg2,
double* __restrict arg3,
int size0,
int size1,
int size2 ){


  int idx_z = blockDim.z * blockIdx.z + threadIdx.z;
  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1 + idx_y * 1 * xdim0_ideal_gas_kernel + idx_z * 1 * xdim0_ideal_gas_kernel * ydim0_ideal_gas_kernel;
  arg1 += idx_x * 1 + idx_y * 1 * xdim1_ideal_gas_kernel + idx_z * 1 * xdim1_ideal_gas_kernel * ydim1_ideal_gas_kernel;
  arg2 += idx_x * 1 + idx_y * 1 * xdim2_ideal_gas_kernel + idx_z * 1 * xdim2_ideal_gas_kernel * ydim2_ideal_gas_kernel;
  arg3 += idx_x * 1 + idx_y * 1 * xdim3_ideal_gas_kernel + idx_z * 1 * xdim3_ideal_gas_kernel * ydim3_ideal_gas_kernel;

  if (idx_x < size0 && idx_y < size1 && idx_z < size2) {
    ideal_gas_kernel(arg0, arg1, arg2, arg3);
  }

}

// host stub function
void ops_par_loop_ideal_gas_kernel(char const *name, ops_block Block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3) {

  ops_arg args[4] = { arg0, arg1, arg2, arg3};

  sub_block_list sb = OPS_sub_block_list[Block->index];
  //compute localy allocated range for the sub-block
  int start_add[3];
  int end_add[3];
  for ( int n=0; n<3; n++ ){
    start_add[n] = sb->istart[n];end_add[n] = sb->iend[n]+1;
    if (start_add[n] >= range[2*n]) {
      start_add[n] = 0;
    }
    else {
      start_add[n] = range[2*n] - start_add[n];
    }
    if (end_add[n] >= range[2*n+1]) {
      end_add[n] = range[2*n+1] - sb->istart[n];
    }
    else {
      end_add[n] = sb->sizes[n];
    }
  }


  int x_size = MAX(0,end_add[0]-start_add[0]);
  int y_size = MAX(0,end_add[1]-start_add[1]);
  int z_size = MAX(0,end_add[2]-start_add[2]);

  int xdim0 = args[0].dat->block_size[0]*args[0].dat->dim;
  int ydim0 = args[0].dat->block_size[1];
  int xdim1 = args[1].dat->block_size[0]*args[1].dat->dim;
  int ydim1 = args[1].dat->block_size[1];
  int xdim2 = args[2].dat->block_size[0]*args[2].dat->dim;
  int ydim2 = args[2].dat->block_size[1];
  int xdim3 = args[3].dat->block_size[0]*args[3].dat->dim;
  int ydim3 = args[3].dat->block_size[1];


  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(3,"ideal_gas_kernel");
  ops_timers_core(&c2,&t2);

  if (OPS_kernels[3].count == 0) {
    cudaMemcpyToSymbol( xdim0_ideal_gas_kernel, &xdim0, sizeof(int) );
    cudaMemcpyToSymbol( ydim0_ideal_gas_kernel, &ydim0, sizeof(int) );
    cudaMemcpyToSymbol( xdim1_ideal_gas_kernel, &xdim1, sizeof(int) );
    cudaMemcpyToSymbol( ydim1_ideal_gas_kernel, &ydim1, sizeof(int) );
    cudaMemcpyToSymbol( xdim2_ideal_gas_kernel, &xdim2, sizeof(int) );
    cudaMemcpyToSymbol( ydim2_ideal_gas_kernel, &ydim2, sizeof(int) );
    cudaMemcpyToSymbol( xdim3_ideal_gas_kernel, &xdim3, sizeof(int) );
    cudaMemcpyToSymbol( ydim3_ideal_gas_kernel, &ydim3, sizeof(int) );
  }



  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, (y_size-1)/OPS_block_size_y + 1, z_size);
  dim3 block(OPS_block_size_x,OPS_block_size_y,1);



  int dat0 = args[0].dat->size;
  int dat1 = args[1].dat->size;
  int dat2 = args[2].dat->size;
  int dat3 = args[3].dat->size;

  char *p_a[4];

  //set up initial pointers
  int base0 = dat0 * 1 * 
  (start_add[0] * args[0].stencil->stride[0] - args[0].dat->offset[0]);
  base0 = base0+ dat0 *
    args[0].dat->block_size[0] *
    (start_add[1] * args[0].stencil->stride[1] - args[0].dat->offset[1]);
  base0 = base0+ dat0 *
    args[0].dat->block_size[0] *
    args[0].dat->block_size[1] *
    (start_add[2] * args[0].stencil->stride[2] - args[0].dat->offset[2]);
  p_a[0] = (char *)args[0].data_d + base0;

  int base1 = dat1 * 1 * 
  (start_add[0] * args[1].stencil->stride[0] - args[1].dat->offset[0]);
  base1 = base1+ dat1 *
    args[1].dat->block_size[0] *
    (start_add[1] * args[1].stencil->stride[1] - args[1].dat->offset[1]);
  base1 = base1+ dat1 *
    args[1].dat->block_size[0] *
    args[1].dat->block_size[1] *
    (start_add[2] * args[1].stencil->stride[2] - args[1].dat->offset[2]);
  p_a[1] = (char *)args[1].data_d + base1;

  int base2 = dat2 * 1 * 
  (start_add[0] * args[2].stencil->stride[0] - args[2].dat->offset[0]);
  base2 = base2+ dat2 *
    args[2].dat->block_size[0] *
    (start_add[1] * args[2].stencil->stride[1] - args[2].dat->offset[1]);
  base2 = base2+ dat2 *
    args[2].dat->block_size[0] *
    args[2].dat->block_size[1] *
    (start_add[2] * args[2].stencil->stride[2] - args[2].dat->offset[2]);
  p_a[2] = (char *)args[2].data_d + base2;

  int base3 = dat3 * 1 * 
  (start_add[0] * args[3].stencil->stride[0] - args[3].dat->offset[0]);
  base3 = base3+ dat3 *
    args[3].dat->block_size[0] *
    (start_add[1] * args[3].stencil->stride[1] - args[3].dat->offset[1]);
  base3 = base3+ dat3 *
    args[3].dat->block_size[0] *
    args[3].dat->block_size[1] *
    (start_add[2] * args[3].stencil->stride[2] - args[3].dat->offset[2]);
  p_a[3] = (char *)args[3].data_d + base3;


  ops_H_D_exchanges_cuda(args, 4);
  ops_halo_exchanges(args,4,range);

  ops_timers_core(&c1,&t1);
  OPS_kernels[3].mpi_time += t1-t2;


  //call kernel wrapper function, passing in pointers to data
  ops_ideal_gas_kernel<<<grid, block >>> (  (double *)p_a[0], (double *)p_a[1],
           (double *)p_a[2], (double *)p_a[3],x_size, y_size, z_size);

  if (OPS_diags>1) {
    cutilSafeCall(cudaDeviceSynchronize());
  }
  ops_timers_core(&c2,&t2);
  OPS_kernels[3].time += t2-t1;
  ops_set_dirtybit_cuda(args, 4);
  ops_set_halo_dirtybit3(&args[2],range);
  ops_set_halo_dirtybit3(&args[3],range);

  //Update kernel record
  OPS_kernels[3].count++;
  OPS_kernels[3].transfer += ops_compute_transfer(dim, range, &arg0);
  OPS_kernels[3].transfer += ops_compute_transfer(dim, range, &arg1);
  OPS_kernels[3].transfer += ops_compute_transfer(dim, range, &arg2);
  OPS_kernels[3].transfer += ops_compute_transfer(dim, range, &arg3);
}
