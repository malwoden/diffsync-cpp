#include "gtest/gtest.h"

#include "Hashes.h"

TEST(HashesTest, weakHash) {
    ASSERT_EQ(294, diffsync::weakHash({'a', 'b', 'c'}));
}

TEST(HashesTest, rollWeakHash) {
    uint32_t hash = diffsync::weakHash({'a', 'b', 'c'});
    ASSERT_EQ(297, diffsync::rollWeakHash(hash, 'a', 'd'));

    ASSERT_EQ(diffsync::weakHash({'b', 'c', 'd'}), diffsync::rollWeakHash(hash, 'a', 'd'));
}

TEST(HashesTest, srongHash) {
    std::string hashed = diffsync::hashToHexString(diffsync::strongHash({'a', 'c', 'd'}));

    ASSERT_EQ("37029430cfd06ae2a279cc1e2504e7c3", hashed);
}