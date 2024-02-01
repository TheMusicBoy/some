cmake_minimum_required(VERSION 3.15)
project(TestMicroCtrl)


# Export compile commands
message(STATUS "Export compile_commands - ON")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Build settings
set(CMAKE_CXX_STANDARD 20)

option(DEBUG "" OFF)

if (${DEBUG})
    message(STATUS "Building with debug...")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

# Building ---
add_subdirectory(thirdparty)

find_package(Eigen3 3.4 REQUIRED NO_MODULE)
add_subdirectory(src)

add_subdirectory(tests)

add_custom_target(build_finish ALL
    COMMENT "Build almost finished..."
)

add_custom_command(TARGET build_finish POST_BUILD
    COMMAND cp ${PROJECT_BINARY_DIR}/compile_commands.json ${PROJECT_SOURCE_DIR}/
    VERBATIM
)
