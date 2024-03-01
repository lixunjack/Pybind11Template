from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup
import sysconfig

__version__ = "0.0.1"



# The main interface is through Pybind11Extension.
# * You can add cxx_std=11/14/17, and then build_ext can be removed.
# * You can set include_pybind11=false to add the include directory yourself,
#   say from a submodule.
#
# Note:
#   Sort input source files if you glob sources to ensure bit-for-bit
#   reproducible builds (https://github.com/pybind/python_example/pull/53)


# Get the include directory dynamically
include_dirs = [sysconfig.get_paths()['include']]
extra_compile_args = ["-std=c++17", "-fopenmp"]


ext_modules = [
    Pybind11Extension(
        "codawavesolver",
        ["Utility/codawavesolver.cpp"],
        define_macros=[("VERSION_INFO", __version__)],
        include_dirs=include_dirs,
        extra_compile_args=extra_compile_args,
    ),
]

setup(
    name="codawavesolver",
    version=__version__,
    author="Jack Li",
    license="MIT",
    author_email="your_email@example.com",
    url="https://github.com/lixunjack/codawavesolver",
    description="A Python module to calculate phase shift between time-serial signals, backend with cpp and Pybind11",
    long_description="codawavesolver is a Python module that implements a stretch method to calculate phase shift between time-serial signals. It utilizes Pybind11 to bind C++ code to Python.",
    ext_modules=ext_modules,
    python_requires=">=3.7",
    install_requires=[
        'pybind11 >=2.10.0',
        'numpy>=1.20',
        'matplotlib>=3.7',
        'importlib>=1.0'],
    cmdclass={"build_ext": build_ext},
    zip_safe=False
)



