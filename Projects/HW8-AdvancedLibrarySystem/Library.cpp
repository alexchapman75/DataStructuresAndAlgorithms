#include "Library.h"
#include <stdexcept>

/* ================= Constructors / Destructor ================= */

Library::Library()
    : catalogHead(nullptr), borrowedHead(nullptr), taskTop(nullptr),
      catalogCount(0), borrowedCount(0), taskCount(0) {}

Library::~Library() {
    clear();
}

/* ================= Rule of 5 ================= */

Library::Library(const Library& other)
    : catalogHead(nullptr), borrowedHead(nullptr), taskTop(nullptr),
      catalogCount(0), borrowedCount(0), taskCount(0)
{
    // copy catalog
    ItemNode* cur = other.catalogHead;
    ItemNode* tail = nullptr;

    while (cur) {
        LibraryItem* copy = cloneItem(cur->item);
        ItemNode* node = new ItemNode(copy);

        if (!catalogHead) catalogHead = node;
        else tail->next = node;

        tail = node;
        cur = cur->next;
        catalogCount++;
    }

    // copy borrowed list
    BorrowNode* bcur = other.borrowedHead;
    BorrowNode* btail = nullptr;

    while (bcur) {
        BorrowNode* node = new BorrowNode(bcur->title);

        if (!borrowedHead) borrowedHead = node;
        else btail->next = node;

        btail = node;
        bcur = bcur->next;
        borrowedCount++;
    }

    // copy task stack (preserve order)
    TaskNode* tcur = other.taskTop;
    TaskNode* temp = nullptr;

    while (tcur) {
        temp = new TaskNode(cloneTask(tcur->task), temp);
        tcur = tcur->next;
    }

    while (temp) {
        pushTask(temp->task);
        TaskNode* d = temp;
        temp = temp->next;
        delete d;
    }
}

Library& Library::operator=(const Library& other) {
    if (this == &other) return *this;

    clear();

    ItemNode* cur = other.catalogHead;
    while (cur) {
        addItem(cloneItem(cur->item));
        cur = cur->next;
    }

    BorrowNode* bcur = other.borrowedHead;
    while (bcur) {
        recordBorrow(bcur->title);
        bcur = bcur->next;
    }

    TaskNode* tcur = other.taskTop;
    TaskNode* temp = nullptr;

    while (tcur) {
        temp = new TaskNode(cloneTask(tcur->task), temp);
        tcur = tcur->next;
    }

    while (temp) {
        pushTask(temp->task);
        TaskNode* d = temp;
        temp = temp->next;
        delete d;
    }

    return *this;
}

Library::Library(Library&& other) noexcept
{
    catalogHead = other.catalogHead;
    borrowedHead = other.borrowedHead;
    taskTop = other.taskTop;

    catalogCount = other.catalogCount;
    borrowedCount = other.borrowedCount;
    taskCount = other.taskCount;

    other.catalogHead = nullptr;
    other.borrowedHead = nullptr;
    other.taskTop = nullptr;

    other.catalogCount = 0;
    other.borrowedCount = 0;
    other.taskCount = 0;
}

Library& Library::operator=(Library&& other) noexcept {
    if (this == &other) return *this;

    clear();

    catalogHead = other.catalogHead;
    borrowedHead = other.borrowedHead;
    taskTop = other.taskTop;

    catalogCount = other.catalogCount;
    borrowedCount = other.borrowedCount;
    taskCount = other.taskCount;

    other.catalogHead = nullptr;
    other.borrowedHead = nullptr;
    other.taskTop = nullptr;

    other.catalogCount = 0;
    other.borrowedCount = 0;
    other.taskCount = 0;

    return *this;
}

/* ================= Private Helpers ================= */

void Library::clear()
{
    while (catalogHead) {
        ItemNode* t = catalogHead;
        catalogHead = catalogHead->next;
        delete t->item;
        delete t;
    }

    while (borrowedHead) {
        BorrowNode* t = borrowedHead;
        borrowedHead = borrowedHead->next;
        delete t;
    }

    while (taskTop) {
        TaskNode* t = taskTop;
        taskTop = taskTop->next;
        delete t->task;
        delete t;
    }

    catalogCount = borrowedCount = taskCount = 0;
}

LibraryItem* Library::cloneItem(const LibraryItem* src)
{
    if (!src) return nullptr;

    if (auto b = dynamic_cast<const Book*>(src))
        return new Book(b->getTitle(), b->isAvailable() ? 1 : 1);

    if (auto j = dynamic_cast<const Journal*>(src))
        return new Journal(j->getTitle(), j->isAvailable() ? 1 : 1);

    if (auto m = dynamic_cast<const Magazine*>(src))
        return new Magazine(m->getTitle(), m->isAvailable() ? 1 : 1);

    return nullptr;
}

Task* Library::cloneTask(const Task* src)
{
    if (!src) return nullptr;

    if (auto b = dynamic_cast<const BorrowTask*>(src))
        return new BorrowTask(b->getTitle());

    if (auto r = dynamic_cast<const ReturnTask*>(src))
        return new ReturnTask(r->getTitle());

    if (auto p = dynamic_cast<const PersonalTask*>(src))
        return new PersonalTask(p->getNote());

    return nullptr;
}

void Library::recordBorrow(const std::string& title)
{
    borrowedHead = new BorrowNode(title, borrowedHead);
    borrowedCount++;
}

bool Library::removeBorrowRecordOnce(const std::string& title)
{
    BorrowNode* cur = borrowedHead;
    BorrowNode* prev = nullptr;

    while (cur) {
        if (cur->title == title) {
            if (prev) prev->next = cur->next;
            else borrowedHead = cur->next;

            delete cur;
            borrowedCount--;
            return true;
        }

        prev = cur;
        cur = cur->next;
    }

    return false;
}

/* ================= Catalog ================= */

bool Library::addItem(LibraryItem* item)
{
    if (!item) return false;

    if (findItem(item->getTitle())) {
        delete item;
        return false;
    }

    ItemNode* node = new ItemNode(item);

    if (!catalogHead || item->getTitle() < catalogHead->item->getTitle()) {
        node->next = catalogHead;
        catalogHead = node;
    } else {
        ItemNode* cur = catalogHead;
        while (cur->next && cur->next->item->getTitle() < item->getTitle())
            cur = cur->next;

        node->next = cur->next;
        cur->next = node;
    }

    catalogCount++;
    return true;
}

LibraryItem* Library::findItem(const std::string& title) const
{
    ItemNode* cur = catalogHead;

    while (cur) {
        if (cur->item->getTitle() == title)
            return cur->item;
        cur = cur->next;
    }

    return nullptr;
}

bool Library::borrowItem(const std::string& title)
{
    LibraryItem* item = findItem(title);

    if (!item || !item->isAvailable())
        return false;

    item->borrowCopy();
    recordBorrow(title);

    return true;
}

bool Library::returnItem(const std::string& title)
{
    if (!removeBorrowRecordOnce(title))
        return false;

    LibraryItem* item = findItem(title);
    if (!item) return false;

    item->returnCopy();
    return true;
}

void Library::listCatalog(std::ostream& os) const
{
    ItemNode* cur = catalogHead;

    while (cur) {
        os << cur->item->getTitle() << "\n";
        cur = cur->next;
    }
}

void Library::listCatalogNumbered(std::ostream& os) const
{
    ItemNode* cur = catalogHead;
    int i = 1;

    while (cur) {
        os << i++ << ") " << cur->item->getTitle() << "\n";
        cur = cur->next;
    }
}

std::string Library::getCatalogTitleByIndex(int index) const
{
    if (index <= 0) return "";

    ItemNode* cur = catalogHead;
    int i = 1;

    while (cur) {
        if (i == index)
            return cur->item->getTitle();
        cur = cur->next;
        i++;
    }

    return "";
}

/* ================= Borrowed ================= */

void Library::listBorrowed(std::ostream& os) const
{
    BorrowNode* cur = borrowedHead;

    while (cur) {
        os << cur->title << "\n";
        cur = cur->next;
    }
}

void Library::listBorrowedNumbered(std::ostream& os) const
{
    BorrowNode* cur = borrowedHead;
    int i = 1;

    while (cur) {
        os << i++ << ") " << cur->title << "\n";
        cur = cur->next;
    }
}

std::string Library::getBorrowedTitleByIndex(int index) const
{
    if (index <= 0) return "";

    BorrowNode* cur = borrowedHead;
    int i = 1;

    while (cur) {
        if (i == index)
            return cur->title;

        cur = cur->next;
        i++;
    }

    return "";
}

/* ================= Tasks ================= */

void Library::pushTask(Task* task)
{
    taskTop = new TaskNode(task, taskTop);
    taskCount++;
}

Task* Library::peekTask() const
{
    if (!taskTop) return nullptr;
    return taskTop->task;
}

Task* Library::popTask()
{
    if (!taskTop) return nullptr;

    TaskNode* node = taskTop;
    taskTop = node->next;

    Task* t = node->task;
    delete node;

    taskCount--;
    return t;
}

bool Library::processNextTask(std::ostream& log)
{
    Task* t = popTask();
    if (!t) return false;

    bool ok = t->execute(*this, log);
    delete t;

    return ok;
}

void Library::listTasks(std::ostream& os) const
{
    TaskNode* cur = taskTop;

    while (cur) {
        cur->task->display(os);
        os << "\n";
        cur = cur->next;
    }
}