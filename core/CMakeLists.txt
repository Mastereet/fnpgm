set(FOLDER_NAME core)

WILL_ADD_LIBRARY(
    NAME fnpgm_core
    SOURCES
        
    HEADERS
        common.hpp
    PUBLIC_LINK_LIBRARIES
        Eigen3::Eigen
)

