include(FetchContent)

function (add_from_fetch TARGET_NAME REPO_TYPE TAG_TYPE REPO)
    message(STATUS "Fetching ${TARGET_NAME} ---")
    set(TAG ${ARGN})
    if (NOT "${TAG}" STREQUAL "")
        FetchContent_Declare(
            ${TARGET_NAME}
            ${REPO_TYPE} ${REPO}
            ${TAG_TYPE} ${TAG}
        )
    else()
        FetchContent_Declare(
            ${TARGET_NAME}
            ${REPO_TYPE} ${REPO}
        )
    endif()

    FetchContent_MakeAvailable(${TARGET_NAME})
    FetchContent_GetProperties(${TARGET_NAME})

    if (NOT ${TARGET_NAME}_POPULATED)
        message(STATUS "Populating...")
        FetchContent_Populate(${TARGET_NAME})
        add_subdirectory(${${TARGET_NAME}_SOURCE_DIR} ${${TARGET_NAME}_BINARY_DIR})
    else()
        message(STATUS "${TARGET_NAME} already populated")
    endif()
    message(STATUS "Successfuly fetched ---")
endfunction()

function (add_from_git TARGET_NAME REPO)
    add_from_fetch(${TARGET_NAME} GIT_REPOSITORY GIT_TAG ${REPO} ${ARGN})
endfunction()

# Fetched content

# add_from_git(matrix "git@github.com:TheMusicBoy/Matrix.git" main)
# add_from_git(eigen "https://gitlab.com/libeigen/eigen.git" master)
