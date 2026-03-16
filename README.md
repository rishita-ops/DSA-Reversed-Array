# DSA — Reverse an Array

A focused C++ implementation that **prints an array in reverse order** using a single backward traversal. Clean, minimal, and correct — this program is the entry point to understanding reverse traversal, the two-pointer technique, and the important distinction between **reversing output order** and **reversing the array in place**. The two-pointer in-place reverse built on this same idea is one of the most reused patterns in string, array, and linked-list problems.

---

## Problem Statement

Given an array of `n` integers entered by the user, print the elements in **reverse order**.

**Example Input:**
```
Enter the size of the array: 5
Enter the elements of the array: 10 20 30 40 50
```

**Example Output:**
```
The reversed array is: 50 40 30 20 10
```

---

## The Code

```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    int arr[n];
    cout << "Enter the elements of the array: ";
    for(int i = 0; i < n; i++)
        cin >> arr[i];

    cout << "The reversed array is: ";
    for(int i = n-1; i >= 0; i--)
        cout << arr[i] << " ";
}
```

---

## The Critical Distinction — Print-Reverse vs In-Place Reverse

This is the most important thing to understand about this program.

**The array `arr[]` is never modified.** The original elements remain in their original positions throughout the program. What changes is only the **order in which they are printed** — the loop walks the array from back to front, outputting each element as it goes.

```
Original arr[]:  10  20  30  40  50
                  ↑                ↑
                 i=0             i=4

Print loop:       i=4  i=3  i=2  i=1  i=0
Output:           50   40   30   20   10
```

After the loop, `arr[]` is still `{10, 20, 30, 40, 50}` in memory — unchanged.

| Approach | Modifies array? | Extra space? | Output |
|----------|----------------|-------------|--------|
| **Print-reverse (this code)** | ❌ No | O(1) | Prints reversed |
| In-place two-pointer reverse | ✅ Yes | O(1) | Array actually reversed |
| Copy-reverse | ✅ New array | O(n) | New reversed array |

When the goal is only to **display** the reverse, this approach is ideal. When downstream code needs the array to be physically reversed, an in-place reverse is required.

---

## How the Loop Works

```cpp
for(int i = n-1; i >= 0; i--)
    cout << arr[i] << " ";
```

- **Start:** `i = n-1` — the last valid index (0-based)
- **Condition:** `i >= 0` — runs until the first element is printed
- **Step:** `i--` — moves one position toward the front each iteration
- **Body:** prints `arr[i]` followed by a space

For `n = 5`, the loop runs 5 times: `i = 4, 3, 2, 1, 0` — accessing every element exactly once in reverse order.

> **Off-by-one note:** The condition is `i >= 0`, not `i > 0`. Using `i > 0` would skip `arr[0]` — the first element of the original array, which is the last element of the reversed output.

---

## Algorithm (Pseudocode)

```
read n
read arr[0..n-1]

for i from n-1 downto 0:
    print arr[i]
```

---

## Dry Run

**Input:** `arr[] = {3, 7, 1, 9, 5}`, `n = 5`

| `i` | `arr[i]` | Output so far |
|-----|----------|---------------|
| 4   | 5        | `5 ` |
| 3   | 9        | `5 9 ` |
| 2   | 1        | `5 9 1 ` |
| 1   | 7        | `5 9 1 7 ` |
| 0   | 3        | `5 9 1 7 3 ` |

**Output:** `The reversed array is: 5 9 1 7 3` ✅

---

## Complexity Analysis

| Metric | Complexity |
|--------|------------|
| Time   | **O(n)** — single backward pass; every element visited exactly once |
| Space  | **O(n)** — array of size `n` (VLA); O(1) auxiliary — no extra storage beyond the loop variable |

---

## Edge Cases

| Scenario | Behavior |
|----------|----------|
| `n = 1` | Loop runs once (`i = 0`); single element printed ✅ |
| `n = 2` | Two elements printed in swapped order ✅ |
| Already reversed input `{5, 4, 3, 2, 1}` | Printed as `1 2 3 4 5` — ascending ✅ |
| All elements equal `{7, 7, 7}` | Output identical to input — correct ✅ |
| Negative elements `{-3, -1, -5}` | Printed as `-5 -1 -3` — correct ✅ |
| `n = 0` | `i = -1 >= 0` is immediately false — loop skipped; label printed with nothing after it ⚠️ |

---

## The Missing `return 0`

The program has no explicit `return 0` at the end of `main()`:

```cpp
int main()
{
    // ...
    for(int i = n-1; i >= 0; i--)
        cout << arr[i] << " ";
    // ← no return 0
}
```

In **C++11 and later**, omitting `return 0` from `main()` is legal — the compiler inserts it implicitly. The program compiles and runs correctly. Explicit `return 0` is always the cleaner, more portable habit regardless.

---

## The Natural Extension — In-Place Two-Pointer Reverse

When the array itself needs to be reversed in memory (not just printed in reverse), the **two-pointer technique** is the standard O(1)-space solution:

```cpp
int left = 0, right = n - 1;
while(left < right)
{
    swap(arr[left], arr[right]);
    left++;
    right--;
}
```

**Trace for `{10, 20, 30, 40, 50}`:**

| Step | `left` | `right` | Array state |
|------|--------|---------|-------------|
| 1    | 0      | 4       | `{50, 20, 30, 40, 10}` |
| 2    | 1      | 3       | `{50, 40, 30, 20, 10}` |
| 3    | 2      | 2       | left == right → stop |

**Result:** `{50, 40, 30, 20, 10}` — array reversed in place ✅

| Property | Print-reverse (this code) | Two-pointer in-place |
|----------|--------------------------|----------------------|
| Array modified? | ❌ No | ✅ Yes |
| Extra space | O(1) | O(1) |
| Time | O(n) | O(n) |
| When to use | Display only | Need reversed array for further processing |

---

## A Note on `#include <bits/stdc++.h>`

The only header needed here is:

```cpp
#include <iostream>   // for cin, cout
```

`bits/stdc++.h` includes the entire C++ standard library — a GCC-specific convenience. Correct for competitive programming, not recommended in production or product-company interview code.

**VLA note:** `int arr[n]` is a Variable Length Array — GCC/C99 extension, not standard C++. For portable code, use `std::vector<int> arr(n)`.

---

## Repository Structure

```
DSA-Reverse-Array/
│
├── reverse_array.cpp     # Main C++ implementation
└── README.md             # Project documentation
```

---

## How to Compile and Run

**Prerequisites:** GCC / G++

```bash
# Clone the repository
git clone https://github.com/rishita-ops/DSA-Reverse-Array.git
cd DSA-Reverse-Array

# Compile
g++ reverse_array.cpp -o reverse_array

# Run
./reverse_array
```

**On Windows:**
```bash
g++ reverse_array.cpp -o reverse_array.exe
reverse_array.exe
```

---

## Key Concepts Covered

- **Reverse traversal** — iterating from `i = n-1` downto `i = 0` to access elements back-to-front
- **Print-reverse vs in-place reverse** — understanding the distinction between output order and memory order
- **`i >= 0` termination condition** — correctly includes index `0`; `i > 0` would skip the first element
- **Two-pointer technique** — the O(1)-space in-place reverse built directly on this idea
- **Implicit `return 0`** — legal in C++11+, but explicit is always cleaner
- **VLA (`int arr[n]`)** — GCC extension; prefer `std::vector<int>` for portability
- **`bits/stdc++.h`** — only `<iostream>` is needed here

---

## Why This Problem Matters in DSA

The reverse traversal and two-pointer reverse pattern appears across a broad family of problems:

| Problem / Concept | Connection |
|-------------------|------------|
| **Reverse String** (LeetCode #344) | Two-pointer in-place reverse on a `char` array — direct extension |
| **Palindrome Check** | Compare characters from both ends — reverse traversal intuition |
| **Rotate Array** (LeetCode #189) | Optimal solution reverses three subarrays in sequence |
| **Reverse Linked List** (LeetCode #206) | Same two-pointer idea adapted for pointer manipulation |
| **Reverse Words in a String** (LeetCode #151) | Reverse the full string, then reverse each word — uses this primitive twice |
| **Valid Palindrome** (LeetCode #125) | Two pointers from both ends checking character equality |
| **Trapping Rain Water** (LeetCode #42) | Left and right pointer prefix arrays — reverse traversal in precomputation |

Every problem involving symmetry, mirroring, or meeting-in-the-middle traces back to the reverse traversal intuition introduced here.

---

## Contributing

Contributions are welcome. Consider adding:
- An **in-place two-pointer reverse** version that modifies the array
- A version that **prints both original and reversed** for comparison
- A version using `std::reverse` from `<algorithm>` for contrast
- Input validation for `n = 0`
- Implementations in Python, Java, or JavaScript

```bash
git checkout -b feature/your-feature
git commit -m "Add: your feature description"
git push origin feature/your-feature
# Then open a Pull Request
```

---

## License

This project is open-source and available under the [MIT License](LICENSE).

---

*Part of a structured DSA practice series — fundamentals, done right.*
