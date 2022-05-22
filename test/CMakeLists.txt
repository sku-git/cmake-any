cmake_minimum_required(VERSION 3.5)

# Enter the project name nd version here
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")  
message("Project name follows...")
project(TEST_PROJ)

include(project.cmake)

#############################################################################
# Do not modify above lines
#############################################################################


# Global variable PROJ_LINK_LIBRARIES to hold linker options
define_property(GLOBAL PROPERTY PROJ_LINK_LIBRARIES
BRIEF_DOCS "Global PROJ_LINK_LIBRARIES options list"
FULL_DOCS "Global PROJ_LINK_LIBRARIES options list")

set_property(GLOBAL PROPERTY PROJ_LINK_LIBRARIES "")

macro(add_prj_link_library linkLibrary)
  set_property(GLOBAL APPEND PROPERTY PROJ_LINK_LIBRARIES "${linkLibrary}")
endmacro(add_prj_link_library)

# Global variable LINK_OPTIONS to hold linker options
define_property(GLOBAL PROPERTY PROJ_LINK_OPTIONS
BRIEF_DOCS "Global PROJ_LINK_OPTIONS options list"
FULL_DOCS "Global PROJ_LINK_OPTIONS options list")

set_property(GLOBAL PROPERTY PROJ_LINK_OPTIONS "")

macro(add_prj_linker_option linkOption)
  set_property(GLOBAL APPEND PROPERTY PROJ_LINK_OPTIONS "${linkOption}")
endmacro(add_prj_linker_option)

# Global variable COMPILER_OPTIONS to hold compiler options
define_property(GLOBAL PROPERTY PROJ_COMPILE_OPTIONS
BRIEF_DOCS "Global PROJ_COMPILE_OPTIONS options list"
FULL_DOCS "Global PROJ_COMPILE_OPTIONS options list")

set_property(GLOBAL PROPERTY PROJ_COMPILE_OPTIONS "")

macro(add_prj_compile_options compOption)
  set_property(GLOBAL APPEND PROPERTY PROJ_COMPILE_OPTIONS "${compOption}")
endmacro(add_prj_compile_options)

# Global variable SRC to hold soruce files
define_property(GLOBAL PROPERTY SRC
BRIEF_DOCS "Global Src files list"
FULL_DOCS "Global Src files list")

set_property(GLOBAL PROPERTY SRC "")

macro(add_src_files srcfiles)
  set_property(GLOBAL APPEND PROPERTY SRC "${srcfiles}")
endmacro(add_src_files)

# Global variable INCDIR to hold include directories
define_property(GLOBAL PROPERTY INCDIR
BRIEF_DOCS "Global include directories list"
FULL_DOCS "Global include directories list")

set_property(GLOBAL PROPERTY INCDIR "")

macro(add_inc_folders folders)
  set_property(GLOBAL APPEND PROPERTY INCDIR "${folders}")
endmacro(add_inc_folders)


#############################################################################
# Do not modify below lines
#############################################################################

include(${PROJ_TARGET_OPTIONS_FILE})

# Add all sub drectories
foreach(sdir IN LISTS sub_dirs)
  message("Adding sub dir : ${sdir}")
  add_subdirectory(${sdir})
endforeach()

# Add all executables collected
get_property(all_src_files GLOBAL PROPERTY SRC)
message("Srcs : ${all_src_files}")

add_executable(${outfile} ${all_src_files})

# Add all the include directories collected
get_property(all_inc_dirs GLOBAL PROPERTY INCDIR)
message("Inc Dirs : ${all_inc_dirs}")
include_directories( ${all_inc_dirs} )

# Get all linker libraries
get_property(all_linker_libraries GLOBAL PROPERTY PROJ_LINK_LIBRARIES)
string(REPLACE ";" ", " use_all_linker_libraries "${all_linker_libraries}")
set(LIBS "${LIBS} ${use_all_linker_libraries}")
message("Link libraries : ${LIBS}")

# Get all linker options
get_property(all_linker_options GLOBAL PROPERTY PROJ_LINK_OPTIONS)
string(REPLACE ";" "," use_all_linker_options "${all_linker_options}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${use_all_linker_options}")
message("Linker options : ${CMAKE_EXE_LINKER_FLAGS}")

# Get all compiler options
get_property(all_compiler_options GLOBAL PROPERTY PROJ_COMPILE_OPTIONS)
string(REPLACE ";" " " use_all_compiler_options "${all_compiler_options}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${use_all_compiler_options}")
message("Compiler options : ${CMAKE_C_FLAGS}")

message("Compiler options C++ : ${CMAKE_CXX_FLAGS}")

#Link external libraries
if("${LIBS}")
target_link_libraries(${outfile} "${LIBS}")
endif("${LIBS}")

# Post build commands

set(HEX_FILE ${outfile}.hex)
set(BIN_FILE ${outfile}.bin)
add_custom_command(TARGET ${outfile} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${outfile}> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${outfile}> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE} \nBuilding ${BIN_FILE}")
