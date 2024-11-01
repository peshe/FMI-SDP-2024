#include <iostream>
#include <queue>
#include <string>

struct Player {
    std::size_t id;
    std::size_t saveCards;

    Player(std::size_t id) {
        this->id = id;
        this->saveCards = 0;
    }
};

unsigned int
kittens(const std::string cards, size_t players) {
    std::queue<Player> playersQueue;
    std::queue<char> cardsQueue;

    // Init players
    for (std::size_t i = 1; i <= players; ++i) {
        playersQueue.push(Player(i));
    }

    // Init cards
    for (std::size_t i = 0; i < cards.length(); ++i) {
        cardsQueue.push(cards[i]);
    }

    while (playersQueue.size() > 1) {
        char currentCard = cardsQueue.front();
        cardsQueue.pop();

        Player currentPlayer = playersQueue.front();
        playersQueue.pop();

        switch (currentCard) {
            case 'B': {
                if (currentPlayer.saveCards > 0) {
                    currentPlayer.saveCards -= 1;
                    cardsQueue.push(currentCard);
                    break;
                } else {
                    continue;
                }
            }
            case 'S': {
                currentPlayer.saveCards += 1;
                break;
            }
        }

        playersQueue.push(currentPlayer);
    }

    return playersQueue.front().id;
}
