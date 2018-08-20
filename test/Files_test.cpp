#include "gtest/gtest.h"

#include "Files.h"

namespace fs = std::experimental::filesystem;

TEST(FilesTest, readFile) {
    fs::path path("/bin/cat");
    std::vector<unsigned char> data = diffsync::readFile(path);
    ASSERT_TRUE(data.size() > 0);
}
