title : Pointer Worked Examples

summary : Test your understanding of &, * and pointers to pointers with worked puzzles. Predict each program's output, then check the step-by-step explanation and the corrected modern C.

# Pointer Worked Examples

This article works through a set of pointer puzzles that test everything covered so far: `&` and `*`, pointer types, call by reference, and functions that return pointers. Try to answer each one before opening the explanation.

Several of these puzzles are classics from older C books. Where modern compilers behave differently from what those books describe, the explanation says so — the answers here match a current GCC on a 64-bit system.

## Part A: Predict the Output

### A1. Same names, different variables

```c runnable
#include <stdio.h>

void adjust(int count, int *total)
{
    count = count * count;          /* changes only adjust's copy        */
    *total = *total * *total;       /* changes main's total through its address */
}

int main(void)
{
    int count = -4, total = 3;

    adjust(count, &total);
    printf("count = %d, total = %d\n", count, total);

    return 0;
}
```

:::details[Answer]
```
count = -4, total = 9
```

`main` and `adjust` both have variables called `count`, but they are **two separate variables** — names are local to the function that declares them, so there is no conflict.

This is a *mixed call*: `count` is passed by value and `total` by address. `adjust` squares its own copy of `count` (to `16`), which `main` never sees. It squares `total` through the pointer, so `main`'s `total` becomes `9`.
:::

### A2. How big are NULL and ""?

```c runnable
#include <stdio.h>

int main(void)
{
    printf("%zu %zu\n", sizeof(NULL), sizeof(""));
    return 0;
}
```

:::details[Answer]
On a typical 64-bit GCC system:

```
8 1
```

`NULL` is a **null pointer constant**. GCC defines it as `((void *)0)`, a pointer, so its size is the size of a pointer: 8 bytes on a 64-bit system. The C standard also allows `NULL` to be a plain `0`, so on some compilers `sizeof(NULL)` is the size of an `int` instead. Old 16-bit compilers printed `2` here.

`""` is an empty string, but it still holds the terminating character `'\0'`, so its size is `1`.
:::

:::callout{kind=warning}
Because `NULL` may be a pointer, never use it as the number zero. Old books show `int a = b + NULL;` "working" because `NULL` was `0` there. With GCC it produces two warnings (arithmetic on a `void *`, and converting a pointer to an `int`), and newer compilers reject it outright. Use `0` for numbers and `NULL` only for pointers.
:::

### A3. Matching the format to the type

What does this print?

```c
double price = 9.5;
printf("%d\n", price);
```

:::details[Answer]
**Nothing reliable.** `%d` tells `printf` to expect an `int`, but a `double` was passed. The mismatch is undefined behaviour: you may see a random-looking number, and GCC warns *format '%d' expects argument of type 'int', but argument 2 has type 'double'*. `printf` does **not** convert the value for you. The opposite mistake — an `int` printed with `%f` — is just as wrong.

Use the format that matches the type, or convert first:

```c runnable
#include <stdio.h>

int main(void)
{
    double price = 9.5;
    int qty = 4;

    printf("price = %f\n", price);   /* %f for double */
    printf("qty   = %d\n", qty);     /* %d for int    */
    printf("price as int = %d\n", (int)price);   /* convert first, then %d */

    return 0;
}
```

```
price = 9.500000
qty   = 4
price as int = 9
```
:::

### A4. Returning a pointer without a prototype

What is wrong with this program?

```c
#include <stdio.h>

int main(void)
{
    int *bigger;
    bigger = larger(12, 30);
    printf("%d\n", *bigger);
    return 0;
}

int *larger(int x, int y)
{
    return (x >= y) ? &x : &y;
}
```

:::details[Answer]
**Two problems.**

1. **No prototype.** When `main` calls `larger`, the compiler has not seen it yet. Old compilers then assumed it returns an `int`, so storing the result in an `int *` triggered a "suspicious pointer conversion". Modern GCC warns about the *implicit declaration*, then stops with *conflicting types for 'larger'* when it reaches the real definition. A function that returns a pointer must be declared before it is called: `int *larger(int x, int y);`
2. **It returns the address of a parameter.** `x` and `y` are local to `larger` — they stop existing when it returns, so the returned pointer dangles. Adding the prototype alone does not fix this.

A correct version takes the caller's addresses and returns one of them:

```c runnable
#include <stdio.h>

int *larger(int *x, int *y);    /* prototype: returns an int pointer */

int main(void)
{
    int width = 12, height = 30;
    int *big = larger(&width, &height);

    printf("larger value = %d\n", *big);
    printf("it is height? %s\n", big == &height ? "yes" : "no");

    return 0;
}

int *larger(int *x, int *y)
{
    return (*x >= *y) ? x : y;    /* both point into main, so they stay valid */
}
```

```
larger value = 30
it is height? yes
```
:::

### A5. Adding 1 to a pointer

```c runnable
#include <stdio.h>

double *next_slot(double *p)
{
    p = p + 1;          /* move to the next double */
    return p;
}

int main(void)
{
    double readings[2] = {1.5, 2.5};
    double *before = &readings[0];
    double *after = next_slot(before);

    printf("moved by %td bytes\n", (char *)after - (char *)before);
    printf("*after = %.1f\n", *after);

    return 0;
}
```

(`readings` is just two `double`s stored side by side, so that the pointer has a real "next" `double` to move to.)

:::details[Answer]
```
moved by 8 bytes
*after = 2.5
```

Adding `1` to a pointer does **not** add one byte. It moves the pointer forward by **one element of its type**. `p` is a `double` pointer and a `double` is 8 bytes, so `p + 1` is 8 bytes further on — exactly where the next `double` starts. An `int` pointer would move by `sizeof(int)`, a `char` pointer by 1.

The function returns a `double *`, and its definition says so; because the definition appears before `main`, it also serves as the declaration.
:::

## Part B: Short Questions

:::details[B1. What other expression does the same job as ++*ptr?]
`(*ptr)++`. Both add 1 to the value that `ptr` points to. (The value of the whole expression differs — `++*ptr` gives the new value, `(*ptr)++` the old one — but the effect on the variable is the same.)

```c runnable
#include <stdio.h>

int main(void)
{
    int stock = 7;
    int *sp = &stock;

    ++*sp;          /* stock becomes 8 */
    (*sp)++;        /* stock becomes 9 */

    printf("stock = %d\n", stock);
    return 0;
}
```

```
stock = 9
```
:::

:::details[B2. A function receives int **slot. What statement makes the caller's pointer point to a variable inside the function?]
`*slot = &variable;` — `slot` holds the address of the caller's pointer, so `*slot` **is** that pointer.

The variable must outlive the function, or the caller ends up with a dangling pointer. An ordinary local variable is destroyed on return; a `static` one is not:

```c runnable
#include <stdio.h>

void point_at_limit(int **slot)
{
    static int limit = 99;   /* static: still alive after the function returns */
    *slot = &limit;          /* store limit's address in the caller's pointer */
}

int main(void)
{
    int *lp = NULL;

    point_at_limit(&lp);
    printf("*lp = %d\n", *lp);

    return 0;
}
```

```
*lp = 99
```
:::

:::details[B3. Are *ptr++ and ++*ptr the same?]
**No.**

- `*ptr++` moves the **pointer**: it reads the value `ptr` points to, then advances `ptr` to the next element. (Postfix `++` binds tighter than `*`, so this is `*(ptr++)`.)
- `++*ptr` changes the **value**: it adds 1 to the value `ptr` points to, and `ptr` does not move.

```c runnable
#include <stdio.h>

int main(void)
{
    int marks[3] = {40, 70, 90};
    int *mp;

    mp = marks;
    int a = *mp++;      /* reads 40, then moves mp to marks[1] */
    printf("a = %d, marks = %d %d %d, *mp = %d\n", a, marks[0], marks[1], marks[2], *mp);

    mp = marks;
    int b = ++*mp;      /* adds 1 to marks[0], mp does not move */
    printf("b = %d, marks = %d %d %d, *mp = %d\n", b, marks[0], marks[1], marks[2], *mp);

    return 0;
}
```

```
a = 40, marks = 40 70 90, *mp = 70
b = 41, marks = 41 70 90, *mp = 41
```
:::

:::details[B4. Where are pointers used?]
Almost everywhere in real C programs, for example:

- accessing the elements of arrays and strings,
- dynamic memory allocation,
- call by reference (letting functions change the caller's variables),
- building linked lists, trees, graphs and other data structures.
:::

:::details[B5. Does assigning between a double * and a void * need a cast?]
**No** (in C). Conversions to and from `void *` happen automatically:

```c runnable
#include <stdio.h>

int main(void)
{
    double rate = 2.75;
    void *any = &rate;        /* double * -> void *: no cast needed */
    double *dp = any;         /* void * -> double *: no cast needed */

    printf("*dp = %.2f\n", *dp);
    return 0;
}
```

```
*dp = 2.75
```

(C++ is stricter: there, converting *from* `void *` needs a cast.)
:::

:::details[B6. Can you do arithmetic on a void pointer, such as vp++?]
**Not in standard C.** `void` has no size, so the compiler cannot know how far "one element" is. GCC accepts it as an extension (treating the size as 1) but warns *wrong type argument to increment*, and rejects it with `-pedantic-errors`. Convert to a typed pointer first, e.g. `char *cp = vp; cp++;`.
:::

:::details[B7. int *ip; void *vp; — do ip = vp; and vp = ip; produce warnings?]
**No.** Both directions are allowed without a cast, because one side is `void *`.
:::

:::details[B8. float level = 3.5f; float *fp; char *cp; — do fp = &level; and cp = &level; produce warnings?]
`fp = &level;` is fine. `cp = &level;` is **not**: GCC warns *assignment to 'char \*' from incompatible pointer type 'float \*'*. A pointer should hold addresses of its own type; if you really need a `char` view of the bytes, write the cast yourself: `cp = (char *)&level;`.
:::

:::details[B9. What is a null pointer?]
For every pointer type, C provides a special value that is guaranteed **not to point to any object or function** — the null pointer. In source code it is written as `NULL` or as the constant `0` in a pointer context. It is commonly used to mean "points nowhere yet" or "not found".
:::

:::details[B10. How do a null pointer, NULL, the NUL character and the empty string differ?]
- A **null pointer** is a pointer value that points nowhere.
- **`NULL`** is a macro you write in source code to produce a null pointer.
- The **NUL character** `'\0'` is the character whose bits are all zero; it marks the end of a string. It is a `char`, not a pointer.
- The **empty (null) string** `""` is a string with no visible characters — it still contains one `'\0'`.
:::

:::details[B11. Which header files define NULL?]
Several standard headers define it, including `<stddef.h>`, `<stdio.h>`, `<stdlib.h>`, `<string.h>`, `<time.h>`, `<locale.h>` and `<wchar.h>`. Including any one of them is enough.
:::

:::details[B12. Is a null pointer the same as an uninitialised pointer?]
**No.** A null pointer has a known value that means "points nowhere", and you can test for it (`if (p == NULL)`). An uninitialised local pointer holds whatever happened to be in that memory — an unknown address, often called a **wild pointer**. Using it is undefined behaviour, and you cannot test for it. Initialise pointers to `NULL` if you have nothing better yet.
:::

:::details[B13. What happens if a program writes through a null pointer, and how do you find the bug?]
Writing through a null pointer (for example `int *p = NULL; *p = 5;`) is undefined behaviour. On today's operating systems the low addresses are protected, so the program usually stops immediately with a **segmentation fault**.

Older DOS compilers could not catch this at the moment it happened. They detected the damage only when the program ended and printed *Null pointer assignment*, which made the faulty statement hard to find.

To track it down today:

- Run the program in a debugger (`gdb ./program`, then `run`); it stops on the exact line that used the bad pointer, and `backtrace` shows how you got there.
- Compile with `-fsanitize=address -g`, which reports the bad access with a stack trace.
- A wild (uninitialised or dangling) pointer can cause the same kind of crash, so check where the pointer got its value.
:::

## Part C: Reading Declarations

What does each of these declare?

```c
long ***ledger;
double **grid;
char ****tag;

void record(char *, int *);
double *scale(double *, double **);
int **pick(char *, long **);
```

:::details[Answers]
- `ledger` is a pointer to a pointer to a pointer to a `long`.
- `grid` is a pointer to a pointer to a `double`.
- `tag` is a pointer to a pointer to a pointer to a pointer to a `char`.
- `record` is a function that takes a `char` pointer and an `int` pointer, and returns nothing.
- `scale` is a function that takes a `double` pointer and a pointer to a `double` pointer, and returns a `double` pointer.
- `pick` is a function that takes a `char` pointer and a pointer to a `long` pointer, and returns a pointer to an `int` pointer.

Read a declaration from the name outwards: each `*` next to the name adds "pointer to", and the type at the left is what you finally reach.
:::
