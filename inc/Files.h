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
    std::ifstream file{path, std::ifstream::binary};
    uint32_t totalbytes = 0;

    if (file) {
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

}
