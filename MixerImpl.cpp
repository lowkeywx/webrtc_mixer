#include <mutex>

#include "MixerImpl.h"

namespace ts{

    class AudioSourceWrap : public ::webrtc::AudioMixer::Source {

    struct AudioData{
        AudioData(uint16_t* a, int b): data(a),sampleCount(b){}
        uint16_t* data{nullptr};
        int sampleCount{0};
    };

    public:
        ~AudioSourceWrap() {
        }
        explicit AudioSourceWrap(int sampleRate, int channelCount)
            : sample_rate_hz_(sampleRate)
            , samples_per_channel_(sample_rate_hz_ / 50)
            , number_of_channels_(channelCount)
        {
        }

        AudioFrameInfo GetAudioFrameWithInfo(int target_rate_hz, ::webrtc::AudioFrame* frame) override {
            if(dataPool.empty()){
                frame->Mute();
                return AudioFrameInfo::kError;
            }
            dataLock.lock();
            auto audioData = dataPool.front();
            dataPool.pop_front();
            dataLock.unlock();
            
            memcpy(frame->mutable_data(),audioData.data, audioData.sampleCount * sizeof(audioData.data[0]));
            frame->samples_per_channel_ = samples_per_channel_;
            frame->num_channels_ = number_of_channels_;
            frame->sample_rate_hz_ = target_rate_hz;
            return AudioFrameInfo::kNormal;
        }

        int Ssrc() const override { return 0; }

        int PreferredSampleRate() const override { return sample_rate_hz_; }

        void pushData(uint16_t* data, int sampleCount) {
            std::lock_guard<std::mutex> lk(dataLock);
            //这里可能需要有一个专门的构造
            dataPool.push_back({data,sampleCount});
        }

    private:
        int sample_rate_hz_;
        int samples_per_channel_;
        int number_of_channels_;
        std::mutex dataLock;
        //这里也许不需要list
        std::list<AudioData> dataPool;
    };


    IMixer* IMixer::Create(int sampleRate, int channelCount){
        return new MixerImpl(sampleRate, channelCount);
    }

    void IMixer::deleteMixer(IMixer* ptr){
        assert(ptr);
        if (ptr) {
            delete ptr;
        }
    }

    MixerImpl::MixerImpl(int sampleRate, int channelCount)
        : m_sampleRate(sampleRate)
        , m_channelCount(channelCount)
    {
        m_mixer = ::webrtc::AudioMixerImpl::Create(
        std::unique_ptr<::webrtc::OutputRateCalculator>(new ::webrtc::DefaultOutputRateCalculator()), true);
    }

    MixerImpl::~MixerImpl(){
    }

    int MixerImpl::Mix(int streamCount ,uint16_t* data[], int sampleCount, uint16_t* mixData){
        int diff = streamCount - m_sources.size();
        //balance source
        if(diff > 0){
            for (int i = 0; i < diff; i++) {
                auto source = std::make_shared<AudioSourceWrap>(m_sampleRate, m_channelCount);
                m_sources.emplace_back(source);
                m_mixer->AddSource(source.get());
            }
        }else{
            for (int i = diff; i < 0; i++) {
                auto source = m_sources.back();
                m_sources.pop_back();
                m_mixer->RemoveSource(source.get());
            }
        }
        // 填充音频数据
        assert(streamCount == m_sources.size());
        auto it = m_sources.begin();
        for (size_t i = 0; i < streamCount; i++) {
            if(it != m_sources.end()){
                (*it)->pushData(data[i],sampleCount);
                it++;
            }
        }
        //执行混音
        ::webrtc::AudioFrame frame;
        m_mixer->Mix(m_channelCount, &frame);
        if (frame.muted()) {
            return -1;
        }
        memcpy(mixData, frame.data(), sampleCount * 2);
        return 0;
    }

}