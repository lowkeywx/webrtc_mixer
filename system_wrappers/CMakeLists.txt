cmake_minimum_required(VERSION 3.10)
project(MediaEngine_SystemWrappers)
 
add_library(system_wrappers OBJECT 
source/metrics.cc
source/field_trial.cc
)

target_include_directories(system_wrappers PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(system_wrappers PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../third_party/abseil-cpp)