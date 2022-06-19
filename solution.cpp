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
    - dp[i] = dp[i-1] if i is valid.
      - (...)-(s[i]) (single digit case)

    - dp[i] = dp[i-2] if s[i-1,i] is valid.
      - (...)-(s[i-1]s[i]) (two digit case)
    - in implemenation we use two variables
      to remember dp[i-2] and dp[i-1]

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
     - consider the case of "29"
       - for "2" there is no dp[0-1]=dp[-1].
         - that's why dp_minus_1 = 1 initiaily
         - dp[0] = 1
       - for "9"
         - 9 is valid
           - dp[1] = dp[1-1] = dp[0] = 0
           - we decode the string as 2-9
         - 29 is not valid so we don't add dp[1-2]
       - and indeed we only have one way to decode the
         string which is 2-9
  */
  auto dp_minus_1 = 1, dp_minus_2 = 1;
  for (auto i = 1; i < s.size(); i++)
  {
    /* for example "200"
       - i = 2
       - s[2] = "0", s[1..2] = "00" neither is valid
       - 2-00 or 20-0
    */
    if (!_isValid(s[i]) && !_isValid(s[i - 1], s[i]))
      return 0;

    /* if you can reach here that means
       - either s[i] or s[i-1][i] is valid
       - or both are valid
    */

    auto w = 0;
    /* carry over dp[i-1]
     */
    if (_isValid(s[i]))
      w += dp_minus_1;
    /* carry over dp[i-2]
     */
    if (_isValid(s[i - 1], s[i]))
      w += dp_minus_2;

    dp_minus_2 = dp_minus_1;
    dp_minus_1 = w;
  }

  return dp_minus_1;
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