# Add Binary

::problem{slug=add-binary}

## Problem Statement

Two non-negative numbers are given as binary strings `a` and `b`. Return their sum, also written as a binary string.

### Examples

| Input | Output | Why |
|---|---|---|
| `a = "101", b = "11"` | `"1000"` | 5 + 3 = 8 |
| `a = "0", b = "0"` | `"0"` | 0 + 0 = 0 |
| `a = "1111", b = "1"` | `"10000"` | 15 + 1 = 16 |

### Constraints

- `1 <= a.length, b.length <= 10^4`
- Both strings contain only the characters `'0'` and `'1'`.
- Neither string has leading zeros, except the string `"0"` itself.

:::callout{kind=tip}
Do exactly what you do on paper: add column by column from the rightmost digit, keep a carry, and write each result digit on the left of the answer. With strings up to 10^4 characters, converting to a built-in integer type would overflow.
:::

## Approach: Column-by-Column Addition with Carry

Walk over positions `i = 0, 1, 2, …` counted **from the right end** of each string:

- The digit of `a` at that position is `a[l1 - i - 1]` if that index is valid, otherwise `0` (the shorter string is padded with zeros).
- Same for `b`.
- `sm = digitA + digitB + carry` is between `0` and `3`.
- The result digit is `sm % 2`, and the new carry is `sm / 2`.

After the longest string is used up, a leftover carry of `1` becomes an extra leading `1`.

:::code-tabs
```cpp
class Solution {
public:
    string addBinary(string a, string b) {
        int l1 = a.length();
        int l2 = b.length();
        int len = max(l1, l2);

        string sum = "";
        int carry = 0;
        for (int i = 0; i < len; i++) {
            int fromEndIdxL1 = l1 - i - 1, fromEndIdxL2 = l2 - i - 1;

            int sm = ((fromEndIdxL1) >= 0 ? a[fromEndIdxL1] - '0' : 0) +
                     ((fromEndIdxL2) >= 0 ? b[fromEndIdxL2] - '0' : 0) + carry;
            carry = sm / 2;
            sm = sm % 2;
            sum = to_string(sm) + sum;
        }
        if (carry) {
            sum = to_string(carry) + sum;
        }

        return sum;
    }
};
```
```java
class Solution {
    public String addBinary(String a, String b) {
        int l1 = a.length();
        int l2 = b.length();
        int len = Math.max(l1, l2);

        StringBuilder sum = new StringBuilder();
        int carry = 0;
        for (int i = 0; i < len; i++) {
            int fromEndIdxL1 = l1 - i - 1, fromEndIdxL2 = l2 - i - 1;

            int sm = (fromEndIdxL1 >= 0 ? a.charAt(fromEndIdxL1) - '0' : 0) +
                     (fromEndIdxL2 >= 0 ? b.charAt(fromEndIdxL2) - '0' : 0) + carry;
            carry = sm / 2;
            sm = sm % 2;
            sum.append(sm);
        }
        if (carry != 0) {
            sum.append(carry);
        }

        return sum.reverse().toString();
    }
}
```
```python
class Solution:
    def addBinary(self, a: str, b: str) -> str:
        l1, l2 = len(a), len(b)
        length = max(l1, l2)

        digits = []
        carry = 0
        for i in range(length):
            from_end_idx_l1, from_end_idx_l2 = l1 - i - 1, l2 - i - 1

            sm = (int(a[from_end_idx_l1]) if from_end_idx_l1 >= 0 else 0) + \
                 (int(b[from_end_idx_l2]) if from_end_idx_l2 >= 0 else 0) + carry
            carry = sm // 2
            sm = sm % 2
            digits.append(str(sm))
        if carry:
            digits.append(str(carry))

        return "".join(reversed(digits))
```
:::

:::callout{kind=note}
The C++ version prepends each digit with `sum = to_string(sm) + sum`, which copies the whole string every time, so the loop costs `O(n²)` overall. The Java and Python versions append digits and reverse once at the end, which keeps it `O(n)`. In C++ you get the same effect with `sum.push_back('0' + sm)` and a final `reverse(sum.begin(), sum.end())`.
:::

**Complexity** (with append-then-reverse)

- **Time:** `O(max(l1, l2))`.
- **Space:** `O(max(l1, l2))` for the result.

### Dry Run

`a = "101"`, `b = "11"`

| i | digit of a | digit of b | carry in | sm | result digit | carry out | sum so far |
|---|---|---|---|---|---|---|---|
| 0 | 1 | 1 | 0 | 2 | 0 | 1 | `0` |
| 1 | 0 | 1 | 1 | 2 | 0 | 1 | `00` |
| 2 | 1 | – (0) | 1 | 2 | 0 | 1 | `000` |
| end | | | | | | 1 | `1000` |

## Try It Yourself

```python runnable
class Solution:
    def addBinary(self, a: str, b: str) -> str:
        l1, l2 = len(a), len(b)
        length = max(l1, l2)

        digits = []
        carry = 0
        for i in range(length):
            from_end_idx_l1, from_end_idx_l2 = l1 - i - 1, l2 - i - 1

            sm = (int(a[from_end_idx_l1]) if from_end_idx_l1 >= 0 else 0) + \
                 (int(b[from_end_idx_l2]) if from_end_idx_l2 >= 0 else 0) + carry
            carry = sm // 2
            sm = sm % 2
            digits.append(str(sm))
        if carry:
            digits.append(str(carry))

        return "".join(reversed(digits))


sol = Solution()
print(sol.addBinary("101", "11"))  # 1000
print(sol.addBinary("0", "0"))  # 0
print(sol.addBinary("1111", "1"))  # 10000
```
## Edge Cases

- **Different lengths:** the missing digits of the shorter string count as `0`.
- **Final carry:** `"1" + "1"` must give `"10"`, not `"0"`.
- **Both zero:** `"0" + "0"` gives `"0"` (no carry is added).

## Practice Questions

:::details[What is the largest value sm can take, and why?]
`3`: both digits are `1` and the carry is `1`. That gives result digit `1` and carry `1`.
:::

:::details[How would you add two numbers written in base k instead of base 2?]
Replace `2` by `k`: the result digit is `sm % k` and the carry is `sm / k`. Everything else stays the same.
:::
