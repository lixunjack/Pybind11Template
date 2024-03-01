#ifndef CODAWAVESOLVER_HPP
#define CODAWAVESOLVER_HPP

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <omp.h>

namespace py = pybind11;

void calculateCCstrech(const py::array_t<double>& data_set,
    py::array_t<double>& cc_epsilon,
    const py::array_t<double>& time_axis,
    const py::array_t<double>& epsilon,
    double window_start_frac, double window_end_frac,
    py::ssize_t ref_trace_index);



PYBIND11_MODULE(codawavesolver, m) {
    m.doc() = "Module for calculating phase shift between time-serial signals using the stretch method";
    m.def("calculateCCstrech", &calculateCCstrech, R"pbdoc(
        Function to calculate the cross-correlation epsilon between time-serial signals.

        Args:
            data_set (numpy.ndarray): The input dataset as a 2D numpy array.
            cc_epsilon (numpy.ndarray): The output cross-correlation epsilon as a 2D numpy array.
            time_axis (numpy.ndarray): The time axis as a 1D numpy array.
            epsilon (numpy.ndarray): The epsilon values as a 1D numpy array.
            window_start_frac (float): The fraction of the window start.
            window_end_frac (float): The fraction of the window end.
            ref_trace_index (int): The index of the reference trace.

        Returns:
            None. The calculated cross-correlation epsilon is stored in cc_epsilon.

        Note:
            This function assumes that all input arrays have compatible shapes.
    )pbdoc");

    m.def("get_max_threads", &omp_get_max_threads, "Returns max number of threads");
    m.def("set_num_threads", &omp_set_num_threads, "Set number of threads");
}

#endif /* CODAWAVESOLVER_HPP */

