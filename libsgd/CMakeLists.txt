cmake_minimum_required(VERSION 3.16)

project("libsgd")

add_library(libsgd INTERFACE)

#target_include_directories(libsgd INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
#target_link_libraries(libsgd INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/libsgd_static.lib)

# Assumes libsgd repos is in same dir as blitz3d,
# and x86-release libsgd_static target has been built.
# What could possibly go wrong?!
target_include_directories(libsgd INTERFACE ${CMAKE_SOURCE_DIR}/../libsgd/libsgd/include)
target_link_libraries(libsgd INTERFACE ${CMAKE_SOURCE_DIR}/../libsgd/cmake-build-windows-x86-release/libsgd/sgd_static.lib)
