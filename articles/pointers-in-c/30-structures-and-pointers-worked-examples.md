title : Structures and Pointers: Worked Examples

summary : Worked puzzles on structures: the dot versus arrow rule, the addresses and padding of structure members, arrays of structures, structures holding char arrays and char pointers, nested structures, and arrays of structures that point to each other. Predict each output, then read the explanation.

# Structures and Pointers: Worked Examples

These puzzles test the last two articles: declaring and initialising structures, the `.` and `->` operators, how members are laid out in memory, and structures that contain pointers — including pointers to other structures. As always, work out each answer **before** opening the solution. For the harder ones, draw each structure as a row of boxes, one box per member.

All answers assume a typical 64-bit system: 1-byte `char`, 4-byte `int` and `float`, 8-byte pointers. Where a puzzle asks about addresses, the programs print byte offsets from the start of the structure, so the output is the same on every run.

### 1. Dot or arrow?

What happens when this program is compiled?

```c
#include <stdio.h>

struct s
{
    char ch;
    int i;
    float a;
};

void f(struct s v)
{
    printf("%c %d %f\n", v->ch, v->i, v->a);
}

void g(struct s *v)
{
    printf("%c %d %f\n", v.ch, v.i, v.a);
}

int main(void)
{
    struct s var = {'K', 250, 7.25f};

    f(var);
    g(&var);
    return 0;
}
```

:::details[Answer]
It does not compile. GCC reports an error for every member access in both functions:

```
error: invalid type argument of '->' (have 'struct s')
error: 'v' is a pointer; did you mean to use '->'?
```

`f()` is sent the structure variable `var` itself, which it collects in `v` — a `struct s`. But its `printf` uses the arrow operator with `v`, and that is the first error: **on the left of `->` there must always be a pointer to a structure.**

`g()` is the other way round. It collects a **pointer** to a structure, but uses it with the dot operator. **The dot operator must always be preceded by a structure variable**, never a pointer. Hence the second error.

The fix is to swap the operators: `v.ch` in `f`, and `v->ch` in `g`. Then both functions print `K 250 7.250000`.
:::

### 2. Addresses of members, and an array member

```c runnable
#include <stdio.h>
#include <string.h>

int main(void)
{
    struct
    {
        int num;
        float f;
        char mess[50];
    } m;

    m.num = 7;
    m.f = 2.5f;
    strcpy(m.mess, "Every cloud has a silver lining");

    printf("+%td +%td +%td\n", (char *)&m.num - (char *)&m,
           (char *)&m.f - (char *)&m, m.mess - (char *)&m);
    printf("%d %f %s\n", m.num, m.f, m.mess);
    return 0;
}
```

:::details[Answer]
```
+0 +4 +8
7 2.500000 Every cloud has a silver lining
```

The first line shows **where** the members are: `num` at the start of `m`, `f` 4 bytes later (an `int` occupies 4 bytes), and the array `mess` 4 bytes after that (a `float` also occupies 4 bytes). The members of a structure are stored in contiguous memory, in the order they are declared. (Older books print absolute addresses with `%u` and assume a 2-byte `int`, giving addresses such as 1401, 1403 and 1407. Use `%p` for real addresses, or offsets as here.)

The second line prints the three members.

Notice how the message was stored: with `strcpy`, the string copy function. Why not simply write `m.mess = "Every cloud has a silver lining";`, the way we assigned values to `num` and `f`? The answer is an emphatic **no**. Unlike `m.num` and `m.f`, `m.mess` is an **array**, and mentioning an array gives its base address — which can never appear on the left-hand side of an assignment. In other words, `m.mess` is not an *lvalue*. GCC says *assignment to expression with array type*. (A structure **initialiser** can set it, though: `= {7, 2.5f, "Every cloud..."}`.)

Notice also that this structure has no name. As we saw earlier, the type can then only be used in this one declaration.
:::

### 3. An array of structures in memory

Suppose the first structure begins at address 1004.

```c runnable
#include <stdio.h>

int main(void)
{
    struct a
    {
        char arr[10];
        int i;
        float b;
    } v[2];
    char *base = (char *)v;

    printf("+%td +%td +%td\n", v[0].arr - base, (char *)&v[0].i - base, (char *)&v[0].b - base);
    printf("+%td +%td +%td\n", v[1].arr - base, (char *)&v[1].i - base, (char *)&v[1].b - base);
    printf("sizeof(struct a) = %zu\n", sizeof(struct a));
    return 0;
}
```

:::details[Answer]
```
+0 +12 +16
+20 +32 +36
sizeof(struct a) = 20
```

So the addresses are 1004, 1016, 1020 for `v[0]`, and 1024, 1036, 1040 for `v[1]`.

`v` has been declared as an **array of structures**. Although each structure consists of dissimilar data types, more than one **similar** structure can form an array; "similar" (of the same type) is the only requirement for any array. And, keeping with the tradition of arrays, the elements of an array of structures are stored in contiguous memory locations.

![v[0].arr at offsets 0–9, two padding bytes, v[0].i at 12, v[0].b at 16; v[1] starts at offset 20](images/struct-array-padding.svg)

The `char` array `arr` of the first structure uses 10 bytes, at offsets 0 to 9. You might expect the `int` to follow immediately at offset 10 — and older books, written for compilers that packed members tightly with 2-byte `int`s, show exactly that (1004, 1014, 1016). A modern compiler instead adds **2 padding bytes**, so that the 4-byte `int` starts at offset 12, a multiple of 4. The `float` follows at 16. The structure is therefore 20 bytes long, and immediately after it, the second structure begins at offset 20.
:::

### 4. A char array and a char pointer in one structure

```c runnable
#include <stdio.h>

int main(void)
{
    struct a
    {
        char ch[7];
        const char *str;
    };

    struct a s1 = {"Indore", "Bhopal"};

    printf("%c %c\n", s1.ch[0], *s1.str);
    printf("%s %s\n", s1.ch, s1.str);
    return 0;
}
```

:::details[Answer]
```
I B
Indore Bhopal
```

`struct a` comprises a `char` array `ch[]` and a `char` pointer `str`. When `s1` is initialised, the two strings are stored **differently**: `"Indore"` is **copied into** the array `ch[]` (6 letters and a `'\0'` — exactly 7 bytes), while `"Bhopal"` stays where the compiler put it, and only its **address** is stored in `str`.

In the first `printf`, `s1.ch[0]` is the zeroth element of the array `ch[]`. Since this array is inside a structure, it is reached through the structure variable and the dot operator. It holds `'I'`. Next, `*s1.str` means `*(s1.str)` — the dot binds more tightly than `*` — the value at the address stored in `s1.str`. That is the `'B'` of `"Bhopal"`.

The second `printf` prints both strings: `s1.ch` gives the base address of the array, and `s1.str` holds the base address of the literal.

(`str` is declared `const char *` because it points to a string literal, which must not be modified. `s1.ch[0] = 'i';` would be fine, but `s1.str[0] = 'b';` would not.)
:::

### 5. A structure inside a structure, and ++ on its pointers

```c runnable
#include <stdio.h>

int main(void)
{
    struct a
    {
        char ch[7];
        const char *str;
    };

    struct b
    {
        const char *c;
        struct a ss1;
    };

    struct b s2 = {"Surat", {"Indore", "Bhopal"}};

    printf("%s %s\n", s2.c, s2.ss1.str);
    printf("%s %s\n", ++s2.c, ++s2.ss1.str);
    return 0;
}
```

:::details[Answer]
```
Surat Bhopal
urat hopal
```

`s2` is a variable of type `struct b`, which is made up of a `char` pointer `c` and a variable `ss1` of type `struct a`. While initialising `s2`, the base address of `"Surat"` is assigned to `s2.c`; `"Indore"` is copied into `s2.ss1.ch[]`; and the base address of `"Bhopal"` is assigned to `s2.ss1.str`. The inner braces mirror the nesting. (Older code leaves them out — `{"Surat", "Indore", "Bhopal"}` — which C allows, filling the members in order; GCC's `-Wall` then warns *missing braces around initializer*.)

The first `printf` is supplied `s2.c`, the base address of `"Surat"`, and `s2.ss1.str`, the base address of `"Bhopal"`, and prints both strings.

The second `printf` uses incremented values of these addresses. `++s2.c` means `++(s2.c)`: the **pointer** member is incremented, so it now points to the next character, the `'u'` of `"Surat"`. Similarly, after `++s2.ss1.str` it points to the `'h'` of `"Bhopal"`. With these as starting addresses, the rest of each string is printed. Note that only the pointers changed; the strings themselves are untouched. (Incrementing `s2.ss1.ch` would not compile: an array name cannot be incremented.)
:::

### 6. Structures that point to each other

```c runnable
#include <stdio.h>

int main(void)
{
    struct s1
    {
        const char *z;
        int i;
        struct s1 *p;
    };

    struct s1 a[] = {
        {"Agra", 1, a + 1},
        {"Pune", 2, a + 2},
        {"Goa", 3, a}
    };
    struct s1 *ptr = a;

    printf("%s %s %s\n", a[0].z, ptr->z, a[2].p->z);
    return 0;
}
```

:::details[Answer]
```
Agra Agra Agra
```

The members of `struct s1` are a `char` pointer `z` and an `int` `i`, as before. The third member is what is new: `p` is a **pointer to a structure of the same type**. That is, `p` stores the starting address of a `struct s1`.

Next, `a[]`, an array of such structures, is declared and initialised. The base address of `"Agra"` is stored in `a[0].z`, 1 in `a[0].i`, and `a + 1` in `a[0].p`. On similar lines, the remaining two elements are initialised: `a[1]` gets `"Pune"`, 2 and `a + 2`; `a[2]` gets `"Goa"`, 3 and `a`.

What exactly do `a`, `a + 1` and `a + 2` signify? `a`, of course, is the base address of the array `a[]` — the address of `a[0]`. And when we say `a + 1`, we do **not** arrive at the next byte: on incrementing any pointer, it points to the next location **of its type**. `a` points to a structure, so `a + 1` is the address of the next structure, `a[1]`, and `a + 2` is the address of `a[2]`. So the three structures are linked in a ring:

![a[0].p points to a[1], a[1].p points to a[2], and a[2].p points back to a[0]; ptr points to a[0]](images/struct-array-self-links.svg)

Each element is 24 bytes here, so `a + 1` is 24 bytes beyond `a`. (With the 2-byte pointers and `int`s of old 16-bit compilers, each element was 6 bytes, and older books show the elements at 4000, 4006 and 4012.)

Now the `printf`:

- `a[0].z` is the address where `"Agra"` is stored, so `"Agra"` is printed.
- `ptr` contains the address of `a[0]`, so `ptr->z` is the member `z` of `a[0]` — `"Agra"` again.
- `a[2].p->z`: the left side of `->` must be the address of a structure. Which structure does `a[2].p` point to? It contains `a`, the address of `a[0]`. So the expression is the same as `a->z`, the member `z` of the zeroth structure — `"Agra"` a third time.

(Older versions declare the array `static`, because very old compilers accepted addresses in an array's initialiser only for `static` arrays. Since C99, an ordinary local array can be initialised this way.)
:::

### 7. Decrementing and incrementing members in a loop

```c runnable
#include <stdio.h>

int main(void)
{
    struct s1
    {
        const char *str;
        int i;
        struct s1 *ptr;
    };

    struct s1 a[] = {
        {"Agra", 1, a + 1},
        {"Pune", 2, a + 2},
        {"Goa", 3, a}
    };

    for (int j = 0; j <= 2; j++) {
        printf("%d ", --a[j].i);
        printf("%s\n", ++a[j].str);
    }
    return 0;
}
```

:::details[Answer]
```
0 gra
1 une
2 oa
```

The structure is like the one just encountered. The `for` loop is executed for three values of `j`: 0, 1 and 2.

The first time through the loop, `j` is 0, so the first `printf` prints `--a[0].i`. The `.` operator (and `[]`) have higher priority than `--`, so first `a[0].i` is reached, which is 1. As `--` comes **before** it, 1 is decremented to 0, and **then** printed.

The second `printf` prints the string at the address `++a[0].str`. `a[0].str` holds the starting address of `"Agra"`; incremented, it points to the next character, `'g'`, so starting from `'g'` the rest of the string, `gra`, is printed.

The same procedure is repeated for `j = 1` and `j = 2`, after which the loop ends. Notice that these changes are permanent: after the loop, `a[0].i` is 0 and `a[0].str` points to `"gra"`.
:::
