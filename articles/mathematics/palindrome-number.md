title : Palindrome Number

summary : Check whether an integer reads the same forwards and backwards. Compare converting it to a string with reversing the number mathematically, and see why negative numbers are never palindromes.

# Palindrome Number

::problem{slug=palindrome-number}

## Problem Statement

You are given an integer `x`. Decide whether it is a **palindrome**, meaning its decimal digits read the same from left to right as from right to left. Return `true` if it is, otherwise `false`.

A negative number is never a palindrome, because the minus sign appears only at the front.

### Examples

| Input | Output | Why |
|---|---|---|
| `x = 1331` | `true` | backwards it is still `1331` |
| `x = -44` | `false` | backwards it reads `44-` |
| `x = 50` | `false` | backwards it reads `05` |
| `x = 8` | `true` | a single digit always reads the same |

### Constraints

- `-2^31 <= x <= 2^31 - 1`

**Follow-up:** can you solve it without turning the number into a string?

:::callout{kind=tip}
A palindrome is unchanged by reversal. So either compare the digit string with itself from both ends, or build the reversed number and check whether it equals the original.
:::

## Approach 1: Compare as a String

Convert the number to its decimal string, then compare characters from both ends moving inward. Only the first half needs to be checked, since each comparison covers one character from each side.

For negative numbers the string starts with `-`, which can never match the last character (a digit), so they correctly return `false`.

:::code-tabs
```cpp
class Solution {
public:
    bool isPalindrome(int x) {
        string s = to_string(x);
        for (int i = 0, sz = s.length(); i < sz / 2; i++) {
            if (s[i] != s[sz - 1 - i]) return false;
        }
        return true;
    }
};
```
```java
class Solution {
    public boolean isPalindrome(int x) {
        String s = Integer.toString(x);
        for (int i = 0, sz = s.length(); i < sz / 2; i++) {
            if (s.charAt(i) != s.charAt(sz - 1 - i)) return false;
        }
        return true;
    }
}
```
```python
class Solution:
    def isPalindrome(self, x: int) -> bool:
        s = str(x)
        sz = len(s)
        for i in range(sz // 2):
            if s[i] != s[sz - 1 - i]:
                return False
        return True
```
:::

**Complexity**

- **Time:** `O(d)` where `d` is the number of digits (about 10 for a 32-bit integer).
- **Space:** `O(d)` for the string.

## Approach 2: Reverse the Number Mathematically

This answers the follow-up. Build the reversed number digit by digit:

1. Take the last digit with `val % 10`.
2. Remove it with `val /= 10`.
3. Append it to the reversed number: `rev = rev * 10 + digit`.

Then compare the reversed value with the original.

Two details make this correct for every 32-bit input:

- **Overflow:** reversing a large `int` can exceed the `int` range (e.g. `2147483647` reversed is `7463847412`), so `rev` and `val` are kept in a 64-bit integer.
- **Negative numbers:** in C++ and Java, `%` keeps the sign of the dividend, so reversing `-121` produces `-121` (every digit comes out negative). Multiplying the reversed value by `-1` for negative inputs turns it into `121`, which can never equal the negative `x`. So every negative number correctly returns `false`.

:::code-tabs
```cpp
class Solution {
public:
    bool isPalindrome(int x) {
        long rev = 0;
        long val = x;
        while (val) {
            int temp = val % 10;
            val /= 10;
            rev = rev * 10 + temp;
        }
        return ((x < 0 ? -1 : 1) * rev) == x;
    }
};
```
```java
class Solution {
    public boolean isPalindrome(int x) {
        long rev = 0;
        long val = x;
        while (val != 0) {
            int temp = (int) (val % 10);
            val /= 10;
            rev = rev * 10 + temp;
        }
        return ((x < 0 ? -1 : 1) * rev) == x;
    }
}
```
```python
class Solution:
    def isPalindrome(self, x: int) -> bool:
        rev = 0
        # Python's % and // round toward -infinity, so reverse the magnitude.
        # rev is then never negative, so a negative x can never match it.
        val = abs(x)
        while val:
            temp = val % 10
            val //= 10
            rev = rev * 10 + temp
        return rev == x
```
:::

**Complexity**

- **Time:** `O(d)`.
- **Space:** `O(1)`.

### Dry Run

`x = 1331`

| val | temp = val % 10 | val after `/10` | rev |
|---|---|---|---|
| 1331 | 1 | 133 | 1 |
| 133 | 3 | 13 | 13 |
| 13 | 3 | 1 | 133 |
| 1 | 1 | 0 | 1331 |

`rev == x`, so the answer is `true`.

## Try It Yourself

```python runnable
class Solution:
    def isPalindrome(self, x: int) -> bool:
        rev = 0
        # Python's % and // round toward -infinity, so reverse the magnitude.
        # rev is then never negative, so a negative x can never match it.
        val = abs(x)
        while val:
            temp = val % 10
            val //= 10
            rev = rev * 10 + temp
        return rev == x


sol = Solution()
print(sol.isPalindrome(1331))  # True
print(sol.isPalindrome(-44))  # False
print(sol.isPalindrome(50))  # False
print(sol.isPalindrome(8))  # True
```
## Comparison

| Approach | Time | Space |
|---|---|---|
| String comparison | `O(d)` | `O(d)` |
| Mathematical reversal | `O(d)` | `O(1)` |

## Edge Cases

- **Negative numbers** are never palindromes.
- **Numbers ending in 0** (other than `0` itself) are never palindromes, since no number starts with `0`.
- **`0`** and any single digit are palindromes.
- **Overflow:** the reversed value of a valid `int` may not fit in an `int`. Use a 64-bit variable.

## Practice Questions

:::details[Why does reversing -121 in C++ give -121 instead of 121?]
In C++ and Java, `-121 % 10` is `-1` and `-121 / 10` is `-12`. Every extracted digit is negative, so the reversed number is built as `-1, -12, -121`. Without the `(x < 0 ? -1 : 1)` factor it would equal the original and `-121` would wrongly be reported as a palindrome.
:::

:::details[Can you stop reversing halfway?]
Yes. Reverse only until the reversed half is at least as large as the remaining half. Then compare `val == rev` (even length) or `val == rev / 10` (odd length). This avoids overflow without needing a 64-bit variable.
:::
