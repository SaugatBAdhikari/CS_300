# CS 300 Project One: Pseudocode and Runtime Analysis

**Author:** Saugat B Adhikari  
**Course:** CS 300 – Data Structures and Algorithms

## Part 1: Main Menu Pseudocode

This menu acts as the main driver for the program, regardless of the underlying data structure used.

```
FUNCTION MainMenu()
    SET choice = 0
    WHILE choice NOT EQUALS 9 DO
        PRINT "1. Load Data"
        PRINT "2. Print Course List (Alphanumeric)"
        PRINT "3. Print Course Information"
        PRINT "9. Exit"
        PRINT "Enter choice: "
        READ choice

        IF choice EQUALS 1 THEN
            LoadCourses()
        ELSE IF choice EQUALS 2 THEN
            PrintSortedList()
        ELSE IF choice EQUALS 3 THEN
            PRINT "What course do you want to know about?"
            READ courseKey
            PrintCourseInformation(courseKey)
        ELSE IF choice NOT EQUALS 9 THEN
            PRINT "Invalid option. Please try again."
        END IF
    END WHILE
    PRINT "Thank you for using the course planner!"
END FUNCTION
```

---

## Part 2: Data Structure Pseudocode (Load, Print, Sort)

### 2A. Vector Implementation

**Data Structure**

```
STRUCT Course
    STRING courseNumber
    STRING courseTitle
    VECTOR OF STRING prerequisites
END STRUCT
```

**Load Data**

```
FUNCTION LoadCourses(filename)
    VECTOR OF Course courses
    OPEN filename FOR READING
    WHILE NOT EndOfFile(filename)
        READ line FROM filename
        tokens = SPLIT line BY ','
        IF tokens.length < 2 THEN CONTINUE
        CREATE Course newCourse
        newCourse.courseNumber = tokens[0]
        newCourse.courseTitle = tokens[1]
        FOR i FROM 2 TO tokens.length - 1
            ADD tokens[i] TO newCourse.prerequisites
        END FOR
        ADD newCourse TO courses
    END WHILE
    CLOSE filename
    RETURN courses
END FUNCTION
```

**Print Sorted List**

```
FUNCTION PrintSortedList(coursesVector)
    SORT coursesVector BY courseNumber ASCENDING
    FOR EACH course IN coursesVector
        PRINT course.courseNumber + ", " + course.courseTitle
    END FOR
END FUNCTION
```

### 2B. Hash Table Implementation

**Print Sorted List** (requires extracting to a temporary structure)

```
FUNCTION PrintSortedList(hashTable)
    VECTOR OF Course tempCourses
    FOR i FROM 0 TO hashTable.tableSize - 1
        SET current = hashTable.table[i]
        WHILE current IS NOT NULL DO
            ADD current.course TO tempCourses
            current = current.next
        END WHILE
    END FOR
    SORT tempCourses BY courseNumber ASCENDING
    FOR EACH course IN tempCourses
        PRINT course.courseNumber + ", " + course.courseTitle
    END FOR
END FUNCTION
```

### 2C. Binary Search Tree Implementation

**Print Sorted List** (utilizes in-order traversal)

```
FUNCTION PrintSortedList(node)
    IF node IS NULL THEN RETURN
    PrintSortedList(node.leftChild)
    PRINT node.course.courseNumber + ", " + node.course.courseTitle
    PrintSortedList(node.rightChild)
END FUNCTION
```

---

## Part 3: Run-Time Analysis (Big O)

The following table evaluates the worst-case running time for opening the file, reading the lines, and storing the course objects into the respective data structures. Assume **n** is the number of courses in the file.

| Data Structure | Action / Line of Code | Cost | Executions | Total Worst Case |
|----------------|----------------------|------|------------|------------------|
| **Vector** | WHILE NOT EndOfFile (Read Line) | 1 | n | |
| **Vector** | ADD newCourse TO courses | 1 (Amortized) | n | **O(n)** |
| **Hash Table** | WHILE NOT EndOfFile (Read Line) | 1 | n | |
| **Hash Table** | Hash(courseNumber) | 1 | n | |
| **Hash Table** | Insert (Handling Collisions) | 1 to n (if all collide) | n | **O(n²)** |
| **Binary Search Tree** | WHILE NOT EndOfFile (Read Line) | 1 | n | |
| **Binary Search Tree** | InsertNode(currentNode, newCourse) | 1 to n (if unbalanced) | n | **O(n²)** |

**Note:** While the average case for BST insertion is O(n log n), the absolute worst-case scenario (inserting already sorted data into a BST without balancing) degrades to a linked list, resulting in O(n²) time complexity.

### Additional Run-Time Considerations

| Operation | Vector | Hash Table | Binary Search Tree |
|-----------|--------|------------|-------------------|
| Search course by number | O(n) linear scan | O(1) average | O(log n) average |
| Print sorted list | O(n log n) sort required | O(n) extract + O(n log n) sort | O(n) in-order traversal |
| Load all courses | O(n) | O(n) average; O(n²) worst | O(n log n) average; O(n²) worst |

---

## Part 4: Memory Analysis

| Structure | Memory Characteristics |
|-----------|------------------------|
| **Vector** | Contiguous storage with minimal per-element overhead. No pointer storage between elements. May reserve extra capacity, using slightly more memory than strictly necessary but with excellent cache locality. |
| **Hash Table** | Fixed bucket array allocated upfront plus one node per course (with chain pointers). Printing sorted output requires an additional temporary vector of size n, costing O(n) extra memory during that operation. |
| **Binary Search Tree** | Each node stores a course plus left and right child pointers. Uses more memory per course than a vector due to pointer overhead and scattered heap allocation, but avoids temporary structures when printing sorted output. |

---

## Part 5: Evaluation and Recommendation

### Vector

**Advantages:** Vectors are simple to implement, provide excellent cache locality, and allow for O(1) amortized appending. They are memory efficient since they do not require pointers for nodes.

**Disadvantages:** Searching for a specific course is O(n) because it requires a linear scan. Printing in alphanumeric order requires a separate sorting operation (O(n log n)) each time, unless maintained sorted upon insertion (which makes insertion O(n)).

### Hash Table

**Advantages:** Hash tables offer average O(1) time complexity for searching, making Option 3 of the menu incredibly fast. Loading data is also generally O(1) amortized per insert.

**Disadvantages:** Hash tables inherently destroy any natural ordering of the data. To fulfill the requirement of printing courses in alphanumeric order, all data must be extracted into a temporary vector and sorted, costing O(n log n) time and O(n) additional memory.

### Binary Search Tree (BST)

**Advantages:** A BST naturally keeps data in sorted order dynamically. By performing a simple in-order traversal, the course list prints in perfect alphanumeric order in exactly O(n) time without needing secondary arrays or sorting algorithms. Search operations are O(log n) on average.

**Disadvantages:** If the data from the file is already sorted, the tree can become unbalanced (acting like a linked list), dropping search and insert efficiency to O(n). It also uses more memory than a vector due to left and right child pointers.

### Final Recommendation

Based on the specific requirements of ABCU's advising program—loading data, looking up individual courses, and printing the entire catalog in alphanumeric order—the **Binary Search Tree (BST)** is the recommended data structure.

The hash table requires significant overhead (extracting and sorting) just to print the list, and the vector is too slow for individual lookups (O(n)). The BST strikes the best balance: it provides efficient O(log n) search for advising specific courses and naturally supports O(n) sorted output via in-order traversal, aligning with both primary goals of the program.

---

*Original submission also available as `CS_300_Project_One_Final.docx` in this directory.*
