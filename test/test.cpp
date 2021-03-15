#include <cmath>
#include <iostream>
#include <vector>
#include <utility>

#include <iterator>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>

using std::string;
// using std::map;
using std::vector;
using std::ifstream;
using std::istream;
using std::istream_iterator;
using std::stringstream;

using std::cout;
using std::endl;

string word1 = "hello1";
string word2 = "hello2";

int main() {
    string word1C = word1;
    string word2C = word2;
    std::transform(word1.begin(), word1.end(), word1C.begin(), ::toupper);
    cout << word1 << word1C << word2C;
    return false;
}