#include "AsyncHasher.h"

#include <future>
#include <queue>

#include "Files.h"
#include "Hashes.h"

namespace diffsync {

std::vector<std::vector<unsigned char>>
asyncHash(const fs::path& filePath, uint32_t blockSize) {
    std::queue<std::future<std::vector<unsigned char>>> hashFutures;

    diffsync::readFile(filePath, blockSize,
            [&hashFutures] (const std::vector<unsigned char>& blockData) {

        auto future = std::async(std::launch::async, &diffsync::strongHash, blockData);
        hashFutures.push(std::move(future));
    });

    std::vector<std::vector<unsigned char>> hashes;
    hashes.reserve(hashFutures.size());

    while (hashFutures.size() > 0) {
        hashes.push_back(hashFutures.front().get());
        hashFutures.pop();
    }

    return hashes;
}

}
