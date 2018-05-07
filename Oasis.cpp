//
// Created by Omer on 07/05/2018.
//

#include "Oasis.h"
#include "exceptions.h"

bool DoubleKey::operator==(const DoubleKey &key) {
    return key1 == key.key1 && key2 == key.key2;
}

bool DoubleKey::operator!=(const DoubleKey &key) {
    return !(*this == key);
}

bool DoubleKey::operator<(const DoubleKey &key) {
    if (key1 < key.key1) return true;
    if (key1 > key.key1) return false;
    return key2 > key.key2;
}

bool DoubleKey::operator<=(const DoubleKey &key) {
    return *this < key || *this == key;
}

bool DoubleKey::operator>(const DoubleKey &key) {
    return !(*this < key) && *this != key;
}

bool DoubleKey::operator>=(const DoubleKey &key) {
    return !(*this < key);
}

void Oasis::addClan(int clanID) {
    if (clanID <= 0) throw OasisInvalidInput();
    Clan clan(clanID);
    if (!clans.insert(clan, clanID)) throw OasisFailure();
}

int Oasis::getBestPlayer(int clanID) {
    if (clanID == 0) throw OasisInvalidInput();
    else if (clanID > 0) {
        try {
            Clan clan = clans.find(clanID);
            if (clan.best_player == nullptr) throw OasisFailure();
            return clan.best_player->id;
        }
        catch (AVLElementNotFound &e) {
            throw OasisFailure();
        }
    } else { // clanID < 0
        if (best_player == nullptr) throw OasisFailure();
        return best_player->id;
    }
}

void Oasis::getScoreboard(int clanID, int **players, int *numOfPlayers) {
    if (clanID == 0 || players == nullptr || numOfPlayers == nullptr) throw OasisInvalidInput();
    else if (clanID > 0) {
        try {
            Clan clan = clans.find(clanID);
            Player **members_coins = clan.members_coins.inOrderToArray();
            if (members_coins == nullptr) {
                *players = nullptr;
                *numOfPlayers = 0;
                return;
            }

            int size = clan.members_coins.getVerticesNumber();
            *numOfPlayers = size;
            *players = (int *) malloc(sizeof(int) * size);
            if(*players == nullptr) throw std::bad_alloc();
            for (int i = 0; i < size; i++) {
                (*players)[i] = members_coins[i]->id;
            }
            delete members_coins;
        }
        catch (AVLElementNotFound &e) {
            throw OasisFailure();
        }
    } else { // clanID < 0
        Player **players_coins = this->players_coins.inOrderToArray();
        if (players_coins == nullptr) {
            *players = nullptr;
            *numOfPlayers = 0;
            return;
        }

        int size = this->players_coins.getVerticesNumber();
        *numOfPlayers = size;
        *players = (int *) malloc(sizeof(int) * size);
        if(*players == nullptr) throw std::bad_alloc();
        for (int i = 0; i < size; i++) {
            (*players)[i] = players_coins[i]->id;
        }
        delete players_coins;
    }
}
