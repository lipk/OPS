//
// auto-generated by ops.py on 2014-03-03 11:38
//

#ifdef _OPENMP
#include <omp.h>
#endif
//user function
#include "initialise_chunk_kernel.h"

// host stub function
void ops_par_loop_initialise_chunk_kernel_y(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2) {

  int  offs[3][2];
  ops_arg args[3] = { arg0, arg1, arg2};


  sub_block_list sb = OPS_sub_block_list[block->index];
  //compute localy allocated range for the sub-block
  int ndim = sb->ndim;
  int start_add[ndim*3];
  int end_add[ndim*3];

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
      end_add[i*ndim+n]   = e[n];
    }
  }

  #ifdef OPS_DEBUG
  ops_register_args(args, "initialise_chunk_kernel_y");
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
  offs[2][0] = args[2].stencil->stride[0]*1;  //unit step in x dimension
  for ( int n=1; n<ndim; n++ ){
    offs[2][n] = off2(ndim, n, &start_add[2*ndim],
    &end_add[2*ndim],args[2].dat->block_size, args[2].stencil->stride);
  }


  //Halo Exchanges
  ops_exchange_halo(&args[1],2);

  int off0_1 = offs[0][0];
  int off0_2 = offs[0][1];
  int dat0 = args[0].dat->size;
  int off1_1 = offs[1][0];
  int off1_2 = offs[1][1];
  int dat1 = args[1].dat->size;
  int off2_1 = offs[2][0];
  int off2_2 = offs[2][1];
  int dat2 = args[2].dat->size;


  #ifdef _OPENMP
  int nthreads = omp_get_max_threads( );
  #else
  int nthreads = 1;
  #endif
  xdim0 = args[0].dat->block_size[0];
  xdim1 = args[1].dat->block_size[0];
  xdim2 = args[2].dat->block_size[0];


  int y_size = e[1]-s[1];


  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(77,"initialise_chunk_kernel_y");
  ops_timers_core(&c1,&t1);

  #pragma omp parallel for
  for ( int thr=0; thr<nthreads; thr++ ){

    char *p_a[3];

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

    //set up initial pointers and exchange halos if nessasary
    p_a[2] = (char *)args[2].data
    + address2(ndim, args[2].dat->size, &start_add[2*ndim],
    args[2].dat->block_size, args[2].stencil->stride, args[2].dat->offset);


    for ( int n_y=start; n_y<finish; n_y++ ){
      for ( int n_x=s[0]; n_x<s[0]+(e[0]-s[0])/SIMD_VEC; n_x++ ){
          //call kernel function, passing in pointers to data -vectorised
          #pragma simd
          for ( int i=0; i<SIMD_VEC; i++ ){
            initialise_chunk_kernel_y(  (double *)p_a[0]+ i*0, (int *)p_a[1]+ i*0, (double *)p_a[2]+ i*0 );

          }

          //shift pointers to data x direction
          p_a[0]= p_a[0] + (dat0 * off0_1)*SIMD_VEC;
          p_a[1]= p_a[1] + (dat1 * off1_1)*SIMD_VEC;
          p_a[2]= p_a[2] + (dat2 * off2_1)*SIMD_VEC;
        }

        for ( int n_x=s[0]+((e[0]-s[0])/SIMD_VEC)*SIMD_VEC; n_x<e[0]; n_x++ ){
            //call kernel function, passing in pointers to data - remainder
            initialise_chunk_kernel_y(  (double *)p_a[0], (int *)p_a[1], (double *)p_a[2] );


            //shift pointers to data x direction
            p_a[0]= p_a[0] + (dat0 * off0_1);
            p_a[1]= p_a[1] + (dat1 * off1_1);
            p_a[2]= p_a[2] + (dat2 * off2_1);
          }

          //shift pointers to data y direction
          p_a[0]= p_a[0] + (dat0 * off0_2);
          p_a[1]= p_a[1] + (dat1 * off1_2);
          p_a[2]= p_a[2] + (dat2 * off2_2);
        }
      }
      ops_set_halo_dirtybit(&args[0]);
      ops_set_halo_dirtybit(&args[2]);

      //Update kernel record
      ops_timers_core(&c2,&t2);
      OPS_kernels[77].count++;
      OPS_kernels[77].time += t2-t1;
      OPS_kernels[77].transfer += ops_compute_transfer(dim, range, &arg0);
      OPS_kernels[77].transfer += ops_compute_transfer(dim, range, &arg1);
      OPS_kernels[77].transfer += ops_compute_transfer(dim, range, &arg2);
    }
