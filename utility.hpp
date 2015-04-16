#ifndef __UTILITY__HPP__
#define __UTILITY__HPP__
#include<functional>
#include<string>

double profile(function<void(void)> func);
vector<string> list_immediate_files(string& dirname);
#endif
