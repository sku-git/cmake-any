# cmake-any
template for cmake projects

In the file toolchain.cmake, please make following changes:
Set the following to proper paths in local machine:

```text
set(TOOL_PATH /usr/bin)
set(LIBPATH /usr/lib )
```
These should point to the installation of the gcc toolchain in the local machine.

>These should point to the places where the gcc, g++ etc compilers are located.
>>The lib folder also shares the same root path as these tools.



Execute the following commands from the cmake-proj folder.:

```commandline
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../test/toolchain.cmake ../test
make

```

> Execute the following from the directory above the src or test folder.
> This is usually the cmake-proj folder.


## Cmake generation
To generate the cmake files for a project that is not supporting, the
`tools/pycmake` python project should be used. See its readme for the details.

## TODO
Support the unit testing using cmocka.