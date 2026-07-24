#include "LibrarySystem.h"
#include "Library.h"
#include <utility>

/* ================= LIBRARY ITEMS ================= */

LibraryItem::LibraryItem(std::string t, int copies)
    : title(std::move(t)), totalCopies(copies), availableCopies(copies)
{}

bool LibraryItem::isAvailable() const
{
  return availableCopies > 0;
}

void LibraryItem::borrowCopy()
{
    if (availableCopies > 0) availableCopies--;
}

void LibraryItem::returnCopy()
{
    if (availableCopies < totalCopies) availableCopies++;
}

std::string LibraryItem::getTitle() const
{
  return title;
}

LibraryItem::~LibraryItem() = default;

Book::Book(std::string t, int copies) : LibraryItem(std::move(t), copies) {}

void Book::display(std::ostream& os) const
{
    os << "[Book] " << title << " (" << availableCopies << "/" << totalCopies << " available)";
}

int Book::getBorrowDuration() const { return 14; }

double Book::calculateFine(int daysLate) const { return daysLate <= 0 ? 0.0 : 1.0 * daysLate; }

Book::~Book() = default;

Journal::Journal(std::string t, int copies) : LibraryItem(std::move(t), copies) {}

void Journal::display(std::ostream& os) const
{
    os << "[Journal] " << title << " (" << availableCopies << "/" << totalCopies << " available)";
}

int Journal::getBorrowDuration() const { return 7; }

double Journal::calculateFine(int daysLate) const { return daysLate <= 0 ? 0.0 : 2.0 * daysLate; }

Journal::~Journal() = default;

Magazine::Magazine(std::string t, int copies) : LibraryItem(std::move(t), copies) {}

void Magazine::display(std::ostream& os) const
{
    os << "[Magazine] " << title << " (" << availableCopies << "/" << totalCopies << " available)";
}

int Magazine::getBorrowDuration() const { return 3; }

double Magazine::calculateFine(int daysLate) const { return daysLate <= 0 ? 0.0 : 0.5 * daysLate; }

Magazine::~Magazine() = default;

/* ================= TASKS ================= */

Task::~Task() = default;

BorrowTask::BorrowTask(std::string t) : title(std::move(t)) {}

void BorrowTask::display(std::ostream& os) const
{
  os << "Borrow: " << title; // FIXed
}

int BorrowTask::getPriority() const { return 1; }

bool BorrowTask::execute(Library& lib, std::ostream& log) const {
    bool ok = lib.borrowItem(title);
  log << (ok ? "Borrowed: " : "Borrow failed: ") << title << "\n";
  return ok;
}

ReturnTask::ReturnTask(std::string t) : title(std::move(t)) {}

void ReturnTask::display(std::ostream& os) const
{
    os << "Return: " << title;
}

int ReturnTask::getPriority() const { return 2; }
bool ReturnTask::execute(Library& lib, std::ostream& log) const {
    bool ok = lib.returnItem(title);
  log << (ok ? "Returned: " : "Return failed: ") << title << "\n";
  return ok;
}

PersonalTask::PersonalTask(std::string n) : note(std::move(n)) {}

void PersonalTask::display(std::ostream& os) const
{
    os << "Personal: " << note;
}

int PersonalTask::getPriority() const { return 3; }

bool PersonalTask::execute(Library&, std::ostream& log) const {
    log << "Personal task noted: " << note << "\n";
    return true;
}
