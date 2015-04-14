#ifndef __COMMON__HPP___
#define __COMMON__HPP___
#include<vector>
#include<string>
#include<functional>
using namespace std;

vector<string> list_files(string& dirname);
void process_file(string& filename);
double profile(function<void(void)> func);
#endif

