#ifndef __FREQUENCY_MAP__HPP__
#define __FREQUENCY_MAP__HPP__
#include<cstdint>
#include<map>
#include<vector>
using namespace std;

class FrequencyMap {
public:
    SearchResult search(string query);
    void insert(char* word, string* index);
private:
    DoubleHash _hash(const char* str);
    class DoubleHash {
        uint64_t hash1;
        uint64_t hash2;
        const bool operator<(DoubleHash const& b) const;
    };
    typedef map<string*, int> ffreq_map;
    typedef map<DoubleHash,ffreq_map> hash_tree;
    typedef vector<pair<int, string*>> SearchResult;
    hash_tree _map;
};
#endif
