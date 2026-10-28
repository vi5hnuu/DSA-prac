title : Pointer Exercises

summary : Practice exercises on pointer basics: predict outputs, find bugs and write small programs using addresses, pointer variables and functions that receive addresses. Solutions included.

# Pointer Exercises

Time to test yourself. Each exercise below is a short program or statement about pointers. Work out your answer first — on paper, using a memory map if it helps — and only then open the answer.

Some programs contain deliberate mistakes. For those, the question is not just "what is the output?" but "what is wrong, and how do you fix it?"

:::callout{kind=note}
Outputs were checked with GCC on a 64-bit Linux system. Where the result depends on the platform (sizes of types, byte order), the answer says so.
:::

## Part A: Programs

### 1. Four levels deep

```c runnable
#include <stdio.h>

int main(void)
{
    int base = 6;
    int *p1, **p2, ***p3, ****p4;

    p1 = &base;
    p2 = &p1;
    p3 = &p2;
    p4 = &p3;

    printf("%d %d %d %d %d\n", base, *p1, **p2, ***p3, ****p4);
    printf("sum = %d\n", base + *p1 + **p2 + ***p3 + ****p4);

    return 0;
}
```

:::details[Answer]
```
6 6 6 6 6
sum = 30
```

`p1` points to `base`, `p2` to `p1`, `p3` to `p2` and `p4` to `p3`. Each pointer needs as many `*` as its level to get back to `base`, so all five expressions are `6`, and their sum is `30`.
:::

### 2. One byte at a time

```c runnable
#include <stdio.h>

int main(void)
{
    char  letter = 'Q';
    int   count  = 15;
    int   big    = 70000;     /* 0x00011170 */
    float ratio  = 3.14f;

    unsigned char *bp;

    bp = (unsigned char *)&letter;
    printf("letter -> %d\n", *bp);
    bp = (unsigned char *)&count;
    printf("count  -> %d\n", *bp);
    bp = (unsigned char *)&big;
    printf("big    -> %d\n", *bp);
    bp = (unsigned char *)&ratio;
    printf("ratio  -> %d\n", *bp);

    return 0;
}
```

:::details[Answer]
On a typical little-endian PC:

```
letter -> 81
count  -> 15
big    -> 112
ratio  -> 195
```

`bp` is a pointer to a single byte, so `*bp` always reads **only the first byte** of whatever it points to:

- `'Q'` fits in one byte; its character code is `81`.
- `15` fits in the lowest byte of the `int`, which is stored first on little-endian machines.
- `70000` is `0x00011170`; its lowest byte is `0x70` = `112`. The other bytes are never read.
- `3.14f` is stored in floating-point format (`0x4048F5C3`), and its first byte is `0xC3` = `195` — nothing like `3.14`.

On a big-endian machine the last three lines would show the *highest* byte instead. The lesson is the same as before: to read a value correctly, use a pointer of the matching type.
:::

### 3. Copies all the way down

```c runnable
#include <stdio.h>

void change(int x, int y)
{
    int t = x;
    x = y;
    y = t;
    printf("in change: x = %d, y = %d\n", x, y);
}

void relay(int x, int y)
{
    change(x, y);
    printf("in relay:  x = %d, y = %d\n", x, y);
}

int main(void)
{
    int x = 3, y = 8;

    relay(x, y);
    printf("in main:   x = %d, y = %d\n", x, y);

    return 0;
}
```

:::details[Answer]
```
in change: x = 8, y = 3
in relay:  x = 3, y = 8
in main:   x = 3, y = 8
```

Each function has its own `x` and `y`, and every call passes **copies** of the values. `change` swaps its copies only, so neither `relay` nor `main` sees any change. Using the same names in all three functions does not connect the variables.
:::

### 4. Swapping through a pointer to a pointer

```c runnable
#include <stdio.h>

void trade(int **pp, int *q)
{
    int t = **pp;
    **pp = *q;
    *q = t;
}

void swap(int *a, int *b)
{
    trade(&a, b);
}

int main(void)
{
    int left = 11, right = 22;

    swap(&left, &right);
    printf("left = %d, right = %d\n", left, right);

    return 0;
}
```

:::details[Answer]
```
left = 22, right = 11
```

In `swap`, `a` holds the address of `left` and `b` the address of `right`. `trade` receives `&a` — the address of the pointer `a` — so `*pp` is `a` and `**pp` is `left`. It also receives `b` itself, so `*q` is `right`. Exchanging `**pp` and `*q` therefore swaps `left` and `right` in `main`.
:::

### 5. Squaring through two levels

```c runnable
#include <stdio.h>

int square(int **pp)
{
    int r = **pp * **pp;
    return r;
}

int main(void)
{
    int n = 6, *np;

    np = &n;
    n = square(&np);
    printf("n = %d, np points to n? %s\n", n, np == &n ? "yes" : "no");

    return 0;
}
```

:::details[Answer]
```
n = 36, np points to n? yes
```

`square` receives the address of `np`. `*pp` is `np`, and `**pp` is `n`, which is `6`. The function returns `6 * 6 = 36`, which `main` stores back in `n`. `np` itself was never changed, so it still points to `n`.
:::

### 6. Spot the bug: returning a result's address

```c
#include <stdio.h>

double *multiply(int n, double x)
{
    double product;

    product = n * x;
    return &product;
}

int main(void)
{
    double *res = multiply(4, 2.5);

    printf("*res = %.2f\n", *res);
    return 0;
}
```

:::details[Answer]
`multiply` returns the address of `product`, an ordinary local variable that is destroyed as soon as the function returns. `res` is a **dangling pointer** and reading `*res` is undefined behaviour.

GCC warns *function returns address of local variable*, and the program crashes with a segmentation fault when run. One fix is to make `product` `static`:

```c runnable
#include <stdio.h>

double *multiply(int n, double x)
{
    static double product;     /* static: survives after multiply returns */

    product = n * x;
    return &product;
}

int main(void)
{
    double *res = multiply(4, 2.5);

    printf("*res = %.2f\n", *res);
    return 0;
}
```

```
*res = 10.00
```

(Returning the `double` value itself, instead of a pointer, would be simpler still.)
:::

### 7. How far does + 1 move?

```c runnable
#include <stdio.h>

int main(void)
{
    char c[2]; int i[2]; long l[2]; float f[2]; double d[2];

    char *cp = c; int *ip = i; long *lp = l; float *fp = f; double *dp = d;

    printf("char   +1 moves %td byte(s)\n", (char *)(cp + 1) - (char *)cp);
    printf("int    +1 moves %td byte(s)\n", (char *)(ip + 1) - (char *)ip);
    printf("long   +1 moves %td byte(s)\n", (char *)(lp + 1) - (char *)lp);
    printf("float  +1 moves %td byte(s)\n", (char *)(fp + 1) - (char *)fp);
    printf("double +1 moves %td byte(s)\n", (char *)(dp + 1) - (char *)dp);

    return 0;
}
```

:::details[Answer]
On 64-bit Linux:

```
char   +1 moves 1 byte(s)
int    +1 moves 4 byte(s)
long   +1 moves 8 byte(s)
float  +1 moves 4 byte(s)
double +1 moves 8 byte(s)
```

Adding `1` to a pointer moves it forward by **the size of the type it points to**. The sizes depend on the platform — `long`, for example, is 8 bytes on 64-bit Linux and macOS but 4 bytes on 64-bit Windows. (Each variable is a two-element array only so that "one element further" is a real location.)

Older books show this with made-up addresses like `char *c = 4000;`. Modern compilers warn that this *makes pointer from integer without a cast* (newer GCC versions reject it), so the example above uses real variables instead.
:::

### 8. Subtracting addresses

What does this print?

```c
#include <stdio.h>

int main(void)
{
    int first = 10, second = 20;
    printf("%td\n", &second - &first);
    return 0;
}
```

:::details[Answer]
**Nothing meaningful.** Subtracting two pointers is only defined when both point into the **same array**; `first` and `second` are separate variables, so the result is undefined behaviour. The compiler is free to place them in any order with any gap. (On the test system it happened to print `1`, but you cannot rely on that.)

When both pointers are in the same array, the difference is the number of **elements** between them, not bytes:

```c runnable
#include <stdio.h>

int main(void)
{
    int scores[5] = {10, 20, 30, 40, 50};
    int *first = &scores[1];
    int *last  = &scores[4];

    printf("elements apart: %td\n", last - first);
    printf("bytes apart:    %td\n", (char *)last - (char *)first);

    return 0;
}
```

```
elements apart: 3
bytes apart:    12
```
:::

### 9. Multiplying a pointer

```c
int main(void)
{
    int *a, *b = 0;
    a = b * 2;
    return 0;
}
```

:::details[Answer]
It does not compile: *invalid operands to binary \* (have 'int \*' and 'int')*. C allows adding an integer to a pointer and subtracting pointers, but **multiplying or dividing** a pointer is meaningless — "twice an address" is not a location.
:::

### 10. Moving a variable

```c
int main(void)
{
    int level = 10;
    &level = 7200;
    return 0;
}
```

:::details[Answer]
It does not compile: *lvalue required as left operand of assignment*. `&level` is the address where `level` lives — a value, not a variable — so nothing can be assigned to it. You cannot move a variable to a different address.
:::

### 11. Spot the bug: four levels of returns

```c
#include <stdio.h>

double **outer(double *z);
double ****inner(double ***x);

double **y;
double ****w;

int main(void)
{
    double amount = 2.5;
    double **result;

    result = outer(&amount);
    printf("%.1f\n", **result);
    return 0;
}

double **outer(double *z)
{
    double ****v;

    y = &z;
    v = inner(&y);
    return **v;
}

double ****inner(double ***x)
{
    w = &x;
    return w;
}
```

:::details[Answer]
It may well print `2.5` — and it is still wrong.

Follow the pointers:

- In `inner`, `w = &x` stores the address of `inner`'s **parameter** `x`. Parameters are local variables, so that address dangles as soon as `inner` returns. GCC warns: *storing the address of local variable 'x' in 'w'*.
- Back in `outer`, `v` is that dangling address, so `**v` reads from memory that no longer belongs to anyone.
- Even if it did not, `**v` would be `y`, which is `&z` — the address of `outer`'s parameter `z`, which dangles once `outer` returns. `main` then reads `**result` through it.

The program printed `2.5` on the test system only because the old stack memory had not been overwritten yet. AddressSanitizer (`-fsanitize=address` with `ASAN_OPTIONS=detect_stack_use_after_return=1`) reports a **stack-use-after-return** error. "Seems to work" is not the same as "correct".
:::

## Part B: True or False

:::details[1. A pointer can be multiplied by an unsigned integer.]
**False.** Pointers can have integers added or subtracted, and two pointers into the same array can be subtracted. Multiplication and division are not allowed, whatever the integer's type.
:::

:::details[2. The address of a double can be stored in a char pointer.]
**Only with an explicit cast.** `char *cp = &value;` makes the compiler warn about incompatible pointer types. `char *cp = (char *)&value;` is allowed, and `*cp` then reads the first byte of the `double`.
:::

:::details[3. A double pointer holds a double value.]
**False.** A `double` pointer holds an **address** — the location of a `double`. The `double` value is what you get with `*`.
:::

:::details[4. q holds the address of a pointer to a pointer to an int. To reach the int you write ****q.]
**False.** `q` is an `int ***`: `*q` is the pointer to a pointer, `**q` is the pointer, and `***q` is the `int`. Three `*`, not four.
:::
