title : Pointers Miscellany: Exercises with Solutions

summary : Exercises with answers: animate the colours of video memory, make text rain down the screen, read and set the BIOS clock, decode the equipment word, predict outputs involving function pointers, far pointers and argv, and answer short questions on near, far and huge pointers.

# Pointers Miscellany: Exercises with Solutions

These exercises cover the previous articles: file pointers, pointers to functions, command-line arguments, variable argument lists, near/far/huge pointers and memory-mapped hardware. The hardware exercises were written for DOS PCs, where a program could write directly to video memory and the BIOS data area. As in the previous article, the solutions here run against a **simulated** memory, so the pointer logic can be tried on any computer.

## Part A: Programs to Write

### 1. Changing the colours of the screen

Every character on the text screen has two bytes in video memory: its code, then its colour. Write a program that continuously changes the colour of the characters on the screen.

:::details[Solution]
```c runnable
#include <stdio.h>
#include <stdint.h>

#define COLS 80

static unsigned char memory[1 << 20];         /* simulated real-mode memory */

unsigned char *at(uint32_t physical) { return &memory[physical]; }

/* gives every character on the screen the next colour (attribute) value */
void next_colours(void)
{
    unsigned char *scr = at(0xB8000);

    for (int i = 1; i < 80 * 25 * 2; i += 2)   /* odd offsets: the colour bytes */
        scr[i] = (unsigned char)(scr[i] + 1);  /* 255 wraps round to 0 */
}

int main(void)
{
    unsigned char *scr = at(0xB8000);
    const char *text = "Colours!";

    for (int i = 0; text[i] != '\0'; i++) {    /* put some text on row 0 */
        scr[2 * i] = (unsigned char)text[i];
        scr[2 * i + 1] = 0x07;                 /* light grey on black */
    }

    for (int round = 0; round < 4; round++) {  /* the real program looped forever */
        printf("round %d: '%c' has colour %02X, '%c' has colour %02X\n",
               round, scr[0], scr[1], scr[2], scr[3]);
        next_colours();
    }
    return 0;
}
```

```
round 0: 'C' has colour 07, 'o' has colour 07
round 1: 'C' has colour 08, 'o' has colour 08
round 2: 'C' has colour 09, 'o' has colour 09
round 3: 'C' has colour 0A, 'o' has colour 0A
```

The colour bytes are the **odd** offsets of video memory, so the loop starts at 1 and steps by 2, visiting only them. Adding 1 to each moves every character to the next of the 256 possible attributes; since the bytes are `unsigned char`, 255 + 1 wraps round to 0. The real program would put this in an endless loop (with a short delay, so that the colours change visibly rather than in a blur). Note that the address of video memory is B8000 for colour displays and B0000 for monochrome ones (older books print B8000000h for both — a slip).
:::

### 2. It's raining

Write a program which makes the characters on the top row of the screen fall down one by one. Characters in the path of a falling character are wiped out. As the characters reach the bottom of the screen, they should build up the message: *It's raining, it's pouring, while the old PC is snoring*.

:::details[Solution]
Here the "screen" is a small 2-D array, and the message starts on the top row:

```c runnable
#include <stdio.h>
#include <string.h>

#define ROWS 6
#define COLS 55

char screen[ROWS][COLS + 1];                   /* +1 for a '\0' to print each row */

void show(const char *title)
{
    printf("%s\n", title);
    for (int r = 0; r < ROWS; r++)
        printf("|%s|\n", screen[r]);
}

int main(void)
{
    const char *msg = "It's raining, it's pouring, while the old PC is snoring";
    int len = (int)strlen(msg);

    for (int r = 0; r < ROWS; r++) {           /* some text that will be wiped out */
        memset(screen[r], r == 0 ? ' ' : '.', COLS);
        screen[r][COLS] = '\0';
    }
    memcpy(screen[0], msg, (size_t)len);       /* the message on the top row */
    show("Before:");

    /* each character falls, one by one, down its own column */
    for (int c = 0; c < len; c++) {
        char ch = screen[0][c];
        for (int r = 0; r < ROWS - 1; r++) {
            screen[r][c] = ' ';                /* leave the current row (wiping it) */
            screen[r + 1][c] = ch;             /* and land on the next one */
        }
    }
    show("After:");
    return 0;
}
```

```
Before:
|It's raining, it's pouring, while the old PC is snoring|
|.......................................................|
|.......................................................|
|.......................................................|
|.......................................................|
|.......................................................|
After:
|                                                       |
|                                                       |
|                                                       |
|                                                       |
|                                                       |
|It's raining, it's pouring, while the old PC is snoring|
```

Each character in turn moves down its column one row at a time: the cell it leaves is set to a space, and the cell it lands on gets the character — overwriting (wiping out) whatever was there. When all the characters have fallen, the message stands in the last row and the rest of the screen is clear.

On a real screen, you would draw each step and pause briefly, so the fall can be seen. With video memory, "the cell at row *r*, column *c*" is the byte at offset 2 × (*r* × 80 + *c*).
:::

### 3. The system clock

The BIOS counts clock ticks since midnight, as a 4-byte number at address 46C. There are 18.2 ticks per second, so 01:04:44 corresponds to 44 × 18.2 + 4 × 60 × 18.2 + 1 × 60 × 60 × 18.2 = 70688 ticks. Write a program to print the current system time in HH:MM:SS format, and a program to change the system time.

:::details[Solution]
```c runnable
#include <stdio.h>
#include <stdint.h>

static unsigned char memory[1 << 20];         /* simulated real-mode memory */

#define TICKS_PER_SEC 18.2

/* the 4-byte tick count at 46Ch, stored little-endian */
uint32_t read_ticks(void)
{
    const unsigned char *p = &memory[0x46C];
    return p[0] | (uint32_t)p[1] << 8 | (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24;
}

void write_ticks(uint32_t t)
{
    unsigned char *p = &memory[0x46C];
    for (int i = 0; i < 4; i++)
        p[i] = (unsigned char)(t >> (8 * i));
}

uint32_t time_to_ticks(int h, int m, int s)
{
    return (uint32_t)((h * 3600 + m * 60 + s) * TICKS_PER_SEC);
}

void print_time(uint32_t ticks)
{
    long secs = (long)(ticks / TICKS_PER_SEC + 0.5);   /* round to the nearest second */
    printf("%02ld:%02ld:%02ld\n", secs / 3600, secs / 60 % 60, secs % 60);
}

int main(void)
{
    write_ticks(time_to_ticks(1, 4, 44));
    printf("ticks at 01:04:44 = %lu\n", (unsigned long)read_ticks());
    printf("current time: ");
    print_time(read_ticks());

    write_ticks(time_to_ticks(13, 30, 5));     /* "change the system time" */
    printf("after setting: ");
    print_time(read_ticks());
    return 0;
}
```

```
ticks at 01:04:44 = 70688
current time: 01:04:44
after setting: 13:30:05
```

- `read_ticks()` assembles the 4-byte number from its bytes, low byte first (little-endian); `write_ticks()` stores it back the same way. On the real machine, a single `unsigned long far *ticks` pointer to 0040:006C did both jobs.
- Converting ticks to time divides by 18.2 to get seconds, then splits them with `/` and `%`: `secs / 3600` hours, `secs / 60 % 60` minutes, `secs % 60` seconds. Rounding to the nearest second avoids printing 01:04:43 because of the fraction lost when the ticks were stored as a whole number.
- "Changing the system time" means writing a new tick count.

(The exact rate is 1193180 / 65536 ≈ 18.2065 ticks per second; 18.2 is the usual approximation.)
:::

### 4. The equipment list

The BIOS stores a list of the equipment attached to the computer in the two bytes at 410 and 411, coded bit by bit:

| Bits | Meaning |
|---|---|
| 0 | Disk drive present / absent |
| 1 | Maths coprocessor present / absent |
| 2–3 | Unused |
| 4–5 | Initial video mode |
| 6–7 | Number of disk drives (minus 1) |
| 8 | DMA chip present / absent |
| 9–11 | Number of serial ports |
| 12 | Game adapter present / absent |
| 13 | Unused |
| 14–15 | Number of parallel ports |

Write a program to display the list of equipment attached to the computer.

:::details[Solution]
```c runnable
#include <stdio.h>
#include <stdint.h>

static unsigned char memory[1 << 20];         /* simulated real-mode memory */

int main(void)
{
    /* a sample equipment word: 2 floppy drives, maths coprocessor, 80x25 colour,
       2 serial ports, 1 parallel port */
    memory[0x410] = 0x63;                      /* low byte  0110 0011 */
    memory[0x411] = 0x44;                      /* high byte 0100 0100 */

    unsigned w = memory[0x410] | (unsigned)memory[0x411] << 8;
    const char *video[4] = {"EGA/VGA or none", "40 x 25 colour", "80 x 25 colour", "80 x 25 monochrome"};

    printf("Equipment word: %04X\n", w);
    printf("Disk drive present:     %s\n", (w & 0x0001) ? "yes" : "no");
    printf("Maths coprocessor:      %s\n", (w & 0x0002) ? "yes" : "no");
    printf("Initial video mode:     %s\n", video[(w >> 4) & 0x3]);
    printf("Disk drives:            %u\n", (w & 0x0001) ? ((w >> 6) & 0x3) + 1 : 0);
    printf("DMA chip present:       %s\n", (w & 0x0100) ? "no" : "yes");
    printf("Serial ports:           %u\n", (w >> 9) & 0x7);
    printf("Game adapter:           %s\n", (w & 0x1000) ? "yes" : "no");
    printf("Parallel ports:         %u\n", (w >> 14) & 0x3);
    return 0;
}
```

```
Equipment word: 4463
Disk drive present:     yes
Maths coprocessor:      yes
Initial video mode:     80 x 25 colour
Disk drives:            2
DMA chip present:       yes
Serial ports:           2
Game adapter:           no
Parallel ports:         1
```

A field of several bits is extracted with a **shift** followed by a **mask**: `(w >> 9) & 0x7` moves bits 9–11 down to the bottom and keeps only those three bits. A single bit is tested with a mask such as `w & 0x0002`.

Two details from the original IBM documentation: bits 6–7 hold the number of drives **minus one** (so 01 means two drives), and bit 8 is **0** when a DMA chip is present.
:::

### 5. A variadic sort

Write a function that arranges the numbers passed to it in ascending or descending order, using a variable argument list. Its fixed arguments are: an integer indicating the order, and an integer giving the number of arguments that follow.

:::details[Solution]
This is the `sort_print()` function in the article on variable argument lists: it copies the unnamed arguments into a `malloc`'d array with `va_arg()`, sorts the array, and prints it.
:::

## Part B: What Will Be the Output?

### 1.

```c runnable
#include <stdio.h>

void print(void);

int main(void)
{
    void (*message)(void);

    print();
    message = print;
    (*message)();
    return 0;
}

void print(void)
{
    printf("Never trouble trouble till trouble troubles you\n");
}
```

:::details[Answer]
```
Never trouble trouble till trouble troubles you
Never trouble trouble till trouble troubles you
```

`print()` is called once directly. Then its address is stored in `message`, a pointer to a function, and `(*message)()` calls it a second time.
:::

### 2.

```c
main()
{
    long far *a;

    printf("\nLove makes life lovely");
    printf("\nPress any key...");
    a = 36;
    *a = 0;
    getch();
    printf("... except when you hit a key");
}
```

:::details[Answer]
It prints the first two lines, and then the computer **hangs**: pressing a key does nothing, and the last line is never printed.

The far pointer `a` is given the value 36 = 0x24, that is, 0000:0024. The first 1024 bytes of a real-mode PC's memory hold the **interrupt vector table**: 256 four-byte far addresses of the routines that handle hardware and software interrupts. Address 0x24 is entry 9 (9 × 4 = 36) — the address of the **keyboard** interrupt handler. Writing 0 there makes every keypress jump to address 0000:0000, which is not a keyboard handler, so `getch()` never receives the key. (On a modern operating system, writing to address 36 would just crash the program with a segmentation fault.)
:::

### 3. Run as: PR5 aabbcc

```c runnable
#include <stdio.h>

/* stands in for main(argc, argv) run as: PR5 aabbcc */
void fake_main(int argc, char *argv[])
{
    (void)argc;
    printf("%c\n", ++(*(++(*++argv))));
    printf("argv[1] now points to \"%s\"\n", *argv);
}

int main(void)
{
    char prog[] = "PR5", arg[] = "aabbcc";     /* arrays: their characters may be changed */
    char *argv[] = {prog, arg, NULL};

    fake_main(2, argv);
    return 0;
}
```

:::details[Answer]
```
b
argv[1] now points to "bbbcc"
```

Work from the inside out:

1. `++argv` moves `argv` from `argv[0]` to `argv[1]`; `*++argv` is `argv[1]`, the pointer to `"aabbcc"`.
2. `++(*++argv)` increments **that pointer** (`argv[1]` itself), so it now points to the second character: `"abbcc"`.
3. `*(...)` is the character it points to: `'a'`.
4. The outer `++` increments **that character** in the string: `'a'` becomes `'b'`, and `'b'` is printed.

The string itself has changed: `argv[1]` now points to `"bbbcc"`. (The demonstration uses `char` arrays for the strings, because only writable characters may be incremented; the strings the system passes to `main()` are writable.)
:::

### 4.

```c runnable
#include <stdio.h>

void fun1(void) { printf("Hail "); }
void fun2(void) { printf("the "); }
void fun3(void) { printf("viruses!\n"); }

int main(void)
{
    void (*f[3])(void);

    f[0] = fun1;
    f[1] = fun2;
    f[2] = fun3;
    for (int i = 0; i <= 2; i++)
        (*f[i])();
    return 0;
}
```

:::details[Answer]
```
Hail the viruses!
```

`f` is an array of three pointers to functions; the loop calls the three functions in order, through the pointers.
:::

### 5.

```c
main()
{
    char huge *a = 0x00000120;
    char huge *b = 0x00100020;
    char huge *c = 0x00120000;

    if (a == b)
        printf("\nHello");
    if (a == c)
        printf("\nHi");
    if (b == c)
        printf("\nHello Hi");
    if (a > b && a > c && b > c)
        printf("\nBye");
}
```

:::details[Answer]
```
Hello
Hi
Hello Hi
```

All three pointers refer to physical address 00120. Because huge pointers are normalized, all three become 0012:0000, so the three equality tests succeed. They are equal, so none is greater than another, and `Bye` is not printed. (With **far** pointers the result is the opposite: only `Bye`. The near/far/huge article simulates both.)
:::

## Part C: Answer the Following

:::details[1. Can you split the statement char far *scr = (char far *)0xB8000000L; into two statements?]
Yes:
```c
char far *scr;
scr = (char far *)0xB8000000L;
```
:::

:::details[2. How would you declare an array of three function pointers, where each function receives two ints and returns a float?]
`float (*arr[3])(int, int);`
:::

:::details[3. How many bytes are occupied by near, far and huge pointers?]
Near: **2** bytes. Far and huge: **4** bytes.
:::

:::details[4. Can two different near pointers contain two different addresses but refer to the same location in memory?]
**No.** Near pointers share one segment, so different offsets mean different locations.
:::

:::details[5. Can two different far pointers contain two different addresses but refer to the same location in memory?]
**Yes.** Many segment:offset pairs name the same physical address, for example 0000:0120 and 0012:0000.
:::

:::details[6. Why is NULL defined as 0L for large memory models and just 0 for small memory models?]
In the large data models, data pointers are 32 bits (segment and offset). On those old compilers, functions were often called without prototypes, and arguments were passed at their own size. Defining `NULL` as `0L`, a 32-bit long, meant that passing `NULL` to such a function pushed 32 bits — the size of a far pointer. In small models, pointers are 16 bits, the same size as an `int`, so plain `0` was right. (With prototypes, as in modern C, the compiler converts `0` to the right pointer type automatically; that is one of many reasons to always use them.)
:::

:::details[7. Can two different huge pointers contain two different addresses but refer to the same location in memory?]
**No.** Huge pointers are always normalized, so each physical address has exactly one huge pointer value.
:::

:::details[8. True or false: in a large data model (compact, large, huge) all pointers to data are 32 bits long, whereas in a small data model (tiny, small, medium) all pointers to data are 16 bits long.]
**True.**
:::

:::details[9. How would you eliminate the warning generated on compiling: char far *scr; scr = 0xB8000000; *scr = 'A';]
Convert the integer constant to the pointer type explicitly:
```c
scr = (char far *)0xB8000000L;
```
Assigning an integer to a pointer without a cast draws a warning (in modern C it is a constraint violation).
:::

:::details[10. How would you obtain a far address from the segment and offset addresses of a memory location?]
With the macro `MK_FP(segment, offset)` from `dos.h`, or by computing `((unsigned long)segment << 16) | offset` and converting that to a far pointer.
:::

:::details[11. True or false: a near pointer uses the contents of the CS register (if it points to code) or the DS register (if it points to data) for the segment part, while the offset part is stored in the 16-bit near pointer.]
**True.**
:::

:::details[12. How would you obtain the segment and offset addresses from a far address of a memory location?]
With the macros `FP_SEG(fp)` and `FP_OFF(fp)` from `dos.h`; equivalently, the segment is the high 16 bits of the far pointer's value and the offset the low 16 bits.
:::
