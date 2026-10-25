# Longest Substring Without Repeating Characters

::problem{slug=longest-substring-without-repeating-characters}

## Problem Statement

Given a string `s`, return the length of the longest **substring** (a contiguous block of characters) in which no character appears more than once.

### Examples

| Input | Output | Why |
|---|---|---|
| `s = "abcaefc"` | `5` | `"bcaef"` has no repeats |
| `s = "zzzz"` | `1` | every substring longer than 1 repeats `z` |
| `s = "dvdf"` | `3` | `"vdf"` |
| `s = ""` | `0` | empty string |

Note that the answer must be contiguous: in `"dvdf"`, the letters `d, v, f` without the middle `d` do not form a substring.

### Constraints

- `0 <= s.length <= 5 * 10^4`
- `s` may contain English letters, digits, symbols and spaces.

:::callout{kind=tip}
Keep a **window** `[start, i]` that never contains a repeated character. When `s[i]` already appears inside the window, the window must start just after that earlier occurrence. The answer is the largest window size ever seen.
:::

## Approach 1: Scan Back for the Repeat — O(n²)

For every end index `i`, walk backwards from `i - 1` down to the current window start (`last_startrepeatingIndex`) looking for `s[i]`:

- If `s[j] == s[i]` is found, the window can no longer reach past `j`, so the new window start is `j + 1`. The longest valid window ending at `i` is then `i - j` characters long.
- While no repeat is found, the window `[j, i]` is valid, so its length `i - j + 1` is a candidate.

:::code-tabs
```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int len = s.length();
        if (!len) return 0;
        int last_startrepeatingIndex = 0; // just next index of repeating char (from start index)

        int maxNonRepLen = 1;
        for (int i = 0; i < len; i++) {
            for (int j = i - 1; j >= last_startrepeatingIndex; j--) {
                if (s[i] == s[j]) {
                    last_startrepeatingIndex = j + 1;
                    maxNonRepLen = max(maxNonRepLen, i - j);
                    break;
                } else {
                    maxNonRepLen = max(maxNonRepLen, i - j + 1);
                }
            }
        }
        return maxNonRepLen;
    }
};
```
```java
class Solution {
    public int lengthOfLongestSubstring(String s) {
        int len = s.length();
        if (len == 0) return 0;
        int last_startrepeatingIndex = 0; // just next index of repeating char (from start index)

        int maxNonRepLen = 1;
        for (int i = 0; i < len; i++) {
            for (int j = i - 1; j >= last_startrepeatingIndex; j--) {
                if (s.charAt(i) == s.charAt(j)) {
                    last_startrepeatingIndex = j + 1;
                    maxNonRepLen = Math.max(maxNonRepLen, i - j);
                    break;
                } else {
                    maxNonRepLen = Math.max(maxNonRepLen, i - j + 1);
                }
            }
        }
        return maxNonRepLen;
    }
}
```
```python
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        length = len(s)
        if not length:
            return 0
        last_startrepeating_index = 0  # just next index of repeating char (from start index)

        max_non_rep_len = 1
        for i in range(length):
            for j in range(i - 1, last_startrepeating_index - 1, -1):
                if s[i] == s[j]:
                    last_startrepeating_index = j + 1
                    max_non_rep_len = max(max_non_rep_len, i - j)
                    break
                else:
                    max_non_rep_len = max(max_non_rep_len, i - j + 1)
        return max_non_rep_len
```
:::

**Complexity**

- **Time:** `O(n · k)` where `k` is the longest window, which is at most `n` — so `O(n²)` in the worst case. Since a window can never be longer than the number of distinct characters, `k` is also bounded by the alphabet size.
- **Space:** `O(1)`.

## Approach 2: Remember the Last Index of Each Character — O(n)

Instead of scanning back, store in a hash map the **last index** where each character was seen. `repIndex` is the start of the current window.

For each `i`:

- If `s[i]` has not been seen, or was last seen **before** `repIndex` (outside the window), the window simply grows: candidate length `i - repIndex + 1`.
- Otherwise `s[i]` repeats inside the window. Move the start to just after the previous occurrence: `repIndex = elIndex[s[i]] + 1`. The code compares `i - repIndex` here. That is one less than the real window length, but it never matters: the window has just *shrunk*, so its length cannot exceed the best length already recorded.
- Record `elIndex[s[i]] = i`.

:::code-tabs
```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int len = s.length();
        if (!len) return 0;

        unordered_map<int, int> elIndex; // char -> last index

        // eg if repeat at index [1,7] then repIndex=2
        int repIndex = 0;

        int maxNonRepLen = 1;
        for (int i = 0; i < len; i++) {
            if (!elIndex.count(s[i]) || (elIndex.count(s[i]) && elIndex[s[i]] < repIndex)) {
                maxNonRepLen = max(maxNonRepLen, i - repIndex + 1);
            } else {
                repIndex = elIndex[s[i]] + 1;
                maxNonRepLen = max(maxNonRepLen, i - repIndex);
            }
            elIndex[s[i]] = i;
        }
        return maxNonRepLen;
    }
};
```
```java
class Solution {
    public int lengthOfLongestSubstring(String s) {
        int len = s.length();
        if (len == 0) return 0;

        Map<Character, Integer> elIndex = new HashMap<>(); // char -> last index

        // eg if repeat at index [1,7] then repIndex=2
        int repIndex = 0;

        int maxNonRepLen = 1;
        for (int i = 0; i < len; i++) {
            char c = s.charAt(i);
            if (!elIndex.containsKey(c) || elIndex.get(c) < repIndex) {
                maxNonRepLen = Math.max(maxNonRepLen, i - repIndex + 1);
            } else {
                repIndex = elIndex.get(c) + 1;
                maxNonRepLen = Math.max(maxNonRepLen, i - repIndex);
            }
            elIndex.put(c, i);
        }
        return maxNonRepLen;
    }
}
```
```python
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        length = len(s)
        if not length:
            return 0

        el_index = {}  # char -> last index

        # eg if repeat at index [1,7] then rep_index=2
        rep_index = 0

        max_non_rep_len = 1
        for i in range(length):
            if s[i] not in el_index or el_index[s[i]] < rep_index:
                max_non_rep_len = max(max_non_rep_len, i - rep_index + 1)
            else:
                rep_index = el_index[s[i]] + 1
                max_non_rep_len = max(max_non_rep_len, i - rep_index)
            el_index[s[i]] = i
        return max_non_rep_len
```
:::

**Complexity**

- **Time:** `O(n)` on average — one pass with `O(1)` hash map operations.
- **Space:** `O(min(n, alphabet size))` for the map.

### Dry Run

`s = "abcaefc"`

| i | s[i] | last seen | repIndex after | window | length | best |
|---|---|---|---|---|---|---|
| 0 | a | – | 0 | `a` | 1 | 1 |
| 1 | b | – | 0 | `ab` | 2 | 2 |
| 2 | c | – | 0 | `abc` | 3 | 3 |
| 3 | a | 0 (inside) | 1 | `bca` | 3 | 3 |
| 4 | e | – | 1 | `bcae` | 4 | 4 |
| 5 | f | – | 1 | `bcaef` | 5 | 5 |
| 6 | c | 2 (inside) | 3 | `aefc` | 4 | 5 |

The answer is `5`.

## Try It Yourself

```python runnable
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        length = len(s)
        if not length:
            return 0

        el_index = {}  # char -> last index

        # eg if repeat at index [1,7] then rep_index=2
        rep_index = 0

        max_non_rep_len = 1
        for i in range(length):
            if s[i] not in el_index or el_index[s[i]] < rep_index:
                max_non_rep_len = max(max_non_rep_len, i - rep_index + 1)
            else:
                rep_index = el_index[s[i]] + 1
                max_non_rep_len = max(max_non_rep_len, i - rep_index)
            el_index[s[i]] = i
        return max_non_rep_len


sol = Solution()
print(sol.lengthOfLongestSubstring("abcaefc"))  # 5
print(sol.lengthOfLongestSubstring("zzzz"))  # 1
print(sol.lengthOfLongestSubstring("dvdf"))  # 3
print(sol.lengthOfLongestSubstring(""))  # 0
```

## Comparison

| Approach | Time | Space |
|---|---|---|
| Scan back for the repeat | `O(n²)` worst case | `O(1)` |
| Last-index hash map | `O(n)` average | `O(min(n, alphabet))` |

## Edge Cases

- **Empty string** returns `0`.
- **All characters equal** returns `1`.
- **A repeat outside the window** (`"abba"`: the last `a` was seen at index 0, but the window already starts at 2) must not move the window backwards. That is why approach 2 checks `elIndex[s[i]] < repIndex`.

## Practice Questions

:::details[What does approach 2 return for "abba", and why is the "< repIndex" check needed?]
At `i = 2` (`b`), the window moves to start at `2`. At `i = 3` (`a`), `a` was last seen at index `0`, which is before `repIndex = 2`, so it is treated as new and the window becomes `"ba"` of length 2. Without the check, the window would jump back to start at `1` and report `"bba"` as valid. The answer is `2`.
:::

:::details[Why is the longest window bounded by the number of distinct characters?]
A window has no repeated characters, so it holds each character at most once. With only 128 possible ASCII characters, no window can be longer than 128.
:::
