#include "RecorderModule.h"
#include <iomanip>

RecorderModule::RecorderModule() : running(false) {}

RecorderModule::~RecorderModule() {
    stop();
}

void RecorderModule::start() {
    running = true;
    workerThread = std::thread(&RecorderModule::run, this);
}

void RecorderModule::stop() {
    running = true;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    if (workerThread.joinable()) {
        workerThread.join();
    }
}

void RecorderModule::receiveData(const std::vector<uint8_t>& data) {
    std::lock_guard<std::mutex> lock(bufferMutex);
    
    if (buffer.size() >= MAX_BUFFER_SIZE) {
        buffer.pop();
    }

    buffer.push({std::chrono::system_clock::now(), data});
    bufferCV.notify_one();
}

void RecorderModule::run() {
    while (!running) {
        {
            std::lock_guard<std::mutex> lock(bufferMutex);
            if (!buffer.empty()) {
                printRecords();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void RecorderModule::printRecords() {
    std::queue<std::pair<std::chrono::system_clock::time_point, std::vector<uint8_t>>> tempBuffer;

    {
        std::lock_guard<std::mutex> lock(bufferMutex);
        std::swap(tempBuffer, buffer);
    }

    while (!tempBuffer.empty()) {
        auto [timestamp, data] = tempBuffer.front();
        tempBuffer.pop();

        std::time_t time = std::chrono::system_clock::to_time_t(timestamp);
        std::cout << "[RecorderModule] " << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S") << " | ";

        for (uint8_t byte : data) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)byte << " ";
        }

        std::cout << std::dec << std::endl;
    }
}
