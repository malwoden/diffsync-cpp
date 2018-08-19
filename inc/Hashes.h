#include <string>
#include <vector>
#include <cstdint>

namespace nconc {

uint32_t
weakHash(const std::vector<unsigned char>& data);

uint32_t
rollWeakHash(uint32_t hash, unsigned char toRemove, unsigned char toAdd);

std::vector<unsigned char>
strongHash(const std::vector<unsigned char>& data);
   
std::string
hashToHexString(const std::vector<unsigned char>& data);

}