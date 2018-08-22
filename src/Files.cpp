#include "Files.h"

#include <experimental/filesystem>
#include <fstream>
#include <iostream>

namespace diffsync {

std::vector<unsigned char>
readFile(const fs::path& path) {
    if (std::ifstream file{path, std::ifstream::binary}) {
        if (file.is_open()) {
            return std::vector<unsigned char>(
                std::istreambuf_iterator<char>(file),
                std::istreambuf_iterator<char>());
        }
    }

    return std::vector<unsigned char>();
}

}
