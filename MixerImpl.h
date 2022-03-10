#include <memory>
#include <list>
#include "IMixer.h"

#include "modules/audio_mixer/audio_mixer_impl.h"
#include "modules/audio_mixer/default_output_rate_calculator.h"

namespace ts{
    
class AudioSourceWrap;

class MixerImpl final: public IMixer{
public:
    MixerImpl(int sampleRate, int channelCount);
    ~MixerImpl();
public:
    int Mix(int streamCount, uint16_t* data[], int sampleCount, uint16_t* mixData) override;

private:
    int m_sampleRate{0};
    int m_channelCount{0};
    rtc::scoped_refptr<::webrtc::AudioMixerImpl> m_mixer;
    using AudioSourcePtr = std::shared_ptr<AudioSourceWrap>;
    std::list<AudioSourcePtr> m_sources;
};

}
