title : Pointers to Pointers and Multi-Dimensional Arrays: Worked Examples

summary : Advanced puzzles combining pointers to pointers, arrays of pointers and multi-dimensional arrays. Untangle expressions like **++ptr and *++*ptr with diagrams and step-by-step answers.

# Pointers to Pointers and Multi-Dimensional Arrays: Worked Examples

The final set of chapter puzzles combines the hardest ideas so far: an **array of pointers**, a **pointer to a pointer** walking through it, and the row-and-column machinery of 2-D and 3-D arrays. Expressions like `*++*ptr` and `++**ptr` look like line noise at first — but every one of them is just a short sequence of the two moves you already know: *follow an address* (`*`) and *move or change something* (`++`).

The secret is to **draw the memory and update the drawing after every statement**. The diagrams in the answers do exactly that. Try it yourself before opening them.

## The Setup Used in Puzzles 1–3

Puzzles 1 to 3 share the same three variables, so it pays to understand them first:

```c
int v[5] = {5, 15, 25, 35, 45};
int *p[5] = {v, v + 1, v + 2, v + 3, v + 4};
int **ptr = p;
```

- `v` is an ordinary array of 5 `int`s.
- `p` is an **array of 5 pointers**. Element `p[i]` holds `v + i`, the address of `v[i]`.
- `ptr` is a **pointer to a pointer**. It is set to `p`, the address of `p[0]` — and since `p[0]` is an `int *`, the address of it is an `int **`.

![v holds five ints; p holds the addresses v + 0 to v + 4, one per element; ptr holds the address of p[0], so *ptr is p[0] and **ptr is v[0]](images/ws2-pointer-to-pointer-array.svg)

To describe where pointers are without real addresses, the programs print three numbers after each step:

- `ptr - p` — which element of `p` the pointer `ptr` points to,
- `*ptr - v` — which element of `v` that element of `p` points to,
- `**ptr` — the `int` value finally reached.

### 1. Following two levels of pointers

```c runnable
#include <stdio.h>

int main(void)
{
    int v[5] = {5, 15, 25, 35, 45};
    int *p[5] = {v, v + 1, v + 2, v + 3, v + 4};
    int **ptr = p;

    printf("*v = %d\n", *v);
    printf("*p points to v[%td], **p = %d\n", *p - v, **p);
    printf("ptr points to p[%td], *ptr points to v[%td], **ptr = %d\n",
           ptr - p, *ptr - v, **ptr);
    return 0;
}
```

:::details[Answer]
```
*v = 5
*p points to v[0], **p = 5
ptr points to p[0], *ptr points to v[0], **ptr = 5
```

- `v` is the base address of `v`, so `*v` is `v[0]`: **5**.
- `p` is the base address of `p`. `*p` is `p[0]`, which holds `v` — the address of `v[0]`. So `**p` is **5**.
- `ptr` was set to `p`, so it behaves exactly like `p` here: `*ptr` is `p[0]`, and `**ptr` is `v[0]`, **5**.

If you printed the raw addresses instead (with `%p`), `v`, `*p` and `*ptr` would show the same address, and so would `p` and `ptr` — two levels of addresses leading to the same value.
:::

### 2. Moving `ptr` — and moving what it points to

```c runnable
#include <stdio.h>

int main(void)
{
    int v[5] = {5, 15, 25, 35, 45};
    int *p[5] = {v, v + 1, v + 2, v + 3, v + 4};
    int **ptr = p;

    ptr++;
    printf("%td %td %d\n", ptr - p, *ptr - v, **ptr);

    (void)*ptr++;     /* only the side effect matters here */
    printf("%td %td %d\n", ptr - p, *ptr - v, **ptr);

    (void)*++ptr;
    printf("%td %td %d\n", ptr - p, *ptr - v, **ptr);

    ++*ptr;
    printf("%td %td %d\n", ptr - p, *ptr - v, **ptr);

    return 0;
}
```

(The `(void)` in front of `*ptr++` and `*++ptr` simply tells the compiler that the value of the expression is deliberately thrown away; only its side effect — moving `ptr` — matters. Without it, GCC warns *value computed is not used*.)

:::details[Answer]
```
1 1 15
2 2 25
3 3 35
3 4 45
```

Take one statement at a time.

**`ptr++`** — `ptr` points to an element of `p`, so `++` moves it to the next element: `p[1]`. Now `ptr - p` is **1**, `*ptr` is `p[1]` = `v + 1`, so `*ptr - v` is **1**, and `**ptr` is `v[1]` = **15**.

**`*ptr++`** — `*` and `++` are both unary operators; postfix `++` belongs to `ptr`, so this is `*(ptr++)`. It reads `*ptr` (which is thrown away) and **then** moves `ptr` on to `p[2]`. Result: **2 2 25**.

**`*++ptr`** — here `++` comes first: `ptr` moves to `p[3]`, and then `*` reads `p[3]` (thrown away again). Result: **3 3 35**.

**`++*ptr`** — now `*` is applied first: `*ptr` **is** `p[3]`, and `++` increments **it**. `ptr` itself does not move. `p[3]` used to hold `v + 3`; incrementing a pointer moves it one element, so `p[3]` now holds `v + 4`. So `ptr - p` is still **3**, but `*ptr - v` becomes **4**, and `**ptr` is `v[4]` = **45**.

![Starting at p[0]: after ptr++ it points to p[1]; after *ptr++ to p[2]; after *++ptr to p[3]; then ++*ptr changes p[3] itself from v + 3 to v + 4](images/ws2-ptr-states-a.svg)

The lesson: **where the `++` sits decides what moves**. `ptr++` and `*ptr++` and `*++ptr` all move `ptr`; `++*ptr` changes the pointer stored in `p`.
:::

### 3. Reaching one level deeper

```c runnable
#include <stdio.h>

int main(void)
{
    int v[5] = {5, 15, 25, 35, 45};
    int *p[5] = {v, v + 1, v + 2, v + 3, v + 4};
    int **ptr = p;

    (void)**ptr++;    /* only the side effect matters here */
    printf("%td %td %d\n", ptr - p, *ptr - v, **ptr);

    (void)*++*ptr;
    printf("%td %td %d\n", ptr - p, *ptr - v, **ptr);

    ++**ptr;
    printf("%td %td %d\n", ptr - p, *ptr - v, **ptr);

    return 0;
}
```

:::details[Answer]
```
1 1 15
1 2 25
1 2 26
```

Unary operators that are written before the operand are applied from right to left (innermost first); a postfix `++` binds before any of them.

**`**ptr++`** — this is `**(ptr++)`. It reads `**ptr` (that is, `v[0]`) and throws it away; the lasting effect is that `ptr` moves to `p[1]`. Result: **1 1 15**.

**`*++*ptr`** — read it as `*(++(*ptr))`. `*ptr` is `p[1]`; `++` increments **`p[1]`**, so it changes from `v + 1` to `v + 2`; the outer `*` reads `v[2]` (thrown away). `ptr` still points to `p[1]`, but `p[1]` now points to `v[2]`. Result: **1 2 25**.

**`++**ptr`** — read it as `++(*(*ptr))`. `*ptr` is `p[1]`, `**ptr` is the `int` it points to — `v[2]` — and `++` increments **that `int`**: `v[2]` goes from 25 to **26**. Nothing moves. Result: **1 2 26**.

![After **ptr++ ptr points to p[1]; *++*ptr changes p[1] from v + 1 to v + 2; ++**ptr then changes v[2] from 25 to 26](images/ws2-ptr-states-b.svg)

Compare the three statements by **what the `++` lands on**:

| Statement | `++` is applied to | What changes |
|---|---|---|
| `**ptr++` | `ptr` | `ptr` moves to the next element of `p` |
| `*++*ptr` | `*ptr` (an element of `p`) | that element now points to the next `int` in `v` |
| `++**ptr` | `**ptr` (an `int` in `v`) | the value itself grows by 1 |
:::

## Two-Dimensional and Three-Dimensional Puzzles

Puzzles 4 to 6 use this table:

```c
int n[3][3] = {
    {4, 7, 1},
    {9, 2, 6},
    {3, 8, 5}
};
```

![The 3 by 3 array n stored as 9 ints; n[0], n[1] and n[2] start at byte offsets 0, 12 and 24; ptr = n[0], so ptr[2] is n[0][2] = 1](images/ws2-2d-rows-and-int-pointer.svg)

### 4. A table, a row and an element

```c runnable
#include <stdio.h>

int main(void)
{
    int n[3][3] = {
        {4, 7, 1},
        {9, 2, 6},
        {3, 8, 5}
    };
    char *base = (char *)n;

    printf("+%td +%td %d\n", (char *)n - base, (char *)n[2] - base, n[2][2]);
    return 0;
}
```

:::details[Answer]
```
+0 +24 5
```

- `n` gives the base address of the array: offset **+0**. (If `n` started at 6000, this would print 6000.)
- A 2-D array is an array of 1-D arrays, and `n[2]` is the third of them. Used as a value, `n[2]` is the address where that row begins. Each row is 3 `int`s (12 bytes), so row 2 starts **24** bytes in.
- `n[2][2]` is the element in row 2, column 2: **5**.

**Why `(char *)`?** This program shows each address as its distance in **bytes** from the start of the array. Two rules of C make the cast necessary. First, C can only subtract two pointers of the **same type**, so both are converted to one type. Second, the difference between two pointers is counted in units of the type they point to, not in bytes: two `int *` pointers 8 bytes apart differ by 2 (two `int`s). A `char` is exactly one byte, so subtracting two `char *` pointers counts bytes. The cast does not change any address — it only changes how the subtraction counts. (`%td` is the `printf` format for a pointer difference, whose type is `ptrdiff_t`.)
:::

### 5. A plain `int` pointer into a 2-D array

```c runnable
#include <stdio.h>

int main(void)
{
    int n[3][3] = {
        {4, 7, 1},
        {9, 2, 6},
        {3, 8, 5}
    };
    int *ptr = n[0];               /* address of n[0][0], as an int pointer */
    char *base = (char *)n;

    printf("+%td %d %d\n", (char *)n[2] - base, ptr[2], *(ptr + 2));
    return 0;
}
```

:::details[Answer]
```
+24 1 1
```

`n[2]` is the start of row 2, offset **+24**, as before.

`ptr` is an ordinary `int` pointer holding the address of `n[0][0]`. Can we subscript it with `ptr[2]` even though `ptr` is not an array? Yes — `ptr[2]` is simply `*(ptr + 2)`: the second `int` after the one `ptr` points to. That is `n[0][2]`, which is **1**. The last expression is the same thing written out.

Notice how the pointer is set up: `ptr = n[0]` (or `&n[0][0]`). Older code writes `ptr = n;`, but `n` used as a value is a pointer to a **row** (`int (*)[3]`), not to an `int`, so modern compilers warn *assignment to 'int \*' from incompatible pointer type 'int (\*)[3]'*.
:::

### 6. Two ways, walked backwards

```c runnable
#include <stdio.h>

int main(void)
{
    int n[3][3] = {
        {4, 7, 1},
        {9, 2, 6},
        {3, 8, 5}
    };

    for (int i = 2; i >= 0; i--)
        for (int j = 2; j >= 0; j--)
            printf("%d %d\n", n[i][j], *(*(n + i) + j));
    return 0;
}
```

:::details[Answer]
```
5 5
8 8
3 3
6 6
2 2
9 9
1 1
7 7
4 4
```

The loops run over the rows from last to first and, inside each row, over the columns from last to first — so the table is printed in exactly reverse order. Each line prints the same element twice, in two notations.

The second notation is worth unpicking once more. The compiler only needs to remember where each row of a 2-D array **starts**, and `n[i]` gives exactly that. Then:

- `n[i]` is the same as `*(n + i)`,
- so `n[i] + j` — the address `j` elements into row `i` — is `*(n + i) + j`,
- and the value there is `*(*(n + i) + j)`, which is `n[i][j]`.
:::

### 7. An array of pointers to rows

```c runnable
#include <stdio.h>

int main(void)
{
    int a[3][3] = {
        {11, 12, 13},
        {21, 22, 23},
        {31, 32, 33}
    };
    int *rows[3] = {a[0], a[1], a[2]};
    int **rp = rows;

    for (int i = 0; i < 3; i++)
        printf("%d ", *rows[i]);
    printf("\n");

    for (int i = 0; i < 3; i++)
        printf("%d ", *a[i]);
    printf("\n");

    for (int i = 0; i < 3; i++) {
        printf("%d ", **rp);
        rp++;
    }
    printf("\n");
    return 0;
}
```

:::details[Answer]
```
11 21 31 
11 21 31 
11 21 31 
```

`rows` is an array of 3 `int` pointers, each set to the start of one row of `a`. All three loops print the **first element of each row**, in three different ways:

1. `*rows[i]` — `rows[i]` holds the address where row `i` starts; `*` reads the `int` there.
2. `*a[i]` — `a[i]` already **is** the start of row `i`, so `*a[i]` reads the same `int`, with no extra array needed.
3. `**rp` — `rp` starts at `rows[0]`. `*rp` is `rows[0]` (an address), and `**rp` follows it to `a[0][0]`. Then `rp++` moves `rp` to `rows[1]`, and so on.

![rows[0], rows[1] and rows[2] hold the start addresses of the three rows of a; rp starts at rows[0] and moves one element per rp++, so **rp gives 11, 21, 31](images/ws2-array-of-row-pointers.svg)
:::

### 8. Finding an element in a 3-D array

```c runnable
#include <stdio.h>

int main(void)
{
    int t[3][2][4] = {
        {{3, 1, 4, 1}, {5, 9, 2, 6}},
        {{5, 3, 5, 8}, {9, 7, 9, 3}},
        {{2, 3, 8, 4}, {6, 2, 6, 4}}
    };

    printf("%d %d\n", t[2][1][3], *(*(*(t + 2) + 1) + 3));
    return 0;
}
```

:::details[Answer]
```
4 4
```

`t` is a collection of three 2-D arrays, each of 2 rows of 4 `int`s. `t[2][1][3]` means block **2**, row **1**, column **3** — the value **4**.

The pointer version reaches the same place one level at a time:

1. `t + 2` — skip two whole blocks (2 × 8 `int`s): offset 64.
2. `*(t + 2)` — block 2 itself, i.e. the address of its first row.
3. `*(t + 2) + 1` — skip one row (4 `int`s): offset 80.
4. `*(*(t + 2) + 1)` — that row, i.e. the address of its first `int`.
5. `*(*(t + 2) + 1) + 3` — skip three `int`s: offset 92.
6. `*(*(*(t + 2) + 1) + 3)` — the value there: **4**.

![t has 3 blocks of 2 rows of 4 ints. t + 2 skips two blocks to block 2 (offset 64); adding 1 row moves to offset 80; adding 3 ints reaches offset 92, the value 4](images/ws2-3d-element-path.svg)

In general, `a[i][j][k]` is `*(*(*(a + i) + j) + k)` — one `+` and one `*` per dimension.
:::

## What These Puzzles Teach

- With an array of pointers `p` and `int **ptr = p`: `ptr` moves through `p`, `*ptr` is an element of `p` (an address), and `**ptr` is the `int` it leads to.
- In expressions like `*ptr++`, `*++ptr`, `++*ptr` and `++**ptr`, find **what the `++` is applied to** — the outer pointer, an element of the pointer array, or the final value. Postfix `++` binds before `*`; prefix operators apply innermost first.
- Draw the memory and update the drawing after every statement — it turns the hardest puzzles into bookkeeping.
- `n[i]` is the start of row `i`; `n[i][j]` ≡ `*(*(n + i) + j)`; `a[i][j][k]` ≡ `*(*(*(a + i) + j) + k)`.
- To point a plain `int *` into a 2-D array, use `n[0]` or `&n[0][0]`, not `n`.
