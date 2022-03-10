cmake_minimum_required(VERSION 3.10)
project(MediaEngine_AudioMixer_RtcBase)
 
add_library(rtc_base OBJECT 
checks.cc
logging.cc
time_utils.cc
system_time.cc
string_utils.cc
string_encode.cc
platform_thread_types.cc
system/file_wrapper.cc
strings/string_builder.cc
synchronization/sequence_checker_internal.cc
)

target_include_directories(rtc_base PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(rtc_base PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../third_party/abseil-cpp)

if(CMAKE_SYSTEM_NAME MATCHES Windows)
    target_link_libraries(rtc_base PRIVATE winmm)
endif()

