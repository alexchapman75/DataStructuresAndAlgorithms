#ifndef TASKLIST_H
#define TASKLIST_H

#include <string>

struct Task {
    // Helpful for making list
    Task *next;

    // Added fields for implementation
    std::string name;
    int date;

    Task(const std::string& n, int d)
        : next(nullptr), name(n), date(d) {}
};

class TaskList {
private:
    // Add implementation-specific private members here
    Task* head;

    // Add other member functions as needed.
    void clear();
    void copyFrom(const TaskList& other);

public:
    // Provide a default constructor
    TaskList();
    // Optionally, add additional constructors

    // Destructor, remove all nodes allocated for list
    ~TaskList();
    // Follow rule 0/3/5
    // Add other special member functions as needed
    TaskList(const TaskList& other);
    TaskList& operator=(const TaskList& other);
    TaskList(TaskList&& other) noexcept;
    TaskList& operator=(TaskList&& other) noexcept;

    // DO NOT MODIFY THE FUNCTION INTERFACES BELOW.
    // YOU MUST KEEP NAME, PARAMETERS, AND RETURN TYPES THE SAME.

    // Description: Return true if date is found on a task
    // Parameters: int date - date to validate: YYYYMMDD, e.g. 20260704 is July 4, 2026
    // Returns: true if valid, false otherwise
    bool isValidDate(int date);

    // Description: add task to list in sorted order by date
    // Parameters: string name - name of task
    //             int date - due date in YYYYMMDD format
    // Returns: true if added, false if date invalid
    bool addTask(std::string name, int date);

    // Decription: display tasks in ascending order; print each task's name and due date
    //             on a line by itself. Other formatting is up to you.
    // Parameters: none
    // Returns: void
    void displayAscending();

    // Decription: display tasks in descending order; print each task's name and due date
    //             on a line by itself. Other formatting is up to you.
    // Parameters: none
    // Returns: void
    void displayDescending();

    // Decription: display tasks for a particular date; print each task's name and due date
    //             on a line by itself. Other formatting is up to you.
    // Parameters: int date - date to display tasks for
    // Returns: void
    void displayTasksForDate(int date);

    // Decription: remove tasks with dueDate after the given date
    // Parameters: int date - cutoff date
    // Returns: void
    void removeTasksAfter(int date);
};

#endif
