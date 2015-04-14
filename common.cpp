#include "common.hpp"
#include "frequency.hpp"
#include<iostream>
#include<dirent.h>
#include<fstream>
#include<chrono>
#include<cstring>
#include<cerrno>
using namespace std;
using namespace std::chrono;

vector<string> list_files(string& dirname) {
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
