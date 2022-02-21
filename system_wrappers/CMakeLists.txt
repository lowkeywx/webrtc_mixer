cmake_minimum_required(VERSION 3.10)
project(MediaEngine_SystemWrappers)
 
add_library(system_wrappers STATIC 
source/metrics.cc
source/field_trial.cc
)

target_include_directories(system_wrappers PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(system_wrappers PUBLIC ${CMAKE_SOURCE_DIR}/third_party/abseil-cpp)