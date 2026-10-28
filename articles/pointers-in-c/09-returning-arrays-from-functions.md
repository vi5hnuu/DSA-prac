title : Returning Arrays from Functions

summary : A C function cannot return an array directly. Learn the ways around it: returning pointers, static arrays and their shared-storage trap, typedefs for array pointers, and caller-provided buffers.

# Returning Arrays from Functions

We now know how to **pass** 2-D and 3-D arrays to functions. The natural next question is the reverse: how does a function **give an array back**?

The short answer is: it can't — not directly. What a function *can* return is a **pointer** to an array that lives somewhere safe. This article explains why, shows the different pointer types a function can return for 2-D and 3-D arrays, and finishes with the pattern most professional C code actually uses.

## Why a Function Cannot Return an Array

Try writing a function whose return type is an array, and the compiler refuses outright:

```c
int make(void)[4];     /* error: 'make' declared as function returning an array */
```

This is the same rule that stops you from copying one array into another with `=`:

```c
int a[3] = {1, 2, 3}, b[3];
b = a;                 /* error: assignment to expression with array type */
```

In C, an array is never copied as a whole by `=`, by passing it, or by returning it. Whenever an array's name is used, it turns into the address of its first element — and that address is what gets passed around. So "returning an array" really means **returning the address of an array**.

That immediately raises a second question: *whose* array? The address is only useful if the array still exists after the function returns. An ordinary local array does not:

```c
int (*make(void))[4]
{
    int grid[3][4] = {{0}};
    return grid;       /* warning: function returns address of local variable */
}
```

`grid` is destroyed the moment `make` returns, so the caller would receive a **dangling pointer** — exactly the bug we met with single variables in an earlier article. The fix is also the same: make the array `static`, so that it lives for the whole run of the program. All the examples below do this.

## Returning a 2-D Array

Suppose a function owns a `static int grid[3][4]` and wants to hand it back. Its base address can be returned as three different pointer types, depending on how the caller wants to view the data:

1. A **pointer to an `int`** — the very first element. The caller sees one long line of 12 `int`s.
2. A **pointer to a row** — a pointer to an array of 4 `int`s (`int (*)[4]`). The caller sees 3 rows.
3. A **pointer to the whole 2-D array** — `int (*)[3][4]`. The caller sees one complete table.

All three hold the **same address**; they differ in what the caller can do with `+ 1` and subscripts. Here are all three, side by side:

```c runnable
#include <stdio.h>

#define ROWS 3
#define COLS 4

int *as_ints(void);                     /* way 1: pointer to the first int          */
int (*as_rows(void))[COLS];             /* way 2: pointer to the first row          */
int (*as_whole(void))[ROWS][COLS];      /* way 3: pointer to the whole 2-D array    */

int main(void)
{
    int *p = as_ints();
    printf("way 1:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++)
            printf("%d ", *(p + i * COLS + j));
        printf("\n");
    }

    int (*rows)[COLS] = as_rows();
    printf("way 2:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++)
            printf("%d ", rows[i][j]);
        printf("\n");
    }

    int (*whole)[ROWS][COLS] = as_whole();
    printf("way 3:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++)
            printf("%d ", (*whole)[i][j]);
        printf("\n");
    }

    return 0;
}

int *as_ints(void)
{
    static int grid[ROWS][COLS] = {{1, 4, 7, 2}, {8, 5, 3, 9}, {6, 0, 2, 4}};
    return &grid[0][0];
}

int (*as_rows(void))[COLS]
{
    static int grid[ROWS][COLS] = {{3, 3, 8, 1}, {7, 2, 6, 5}, {0, 9, 4, 4}};
    return grid;                        /* name -> address of row 0 */
}

int (*as_whole(void))[ROWS][COLS]
{
    static int grid[ROWS][COLS] = {{2, 6, 1, 8}, {5, 5, 0, 3}, {9, 7, 2, 6}};
    return &grid;                       /* address of the whole array */
}
```

```
way 1:
1 4 7 2 
8 5 3 9 
6 0 2 4 
way 2:
3 3 8 1 
7 2 6 5 
0 9 4 4 
way 3:
2 6 1 8 
5 5 0 3 
9 7 2 6 
```

Let's look at each one closely.

**Way 1 — `int *`.** `as_ints` returns `&grid[0][0]`, the address of the first `int`. The caller gets no information about rows, so it computes positions itself with the familiar formula `i × COLS + j`. Simple, but the shape of the table is lost.

**Way 2 — pointer to a row.** `as_rows` simply returns `grid`. Used as a value, the name of a 2-D array is the address of its first row, which has type `int (*)[4]` — exactly the declared return type, so no cast is needed. The caller stores it in a matching pointer, `int (*rows)[COLS]`, and can then write `rows[i][j]` just as if it had the array itself, because `rows + i` jumps whole rows.

**Way 3 — pointer to the whole array.** `as_whole` returns `&grid`. Putting `&` in front of an array's name gives the address of the **entire array**, type `int (*)[3][4]`. The caller first follows the pointer with `*whole` to get the table, then subscripts it: `(*whole)[i][j]`. The parentheses are needed because `[]` binds tighter than `*`.

:::callout{kind=note}
`grid`, `&grid[0][0]` and `&grid` are all the same address. What changes is the **type** — a pointer to an `int`, to a row, or to the whole table — and therefore how far `+ 1` moves: 4 bytes, 16 bytes, or 48 bytes. Older books often return these with casts such as `return (int *) a;`; choosing the right expression (`&grid[0][0]`, `grid`, `&grid`) makes casts unnecessary.
:::

### Reading Those Declarations

Declarations like `int (*as_rows(void))[COLS]` look intimidating, but they follow one rule: **start at the name, go right when you can, go left when you must** — and treat parentheses as a fence you finish before stepping outside.

![The declaration int (*as_rows(void))[4] read in four steps: as_rows is a function taking no arguments, returning a pointer, to an array of 4, ints](images/reading-function-returning-array-pointer.svg)

1. Start at the name: `as_rows`.
2. Go right: `(void)` — **a function taking no arguments**…
3. Hit the closing parenthesis, so go left: `*` — **…that returns a pointer…**
4. Step outside the parentheses and go right: `[4]` — **…to an array of 4…**
5. Nothing more on the right, so go left: `int` — **…ints.**

The same reading turns `int (*as_whole(void))[3][4]` into "a function returning a pointer to an array of 3 arrays of 4 `int`s" — a pointer to a `3 × 4` table.

### Making It Readable with `typedef`

In real code, such declarations are usually tidied up with `typedef`, which gives a name to a type:

```c runnable
#include <stdio.h>

#define ROWS 3
#define COLS 4

typedef int Row[COLS];             /* Row  = an array of COLS ints        */
typedef int Grid[ROWS][COLS];      /* Grid = an array of ROWS x COLS ints */

Row  *as_rows(void);               /* same as: int (*as_rows(void))[COLS]        */
Grid *as_whole(void);              /* same as: int (*as_whole(void))[ROWS][COLS] */

int main(void)
{
    Row  *r = as_rows();
    Grid *g = as_whole();

    printf("r[2][3] = %d, (*g)[2][3] = %d\n", r[2][3], (*g)[2][3]);
    return 0;
}

Row *as_rows(void)
{
    static int grid[ROWS][COLS] = {{3, 3, 8, 1}, {7, 2, 6, 5}, {0, 9, 4, 4}};
    return grid;
}

Grid *as_whole(void)
{
    static Grid grid = {{2, 6, 1, 8}, {5, 5, 0, 3}, {9, 7, 2, 6}};
    return &grid;
}
```

```
r[2][3] = 4, (*g)[2][3] = 6
```

`Row *as_rows(void)` says exactly what it means — "returns a pointer to a `Row`" — and compiles to the same thing as the long form.

## Returning a 3-D Array

A 3-D array adds one more level, so there is one more way to describe its base address. For a `static int cube[2][3][4]`, a function can return:

1. a pointer to an `int` (`int *`),
2. a pointer to a row of 4 (`int (*)[4]`),
3. a pointer to a `3 × 4` block (`int (*)[3][4]`),
4. a pointer to the whole cube (`int (*)[2][3][4]`).

The program below returns the cube all four ways and reaches the same element, `cube[1][2][0]`, through each:

```c runnable
#include <stdio.h>

#define SETS 2
#define ROWS 3
#define COLS 4

static int cube[SETS][ROWS][COLS] = {
    {{5, 8, 2, 6}, {7, 1, 9, 4}, {3, 6, 8, 2}},
    {{4, 9, 7, 1}, {6, 2, 5, 8}, {9, 3, 4, 7}}
};

int *as_ints(void)                    { return &cube[0][0][0]; } /* way 1 */
int (*as_rows(void))[COLS]            { return cube[0]; }        /* way 2 */
int (*as_blocks(void))[ROWS][COLS]    { return cube; }           /* way 3 */
int (*as_whole(void))[SETS][ROWS][COLS] { return &cube; }        /* way 4 */

int main(void)
{
    int *p = as_ints();
    int (*r)[COLS] = as_rows();
    int (*b)[ROWS][COLS] = as_blocks();
    int (*w)[SETS][ROWS][COLS] = as_whole();

    /* the same element, cube[1][2][0], reached four ways */
    printf("way 1: %d\n", *(p + 1 * ROWS * COLS + 2 * COLS + 0));
    printf("way 2: %d\n", r[1 * ROWS + 2][0]);   /* rows of all blocks in one run */
    printf("way 3: %d\n", b[1][2][0]);
    printf("way 4: %d\n", (*w)[1][2][0]);

    return 0;
}
```

```
way 1: 9
way 2: 9
way 3: 9
way 4: 9
```

- **Way 1** sees 24 `int`s in a line and uses `i × ROWS × COLS + j × COLS + k`.
- **Way 2** sees 6 rows of 4 one after another (3 rows from block 0, then 3 from block 1), so the row number is `1 × ROWS + 2 = 5`.
- **Way 3** is the most natural: `b[1][2][0]`, exactly like the array itself. It is also what the cube's name gives on its own (`return cube;`).
- **Way 4** points at the whole cube: dereference once, then subscript: `(*w)[1][2][0]`.

:::callout{kind=note}
Ways 1 and 2 walk across the boundaries between rows and blocks, relying on the array being stored contiguously. That always matches how C lays the data out and works on every mainstream compiler, but the standard strictly guarantees pointer arithmetic only within one array. When you have the choice, return the pointer type the caller will index naturally — usually way 3.
:::

## The Catch with `static`: One Shared Copy

`static` solves the dangling-pointer problem, but it has a cost that catches many programmers out: there is only **one** copy of the array for the whole program. Every call returns the address of the same storage, so each call overwrites what the previous call produced.

```c runnable
#include <stdio.h>

int (*squares_upto(int n))[3]
{
    static int table[2][3];          /* ONE table, shared by every call */

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            table[i][j] = (i * 3 + j + 1) * n;
    return table;
}

int main(void)
{
    int (*first)[3]  = squares_upto(1);
    printf("first[1][2] = %d\n", first[1][2]);

    int (*second)[3] = squares_upto(10);
    printf("second[1][2] = %d\n", second[1][2]);
    printf("first[1][2] is now %d  (same storage!)\n", first[1][2]);

    return 0;
}
```

```
first[1][2] = 6
second[1][2] = 60
first[1][2] is now 60  (same storage!)
```

![Two pointers, first and second, returned by two calls of squares_upto, both point to the start of the same static table; the second call overwrote element [1][2] from 6 to 60](images/static-array-shared-storage.svg)

`first` was never changed by the program — yet its data changed underneath it, because `first` and `second` point to the same table. The same problem makes such functions unsafe when several threads call them at once.

## The Professional Pattern: Let the Caller Provide the Array

Most real C libraries avoid both problems by turning the job around: **the caller owns the array and passes it in; the function only fills it.** You already know how to pass 2-D arrays, so this needs nothing new:

```c runnable
#include <stdio.h>

#define ROWS 2
#define COLS 3

/* The caller owns the array; the function only fills it in. */
void fill_table(int table[][COLS], int rows, int factor)
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < COLS; j++)
            table[i][j] = (i * COLS + j + 1) * factor;
}

int main(void)
{
    int first[ROWS][COLS], second[ROWS][COLS];

    fill_table(first, ROWS, 1);
    fill_table(second, ROWS, 10);

    printf("first[1][2] = %d, second[1][2] = %d\n", first[1][2], second[1][2]);
    return 0;
}
```

```
first[1][2] = 6, second[1][2] = 60
```

Each caller gets its own array, nothing dangles, nothing is shared, and the function's signature is easy to read. (Standard functions such as `fgets` and `snprintf` work exactly this way.) A third option — creating a brand-new array at run time with **dynamic memory allocation** — is coming up later in this course.

| Approach | Data survives the call? | Each call gets its own data? |
|---|---|---|
| Return address of a local array | **no** — dangling pointer | — |
| Return address of a `static` array | yes | **no** — one shared copy |
| Caller passes the array in | yes | yes |

## Key Takeaways

- A C function cannot return an array; it returns a **pointer** to one. Arrays are never copied whole by `=`, by passing, or by returning.
- The array must outlive the call. Returning the address of an ordinary local array creates a dangling pointer; `static` keeps it alive.
- A 2-D array's base address can be returned as `int *`, `int (*)[COLS]` or `int (*)[ROWS][COLS]`; a 3-D array adds `int (*)[SETS][ROWS][COLS]`. Same address, different steps for `+ 1`.
- Return `&a[0][0]`, `a` or `&a` to match the declared type, instead of casting.
- Read declarations from the name outwards — right when you can, left when you must — and use `typedef` to keep them readable.
- A `static` array is shared by every call. The robust pattern is to let the **caller provide the array** and have the function fill it.

## Practice Questions

:::details[Why is int (*f(void))[5] allowed but int f(void)[5] is not?]
`int f(void)[5]` declares a function returning an **array**, which C forbids. `int (*f(void))[5]` declares a function returning a **pointer to** an array of 5 `int`s, which is allowed.
:::

:::details[static int t[4][5]; — write return statements that return its base address as int *, int (*)[5] and int (*)[4][5].]
`return &t[0][0];`, `return t;` and `return &t;` respectively.
:::

:::details[Read this declaration aloud: double (*grid_of(int n))[8]]
`grid_of` is a function taking an `int`, returning a pointer to an array of 8 `double`s.
:::

:::details[Rewrite double (*grid_of(int n))[8] using a typedef.]
`typedef double Row8[8];` then `Row8 *grid_of(int n);`.
:::

:::details[A function returns the address of a static array. Two threads call it at the same time. What can go wrong?]
Both calls write into the same single array, so each thread can see values written by the other — the results get mixed up. Letting each caller pass in its own array avoids this.
:::
