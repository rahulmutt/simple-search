#include "cli.hpp"
#include "frequency.hpp"
#include "common.hpp"
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;
// *zammydragon!
vector<string> files; //@TODO: CHECK ONCE!

void print(SearchResult result) {
    if (result.size() <= 0) {
        cout << "Not found." << endl;
    } else {
        for (auto &it : result) {
            cout << (*(it.second)) << ": " << it.first << " results." << endl;
        }
    }
}

int search_cli(int argc, char **argv) {
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

string get_dir() {
    string dirname;
    cout << "Enter directory: ";
    getline(cin, dirname);
    cout << "Processing directory at " << dirname << endl;
    return dirname;
}
