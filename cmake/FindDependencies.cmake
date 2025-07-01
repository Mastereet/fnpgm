# if FNPGM_FIND_QUIETLY is true, set FNPGM_FIND_TYPE to QUIET
# Only the error message that the library cannot be found FNPGM be output, 
# and the search process FNPGM not be output.
# if FNPGM_FIND_QUIETLY is false, set FNPGM_FIND_TYPE to REQUIRED
# If the library cannot be found, the build FNPGM fail.
if(FNPGM_FIND_QUIETLY)
    set(FNPGM_FIND_TYPE QUIET)
else()
    set(FNPGM_FIND_TYPE REQUIRED)
endif()

find_package(OpenCV ${FNPGM_FIND_TYPE})
find_package(Ceres ${FNPGM_FIND_TYPE})
find_package(Eigen3 ${FNPGM_FIND_TYPE})

find_package(OpenMP ${FNPGM_FIND_TYPE})
if(OPENMP_ENABLED AND OPENMP_FOUND)
    message(STATUS "Enabling OpenMP support")
    add_definitions("-DFNPGM_OPENMP_ENABLED")
else()
    message(STATUS "Disabling OpenMP support")
endif()

if(TESTS_ENABLED)
    find_package(GTest ${FNPGM_FIND_TYPE})
endif()
