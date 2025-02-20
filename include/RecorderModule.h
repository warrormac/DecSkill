#ifndef RECORDER_MODULE_H
#define RECORDER_MODULE_H

#include "IModule.h"
#include <vector>
#include <queue>
#include <mutex>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <chrono>
#include <iostream>

class RecorderModule : public IModule {
public:
    RecorderModule();
    ~RecorderModule();

    void start() override;
    void stop() override;
    void receiveData(const std::vector<uint8_t>& data) override;

private:
    void run();
    void printRecords();

    std::thread workerThread;
    std::atomic<bool> running;
    std::atomic<bool> exitFlag;  // **New flag to force shutdown**

    std::queue<std::pair<std::chrono::system_clock::time_point, std::vector<uint8_t>>> buffer;
    std::mutex bufferMutex;
    std::condition_variable bufferCV;

    const size_t MAX_BUFFER_SIZE = 100; 
};

#endif // RECORDER_MODULE_H
