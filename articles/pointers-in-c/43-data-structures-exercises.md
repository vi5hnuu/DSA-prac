title : Data Structures: Exercises with Solutions

summary : Seven exercises with full, runnable solutions: a stack as a circular linked list, a circular doubly linked list, preorder and postorder traversal without recursion, copying and comparing binary search trees with recursion, and inserting a node as a left child in a threaded binary tree.

# Data Structures: Exercises with Solutions

These exercises close the chapter on pointers and data structures. Each one combines ideas from several articles: circular lists, doubly linked lists, recursion on trees, explicit stacks, and threaded trees. Try each one yourself first — the hints point the way without giving the code — and then compare with the solution.

### 1. A stack as a circular linked list

Write a program to implement a stack as a circular linked list.

:::details[Hint]
Keep a single pointer, `last`, to one node of the ring, and treat `last->link` as the **top** of the stack. Pushing inserts a node right after `last`; popping removes the node right after `last`. A ring of one node links to itself.
:::

:::details[Solution]
```c runnable
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node
{
    int data;
    struct node *link;
};

/* the stack is reached through last: the TOP of the stack is last->link */
void push(struct node **last, int item)
{
    struct node *q = malloc(sizeof *q);
    if (q == NULL)
        exit(EXIT_FAILURE);
    q->data = item;

    if (*last == NULL) {                       /* empty: one node linked to itself */
        q->link = q;
        *last = q;
    } else {
        q->link = (*last)->link;               /* new node points to the old top */
        (*last)->link = q;                     /* and becomes the new top */
    }
}

bool pop(struct node **last, int *item)
{
    if (*last == NULL)
        return false;

    struct node *top = (*last)->link;
    *item = top->data;
    if (top == *last)                          /* it was the only node */
        *last = NULL;
    else
        (*last)->link = top->link;             /* the next node is the new top */
    free(top);
    return true;
}

void display(const struct node *last)
{
    if (last == NULL) {
        printf("stack is empty\n");
        return;
    }
    const struct node *q = last->link;         /* start at the top */
    do {
        printf("%d ", q->data);
        q = q->link;
    } while (q != last->link);
    printf("\n");
}

int main(void)
{
    struct node *last = NULL;
    int item;

    for (int v = 1; v <= 5; v++)
        push(&last, v * 11);
    printf("Stack (top first): ");
    display(last);

    pop(&last, &item);
    printf("Popped %d, ", item);
    pop(&last, &item);
    printf("popped %d\n", item);
    printf("Stack (top first): ");
    display(last);

    while (pop(&last, &item))
        ;
    display(last);
    return 0;
}
```

```
Stack (top first): 55 44 33 22 11 
Popped 55, popped 44
Stack (top first): 33 22 11 
stack is empty
```

Pushing and popping both work at `last->link`, the top, so `last` itself never has to change — except when the stack goes from empty to one node, or from one node to empty. `push()` and `pop()` take `struct node **` precisely for those two moments. Both operations take the same short time whatever the size of the stack.

`display()` walks the ring once with a `do`-`while`, starting and stopping at the top (see the circular-list article for why `do`-`while` is needed).

Is a circular list a good stack? It works, but an ordinary singly linked list with a `top` pointer is just as fast and simpler. Where a ring shines is when **both** ends are needed, as in a queue — the same ring with the same single pointer can serve as both.
:::

### 2. A doubly linked list as a circular list

Write a program to implement a doubly linked list as a circular linked list.

:::details[Hint]
Make the last node's `next` point to the first node, and the first node's `prev` point to the last. Then `head->prev` is the last node, reachable in one step. Every insertion links a new node **between two neighbours**, so write that once as a helper. A single node is its own `prev` and `next`.
:::

:::details[Solution]
```c runnable
#include <stdio.h>
#include <stdlib.h>

struct dnode
{
    struct dnode *prev;
    int data;
    struct dnode *next;
};

/* in a circular doubly linked list, head->prev is the LAST node */
static struct dnode *new_dnode(int num)
{
    struct dnode *r = malloc(sizeof *r);
    if (r == NULL)
        exit(EXIT_FAILURE);
    r->data = num;
    r->prev = r->next = r;                     /* alone, a node is its own neighbour */
    return r;
}

/* links r in between a and b, which are neighbours (a->next == b) */
static void link_between(struct dnode *r, struct dnode *a, struct dnode *b)
{
    r->prev = a;
    r->next = b;
    a->next = r;
    b->prev = r;
}

void append(struct dnode **head, int num)
{
    struct dnode *r = new_dnode(num);

    if (*head == NULL)
        *head = r;
    else
        link_between(r, (*head)->prev, *head); /* between the last node and the head */
}

void add_at_beg(struct dnode **head, int num)
{
    append(head, num);                         /* add at the end of the ring ... */
    *head = (*head)->prev;                     /* ... and call that node the head */
}

void delete_node(struct dnode **head, int num)
{
    struct dnode *q = *head;

    if (q == NULL)
        return;
    do {
        if (q->data == num) {
            if (q->next == q) {                /* the only node */
                *head = NULL;
            } else {
                q->prev->next = q->next;       /* bypass q in both directions */
                q->next->prev = q->prev;
                if (q == *head)
                    *head = q->next;
            }
            free(q);
            return;
        }
        q = q->next;
    } while (q != *head);
    printf("%d not found\n", num);
}

void display(const struct dnode *head)
{
    if (head == NULL) {
        printf("(empty)\n");
        return;
    }
    const struct dnode *q = head;
    printf("forwards: ");
    do {
        printf("%d ", q->data);
        q = q->next;
    } while (q != head);

    printf("| backwards: ");
    q = head->prev;                            /* the last node, reached in one step */
    do {
        printf("%d ", q->data);
        q = q->prev;
    } while (q != head->prev);
    printf("\n");
}

void free_list(struct dnode **head)
{
    while (*head != NULL)
        delete_node(head, (*head)->data);
}

int main(void)
{
    struct dnode *head = NULL;

    append(&head, 30);
    append(&head, 40);
    append(&head, 50);
    add_at_beg(&head, 20);
    add_at_beg(&head, 10);
    display(head);

    delete_node(&head, 10);                    /* the head */
    delete_node(&head, 50);                    /* the last node */
    delete_node(&head, 30);                    /* a middle node */
    delete_node(&head, 99);
    display(head);

    free_list(&head);
    display(head);
    return 0;
}
```

```
forwards: 10 20 30 40 50 | backwards: 50 40 30 20 10 
99 not found
forwards: 20 40 | backwards: 40 20 
(empty)
```

In a circular doubly linked list there is no `NULL` link at all, so every insertion is the same operation: link the new node `r` between two neighbours `a` and `b`. `link_between()` sets the four pointers involved, and is used for every case:

- **Append** puts the node between the last node, `(*head)->prev`, and the head. That needs no walk along the list: the last node is one step away.
- **Add at the beginning** is the same as appending — the node ends up in the same place in the ring — after which the head is moved to it: `*head = (*head)->prev;`.

Deleting a node bypasses it in both directions. The special cases are deleting the **only** node (the list becomes empty) and deleting the **head** (the head moves to the next node). `display()` walks the ring forwards and then backwards — the backwards walk starts directly at `head->prev`, which a plain doubly linked list could only reach by walking the whole list first.
:::

### 3. Preorder traversal without recursion

Write a program to traverse a binary tree in preorder without using recursion.

:::details[Hint]
Preorder visits a node **before** its subtrees. Use a stack of node pointers: pop a node, print it, then push its children. Since a stack returns the **last** item pushed first, push the right child before the left one.
:::

:::details[Solution]
```c runnable
#include <stdio.h>
#include <stdlib.h>

#define MAX 20                                 /* the deepest tree the stack can hold */

struct btreenode
{
    struct btreenode *leftchild;
    int data;
    struct btreenode *rightchild;
};

void insert(struct btreenode **sr, int num)
{
    if (*sr == NULL) {
        *sr = malloc(sizeof **sr);
        if (*sr == NULL)
            exit(EXIT_FAILURE);
        (*sr)->leftchild = (*sr)->rightchild = NULL;
        (*sr)->data = num;
    } else if (num < (*sr)->data) {
        insert(&(*sr)->leftchild, num);
    } else {
        insert(&(*sr)->rightchild, num);
    }
}

void free_tree(struct btreenode *sr)
{
    if (sr == NULL)
        return;
    free_tree(sr->leftchild);
    free_tree(sr->rightchild);
    free(sr);
}

/* preorder (Data-Left-Right) with an explicit stack */
void preorder(const struct btreenode *root)
{
    const struct btreenode *stack[MAX];
    int top = 0;

    if (root != NULL)
        stack[top++] = root;

    while (top > 0) {
        const struct btreenode *p = stack[--top];
        printf("%d ", p->data);                /* visit the node first */

        if (top + 2 > MAX) {                   /* room for both children? */
            printf("\nStack is full\n");
            return;
        }
        /* push right before left, so that left comes off the stack first */
        if (p->rightchild != NULL)
            stack[top++] = p->rightchild;
        if (p->leftchild != NULL)
            stack[top++] = p->leftchild;
    }
    printf("\n");
}

int main(void)
{
    struct btreenode *bt = NULL;
    int items[] = {41, 23, 68, 15, 30, 52, 77, 27, 35, 60};

    for (int i = 0; i < 10; i++)
        insert(&bt, items[i]);
    preorder(bt);
    free_tree(bt);
    return 0;
}
```

```
41 23 15 30 27 35 68 52 60 77 
```

This is the same order the recursive `preorder()` produced for this tree in the binary-tree article. The stack holds the subtrees still to be visited. Each time round the loop, the most recently pushed subtree root is popped and printed, then its right and left children are pushed — right first, so that the left subtree is completely visited before the right one. The loop ends when the stack is empty.

`stack[top++] = x` stores at index `top` and then increments it; `stack[--top]` decrements first and then reads. So the elements in use are always `stack[0]` to `stack[top - 1]`. Before pushing, the function checks that there is room for two more pointers, so the array can never overflow.
:::

### 4. Postorder traversal without recursion

Write a program to traverse a binary tree in postorder without using recursion.

:::details[Hint]
Postorder is the hardest of the three, because a node is visited only after **both** of its subtrees, so it is met twice on the stack: once after its left subtree, once after its right subtree. Go left pushing nodes as in the inorder version. When you can go no further, look at (but do not pop) the top node: if it has a right subtree that has not been done yet, go into it; otherwise print and pop the node. A pointer to the most recently printed node tells you whether the right subtree has been done.
:::

:::details[Solution]
```c runnable
#include <stdio.h>
#include <stdlib.h>

#define MAX 20

struct btreenode
{
    struct btreenode *leftchild;
    int data;
    struct btreenode *rightchild;
};

void insert(struct btreenode **sr, int num)
{
    if (*sr == NULL) {
        *sr = malloc(sizeof **sr);
        if (*sr == NULL)
            exit(EXIT_FAILURE);
        (*sr)->leftchild = (*sr)->rightchild = NULL;
        (*sr)->data = num;
    } else if (num < (*sr)->data) {
        insert(&(*sr)->leftchild, num);
    } else {
        insert(&(*sr)->rightchild, num);
    }
}

void free_tree(struct btreenode *sr)
{
    if (sr == NULL)
        return;
    free_tree(sr->leftchild);
    free_tree(sr->rightchild);
    free(sr);
}

/* postorder (Left-Right-Data) with an explicit stack */
void postorder(const struct btreenode *p)
{
    const struct btreenode *stack[MAX];
    const struct btreenode *last = NULL;       /* the node printed most recently */
    int top = 0;

    while (p != NULL || top > 0) {
        if (p != NULL) {                       /* go left as far as possible */
            if (top == MAX)
                return;
            stack[top++] = p;
            p = p->leftchild;
        } else {
            const struct btreenode *peek = stack[top - 1];

            /* the right subtree exists and has not been done yet: do it now */
            if (peek->rightchild != NULL && last != peek->rightchild) {
                p = peek->rightchild;
            } else {                           /* both subtrees done: visit the node */
                printf("%d ", peek->data);
                last = peek;
                top--;
            }
        }
    }
    printf("\n");
}

int main(void)
{
    struct btreenode *bt = NULL;
    int items[] = {41, 23, 68, 15, 30, 52, 77, 27, 35, 60};

    for (int i = 0; i < 10; i++)
        insert(&bt, items[i]);
    postorder(bt);
    free_tree(bt);
    return 0;
}
```

```
15 27 35 30 23 60 52 77 68 41 
```

Again the result matches the recursive version. The key is the pointer `last`, the node printed most recently. When the node on top of the stack (`peek`) has a right child, there are two possibilities:

- we have just come **up** from its left subtree, so the right subtree has not been visited: go into it;
- we have just come up from its **right** subtree — in which case the right child was the last node printed, `last == peek->rightchild` — so both subtrees are done and `peek` can be printed and popped.

A node is popped only when it is printed, so each node is pushed once and popped once.
:::

### 5 and 6. Copy and compare binary search trees using recursion

Write a program to copy a binary search tree using recursion, and a program to compare two binary search trees using recursion.

:::details[Hint]
Both follow the recursive definition of a binary tree. A copy of an empty tree is an empty tree; otherwise, copy the root's data into a new node and set its children to copies of the subtrees. Two trees are equal if both are empty, or if their roots hold the same value **and** their left subtrees are equal **and** their right subtrees are equal.
:::

:::details[Solution]
```c runnable
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct btreenode
{
    struct btreenode *leftchild;
    int data;
    struct btreenode *rightchild;
};

void insert(struct btreenode **sr, int num)
{
    if (*sr == NULL) {
        *sr = malloc(sizeof **sr);
        if (*sr == NULL)
            exit(EXIT_FAILURE);
        (*sr)->leftchild = (*sr)->rightchild = NULL;
        (*sr)->data = num;
    } else if (num < (*sr)->data) {
        insert(&(*sr)->leftchild, num);
    } else {
        insert(&(*sr)->rightchild, num);
    }
}

void free_tree(struct btreenode *sr)
{
    if (sr == NULL)
        return;
    free_tree(sr->leftchild);
    free_tree(sr->rightchild);
    free(sr);
}

/* builds a new tree with the same shape and values: copy the root, then the subtrees */
struct btreenode *copy(const struct btreenode *sr)
{
    if (sr == NULL)
        return NULL;

    struct btreenode *r = malloc(sizeof *r);
    if (r == NULL)
        exit(EXIT_FAILURE);
    r->data = sr->data;
    r->leftchild = copy(sr->leftchild);
    r->rightchild = copy(sr->rightchild);
    return r;
}

/* two trees are equal if both are empty, or both roots hold the same value
   and their left subtrees are equal and their right subtrees are equal */
bool compare(const struct btreenode *a, const struct btreenode *b)
{
    if (a == NULL && b == NULL)
        return true;
    if (a == NULL || b == NULL)
        return false;
    return a->data == b->data
        && compare(a->leftchild, b->leftchild)
        && compare(a->rightchild, b->rightchild);
}

void inorder(const struct btreenode *sr)
{
    if (sr == NULL)
        return;
    inorder(sr->leftchild);
    printf("%d ", sr->data);
    inorder(sr->rightchild);
}

int main(void)
{
    struct btreenode *bt = NULL, *other = NULL;
    int items[] = {41, 23, 68, 15, 30, 52, 77};

    for (int i = 0; i < 7; i++)
        insert(&bt, items[i]);

    struct btreenode *dup = copy(bt);
    printf("copy: ");
    inorder(dup);
    printf("\nbt and its copy: %s\n", compare(bt, dup) ? "EQUAL" : "DIFFERENT");

    /* the same values inserted in a different order give a different shape */
    int shuffled[] = {23, 15, 41, 30, 68, 52, 77};
    for (int i = 0; i < 7; i++)
        insert(&other, shuffled[i]);
    printf("bt and other:    %s\n", compare(bt, other) ? "EQUAL" : "DIFFERENT");

    free_tree(bt);
    free_tree(dup);
    free_tree(other);
    return 0;
}
```

```
copy: 15 23 30 41 52 68 77 
bt and its copy: EQUAL
bt and other:    DIFFERENT
```

`copy()` returns the new tree's root, so the recursive calls can be assigned directly to the new node's children: `r->leftchild = copy(sr->leftchild);`. Every node of the copy is newly allocated, so the copy and the original share nothing, and both can be freed independently.

`compare()` checks the cases in order: both empty — equal; exactly one empty — different; otherwise compare the data and both pairs of subtrees. `&&` stops at the first `false`, so as soon as one difference is found, no further comparisons are made.

The last line of output shows something worth remembering: `other` holds exactly the same seven values as `bt`, but they were inserted in a different order, so the tree has a different **shape**. `compare()` compares structure as well as values, so the trees are "different" even though an inorder traversal of either prints the same sorted list. (To ask "do these trees hold the same values?", compare their inorder traversals instead.)
:::

### 7. Insert a node as the left child of a node in a threaded binary tree

Write a function to insert a node `t` as the left child of `s` in a threaded binary tree.

:::details[Hint]
`t` goes between `s` and whatever was on `s`'s left: `t` takes over `s`'s old left link (child or thread), `t`'s right link is a thread to `s` (since `t` comes just before `s` in inorder), and `s`'s left link becomes a real child pointer to `t`. One more thread may need fixing: if `s` had a left subtree, its rightmost node had a right thread to `s` — but now `t` comes between them.
:::

:::details[Solution]
This builds on the threaded tree program from the threaded binary trees article (the deletion functions are left out to keep it shorter):

```c runnable
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* lthread/rthread are true when left/right is a THREAD, false for a real child */
struct thtree
{
    bool lthread;
    struct thtree *left;
    int data;
    struct thtree *right;
    bool rthread;
};

struct thtree *make_tree(void);
void insert(struct thtree *head, int num);
struct thtree *successor(const struct thtree *p);
struct thtree *predecessor(const struct thtree *p);
void inorder(const struct thtree *head);
void free_tree(struct thtree *head);
struct thtree *find(struct thtree *head, int num);
void insert_left(struct thtree *s, struct thtree *t);

/* creates the head node of an empty tree */
struct thtree *make_tree(void)
{
    struct thtree *head = malloc(sizeof *head);
    if (head == NULL)
        exit(EXIT_FAILURE);

    head->lthread = true;                      /* no tree yet: left is a thread ... */
    head->left = head;                         /* ... pointing back to the head */
    head->data = -9999;                        /* not used */
    head->right = head;                        /* the right link always points to itself */
    head->rthread = false;
    return head;
}

/* inorder successor: the node visited after p */
struct thtree *successor(const struct thtree *p)
{
    if (p->rthread)                            /* a thread leads straight there */
        return p->right;

    struct thtree *q = p->right;               /* otherwise: right once ... */
    while (!q->lthread)                        /* ... then left as far as possible */
        q = q->left;
    return q;
}

/* inorder predecessor: the node visited before p */
struct thtree *predecessor(const struct thtree *p)
{
    if (p->lthread)
        return p->left;

    struct thtree *q = p->left;                /* left once, then right as far as possible */
    while (!q->rthread)
        q = q->right;
    return q;
}

/* inserts num into the threaded binary search tree */
void insert(struct thtree *head, int num)
{
    struct thtree *z = malloc(sizeof *z);
    if (z == NULL)
        exit(EXIT_FAILURE);
    z->data = num;
    z->lthread = z->rthread = true;            /* a new node is a leaf: both are threads */

    if (head->lthread) {                       /* the tree is empty */
        z->left = z->right = head;             /* both threads lead to the head */
        head->left = z;
        head->lthread = false;                 /* the head now has a real left child */
        return;
    }

    struct thtree *p = head->left;             /* start at the root */
    while (true) {
        if (num < p->data) {
            if (!p->lthread) {                 /* a real left child: keep going */
                p = p->left;
                continue;
            }
            z->left = p->left;                 /* z's predecessor is p's old predecessor */
            z->right = p;                      /* z's successor is p */
            p->left = z;                       /* z becomes p's left child */
            p->lthread = false;
            return;
        } else {
            if (!p->rthread) {                 /* a real right child: keep going */
                p = p->right;
                continue;
            }
            z->right = p->right;               /* z's successor is p's old successor */
            z->left = p;                       /* z's predecessor is p */
            p->right = z;                      /* z becomes p's right child */
            p->rthread = false;
            return;
        }
    }
}

/* inorder traversal without recursion and without a stack */
void inorder(const struct thtree *head)
{
    if (head->lthread) {
        printf("(empty)\n");
        return;
    }

    const struct thtree *p = head->left;
    while (!p->lthread)                        /* start at the leftmost node */
        p = p->left;

    while (p != head) {                        /* the last thread leads back to the head */
        printf("%d ", p->data);
        p = successor(p);
    }
    printf("\n");
}

void free_tree(struct thtree *head)
{
    if (!head->lthread) {
        struct thtree *p = head->left;
        while (!p->lthread)
            p = p->left;
        while (p != head) {                    /* free in inorder; get the next one first */
            struct thtree *next = successor(p);
            free(p);
            p = next;
        }
    }
    free(head);
}

/* returns the node holding num, or NULL */
struct thtree *find(struct thtree *head, int num)
{
    if (head->lthread)
        return NULL;
    struct thtree *p = head->left;
    while (p->data != num) {
        if (num < p->data) {
            if (p->lthread)
                return NULL;
            p = p->left;
        } else {
            if (p->rthread)
                return NULL;
            p = p->right;
        }
    }
    return p;
}

/* inserts the new node t as the LEFT child of s; s's old left subtree
   becomes the left subtree of t */
void insert_left(struct thtree *s, struct thtree *t)
{
    t->left = s->left;                         /* t takes over s's left link ... */
    t->lthread = s->lthread;                   /* ... whether it is a child or a thread */
    t->right = s;                              /* s comes right after t in inorder */
    t->rthread = true;
    s->left = t;
    s->lthread = false;

    if (!t->lthread)                           /* t has a left subtree: its last node */
        predecessor(t)->right = t;             /* used to have a thread to s; now to t */
}

int main(void)
{
    struct thtree *head = make_tree();
    int a[] = {50, 30, 70, 20, 40};

    for (int i = 0; i < 5; i++)
        insert(head, a[i]);
    printf("Before: ");
    inorder(head);

    /* a node with no left child: 70 */
    struct thtree *t1 = malloc(sizeof *t1);
    if (t1 == NULL)
        return 1;
    t1->data = 65;
    insert_left(find(head, 70), t1);
    printf("Insert 65 as left child of 70: ");
    inorder(head);

    /* a node WITH a left subtree: 50, whose left subtree is 30, 20, 40 */
    struct thtree *t2 = malloc(sizeof *t2);
    if (t2 == NULL)
        return 1;
    t2->data = 45;
    insert_left(find(head, 50), t2);
    printf("Insert 45 as left child of 50: ");
    inorder(head);

    printf("Backwards from the last node: ");
    const struct thtree *p = head->left;
    while (!p->rthread)
        p = p->right;
    for (; p != head; p = predecessor(p))
        printf("%d ", p->data);
    printf("\n");

    free_tree(head);
    return 0;
}
```

```
Before: 20 30 40 50 70 
Insert 65 as left child of 70: 20 30 40 50 65 70 
Insert 45 as left child of 50: 20 30 40 45 50 65 70 
Backwards from the last node: 70 65 50 45 40 30 20 
```

`insert_left()` does four things:

1. `t` inherits `s`'s left link and its flag: if `s` had a left **subtree**, it becomes `t`'s left subtree; if `s` had a left **thread** to its predecessor, `t` gets that thread, because `t` now comes right after that predecessor.
2. `t`'s right link becomes a thread to `s`: in inorder, `t` comes immediately before `s`.
3. `s`'s left link becomes a real child pointer to `t`.
4. If `t` now has a left subtree, the **last** node of that subtree (its rightmost node, `predecessor(t)`) still has a right thread pointing to `s`. Its successor is now `t`, so the thread is redirected: `predecessor(t)->right = t;`.

The program tests both situations: 70 had no left child (only step 1's thread is inherited), while 50 had the whole subtree 30, 20, 40 (step 4 redirects 40's thread from 50 to 45). The inorder output proves the forward threads are right, and the backwards walk with `predecessor()` proves the left threads are right too.

Note that inserting `t` this way respects the tree's shape, not necessarily the binary-search-tree ordering: 45 fits between 40 and 50, so the tree is still a valid BST here, but in general the caller must choose `t`'s value with care.
:::

## Key Takeaways

- A circular list reached through one pointer to its last node gives instant access to both ends; it can serve as a stack or a queue.
- In a circular doubly linked list there are no `NULL` links: every insertion links a node between two neighbours, and the last node is `head->prev`.
- Any recursive traversal can be rewritten with an explicit stack. Preorder pushes right before left; postorder needs to remember the last node printed.
- Recursive copy and comparison follow the definition of a binary tree: handle the empty tree, then the root, then both subtrees.
- Every change to a threaded tree must keep every thread correct, including the thread of the node whose successor changes.
