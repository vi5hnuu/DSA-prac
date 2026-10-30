title : Threaded Binary Trees

summary : Traverse a binary tree in inorder with no recursion and no stack, by turning the NULL links of the leaves into threads to the inorder successor and predecessor. Build a threaded binary search tree with a head node, and insert and delete nodes while keeping every thread correct.

# Threaded Binary Trees

The traversal functions in the binary tree articles are recursive. Each recursive call remembers, on the program's call stack, where to come back to — in effect, a stack of pointers to the nodes whose right subtrees are still to be visited. A non-recursive version must keep exactly such a stack itself (one of the worked problems later in this chapter does that). Either way, the traversal needs extra memory that grows with the depth of the tree, and the time to push and pop it.

It is possible to traverse a binary tree **without** any such stack. The trick lies in the `NULL` pointers that every binary tree is full of: a tree of *n* nodes has *n* + 1 empty child links. Those links can be put to work.

## The Idea of Threads

Consider this tree, and an inorder traversal of it (20 30 40 50 60 70 80):

![A threaded binary tree: 50 at the top with children 30 and 70 and grandchildren 20, 40, 60 and 80. Dashed red right threads lead 20 to 30, 40 to 50, 60 to 70 and 80 to the head; dashed purple left threads lead 40 to 30, 60 to 50, 80 to 70 and 20 to the head](images/threaded-binary-tree.svg)

We follow left pointers until we reach 20, the leftmost node, without pushing anything. We print 20. Normally, we would now need the stack to get back up to 30. But suppose that, when the tree was built, the empty right pointer of 20 was set to point **back up to 30**. Then we could simply follow it, print 30, and carry on. Likewise, if the empty right pointer of 40 pointed up to 50, then after printing 40 we could jump straight to 50 and print it.

A pointer of this kind, which replaces an empty right link and points to the node's **inorder successor** (the node visited next in inorder), is called a **right thread**. In the same way, an empty left link can be made to point to the node's **inorder predecessor**: a **left thread**. A binary tree whose empty links have been replaced by threads is a **threaded binary tree**.

## Telling Threads from Children

There is one problem with threads: a program must know whether a pointer is a **normal** pointer to a child, or a **thread** back to an ancestor. Both are just addresses. The solution is to store two extra flags in each node:

```c
struct thtree
{
    bool lthread;            /* true: left is a thread, false: left is a child */
    struct thtree *left;
    int data;
    struct thtree *right;
    bool rthread;            /* true: right is a thread, false: right is a child */
};
```

`bool`, `true` and `false` come from `<stdbool.h>`. (Older code declares its own `enum boolean { false, true };`. Since C99 that is unnecessary, and since C23 `bool`, `true` and `false` are keywords, so a homemade enum with those names no longer even compiles.) The names `lthread` and `rthread` say what `true` means, which is easier to read than flags called just `left` and `right`.

### The head node

Two links in every threaded tree have nothing to point to: the left thread of the very first node in inorder (20), and the right thread of the very last (80). Rather than leaving them `NULL`, we add a dummy **head node** above the tree:

- the whole tree hangs from the head as its **left** subtree: `head->left` is the root;
- the head's own `right` link points to the head itself;
- the two "nowhere" threads point to the head.

Now **every** link points somewhere. A traversal knows it has finished when it arrives back at the head. For an empty tree, the head's `left` is a thread to itself.

## The Program

This program builds a threaded binary search tree, deletes several nodes, and prints the tree in inorder after each change — all without recursion and without a stack.

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
void delete_node(struct thtree *head, int num);
struct thtree *successor(const struct thtree *p);
struct thtree *predecessor(const struct thtree *p);
void inorder(const struct thtree *head);
void free_tree(struct thtree *head);

int main(void)
{
    struct thtree *head = make_tree();         /* empty tree */
    int a[] = {50, 30, 70, 20, 40, 60, 80, 35, 65};

    for (int i = 0; i < 9; i++)
        insert(head, a[i]);

    printf("Threaded binary tree before deletion: ");
    inorder(head);

    int del[] = {40, 70, 20, 50, 99};          /* one child, two children, leaf, root, absent */
    for (int i = 0; i < 5; i++) {
        printf("Delete %d: ", del[i]);
        delete_node(head, del[i]);
        inorder(head);
    }

    free_tree(head);
    return 0;
}

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

/* removes x, which has at most one child, from under its father par */
static void remove_simple(struct thtree *par, struct thtree *x)
{
    bool is_left = !par->lthread && par->left == x;   /* x is par's LEFT child */

    if (x->lthread && x->rthread) {            /* a leaf: the father's link becomes a thread */
        if (is_left) {
            par->left = x->left;               /* x's predecessor */
            par->lthread = true;
        } else {
            par->right = x->right;             /* x's successor */
            par->rthread = true;
        }
    } else {                                   /* one child: the father adopts it */
        struct thtree *child;

        if (!x->lthread) {                     /* only a left child */
            child = x->left;
            predecessor(x)->right = x->right;  /* its thread pointed to x: now to x's successor */
        } else {                               /* only a right child */
            child = x->right;
            successor(x)->left = x->left;      /* its thread pointed to x: now to x's predecessor */
        }

        if (is_left)
            par->left = child;
        else
            par->right = child;
    }
    free(x);
}

/* deletes the node holding num */
void delete_node(struct thtree *head, int num)
{
    struct thtree *par = head, *x = head->left;

    if (head->lthread) {                       /* empty tree */
        printf("(tree is empty) ");
        return;
    }

    /* search for num, remembering the father */
    while (x->data != num) {
        par = x;
        if (num < x->data) {
            if (x->lthread) {                  /* a thread: no further left child */
                printf("(%d not found) ", num);
                return;
            }
            x = x->left;
        } else {
            if (x->rthread) {
                printf("(%d not found) ", num);
                return;
            }
            x = x->right;
        }
    }

    if (!x->lthread && !x->rthread) {          /* two children */
        struct thtree *spar = x, *s = x->right;
        while (!s->lthread) {                  /* inorder successor and its father */
            spar = s;
            s = s->left;
        }
        x->data = s->data;                     /* copy, then remove the successor */
        remove_simple(spar, s);
    } else {
        remove_simple(par, x);
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
```

```
Threaded binary tree before deletion: 20 30 35 40 50 60 65 70 80 
Delete 40: 20 30 35 50 60 65 70 80 
Delete 70: 20 30 35 50 60 65 80 
Delete 20: 30 35 50 60 65 80 
Delete 50: 30 35 60 65 80 
Delete 99: (99 not found) 30 35 60 65 80 
```

## How It Works

### Successor and predecessor

Everything rests on two small functions:

```c
struct thtree *successor(const struct thtree *p)
{
    if (p->rthread)                /* a thread leads straight there */
        return p->right;

    struct thtree *q = p->right;   /* otherwise: right once ... */
    while (!q->lthread)            /* ... then left as far as possible */
        q = q->left;
    return q;
}
```

If `p`'s right link is a thread, it **is** the successor. Otherwise `p` has a right subtree, and its successor is the leftmost node of that subtree — the same rule used for deletion in a plain binary search tree. The predecessor is the mirror image: follow a left thread, or go left once and then right as far as possible.

### inorder(): no recursion, no stack

```c
const struct thtree *p = head->left;
while (!p->lthread)            /* start at the leftmost node */
    p = p->left;

while (p != head) {            /* the last thread leads back to the head */
    printf("%d ", p->data);
    p = successor(p);
}
```

Starting from the root, follow left children until a left **thread** is found: that is the first node in inorder. Then repeatedly print the node and move to its successor. The traversal stops when it arrives back at the head, which is where the last node's right thread leads.

### insert(): keeping the threads right

A new node always becomes a **leaf**, so both its links start as threads. The search for its place works like in an ordinary BST, except that "an empty child" now means "a thread": `if (!p->lthread)` means "p has a real left child, keep going".

When the new node `z` becomes the **left** child of `p`:

```c
z->left = p->left;      /* z's predecessor is p's old predecessor */
z->right = p;           /* z's successor is p */
p->left = z;            /* z becomes p's left child */
p->lthread = false;     /* p's left is now a real child */
```

Why? `p->left` was a thread to `p`'s predecessor. `z` is inserted just before `p` in inorder, so `z` inherits that predecessor, and `z`'s own successor is `p`. Inserting as a right child is the mirror image. For the first node of an empty tree, both threads lead to the head.

Values equal to an existing node go to the right, as in the plain BST. (Older versions of this function test `p->data > num` and `p->data < num` but have no case for **equal**, so inserting a duplicate value loops forever.)

### delete_node(): the same four cases, plus threads

Deletion follows the plan of the previous article — not found, leaf, one child, two children — with some readjusting of threads:

- **Two children**: copy the inorder successor's data into the node, and remove the successor instead. The successor is found by going right once and then left until a left thread appears, keeping track of its father `spar`. The successor has no left child, so removing it is one of the simpler cases.
- **A leaf**: the father's link that pointed to it becomes a thread. If it was a left child, the father's left thread must lead to the leaf's predecessor — which is exactly where the leaf's own left thread pointed — so `par->left = x->left;` and `par->lthread = true;`. Similarly for a right child.
- **One child**: the father adopts the child. But one thread in the child's subtree pointed **at the node being deleted**, and it must be redirected. If `x` has only a **left** subtree, `x` was the successor of the **rightmost** node of that subtree — `x`'s predecessor — so that node's right thread is pointed at `x`'s successor: `predecessor(x)->right = x->right;`. If `x` has only a right subtree, the leftmost node of that subtree had a left thread to `x`, which is pointed at `x`'s predecessor instead.

The test `bool is_left = !par->lthread && par->left == x;` decides whether `x` hangs on its father's left. Comparing `par->left == x` alone is not enough, because a left **thread** can also point at `x`. The head counts as a father too: the root is its left child, so deleting the root needs no special case.

:::callout{kind=warning}
In the one-child case, older versions of this program write `x->rightchild->leftchild = x->leftchild;`. That treats `x`'s right child as the node with the thread back to `x` — true only if that child has **no left subtree**. If it does, the statement overwrites a real left child with a thread, and the whole left subtree of that child is lost from the tree. The node that holds the thread to `x` is the **leftmost** node of `x`'s right subtree — `successor(x)` — which is what this program updates.
:::

### free_tree()

The tree is freed by walking it in inorder with `successor()`. The next node is found **before** the current one is freed: `successor()` reads `p`'s links, which must not happen after `free(p)`. This works because the successor is always either in `p`'s right subtree or an ancestor of `p` — never a node that has already been freed.

## Is It Worth It?

Threads make inorder traversal (and finding a node's successor or predecessor) possible without recursion or extra memory. The price is two flags per node, and noticeably more complicated insertion and deletion. In practice, threaded trees are used where memory is very tight or where "move to the next item" must be fast, for example in some database index structures. Their real value for a learner is as an exercise in pointer bookkeeping: every change must keep every link and every flag consistent.

## Key Takeaways

- A threaded binary tree replaces empty left and right links with **threads** to the inorder predecessor and successor.
- Each node needs two flags to tell a thread from a real child pointer.
- A head node gives the first and last threads somewhere to point, and marks the end of a traversal.
- The successor of `p` is `p->right` if that is a thread; otherwise the leftmost node of `p`'s right subtree.
- Inorder traversal becomes a simple loop: start at the leftmost node, then repeatedly move to the successor until the head is reached.
- Insertion and deletion must keep every thread correct; in particular, deleting a node with one child must redirect the thread that pointed to it.

## Practice Questions

:::details[In the tree shown above, where do the right threads of 20, 40, 60 and 80 point?]
20 → 30, 40 → 50, 60 → 70, and 80 → the head node (80 is the last node in inorder).
:::

:::details[A threaded tree has 9 nodes. How many of its 18 child links are threads?]
A binary tree of *n* nodes has *n* − 1 real child links (one leading to each node except the root), so 18 − 8 = **10** links are threads — *n* + 1 in general.
:::

:::details[Why can't the threaded inorder traversal stop when it meets a NULL pointer, as a linked-list traversal does?]
There are no `NULL` links in a threaded tree with a head node: every empty link has become a thread, and the last node's right thread points to the head. The traversal stops when it returns to the head.
:::

:::details[Write a loop that prints a threaded tree in DESCENDING order.]
Start at the rightmost node and follow predecessors back to the head:
```c
const struct thtree *p = head->left;
while (!p->rthread)
    p = p->right;
while (p != head) {
    printf("%d ", p->data);
    p = predecessor(p);
}
```
:::
