#for development!
import importlib
import stretchCC
importlib.reload(stretchCC)

import numpy as np

# Generate random data_set
num_trace = 100  # Number of traces
trace_length = 10000  # Length of each trace

# Initialize data_set with zeros
data_set = np.array([[100 * np.sin(i + 12) * np.cos(j + 14) for j in range(trace_length)] for i in range(num_trace)])

# Generate other necessary input vectors
time_step = 0.1  # Time step size
time_axis = np.arange(trace_length) * time_step

num_epsilons = 100  # Number of epsilons
epsilon = np.linspace(-0.05, 0.05, num_epsilons)

window_start_index = 0.2
window_end_index = 0.4
ref_trace_index = 0

# Create cc_epsilon vector as a NumPy array
cc_epsilon = np.zeros((num_trace, num_epsilons), dtype=float)



stretchCC.calculateCCstrech(data_set, cc_epsilon, time_axis, epsilon, window_start_index, window_end_index, ref_trace_index)

print(cc_epsilon)

import matplotlib.pyplot as plt
plt.plot(np.max(cc_epsilon, axis=1))
