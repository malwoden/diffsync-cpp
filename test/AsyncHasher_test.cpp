#include "gtest/gtest.h"

#include "Hashes.h"
#include "AsyncHasher.h"

namespace fs = std::experimental::filesystem;

TEST(AsyncHasherTest, returnCount) {
    fs::path path("testdata/1k_binary_blob");
    auto hashes = diffsync::asyncHash(path, 100);

    std::vector<std::string> expectedHashes = {
        "5e7a73eb221c7a35a2852eccd0d27cd4",
        "e1d09567de47dcf761e715dd1fcdc5c8",
        "cd31626e4389b124c15ae69d276bae40",
        "eb1f542aa4ca72deb1525e439d98d3b5",
        "6acc6b393cf96aff740ae2ad80e5086a",
        "a6c928b3a824e09096fb04e0f4876938",
        "26d82d47471d4fd16a64b4b876fe6ca8",
        "1e5c8b9e1259d2c807cdb7f891be8b84",
        "dde4fedbad2e727cd35ff03e7d6b807f",
        "b8cab0615154664f31382970a3f4472c",
        "454e7f98c00dfc87324690663a92570e"};

    std::vector<std::string> actualHashes;
    std::transform(hashes.begin(), hashes.end(),
        std::back_inserter(actualHashes),
        &diffsync::hashToHexString);

    ASSERT_EQ(actualHashes, expectedHashes);
}
