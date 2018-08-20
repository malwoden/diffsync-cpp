#pragma once

#include <experimental/filesystem>

namespace diffsync {

std::vector<unsigned char> 
readFile(std::experimental::filesystem::path path);

}
