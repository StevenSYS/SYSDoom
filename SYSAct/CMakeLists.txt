cmake_minimum_required(VERSION 3.11)

project(SYSAct LANGUAGES C CXX VERSION 1.0)

if(WIN32)
	set(BUILD_SHARED_LIBS OFF)
else()
	option(BUILD_SHARED_LIBS "Build the libraries as shared libraries" ON)
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -MD")
set(CMAKE_C_FLAGS_DEBUG "-g -Wall")
set(CMAKE_C_FLAGS_RELEASE "-O2")
if (NOT CMAKE_C_COMPILER_ID MATCHES "Clang")
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -MD")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
if (NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s")
endif()

if(WIN32)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-subsystem,windows")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,-subsystem,windows")
endif()

add_subdirectory(src/submodules)

file(GLOB SOURCE_FILES "src/*.c")

find_package(SDL3 REQUIRED)
find_package(OpenGL REQUIRED)
include_directories(
	${OpenGL_INCLUDE_DIRS}
	"src/submodules"
)

configure_file(src/progInfo.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/progInfo.h @ONLY)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(
	${PROJECT_NAME}
	SDL3::SDL3
	${OPENGL_LIBRARY}
	json-c
	cimgui
)
set_property(TARGET ${PROJECT_NAME} PROPERTY BUILD_RPATH ".")
target_include_directories(${PROJECT_NAME} PRIVATE src)