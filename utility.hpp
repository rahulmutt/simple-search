#ifndef __UTILITY__HPP__
#define __UTILITY__HPP__
#include<vector>
#include<functional>
#include<string>
using namespace std;

double profile(function<void(void)> func);
vector<string> list_immediate_files(string const& dirname);
#endif
