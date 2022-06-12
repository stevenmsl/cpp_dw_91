#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <string>

using namespace std;
namespace sol213
{

  class Solution
  {
  private:
    bool _isValid(char c);
    bool _isValid(char c1, char c2);

  public:
    int numDecodings(string s);
  };
}
#endif