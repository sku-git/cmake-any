
add_prj_link_library(libcmocka.so)

add_prj_linker_option("-Wl,-gc-sections")
add_prj_linker_option("-Map=${outfile}.map")
add_prj_linker_option("-L${CMAKE_SOURCE_DIR}")

