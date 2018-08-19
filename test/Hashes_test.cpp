#include "gtest/gtest.h"

#include "Hashes.h"

TEST(HashesTest, weakHash) {
    ASSERT_EQ(294, nconc::weakHash({'a', 'b', 'c'}));
}

TEST(HashesTest, rollWeakHash) {
    uint32_t hash = nconc::weakHash({'a', 'b', 'c'});
    ASSERT_EQ(297, nconc::rollWeakHash(hash, 'a', 'd'));

    ASSERT_EQ(nconc::weakHash({'b', 'c', 'd'}), nconc::rollWeakHash(hash, 'a', 'd'));
}

TEST(HashesTest, srongHash) {
    std::string hashed = nconc::hashToHexString(nconc::strongHash({'a', 'c', 'd'})); 

    ASSERT_EQ("37029430cfd06ae2a279cc1e2504e7c3", hashed);
}