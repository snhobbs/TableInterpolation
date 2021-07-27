cmake_minimum_required(VERSION 3.10.0)
#SET(CMAKE_VERBOSE_MAKEFILE ON)
project(Tests)
set(ProjectDirectory "${CMAKE_CURRENT_SOURCE_DIR}/..")
set(LibraryDirectory ${ProjectDirectory}/lib)
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON )
add_executable(${PROJECT_NAME})

# Target Options
set(CMAKE_CXX_STANDARD 20)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
#SET(CMAKE_CXX_COMPILER clang++-8)
#SET(CMAKE_CXX_COMPILER /usr/bin/g++-8)
target_compile_definitions(${PROJECT_NAME} PRIVATE TESTING)
target_compile_definitions(${PROJECT_NAME} PRIVATE UNITTESTING)
target_compile_definitions(${PROJECT_NAME} PRIVATE LINUX)
target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)

# Add test sources
set(TESTSRC ${CMAKE_CURRENT_SOURCE_DIR}/source)
#get_filename_component(TESTSRC source ABSOLUTE)
aux_source_directory(${TESTSRC} DIR_SRCS)
target_include_directories(${PROJECT_NAME} PUBLIC ${ProjectDirectory}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${TESTSRC} )

# System Includes to keep eclipse happy
include_directories("/usr/src")
#include_directories("/usr/include")
include_directories(SYSTEM /usr/lib)
include_directories(SYSTEM /home/simon/local/include)
include_directories(SYSTEM /usr/include)


# Dependancies
if(FALSE)
# Matplotlib & python
#find_package(matplotlib_cpp REQUIRED PATHS ${LibraryDirectory}/matplotlib-cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${LibraryDirectory}/matplotlib-cpp)
target_include_directories(${PROJECT_NAME} PUBLIC /usr/include/python3.8)
target_link_libraries(${PROJECT_NAME} python3.8)
endif()

## GTest
#set(gtest_DIR "${CMAKE_CURRENT_SOURCE_DIR}/extern/googletest/googletest")
set(gtest_DIR ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest)
target_include_directories(${PROJECT_NAME} PUBLIC "${gtest_DIR}/include")
target_link_directories(${PROJECT_NAME} PUBLIC ${gtest_DIR}/../lib)
target_link_libraries(${PROJECT_NAME} gtest)
target_link_libraries(${PROJECT_NAME} pthread)

# Santizers
if(FALSE)
  include(Sanitizers.cmake)
endif()

include(CompileOptions.cmake)
AddCompileOptions(${PROJECT_NAME})

#list(APPEND CMAKE_SYSTEM_INCLUDE_PATH "/usr/include")

target_sources(${PROJECT_NAME} PUBLIC ${DIR_SRCS})
add_test(
  NAME ${PROJECT_NAME}
  COMMAND ${PROJECT_NAME}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
