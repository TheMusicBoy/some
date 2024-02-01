set(INCROOT "${PROJECT_SOURCE_DIR}/include")
set(SRCROOT "${PROJECT_SOURCE_DIR}/src")

set(SRC
    ${INCROOT}/types.h
    ${INCROOT}/options.h
    ${INCROOT}/latex.h
    ${INCROOT}/lu_dec.h
    ${INCROOT}/gaus.h
    ${INCROOT}/rev_iter.h
    ${INCROOT}/simple_iter.h
    ${INCROOT}/fast_descent.h
)

set(MAINSRC 
    ${SRC}
    ${SRCROOT}/main.cpp
)
set(BENCHSRC 
    ${SRC} 
    ${SRCROOT}/benchmark.cpp
)

if (NOT "${MAINSRC}" STREQUAL "")
    message(STATUS "Building main executable...")
    add_executable(main ${MAINSRC})
    target_link_libraries(main PUBLIC Eigen3::Eigen)
    target_include_directories(main PUBLIC ${INCROOT})
    set_target_properties(main PROPERTIES LINKER_LANGUAGE CXX)
else()
    message(WARNING "Main executable is not built")
endif()

if (NOT "${BENCHSRC}" STREQUAL "")
    message(STATUS "Building benchmark executable...")
    add_executable(benchmark ${BENCHSRC})
    target_link_libraries(benchmark PUBLIC Eigen3::Eigen)
    target_include_directories(benchmark PUBLIC ${INCROOT})
    set_target_properties(benchmark PROPERTIES LINKER_LANGUAGE CXX)
else()
    message(WARNING "Main executable is not built")
endif()
