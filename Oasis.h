//
// Created by Omer on 07/05/2018.
//

#ifndef DATASTRUCTURES_HW1_OASIS_H
#define DATASTRUCTURES_HW1_OASIS_H

#include "AVLTree.h"

class DoubleKey {
    int key1;
    int key2;

public:

    DoubleKey(int key1, int key2) {
        this->key1 = key1;
        this->key2 = key2;
    }

    DoubleKey &operator=(const DoubleKey &key) = delete;

    bool operator==(const DoubleKey &key);

    bool operator!=(const DoubleKey &key);

    bool operator<(const DoubleKey &key);

    bool operator<=(const DoubleKey &key);

    bool operator>(const DoubleKey &key);

    bool operator>=(const DoubleKey &key);
};

class Oasis {
    class Player {
        int id;
        int clan;
        int coins;
        int challenges;

    public:

        Player() {
            id = -1;
            clan = -1;
            coins = -1;
            challenges = -1;
        }

        Player &operator=(const Player &player) = delete;
    };

    class Clan {
        int id;
        Player *best_player;
        int members_size;
        AVLTree<Player *, DoubleKey> members_coins;

    public:

        Clan() {
            id = -1;
            best_player = nullptr;
            members_size = -1;
        };

        Clan &operator=(const Clan &player) = delete;
    };

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

    void addPlayer(int playerID, int initialCoins);

    void addClan(int clanID);

    void joinClan(int playerID, int clanID);

    int getBestPlayer(int clanID, int playerID);

    void completeChallenge(int playerID, int coins);

    void getScoreboard(int clanID, int **players, int *numOfPlayers);

    void uniteClans(int clanID1, int clanID2);
};

#endif //DATASTRUCTURES_HW1_OASIS_H
