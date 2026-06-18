//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Saugat B Adhikari
// Version     : 1.0
// Description : CS 300 Project Two - Advising Assistance Program (BST)
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// ---------------------------------------------------------
// 1. Define the Course and Node Structures
// ---------------------------------------------------------
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

struct Node {
    Course course;
    Node* left;
    Node* right;

    // Default Constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // Initialize with a course
    Node(Course aCourse) : Node() {
        course = aCourse;
    }
};

// ---------------------------------------------------------
// 2. Binary Search Tree Implementation
// ---------------------------------------------------------
class BinarySearchTree {
private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void destroyTree(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void Insert(Course course);
    Course Search(string courseNumber);
    void PrintSortedList();
};

// Constructor
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

// Destructor
BinarySearchTree::~BinarySearchTree() {
    destroyTree(root);
}

// Recursively destroy the tree to free memory
void BinarySearchTree::destroyTree(Node* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

// Insert a course into the BST
void BinarySearchTree::Insert(Course course) {
    if (root == nullptr) {
        root = new Node(course);
    } else {
        this->addNode(root, course);
    }
}

// Recursive logic to find the correct insertion point based on alphanumeric order
void BinarySearchTree::addNode(Node* node, Course course) {
    // If the new course number is less than the current node's course number
    if (course.courseNumber.compare(node->course.courseNumber) < 0) {
        if (node->left == nullptr) {
            node->left = new Node(course);
        } else {
            addNode(node->left, course);
        }
    } 
    // If it's greater or equal, it goes to the right
    else {
        if (node->right == nullptr) {
            node->right = new Node(course);
        } else {
            addNode(node->right, course);
        }
    }
}

// Public method to trigger printing the list
void BinarySearchTree::PrintSortedList() {
    inOrder(root);
}

// In-Order Traversal to print courses in Alphanumeric order
void BinarySearchTree::inOrder(Node* node) {
    if (node != nullptr) {
        inOrder(node->left);
        cout << node->course.courseNumber << ", " << node->course.courseTitle << endl;
        inOrder(node->right);
    }
}

// Search for a specific course by its course number
Course BinarySearchTree::Search(string courseNumber) {
    Node* current = root;

    while (current != nullptr) {
        if (current->course.courseNumber.compare(courseNumber) == 0) {
            return current->course;
        } else if (courseNumber.compare(current->course.courseNumber) < 0) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    // Return an empty course if not found
    Course emptyCourse;
    return emptyCourse;
}

// ---------------------------------------------------------
// 3. Helper Functions & File Loading
// ---------------------------------------------------------

// Helper function to convert a string to uppercase for consistent searching
string toUpper(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

// Function to parse the CSV file and load courses into the BST
void loadCourses(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << "..." << endl;
    
    ifstream file(csvPath);
    if (!file.is_open()) {
        cout << "Error: File could not be opened. Please check the file name." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        // Remove carriage return at the end of the line if parsing a Windows file on a UNIX system
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        
        // Skip empty lines
        if (line.empty()) continue;

        stringstream ss(line);
        string token;
        vector<string> tokens;

        // Split the line by commas
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        // Validate: Ensure there are at least two parameters (ID and Title)
        if (tokens.size() < 2) {
            cout << "Error: Invalid line format. Skipping line." << endl;
            continue;
        }

        // Create the course and populate data
        Course newCourse;
        newCourse.courseNumber = tokens[0];
        newCourse.courseTitle = tokens[1];

        // Any remaining tokens are prerequisites
        for (size_t i = 2; i < tokens.size(); ++i) {
            // Prevent adding empty prerequisites
            if (!tokens[i].empty()) {
                newCourse.prerequisites.push_back(tokens[i]);
            }
        }

        // Insert into the BST
        bst->Insert(newCourse);
    }
    
    file.close();
    cout << "Data loaded successfully." << endl;
}

// ---------------------------------------------------------
// 4. Main Menu Loop
// ---------------------------------------------------------
int main() {
    // Instantiate the Binary Search Tree
    BinarySearchTree* bst = new BinarySearchTree();
    
    int choice = 0;
    string csvPath;
    string courseKey;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {
        cout << "\n  1. Load Data Structure." << endl;
        cout << "  2. Print Course List." << endl;
        cout << "  3. Print Course." << endl;
        cout << "  9. Exit" << endl;
        cout << "\nWhat would you like to do? ";
        
        cin >> choice;

        // Error handling for invalid menu input (e.g., characters instead of numbers)
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a valid number." << endl;
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1:
                cout << "Enter the file name to load (e.g., input.csv): ";
                cin >> csvPath;
                loadCourses(csvPath, bst);
                break;
                
            case 2:
                cout << "Here is a sample schedule:\n" << endl;
                bst->PrintSortedList();
                break;
                
            case 3:
                cout << "What course do you want to know about? ";
                cin >> courseKey;
                courseKey = toUpper(courseKey); // Ensure uppercase for strict matching
                
                {
                    Course course = bst->Search(courseKey);
                    if (!course.courseNumber.empty()) {
                        cout << course.courseNumber << ", " << course.courseTitle << endl;
                        cout << "Prerequisites: ";
                        
                        if (course.prerequisites.empty()) {
                            cout << "None" << endl;
                        } else {
                            for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                                cout << course.prerequisites[i];
                                if (i < course.prerequisites.size() - 1) {
                                    cout << ", ";
                                }
                            }
                            cout << endl;
                        }
                    } else {
                        cout << "Error: Course not found in the catalog." << endl;
                    }
                }
                break;
                
            case 9:
                cout << "Thank you for using the course planner!" << endl;
                break;
                
            default:
                cout << choice << " is not a valid option." << endl;
                break;
        }
    }

    // Clean up memory
    delete bst;
    return 0;
}
