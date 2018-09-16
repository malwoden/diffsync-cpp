#include "gtest/gtest.h"

#include "Files.h"

namespace fs = std::experimental::filesystem;

TEST(FilesTest, readFile) {
    fs::path path("testdata/1k_binary_blob");
    std::vector<unsigned char> data = diffsync::readFile(path);
    ASSERT_EQ(data.size(), 1024);
}

TEST(FilesTest, readFileMatchesBlockRead) {
    fs::path path("testdata/1k_binary_blob");
    std::vector<unsigned char> singleReadData = diffsync::readFile(path);

    std::vector<unsigned char> blockdata;

    int32_t readCount = diffsync::readFile(path, 600,
        [&blockdata] (const std::vector<unsigned char>& data) {
            blockdata.insert(blockdata.end(), data.begin(), data.end());
         });

    ASSERT_EQ(singleReadData, blockdata);
}

// TODO: parameterise these tests with TEST_P

TEST(FilesTest, readFileFunctorSmallIncrements) {
    fs::path path("testdata/1k_binary_blob");
    int callcount = 0;

    int32_t readCount = diffsync::readFile(path, 100,
        [&callcount] (const std::vector<unsigned char>& data) { callcount++; });

    ASSERT_EQ(readCount, 1024);
    ASSERT_EQ(callcount, 11);
}

TEST(FilesTest, readFileFunctorExactBlocksize) {
    fs::path path("testdata/1k_binary_blob");
    int callcount = 0;

    int32_t readCount = diffsync::readFile(path, 1024,
        [&callcount] (const std::vector<unsigned char>& data) { callcount++; });

    ASSERT_EQ(readCount, 1024);
    ASSERT_EQ(callcount, 1);
}


TEST(FilesTest, readFileFunctorLargerBlocksize) {
    fs::path path("testdata/1k_binary_blob");
    int callcount = 0;

    int32_t readCount = diffsync::readFile(path, 10000,
        [&callcount] (const std::vector<unsigned char>& data) { callcount++; });

    ASSERT_EQ(readCount, 1024);
    ASSERT_EQ(callcount, 1);
}

TEST(FilesTest, readFileFunctorOffsets) {
    fs::path path("testdata/1k_binary_blob");
    int callcount = 0;

    int32_t readCount = diffsync::readFile(path, 100, 512,
        [&callcount] (const std::vector<unsigned char>& data) { callcount++; });

    ASSERT_EQ(readCount, 512);
    ASSERT_EQ(callcount, 6);
}

TEST(FilesTest, readBlock) {
    fs::path path("testdata/1k_binary_blob");
    std::vector<unsigned char> data = diffsync::readBlock(path, 512, 512);
    ASSERT_EQ(data.size(), 512);
}