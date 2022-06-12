#include "solution.h"
#include "util.h"
#include <unordered_map>
#include <algorithm> //lower_bound
#include <string>
#include <queue>
#include <sstream>
#include <functional>
#include <math.h>

using namespace sol213;
using namespace std;

/*takeaways
  - DP
    - decode 1 or 2 digits at a time
  - time complexity: O(n)
*/

int Solution::numDecodings(string s)
{
  /* we don't know how to decode 0 */
  if (s[0] == '0')
    return 0;
  if (s.size() == 1)
    return 1;

  /*
     - f1
       - carry over ways of decoding one digit
     - f2
       - carry over ways of decoding both one and
         two digits
     - consider the case of "29"
       - for "2" both f1 and f2 are 1 as it's not
         passible to have 2 digits
       - for "9"
         - 9 is valid so carry over f1 = 1
         - 29 is not valid so we can't count the f2 part
         - f2 = f1 = 1;
       - and indeed we only have one way to decode the
         string which is 2-9
  */
  auto f1 = 1, f2 = 1;
  for (auto i = 1; i < s.size(); i++)
  {
    /* for example "200" */
    if (!_isValid(s[i]) && !_isValid(s[i - 1], s[i]))
      return 0;
    auto w = 0;
    /* look at a single digit */
    if (_isValid(s[i]))
      w += f1;
    /* look at two digits */
    if (_isValid(s[i - 1], s[i]))
      w += f2;

    f1 = f2;
    f2 = w;
  }

  return f2;
}

bool Solution::_isValid(char c)
{
  return c != '0';
}
bool Solution::_isValid(char c1, char c2)
{
  if (c1 == '0')
    return false;
  auto num = (c1 - '0') * 10 + (c2 - '0');
  return num >= 10 && num <= 26;
}