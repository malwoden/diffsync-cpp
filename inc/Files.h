#pragma once

#include <experimental/filesystem>
#include <vector>
#include <fstream>

namespace diffsync {

namespace fs = std::experimental::filesystem;

/**
 * Reads the file at \p path in one pass, returning the data vector.
 */
std::vector<unsigned char>
readFile(const fs::path& path);

/**
 * Like readFile(const fs::path& path, uint32_t blocksize, Fun blockCallback), but allowing
 * for the read to be offset from the file start.
 */
template<typename Fun>
int32_t
readFile(const fs::path& path, uint32_t blocksize, uint32_t offset, Fun blockCallback) {
    std::ifstream file{path, std::ifstream::binary};
    uint32_t totalbytes = 0;

    if (file) {
        file.seekg(offset);

        std::vector<unsigned char> data;
        data.resize(blocksize);
        while (file.read(reinterpret_cast<char*>(&data[0]), blocksize)) {
            blockCallback(data);
            totalbytes += blocksize;
        }

        // get any data left if the last block is less than blocksize bytes
        if (file.gcount() > 0) {
            data.resize(file.gcount());
            blockCallback(data);
            totalbytes += data.size();
        }
    }

    return totalbytes;
}

/**
 * Reads the data from \p path in \p blocksize chunks.
 *
 * For each chunk the \p blockCallback (function(std::vector<unsigned char>)) is invoked
 * with the data.
 *
 * Returns the total amount of data read.
 */
template<typename Fun>
int32_t
readFile(const fs::path& path, uint32_t blocksize, Fun blockCallback) {
    return readFile(path, blocksize, 0, blockCallback);
}

std::vector<unsigned char>
readBlock(const fs::path& path, uint32_t blocksize, uint32_t offset);

}
