cmake_minimum_required(VERSION 3.10)
project(MediaEngine_Modules_AudioMixer)

set(TARGET_NAME modules_audio_mixer)
 
add_library(${TARGET_NAME} SHARED
./audio_frame_manipulator.cc
./audio_mixer_impl.cc
./default_output_rate_calculator.cc
./frame_combiner.cc
)

target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_SOURCE_DIR})
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/third_party/abseil-cpp)
target_link_libraries(${TARGET_NAME} PRIVATE rtc_base api audio modules_audio_process system_wrappers common_audio)
target_link_libraries(${TARGET_NAME} PRIVATE absl::flags_parse)

if(ANDROID)
        find_library(ANDROID_LOG_LIB log)
        target_link_libraries(${TARGET_NAME} PRIVATE ${ANDROID_LOG_LIB})
endif(ANDROID)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
    #add_executable(modules_audio_mixer_test audio_mixer_test.cc)
    #target_link_libraries(modules_audio_mixer_test PRIVATE ${TARGET_NAME})
endif()

