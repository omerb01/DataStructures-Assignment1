//
// Created by Omer on 07/05/2018.
//

#ifndef DATASTRUCTURES_HW1_OASIS_H
#define DATASTRUCTURES_HW1_OASIS_H

#include "AVLTree.h"

class Player;
class Clan;

class DoubleKey {
    int key1;
    int key2;

public:

    DoubleKey() {
        key1 = -1;
        key2 = -1;
    }

    DoubleKey(int key1, int key2) {
        this->key1 = key1;
        this->key2 = key2;
    }

    bool operator==(const DoubleKey &key);

    bool operator!=(const DoubleKey &key);

    bool operator<(const DoubleKey &key);

    bool operator<=(const DoubleKey &key);

    bool operator>(const DoubleKey &key);

    bool operator>=(const DoubleKey &key);
};

class Clan {
public:

    int id;
    Player *best_player;
    int members_size;
    AVLTree<Player *, DoubleKey> members_coins;

    Clan() {
        id = -1;
        best_player = nullptr;
        members_size = -1;
    };

    explicit Clan(int id) {
        this->id = id;
        best_player = nullptr;
        members_size = 0;
    }
};

class Player {
public:

    int id;
    Clan* clan;
    int coins;
    int challenges;

    Player() {
        id = -1;
        clan = nullptr;
        coins = -1;
        challenges = -1;
    }

    explicit Player(int id, int coins = 0) {
        this->id = id;
        clan = nullptr;
        this->coins = coins;
        challenges = 0;
    }
};

class Oasis {
    AVLTree<Player, int> players;
    AVLTree<Clan, int> clans;
    Player *best_player;
    AVLTree<Player *, DoubleKey> players_coins;

public:
    Oasis() {
        best_player = nullptr;
    }

    Oasis(const Oasis &oasis) = delete;

    Oasis &operator=(const Oasis &oasis) = delete;

    void addPlayer(int playerID, int initialCoins); // ILYA

    void addClan(int clanID);

    void joinClan(int playerID, int clanID); // ILYA

    int getBestPlayer(int clanID);

    void completeChallenge(int playerID, int coins); // ILYA

    void getScoreboard(int clanID, int **players, int *numOfPlayers);

    void uniteClans(int clanID1, int clanID2); // ILYA
};

#endif //DATASTRUCTURES_HW1_OASIS_H
