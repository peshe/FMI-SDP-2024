#include <cassert>
#include <queue>
#include <string>
#include <vector>


unsigned int kittens(const std::string& cards, unsigned int players) {
	assert(players > 0);

	std::queue<char> nextCards;
	for (char card : cards) {
		nextCards.push(card);
	}

	std::vector<bool> defeated(players, false);
	unsigned nDefeated = 0;

	std::vector<unsigned> defuses(players, 0);

	unsigned currentPlayer = 0;
	while (nDefeated < players - 1) {
		if (!defeated[currentPlayer]) {
			char nextCard = nextCards.front();
			nextCards.pop();

			switch (nextCard) {
			case 'S':
				++defuses[currentPlayer];
				break;
			case 'B':
				if (defuses[currentPlayer] == 0) {
					defeated[currentPlayer] = true;
					++nDefeated;
				}
				else {
					--defuses[currentPlayer];
					nextCards.push(nextCard);
				}
				break;
			case 'O':
				break;
			default:
				assert(false);
			}
		}
		currentPlayer = (currentPlayer + 1) % players;
	}

	for (unsigned player = 0; player < players; ++player) {
		if (!defeated[player]) {
			return player + 1;
		}
	}
}

int main() {
	assert(kittens("BB", 3) == 3);
	assert(kittens("SSBB", 3) == 2);
	assert(kittens("SSBBOOOOOOOSBOOOOOOOOOSB", 5) == 1);
	assert(kittens("SOOSBBOOOOSOOOSBOSOOBOSOSOOBOSOSOOB", 7) == 3);

	return 0;
}
