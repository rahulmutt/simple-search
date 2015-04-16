#include "frequencymap.hpp"
#include<algorithm>
#include<cstring>

search_result FrequencyMap::search(string const& query) {
    auto freqs = _map[_hash(query.c_str())];
    search_result result;
    for (auto& it : freqs) {
        result.push_back(make_pair(it.second, it.first));
    }
    stable_sort(result.rbegin(), result.rend());
    return result;
}

void FrequencyMap::insert(char * const word, string * const index) {
    word[0] = tolower(word[0]);
    _map[_hash(word)][index]++;
}

const double_hash FrequencyMap::_hash(const char * const input) const {
    uint64_t h2 = 0;
    union { uint64_t h1; uint64_t u[8]; };
    const char* str = input;
    h1 = strlen(str);
    for (int i = 0; *str; i++, str++) {
        u[i % 8] += *str + i + (*str >> ((h1 / (i + 1)) % 5));
        h2 += *str;
    }
    return {h1, h2};
}

const bool double_hash::operator<(double_hash const& b) const {
    if (this->hash1 < b.hash1) return true;
    if (this->hash1 > b.hash1) return false;
    if (this->hash2 < b.hash2) return true;
    if (this->hash2 > b.hash2) return false;
    return false;
};

