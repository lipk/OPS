//
// auto-generated by ops.py
//
#define OPS_ACC0(x, y)                                                         \
  (n_x * 1 + n_y * xdim0_advec_cell_kernel3_ydir * 1 + x +                     \
   xdim0_advec_cell_kernel3_ydir * (y))
#define OPS_ACC1(x, y)                                                         \
  (n_x * 1 + n_y * xdim1_advec_cell_kernel3_ydir * 1 + x +                     \
   xdim1_advec_cell_kernel3_ydir * (y))
#define OPS_ACC2(x, y)                                                         \
  (n_x * 0 + n_y * xdim2_advec_cell_kernel3_ydir * 1 + x +                     \
   xdim2_advec_cell_kernel3_ydir * (y))
#define OPS_ACC3(x, y)                                                         \
  (n_x * 0 + n_y * xdim3_advec_cell_kernel3_ydir * 1 + x +                     \
   xdim3_advec_cell_kernel3_ydir * (y))
#define OPS_ACC4(x, y)                                                         \
  (n_x * 1 + n_y * xdim4_advec_cell_kernel3_ydir * 1 + x +                     \
   xdim4_advec_cell_kernel3_ydir * (y))
#define OPS_ACC5(x, y)                                                         \
  (n_x * 1 + n_y * xdim5_advec_cell_kernel3_ydir * 1 + x +                     \
   xdim5_advec_cell_kernel3_ydir * (y))
#define OPS_ACC6(x, y)                                                         \
  (n_x * 1 + n_y * xdim6_advec_cell_kernel3_ydir * 1 + x +                     \
   xdim6_advec_cell_kernel3_ydir * (y))
#define OPS_ACC7(x, y)                                                         \
  (n_x * 1 + n_y * xdim7_advec_cell_kernel3_ydir * 1 + x +                     \
   xdim7_advec_cell_kernel3_ydir * (y))

// user function

// host stub function
void ops_par_loop_advec_cell_kernel3_ydir_execute(ops_kernel_descriptor *desc) {
  ops_block block = desc->block;
  int dim = desc->dim;
  int *range = desc->range;
  ops_arg arg0 = desc->args[0];
  ops_arg arg1 = desc->args[1];
  ops_arg arg2 = desc->args[2];
  ops_arg arg3 = desc->args[3];
  ops_arg arg4 = desc->args[4];
  ops_arg arg5 = desc->args[5];
  ops_arg arg6 = desc->args[6];
  ops_arg arg7 = desc->args[7];

  // Timing
  double t1, t2, c1, c2;

  ops_arg args[8] = {arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7};

#ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args, 8, range, 13))
    return;
#endif

  if (OPS_diags > 1) {
    OPS_kernels[13].count++;
    ops_timers_core(&c2, &t2);
  }

  // compute locally allocated range for the sub-block
  int start[2];
  int end[2];

  for (int n = 0; n < 2; n++) {
    start[n] = range[2 * n];
    end[n] = range[2 * n + 1];
  }

#ifdef OPS_DEBUG
  ops_register_args(args, "advec_cell_kernel3_ydir");
#endif

  // set up initial pointers and exchange halos if necessary
  int base0 = args[0].dat->base_offset;
  const double *__restrict__ vol_flux_y = (double *)(args[0].data + base0);

  int base1 = args[1].dat->base_offset;
  const double *__restrict__ pre_vol = (double *)(args[1].data + base1);

  int base2 = args[2].dat->base_offset;
  const int *__restrict__ yy = (int *)(args[2].data + base2);

  int base3 = args[3].dat->base_offset;
  const double *__restrict__ vertexdy = (double *)(args[3].data + base3);

  int base4 = args[4].dat->base_offset;
  const double *__restrict__ density1 = (double *)(args[4].data + base4);

  int base5 = args[5].dat->base_offset;
  const double *__restrict__ energy1 = (double *)(args[5].data + base5);

  int base6 = args[6].dat->base_offset;
  double *__restrict__ mass_flux_y = (double *)(args[6].data + base6);

  int base7 = args[7].dat->base_offset;
  double *__restrict__ ener_flux = (double *)(args[7].data + base7);

  // initialize global variable with the dimension of dats
  int xdim0_advec_cell_kernel3_ydir = args[0].dat->size[0];
  int xdim1_advec_cell_kernel3_ydir = args[1].dat->size[0];
  int xdim2_advec_cell_kernel3_ydir = args[2].dat->size[0];
  int xdim3_advec_cell_kernel3_ydir = args[3].dat->size[0];
  int xdim4_advec_cell_kernel3_ydir = args[4].dat->size[0];
  int xdim5_advec_cell_kernel3_ydir = args[5].dat->size[0];
  int xdim6_advec_cell_kernel3_ydir = args[6].dat->size[0];
  int xdim7_advec_cell_kernel3_ydir = args[7].dat->size[0];

  if (OPS_diags > 1) {
    ops_timers_core(&c1, &t1);
    OPS_kernels[13].mpi_time += t1 - t2;
  }

#pragma omp parallel for
  for (int n_y = start[1]; n_y < end[1]; n_y++) {
#ifdef intel
#pragma loop_count(10000)
#pragma omp simd aligned(vol_flux_y, pre_vol, yy, vertexdy, density1, energy1, \
                         mass_flux_y, ener_flux)
#else
#pragma simd
#endif
    for (int n_x = start[0]; n_x < end[0]; n_x++) {

      double sigmat, sigmav, sigmam, sigma3, sigma4;
      double diffuw, diffdw, limiter;
      double one_by_six = 1.0 / 6.0;

      int y_max = field.y_max;

      int upwind, donor, downwind, dif;

      if (vol_flux_y[OPS_ACC0(0, 0)] > 0.0) {
        upwind = -2;
        donor = -1;
        downwind = 0;
        dif = donor;
      } else if (yy[OPS_ACC2(0, 1)] < y_max + 2 - 2) {
        upwind = 1;
        donor = 0;
        downwind = -1;
        dif = upwind;
      } else {
        upwind = 0;
        donor = 0;
        downwind = -1;
        dif = upwind;
      }

      sigmat = fabs(vol_flux_y[OPS_ACC0(0, 0)]) / pre_vol[OPS_ACC1(0, donor)];
      sigma3 = (1.0 + sigmat) *
               (vertexdy[OPS_ACC3(0, 0)] / vertexdy[OPS_ACC3(0, dif)]);
      sigma4 = 2.0 - sigmat;

      sigmav = sigmat;

      diffuw = density1[OPS_ACC4(0, donor)] - density1[OPS_ACC4(0, upwind)];
      diffdw = density1[OPS_ACC4(0, downwind)] - density1[OPS_ACC4(0, donor)];

      if ((diffuw * diffdw) > 0.0)
        limiter =
            (1.0 - sigmav) * SIGN(1.0, diffdw) *
            MIN(MIN(fabs(diffuw), fabs(diffdw)),
                one_by_six * (sigma3 * fabs(diffuw) + sigma4 * fabs(diffdw)));
      else
        limiter = 0.0;

      mass_flux_y[OPS_ACC6(0, 0)] = (vol_flux_y[OPS_ACC0(0, 0)]) *
                                    (density1[OPS_ACC4(0, donor)] + limiter);

      sigmam = fabs(mass_flux_y[OPS_ACC6(0, 0)]) /
               (density1[OPS_ACC4(0, donor)] * pre_vol[OPS_ACC1(0, donor)]);
      diffuw = energy1[OPS_ACC5(0, donor)] - energy1[OPS_ACC5(0, upwind)];
      diffdw = energy1[OPS_ACC5(0, downwind)] - energy1[OPS_ACC5(0, donor)];

      if ((diffuw * diffdw) > 0.0)
        limiter =
            (1.0 - sigmam) * SIGN(1.0, diffdw) *
            MIN(MIN(fabs(diffuw), fabs(diffdw)),
                one_by_six * (sigma3 * fabs(diffuw) + sigma4 * fabs(diffdw)));
      else
        limiter = 0.0;

      ener_flux[OPS_ACC7(0, 0)] =
          mass_flux_y[OPS_ACC6(0, 0)] * (energy1[OPS_ACC5(0, donor)] + limiter);
    }
  }
  if (OPS_diags > 1) {
    ops_timers_core(&c2, &t2);
    OPS_kernels[13].time += t2 - t1;
  }

  if (OPS_diags > 1) {
    // Update kernel record
    ops_timers_core(&c1, &t1);
    OPS_kernels[13].mpi_time += t1 - t2;
    OPS_kernels[13].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[13].transfer += ops_compute_transfer(dim, start, end, &arg1);
    OPS_kernels[13].transfer += ops_compute_transfer(dim, start, end, &arg2);
    OPS_kernels[13].transfer += ops_compute_transfer(dim, start, end, &arg3);
    OPS_kernels[13].transfer += ops_compute_transfer(dim, start, end, &arg4);
    OPS_kernels[13].transfer += ops_compute_transfer(dim, start, end, &arg5);
    OPS_kernels[13].transfer += ops_compute_transfer(dim, start, end, &arg6);
    OPS_kernels[13].transfer += ops_compute_transfer(dim, start, end, &arg7);
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6
#undef OPS_ACC7

void ops_par_loop_advec_cell_kernel3_ydir(char const *name, ops_block block,
                                          int dim, int *range, ops_arg arg0,
                                          ops_arg arg1, ops_arg arg2,
                                          ops_arg arg3, ops_arg arg4,
                                          ops_arg arg5, ops_arg arg6,
                                          ops_arg arg7) {
  ops_kernel_descriptor *desc =
      (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->index = 13;
  desc->hash = 5381;
  desc->hash = ((desc->hash << 5) + desc->hash) + 13;
  for (int i = 0; i < 4; i++) {
    desc->range[i] = range[i];
    desc->orig_range[i] = range[i];
    desc->hash = ((desc->hash << 5) + desc->hash) + range[i];
  }
  desc->nargs = 8;
  desc->args = (ops_arg *)malloc(8 * sizeof(ops_arg));
  desc->args[0] = arg0;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg0.dat->index;
  desc->args[1] = arg1;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg1.dat->index;
  desc->args[2] = arg2;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg2.dat->index;
  desc->args[3] = arg3;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg3.dat->index;
  desc->args[4] = arg4;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg4.dat->index;
  desc->args[5] = arg5;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg5.dat->index;
  desc->args[6] = arg6;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg6.dat->index;
  desc->args[7] = arg7;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg7.dat->index;
  desc->function = ops_par_loop_advec_cell_kernel3_ydir_execute;
  if (OPS_diags > 1) {
    ops_timing_realloc(13, "advec_cell_kernel3_ydir");
  }
  ops_enqueue_kernel(desc);
}
