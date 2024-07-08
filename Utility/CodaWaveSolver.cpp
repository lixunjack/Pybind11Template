#include "codawavesolver.hpp"



void calculateCCstrech(const py::array_t<double>& data_set,
    py::array_t<double>& cc_epsilon,
    const py::array_t<double>& time_axis,
    const py::array_t<double>& epsilon_matrix,
    double window_start_frac, double window_end_frac,
    py::ssize_t ref_trace_index) {


    auto data_set_ptr = data_set.unchecked<2>(); // 2D numpy array
    auto cc_epsilon_ptr = cc_epsilon.mutable_unchecked<2>(); // Mutable 2D numpy array

    auto time_axis_ptr = time_axis.unchecked<1>(); // 1D numpy array
    auto epsilon_ptr = epsilon_matrix.unchecked<2>(); // 2D numpy array

    double denominator1 = 0.0, denominator2 = 0.0; 
    double total_deno=0.0, ij_sum=0.0; 
    auto time_interval = time_axis_ptr(1) - time_axis_ptr(0);
  

    for (py::ssize_t  i= static_cast<py::ssize_t>(data_set_ptr.shape(1) * window_start_frac); i < static_cast<py::ssize_t> (data_set_ptr.shape(1)* window_end_frac); i++) { //have to use special type to access
        denominator1 += data_set_ptr(ref_trace_index, i) * data_set_ptr(ref_trace_index, i);
    }


    py::ssize_t i=0, j=0, k=0;
    //warning shift cannot be size type as it can be negative number
    long long int shift = 0;
    py::ssize_t numtrace = data_set_ptr.shape(0);
    py::ssize_t numtimesamples = data_set_ptr.shape(1);
    py::ssize_t numeps = epsilon_ptr.shape(1);
    
    // Release the GIL
    py::gil_scoped_release release;

#pragma omp parallel for  private(i,j,k,shift,denominator2,total_deno,ij_sum) shared(window_end_frac, window_start_frac, ref_trace_index, numtrace,numtimesamples,numeps ,data_set_ptr,cc_epsilon_ptr,time_interval,time_axis_ptr,denominator1,epsilon_ptr) default (none)
    for (i = 0; i < numtrace; i++) {
        for (j = 0; j < numeps; j++) {
            denominator2 = 0.0;
            ij_sum = 0.0;

            for (k= static_cast<py::ssize_t>(numtimesamples * window_start_frac); k < static_cast<py::ssize_t>(numtimesamples * window_end_frac); k++) {
                shift = static_cast<long long int>(time_axis_ptr(k) * epsilon_ptr(i,j) / time_interval);

                ij_sum += data_set_ptr(ref_trace_index, k) * data_set_ptr(i, k + shift);
                
                denominator2 += data_set_ptr(i, k + shift) * data_set_ptr(i, k + shift);
            }

            total_deno = sqrt(fabs(denominator1 * denominator2));

            cc_epsilon_ptr(i, j) = ij_sum/ total_deno;
        }
    }

    // Re-acquire the GIL after the parallel region
    py::gil_scoped_acquire acquire;


}

