cmake_minimum_required(VERSION 3.10)
project(MediaEngine)
 
set(CMAKE_CXX_STANDARD 17)

ADD_DEFINITIONS(-DWEBRTC_POSIX)
ADD_DEFINITIONS(-DWEBRTC_MAC)

add_subdirectory(third_party/abseil-cpp)
add_subdirectory(api)
add_subdirectory(audio)
add_subdirectory(modules)
add_subdirectory(common_audio)
add_subdirectory(rtc_base)
add_subdirectory(system_wrappers)