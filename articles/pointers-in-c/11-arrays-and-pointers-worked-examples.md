title : Arrays and Pointers: Worked Examples

summary : Worked puzzles on arrays and pointers: array names as base addresses, pointer arithmetic, sizeof, and 2-D array addresses. Predict each output, then read the step-by-step explanation.

# Arrays and Pointers: Worked Examples

These puzzles test everything from the last few articles: array names as base addresses, pointer arithmetic, `sizeof`, 2-D arrays and pointers to pointers. For each one, work out your answer **before** opening the solution — ideally on paper, drawing the array and its addresses.

Several puzzles ask about addresses. Real addresses change on every run, so these programs print each address as a **byte offset** from the start of the array (`+0`, `+4`, …). Where a puzzle says "suppose the array starts at address 5000", just add 5000 to those offsets.

All answers assume a typical 64-bit system: 4-byte `int`, 8-byte pointers.

### 1. Walking with the array name

What happens with this program?

```c
#include <stdio.h>

int main(void)
{
    int ages[] = {12, 19, 25, 31, 46};

    for (int i = 0; i < 5; i++) {
        printf("%d\n", *ages);
        ages++;
    }
    return 0;
}
```

:::details[Answer]
It does not compile: *lvalue required as increment operand*, on `ages++`.

The first `printf` would be fine — `*ages` is the first element. The problem is `ages++`. An array's name stands for the array's **fixed** base address; it is not a variable that holds an address, so it cannot be changed. (If it could, the program would lose track of where its own array begins.) An **lvalue** is something that can be assigned to or modified, and an array name is not one.

The fix is to walk with a real pointer:

```c runnable
#include <stdio.h>

int main(void)
{
    int ages[] = {12, 19, 25, 31, 46};
    int *p = ages;                  /* a pointer CAN be moved */

    for (int i = 0; i < 5; i++) {
        printf("%d\n", *p);
        p++;
    }
    return 0;
}
```

```
12
19
25
31
46
```
:::

### 2. Arithmetic that is not allowed

Which lines are wrong?

```c
int main(void)
{
    double prices[] = {2.5, 4.0, 1.25, 8.75, 3.5};
    double *p, *q;

    p = prices;
    q = prices + 3;
    p = p * 2;
    q = q / 2;
    return 0;
}
```

:::details[Answer]
The last two assignments. `p = prices;` stores the base address, and `q = prices + 3;` stores the address of the fourth `double` — both are fine. But a pointer can only have integers **added** or **subtracted**; multiplying or dividing an address has no meaning. GCC reports:

```
error: invalid operands to binary * (have 'double *' and 'int')
error: invalid operands to binary / (have 'double *' and 'int')
```
:::

### 3. First and last

```c runnable
#include <stdio.h>

int main(void)
{
    int readings[20];
    readings[0]  = 40;
    readings[19] = 70;

    printf("%d %d\n", *readings, *(readings + 19) + *(readings + 0));
    return 0;
}
```

:::details[Answer]
```
40 110
```

`readings` has 20 elements, numbered `0` to `19`; only the first and last are given values. `readings` is the base address, so `*readings` is element `0`: **40**. `readings + 19` is the address of the last element, so `*(readings + 19)` is **70**, and `*(readings + 0)` is element `0` again, **40**. Their sum is **110**.

The other 18 elements are never read, so it does not matter that they hold garbage.
:::

### 4. Starting from the end

```c runnable
#include <stdio.h>

int main(void)
{
    int vals[5] = {11, 22, 33, 44, 55};
    int *p = &vals[4] - 4;

    for (int i = 0; i < 5; i++) {
        printf("%d ", *p);
        p++;
    }
    printf("\n");
    return 0;
}
```

:::details[Answer]
```
11 22 33 44 55 
```

`&vals[4]` is the address of the last element. Subtracting `4` from an `int` pointer does **not** subtract 4 bytes — it moves back **4 `int`s**. That lands on `vals[0]`. If `vals` starts at 5000, `&vals[4]` is 5016, and `&vals[4] - 4` is `5016 − 4 × 4 = 5000`, not 5012.

From there the loop reads each element and steps forward one `int` at a time.
:::

### 5. sizeof: array vs pointer

```c runnable
#include <stdio.h>

int main(void)
{
    char  name[] = "Pointer!";
    char *np     = "Pointer!";

    printf("%zu %zu\n", sizeof name, sizeof np);
    printf("%zu %zu\n", sizeof *name, sizeof *np);
    return 0;
}
```

:::details[Answer]
```
9 8
1 1
```

`name` is a **`char` array** initialised from the string: 8 visible characters plus the `'\0'` that ends every string, so `sizeof name` is **9**. `np` is a **pointer** to the same text, and `sizeof np` is the size of a pointer: **8** on a 64-bit system (older 16-bit compilers printed `2`).

`*name` and `*np` are both the first character, `'P'` — a `char`, whose size is always **1**.

The lesson: an array and a pointer can be used in similar ways, but `sizeof` tells them apart. Strings are covered in depth in the next chapter.
:::

### 6. The name of an array, and sizeof

Suppose `rates` starts at address 5000.

```c runnable
#include <stdio.h>

int main(void)
{
    int rates[] = {3, 7, 2, 9, 5};

    printf("rates is at +%td, sizeof rates = %zu\n",
           (char *)rates - (char *)&rates[0], sizeof rates);
    return 0;
}
```

:::details[Answer]
```
rates is at +0, sizeof rates = 20
```

So `rates` gives **5000** and `sizeof rates` gives **20**.

Mentioning the name of an array gives its base address — the address of element `0`, hence offset `+0`. There is an exception: with `sizeof`, the name means the **whole array**, so `sizeof rates` is 5 elements × 4 bytes = **20**. (Old 16-bit systems with 2-byte `int`s printed `10`.) The `&` operator is the other exception, as the next puzzle shows.
:::

### 7. rates + 1 vs &rates + 1

Suppose `rates` starts at address 5000.

```c runnable
#include <stdio.h>

int main(void)
{
    int rates[] = {3, 7, 2, 9, 5};
    char *base = (char *)rates;

    printf("rates      -> +%td\n", (char *)rates - base);
    printf("&rates     -> +%td\n", (char *)&rates - base);
    printf("rates + 1  -> +%td\n", (char *)(rates + 1) - base);
    printf("&rates + 1 -> +%td\n", (char *)(&rates + 1) - base);
    return 0;
}
```

:::details[Answer]
```
rates      -> +0
&rates     -> +0
rates + 1  -> +4
&rates + 1 -> +20
```

So the addresses are 5000, 5000, 5004 and 5020.

`rates` and `&rates` hold the **same address**, but their types differ:

- `rates` becomes a pointer to the first **`int`** (`int *`), so `rates + 1` moves one `int`: **+4**.
- `&rates` is a pointer to the **whole array of 5 `int`s** (`int (*)[5]`), so `&rates + 1` jumps past the entire array: **+20**.
:::

### 8. The same idea in two dimensions

Suppose `grid` starts at address 5000.

```c runnable
#include <stdio.h>

int main(void)
{
    int grid[3][4] = {
        {4, 1, 7, 3},
        {8, 2, 6, 5},
        {9, 0, 4, 2}
    };
    char *base = (char *)grid;

    printf("grid + 1  -> +%td\n", (char *)(grid + 1) - base);
    printf("&grid + 1 -> +%td\n", (char *)(&grid + 1) - base);
    return 0;
}
```

:::details[Answer]
```
grid + 1  -> +16
&grid + 1 -> +48
```

So the addresses are 5016 and 5048.

The name of a 2-D array gives the address of its first element, and its first element is a **row** of 4 `int`s. So `grid + 1` moves one row: 4 × 4 = **16** bytes, to the start of row 1. `&grid` is a pointer to the **whole** `3 × 4` table, so `&grid + 1` jumps past all of it: 12 × 4 = **48** bytes.
:::

### 9. Three ways to say the same thing

Suppose `grid` (the same array as above) starts at address 5000.

```c runnable
#include <stdio.h>

int main(void)
{
    int grid[3][4] = {
        {4, 1, 7, 3},
        {8, 2, 6, 5},
        {9, 0, 4, 2}
    };
    char *base = (char *)grid;

    printf("grid[0] + 1          -> +%td\n", (char *)(grid[0] + 1) - base);
    printf("*(grid[0] + 1)       =  %d\n", *(grid[0] + 1));
    printf("*(*(grid + 0) + 1)   =  %d\n", *(*(grid + 0) + 1));
    return 0;
}
```

:::details[Answer]
```
grid[0] + 1          -> +4
*(grid[0] + 1)       =  1
*(*(grid + 0) + 1)   =  1
```

So `grid[0] + 1` is **5004**, and the other two print **1**.

`grid[0]` is row 0 — a 1-D array — so it becomes the address of `grid[0][0]`. Adding 1 moves one `int`: address 5004, which is `&grid[0][0] + 1`, the address of `grid[0][1]`. `*(grid[0] + 1)` reads that element: **1**.

The compiler rewrites `grid[0]` as `*(grid + 0)`, so `*(*(grid + 0) + 1)` is exactly the same expression in pointer form — and gives the same **1**. All three are ways of reaching `grid[0][1]`.
:::

### 10. A pointer to a pointer into a 2-D array

```c runnable
#include <stdio.h>

void show_first(int **pp)
{
    printf("%d\n", **pp);
}

int main(void)
{
    int grid[3][4] = {
        {4, 1, 7, 3},
        {8, 2, 6, 5},
        {9, 0, 4, 2}
    };
    int *ptr = &grid[0][0];

    show_first(&ptr);
    return 0;
}
```

:::details[Answer]
```
4
```

`ptr` holds the address of `grid[0][0]`. `main` passes `&ptr` — the address of the pointer — so `show_first` receives an `int **`. One `*` gives back `ptr`, and the second `*` follows it to `grid[0][0]`, which is **4**.

Note that `int **` works here only because we passed the address of a real `int *` variable. Passing `grid` itself to an `int **` parameter would be wrong: `grid` becomes a pointer to a **row** (`int (*)[4]`), not a pointer to a pointer — the compiler warns about incompatible pointer types, and using it that way would read garbage.
:::
