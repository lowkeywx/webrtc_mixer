cmake_minimum_required(VERSION 3.10)
project(MediaEngine_Api)
 
add_library(api STATIC 
stats_types.cc
audio/channel_layout.cc
audio/audio_frame.cc
task_queue/task_queue_base.cc
)

target_include_directories(api PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(api PUBLIC ${CMAKE_SOURCE_DIR}/third_party/abseil-cpp)

#target_link_libraries(api PRIVATE rtc_base)

