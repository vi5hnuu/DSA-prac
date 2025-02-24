/*
For an integer n, find the number of trailing zeroes in n!.

Examples :

Input: n = 5
Output: 1
Explanation: 5! = 120 so the number of trailing zero is 1.
Input: n = 4
Output: 0
Explanation: 4! = 24 so the number of trailing zero is 0.
Input: n = 43
Output: 9
Constraints:
1 <= n <= 109
*/

/*
The naive solution would be too fisrt calculate factorial
and the count zeros in the number
but the problem is for example xxxxxxxxxx such digit or digit even
greater then 20 would be difficult to store in a variable
*/

/*
The number of zero in factorial is equal to pairs of 5*2
and the fact is there will be more 2's than 5 in factorial we will count only 5's
1. every 5th number is div by 5 [5*x]
2. every 25th number is div by 5 [5*5*x where one 5 is counted by 1]
3. every 125th number is div by 5 [5*5*5*x where two 5 is counted by 1,2]

so for example 100
100/5 -> 20 5's
100/25 -> 4 extra 5's in 25 (5[counted by 1.]*5),50(5[counted by 1.]*5*2),75,100
100/125 -> end
*/
class Solution {
  public:
    int trailingZeroes(int n) {
        int total5=0;
        int divBy=5;
        while(n/divBy){
            total5+=(n/divBy);
            divBy*=5;
        }
        return total5;
    }
};