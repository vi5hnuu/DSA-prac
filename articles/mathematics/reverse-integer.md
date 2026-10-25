# Reverse Integer

::problem{slug=reverse-integer}

## Problem Statement

You are given a signed 32-bit integer `x`. Return the number formed by writing its digits in reverse order, keeping the sign. If the reversed value does not fit in the signed 32-bit range `[-2^31, 2^31 - 1]`, return `0` instead.

The problem also asks you to pretend the environment cannot store 64-bit integers.

### Examples

| Input | Output | Why |
|---|---|---|
| `x = 456` | `654` | digits reversed |
| `x = -78` | `-87` | sign is kept |
| `x = 900` | `9` | leading zeros of the result disappear |
| `x = 1999999999` | `0` | `9999999991` is larger than `2^31 - 1` |

### Constraints

- `-2^31 <= x <= 2^31 - 1`

:::callout{kind=tip}
`x % 10` gives the last digit and `x / 10` removes it. Feeding the digits into `num = num * 10 + digit` builds the reversed number. The only real difficulty is detecting overflow.
:::

## Approach: Pop and Push Digits

Repeatedly pop the last digit of `x` and push it onto the end of `num`:

1. `temp = val % 10` — the last digit (negative when `x` is negative in C++/Java, so the sign is carried along automatically).
2. `val /= 10` — drop that digit.
3. `num = num * 10 + temp` — append it.
4. After every step, if `num` has left the 32-bit range, return `0`.

`num` is declared as a 64-bit `long`, so the step that crosses the limit is still computed exactly and the check catches it.

:::code-tabs
```cpp
class Solution {
public:
    int reverse(int x) {
        long num = 0;

        int val = x;
        while (val) {
            int temp = val % 10;
            val /= 10;
            if (num || temp) num = num * 10 + temp;
            if ((x < 0 && num < INT_MIN) || (x > 0 && num > INT_MAX)) return 0;
        }
        return num;
    }
};
```
```java
class Solution {
    public int reverse(int x) {
        long num = 0;

        int val = x;
        while (val != 0) {
            int temp = val % 10;
            val /= 10;
            if (num != 0 || temp != 0) num = num * 10 + temp;
            if ((x < 0 && num < Integer.MIN_VALUE) || (x > 0 && num > Integer.MAX_VALUE)) return 0;
        }
        return (int) num;
    }
}
```
```python
class Solution:
    def reverse(self, x: int) -> int:
        INT_MIN, INT_MAX = -2**31, 2**31 - 1
        sign = -1 if x < 0 else 1
        num = 0

        # Python's % and // round toward -infinity, so work on the magnitude
        # and apply the sign to each digit, as C++/Java do automatically.
        val = abs(x)
        while val:
            temp = sign * (val % 10)
            val //= 10
            if num or temp:
                num = num * 10 + temp
            if (x < 0 and num < INT_MIN) or (x > 0 and num > INT_MAX):
                return 0
        return num
```
:::

**Complexity**

- **Time:** `O(d)` where `d ≤ 10` is the number of digits.
- **Space:** `O(1)`.

:::callout{kind=note}
The line `if (num || temp)` only skips the multiplication while `num` is still `0`; since `0 * 10 + 0` is `0` anyway, the result is the same without it.
:::

### Dry Run

`x = -78`

| val | temp | val after `/10` | num |
|---|---|---|---|
| -78 | -8 | -7 | -8 |
| -7 | -7 | 0 | -87 |

`num = -87` is inside the range, so the answer is `-87`.

## The 64-bit Restriction

The solution above stores `num` in a 64-bit `long`, which the problem statement asks you to avoid. It produces correct answers, but a strictly compliant solution must detect overflow *before* the multiplication happens.

:::details[How can the overflow be detected without a 64-bit variable?]
`num * 10 + temp` overflows exactly when `num > INT_MAX / 10`, or `num == INT_MAX / 10` and `temp > 7` (since `INT_MAX = 2147483647` ends in 7). For negatives the mirror condition is `num < INT_MIN / 10`, or `num == INT_MIN / 10` and `temp < -8`. Checking this before updating `num` keeps every value inside 32 bits.
:::

## Try It Yourself

```python runnable
class Solution:
    def reverse(self, x: int) -> int:
        INT_MIN, INT_MAX = -2**31, 2**31 - 1
        sign = -1 if x < 0 else 1
        num = 0

        # Python's % and // round toward -infinity, so work on the magnitude
        # and apply the sign to each digit, as C++/Java do automatically.
        val = abs(x)
        while val:
            temp = sign * (val % 10)
            val //= 10
            if num or temp:
                num = num * 10 + temp
            if (x < 0 and num < INT_MIN) or (x > 0 and num > INT_MAX):
                return 0
        return num


sol = Solution()
print(sol.reverse(456))  # 654
print(sol.reverse(-78))  # -87
print(sol.reverse(900))  # 9
print(sol.reverse(1999999999))  # 0
```
## Edge Cases

- **Trailing zeros** (`900`) become leading zeros and vanish: `9`.
- **`0`** returns `0`.
- **`-2^31`** reversed is `-8463847412`, outside the range, so the answer is `0`.
- **`1463847412`** reversed is `2147483641`, which *just* fits, so it is returned as is.

## Practice Questions

:::details[Why is no special handling needed for the sign in C++ or Java?]
In C++ and Java, `%` and `/` truncate toward zero, so for a negative `val` every `temp` is negative (or zero), and `num` is built as a negative number directly. For `-123`: `-3`, then `-32`, then `-321`.
:::

:::details[Why check the range after every digit, not only at the end?]
With a 64-bit `num` a single check at the end would also work, because 10 digits can never overflow 64 bits. Checking inside the loop is what you need once `num` is restricted to 32 bits, since the overflow must be caught at the step where it would happen.
:::
