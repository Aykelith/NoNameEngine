cmake_minimum_required(VERSION 3.2)
project(NNE)

### VERSION ###
set( NNE_MAJOR_VERSION    0 )
set( NNE_MINOR_VERSION    0 )
set( NNE_REVISION_VERSION 1 )

### User input #################################################################
set( NNE_BUILD_SHARED_LIBS true CACHE BOOL "Build shared library." )
################################################################################

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/;${CMAKE_MODULE_PATH}")
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

set(INCLUDE_PATH "${PROJECT_SOURCE_DIR}/include")
set(SOURCE_PATH "${PROJECT_SOURCE_DIR}/src")

include_directories(
    ${INCLUDE_PATH}
    ${OPENGL_INCLUDE_DIRS}
	${GLEW_INCLUDE_DIRS}
    SYSTEM "E:/Programming/Desktop/Libraries/glm"
)

file(
        GLOB_RECURSE
        SOURCES
        ${SOURCE_PATH}/*
)

add_definitions(-DNNE_DLL)
add_definitions(-DNNE_DLL_EXPORTS)

add_definitions(-DNNE_DEBUG)

if(NNE_BUILD_SHARED_LIBS)
    # Shared library
    message("SOURCES " ${SOURCES})
    add_library(NNE SHARED ${SOURCES})
    set_target_properties(NNE PROPERTIES DEBUG_POSTFIX -d)
else()
    # Static library

endif()

# set the output directory for SFML libraries
set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")

# Platform- and compiler-specific options.
if( WIN32 )
    #add_definitions( -DWIN32 )
    target_link_libraries(NNE
        ${GLEW_LIBRARIES}
        ${OPENGL_LIBRARIES}
    )

    if( CMAKE_COMPILER_IS_GNUCXX )
        if( NNE_BUILD_SHARED_LIBS )
            set_target_properties( NNE PROPERTIES PREFIX "" )
        endif()
        set_target_properties( NNE PROPERTIES IMPORT_SUFFIX ".a" )
    endif()
    set( SHARE_PATH "." )
endif()

if( CMAKE_CXX_COMPILER MATCHES ".*clang[+][+]" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang" )
    set( CMAKE_CXX_FLAGS "-std=c++14 -stdlib=libc++ -fvisibility=hidden -fvisibility-inlines-hidden -Wall -Wextra -Wshadow -Wconversion -Wunused-parameter -Wno-long-long -pedantic ${CMAKE_CXX_FLAGS}" )
    set( CMAKE_C_FLAGS "-Wall -Wextra -Wshadow -Wconversion -Wno-long-long -pedantic ${CMAKE_C_FLAGS}" )
elseif( CMAKE_COMPILER_IS_GNUCXX )
    set( CMAKE_CXX_FLAGS "-std=c++14 -fvisibility=hidden -fvisibility-inlines-hidden -Wall -Wextra -Wshadow -Wconversion -Wno-long-long -pedantic ${CMAKE_CXX_FLAGS}" )
    set( CMAKE_C_FLAGS "-Wall -Wextra -Wshadow -Wconversion -Wno-long-long -pedantic ${CMAKE_C_FLAGS}" )
endif()

#install(DIRECTORY ${PROJECT_SOURCE_DIR}/include DESTINATION ${PROJECT_BINARY_DIR})
install(FILES ${PROJECT_BINARY_DIR}/lib/NNE.dll DESTINATION "E:/Programming/Desktop/Apps/NoNameEngine/demo/rectangle/bin")
install(FILES ${PROJECT_BINARY_DIR}/lib/NNE.dll DESTINATION "E:/Programming/Desktop/Apps/NoNameEngine/demo/rectangle_uniforms/bin")
install(FILES ${PROJECT_BINARY_DIR}/lib/NNE.dll DESTINATION "E:/Programming/Desktop/Apps/NoNameEngine/demo/camera_moving/bin")
