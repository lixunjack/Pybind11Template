# codawavesolver

codawavesolver is a Python module that implements a stretch method to calculate phase shift between time-serial signals. It utilizes Pybind11 to bind C++ code to Python.

## Installation

To install codawavesolver, follow these steps:

- Clone this repository.
- Navigate to the repository directory.
- Run `pip install ./codawavesolver`

## Usage Example

For development purposes, you can test the functionality of codawavesolver with the following command:

```python
# For development!
import importlib
import codawavesolver
importlib.reload(codawavesolver)

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

codawavesolver.calculateCCstrech(data_set, cc_epsilon, time_axis, epsilon, window_start_index, window_end_index, ref_trace_index)

print(cc_epsilon)

import matplotlib.pyplot as plt
plt.plot(np.max(cc_epsilon, axis=1))
```
## Building the Documentation

The documentation for this project is generated using Sphinx. To generate HTML-based reference documentation:

- Navigate to the `docs` directory (`cd codawavesolver/docs`).
- Run `make html`.

For other formats, please refer to the Sphinx manual.

## License

codawavesolver is provided under a BSD-style license. By using, distributing, or contributing to this project, you agree to the terms and conditions of this license.


