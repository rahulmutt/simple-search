#ifndef __CLI__HPP__
#define __CLI__HPP__
#include "coreengine.hpp"
#include "frequencymap.hpp"
#include<string>

using namespace std;

class CliApp {
public:
    CliApp(int argc, char** argv);
    ~CliApp();
    int run();
private:
    string get_dir();
    void print(search_result result);
    vector<string> files;
    CoreEngine engine;
};
#endif
