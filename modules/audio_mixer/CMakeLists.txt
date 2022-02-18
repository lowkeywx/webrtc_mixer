cmake_minimum_required(VERSION 3.10)
project(MediaEngine_Modules_AudioMixer)

set(TARGET_NAME webrtc_audio_mixer)
 
add_library(${TARGET_NAME} 
./audio_frame_manipulator.cc
./audio_mixer_impl.cc
./default_output_rate_calculator.cc
./frame_combiner.cc
)

target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/third_party/abseil-cpp)