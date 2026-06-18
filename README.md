# CS 300 – Data Structures and Algorithms Portfolio

**Student:** Saugat B Adhikari  
**Repository:** [github.com/SaugatBAdhikari/CS_300](https://github.com/SaugatBAdhikari/CS_300)

This repository contains portfolio artifacts from CS 300, showcasing work in data structures and algorithms through two course projects.

## Portfolio Contents

| Project | Artifact | Location |
|---------|----------|----------|
| Project One | Run-time and memory analysis of vector, hash table, and BST | [`project-one/data_structure_analysis.md`](project-one/data_structure_analysis.md) |
| Project Two | Advising Assistance Program — BST that sorts and prints CS courses in alphanumeric order | [`project-two/ProjectTwo.cpp`](project-two/ProjectTwo.cpp) |

### Running Project Two

Compile and run from the `project-two` directory:

```bash
g++ -o ProjectTwo ProjectTwo.cpp
./ProjectTwo
```

1. Choose option **1** and enter `input.csv` to load the course catalog.
2. Choose option **2** to print all courses sorted in alphanumeric order.

---

## Course Reflection

### What was the problem you were solving in the projects for this course?

In Project One, the problem was choosing the best data structure for ABCU's advising program—one that could load course data from a CSV file, look up individual courses quickly, and print the full catalog in alphanumeric order. I compared vector, hash table, and binary search tree approaches by writing pseudocode for each and analyzing their run-time and memory trade-offs. In Project Two, I implemented the recommended solution: an advising tool that loads the Computer Science course catalog into a binary search tree, prints a sorted course list, and lets students look up courses and their prerequisites.

### How did you approach the problem? Consider why data structures are important to understand.

I approached Project One by designing pseudocode for the same menu-driven workflow using three different data structures, then analyzing Big-O complexity for load, search, and print operations along with memory overhead for each. For Project Two, I implemented the binary search tree because in-order traversal naturally produces alphanumeric order without a separate sort step, and search runs in O(log n) on average. Understanding data structures matters because the same course catalog can be stored many ways—a vector requires O(n log n) sorting to print the list, while a hash table needs a temporary vector and sort, but a BST prints sorted output in O(n) with a single traversal.

### How did you overcome any roadblocks you encountered while going through the activities or project?

The binary search tree remove operation for nodes with two children was the most difficult lab challenge. Replacing the node with its in-order successor from the right subtree, then recursively deleting that successor, took several attempts before the tree stayed valid. In Project Two, parsing the CSV correctly on different platforms required handling carriage returns and empty prerequisite fields. I also added input validation for the menu so non-numeric entries would not crash the program. When timed tests showed unexpected results, I traced each operation's complexity rather than relying on assumptions about which structure would be fastest.

### How has your work on this project expanded your approach to designing software and developing programs?

Before this course, I tended to pick whatever container was familiar—usually a vector or array—for every problem. Now I start by asking what operations the program performs most often. If lookup by key dominates, I consider a hash table. If sorted output matters, a BST or sorted structure makes more sense. I also think about scale early: a structure that works for 100 records may fail for 12,000. Designing with the right abstraction from the start saves refactoring later.

### How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?

Working through the labs taught me to separate public interfaces from private recursive helpers, keep functions focused on one task, and manage memory explicitly with destructors that clean up dynamically allocated nodes. In Project Two, I organized the code into clear sections—structures, BST class, file loading, and menu logic—so each part can be changed independently. Using descriptive names like `PrintSortedList` and `loadCourses` makes the code easier to revisit months later, which is exactly what a portfolio should support. These habits make programs easier to extend, such as adding new menu options or swapping the BST for another structure without rewriting the entire application.
