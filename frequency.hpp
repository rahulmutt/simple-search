#ifndef __FREQUENCY__HPP__
#define __FREQUENCY__HPP__
#include<cstdint>
#include<map>
#include<vector>
using namespace std;

struct double_hash {
    uint64_t hash1;
    uint64_t hash2;
    const bool operator<(double_hash const& b) const;
};

typedef map<string*, int> ffreq_map;
typedef map<double_hash,ffreq_map> hash_tree;
typedef vector<pair<int, string*>> search_result;
extern hash_tree frequency_map;

double_hash _hash(const char* str);
void insert_word(char* word, string* index);
search_result search(string query);
void print(search_result result);

#endif
