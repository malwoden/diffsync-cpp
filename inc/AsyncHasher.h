#pragma once

#include <experimental/filesystem>

#include <future>
#include <queue>

#include "DiffSync.h"
#include "Files.h"
#include "Hashes.h"

namespace diffsync {

namespace fs = std::experimental::filesystem;

/**
 * Reads the file in blocks from the current thread and calculates
 * the hash in backgrounds threads.
 *
 * Returns a collection of the hashes from the file.
 */
template <typename HashT, typename HashF>
auto
asyncHash(const fs::path& filePath, uint32_t blockSize, HashF hashFunction) {
    std::queue<std::future<HashT>> hashFutures;

    diffsync::readFile(filePath, blockSize,
            [&hashFutures, &hashFunction] (const std::vector<unsigned char>& blockData) {

        auto future = std::async(std::launch::async, hashFunction, blockData);
        hashFutures.push(std::move(future));
    });

    // function is called 'asyncHash' but it is actually more general than that,
    // it is a function that allows the caller to process blocks of a file
    // concurrently with a given function, so we will handle the void return case
    // in the event the function doens't return anything.
    if constexpr (!std::is_void<HashT>::value) {
        std::vector<HashT> hashes;
        hashes.reserve(hashFutures.size());

        while (hashFutures.size() > 0) {
            hashes.push_back(hashFutures.front().get());
            hashFutures.pop();
        }

        return hashes;
    } else {
        while (hashFutures.size() > 0) {
            hashFutures.front().get();
            hashFutures.pop();
        }
    }
}

/**
 * Reads the file in blocks and collects both the strong and the weak hashes.
 */
HashVector
asyncStrongAndWeakHash(const fs::path& filePath, uint32_t blockSize);

}