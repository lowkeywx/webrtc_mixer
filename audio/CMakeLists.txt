cmake_minimum_required(VERSION 3.10)
project(MediaEngine_Audio)
 
add_library(audio OBJECT 
utility/channel_mixer.cc
utility/audio_frame_operations.cc
utility/channel_mixing_matrix.cc
)

target_include_directories(audio PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)
target_include_directories(audio PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../third_party/abseil-cpp)

