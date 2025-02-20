#include "../include/GeneratorModule.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <random>

GeneratorModule::GeneratorModule(Callback callback)
    : running(false), sendDataCallback(callback) {}

GeneratorModule::~GeneratorModule() {
    stop();
}

void GeneratorModule::start() {
    running = true;
    std::cout << "[GeneratorModule] Starting thread..." << std::endl;
    workerThread = std::thread(&GeneratorModule::run, this);
}

void GeneratorModule::stop() {
    running = false;
    if (workerThread.joinable()) {
        workerThread.join();
    }
    std::cout << "[GeneratorModule] Stopped." << std::endl;
}

void GeneratorModule::run() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> lengthDist(1, 100);
    std::uniform_int_distribution<int> byteDist(0, 255);

    while (running) {
        std::vector<uint8_t> data(lengthDist(gen));
        for (auto &byte : data) {
            byte = static_cast<uint8_t>(byteDist(gen));
        }

        if (sendDataCallback) {
            sendDataCallback(data);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
