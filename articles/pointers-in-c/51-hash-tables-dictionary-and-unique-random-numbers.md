title : Hash Tables: A Dictionary and Unique Random Numbers

summary : Speed up searching by splitting data into many short linked lists, reached through an array of pointers. Build a spelling dictionary with one sorted list per letter, then generate unique random numbers with a bucketed hash table, and learn what makes a good hash function.

# Hash Tables: A Dictionary and Unique Random Numbers

Two classic problems have the same shape. A **dictionary** program must store many words and answer "is this word in the dictionary?" quickly. A **random number generator** that must never repeat a number must remember every number it has produced, and answer "have I produced this one before?" quickly. Both need a collection that grows while the program runs and supports fast searching.

The solution used for both is a **hash table**: an array of pointers, each the head of its own short linked list. It combines the strengths of the two structures this course has studied most — the array (instant access by position) and the linked list (easy growth and insertion).

## Why Not an Array, or One Long List?

The words could be stored in an array. But an array has serious limitations here:

- its size must be fixed when the program is written;
- it cannot grow or shrink while the program runs;
- inserting a new word in the middle (to keep alphabetical order) means moving every later word;
- deleting a word also means moving words;
- a large dictionary needs a very large block of **contiguous** memory, which may not be available.

A linked list solves all of these. But a single list of all the words is slow to search: to look up *Zimbabwe*, or to find where to insert it, we must start at the first node and walk past every word from *A* onwards.

## A Dictionary with One List per Letter

The fix is to keep **26** linked lists, one for each initial letter, and store their heads in an array of 26 pointers. A word starting with *Z* is stored in, and searched for in, the *Z* list only. Each list is kept in alphabetical order.

![The array a holds 26 pointers. a[1] leads to Belgium, Bhutan and Brazil; a[8] to Iceland, India, Iran and Italy; a[25] to Zambia; a[0] is NULL](images/array-of-lists-dictionary.svg)

The program below builds such a dictionary of countries, then checks some names:

```c runnable
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct clist
{
    char name[20];
    struct clist *link;
};

struct clist *a[26];                           /* one sorted list per initial letter */

/* which list a word belongs to: 0 for A, 1 for B, ... or -1 if not a letter */
int bucket(const char *word)
{
    unsigned char first = (unsigned char)word[0];
    return isalpha(first) ? toupper(first) - 'A' : -1;
}

/* inserts word into its list, keeping the list in alphabetical order */
void addtolist(const char *word)
{
    int index = bucket(word);
    if (index < 0)
        return;

    struct clist **q = &a[index];              /* walk the links to the right gap */
    while (*q != NULL && strcmp((*q)->name, word) < 0)
        q = &(*q)->link;
    if (*q != NULL && strcmp((*q)->name, word) == 0)
        return;                                /* already in the dictionary */

    struct clist *r = malloc(sizeof *r);
    if (r == NULL)
        exit(EXIT_FAILURE);
    snprintf(r->name, sizeof r->name, "%s", word);
    r->link = *q;
    *q = r;
}

/* returns 1 if word is in the dictionary: only its own list is searched */
int search_list(const char *word)
{
    int index = bucket(word);
    if (index < 0)
        return 0;

    for (const struct clist *p = a[index]; p != NULL; p = p->link) {
        int cmp = strcmp(p->name, word);
        if (cmp == 0)
            return 1;
        if (cmp > 0)                           /* the list is sorted: we have gone past it */
            return 0;
    }
    return 0;
}

int main(void)
{
    /* stands in for the file CNAMES.TXT */
    const char *countries[] = {"India", "Brazil", "Japan", "Bhutan", "Iran", "Kenya",
                               "Belgium", "Italy", "Chile", "Iceland", "Zambia"};
    const char *queries[] = {"Iceland", "Ireland", "Zambia", "Belize"};

    for (size_t i = 0; i < sizeof countries / sizeof countries[0]; i++)
        addtolist(countries[i]);

    printf("List B: ");
    for (const struct clist *p = a['B' - 'A']; p != NULL; p = p->link)
        printf("%s ", p->name);
    printf("\nList I: ");
    for (const struct clist *p = a['I' - 'A']; p != NULL; p = p->link)
        printf("%s ", p->name);
    printf("\n\n");

    for (size_t i = 0; i < sizeof queries / sizeof queries[0]; i++)
        printf("%-8s %s\n", queries[i], search_list(queries[i]) ? "is present in the list" : "misspelled / not present");

    addtolist("Ireland");                      /* the user chose to add it */
    printf("after adding: Ireland %s\n", search_list("Ireland") ? "is present" : "not present");

    for (int i = 0; i < 26; i++)               /* free every list */
        while (a[i] != NULL) {
            struct clist *next = a[i]->link;
            free(a[i]);
            a[i] = next;
        }
    return 0;
}
```

```
List B: Belgium Bhutan Brazil 
List I: Iceland India Iran Italy 

Iceland  is present in the list
Ireland  misspelled / not present
Zambia   is present in the list
Belize   misspelled / not present
after adding: Ireland is present
```

### How it works

**`struct clist *a[26];`** is an array of 26 pointers to nodes. Declared outside every function, it starts with all elements `NULL` — 26 empty lists.

**`bucket()`** decides which list a word belongs to. `toupper(first) - 'A'` turns `'A'`…`'Z'` into 0…25: letters have consecutive codes, so subtracting the code of `'A'` gives the position in the alphabet. Two details matter:

- The character is first converted to `unsigned char`. The functions in `<ctype.h>` require a value that fits in an `unsigned char` (or `EOF`); passing a negative `char`, such as a byte from a non-ASCII name, is undefined behaviour.
- A word that does not start with a letter returns −1 and is rejected. Older versions of this program compute `toupper(country[0]) - 65` without any check, so a name like `"1st Republic"` gives a negative index and writes outside the array.

**`addtolist()`** keeps each list in alphabetical order with the pointer-to-a-link technique from the linked-list articles: `q` walks the **links** of the chosen list until it reaches the first word that is not smaller than the new one, and the new node is linked in there. Because `q` starts at `&a[index]` itself, inserting at the front of a list needs no special case. A word that is already present is not added twice.

(Older versions write this insertion with the test `strcmp(temp->link->name, str) > 0 || temp->link == NULL`, which reads `temp->link->name` **before** checking whether `temp->link` is `NULL` — the same trap seen in the sorted-list article, which crashes as soon as a word belongs at the end of a list.)

**`search_list()`** looks only in the word's own list, and because the list is sorted, it can stop as soon as it passes the place where the word would be (`cmp > 0`), without walking to the end.

The original program read the countries from a file with `fgets()`, removing the newline at the end of each line, and asked the user, for every misspelled word, whether to add it to the dictionary and to the file (`fseek(fp, 0L, SEEK_END)` and `fputs()`). The data structure is the same; here the names come from an array so that the program can run anywhere.

## Unique Random Numbers with Hashing

Suppose an application needs 1000 random numbers in the range 1 to 32,767, all **different**: once 511 has been produced, it must never be produced again. A random number generator does not promise unique values, so we must remember every number produced and reject repeats.

How should they be remembered?

- A **boolean array** of 32,767 elements, one per possible number, would make checking instant — but it is wasteful to use 32,767 elements to remember just 1000 numbers.
- A **single linked list** of the numbers produced uses little memory, but checking a new number means searching the whole list, which gets slower and slower as the list grows.

**Hashing** combines the two. The range of possible numbers is divided into **buckets**: numbers 0 to 999 go in bucket 0, 1000 to 1999 in bucket 1, and so on, which needs 33 buckets for numbers up to 32,767. Each bucket is a linked list, and an array of 33 pointers holds the lists' heads. To check or store a number, compute its bucket — `num / 1000` — and search only that short list.

```c runnable
#include <stdio.h>
#include <stdlib.h>

#define BUCKETS 33                             /* numbers 0..32767, 1000 per bucket */

struct node
{
    int data;
    struct node *link;
};

struct node *bucks[BUCKETS];                   /* globals start as NULL: empty buckets */

/* a small random-number generator, so the output is the same on every system
   (rand() gives different sequences in different C libraries) */
static unsigned long seed = 2024;

int random_1_to_32767(void)
{
    seed = (seed * 1103515245UL + 12345UL) % 2147483648UL;
    return (int)(seed / 65536 % 32767) + 1;
}

/* adds data to its bucket's sorted list; returns 0 if it was already there */
int add_unique(int data)
{
    struct node **q = &bucks[data / 1000];     /* the hash function: which bucket */

    while (*q != NULL && (*q)->data < data)
        q = &(*q)->link;
    if (*q != NULL && (*q)->data == data)
        return 0;                              /* a repeat: reject it */

    struct node *r = malloc(sizeof *r);
    if (r == NULL)
        exit(EXIT_FAILURE);
    r->data = data;
    r->link = *q;
    *q = r;
    return 1;
}

int main(void)
{
    int wanted = 1000, made = 0, rejected = 0;

    while (made < wanted) {
        int num = random_1_to_32767();
        if (add_unique(num))
            made++;
        else
            rejected++;
    }
    printf("%d unique numbers generated, %d repeats rejected\n", made, rejected);

    int longest = 0, total = 0;
    for (int b = 0; b < BUCKETS; b++) {
        int len = 0;
        for (const struct node *p = bucks[b]; p != NULL; p = p->link)
            len++;
        total += len;
        if (len > longest)
            longest = len;
    }
    printf("numbers stored: %d, longest bucket list: %d\n", total, longest);

    printf("bucket 0 starts:");
    int shown = 0;
    for (const struct node *p = bucks[0]; p != NULL && shown < 6; p = p->link, shown++)
        printf(" %d", p->data);
    printf(" ...\n");

    for (int b = 0; b < BUCKETS; b++)
        while (bucks[b] != NULL) {
            struct node *next = bucks[b]->link;
            free(bucks[b]);
            bucks[b] = next;
        }
    return 0;
}
```

```
1000 unique numbers generated, 18 repeats rejected
numbers stored: 1000, longest bucket list: 38
bucket 0 starts: 17 48 62 91 98 118 ...
```

The function that turns a value into a bucket number — here `data / 1000` — is called the **hash function**. With 1000 numbers spread over 33 buckets, each list holds about 30 numbers, so checking a new number takes about 30 comparisons instead of up to 1000.

The program uses its own small random-number generator rather than `rand()`, only so that its output is the same on every computer: different C libraries produce different `rand()` sequences. The generator is a **linear congruential generator**, the classic method behind many versions of `rand()`.

## Choosing a Hash Function

Both programs use simple hash functions: the first letter of a word, and a number divided by 1000. They work, but they show the main weakness of a poor hash function — **uneven buckets**. Far more country names start with *B* or *S* than with *X*, so the *B* list is long while the *X* list is empty, and searching the long lists is slow.

A good hash function spreads the values evenly over the buckets, so that every list stays short. For strings, a common choice combines **all** the characters, for example:

```c
unsigned long hash = 5381;
for (const unsigned char *p = (const unsigned char *)word; *p != '\0'; p++)
    hash = hash * 33 + *p;
index = hash % NBUCKETS;
```

With a good hash function and enough buckets, a lookup takes a small, nearly constant number of steps however many items are stored — which is why hash tables are the standard way to implement dictionaries, symbol tables in compilers, caches and database indexes. Their one drawback: the items are no longer kept in sorted order overall, only within each bucket.

## Key Takeaways

- A hash table is an array of pointers to linked lists ("buckets"). A hash function maps each item to a bucket, and only that bucket is searched.
- It keeps the flexibility of linked lists while making searches much shorter than in one long list.
- A dictionary with one sorted list per initial letter, and a set of numbers bucketed by `num / 1000`, are both simple hash tables.
- Check that the computed index is within the array before using it; convert `char`s to `unsigned char` before passing them to `<ctype.h>` functions.
- A good hash function spreads items evenly so that every list stays short.

## Practice Questions

:::details[In the number hash table, which bucket holds 20457, and how many buckets are needed for numbers up to 32767?]
20457 / 1000 = **20**. The largest number, 32767, goes in bucket 32, so **33** buckets (0 to 32) are needed.
:::

:::details[Why does search_list() return 0 as soon as strcmp(p->name, word) is positive?]
The list is in alphabetical order. Once we reach a name that comes **after** the word, every remaining name also comes after it, so the word cannot be further along.
:::

:::details[What would go wrong in the dictionary if bucket() simply returned toupper(word[0]) - 'A' and a word started with a digit?]
For `'1'`, the result is `'1' - 'A'`, a negative number. `a[index]` would then refer to memory before the array — undefined behaviour, usually corrupting other data or crashing.
:::

:::details[Suggest a better hash function for the 1000 random numbers than num / 1000.]
`num % 33` (or modulo any number of buckets) spreads consecutive numbers across different buckets. For random numbers both work, but `%` keeps working well even if the numbers cluster in one part of the range. Using more buckets, such as 101, makes each list shorter still.
:::
