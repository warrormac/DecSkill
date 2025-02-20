#ifndef FILTER_MODULE_H
#define FILTER_MODULE_H

#include "IModule.h"
#include <vector>
#include <thread>
#include <atomic>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <cstdint>

class FilterModule : public IModule {
public:
    using Callback = std::function<void(const std::vector<uint8_t>&)>;

    explicit FilterModule(Callback callback);
    ~FilterModule();

    void start() override;
    void stop() override;
    void receiveData(const std::vector<uint8_t>& data) override;

private:
    void run();
    bool containsSequence(const std::vector<uint8_t>& data);

    std::thread workerThread;
    std::atomic<bool> running{false};
    
    std::queue<std::vector<uint8_t>> buffer;
    std::mutex bufferMutex;
    std::condition_variable bufferCV;

    Callback sendDataCallback;
    const std::vector<uint8_t> targetSequence = {0x00, 0x01, 0x02};
};

#endif // FILTER_MODULE_H
