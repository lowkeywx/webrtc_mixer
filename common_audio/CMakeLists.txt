cmake_minimum_required(VERSION 3.10)
project(MediaEngine_CommonAudio)
 
add_library(common_audio STATIC 
wav_file.cc
audio_util.cc
wav_header.cc
)

target_include_directories(common_audio PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(common_audio PUBLIC ${CMAKE_SOURCE_DIR}/third_party/abseil-cpp)