#ifndef __FREQUENCY_MAP__HPP__
#define __FREQUENCY_MAP__HPP__
#include<cstdint>
#include<unordered_map>
#include<map>
#include<vector>
using namespace std;

typedef vector<pair<int, string*>> search_result; 

struct double_hash {
    uint64_t hash1;
    uint64_t hash2;
    const bool operator<(double_hash const& b) const;
};

class FrequencyMap {
public:
    search_result search(string const& query);
    void insert(char * const word, string * const index);
private:
    const double_hash _hash(const char* const input) const;

    map<double_hash, map<string*, int>> _map;
};
#endif
