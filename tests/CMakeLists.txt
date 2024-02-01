set(SRCROOT "${PROJECT_SOURCE_DIR}/tests")

set(SRC
    ${SRCROOT}/test.cpp
)

if (NOT "${SRC}" STREQUAL "")
    message(STATUS "Building test executable...")
    add_executable(test ${SRC})
    target_link_libraries(test PUBLIC Eigen3::Eigen)
    target_include_directories(test PUBLIC ${INCROOT})
    set_target_properties(test PROPERTIES LINKER_LANGUAGE CXX)
else()
    message(WARNING "Test executable is not built")
endif()

set(SRC
    ${SRCROOT}/benchmark.cpp
)

