#include "gtest/gtest.h"

#include <experimental/filesystem>

#include "AsyncHasher.h"
#include "Delta.h"
#include "Hashes.h"

using namespace diffsync;

// namespace fs = std::experimental::filesystem;

std::unordered_map<WeakHash, std::tuple<StrongHash, uint32_t>>
transformHashes(Hashes hashes) {
    std::unordered_map<WeakHash, std::tuple<StrongHash, uint32_t>> map(hashes.size());

    auto index = 0;
    for (auto&&[first, second] : hashes) {
        map[first] = std::make_tuple(second, index);
        index++;
    }

    return map;
}

TEST(DeltaTest, createAndApplyDelta) {
    uint32_t blockSize = 1024;
    fs::path original("testdata/original.bmp");
    fs::path updated("testdata/updated.bmp");
    // this results in the file being written to the testdata dir, which is not ideal
    fs::path deltaApplied("testdata/delta_applied.bmp");

    Hashes hashes = asyncStrongAndWeakHash(original, blockSize);
    ASSERT_EQ(88, hashes.size());

    Delta delta = calculateDelta(updated, blockSize, transformHashes(hashes));

    ASSERT_EQ(48, delta.changes_size());

    applyDelta(delta, original, deltaApplied, blockSize);

    auto updatedBytes = readFile(updated);
    auto deltaAppliedBytes = readFile(deltaApplied);
    ASSERT_EQ(updatedBytes, deltaAppliedBytes);
}