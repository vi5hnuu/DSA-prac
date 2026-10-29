title : Structures and Linked Lists: Output Exercises

summary : Five exercises on structures and pointers: arrays of pointers to structures, a list built from malloc'd nodes, 2-D char arrays inside a structure, nested structures reached through a pointer, and calling a function before it is declared. Work out each output, then check the answer and the bugs hidden in each.

# Structures and Linked Lists: Output Exercises

Five more programs to trace on your own. Unlike the worked examples, these come without a walkthrough in the question — work out the output first, then open the answer. Each answer also points out what the program does **wrong** or **unsafely**, because several of them contain a classic mistake that compiles but should not be copied.

All answers assume a typical 64-bit system: 4-byte `int`, 8-byte pointers.

### 1. Pointers to structures in a different order

What will be the output of this program?

```c runnable
#include <stdio.h>

int main(void)
{
    struct a
    {
        const char *str;
        struct a *ptr;
    };

    struct a arr[] = {
        {"Lina", arr + 2},
        {"Omar", arr},
        {"Priya", arr + 1}
    };
    struct a *p[3];

    for (int i = 0; i <= 2; i++)
        p[i] = arr[i].ptr;

    printf("%s\n", p[0]->str);
    printf("%s\n", (*p)->str);
    printf("%s\n", (**p).str);
    return 0;
}
```

:::details[Answer]
```
Priya
Priya
Priya
```

The loop copies each structure's `ptr` member into `p[]`. `arr[0].ptr` is `arr + 2`, so `p[0]` points to `arr[2]`; likewise `p[1]` points to `arr[0]` and `p[2]` to `arr[1]`.

- `p[0]->str` is `arr[2].str`: `Priya`.
- `*p` is the same as `p[0]`, so `(*p)->str` is `Priya` again.
- `**p` is the structure `p[0]` points to — `arr[2]` itself — so `(**p).str` is `Priya` a third time.

Older versions of this exercise print the last line with `printf("%s", **p);`. That passes a whole structure where `%s` needs a `char *`: GCC's `-Wall` warns, and the behaviour is undefined. To print a member, name the member.
:::

### 2. A list built through an array of pointers

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    struct a
    {
        struct a *next;
        int data;
    };
    struct a *ptr[3];

    for (int i = 0; i < 3; i++) {
        ptr[i] = malloc(sizeof(struct a));
        if (ptr[i] == NULL)
            return 1;
    }

    ptr[0]->data = 13;
    ptr[1]->data = 26;
    ptr[2]->data = 39;
    ptr[0]->next = ptr[1];
    ptr[1]->next = ptr[2];
    ptr[2]->next = NULL;

    while (ptr[0] != NULL) {
        printf("%d\n", ptr[0]->data);
        ptr[0] = ptr[0]->next;
    }

    free(ptr[1]);
    free(ptr[2]);
    return 0;
}
```

:::details[Answer]
```
13
26
39
```

`ptr[]` is an array of three pointers to structures. Each is given a block from `malloc`, large enough for one `struct a`. The `data` parts are filled in, and the `next` parts link the three blocks into a list: the first points to the second, the second to the third, and the third's `next` is `NULL`.

The `while` loop walks the list **using `ptr[0]` itself** as the moving pointer: it prints `ptr[0]->data`, then moves `ptr[0]` to the next node, until it becomes `NULL`. So `13`, `26` and `39` are printed.

But there is a cost. When the loop ends, `ptr[0]` is `NULL`, and the address of the **first** block is gone: nothing points to it any more, so it can never be freed. This program frees the other two blocks (their addresses are still in `ptr[1]` and `ptr[2]`), and the first one leaks. AddressSanitizer catches exactly this: *Direct leak of 16 byte(s) in 1 object(s)*.

The fix is the habit from the linked-list articles — walk with a **copy**, so that the address of the first node is kept, and then every node can be freed:

```c runnable
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    struct a
    {
        struct a *next;
        int data;
    };
    struct a *ptr[3];

    for (int i = 0; i < 3; i++) {
        ptr[i] = malloc(sizeof(struct a));
        if (ptr[i] == NULL)
            return 1;
    }

    ptr[0]->data = 13;
    ptr[1]->data = 26;
    ptr[2]->data = 39;
    ptr[0]->next = ptr[1];
    ptr[1]->next = ptr[2];
    ptr[2]->next = NULL;

    for (struct a *t = ptr[0]; t != NULL; t = t->next)   /* walk with a copy */
        printf("%d\n", t->data);

    for (int i = 0; i < 3; i++)                          /* ptr[0] is still valid */
        free(ptr[i]);
    return 0;
}
```

```
13
26
39
```

(Older versions of this program also include `"alloc.h"`, a header of old DOS compilers. `malloc` is declared in `<stdlib.h>`.)
:::

### 3. Two-dimensional char arrays inside a structure

```c
#include <stdio.h>

struct a
{
    char city[3][20];
    char state[3][20];
};

int main(void)
{
    struct a arr = {
        {"Mysuru", "Jaipur", "Kochi"},
        {"Karnataka", "Rajasthan", "Kerala"}
    };

    printf("%s %s\n", arr.city, arr.state);
    printf("%s %s\n", arr.city + 2, arr.state + 2);
    return 0;
}
```

:::details[Answer]
In practice it prints:

```
Mysuru Karnataka
Kochi Kerala
```

`arr` is a single structure containing two 2-D `char` arrays, each holding three strings of up to 19 characters. The initialiser fills `city` with three city names and `state` with three state names.

`arr.city` is a 2-D array, so mentioning it gives the address of its first **row**: a pointer to an array of 20 `char`s, `char (*)[20]`. That address is the same as the address of the first character of `"Mysuru"`, so `%s` prints `Mysuru`; likewise `arr.state` prints `Karnataka`. `arr.city + 2` moves **two rows** (40 bytes) forward, to the third string, `"Kochi"`; and `arr.state + 2` reaches `"Kerala"`.

It prints the expected text, but the types are wrong: `%s` expects a `char *`, not a pointer to a row. GCC says so with `-Wall`:

```
warning: format '%s' expects argument of type 'char *', but argument 2 has type 'char (*)[20]'
```

The correct way names the row, which then gives a `char *` to its first character:

```c runnable
#include <stdio.h>

struct a
{
    char city[3][20];
    char state[3][20];
};

int main(void)
{
    struct a arr = {
        {"Mysuru", "Jaipur", "Kochi"},
        {"Karnataka", "Rajasthan", "Kerala"}
    };

    printf("%s %s\n", arr.city[0], arr.state[0]);
    printf("%s %s\n", arr.city[2], arr.state[2]);   /* or *(arr.city + 2) */
    return 0;
}
```

```
Mysuru Karnataka
Kochi Kerala
```
:::

### 4. Nested structures through a pointer

```c runnable
#include <stdio.h>

int main(void)
{
    struct a
    {
        struct b
        {
            char name[10];
            int age;
        } bb;
        struct c
        {
            char address[50];
            int sal;
        } cc;
    };

    struct a *ptr;
    struct a aa = {
        {"Farida", 41},
        {"12, Lake Road, Bhopal", 5200}
    };

    ptr = &aa;
    printf("%s %s %d %d\n", ptr->bb.name, ptr->cc.address, ptr->bb.age, ptr->cc.sal);
    return 0;
}
```

:::details[Answer]
```
Farida 12, Lake Road, Bhopal 41 5200
```

`struct a` contains two structures, `bb` and `cc`, declared right inside it. The initialiser has one pair of inner braces for each of them, in order.

`ptr` holds the address of `aa`, so the `->` operator reaches the members of `aa`, and then `.` goes one level deeper:

- `ptr->bb.name` is `aa.bb.name`, `"Farida"`;
- `ptr->cc.address` is `aa.cc.address`, `"12, Lake Road, Bhopal"`;
- `ptr->bb.age` and `ptr->cc.sal` are 41 and 5200.

Note the mix of operators: `->` is used once, because `ptr` is a pointer; `.` is used for `bb` and `cc`, because they are structures, not pointers to structures. `ptr->bb.name` means `(ptr->bb).name`, since `->` and `.` have the same priority and group left to right.

(Unlike C++, C makes `struct b` and `struct c` ordinary types visible outside `struct a`: you could declare `struct b x;` later in the same function.)
:::

### 5. Calling a function before it is declared

```c
#include <stdio.h>

struct b
{
    char name[10];
    char address[50];
};

int main(void)
{
    struct b bb = {"Tanvir", "Flat 4, Green Park, Indore"};

    print(&bb);
    return 0;
}

void print(const struct b *bb)
{
    printf("%s\n", bb->name);
    printf("%s\n", bb->address);
}
```

:::details[Answer]
**It depends on the compiler — and on modern compilers, it does not compile.** The problem is that `main` calls `print()` before the compiler has seen any declaration of it.

In the original 1989 C standard, an undeclared function was **implicitly declared** as returning `int`, with unknown parameters. Older books rely on this: their version defines `print` without a return type (so it also returns `int` by default), the guess happens to match, and the program prints the name and the address.

C99 removed implicit declarations from the language. Today:

- **GCC 13** compiles it with two warnings: *implicit declaration of function 'print'* and *conflicting types for 'print'*, because the implicit guess (`int`) does not match the real definition (`void`). A mismatch like this is undefined behaviour.
- **GCC 14** and later, and **Clang**, reject it outright: *call to undeclared function 'print'; ISO C99 and later do not support implicit function declarations*.

The fix is to declare the function before it is used — with a **prototype** above `main`, or by placing the whole definition above `main`:

```c runnable
#include <stdio.h>

struct b
{
    char name[10];
    char address[50];
};

void print(const struct b *bb);            /* prototype: declared before use */

int main(void)
{
    struct b bb = {"Tanvir", "Flat 4, Green Park, Indore"};

    print(&bb);
    return 0;
}

void print(const struct b *bb)
{
    printf("%s\n", bb->name);
    printf("%s\n", bb->address);
}
```

```
Tanvir
Flat 4, Green Park, Indore
```

Also notice that `struct b` is declared **outside** `main`. If it were declared inside `main`, the type would not exist for `print`, and its parameter could not be declared.
:::
