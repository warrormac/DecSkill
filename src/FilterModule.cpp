#include "../include/FilterModule.h"
#include <iostream>


FilterModule::FilterModule(Callback callback) 
    : running(false), sendDataCallback(callback) {}

FilterModule::~FilterModule() {
    stop();
}

void FilterModule::start() {
    running = true;
    std::cout << "[FilterModule] Starting thread..." << std::endl;
    workerThread = std::thread(&FilterModule::run, this);
}

void FilterModule::stop() {
    running = false;
    bufferCV.notify_all();  // Wake up the thread to exit
    if (workerThread.joinable()) {
        workerThread.join();
    }
    std::cout << "[FilterModule] Stopped." << std::endl;
}

void FilterModule::receiveData(const std::vector<uint8_t>& data) {
    if (data.size() < targetSequence.size()) {
        std::cout << "[ERROR] Data too small, skipping comparison!" << std::endl;
        return;
    }

    for (size_t i = 0; i <= data.size() - targetSequence.size(); ++i) {
        if (std::equal(targetSequence.begin(), targetSequence.end(), data.begin() + i)) {
            std::cout << "[DEBUG] Match found at index: " << i << std::endl;
            if (sendDataCallback) {
                sendDataCallback(data);
            } else {
                std::cout << "[ERROR] sendDataCallback is NULL!" << std::endl;
            }
        }
    }
}

void FilterModule::run() {
    while (running) {
        std::vector<uint8_t> data;
        {
            std::unique_lock<std::mutex> lock(bufferMutex);
            bufferCV.wait(lock, [this] { return !buffer.empty() || !running; });

            if (!running) return;

            data = buffer.front();
            buffer.pop();
        }

        if (containsSequence(data)) {
            if (sendDataCallback) {
                sendDataCallback(data);
            }
        }
    }
}

bool FilterModule::containsSequence(const std::vector<uint8_t>& data) {
    if (data.size() < targetSequence.size()) return false;

    for (size_t i = 0; i <= data.size() - targetSequence.size(); ++i) {
        bool match = true;
        for (size_t j = 0; j < targetSequence.size(); j++) {
            if (data[i + j] != targetSequence[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            return true;
        }
    }
    
    return false;
}


