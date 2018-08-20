#include "Files.h"

#include <experimental/filesystem>
#include <fstream>

namespace fs = std::experimental::filesystem;

namespace diffsync {

std::vector<unsigned char> 
readFile(fs::path path)
{
    std::ifstream file{path, std::ifstream::binary};
    std::vector<unsigned char> data;

    if (file) {
        const auto size = fs::file_size(path);
        data.resize(size);
        file.read(reinterpret_cast<char*>(&data[0]), size);
    }

    return data;
}

}
