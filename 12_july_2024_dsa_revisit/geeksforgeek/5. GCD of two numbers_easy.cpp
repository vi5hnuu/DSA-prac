/*
Given two positive integers a and b, find GCD of a and b.

Note: Don't use the inbuilt gcd function

Examples:

Input: a = 3, b = 6
Output: 3
Explanation: GCD of 3 and 6 is 3
Input: a = 1, b = 1
Output: 1
Explanation: GCD of 1 and 1 is 1
Constraints:
1 ≤ a, b ≤ 109
*/


/*
since gcd can less than or equal to min of both number
we start with min unitll that number divides both a and b
*/
class Solution {
  public:
    int gcd(int a, int b) {
        int mn=min(a,b);
        while(mn>0){
            if(a%mn==0 && b%mn==0) return mn;
            mn--;
        }
        return 1;
    }
};


/*
The fundamental property of the Euclidean algorithm is:

**GCD(a, b) = GCD(a - b, b)**

### Why does this work?
1. Let **d** be the GCD of `a` and `b`, meaning:
   - `d` divides `a`
   - `d` divides `b`

2. Since **d** divides both `a` and `b`, it must also divide their difference:

   `d` divides `(a - b)`

3. This means **d** is also a divisor of `(a - b, b)`, proving that:

   `GCD(a, b) = GCD(a - b, b)`

### Example:
Find `GCD(48, 18)` using `GCD(a - b, b)`:

1. `GCD(48, 18) = GCD(48 - 18, 18) = GCD(30, 18)`
2. `GCD(30, 18) = GCD(30 - 18, 18) = GCD(12, 18)`
3. `GCD(12, 18) = GCD(18 - 12, 12) = GCD(6, 12)`
4. `GCD(6, 12) = GCD(12 - 6, 6) = GCD(6, 6)`
5. `GCD(6, 6) = 6`

Thus, **GCD(48, 18) = 6**.

This property forms the basis of the **Euclidean Algorithm**, which is optimized using modulo:
**GCD(a, b) = GCD(b, a % b)**
*/

class Solution {
  public:
    int gcd(int a, int b) {
        while(a!=b){
            if(a>b) a-=b;
            else b-=a;
        }
        return a;
    }
};
// ///////////////////////
class Solution {
  public:
    int gcd(int a, int b) {
        if(a==0) return b;
        else if(b==0) return a;
        if(a%b==0) return b;
        else if(b%a==0) return a;
        
        
        return gcd(max(a,b)-min(a,b),min(a,b));
    }
};

// using modulo
class Solution {
  public:
    int gcd(int a, int b) {
        if(a==0 || b==0) return max(a,b);
        return gcd(max(a,b)%min(a,b),min(a,b));
    }
};

class Solution {
  public:
    int gcd(int a, int b) {
        if(b==0) return a;
        return gcd(b,a%b);
    }
};


/*
### Why Does `GCD(a, b) = GCD(b, a % b)` Work?  

We need to prove that replacing `a` with `a % b` does not change the **GCD**.  

---

### Step 1: Understanding What GCD Means  
- The **GCD** of two numbers `a` and `b` is the largest number that divides both `a` and `b`.  
- Suppose `g` is the **GCD of `a` and `b`**, meaning:  
  - `g` divides `a`  
  - `g` divides `b`  
  - `g` is the **largest** such number.  

---

### Step 2: Expressing `a % b` Mathematically  
When we divide `a` by `b`, we get:  

`a = q * b + r`  

where:  
- `q` is the quotient (how many times `b` fits in `a`)  
- `r` is the remainder (`a % b`), which is **always smaller than `b`**  

So, we can rewrite `GCD(a, b)` as:  

`GCD(a, b) = GCD(b, r)`  

where `r = a % b`.  

---

### Step 3: Why Does This Preserve the GCD?  
We need to show that **`GCD(a, b) = GCD(b, a % b)`**, meaning they have the same greatest common divisor.  

#### 1. Any number that divides both `a` and `b` also divides `r`  
- If `g` divides `a` and `b`, then `g` must also divide **any linear combination** of `a` and `b`.  
- Since `r = a - q * b`, and `g` divides both `a` and `b`, it **must also divide `r`**.  

#### 2. Any number that divides `b` and `r` also divides `a`  
- If some number divides both `b` and `r`, it must also divide:  

  `a = q * b + r`  

  because `a` is just a sum of multiples of `b` and `r`.  

- So, the set of common divisors of `(a, b)` is the same as the set of common divisors of `(b, r)`, meaning:  

  `GCD(a, b) = GCD(b, r)`.  

---

### Step 4: Example to See It in Action  
Let's find `GCD(48, 18)` using the modulo method:  

1. Compute `48 % 18 = 12`  
   `GCD(48, 18) = GCD(18, 12)`  

2. Compute `18 % 12 = 6`  
   `GCD(18, 12) = GCD(12, 6)`  

3. Compute `12 % 6 = 0`  
   `GCD(12, 6) = GCD(6, 0)`  

4. Since `b = 0`, the answer is **6**.  

---

### Step 5: Why is This Faster Than Subtraction?  
Instead of repeatedly subtracting `b` from `a`, we **directly jump to the remainder**, which reduces the size of the problem much faster. This gives the algorithm a **logarithmic time complexity**:  

`O(log(min(a, b)))`  

---

### Conclusion  
The modulo version of the Euclidean Algorithm works because:  
1. The remainder `a % b` preserves all common divisors.  
2. The GCD does not change when replacing `a` with `a % b`.  
3. The algorithm quickly reduces the problem size, making it efficient.  

Would you like another example to clarify further? 😊
*/
class Solution {
  public:
    int gcd(int a, int b) {
        while(a!=0 && b!=0){
            int am=max(a,b);
            int bm=min(a,b);
            a=am%bm;
            b=bm;
        }
        return max(a,b);
    }
};