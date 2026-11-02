title : File Pointers: What FILE * Really Is

summary : Every file a C program opens is reached through a FILE *. Learn what that pointer points to (a structure holding a buffer and a position), how fopen, fgetc and fclose use it, and why the character read from a file must be stored in an int, never a char.

# File Pointers: What FILE * Really Is

The chapters so far used pointers to reach variables, arrays, strings and structures in memory. The rest of this course looks at some places where pointers turn up in everyday C without always being recognised as pointers: **file pointers**, **pointers to functions**, **variable argument lists**, and the special pointers of old 16-bit systems.

We begin with files. Every C program that reads or writes a file uses a pointer of type `FILE *`. Most people learn to write `FILE *fp = fopen(...)` as a magic formula. This article shows what is really behind it.

## Counting the Characters in a File

Here is a program that counts how many characters a file contains. So that it can run anywhere, it first creates a small file, then reopens it and counts:

```c runnable
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp;
    int ch;                                    /* int, not char: it must also hold EOF */
    long noc = 0;

    /* first create a small file to count */
    fp = fopen("poem.txt", "w");
    if (fp == NULL) {
        perror("poem.txt");
        return EXIT_FAILURE;
    }
    fputs("Twinkle, twinkle, little star,\nHow I wonder what you are.\n", fp);
    fclose(fp);

    /* now open it for reading and count its characters */
    fp = fopen("poem.txt", "r");
    if (fp == NULL) {
        perror("poem.txt");
        return EXIT_FAILURE;
    }

    while ((ch = fgetc(fp)) != EOF)            /* read one character at a time */
        noc++;

    fclose(fp);
    printf("Number of characters = %ld\n", noc);

    remove("poem.txt");                        /* tidy up */
    return 0;
}
```

```
Number of characters = 58
```

The two lines of the poem have 31 and 27 characters, including the newline (`\n`) at the end of each: 58 in all.

The counting itself is three lines:

```c
fp = fopen("poem.txt", "r");
while ((ch = fgetc(fp)) != EOF)
    noc++;
fclose(fp);
```

- **`fopen()`** opens the file and returns a `FILE *`. `"r"` asks for reading; `"w"` (used above to create the file) for writing, erasing any old contents.
- **`fgetc(fp)`** returns the next character of the file each time it is called. When there are no characters left, it returns the special value **`EOF`** (end of file), a negative number defined in `<stdio.h>` (usually −1).
- **`fclose(fp)`** closes the file.

Notice the parentheses in `while ((ch = fgetc(fp)) != EOF)`. The `!=` operator binds more tightly than `=`. Without the inner parentheses, `ch = fgetc(fp) != EOF` would store the **result of the comparison** (1 or 0) in `ch`, not the character. The parentheses make the assignment happen first, and then the value just assigned is compared with `EOF`.

Also notice the check `if (fp == NULL)`. `fopen()` returns `NULL` when it cannot open the file — it may not exist, or the program may not have permission. Using a `NULL` file pointer crashes the program, so the result of `fopen()` must always be checked. `perror()` prints a message explaining why the last library call failed.

## What Is fp Pointing To?

`fp` is declared as `FILE *fp;` — a pointer to a `FILE`. `FILE` is a structure type, defined (with `typedef`) in `<stdio.h>`. Its members are not part of the C language; each library defines them as it needs. Old DOS compilers, for example, used a structure like this:

```c
typedef struct
{
    short level;            /* fill/empty level of buffer */
    unsigned flags;         /* file status flags */
    char fd;                /* file descriptor */
    unsigned char hold;     /* ungetc char if no buffer */
    short bsize;            /* buffer size */
    unsigned char *buffer;  /* data transfer buffer */
    unsigned char *curp;    /* current active pointer */
    unsigned istemp;        /* temporary file indicator */
    short token;            /* used for validity checking */
} FILE;
```

The GNU C library on Linux uses a different, larger structure. That is why a program should never touch the members directly: it treats `FILE` as an **opaque** type, used only through a pointer and the library functions.

What happens when a file is opened?

![fp holds 200, the address of a FILE structure. The structure records the address of a buffer (300), the current position in it, the number of characters left and the file descriptor. getc returns the character at the current position; the buffer is refilled from the disk file a block at a time](images/file-pointer-structure.svg)

1. `fopen()` asks the operating system to open the file, and receives a small number, the **file descriptor**, that identifies it.
2. It allocates a **buffer** in memory and, when reading starts, fills it with a block of the file's contents (often 4096 bytes at a time).
3. It allocates a `FILE` structure that records where the buffer is, how many characters it still holds, which character comes next, and the file descriptor.
4. It returns the **address of that structure**. That address is what we store in `fp`.

Each call to `fgetc(fp)` uses `fp` to find the structure, returns the character at the current position in the buffer, and moves the current position on by one. Only when the buffer runs out does the library go back to the disk for the next block. This is why reading a file one character at a time is fast: almost every `fgetc()` is just a pointer increment in memory.

So `fgetc()` needs `fp` as an argument for the same reason any function needs a pointer to a structure it must update: to reach and change the bookkeeping that belongs to that particular open file.

`fclose(fp)` writes out anything still waiting in the buffer (when writing), tells the operating system the file is no longer needed, and frees the buffer and the structure. After `fclose()`, `fp` is a dangling pointer and must not be used again.

Writing to a file works the same way in reverse: `fputc()` and `fputs()` put characters into the buffer, and the library writes the buffer to the disk when it is full, or when the file is closed.

Each `fopen()` creates its **own** structure, so two open files never interfere with each other. And the three streams every program starts with — `stdin` (keyboard), `stdout` (screen) and `stderr` (error messages) — are `FILE *` values too:

```c runnable
#include <stdio.h>

int main(void)
{
    FILE *a = tmpfile(), *b = tmpfile();
    if (a == NULL || b == NULL)
        return 1;

    printf("sizeof(FILE *) = %zu bytes\n", sizeof(FILE *));
    printf("a and b point to %s FILE structures\n", a == b ? "the same" : "different");
    printf("stdin, stdout and stderr are FILE * too: %s\n",
           stdin != NULL && stdout != NULL && stderr != NULL ? "yes" : "no");

    fputs("abc", a);                           /* each FILE keeps its own position */
    fputs("12345", b);
    printf("position in a: %ld, position in b: %ld\n", ftell(a), ftell(b));

    fclose(a);
    fclose(b);
    return 0;
}
```

```
sizeof(FILE *) = 8 bytes
a and b point to different FILE structures
stdin, stdout and stderr are FILE * too: yes
position in a: 3, position in b: 5
```

`tmpfile()` creates a temporary file that is deleted automatically when it is closed — convenient for demonstrations. `ftell()` reports the current position recorded in each structure: 3 characters written to one file, 5 to the other.

## Why ch Must Be an int

One detail of the counting program deserves special attention: `ch` is declared as `int`, not `char`, even though it holds characters. Older programs often write `char ch;`, and that is a real bug.

`fgetc()` returns an `int` for a reason. It must be able to return **every** possible byte value, 0 to 255, **and** one more value, `EOF`, that is different from all of them. That is 257 different values; a `char` has only 256. Storing the result in a `char` throws away the difference between the byte 255 and `EOF`:

```c runnable
#include <stdio.h>

/* counts the bytes of a file, storing each one first in an int, then in a char */
long count_with_int(FILE *fp)
{
    long n = 0;
    int ch;

    while ((ch = fgetc(fp)) != EOF)
        n++;
    return n;
}

long count_with_char(FILE *fp)
{
    long n = 0;
    char ch;

    while ((ch = (char)fgetc(fp)) != EOF) {    /* the classic mistake */
        n++;
        if (n > 100) {                         /* safety stop for this demo */
            printf("(never stopped by itself) ");
            break;
        }
    }
    return n;
}

int main(void)
{
    unsigned char data[] = {'A', 'B', 0xFF, 'C', 'D'};   /* byte 255 in the middle */
    FILE *fp = tmpfile();                      /* a temporary binary file */
    if (fp == NULL)
        return 1;
    fwrite(data, 1, sizeof data, fp);

    rewind(fp);
    printf("Counting into an int:  %ld bytes\n", count_with_int(fp));
    rewind(fp);
    printf("Counting into a char:  %ld bytes\n", count_with_char(fp));

    fclose(fp);
    return 0;
}
```

```
Counting into an int:  5 bytes
Counting into a char:  2 bytes
```

The file holds five bytes, one of which is 255. With an `int`, all five are counted. With a `char`, what happens depends on whether `char` is signed on your system:

- Where `char` is **signed** (most PCs), the byte 255 is stored as −1 — the same as `EOF` — so the loop stops early, at the third byte, as shown above. The rest of the file is never read.
- Where `char` is **unsigned** (common on ARM processors), `EOF` itself becomes 255 when stored, so `ch` is **never** equal to −1, and the loop never stops at the end of the file. That is why this demonstration has a safety limit.

Text files rarely contain the byte 255, so the bug can hide for years — until the program meets a binary file, or text in some other encoding. Always store the result of `fgetc()`, `getc()` and `getchar()` in an `int`, compare it with `EOF`, and only then treat it as a character.

## Key Takeaways

- `fopen()` returns a `FILE *`: the address of a structure, created by the library, that records the file's buffer, the current position and the operating system's file descriptor. It returns `NULL` on failure — always check.
- `fgetc()`, `fputc()` and the other file functions take the `FILE *` so that they can find and update that structure. Most reads and writes only touch the buffer in memory.
- `fclose()` flushes the buffer and frees the structure; do not use the pointer afterwards.
- Treat `FILE` as opaque: its members differ between libraries.
- Store the result of `fgetc()` in an `int`; a `char` cannot tell the byte 255 apart from `EOF`.
- Write `(ch = fgetc(fp)) != EOF` with the inner parentheses, because `!=` binds more tightly than `=`.

## Practice Questions

:::details[What is wrong with: FILE *fp = fopen("data.txt", "r"); int c = fgetc(fp); — if data.txt does not exist?]
`fopen()` returns `NULL`, and `fgetc(NULL)` follows a null pointer — undefined behaviour, usually a crash. Check `if (fp == NULL)` before using `fp`.
:::

:::details[What does ch hold after ch = fgetc(fp) != EOF; when the next character is 'A'?]
**1**. Without the extra parentheses, `fgetc(fp) != EOF` is evaluated first (it is true, so 1), and that 1 is stored in `ch`. Write `(ch = fgetc(fp)) != EOF`.
:::

:::details[Why does reading a file one character at a time with fgetc() not mean one disk access per character?]
`fgetc()` reads from the buffer that the `FILE` structure points to. The library refills that buffer from the disk a whole block at a time, so most calls just return the next byte from memory and move the current position.
:::

:::details[Write a program that counts the lines in a file.]
Count the newline characters:
```c
int ch;
long lines = 0;

while ((ch = fgetc(fp)) != EOF)
    if (ch == '\n')
        lines++;
```
(If the last line has no newline at the end, add one more when the file is non-empty and the last character read was not `'\n'`.)
:::
