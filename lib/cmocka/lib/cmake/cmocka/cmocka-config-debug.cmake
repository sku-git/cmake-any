#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "cmocka::cmocka" for configuration "Debug"
set_property(TARGET cmocka::cmocka APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(cmocka::cmocka PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libcmocka.so.0.7.0"
  IMPORTED_SONAME_DEBUG "libcmocka.so.0"
  )

list(APPEND _IMPORT_CHECK_TARGETS cmocka::cmocka )
list(APPEND _IMPORT_CHECK_FILES_FOR_cmocka::cmocka "${_IMPORT_PREFIX}/lib/libcmocka.so.0.7.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
