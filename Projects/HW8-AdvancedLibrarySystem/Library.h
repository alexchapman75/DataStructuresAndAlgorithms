#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <iostream>
#include "LibrarySystem.h"

class Library {
private:
    struct ItemNode {
        LibraryItem* item;
        ItemNode* next;
        ItemNode(LibraryItem* it, ItemNode* n=nullptr) : item(it), next(n) {}
    };

    struct BorrowNode {
        std::string title;
        BorrowNode* next;
        BorrowNode(const std::string& t, BorrowNode* n=nullptr) : title(t), next(n) {}
    };

    struct TaskNode {
        Task* task;
        TaskNode* next;
        TaskNode(Task* t, TaskNode* n=nullptr) : task(t), next(n) {}
    };

    ItemNode* catalogHead;
    BorrowNode* borrowedHead;
    TaskNode* taskTop;

    int catalogCount;
    int borrowedCount;
    int taskCount;

    void clear();

    // Polymorphic deep-copy helpers
    static LibraryItem* cloneItem(const LibraryItem* src);
    static Task* cloneTask(const Task* src);

    // borrowed list helpers
    void recordBorrow(const std::string& title);
    bool removeBorrowRecordOnce(const std::string& title);

public:
    Library();
    ~Library();

    // Rule of 5
    Library(const Library& other);
    Library& operator=(const Library& other);
    Library(Library&& other) noexcept;
    Library& operator=(Library&& other) noexcept;

    // ===== Catalog =====
    bool addItem(LibraryItem* item); // takes ownership; rejects duplicates (delete on reject)
    LibraryItem* findItem(const std::string& title) const; // non-owning
    bool borrowItem(const std::string& title);  // must add borrowed record on success
    bool returnItem(const std::string& title);  // must fail if never borrowed
    void listCatalog(std::ostream& os) const;   // sorted by title, 1 per line
    int getCatalogCount() const { return catalogCount; }

    // UI selection helpers (1-based)
    void listCatalogNumbered(std::ostream& os) const;
    std::string getCatalogTitleByIndex(int index1based) const;

    // ===== Borrowed list =====
    void listBorrowed(std::ostream& os) const; // 1 per line
    void listBorrowedNumbered(std::ostream& os) const;
    std::string getBorrowedTitleByIndex(int index1based) const;
    int getBorrowedCount() const { return borrowedCount; }

    // ===== Tasks stack =====
    void pushTask(Task* task); // takes ownership
    Task* peekTask() const;    // non-owning
    Task* popTask();           // owning pointer returned; caller deletes
    bool processNextTask(std::ostream& log); // pops, executes, deletes task
    void listTasks(std::ostream& os) const;  // 1 per line
    int getTaskCount() const { return taskCount; }
};

#endif
