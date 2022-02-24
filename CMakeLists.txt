cmake_minimum_required(VERSION 3.10)
project(MediaEngine)
 
set(CMAKE_CXX_STANDARD 11)

if(NOT CMAKE_SYSTEM_NAME MATCHES Windows)
    ADD_DEFINITIONS(-DWEBRTC_POSIX)
endif()

if(CMAKE_SYSTEM_NAME MATCHES iOS)
    message(==============now is iOS================)
    ADD_DEFINITIONS(-DWEBRTC_IOS)
    ADD_DEFINITIONS(-DWEBRTC_MAC)
elseif(CMAKE_SYSTEM_NAME MATCHES Darwin)
    message(==============now is Mac================)
    ADD_DEFINITIONS(-DWEBRTC_MAC)
elseif(CMAKE_SYSTEM_NAME MATCHES Windows)
    message(==============now is Windows================)
    ADD_DEFINITIONS(-DWEBRTC_WIN)
    ADD_DEFINITIONS(-DNOMINMAX)
    ADD_DEFINITIONS(-DWIN32_LEAN_AND_MEAN)
elseif(CMAKE_SYSTEM_NAME MATCHES Android)
    message(==============now is Android================)
    ADD_DEFINITIONS(-DWEBRTC_LINUX)
    ADD_DEFINITIONS(-DWEBRTC_ANDROID)
elseif(CMAKE_SYSTEM_NAME MATCHES Linux)
    message(==============now is linux================)
    ADD_DEFINITIONS(-DWEBRTC_LINUX)
endif()

add_subdirectory(third_party/abseil-cpp)
add_subdirectory(api)
add_subdirectory(audio)
add_subdirectory(modules)
add_subdirectory(common_audio)
add_subdirectory(rtc_base)
add_subdirectory(system_wrappers)

if(BUILD_SHARED)
set(LIBRARY_TYPE SHARED)
else()
set(LIBRARY_TYPE STATIC)
endif(BUILD_DYNAMIC)

add_library(ts_mixer ${LIBRARY_TYPE} MixerImpl.cpp 
$<TARGET_OBJECTS:modules_audio_mixer>
$<TARGET_OBJECTS:rtc_base>
$<TARGET_OBJECTS:api>
$<TARGET_OBJECTS:audio>
$<TARGET_OBJECTS:modules_audio_process>
$<TARGET_OBJECTS:system_wrappers>
$<TARGET_OBJECTS:common_audio>
)

target_link_libraries(ts_mixer PRIVATE absl::throw_delegate absl::strings)

target_include_directories(ts_mixer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ts_mixer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/abseil-cpp)

INSTALL ( TARGETS ts_mixer						DESTINATION lib )

