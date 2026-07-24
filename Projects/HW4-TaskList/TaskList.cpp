#include <iostream>
#include "TaskList.h"

using namespace std;

// Provide a default constructor
TaskList::TaskList() : head(nullptr) {}

// Destructor, remove all nodes allocated for list
TaskList::~TaskList()
{
    clear();
}

void TaskList::clear() {
    while (head) {
        Task* temp = head;
        head = head->next;
        delete temp;
    }
}

void TaskList::copyFrom(const TaskList& other) {
    if (!other.head) {
        head = nullptr;
        return;
    }

    head = new Task(other.head->name, other.head->date);
    Task* curr = head;
    Task* src = other.head->next;

    while (src) {
        curr->next = new Task(src->name, src->date);
        curr = curr->next;
        src = src->next;
    }
}

// Copy constructor
TaskList::TaskList(const TaskList& other) : head(nullptr)
{
    copyFrom(other);
}

// Copy assignment operator
TaskList& TaskList::operator=(const TaskList& other)
{
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

// Move constructor
TaskList::TaskList(TaskList&& other) noexcept : head(other.head)
{
    other.head = nullptr;
}

// Move assignment operator
TaskList& TaskList::operator=(TaskList&& other) noexcept
{
    if (this != &other) {
        clear();
        head = other.head;
        other.head = nullptr;
    }
    return *this;
}


// Description: Return true if date is found on a task
// Parameters: int date - date to validate
// Returns: true if valid, false otherwise
bool TaskList::isValidDate(int date)
{
    if (date < 10000101 || date > 99991231) return false;

    int day = date % 100;
    int month = (date / 100) % 100;
    int year = date / 10000;

    if (month < 1 || month > 12) return false;

    int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (leap) daysInMonth[1] = 29;

    return day >= 1 && day <= daysInMonth[month - 1];
}

// Description: add task to list in sorted order by date
// Parameters: string name - name of task
//             int date - due date in YYYYMMDD format
// Returns: true if added, false if date invalid
bool TaskList::addTask(string name, int date)
{
    if (!isValidDate(date)) return false;

    Task* newTask = new Task(name, date);

    if (!head || date < head->date) {
        newTask->next = head;
        head = newTask;
        return true;
    }

    Task* curr = head;
    while (curr->next && curr->next->date <= date) {
        curr = curr->next;
    }

    newTask->next = curr->next;
    curr->next = newTask;
    return true;
}

// Decription: display tasks in ascending order; print each task's name and due date
//             on a line by itself. Other formatting is up to you.
// Parameters: none
// Returns: void
void TaskList::displayAscending()
{
    if (!head) {
        cout << "No tasks available" << endl;
        return;
    }

    Task* curr = head;
    while (curr) {
        cout << curr->date << ": " << curr->name << endl;
        curr = curr->next;
    }
}

// Decription: display tasks in ascending order; print each task's name and due date
//             on a line by itself. Other formatting is up to you.
// Parameters: none
// Returns: void
void TaskList::displayDescending()
{
    // Count nodes
    int count = 0;
    Task* curr = head;
    while (curr) {
        count++;
        curr = curr->next;
    }

    // Print from last to first
    for (int i = count - 1; i >= 0; i--) {
        curr = head;
        for (int j = 0; j < i; j++) {
            curr = curr->next;
        }
        cout << curr->date << ": " << curr->name << endl;
    }
}

// Decription: display tasks for a particular date; print each task's name and due date
//             on a line by itself. Other formatting is up to you.
// Parameters: int date - date to display tasks for
// Returns: void
void TaskList::displayTasksForDate(int date)
{
    if (!head) {
        cout << "No tasks available" << endl;
        return;
    }

    bool found = false;
    Task* curr = head;

    while (curr) {
        if (curr->date == date) {
            cout << curr->date << ": " << curr->name << endl;
            found = true;
        }
        curr = curr->next;
    }

    if (!found) {
        cout << "No tasks found for this date" << endl;
    }
}

// Decription: remove tasks with dueDate after the given date
// Parameters: int date - cutoff date
// Returns: void
void TaskList::removeTasksAfter(int date)
{
    while (head && head->date > date) {
        Task* temp = head;
        head = head->next;
        delete temp;
    }

    Task* curr = head;
    while (curr && curr->next) {
        if (curr->next->date > date) {
            Task* temp = curr->next;
            curr->next = temp->next;
            delete temp;
        } else {
            curr = curr->next;
        }
    }
}
