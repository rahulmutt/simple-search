#include "cli.hpp"
#include "utility.hpp"
#include<iostream>
#include<vector>
#include<algorithm>

void CliApp::print(search_result result) {
    if (result.size() <= 0) {
        cout << "Not found." << endl;
    } else {
        for (auto &it : result) {
            cout << (*(it.second)) << ": " << it.first << " results." << endl;
        }
    }
}

int CliApp::run() {
    string dirname = get_dir();
    auto process = [this, &dirname]() {
        this->engine.populate(dirname);
    };

    cout << "**Took " << profile(process) << "us to build search index." << endl;
    string query;
    search_result result;
    cout << "**Enter :q to stop at anytime.**" << endl;
    do {

        cout << "Enter search query: ";
        cin >> query;
        auto query_index = [this, &query, &result] () {
            result = this->engine.search(query);
        };
        cout << "**Took " << profile(query_index) << "us to query tree." << endl;
        print(result);

    } while (query != ":q");

    cout << "Exiting search engine...Done!" << endl;
    return 0;
}

CliApp::CliApp(int argc, char **argv) {}
CliApp::~CliApp() {}


string CliApp::get_dir() {
    string dirname;
    cout << "Enter directory: ";
    getline(cin, dirname);
    cout << "Processing directory at " << dirname << endl;
    return dirname;
}
