title : Design Browser History

summary : Build a browser history that supports visit, back and forward. Compare two designs, a doubly linked list and two stacks, and see how each handles moving through pages and clearing forward history.

# Design Browser History

::problem{slug=design-browser-history}

## Problem Statement

Model the history of a single browser tab. The tab starts on a `homepage`, and you can open new pages or move backwards and forwards through the pages you have visited.

Implement the class `BrowserHistory`:

- `BrowserHistory(string homepage)` — start the tab on `homepage`.
- `void visit(string url)` — open `url` from the current page. Any pages that were "forward" of the current page are **discarded**.
- `string back(int steps)` — go back up to `steps` pages. If fewer than `steps` pages exist behind you, go back as far as possible. Return the page you end on.
- `string forward(int steps)` — go forward up to `steps` pages, stopping early if you run out. Return the page you end on.

### Example

| Call | Returns | History (current page in **bold**) |
|---|---|---|
| `BrowserHistory("home.page")` | – | **home.page** |
| `visit("news.site")` | – | home.page, **news.site** |
| `visit("blog.site")` | – | home.page, news.site, **blog.site** |
| `visit("shop.site")` | – | home.page, news.site, blog.site, **shop.site** |
| `back(1)` | `"blog.site"` | home.page, news.site, **blog.site**, shop.site |
| `back(1)` | `"news.site"` | home.page, **news.site**, blog.site, shop.site |
| `forward(1)` | `"blog.site"` | home.page, news.site, **blog.site**, shop.site |
| `visit("mail.site")` | – | home.page, news.site, blog.site, **mail.site** (shop.site discarded) |
| `forward(2)` | `"mail.site"` | nothing ahead, stay |
| `back(2)` | `"news.site"` | home.page, **news.site**, blog.site, mail.site |
| `back(7)` | `"home.page"` | only one page behind, stop at **home.page** |

### Constraints

- `1 <= homepage.length, url.length <= 20`
- `1 <= steps <= 100`
- Page names contain only `'.'` and lowercase English letters.
- At most `5000` calls are made in total to `visit`, `back` and `forward`.

:::callout{kind=tip}
The history is a line of pages with a "current" marker that moves left (`back`) and right (`forward`). `visit` cuts off everything to the right of the marker and appends the new page. Any structure that supports "move the marker" and "cut off the right side" works.
:::

## Approach 1: Doubly Linked List

Each page is a node with `prev` and `next` pointers, and `head` points to the **current** page (not the first one).

- **`visit(url)`**: free every node after the current one (the forward history), then create the new node, link it after the current node, and move `head` to it.
- **`back(steps)`**: follow `prev` up to `steps` times, stopping when there is no previous page.
- **`forward(steps)`**: follow `next` the same way.

:::code-tabs
```cpp
class BrowserHistory {
private:
    class BrowserHistoryNode {
    public:
        string url;
        BrowserHistoryNode *next = nullptr, *prev = nullptr;
        BrowserHistoryNode(string url) : url(url) {
            this->next = this->prev = nullptr;
        };
        BrowserHistoryNode(string url, BrowserHistoryNode *next, BrowserHistoryNode *prev) {
            this->url = url;
            this->next = next;
            this->prev = prev;
        };
    };
    BrowserHistoryNode *head = nullptr;
public:
    BrowserHistory(string homepage) {
        this->head = new BrowserHistoryNode(homepage);
    }
    ~BrowserHistory() {
        // free the pages behind the current one, then the current one and everything after it
        while (head && head->prev) head = head->prev;
        freeMemory(head);
    }

    void visit(string url) {
        freeMemory(head->next);
        head = head->next = new BrowserHistoryNode(url, nullptr, head);
    }

    string back(int steps) {
        while (head && head->prev && steps--) {
            head = head->prev;
        }
        return head->url;
    }

    string forward(int steps) {
        while (head && head->next && steps--) {
            head = head->next;
        }
        return head->url;
    }

    void freeMemory(BrowserHistoryNode *from) {
        while (from) {
            BrowserHistoryNode* temp = from;
            from = from->next;
            delete temp;
        }
    }
};
```
```java
class BrowserHistory {
    private static class BrowserHistoryNode {
        String url;
        BrowserHistoryNode next, prev;

        BrowserHistoryNode(String url, BrowserHistoryNode next, BrowserHistoryNode prev) {
            this.url = url;
            this.next = next;
            this.prev = prev;
        }
    }

    private BrowserHistoryNode head;

    public BrowserHistory(String homepage) {
        this.head = new BrowserHistoryNode(homepage, null, null);
    }

    public void visit(String url) {
        // the old forward pages become unreachable and are garbage-collected
        head = head.next = new BrowserHistoryNode(url, null, head);
    }

    public String back(int steps) {
        while (head != null && head.prev != null && steps-- > 0) {
            head = head.prev;
        }
        return head.url;
    }

    public String forward(int steps) {
        while (head != null && head.next != null && steps-- > 0) {
            head = head.next;
        }
        return head.url;
    }
}
```
```python
class BrowserHistory:
    class BrowserHistoryNode:
        def __init__(self, url, next=None, prev=None):
            self.url = url
            self.next = next
            self.prev = prev

    def __init__(self, homepage: str):
        self.head = self.BrowserHistoryNode(homepage)

    def visit(self, url: str) -> None:
        # the old forward pages become unreachable and are garbage-collected
        self.head.next = self.BrowserHistoryNode(url, None, self.head)
        self.head = self.head.next

    def back(self, steps: int) -> str:
        while self.head and self.head.prev and steps > 0:
            steps -= 1
            self.head = self.head.prev
        return self.head.url

    def forward(self, steps: int) -> str:
        while self.head and self.head.next and steps > 0:
            steps -= 1
            self.head = self.head.next
        return self.head.url
```
:::

**Complexity**

- **`visit`:** `O(f)` in C++ to free the `f` forward pages (each page is freed at most once, so this is `O(1)` amortized); `O(1)` in Java and Python.
- **`back` / `forward`:** `O(min(steps, pages available))`.
- **Space:** `O(number of pages kept)`.

## Approach 2: Two Stacks

Keep the pages up to and including the current one on a stack `curr` (current page on top), and the forward pages on a stack `rest` (the next page on top).

- **`visit(url)`**: clear `rest`, push `url` onto `curr`.
- **`back(steps)`**: move pages from `curr` to `rest`, but never the last one (the homepage must stay).
- **`forward(steps)`**: move pages from `rest` back to `curr` while any remain.

The current page is always `curr.top()`.

:::code-tabs
```cpp
class BrowserHistory {
private:
    stack<string> curr, rest;
public:
    BrowserHistory(string homepage) {
        curr.push(homepage);
    }

    void visit(string url) {
        clear(rest);
        curr.push(url);
    }

    string back(int steps) {
        while (curr.size() > 1 && steps--) {
            rest.push(curr.top());
            curr.pop();
        }
        return curr.top();
    }

    string forward(int steps) {
        while (!rest.empty() && steps--) {
            curr.push(rest.top());
            rest.pop();
        }
        return curr.top();
    }

    void clear(stack<string> &x) {
        while (!x.empty()) {
            x.pop();
        }
    }
};
```
```java
class BrowserHistory {
    private Deque<String> curr = new ArrayDeque<>(), rest = new ArrayDeque<>();

    public BrowserHistory(String homepage) {
        curr.push(homepage);
    }

    public void visit(String url) {
        rest.clear();
        curr.push(url);
    }

    public String back(int steps) {
        while (curr.size() > 1 && steps-- > 0) {
            rest.push(curr.pop());
        }
        return curr.peek();
    }

    public String forward(int steps) {
        while (!rest.isEmpty() && steps-- > 0) {
            curr.push(rest.pop());
        }
        return curr.peek();
    }
}
```
```python
class BrowserHistory:
    def __init__(self, homepage: str):
        self.curr = [homepage]
        self.rest = []

    def visit(self, url: str) -> None:
        self.rest.clear()
        self.curr.append(url)

    def back(self, steps: int) -> str:
        while len(self.curr) > 1 and steps > 0:
            steps -= 1
            self.rest.append(self.curr.pop())
        return self.curr[-1]

    def forward(self, steps: int) -> str:
        while self.rest and steps > 0:
            steps -= 1
            self.curr.append(self.rest.pop())
        return self.curr[-1]
```
:::

**Complexity**

- **`visit`:** `O(f)` to clear `f` forward pages (`O(1)` amortized).
- **`back` / `forward`:** `O(min(steps, pages available))`.
- **Space:** `O(number of pages kept)`.

:::callout{kind=note}
In C++, clearing a stack by popping every element and replacing it with a fresh one (`x = stack<string>();`) both work. The difference only matters for very large stacks or elements with expensive destructors; for strings here it is negligible.
:::

## Try It Yourself

```python runnable
class BrowserHistory:
    def __init__(self, homepage: str):
        self.curr = [homepage]
        self.rest = []

    def visit(self, url: str) -> None:
        self.rest.clear()
        self.curr.append(url)

    def back(self, steps: int) -> str:
        while len(self.curr) > 1 and steps > 0:
            steps -= 1
            self.rest.append(self.curr.pop())
        return self.curr[-1]

    def forward(self, steps: int) -> str:
        while self.rest and steps > 0:
            steps -= 1
            self.curr.append(self.rest.pop())
        return self.curr[-1]


b = BrowserHistory("home.page")
b.visit("news.site")
b.visit("blog.site")
b.visit("shop.site")
print(b.back(1))  # blog.site
print(b.back(1))  # news.site
print(b.forward(1))  # blog.site
b.visit("mail.site")
print(b.forward(2))  # mail.site
print(b.back(2))  # news.site
print(b.back(7))  # home.page
```

## Comparison

| Approach | visit | back / forward | Notes |
|---|---|---|---|
| Doubly linked list | `O(1)` amortized | `O(steps)` | explicit memory management in C++ |
| Two stacks | `O(1)` amortized | `O(steps)` | simplest to write |

## Edge Cases

- **`back` on the homepage:** stays on the homepage — the homepage is never removed.
- **`forward` after `visit`:** there is nothing ahead; the current page is returned.
- **Large `steps`:** movement stops at the first or last page.

## Practice Questions

:::details[How could back and forward run in O(1) time?]
Store the pages in an array with an index `cur` for the current page and `last` for the last valid page. `visit` writes at `cur + 1` and sets `last = cur + 1`; `back` sets `cur = max(0, cur - steps)`; `forward` sets `cur = min(last, cur + steps)`. Old forward pages are simply overwritten.
:::

:::details[Why does back keep at least one page in curr?]
The bottom of `curr` is the homepage, and the problem never lets you go back past it. Keeping `curr.size() > 1` also guarantees `curr.top()` always exists.
:::
