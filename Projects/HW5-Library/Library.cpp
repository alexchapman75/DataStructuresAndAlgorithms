#include "Library.h"
#include <iostream>

using namespace std;

Library::Library() : bookTop(nullptr), studentFront(nullptr), studentRear(nullptr), bookCount(0), studentCount(0) {}

Library::~Library() {
    // TODO: implement destructor to free all nodes in stack and queue
    clear();
}

void Library::addBook(string title) {
    // TODO: Implement Stack Push (LIFO)
    BookNode* newNode = new BookNode;
    newNode->title = title;
    newNode->next = bookTop;

    bookTop = newNode;
    bookCount++;
}

Library::Library(const Library& other)
    : bookTop(nullptr),
      studentFront(nullptr),
      studentRear(nullptr),
      bookCount(0),
      studentCount(0)
{
    // Copy stack (preserve order)
    BookNode* temp = other.bookTop;
    BookNode* reversed = nullptr;

    while (temp != nullptr) {
        BookNode* newNode = new BookNode{temp->title, reversed};
        reversed = newNode;
        temp = temp->next;
    }

    while (reversed != nullptr) {
        addBook(reversed->title);
        BookNode* toDelete = reversed;
        reversed = reversed->next;
        delete toDelete;
    }

    // Copy queue (preserve order)
    StudentNode* current = other.studentFront;
    while (current != nullptr) {
        enqueueStudent(current->data.name,
                       current->data.booksRequested);
        current = current->next;
    }
}

Library& Library::operator=(const Library& other) {
    if (this == &other)
        return *this;

    clear();

    // Copy stack
    BookNode* temp = other.bookTop;
    BookNode* reversed = nullptr;

    while (temp != nullptr) {
        BookNode* newNode = new BookNode{temp->title, reversed};
        reversed = newNode;
        temp = temp->next;
    }

    while (reversed != nullptr) {
        addBook(reversed->title);
        BookNode* toDelete = reversed;
        reversed = reversed->next;
        delete toDelete;
    }

    // Copy queue
    StudentNode* current = other.studentFront;
    while (current != nullptr) {
        enqueueStudent(current->data.name,
                       current->data.booksRequested);
        current = current->next;
    }

    return *this;
}

Library::Library(Library&& other) noexcept
    : bookTop(other.bookTop),
      studentFront(other.studentFront),
      studentRear(other.studentRear),
      bookCount(other.bookCount),
      studentCount(other.studentCount)
{
    other.bookTop = nullptr;
    other.studentFront = nullptr;
    other.studentRear = nullptr;
    other.bookCount = 0;
    other.studentCount = 0;
}


Library& Library::operator=(Library&& other) noexcept {
    if (this == &other)
        return *this;

    clear();

    bookTop = other.bookTop;
    studentFront = other.studentFront;
    studentRear = other.studentRear;
    bookCount = other.bookCount;
    studentCount = other.studentCount;

    other.bookTop = nullptr;
    other.studentFront = nullptr;
    other.studentRear = nullptr;
    other.bookCount = 0;
    other.studentCount = 0;

    return *this;
}


bool Library::enqueueStudent(string name, int count) {
    // TODO: Implement Queue Enqueue (FIFO)
    if (count < 1 || count > 5)
        return false;

    StudentNode* newNode = new StudentNode;
    newNode->data.name = name;
    newNode->data.booksRequested = count;
    newNode->next = nullptr;

    if (studentFront == nullptr) {
        // Empty queue
        studentFront = studentRear = newNode;
    } else {
        studentRear->next = newNode;
        studentRear = newNode;
    }

    studentCount++;
    return true;
}

IssueResult Library::issueBook() {
    IssueResult result{0, 0, false};

    // TODO: Implement the issuance logic
    // No students waiting
    if (studentFront == nullptr)
        return result;

    // Dequeue front student
    StudentNode* currentStudent = studentFront;
    studentFront = studentFront->next;

    if (studentFront == nullptr)
        studentRear = nullptr;

    studentCount--;

    int requested = currentStudent->data.booksRequested;

    // Defensive check (should never trigger because enqueue validates)
    if (requested > 5) {
        result.invalidRequest = true;
        delete currentStudent;
        return result;
    }

    // Issue books (pop from stack)
    while (requested > 0 && bookTop != nullptr) {
        BookNode* temp = bookTop;
        bookTop = bookTop->next;

        delete temp;
        bookCount--;

        result.booksIssued++;
        requested--;
    }

    // Remaining requested are denied
    result.booksDenied = requested;

    delete currentStudent;

    return result;
}

void Library::showBooks() const {
    // TODO: Traverse the stack from bookTop and print titles
    if (bookTop == nullptr) {
        cout << "Available Books (Top to Bottom):\n";
        cout << "  (No books available)\n";
        return;
    }

    cout << "Available Books (Top to Bottom):\n";
    BookNode* temp = bookTop;
    while (temp != nullptr) {
        cout << "- " << temp->title << endl;
        temp = temp->next;
    }
}

void Library::showStudents() const {
    // TODO: Traverse the queue from studentFront and print names/requests
    if (studentFront == nullptr) {
        cout << "Waiting Students (FIFO Order):\n";
        cout << "  (No students waiting)\n";
        return;
    }

    cout << "Waiting Students (FIFO Order):\n";
    StudentNode* temp = studentFront;
    while (temp != nullptr) {
        cout << "- " << temp->data.name
             << " (" << temp->data.booksRequested
             << " requested)\n";
        temp = temp->next;
    }
}

void Library::clear() {
    // TODO: Manually delete all nodes in the stack and queue to prevent memory leaks
    // Clear book stack
    while (bookTop != nullptr) {
        BookNode* temp = bookTop;
        bookTop = bookTop->next;
        delete temp;
    }

    // Clear student queue
    while (studentFront != nullptr) {
        StudentNode* temp = studentFront;
        studentFront = studentFront->next;
        delete temp;
    }

    studentRear = nullptr;

    bookCount = 0;
    studentCount = 0;
}