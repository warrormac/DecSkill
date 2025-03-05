#include <gtest/gtest.h>
#include "../include/FilterModule.h"

TEST(FilterModuleTest, DetectsMatchingSequence) {
    bool found = false;

    FilterModule filter([&found](const std::vector<uint8_t>& data) {
        std::cout << "[TEST] Sequence detected and forwarded!" << std::endl;
        found = true;
    });

    std::vector<uint8_t> matchingData = {0x11, 0x22, 0x00, 0x01, 0x02, 0x33, 0x44};
    std::cout << "[TEST] Sending data: ";
    for (uint8_t byte : matchingData) std::cout << std::hex << (int)byte << " ";
    std::cout << std::endl;

    filter.receiveData(matchingData);

    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    EXPECT_TRUE(found);
}


TEST(FilterModuleTest, IgnoresNonMatchingSequence) {
    bool found = false;

    FilterModule filter([&found](const std::vector<uint8_t>& data) {
        found = true;
    });

    std::vector<uint8_t> nonMatchingData = {0x11, 0x22, 0x33, 0x44};
    filter.receiveData(nonMatchingData);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    EXPECT_FALSE(found);
}

TEST(FilterModuleTest, DetectsMultipleMatchingSequences) {
    int matchCount = 0;

    FilterModule filter([&matchCount](const std::vector<uint8_t>& data) {
        matchCount++;
    });

    // Send multiple arrays with {0x00, 0x01, 0x02}
    std::vector<std::vector<uint8_t>> testData = {
        {0x00, 0x01, 0x02, 0x11, 0x22},  // 1st match
        {0x33, 0x44, 0x00, 0x01, 0x02},  // 2nd match
        {0x55, 0x66, 0x77, 0x88},        // No match
        {0x99, 0x00, 0x01, 0x02, 0xAA},  // 3rd match
        {0xBB, 0xCC, 0xDD, 0xEE}         // No match
    };

    for (const auto& data : testData) {
        filter.receiveData(data);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Expect exactly 3 matches to be found
    EXPECT_EQ(matchCount, 3);
}

TEST(FilterModuleTest, HandlesMultipleMatches) {
    int matchCount = 0;
    
    FilterModule filter([&matchCount](const std::vector<uint8_t>& data) {
        std::cout << "[TEST] Match detected!" << std::endl;
        matchCount++;
    });

    std::vector<uint8_t> testData = {
        0x00, 0x01, 0x02, 0x11, 0x22,  // Match 1
        0x00, 0x01, 0x02, 0x33, 0x44,  // Match 2
        0x00, 0x01, 0x02               // Match 3
    };

    std::cout << "[TEST] Sending test data..." << std::endl;
    filter.receiveData(testData);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    std::cout << "[TEST] Expected 3 matches, got: " << matchCount << std::endl;
    EXPECT_EQ(matchCount, 3);
}



TEST(FilterModuleTest, FiltersLargeData) {
    bool found = false;
    FilterModule filter([&found](const std::vector<uint8_t>& data) {
        found = true;
    });

    std::vector<uint8_t> largeData(100, 0xFF);  // Fill with random bytes
    largeData[50] = 0x00;  // Insert sequence at random position
    largeData[51] = 0x01;
    largeData[52] = 0x02;

    filter.receiveData(largeData);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    EXPECT_TRUE(found);
}

TEST(FilterModuleTest, HandlesConcurrentData) {
    int matchCount = 0;
    FilterModule filter([&matchCount](const std::vector<uint8_t>& data) {
        matchCount++;
    });

    for (int i = 0; i < 20; i++) {
        std::vector<uint8_t> testData = {0x00, 0x01, 0x02, (uint8_t)i};
        filter.receiveData(testData);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    EXPECT_EQ(matchCount, 20);
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
