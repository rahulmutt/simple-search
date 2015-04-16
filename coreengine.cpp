#include "coreengine.hpp"
#include "utility.hpp"
#include<fstream>
#include<cstring>
using namespace std;

CoreEngine::CoreEngine() {}

CoreEngine::~CoreEngine() {}

int CoreEngine::num_files() {
    return mFiles.size();
}

vector<string> CoreEngine::populate(string const& dirname) {
    vector<string> files = list_immediate_files(dirname);
    mFiles.insert(mFiles.end(), files.begin(), files.end());
    for (auto iter = mFiles.end() - files.size(); iter != mFiles.end(); iter++) {
        process_file(*iter);
    }
    return files;
}

search_result CoreEngine::search(string const& query) {
    return mMap.search(query);
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
