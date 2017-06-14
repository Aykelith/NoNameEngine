cmake_minimum_required(VERSION 2.8)
project ("Rectangle")

# REQUIRED LIBRARIES
################################################################################
# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.4 REQUIRED system window graphics)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
#####################################################1###########################

add_definitions(-DNNE_DLL)
add_definitions(-DNNE_DEBUG)

message(${GLEW_INCLUDE_DIRS} ${GLEW_LIBRARIES})

include_directories(
	"${PROJECT_SOURCE_DIR}/../../include"
	${OPENGL_INCLUDE_DIRS}
	${GLEW_INCLUDE_DIRS}
	${SFML_INCLUDE_DIR}
	SYSTEM "E:/Programming/Desktop/Libraries/glm"
)

# Compiler settings
################################################################################
# Detect compiler
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(USING_GCC TRUE)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(USING_CLANG TRUE)
endif()

# For GCC and Clang, enable C++11 support and add some other flags
if(USING_GCC OR USING_CLANG)
  add_compile_options(-std=c++14 -pedantic -Wall)
endif()
################################################################################

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_executable(
        "Rectangle"
        "main.cpp"
)

target_link_libraries(Rectangle
	${SFML_LIBRARIES}
	"${PROJECT_SOURCE_DIR}/../../builds/mingw63/lib/libNNE.a"
	${GLEW_LIBRARIES}
	${OPENGL_LIBRARIES}
)
