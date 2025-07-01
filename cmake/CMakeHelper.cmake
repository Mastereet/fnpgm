# This macro will search for source files in a given directory, will add them
# to a source group (folder within a project), and will then return paths to
# each of the found files. The usage of the macro is as follows:
# WILL_ADD_SOURCE_DIR(
#     <source directory to search>
#     <output variable with found source files>
#     <search expressions such as *.h *.cc>)
macro(WILL_ADD_SOURCE_DIR SRC_DIR OUTPUT_VAR)
    # Set the glob expressions to search for
    set(GLOB_EXPRESSIONS "")
    # Add the glob expressions to the list
    # eg src/*.cpp
    foreach(ARG ${ARGN})
        list(APPEND GLOB_EXPRESSIONS ${SRC_DIR}/${ARG})
    endforeach()
    # Find the files in the directory, return relative paths
    file(GLOB ${OUTPUT_VAR} RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${GLOB_EXPRESSIONS})
    # Create the source group.
    string(REPLACE "/" "\\" GROUP_NAME ${SRC_DIR})
    source_group(${GROUP_NAME} FILES ${${OUTPUT_VAR}})
    # Clean-up.
    unset(GLOB_EXPRESSIONS)
    unset(ARG)
    unset(GROUP_NAME)
endmacro(WILL_ADD_SOURCE_DIR)

# This macro will add a library to the project.
# If there are source files, it will create a static library.
# If there are no source files, it will create an interface library (for pure header library).
# The usage of the macro is as follows:
# WILL_ADD_LIBRARY(
#     NAME <library name>
#     SOURCES <source files>
#     HEADERS <header files>
#     PUBLIC_LINK_LIBRARIES <libraries to link against>
#     PRIVATE_LINK_LIBRARIES <libraries to link against>
# )

macro(WILL_ADD_LIBRARY)
    # Set the options
    set(options)
    # Set the single-value arguments
    set(single_value_args)
    # Set the multi-value arguments
    set(multi_value_args "NAME" "SOURCES" "HEADERS" "PUBLIC_LINK_LIBRARIES" "PRIVATE_LINK_LIBRARIES")
    # Parse the arguments
    cmake_parse_arguments(WILL_ADD_LIBRARY "${options}" "${single_value_args}" "${multi_value_args}" ${ARGN})

    if(WILL_ADD_LIBRARY_SOURCES)
        # if there are source files, create a static library
        add_library(${WILL_ADD_LIBRARY_NAME} STATIC ${WILL_ADD_LIBRARY_SOURCES} ${WILL_ADD_LIBRARY_HEADERS})
        # link the library
        target_link_libraries(${WILL_ADD_LIBRARY_NAME}
            PRIVATE ${WILL_ADD_LIBRARY_PRIVATE_LINK_LIBRARIES}
            PUBLIC ${WILL_ADD_LIBRARY_PUBLIC_LINK_LIBRARIES})
    else()
        # if there are no source files, create an interface library (for pure header library)
        add_library(${WILL_ADD_LIBRARY_NAME} INTERFACE ${WILL_ADD_LIBRARY_HEADERS})
        # target_include_directories(${WILL_ADD_LIBRARY_NAME} INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
        # For an interface library, linking must be done with INTERFACE keyword only
        target_link_libraries(${WILL_ADD_LIBRARY_NAME}
            INTERFACE 
            ${WILL_ADD_LIBRARY_PRIVATE_LINK_LIBRARIES}
            ${WILL_ADD_LIBRARY_PUBLIC_LINK_LIBRARIES})
    endif()
endmacro(WILL_ADD_LIBRARY)


macro(WILL_ADD_STATIC_LIBRARY)
    # Set the options
    set(options)
    # Set the single-value arguments
    set(single_value_args)
    # Set the multi-value arguments
    set(multi_value_args "NAME" "SOURCES" "HEADERS" "PUBLIC_LINK_LIBRARIES" "PRIVATE_LINK_LIBRARIES")
    # Parse the arguments
    cmake_parse_arguments(WILL_ADD_LIBRARY "${options}" "${single_value_args}" "${multi_value_args}" ${ARGN})
    # Add the library
    add_library(${WILL_ADD_LIBRARY_NAME} STATIC ${WILL_ADD_LIBRARY_SOURCES} ${WILL_ADD_LIBRARY_HEADERS})
    # Link the library against the specified libraries
    target_link_libraries(${WILL_ADD_LIBRARY_NAME}
        PRIVATE
        ${WILL_ADD_LIBRARY_PRIVATE_LINK_LIBRARIES}
        PUBLIC
        ${WILL_ADD_LIBRARY_PUBLIC_LINK_LIBRARIES})
endmacro(WILL_ADD_STATIC_LIBRARY)

# This macro will add an interface library to the project, pure header library.
# The usage of the macro is as follows:
# WILL_ADD_INTERFACE_LIBRARY(
#     NAME <library name>
#     HEADERS <header files>
#     PUBLIC_LINK_LIBRARIES <libraries to link against>
#     PRIVATE_LINK_LIBRARIES <libraries to link against>
# )
macro(WILL_ADD_INTERFACE_LIBRARY)
    # Set the options
    set(options)
    # Set the single-value arguments
    set(single_value_args)
    # Set the multi-value arguments
    set(multi_value_args "NAME" "HEADERS" "PUBLIC_LINK_LIBRARIES" "PRIVATE_LINK_LIBRARIES")
    # Parse the arguments
    cmake_parse_arguments(WILL_ADD_INTERFACE_LIBRARY "${options}" "${single_value_args}" "${multi_value_args}" ${ARGN})
    # Add the library
    add_library(${WILL_ADD_INTERFACE_LIBRARY_NAME} INTERFACE ${WILL_ADD_INTERFACE_LIBRARY_HEADERS})
    # Link the library against the specified libraries
    target_link_libraries(${WILL_ADD_INTERFACE_LIBRARY_NAME}
        INTERFACE
        ${WILL_ADD_INTERFACE_LIBRARY_PRIVATE_LINK_LIBRARIES}
        ${WILL_ADD_INTERFACE_LIBRARY_PUBLIC_LINK_LIBRARIES})
endmacro(WILL_ADD_INTERFACE_LIBRARY)

# This macro will add an executable to the project.
# The usage of the macro is as follows:
# WILL_ADD_EXECUTABLE(
#     NAME <executable name>
#     SOURCES <source files>
#     HEADERS <header files>
#     PUBLIC_LINK_LIBRARIES <libraries to link against>
#     PRIVATE_LINK_LIBRARIES <libraries to link against>
# )
macro(WILL_ADD_EXECUTABLE)
    # Set the options
    set(options)
    # Set the single-value arguments
    set(single_value_args)
    # Set the multi-value arguments
    set(multi_value_args "NAME" "SOURCES" "HEADERS" "PUBLIC_LINK_LIBRARIES" "PRIVATE_LINK_LIBRARIES")
    # Parse the arguments
    cmake_parse_arguments(WILL_ADD_EXECUTABLE "${options}" "${single_value_args}" "${multi_value_args}" ${ARGN})
    # Add the executable
    add_executable(${WILL_ADD_EXECUTABLE_NAME} ${WILL_ADD_EXECUTABLE_SOURCES} ${WILL_ADD_EXECUTABLE_HEADERS})
    # Link the executable against the specified libraries
    target_link_libraries(${WILL_ADD_EXECUTABLE_NAME}
        PRIVATE
        ${WILL_ADD_EXECUTABLE_PRIVATE_LINK_LIBRARIES}
        PUBLIC
        ${WILL_ADD_EXECUTABLE_PUBLIC_LINK_LIBRARIES})
endmacro(WILL_ADD_EXECUTABLE)

# This macro will add a test to the project.
# The usage of the macro is as follows:
# WILL_ADD_TEST(
#     NAME <test name>
#     SOURCES <source files>
#     HEADERS <header files>
#     PUBLIC_LINK_LIBRARIES <libraries to link against>
#     PRIVATE_LINK_LIBRARIES <libraries to link against>
# )
macro(WILL_ADD_TEST)
    # Set the options
    set(options)
    # Set the single-value arguments
    set(single_value_args)
    # Set the multi-value arguments
    set(multi_value_args "NAME" "SOURCES" "HEADERS" "PUBLIC_LINK_LIBRARIES" "PRIVATE_LINK_LIBRARIES")
    # Parse the arguments
    cmake_parse_arguments(WILL_ADD_TEST "${options}" "${single_value_args}" "${multi_value_args}" ${ARGN})
    if(TESTS_ENABLED)
        set(WILL_ADD_TEST_NAME "WILL_${FOLDER_NAME}_${WILL_ADD_TEST_NAME}")
        add_executable(${WILL_ADD_TEST_NAME} ${WILL_ADD_TEST_SOURCES} ${WILL_ADD_TEST_HEADERS})
        target_link_libraries(${WILL_ADD_TEST_NAME}
            PRIVATE
            ${WILL_ADD_TEST_PRIVATE_LINK_LIBRARIES}
            GTest::gtest_main
            GTest::gtest
            PUBLIC
            ${WILL_ADD_TEST_PUBLIC_LINK_LIBRARIES})
        # Add the test
        # add_test("${FOLDER_NAME}/${WILL_ADD_TEST_NAME}" ${WILL_ADD_TEST_NAME})
        gtest_discover_tests(${WILL_ADD_TEST_NAME})
    endif()
endmacro(WILL_ADD_TEST)

# This macro will remove *_test.cc files from the source group.
# The usage of the macro is as follows:
# WILL_REMOVE_TEST_FILES(
#     SOURCE_LIST_VAR <source list variable>
# )
macro(WILL_REMOVE_TEST_FILES SOURCE_LIST_VAR)
    # Create a new empty list to store files that do not match the test file pattern
    set(new_sources "")
    # Iterate over the list of files (using variable expansion to get the list content)
    foreach(file ${${SOURCE_LIST_VAR}})
        # If the current file name does not match the test file pattern, add it to the new list
        if(NOT file MATCHES ".*_test\\.cc$")
            list(APPEND new_sources ${file})
        endif()
    endforeach()
    # Assign the processed new list back to the original variable
    set(${SOURCE_LIST_VAR} ${new_sources})
    # Clean-up.
    unset(new_sources)
endmacro(WILL_REMOVE_TEST_FILES)
