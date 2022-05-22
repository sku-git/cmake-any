# Setup toolchain information
# include(avr-tools.cmake)

# Define the name of the executable here
set(exec_name    SIMPLE_TEST)
set(exec_version 1.0)

set(outfile "${exec_name}_${exec_version}")

# Add the sub directories to be parsed in the following list
include(subdirs.cmake)
