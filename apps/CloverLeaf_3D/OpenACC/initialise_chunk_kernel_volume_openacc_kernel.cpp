//
// auto-generated by ops.py on 2014-07-15 13:58
//

#include "./OpenACC/clover_leaf_common.h"

#define OPS_GPU

extern int xdim0_initialise_chunk_kernel_volume;
extern int ydim0_initialise_chunk_kernel_volume;
extern int xdim1_initialise_chunk_kernel_volume;
extern int ydim1_initialise_chunk_kernel_volume;
extern int xdim2_initialise_chunk_kernel_volume;
extern int ydim2_initialise_chunk_kernel_volume;
extern int xdim3_initialise_chunk_kernel_volume;
extern int ydim3_initialise_chunk_kernel_volume;
extern int xdim4_initialise_chunk_kernel_volume;
extern int ydim4_initialise_chunk_kernel_volume;
extern int xdim5_initialise_chunk_kernel_volume;
extern int ydim5_initialise_chunk_kernel_volume;
extern int xdim6_initialise_chunk_kernel_volume;
extern int ydim6_initialise_chunk_kernel_volume;

#ifdef __cplusplus
extern "C" {
#endif
void initialise_chunk_kernel_volume_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  double *p_a3,
  double *p_a4,
  double *p_a5,
  double *p_a6,
  int x_size, int y_size, int z_size);

#ifdef __cplusplus
}
#endif

// host stub function
void ops_par_loop_initialise_chunk_kernel_volume(char const *name, ops_block Block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3, ops_arg arg4, ops_arg arg5, ops_arg arg6) {

  ops_arg args[7] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6};

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


  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(52,"initialise_chunk_kernel_volume");
  ops_timers_core(&c2,&t2);

  if (OPS_kernels[52].count == 0) {
    xdim0_initialise_chunk_kernel_volume = args[0].dat->block_size[0]*args[0].dat->dim;
    ydim0_initialise_chunk_kernel_volume = args[0].dat->block_size[1];
    xdim1_initialise_chunk_kernel_volume = args[1].dat->block_size[0]*args[1].dat->dim;
    ydim1_initialise_chunk_kernel_volume = args[1].dat->block_size[1];
    xdim2_initialise_chunk_kernel_volume = args[2].dat->block_size[0]*args[2].dat->dim;
    ydim2_initialise_chunk_kernel_volume = args[2].dat->block_size[1];
    xdim3_initialise_chunk_kernel_volume = args[3].dat->block_size[0]*args[3].dat->dim;
    ydim3_initialise_chunk_kernel_volume = args[3].dat->block_size[1];
    xdim4_initialise_chunk_kernel_volume = args[4].dat->block_size[0]*args[4].dat->dim;
    ydim4_initialise_chunk_kernel_volume = args[4].dat->block_size[1];
    xdim5_initialise_chunk_kernel_volume = args[5].dat->block_size[0]*args[5].dat->dim;
    ydim5_initialise_chunk_kernel_volume = args[5].dat->block_size[1];
    xdim6_initialise_chunk_kernel_volume = args[6].dat->block_size[0]*args[6].dat->dim;
    ydim6_initialise_chunk_kernel_volume = args[6].dat->block_size[1];
  }

  int dat0 = args[0].dat->size;
  int dat1 = args[1].dat->size;
  int dat2 = args[2].dat->size;
  int dat3 = args[3].dat->size;
  int dat4 = args[4].dat->size;
  int dat5 = args[5].dat->size;
  int dat6 = args[6].dat->size;


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
  #ifdef OPS_GPU
  double *p_a0 = (double *)((char *)args[0].data_d + base0);
  #else
  double *p_a0 = (double *)((char *)args[0].data + base0);
  #endif

  int base1 = dat1 * 1 * 
    (start_add[0] * args[1].stencil->stride[0] - args[1].dat->offset[0]);
  base1 = base1+ dat1 *
    args[1].dat->block_size[0] *
    (start_add[1] * args[1].stencil->stride[1] - args[1].dat->offset[1]);
  base1 = base1+ dat1 *
    args[1].dat->block_size[0] *
    args[1].dat->block_size[1] *
    (start_add[2] * args[1].stencil->stride[2] - args[1].dat->offset[2]);
  #ifdef OPS_GPU
  double *p_a1 = (double *)((char *)args[1].data_d + base1);
  #else
  double *p_a1 = (double *)((char *)args[1].data + base1);
  #endif

  int base2 = dat2 * 1 * 
    (start_add[0] * args[2].stencil->stride[0] - args[2].dat->offset[0]);
  base2 = base2+ dat2 *
    args[2].dat->block_size[0] *
    (start_add[1] * args[2].stencil->stride[1] - args[2].dat->offset[1]);
  base2 = base2+ dat2 *
    args[2].dat->block_size[0] *
    args[2].dat->block_size[1] *
    (start_add[2] * args[2].stencil->stride[2] - args[2].dat->offset[2]);
  #ifdef OPS_GPU
  double *p_a2 = (double *)((char *)args[2].data_d + base2);
  #else
  double *p_a2 = (double *)((char *)args[2].data + base2);
  #endif

  int base3 = dat3 * 1 * 
    (start_add[0] * args[3].stencil->stride[0] - args[3].dat->offset[0]);
  base3 = base3+ dat3 *
    args[3].dat->block_size[0] *
    (start_add[1] * args[3].stencil->stride[1] - args[3].dat->offset[1]);
  base3 = base3+ dat3 *
    args[3].dat->block_size[0] *
    args[3].dat->block_size[1] *
    (start_add[2] * args[3].stencil->stride[2] - args[3].dat->offset[2]);
  #ifdef OPS_GPU
  double *p_a3 = (double *)((char *)args[3].data_d + base3);
  #else
  double *p_a3 = (double *)((char *)args[3].data + base3);
  #endif

  int base4 = dat4 * 1 * 
    (start_add[0] * args[4].stencil->stride[0] - args[4].dat->offset[0]);
  base4 = base4+ dat4 *
    args[4].dat->block_size[0] *
    (start_add[1] * args[4].stencil->stride[1] - args[4].dat->offset[1]);
  base4 = base4+ dat4 *
    args[4].dat->block_size[0] *
    args[4].dat->block_size[1] *
    (start_add[2] * args[4].stencil->stride[2] - args[4].dat->offset[2]);
  #ifdef OPS_GPU
  double *p_a4 = (double *)((char *)args[4].data_d + base4);
  #else
  double *p_a4 = (double *)((char *)args[4].data + base4);
  #endif

  int base5 = dat5 * 1 * 
    (start_add[0] * args[5].stencil->stride[0] - args[5].dat->offset[0]);
  base5 = base5+ dat5 *
    args[5].dat->block_size[0] *
    (start_add[1] * args[5].stencil->stride[1] - args[5].dat->offset[1]);
  base5 = base5+ dat5 *
    args[5].dat->block_size[0] *
    args[5].dat->block_size[1] *
    (start_add[2] * args[5].stencil->stride[2] - args[5].dat->offset[2]);
  #ifdef OPS_GPU
  double *p_a5 = (double *)((char *)args[5].data_d + base5);
  #else
  double *p_a5 = (double *)((char *)args[5].data + base5);
  #endif

  int base6 = dat6 * 1 * 
    (start_add[0] * args[6].stencil->stride[0] - args[6].dat->offset[0]);
  base6 = base6+ dat6 *
    args[6].dat->block_size[0] *
    (start_add[1] * args[6].stencil->stride[1] - args[6].dat->offset[1]);
  base6 = base6+ dat6 *
    args[6].dat->block_size[0] *
    args[6].dat->block_size[1] *
    (start_add[2] * args[6].stencil->stride[2] - args[6].dat->offset[2]);
  #ifdef OPS_GPU
  double *p_a6 = (double *)((char *)args[6].data_d + base6);
  #else
  double *p_a6 = (double *)((char *)args[6].data + base6);
  #endif


  #ifdef OPS_GPU
  ops_H_D_exchanges_cuda(args, 7);
  #else
  ops_H_D_exchanges(args, 7);
  #endif
  ops_halo_exchanges(args,7,range);

  ops_timers_core(&c1,&t1);
  OPS_kernels[52].mpi_time += t1-t2;

  initialise_chunk_kernel_volume_c_wrapper(
    p_a0,
    p_a1,
    p_a2,
    p_a3,
    p_a4,
    p_a5,
    p_a6,
    x_size, y_size, z_size);

  ops_timers_core(&c2,&t2);
  OPS_kernels[52].time += t2-t1;
  #ifdef OPS_GPU
  ops_set_dirtybit_cuda(args, 7);
  #else
  ops_set_dirtybit_host(args, 7);
  #endif
  ops_set_halo_dirtybit3(&args[0],range);
  ops_set_halo_dirtybit3(&args[2],range);
  ops_set_halo_dirtybit3(&args[4],range);
  ops_set_halo_dirtybit3(&args[6],range);

  //Update kernel record
  OPS_kernels[52].count++;
  OPS_kernels[52].transfer += ops_compute_transfer(dim, range, &arg0);
  OPS_kernels[52].transfer += ops_compute_transfer(dim, range, &arg1);
  OPS_kernels[52].transfer += ops_compute_transfer(dim, range, &arg2);
  OPS_kernels[52].transfer += ops_compute_transfer(dim, range, &arg3);
  OPS_kernels[52].transfer += ops_compute_transfer(dim, range, &arg4);
  OPS_kernels[52].transfer += ops_compute_transfer(dim, range, &arg5);
  OPS_kernels[52].transfer += ops_compute_transfer(dim, range, &arg6);
}
