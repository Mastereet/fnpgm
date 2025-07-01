set(FOLDER_NAME FileHandle)

WILL_ADD_LIBRARY(
    NAME fnpgm_filehandle
    SOURCES
        ExtendFilter.cpp
        FilePathCollector.cpp
    HEADERS
        ExtendFilter.hpp
        FilePathExtractor.hpp
        FilePathCollector.hpp
)

WILL_ADD_TEST(
    NAME ExtendFilter_test
    SOURCES
        ExtendFilter_test.cpp
    PRIVATE_LINK_LIBRARIES
        fnpgm_filehandle
)

WILL_ADD_TEST(
    NAME FilePathExtractor_test
    SOURCES
        FilePathExtractor_test.cpp
    PRIVATE_LINK_LIBRARIES
        fnpgm_filehandle
)

WILL_ADD_TEST(
    NAME FilePathCollector_test
    SOURCES
        FilePathCollector_test.cpp
    PRIVATE_LINK_LIBRARIES
        fnpgm_filehandle
)