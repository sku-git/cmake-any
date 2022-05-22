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

## cmocka
Install the Cmocka as described in the https://cmocka.org.
The cmocka can be downloaded, build and installed as described on the website.

## Testing
Write the test cases in the "sources" folder.
Update the CMakeLists.txt file.
Then build as described above.

### Unit tests
Each file should be self contained unit test module. This should have a main() function in it.
Mock the required functions and write unit tests as described in the cmocka documentation.

### Examples
Some examples are available in the source for the `cliapp` provided in `guest/` folder.
