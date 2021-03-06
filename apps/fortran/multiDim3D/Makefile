OPS = $(OPS_INSTALL_PATH)
F_OPS = $(OPS)/fortran
F_OPS_LIB = $(F_OPS)/lib
F_OPS_MOD = $(F_OPS)/mod/$(OPS_COMPILER)
F_OPS_INC = $(F_OPS)/include

# flags for nvcc
# set NV_ARCH to select the correct one
ifndef NV_ARCH
  MESSAGE=select an NVIDA device to compile in CUDA, e.g. make NV_ARCH=KEPLER
  NV_ARCH=Kepler
endif
ifeq ($(NV_ARCH),Fermi)
  CODE_GEN_CUDA=-gencode arch=compute_20,code=sm_21
  PGI_CUDA_FORT_FLAGS=-Mcuda=cuda6.5,cc20
else
ifeq ($(NV_ARCH),Kepler)
  CODE_GEN_CUDA=-gencode arch=compute_35,code=sm_35
  PGI_CUDA_FORT_FLAGS=-Mcuda=cuda7.5,cc35
endif
endif

ifdef HDF5_INSTALL_PATH
  HDF5_INC              := -I$(HDF5_INSTALL_PATH)/include
  HDF5_LIB              := -L$(HDF5_INSTALL_PATH)/lib -lhdf5_hl -lhdf5 -lz
ifdef CHECKPOINTING
  HDF5_INC              := $(HDF5_INC) -DCHECKPOINTING
endif
endif


ifeq ($(OPS_COMPILER),intel)
  CC 		= icc -std=c99
ifdef DEBUG
  OPT	 	= -O0 -g
else
  OPT	 	= -O2 -xAVX
endif
  CCFLAGS       = $(OPT) -Wall -Werror -wd981
  CXX 		= icpc
  CXXFLAGS 	= $(CCFLAGS)
  CXXLINK	= -lstdc++
  FC		= ifort
  OMPFLAGS 	= -openmp -openmp-report2
  FFLAGS	= $(OPT)
  MPICC 	= $(MPI_INSTALL_PATH)/bin/mpicc -std=c99
  MPICXX 	= $(MPI_INSTALL_PATH)/bin/mpicxx
  MPIF90        = $(MPI_INSTALL_PATH)/bin/mpif90
  MPIFLAGS 	= $(CXXFLAGS) -DMPICH_IGNORE_CXX_SEEK -DMPICH_SKIP_MPICXX
  TARGETS	= clean multidim_seq multidim_openmp multidim_mpi multidim_mpi_openmp
else
ifeq ($(OPS_COMPILER),pgi)
ifdef DEBUG
  OPT           = -O0 -g #-Minline -Kieee -Minform=inform -Minfo=all
else
  OPT           = -O3 -Kieee -Minline
endif
  CCFLAGS       = $(OPT) -Wall -Werror -wd981
  CXX           = pgc++
  CXXFLAGS      = $(CCFLAGS)
  CUDA_ALIGN_FLAG = -D__x86_64 -D__align__\(n\)=__attribute__\(\(aligned\(n\)\)\) -D__location__\(a\)=__annotate__\(a\) -DCUDARTAPI=
  CXXLINK       = -lstdc++ -pgcpplibs
  OMPFLAGS 	= -mp
  FC            = pgfortran $(PGI_CUDA_FORT_FLAGS) #,fastmath,ptxinfo
  FFLAGS        = $(OPT) $(PGFLAGS) -ldl
  MPICC         = $(MPI_INSTALL_PATH)/bin/mpicc -std=c99
  MPICXX        = $(MPI_INSTALL_PATH)/bin/mpicxx
  MPIF90        = $(MPI_INSTALL_PATH)/bin/mpif90 $(PGI_CUDA_FORT_FLAGS)
  MPIFLAGS      = $(CXXFLAGS)
  TARGETS       = clean multidim_seq multidim_openmp multidim_mpi multidim_mpi_openmp multidim_cuda multidim_mpi_cuda
else
print:
	@echo "unrecognised value for OPS_COMPILER"
endif
endif

FLINK = -L$(F_OPS_LIB) $(CXXLINK)
FMODS = -I$(F_OPS_MOD) -I$(F_OPS_INC)

all: $(TARGETS)

multidim_seq: multidim_ops.F90 constants.F90
	$(MPIF90) $(FFLAGS) $(FMODS) constants.F90 -c ./MPI/multidim_print_kernel_seq_kernel.F90 \
	./MPI/multidim_copy_kernel_seq_kernel.F90 ./MPI/multidim_kernel_seq_kernel.F90 ./MPI/multidim_reduce_kernel_seq_kernel.F90 multidim_ops.F90
	$(FC) $(FFLAGS) $(FLINK) multidim_ops.o constants.o multidim_kernel_seq_kernel.o multidim_copy_kernel_seq_kernel.o \
	multidim_print_kernel_seq_kernel.o multidim_reduce_kernel_seq_kernel.o -o multidim_seq -lops_for_seq

multidim_openmp: multidim_ops.F90 constants.F90
	$(FC) $(FFLAGS) $(FMODS) $(OMPFLAGS) constants.F90 -c ./MPI/multidim_print_kernel_seq_kernel.F90 \
        ./MPI/multidim_copy_kernel_seq_kernel.F90 ./MPI/multidim_kernel_seq_kernel.F90 ./MPI/multidim_reduce_kernel_seq_kernel.F90 multidim_ops.F90
	$(FC) $(FFLAGS) $(FLINK) $(OMPFLAGS) multidim_ops.o constants.o multidim_kernel_seq_kernel.o multidim_copy_kernel_seq_kernel.o \
        multidim_print_kernel_seq_kernel.o multidim_reduce_kernel_seq_kernel.o -o multidim_openmp -lops_for_seq

multidim_cuda: multidim_ops.F90 constants.F90
ifeq ($(OPS_COMPILER),pgi)
	$(FC) $(FFLAGS) $(FMODS) $(CUDA_ALIGN_FLAG) -DOPS_WITH_CUDAFOR constants.F90 -c ./CUDA/multidim_print_kernel_cuda_kernel.CUF \
	./CUDA/multidim_copy_kernel_cuda_kernel.CUF ./CUDA/multidim_kernel_cuda_kernel.CUF ./CUDA/multidim_reduce_kernel_cuda_kernel.CUF multidim_ops.F90
	$(FC) $(FFLAGS) $(FLINK) $(CUDA_ALIGN_FLAG) -DOPS_WITH_CUDAFOR multidim_ops.o constants.o multidim_kernel_cuda_kernel.o \
	multidim_copy_kernel_cuda_kernel.o multidim_print_kernel_cuda_kernel.o \
	multidim_reduce_kernel_cuda_kernel.o -o multidim_cuda -lops_for_cuda
else
	@echo "cuda cannot be built with $(OPS_COMPILER) compilers .. requires a CUDA FORTRAN compiler (e.g. pgi)"
endif

multidim_mpi: multidim_ops.F90 constants.F90
	$(MPIF90) $(FFLAGS) $(FMODS) -DOPS_MPI -c constants.F90 ./MPI/multidim_print_kernel_seq_kernel.F90 \
        ./MPI/multidim_copy_kernel_seq_kernel.F90 ./MPI/multidim_kernel_seq_kernel.F90 ./MPI/multidim_reduce_kernel_seq_kernel.F90 multidim_ops.F90
	$(MPIF90) $(FFLAGS) $(FLINK) -DOPS_MPI multidim_ops.o constants.o multidim_kernel_seq_kernel.o multidim_copy_kernel_seq_kernel.o \
        multidim_print_kernel_seq_kernel.o multidim_reduce_kernel_seq_kernel.o -o multidim_mpi -lops_for_mpi $(HDF5_LIB)

multidim_mpi_openmp: multidim_ops.F90 constants.F90
	$(MPIF90) $(FFLAGS) $(FMODS) $(OMPFLAGS) -DOPS_MPI -c constants.F90 ./MPI/multidim_print_kernel_seq_kernel.F90 \
        ./MPI/multidim_copy_kernel_seq_kernel.F90 ./MPI/multidim_kernel_seq_kernel.F90 ./MPI/multidim_reduce_kernel_seq_kernel.F90 multidim_ops.F90
	$(MPIF90) $(FFLAGS) $(FLINK) $(OMPFLAGS) -DOPS_MPI multidim_ops.o constants.o multidim_kernel_seq_kernel.o multidim_copy_kernel_seq_kernel.o \
        multidim_print_kernel_seq_kernel.o multidim_reduce_kernel_seq_kernel.o -o multidim_mpi_openmp -lops_for_mpi $(HDF5_LIB)


multidim_mpi_cuda: multidim_ops.F90 constants.F90
ifeq ($(OPS_COMPILER),pgi)
	$(MPIF90) $(FFLAGS) $(FMODS) $(CUDA_ALIGN_FLAG) -DOPS_WITH_CUDAFOR -DOPS_MPI -c constants.F90 ./CUDA/multidim_print_kernel_cuda_kernel.CUF \
	./CUDA/multidim_copy_kernel_cuda_kernel.CUF ./CUDA/multidim_kernel_cuda_kernel.CUF ./CUDA/multidim_reduce_kernel_cuda_kernel.CUF multidim_ops.F90
	$(MPIF90) $(FFLAGS) $(FLINK) $(CUDA_ALIGN_FLAG) -DOPS_WITH_CUDAFOR -DOPS_MPI multidim_ops.o constants.o multidim_kernel_cuda_kernel.o \
        multidim_copy_kernel_cuda_kernel.o multidim_print_kernel_cuda_kernel.o \
        multidim_reduce_kernel_cuda_kernel.o -o multidim_mpi_cuda -lops_for_mpi_cuda $(HDF5_LIB)
else
	@echo "cuda cannot be built with $(OPS_COMPILER) compilers .. requires a CUDA FORTRAN compiler (e.g. pgi)"
endif


clean:
	rm -f *.o
	rm -f *.mod
	rm -f $(EXEC)
	rm -f *~
	rm -f multidim_seq multidim_cuda multidim_openmp multidim_mpi multidim_mpi_openmp multidim_mpi_cuda
