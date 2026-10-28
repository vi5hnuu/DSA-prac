title : Two Sum

summary : Find two numbers in an array that add up to a target. Start with the simple brute-force check of every pair, then cut it to a single pass using a hash map, with clear complexity comparisons and code in C++, Java and Python.

# Two Sum

::problem{slug=two-sum}

## Problem Statement

You are given an integer array `nums` and a number `target`. Find two **different positions** in the array whose values add up to `target`, and return those two positions (indices).

- There is always **exactly one** such pair.
- One position cannot be used twice, but two positions may hold the same value.
- The two indices can be returned in either order.

### Examples

| Input | Output | Why |
|---|---|---|
| `nums = [4, 9, 2, 6], target = 11` | `[1, 2]` | `9 + 2 = 11` |
| `nums = [5, 8, 3], target = 11` | `[1, 2]` | `8 + 3 = 11` |
| `nums = [6, 6], target = 12` | `[0, 1]` | `6 + 6 = 12`, two different positions |

### Constraints

- The array has between `2` and `10^4` elements.
- Every value and the `target` lie between `-10^9` and `10^9`.
- Exactly one valid pair exists.

**Follow-up:** Can you beat the obvious `O(n²)` approach?

:::callout{kind=tip}
For every number `x`, the partner we need is `target - x`. The whole problem reduces to: *"have I already seen `target - x`, and where?"*
:::

## Approach 1: Brute Force

Check every pair `(i, j)` with `i < j`. As soon as `nums[i] + nums[j] == target`, return `[i, j]`.

Starting `j` from `i + 1` guarantees we never use the same element twice and never check a pair twice.

:::code-tabs
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        for (int i = 0, sz = nums.size(); i < sz; i++) {
            const auto &x = nums[i];
            for (int j = i + 1; j < sz; j++) {
                if (x == target - nums[j]) return {i, j};
            }
        }
        return {};
    }
};
```
```java
class Solution {
    public int[] twoSum(int[] nums, int target) {
        for (int i = 0; i < nums.length; i++) {
            for (int j = i + 1; j < nums.length; j++) {
                if (nums[i] == target - nums[j]) return new int[]{i, j};
            }
        }
        return new int[]{};
    }
}
```
```python
class Solution:
    def twoSum(self, nums: list[int], target: int) -> list[int]:
        n = len(nums)
        for i in range(n):
            for j in range(i + 1, n):
                if nums[i] == target - nums[j]:
                    return [i, j]
        return []
```
:::

**Complexity**

- **Time:** `O(n²)` — every pair is checked in the worst case.
- **Space:** `O(1)` — no extra data structure.

:::callout{kind=note}
Writing the check as `x == target - nums[j]` instead of `x + nums[j] == target` avoids a possible `int` overflow in C++/Java when both values are close to `±10^9`.
:::

## Approach 2: One-Pass Hash Map

Instead of searching for the partner with an inner loop, remember every number we have already visited in a hash map `value -> index`.

For each index `i` with value `x`:

1. Look up `target - x` in the map.
2. If it is there, we found the pair: return `[i, map[target - x]]`.
3. Otherwise store `map[x] = i` and move on.

Because we look up **before** inserting the current element, an element can never be paired with itself. Duplicates like `[3,3]` still work: the first `3` is stored, and the second `3` finds it.

### Dry Run

`nums = [4, 9, 2, 6]`, `target = 11`

| i | x | need = target - x | map before step | Action |
|---|---|---|---|---|
| 0 | 4 | 7 | `{}` | not found, store `4 → 0` |
| 1 | 9 | 2 | `{4: 0}` | not found, store `9 → 1` |
| 2 | 2 | 9 | `{4: 0, 9: 1}` | found at index 1 → return `[2, 1]` |

:::code-tabs
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> parsedNums; // value -> index
        for (int i = 0; i < nums.size(); i++) {
            const auto &x = nums[i];
            const auto &itr = parsedNums.find(target - x);
            if (itr != parsedNums.end()) return {i, itr->second};
            parsedNums[x] = i;
        }
        return {};
    }
};
```
```java
class Solution {
    public int[] twoSum(int[] nums, int target) {
        Map<Integer, Integer> parsedNums = new HashMap<>(); // value -> index
        for (int i = 0; i < nums.length; i++) {
            Integer j = parsedNums.get(target - nums[i]);
            if (j != null) return new int[]{i, j};
            parsedNums.put(nums[i], i);
        }
        return new int[]{};
    }
}
```
```python
class Solution:
    def twoSum(self, nums: list[int], target: int) -> list[int]:
        parsed_nums = {}  # value -> index
        for i, x in enumerate(nums):
            if target - x in parsed_nums:
                return [i, parsed_nums[target - x]]
            parsed_nums[x] = i
        return []
```
:::

**Complexity**

- **Time:** `O(n)` on average — one pass, each hash map lookup/insert is `O(1)` average.
- **Space:** `O(n)` — the map can hold up to `n` entries.

## Try It Yourself

```python runnable
class Solution:
    def twoSum(self, nums: list[int], target: int) -> list[int]:
        parsed_nums = {}  # value -> index
        for i, x in enumerate(nums):
            if target - x in parsed_nums:
                return [i, parsed_nums[target - x]]
            parsed_nums[x] = i
        return []


sol = Solution()
print(sol.twoSum([4, 9, 2, 6], 11))  # [2, 1]
print(sol.twoSum([5, 8, 3], 11))  # [2, 1]
print(sol.twoSum([6, 6], 12))  # [1, 0]
```
## Comparison

| Approach | Time | Space |
|---|---|---|
| Brute force | `O(n²)` | `O(1)` |
| One-pass hash map | `O(n)` average | `O(n)` |

## Practice Questions

:::details[Why not sort the array and use two pointers?]
Sorting gives `O(n log n)` time and the two-pointer scan works for finding the *values*, but sorting destroys the original positions. Since the problem asks for **indices**, you would have to sort `(value, index)` pairs, which costs extra `O(n)` space anyway. The hash map is simpler and faster.
:::

:::details[What happens with nums = [6, 6] and target = 12?]
At `i = 0`, we need `6`, the map is empty, so we store `6 → 0`. At `i = 1`, we need `6`, which is in the map at index `0`, so we return `[1, 0]`. Because we search before inserting, the same element is never used twice.
:::

:::details[Would the solution break if we inserted first and then searched?]
Yes. For `nums = [5, 2, 8]`, `target = 10` (answer `[1, 2]`), at `i = 0` we would insert `5 → 0` and then search for `5`, finding index `0` itself and wrongly returning `[0, 0]`.
:::
