#include<iostream>
#include<fstream>
#include<string>

#include<algorithm>
#include<vector>
#include<chrono>
#include "frequency.h"

#include<cstring>
#include<dirent.h>
#include<cerrno>
#include<cstdint>

#define PROFILING
#define DEBUG

using namespace std;
using namespace std::chrono;

vector<string> files;

vector<string> list_files(string dirname) {
    vector<string> filenames;
    DIR *target = opendir(dirname.c_str());
    if (target == NULL) {
        cout << "Error: " << strerror(errno) << endl;
    } else {
        for (dirent *entry = readdir(target); 
             entry != NULL ;
             entry = readdir(target)) {
            if (entry->d_name[0] == '.') continue;
            filenames.push_back(dirname + "/" + string(entry->d_name));
        }
    }
    return filenames;
}


void process_file(string& filename)
{
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
                insert_word(word, &filename);
                word_pos = 0;
                memset(word, 0, 100 * sizeof(char));
            }
        }
    }

    if(word_pos > 0)
        insert_word(word, &filename);

    file.close();
}

double profile(function<void(void)> func) {
    auto start = high_resolution_clock::now();
    func();
    auto finish = high_resolution_clock::now();
    return duration_cast<nanoseconds>(finish - start).count() / 10e3;
}

string get_dir() {
    string dirname;
    cout << "Enter directory: ";
    getline(cin, dirname);
    cout << "Processing directory at " << dirname << endl;
    return dirname;
}

int main(int argc, char **argv)
{
    string dirname = get_dir();
    vector<string> files = list_files(dirname);
    auto process = [&files]() {
        for_each(files.begin(), files.end(), process_file);
    };

#ifdef PROFILING
    cout << "**Took " << profile(process) << "us to build search index." << endl;
#else
    process();
#endif
    string query;
    search_result result;
    cout << "**Enter :q to stop at anytime.**" << endl;
    do {

        cout << "Enter search query: ";
        cin >> query;
        auto query_index = [&query, &result] () {
            result = search(query);
        };
#ifdef PROFILING
        cout << "**Took " << profile(query_index) << "us to query tree" << endl;
#else
        query_index();
#endif
        print(result);

    } while (query != ":q");

    cout << "Exiting search engine...Done!" << endl;
    return 0;
}
