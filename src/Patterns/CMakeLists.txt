cmake_minimum_required(VERSION 3.2)

# Add project folder into includes
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Configure Patterns static library
set(PATTERNS Patterns)
file(GLOB_RECURSE PATTERNS_SRC "*.cpp")
file(GLOB_RECURSE PATTERNS_HDR "*.h")
add_library(${PATTERNS} STATIC ${PATTERNS_SRC} ${PATTERNS_HDR})
target_link_libraries(${PATTERNS})

#Configure source groups
foreach(FILE ${PATTERNS_SRC} ${PATTERNS_HDR}) 
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
    string(REPLACE "/" "\\" GROUP "${GROUP}")

    if ("${FILE}" MATCHES ".*\\.cpp")
       set(GROUP "Source Files${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.h")
       set(GROUP "Header Files${GROUP}")
    endif()

    source_group("${GROUP}" FILES "${FILE}")
endforeach()