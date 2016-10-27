add_subdirectory(sequential)
add_subdirectory(tbb)
add_subdirectory(mpi_tbb)
add_subdirectory(mpi_farm)

set(SOURCE ${SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/IntegrationMethod.cpp
        PARENT_SCOPE)
set(HEADER ${HEADER}
        ${CMAKE_CURRENT_SOURCE_DIR}/IntegrationMethod.h
        PARENT_SCOPE)