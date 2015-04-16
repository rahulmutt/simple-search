#include "frequencymap.hpp"

SearchResult FrequencyMap::search(string query) {
    auto freqs = frequency_map[_hash(query.c_str())];
    search_result result;
    for (auto& it : freqs) {
        result.push_back(make_pair(it.second, it.first));
    }
    stable_sort(result.rbegin(), result.rend());
    return result;
}

void DoubleHash::insert(char* word, string* index) {
    word[0] = tolower(word[0]);
    _map[_hash(word)][index]++;
}

DoubleHash FrequencyMap::_hash(const char* str) {
    uint64_t h2 = 0;
    union { uint64_t h1; uint64_t u[8]; };
    h1 = strlen(str);
    for (int i = 0; *str; i++, str++) {
        u[i % 8] += *str + i + (*str >> ((h1 / (i + 1)) % 5));
        h2 += *str;
    }
    return {h1, h2};
}

const bool FrequencyMap::DoubleHash::operator<(DoubleHash const& b) const {
    if (this->hash1 < b.hash1) return true;
    if (this->hash1 > b.hash1) return false;
    if (this->hash2 < b.hash2) return true;
    if (this->hash2 > b.hash2) return false;
    return false;
};

