cmake_minimum_required(VERSION 3.10)
project(MediaEngine_Modules_AudioProcess)
 
add_library(modules_audio_process STATIC 
logging/apm_data_dumper.cc
agc2/limiter.cc
agc2/interpolated_gain_curve.cc
agc2/fixed_digital_level_estimator.cc
)

target_compile_definitions(modules_audio_process PUBLIC WEBRTC_APM_DEBUG_DUMP=0)

target_include_directories(modules_audio_process PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(modules_audio_process PUBLIC ${CMAKE_SOURCE_DIR}/third_party/abseil-cpp)

