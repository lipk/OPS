//
// auto-generated by ops.py on 2014-07-15 13:58
//

#include "./OpenACC/clover_leaf_common.h"

#define OPS_GPU

extern int xdim0_advec_mom_kernel_z3;
extern int ydim0_advec_mom_kernel_z3;
extern int xdim1_advec_mom_kernel_z3;
extern int ydim1_advec_mom_kernel_z3;
extern int xdim2_advec_mom_kernel_z3;
extern int ydim2_advec_mom_kernel_z3;
extern int xdim3_advec_mom_kernel_z3;
extern int ydim3_advec_mom_kernel_z3;

#ifdef __cplusplus
extern "C" {
#endif
void advec_mom_kernel_z3_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  double *p_a3,
  int x_size, int y_size, int z_size);

#ifdef __cplusplus
}
#endif

// host stub function
void ops_par_loop_advec_mom_kernel_z3(char const *name, ops_block Block, int dim, int* range,
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


  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(24,"advec_mom_kernel_z3");
  ops_timers_core(&c2,&t2);

  if (OPS_kernels[24].count == 0) {
    xdim0_advec_mom_kernel_z3 = args[0].dat->block_size[0]*args[0].dat->dim;
    ydim0_advec_mom_kernel_z3 = args[0].dat->block_size[1];
    xdim1_advec_mom_kernel_z3 = args[1].dat->block_size[0]*args[1].dat->dim;
    ydim1_advec_mom_kernel_z3 = args[1].dat->block_size[1];
    xdim2_advec_mom_kernel_z3 = args[2].dat->block_size[0]*args[2].dat->dim;
    ydim2_advec_mom_kernel_z3 = args[2].dat->block_size[1];
    xdim3_advec_mom_kernel_z3 = args[3].dat->block_size[0]*args[3].dat->dim;
    ydim3_advec_mom_kernel_z3 = args[3].dat->block_size[1];
  }

  int dat0 = args[0].dat->size;
  int dat1 = args[1].dat->size;
  int dat2 = args[2].dat->size;
  int dat3 = args[3].dat->size;


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


  #ifdef OPS_GPU
  ops_H_D_exchanges_cuda(args, 4);
  #else
  ops_H_D_exchanges(args, 4);
  #endif
  ops_halo_exchanges(args,4,range);

  ops_timers_core(&c1,&t1);
  OPS_kernels[24].mpi_time += t1-t2;

  advec_mom_kernel_z3_c_wrapper(
    p_a0,
    p_a1,
    p_a2,
    p_a3,
    x_size, y_size, z_size);

  ops_timers_core(&c2,&t2);
  OPS_kernels[24].time += t2-t1;
  #ifdef OPS_GPU
  ops_set_dirtybit_cuda(args, 4);
  #else
  ops_set_dirtybit_host(args, 4);
  #endif
  ops_set_halo_dirtybit3(&args[0],range);
  ops_set_halo_dirtybit3(&args[1],range);

  //Update kernel record
  OPS_kernels[24].count++;
  OPS_kernels[24].transfer += ops_compute_transfer(dim, range, &arg0);
  OPS_kernels[24].transfer += ops_compute_transfer(dim, range, &arg1);
  OPS_kernels[24].transfer += ops_compute_transfer(dim, range, &arg2);
  OPS_kernels[24].transfer += ops_compute_transfer(dim, range, &arg3);
}
