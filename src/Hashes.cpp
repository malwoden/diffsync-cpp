#include "Hashes.h"

#include <sstream>
#include <iomanip>

#include <openssl/md5.h>

namespace nconc {

// TODO: Replace: this is a really rubbish hashing algo
uint32_t
weakHash(const std::vector<unsigned char>& data) {
    uint32_t hash = 0;
    for (unsigned char c : data) {
        hash += c;
    }
    return hash;
}

uint32_t
rollWeakHash(uint32_t hash, unsigned char toRemove, unsigned char toAdd) {
    hash -= toRemove;
    hash += toAdd;
    return hash;
}

std::vector<unsigned char>
strongHash(const std::vector<unsigned char>& data) {
    std::vector<unsigned char> digest;
    digest.resize(MD5_DIGEST_LENGTH);

    MD5(&data[0], data.size(), &digest[0]);

    return digest;
}

std::string
hashToHexString(const std::vector<unsigned char>& data) {
    std::ostringstream stream;
    stream << std::hex << std::setfill('0');

    for (unsigned char c : data) {
        stream << std::setw(2) << static_cast<int>(c);
    }

    return stream.str();
}

}