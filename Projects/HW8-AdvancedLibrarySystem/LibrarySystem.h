#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include <string>
#include <iostream>

// Forward declaration to avoid circular include.
// Task::execute will be implemented in LibrarySystem.cpp (which includes Library.h).
class Library;

/* ================= LIBRARY ITEMS ================= */

class LibraryItem {
protected:
    std::string title;
    int totalCopies;
    int availableCopies;

public:
    LibraryItem(std::string t, int copies);

    virtual void display(std::ostream& os) const = 0;
    virtual int getBorrowDuration() const = 0;
    virtual double calculateFine(int daysLate) const = 0;

    bool isAvailable() const;
    void borrowCopy();   // decrements if possible
    void returnCopy();   // increments if possible
    std::string getTitle() const;

    virtual ~LibraryItem();
};

class Book : public LibraryItem {
public:
    Book(std::string t, int copies);
    void display(std::ostream& os) const override;
    int getBorrowDuration() const override;
    double calculateFine(int daysLate) const override;
    ~Book() override;
};

class Journal : public LibraryItem {
public:
    Journal(std::string t, int copies);
    void display(std::ostream& os) const override;
    int getBorrowDuration() const override;
    double calculateFine(int daysLate) const override;
    ~Journal() override;
};

class Magazine : public LibraryItem {
public:
    Magazine(std::string t, int copies);
    void display(std::ostream& os) const override;
    int getBorrowDuration() const override;
    double calculateFine(int daysLate) const override;
    ~Magazine() override;
};

/* ================= TASKS ================= */

class Task {
public:
    virtual void display(std::ostream& os) const = 0;
    virtual int getPriority() const = 0;

    // Option B: tasks execute actions on the Library backend
    virtual bool execute(Library& lib, std::ostream& log) const = 0;

    virtual ~Task();
};

class BorrowTask : public Task {
    std::string title;
public:
    explicit BorrowTask(std::string t);
    const std::string& getTitle() const { return title; }

    void display(std::ostream& os) const override;
    int getPriority() const override;
    bool execute(Library& lib, std::ostream& log) const override;
};

class ReturnTask : public Task {
    std::string title;
public:
    explicit ReturnTask(std::string t);
    const std::string& getTitle() const { return title; }

    void display(std::ostream& os) const override;
    int getPriority() const override;
    bool execute(Library& lib, std::ostream& log) const override;
};

class PersonalTask : public Task {
    std::string note;
public:
    explicit PersonalTask(std::string n);
    const std::string& getNote() const { return note; }

    void display(std::ostream& os) const override;
    int getPriority() const override;
    bool execute(Library& lib, std::ostream& log) const override;
};

#endif
