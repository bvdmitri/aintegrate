cmake_minimum_required(VERSION 2.8)
project(integrate CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_find")

find_package(TBB REQUIRED)
find_package(MPI REQUIRED)

include_directories(${MPI_INCLUDE_PATH})
include_directories(${TBB_INCLUDE_DIRS})

add_subdirectory(src)

set(HEADER ${HEADER} ${CMAKE_CURRENT_SOURCE_DIR}/functions.h)

##-------------------------------------------------------------------------------------------##
##-------------------------------------------------------------------------------------------##
set(SOURCE_SEQUENTIAL ${SOURCE} ${HEADER} ${CMAKE_CURRENT_SOURCE_DIR}/sequential.cpp)
add_executable(sequential ${SOURCE_SEQUENTIAL} ${HEADER})
target_link_libraries(sequential ${TBB_LIBRARY} ${TBB_MALLOC_LIBRARY} -ltbb ${MPI_LIBRARIES})
set_property(TARGET sequential PROPERTY CXX_STANDARD 11)
set_property(TARGET sequential PROPERTY CXX_STANDARD_REQUIRED ON)
##-------------------------------------------------------------------------------------------##
##-------------------------------------------------------------------------------------------##
set(SOURCE_TBB ${SOURCE} ${HEADER} ${CMAKE_CURRENT_SOURCE_DIR}/tbb.cpp)
add_executable(tbb ${SOURCE_TBB} ${HEADER})
target_link_libraries(tbb ${TBB_LIBRARY} ${TBB_MALLOC_LIBRARY} -ltbb ${MPI_LIBRARIES})
set_property(TARGET tbb PROPERTY CXX_STANDARD 11)
set_property(TARGET tbb PROPERTY CXX_STANDARD_REQUIRED ON)
##-------------------------------------------------------------------------------------------##
##-------------------------------------------------------------------------------------------##
set(SOURCE_MPI_TBB ${SOURCE} ${HEADER} ${CMAKE_CURRENT_SOURCE_DIR}/mpi_tbb.cpp)
add_executable(mpi_tbb ${SOURCE_MPI_TBB} ${HEADER})
target_link_libraries(mpi_tbb ${TBB_LIBRARY} ${TBB_MALLOC_LIBRARY} -ltbb ${MPI_LIBRARIES})
set_property(TARGET mpi_tbb PROPERTY CXX_STANDARD 11)
set_property(TARGET mpi_tbb PROPERTY CXX_STANDARD_REQUIRED ON)
##-------------------------------------------------------------------------------------------##
##-------------------------------------------------------------------------------------------##
set(SOURCE_MPI_FARM ${SOURCE} ${HEADER} ${CMAKE_CURRENT_SOURCE_DIR}/mpi_farm.cpp)
add_executable(mpi_farm ${SOURCE_MPI_FARM} ${HEADER})
target_link_libraries(mpi_farm ${TBB_LIBRARY} ${TBB_MALLOC_LIBRARY} -ltbb ${MPI_LIBRARIES})
set_property(TARGET mpi_farm PROPERTY CXX_STANDARD 11)
set_property(TARGET mpi_farm PROPERTY CXX_STANDARD_REQUIRED ON)
##-------------------------------------------------------------------------------------------##
##-------------------------------------------------------------------------------------------##