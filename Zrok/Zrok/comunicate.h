
//Capsalera de propietats: 

#ifndef __Properties__
#define __Properties__

#include <string>
#include <vector>

using namespace std;

bool Same(const string& a, const string& b);
bool Same(const char* a, const string& b);
bool Same(const string& a, const char* b);
int Roll(int min, int max);
void Tokenize(const string& line, vector<string>& arguments);

#endif //__Properties__