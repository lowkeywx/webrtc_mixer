#include <iostream>

namespace ts{

class IMixer {
public:
    static IMixer* Create(int sampleRate, int channelCount);
    static void deleteMixer(IMixer*);
public:
    /**
     * @brief 
     * 
     * @param streamCount 流的数量
     * @param data 混音数据，每个流取一帧
     * @param lineSize 每个音频帧，一共有多少采样
     * @param mixData 混音之后的输出数据，需要外部开辟好内存
     */
    virtual int Mix(int streamCount, uint16_t* data[], int sampleCount, uint16_t* mixData) = 0;
protected:
    IMixer() = default;
    virtual ~IMixer() = default;
    IMixer(const IMixer&) = default;
};

}
