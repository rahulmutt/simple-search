#include "utility.hpp"
#include<chrono>
#include<cerrno>
#include<dirent.h>

using namespace std::chrono;

double profile(function<void(void)> func) {
    auto start = high_resolution_clock::now();
    func();
    auto finish = high_resolution_clock::now();
    return duration_cast<nanoseconds>(finish - start).count() / 10e3;
}

vector<string> list_immediate_files(string const& dirname) {
    vector<string> filenames;
    DIR *target = opendir(dirname.c_str());
    if (target != NULL) {
        for (dirent *entry = readdir(target); 
             entry != NULL ;
             entry = readdir(target)) {
            if (entry->d_name[0] == '.' ||
                (entry->d_type & DT_DIR)) continue;
            filenames.push_back(dirname + "/" + string(entry->d_name));
        }
        closedir(target);
    }
    return filenames;
}

