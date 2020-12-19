import matplotlib.pyplot as plt

inputs_size = [20, 21, 22, 23, 24, 25]

serial = [1.318, 2.831, 6.182, 13.272, 28.545, 61.401]
openmp = [0.585, 1.282, 2.523, 5.609, 12.148, 24.963]
mpi = [0.663, 1.282, 2.741, 5.801, 11.726, 25.828]
pthreads = [0.443, 0.925, 1.889, 4.205, 8.701, 18.267]
hybrid_mpi_openmp = [0.818, 1.613, 3.123, 6.585, 13.222, 27.722]
# hybrid_mpi_pthreads = []

plt.figure(1)

plt.plot(inputs_size, serial, label = "Serial")
plt.plot(inputs_size, openmp, label = "OpenMP")
plt.plot(inputs_size, mpi, label = "MPI")
plt.plot(inputs_size, pthreads, label = "PThreads")
plt.plot(inputs_size, hybrid_mpi_openmp, label = "Hybrid (MPI + OpenMP)")
# plt.plot(inputs_size, hybrid_mpi_pthreads, label = "Hybrid (MPI + PThreads)")

plt.xlabel('numar de noduri (log2(DIM_VECTOR))')
plt.ylabel('timp executie')
plt.legend()
plt.title("Timpi de executie Bitonic Sort")
plt.show()
