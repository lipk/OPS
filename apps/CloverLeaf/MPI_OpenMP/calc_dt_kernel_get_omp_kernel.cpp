//
// auto-generated by ops.py on 2014-03-03 11:38
//

#ifdef _OPENMP
#include <omp.h>
#endif
//user function
#include "calc_dt_kernel.h"

// host stub function
void ops_par_loop_calc_dt_kernel_get(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3) {

  int  offs[4][2];
  ops_arg args[4] = { arg0, arg1, arg2, arg3};


  sub_block_list sb = OPS_sub_block_list[block->index];
  //compute localy allocated range for the sub-block
  int ndim = sb->ndim;
  int start_add[ndim*4];
  int end_add[ndim*4];

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

  for ( int i=0; i<4; i++ ){
    for ( int n=0; n<ndim; n++ ){
      start_add[i*ndim+n] = s[n];
      end_add[i*ndim+n]   = e[n];
    }
  }

  #ifdef OPS_DEBUG
  ops_register_args(args, "calc_dt_kernel_get");
  #endif

  offs[0][0] = args[0].stencil->stride[0]*1;  //unit step in x dimension
  for ( int n=1; n<ndim; n++ ){
    offs[0][n] = off2(ndim, n, &start_add[0*ndim],
    &end_add[0*ndim],args[0].dat->block_size, args[0].stencil->stride);
  }
  offs[1][0] = args[1].stencil->stride[0]*1;  //unit step in x dimension
  for ( int n=1; n<ndim; n++ ){
    offs[1][n] = off2(ndim, n, &start_add[1*ndim],
    &end_add[1*ndim],args[1].dat->block_size, args[1].stencil->stride);
  }


  //Halo Exchanges
  ops_exchange_halo(&args[0],2);
  ops_exchange_halo(&args[1],2);

  int off0_1 = offs[0][0];
  int off0_2 = offs[0][1];
  int dat0 = args[0].dat->size;
  int off1_1 = offs[1][0];
  int off1_2 = offs[1][1];
  int dat1 = args[1].dat->size;

  double*arg2h = (double *)arg2.data;
  double*arg3h = (double *)arg3.data;

  #ifdef _OPENMP
  int nthreads = omp_get_max_threads( );
  #else
  int nthreads = 1;
  #endif
  //allocate and initialise arrays for global reduction
  //assumes a max of 64 threads with a cacche line size of 64 bytes
  double arg_gbl2[1 * 64 * 64];
  double arg_gbl3[1 * 64 * 64];
  for ( int thr=0; thr<nthreads; thr++ ){
  }
  xdim0 = args[0].dat->block_size[0];
  xdim1 = args[1].dat->block_size[0];


  int y_size = e[1]-s[1];


  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(30,"calc_dt_kernel_get");
  ops_timers_core(&c1,&t1);

  #pragma omp parallel for
  for ( int thr=0; thr<nthreads; thr++ ){

    char *p_a[4];

    int start = s[1];// + ((y_size-1)/nthreads+1)*thr;
    int finish = e[1];//s[1] + MIN(((y_size-1)/nthreads+1)*(thr+1),y_size);

    //set up initial pointers and exchange halos if nessasary
    p_a[0] = (char *)args[0].data
    + address2(ndim, args[0].dat->size, &start_add[0*ndim],
    args[0].dat->block_size, args[0].stencil->stride, args[0].dat->offset);

    //set up initial pointers and exchange halos if nessasary
    p_a[1] = (char *)args[1].data
    + address2(ndim, args[1].dat->size, &start_add[1*ndim],
    args[1].dat->block_size, args[1].stencil->stride, args[1].dat->offset);

    p_a[2] = (char *)args[2].data;

    p_a[3] = (char *)args[3].data;


    for ( int n_y=start; n_y<finish; n_y++ ){
      for ( int n_x=s[0]; n_x<s[0]+(e[0]-s[0])/SIMD_VEC; n_x++ ){
          //call kernel function, passing in pointers to data -vectorised
          for ( int i=0; i<SIMD_VEC; i++ ){
            calc_dt_kernel_get(  (double *)p_a[0]+ i*1, (double *)p_a[1]+ i*0, &arg_gbl2[64*thr],
           &arg_gbl3[64*thr] );

          }

          //shift pointers to data x direction
          p_a[0]= p_a[0] + (dat0 * off0_1)*SIMD_VEC;
          p_a[1]= p_a[1] + (dat1 * off1_1)*SIMD_VEC;
        }

        for ( int n_x=s[0]+((e[0]-s[0])/SIMD_VEC)*SIMD_VEC; n_x<e[0]; n_x++ ){
            //call kernel function, passing in pointers to data - remainder
            calc_dt_kernel_get(  (double *)p_a[0], (double *)p_a[1], &arg_gbl2[64*thr],
           &arg_gbl3[64*thr] );


            //shift pointers to data x direction
            p_a[0]= p_a[0] + (dat0 * off0_1);
            p_a[1]= p_a[1] + (dat1 * off1_1);
          }

          //shift pointers to data y direction
          p_a[0]= p_a[0] + (dat0 * off0_2);
          p_a[1]= p_a[1] + (dat1 * off1_2);
        }
      }

      // combine reduction data
      for ( int thr=0; thr<nthreads; thr++ ){
        for ( int d=0; d<1; d++ ){
          if(arg_gbl2[64*thr] != 0.0) arg2h[0] += arg_gbl2[64*thr];
        }
        for ( int d=0; d<1; d++ ){
          if(arg_gbl3[64*thr] != 0.0) arg3h[0] += arg_gbl3[64*thr];
        }
      }
      ops_mpi_reduce(&arg2,(double *)arg2h);
      ops_mpi_reduce(&arg3,(double *)arg3h);

      //Update kernel record
      ops_timers_core(&c2,&t2);
      OPS_kernels[30].count++;
      OPS_kernels[30].time += t2-t1;
      OPS_kernels[30].transfer += ops_compute_transfer(dim, range, &arg0);
      OPS_kernels[30].transfer += ops_compute_transfer(dim, range, &arg1);
    }
