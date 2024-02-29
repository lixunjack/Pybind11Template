#include "CodaWaveSolver.hpp"

void calculateCCstrech(const py::array_t<double>& data_set,
    py::array_t<double>& cc_epsilon,
    const py::array_t<double>& time_axis,
    const py::array_t<double>& epsilon,
    double window_start_frac, double window_end_frac,
    py::ssize_t ref_trace_index) {

    auto data_set_ptr = data_set.unchecked<2>(); // 2D numpy array
    auto cc_epsilon_ptr = cc_epsilon.mutable_unchecked<2>(); // Mutable 2D numpy array

    auto time_axis_ptr = time_axis.unchecked<1>(); // 1D numpy array
    auto epsilon_ptr = epsilon.unchecked<1>(); // 1D numpy array

    double denominator1 = 0.0, denominator2 = 0.0; double total_deno=0.0;
    auto time_interval = time_axis_ptr(1) - time_axis_ptr(0);
  

    for (py::ssize_t  i= py::ssize_t(data_set_ptr.shape(1) * window_start_frac); i < py::ssize_t (data_set_ptr.shape(1)* window_end_frac); i++) { //have to use special type to access
        denominator1 += data_set_ptr(ref_trace_index, i) * data_set_ptr(ref_trace_index, i);
    }

    for (py::ssize_t i = 0; i < data_set_ptr.shape(0); i++) {
        for (py::ssize_t j = 0; j < cc_epsilon_ptr.shape(0); j++) {
            denominator2 = 0.0;
            cc_epsilon_ptr(i, j) = 0.0;

            for (py::ssize_t k= py::ssize_t(data_set_ptr.shape(1) * window_start_frac); k < py::ssize_t(data_set_ptr.shape(1) * window_end_frac); k++) {
                py::ssize_t shift = static_cast<py::ssize_t>(time_axis_ptr(k) * epsilon_ptr(j) / time_interval);

                cc_epsilon_ptr(i, j) += data_set_ptr(ref_trace_index, k) * data_set_ptr(i, k + shift);
                
                denominator2 += data_set_ptr(i, k + shift) * data_set_ptr(i, k + shift);
            }

            total_deno = sqrt(fabs(denominator1 * denominator2));

            cc_epsilon_ptr(i, j) /= total_deno;
        }
    }
}

