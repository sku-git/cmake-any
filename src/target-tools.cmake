message("Using arm32-cortex-m3-tools")
##########################################################################
# executables in use
##########################################################################
set(TOOL_PATH /usr/bin)
set(LIBPATH /usr/lib )

message("Tool path ${TOOL_PATH}")
message("Tool libraries path ${LIBPATH}")

#set(ARM_CPU cortex-m3)  # Only use for ARM processors

find_program(TARGET_CC gcc PATHS ${TOOL_PATH} NO_DEFAULT_PATH)
find_program(TARGET_CXX g++ PATHS ${TOOL_PATH} NO_DEFAULT_PATH)
find_program(TARGET_OBJCOPY objcopy PATHS ${TOOL_PATH} NO_DEFAULT_PATH)
find_program(TARGET_SIZE_TOOL size PATHS ${TOOL_PATH} NO_DEFAULT_PATH)
find_program(TARGET_OBJDUMP objdump PATHS ${TOOL_PATH} NO_DEFAULT_PATH)

message("TARGET_CC : ${TARGET_CC}")
message("TARGET_CXX : ${TARGET_CXX}")
message("TARGET_OBJCOPY : ${TARGET_OBJCOPY}")
message("TARGET_SIZE_TOOL : ${TARGET_SIZE_TOOL}")
message("TARGET_OBJDUMP : ${TARGET_OBJDUMP}")

##########################################################################
# toolchain starts with defining mandatory variables
##########################################################################
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ${CMAKE_HOST_SYSTEM_PROCESSOR})
set(CMAKE_C_COMPILER ${TARGET_CC})
set(CMAKE_CXX_COMPILER ${TARGET_CXX})

set(PROJ_TARGET_OPTIONS_FILE "target-options.cmake")

