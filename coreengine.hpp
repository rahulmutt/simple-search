#ifndef __COREENGINE__HPP__
#define __COREENGINE__HPP__
#include "frequencymap.hpp"
#include<string>
#include<vector>

using namespace std;

class CoreEngine {
public:
    CoreEngine();
    ~CoreEngine();
    vector<string> populate(string&& dirname):
private:
    void process_file(string& filename);
    FrequencyMap mMap;
};
#endif

