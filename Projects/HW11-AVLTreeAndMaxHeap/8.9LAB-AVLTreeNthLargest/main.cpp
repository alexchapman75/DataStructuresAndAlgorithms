#include <iostream>
#include <vector>
#include <string>
#include <sstream>

// Card struct representing a playing card
struct Card {
    char rank; // '2'-'9', 'T', 'J', 'Q', 'K', 'A'
    char suit; // 'H', 'D', 'C', 'S'

    Card(char r, char s) : rank(r), suit(s) {}
    Card() : rank('2'), suit('H') {}
};

// Helper function to get rank value, Ace highest
int rankValue(char rank) {
    if(rank >= '2' && rank <= '9') return rank - '0'; 
    if(rank == 'T') return 10;
    if(rank == 'J') return 11;
    if(rank == 'Q') return 12;
    if(rank == 'K') return 13;
    if(rank == 'A') return 14;
    return 0; // stub
}

// Compare two cards: return true if c1 > c2 (for max-heap)
bool cardGreater(const Card& c1, const Card& c2) {

    return rankValue(c1.rank) > rankValue(c2.rank);
    return false; // stub
}

// Heapify function for max-heap property
void heapify(std::vector<Card>& cards, int n, int i) {

    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Check left child
    if (left < n && cardGreater(cards[left], cards[largest])) {
        largest = left;
    }

    // Check right child
    if (right < n && cardGreater(cards[right], cards[largest])) {
        largest = right;
    }

    // If largest is not root, swap and continue heapifying
    if (largest != i) {
        std::swap(cards[i], cards[largest]);
        heapify(cards, n, largest);
    }

}

// Build max-heap from array of cards
void buildMaxHeap(std::vector<Card>& cards) {

    int n = cards.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(cards, n, i);
    }

}

// Print the heap as specified
void printHeap(const std::vector<Card>& cards) {

    for (size_t i = 0; i < cards.size(); i++) {
        std::cout << cards[i].rank << cards[i].suit;
        if (i != cards.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

int main() {
    std::string line;
    std::getline(std::cin, line);
    std::istringstream iss(line);
    std::vector<Card> cards;
    std::string token;
    while (iss >> token) {
        if (token.length() == 2) {
            char rank = token[0];
            char suit = token[1];
            cards.push_back(Card(rank, suit));
        }
    }
    buildMaxHeap(cards);
    printHeap(cards);
    return 0;
}
