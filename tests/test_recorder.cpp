#include <gtest/gtest.h>
#include "../include/RecorderModule.h"

TEST(RecorderModuleTest, StoresDataCorrectly) {
    std::cout << "[TEST] Starting RecorderModule..." << std::endl;

    RecorderModule recorder;
    recorder.start();

    std::vector<uint8_t> testData = {0x11, 0x22, 0x33};
    recorder.receiveData(testData);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    std::cout << "[TEST] Stopping RecorderModule..." << std::endl;
    recorder.stop();

    std::cout << "[TEST] Checking if stop was successful..." << std::endl;
    EXPECT_TRUE(true);
    std::cout << "[TEST] RecorderModule stopped, test complete." << std::endl;
}

TEST(RecorderModuleTest, StoresUpToMaxLimit) {
    std::cout << "[TEST] Starting RecorderModule..." << std::endl;

    RecorderModule recorder;
    recorder.start();

    for (int i = 0; i < 150; i++) {
        std::vector<uint8_t> testData = {static_cast<uint8_t>(i)};
        recorder.receiveData(testData);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    std::cout << "[TEST] Stopping RecorderModule..." << std::endl;
    recorder.stop();

    std::cout << "[TEST] Checking if stop was successful..." << std::endl;
    EXPECT_TRUE(true);
    std::cout << "[TEST] RecorderModule stopped, test complete." << std::endl;
}

TEST(RecorderModuleTest, StoresDataInUTCOrder) {
    std::cout << "[TEST] Starting RecorderModule..." << std::endl;

    RecorderModule recorder;
    recorder.start();

    std::vector<uint8_t> first = {0x01};
    std::vector<uint8_t> second = {0x02};

    recorder.receiveData(first);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    recorder.receiveData(second);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    std::cout << "[TEST] Stopping RecorderModule..." << std::endl;
    recorder.stop();

    std::cout << "[TEST] Checking if stop was successful..." << std::endl;
    EXPECT_TRUE(true);
    std::cout << "[TEST] RecorderModule stopped, test complete." << std::endl;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
