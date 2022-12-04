cmake_minimum_required(VERSION 3.0.0)
project(quicksort VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(TBB REQUIRED)
link_libraries(TBB::tbb)

add_library(my_qsort src/qsort.cpp)
target_compile_features(my_qsort PRIVATE cxx_std_11)

add_executable(par src/main.cpp)
target_compile_options(par PRIVATE -DALGO_PAR)

add_executable(seq src/main.cpp)
target_compile_options(seq PRIVATE -DALGO_SEQ)

add_executable(std src/main.cpp)
target_compile_options(std PRIVATE -DALGO_STD)

add_executable(io_bench src/main.cpp)
target_compile_options(io_bench PRIVATE -DALGO_IO_BENCH)

add_executable(valid src/test.cpp)
target_compile_options(valid PRIVATE)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ltbb")

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -Werror -D_GLIBCXX_DEBUG")
endif()


add_compile_definitions(__TBB_DYNAMIC_LOAD_ENABLED=0)

