#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>

struct Student {
    std::string name;
    int booksRequested;
};

struct IssueResult {
    int booksIssued;
    int booksDenied;
    bool invalidRequest;
};

// Internal nodes for manual implementation
struct BookNode {
    std::string title;
    BookNode* next;
};

struct StudentNode {
    Student data;
    StudentNode* next;
};

class Library {
private:
    BookNode* bookTop;         // Stack Top (LIFO)
    StudentNode* studentFront; // Queue Front (FIFO)
    StudentNode* studentRear;  // Queue Rear

    int bookCount;
    int studentCount;

public:
    Library();
    ~Library();

    Library(const Library& other);            // Copy constructor
    Library& operator=(const Library& other); // Copy assignment

    Library(Library&& other) noexcept;        // Move constructor
    Library& operator=(Library&& other) noexcept; // Move assignment

    // Core Logic to be implemented
    void addBook(std::string title);
    bool enqueueStudent(std::string name, int count);
    IssueResult issueBook();

    // Helper functions
    int getBookCount() const { return bookCount; }
    int getStudentCount() const { return studentCount; }
    void showBooks() const;
    void showStudents() const;
    void clear();
};

#endif