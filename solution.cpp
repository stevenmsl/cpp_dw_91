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
    - dp[i] = dp[i-2] if i is valid.
      - we add s[i] to s[0..i-2] (single digit case)
      - we are evaluating the string s[0..i-2,i]
    - dp[i] = dp[i-1] if s[i-1,i] is valid.
      - we add s[i] to s[0..i-1] (two digit case)
      - we are evaluating the string s[0..i]
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
     - prevprev
       - dp[i-2]
     - prev
       - dp[i-1]
     - consider the case of "29"
       - for "2" there is no dp[0-2]=dp[-2].
         - that's why we need to set prevprev=1 to
           the the ball rolling
         - dp[0] = 1
       - for "9"
         - 9 is valid but there is no dp[1-2]=dp[-1].
           - that's why we need to set prevprev=1 to
             the the ball rolling
           - dp[1] = 1
         - 29 is not valid so we don't add dp[1-1]=dp[0]
       - and indeed we only have one way to decode the
         string which is 2-9
  */
  auto prevprev = 1, prev = 1;
  for (auto i = 1; i < s.size(); i++)
  {
    /* for example "200"
       - i = 2
       - s[2] = "0", s[1..2] = "00" neither is valid
    */
    if (!_isValid(s[i]) && !_isValid(s[i - 1], s[i]))
      return 0;

    /* if you can reach here that means
       - either s[i] or s[i-1][i] is valid
       - or both are valid
    */

    auto w = 0;
    /* carry over dp[i-2]
     */
    if (_isValid(s[i]))
      w += prevprev;
    /* carry over dp[i-1]
     */
    if (_isValid(s[i - 1], s[i]))
      w += prev;

    /* w records what you have approved */
    prevprev = prev;
    prev = w;
  }

  return prev;
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