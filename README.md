# 项目简介
该项目主要为了将webrtc中的音频处理模块提取成单独的代码库，以独立的库提供。目前，以完成混音模块的提取。后续会继续完成aec、ns、agc等模块的提取。main分之最低要求cpp17，如果需要使用cpp11版本需要切换到cpp11分之。但是，cpp11分之性能会稍稍降低。

# 使用方式
## submodule方式
```
cd 'SomeDir' //in your project
git submodule add https://github.com/lowkeywx/webrtc_mixer.git

```
> 需要主项目也使用cmake方式组织

## 编译成库
```
git clone https://github.com/lowkeywx/webrtc_mixer.git
cd webrtc_mixer
mkdir build && cd build
cmake .. && cmake --build .
or
cmake .. -DBUILD_SHARED=ON && cmake --build .
```

> 默认每帧，支持10ms。建议使用单声道、16000hz采样率。
> 如果需要增大每帧到20ms，需要修改 modules/audio_mixer/audio_mixer_impl.h 中 kFrameDurationInMs = 20; modules/audio_mixer/frame_combiner.cc 中       limiter_(static_cast<size_t>(24000), data_dumper_.get(), "AudioMixer")；modules/audio_processing/agc2/agc2_common.h 中 kFrameDurationMs = 20;

