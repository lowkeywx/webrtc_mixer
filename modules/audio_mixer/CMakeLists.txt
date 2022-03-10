cmake_minimum_required(VERSION 3.10)
project(MediaEngine_Modules_AudioMixer)

set(TARGET_NAME modules_audio_mixer)
 
add_library(${TARGET_NAME} OBJECT
./audio_frame_manipulator.cc
./audio_mixer_impl.cc
./default_output_rate_calculator.cc
./frame_combiner.cc
)

target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../)
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../third_party/abseil-cpp)

target_link_libraries(${TARGET_NAME} PRIVATE absl::flags_parse)
target_compile_definitions(${TARGET_NAME} PRIVATE WEBRTC_APM_DEBUG_DUMP=0)

if(ANDROID)
        find_library(ANDROID_LOG_LIB log)
        target_link_libraries(${TARGET_NAME} PRIVATE ${ANDROID_LOG_LIB})
endif(ANDROID)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
    #add_executable(modules_audio_mixer_test audio_mixer_test.cc)
    #target_link_libraries(modules_audio_mixer_test PRIVATE ${TARGET_NAME})
endif()

