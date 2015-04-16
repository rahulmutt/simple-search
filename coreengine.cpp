#include "coreengine.hpp"
#include "utility.hpp"
#include<fstream>
#include<cstring>
using namespace std;

CoreEngine::CoreEngine() {}

CoreEngine::~CoreEngine() {}

vector<string> CoreEngine::populate(string& dirname) {
    vector<string> files = list_immediate_files(dirname);
    for (auto& file : files) {
        process_file(file);
    }
}

void CoreEngine::process_file(string& filename) {
    ifstream file;
    file.open(filename.c_str(), ifstream::in);
    int word_pos = 0;
    char word[100];
    memset(word, 0, 100 * sizeof(char));

    for (char c = file.get(); file.good(); c = file.get()) {
        if (isalpha(c)) {
            word[word_pos++] = c;
        } else {
            if (word_pos > 0) {
                mMap.insert(word, &filename);
                word_pos = 0;
                memset(word, 0, 100 * sizeof(char));
            }
        }
    }

    if(word_pos > 0)
        mMap.insert(word, &filename);

    file.close();
}
