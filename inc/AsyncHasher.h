#pragma once

#include <experimental/filesystem>

namespace diffsync {

namespace fs = std::experimental::filesystem;

/**
 * Reads the file in blocks from the current thread and calculates
 * the hash in backgrounds threads.
 *
 * Returns a collection of the hashes from the file.
 */
std::vector<std::vector<unsigned char>>
asyncHash(const fs::path& filePath, uint32_t blockSize);

}