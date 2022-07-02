from setuptools import setup, find_packages
from distutils.core import Extension

setup(
    name='pr',
    version='0.0',
    ext_modules=[Extension('pr._accel', sources=['pr/_accel.c'])],
    description='python prisoners riddle with optional c bindings',
    packages=find_packages()
)
