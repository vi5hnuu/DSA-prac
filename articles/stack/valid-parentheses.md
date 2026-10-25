# Valid Parentheses

::problem{slug=valid-parentheses}

## Problem Statement

You are given a string `s` made only of the bracket characters `(`, `)`, `[`, `]`, `{` and `}`. Decide whether the brackets are **balanced**:

- every opening bracket is closed by a bracket of the **same type**,
- brackets are closed in the **reverse order** they were opened (inner pairs close before outer ones), and
- no closing bracket appears without a matching opening bracket before it.

Return `true` if the string is balanced, otherwise `false`.

### Examples

| Input | Output | Why |
|---|---|---|
| `s = "{[]}"` | `true` | `[]` is closed inside `{}` |
| `s = "()[]{}"` | `true` | three independent pairs |
| `s = "([)]"` | `false` | `[` is still open when `)` arrives |
| `s = "]"` | `false` | nothing to close |

### Constraints

- `1 <= s.length <= 10^4`
- `s` contains only the characters `()[]{}`.

:::callout{kind=tip}
The most recently opened bracket must be the first one to close. "Last in, first out" is exactly what a **stack** gives you.
:::

## Approach: Stack with an ASCII Trick

Scan the string from left to right with a stack of characters:

- If the current character **closes the bracket on top of the stack**, pop it — that pair is done.
- Otherwise push the current character.

At the end the string is balanced only if the stack is empty.

To test "closes the top" without a lookup table, the solution uses the ASCII codes of the brackets:

| Pair | Opening code | Closing code | Difference |
|---|---|---|---|
| `( )` | 40 | 41 | **1** |
| `[ ]` | 91 | 93 | **2** |
| `{ }` | 123 | 125 | **2** |

So `s[i]` closes `top` exactly when `s[i] - top` is `1` or `2`. No other pair of bracket characters differs by 1 or 2 in that direction (for example `]` − `(` is 53), so the test never matches the wrong type.

A closing bracket that does *not* match is pushed onto the stack. Nothing can ever pop it (no character is 1 or 2 above a closing bracket), so the stack stays non-empty and the answer is correctly `false`.

:::code-tabs
```cpp
class Solution {
public:
    bool isValid(string s) {
        stack<char> stck;

        for (int i = 0, sz = s.length(); i < sz; i++) {
            if (stck.empty() || ((s[i] - stck.top()) != 1 && (s[i] - stck.top()) != 2)) stck.push(s[i]);
            else stck.pop();
        }
        return stck.empty();
    }
};
```
```java
class Solution {
    public boolean isValid(String s) {
        Deque<Character> stck = new ArrayDeque<>();

        for (int i = 0, sz = s.length(); i < sz; i++) {
            char c = s.charAt(i);
            if (stck.isEmpty() || ((c - stck.peek()) != 1 && (c - stck.peek()) != 2)) stck.push(c);
            else stck.pop();
        }
        return stck.isEmpty();
    }
}
```
```python
class Solution:
    def isValid(self, s: str) -> bool:
        stck = []

        for ch in s:
            if not stck or (ord(ch) - ord(stck[-1]) != 1 and ord(ch) - ord(stck[-1]) != 2):
                stck.append(ch)
            else:
                stck.pop()
        return not stck
```
:::

**Complexity**

- **Time:** `O(n)` — each character is pushed and popped at most once.
- **Space:** `O(n)` — the stack can hold every character, e.g. `"(((((("`.

### Dry Run

`s = "{[]}"`

| Char | Top before | Difference | Action | Stack after |
|---|---|---|---|---|
| `{` | – | – | push | `{` |
| `[` | `{` | 91 − 123 = −32 | push | `{ [` |
| `]` | `[` | 93 − 91 = 2 | pop | `{` |
| `}` | `{` | 125 − 123 = 2 | pop | empty |

The stack is empty, so the string is valid.

## Try It Yourself

```python runnable
class Solution:
    def isValid(self, s: str) -> bool:
        stck = []

        for ch in s:
            if not stck or (ord(ch) - ord(stck[-1]) != 1 and ord(ch) - ord(stck[-1]) != 2):
                stck.append(ch)
            else:
                stck.pop()
        return not stck


sol = Solution()
print(sol.isValid("{[]}"))  # True
print(sol.isValid("()[]{}"))  # True
print(sol.isValid("([)]"))  # False
print(sol.isValid("]"))  # False
```

## Edge Cases

- **Odd length** strings can never be balanced.
- **A closing bracket first** (`"]"`, `")("`) leaves something on the stack.
- **Only opening brackets** (`"(("`) leave the stack non-empty.

## Practice Questions

:::details[Why does the ASCII trick depend on the input containing only bracket characters?]
With other characters allowed, unrelated pairs could differ by 1 or 2 — for example `*` (42) minus `(` (40) is 2 — and would be wrongly treated as a matching pair. A map from closing to opening bracket avoids this.
:::

:::details[Can you answer in O(1) extra space if only one bracket type ( ) is used?]
Yes. Keep a counter: `+1` for `(`, `-1` for `)`. The string is valid if the counter never goes below zero and ends at zero. With several bracket types a counter is not enough, because it cannot tell which type is open.
:::
