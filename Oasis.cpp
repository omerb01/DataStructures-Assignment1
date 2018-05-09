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

void Oasis::addPlayer(int playerID, int initialCoins) {
    if (playerID <= 0 || initialCoins < 0) {
        throw OasisInvalidInput();
    }
    Player new_player(playerID, initialCoins);
    DoubleKey new_key(initialCoins, playerID);
    bool result = players.insert(new_player, playerID);
    if (!result) {
        throw OasisFailure();
    }
    Player &p = players.find(playerID);
    players_coins.insert(&p, new_key);
}

void Oasis::addClan(int clanID) {
    if (clanID <= 0) throw OasisInvalidInput();
    Clan clan(clanID);
    if (!clans.insert(clan, clanID)) throw OasisFailure();
}

void Oasis::joinClan(int playerID, int clanID) {
    if (playerID <= 0 || clanID == 0) {
        throw OasisInvalidInput();
    }
    try {
        Player &player = players.find(playerID);
        Clan &players_clan = clans.find(clanID);

        if (player.clan == nullptr) {
            throw OasisFailure(); //player is already in a different clan
        }

        DoubleKey player_key(player.coins, player.id);
        players_clan.members_coins.insert(&player, player_key);
        players_clan.members_size++;

        if (player.challenges > players_clan.best_player->challenges) {
            players_clan.best_player = &player;
        }

        player.clan = &players_clan;

    } catch (AVLElementNotFound &e) {
        throw OasisFailure();
    }
}

int Oasis::getBestPlayer(int clanID) {
    if (clanID == 0) throw OasisInvalidInput();
    else if (clanID > 0) {
        try {
            Clan &clan = clans.find(clanID);
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

void Oasis::completeChallenge(int playerID, int coins) {
    if (playerID <= 0 || coins <= 0) {
        throw OasisInvalidInput();
    }

    try {
        Player &player = players.find(playerID);
        if (player.clan != nullptr) {
            Clan &players_clan = *player.clan;
            DoubleKey old_key(player.coins, player.id);
            players_clan.members_coins.remove(old_key);
            players_coins.remove(old_key);

            player.coins += coins;
            player.challenges += 1;

            DoubleKey new_key(player.coins, player.id);
            players_clan.members_coins.insert(&player, new_key);
            players_coins.insert(&player, new_key);

            if (player.challenges > players_clan.best_player->challenges) {
                players_clan.best_player = &player;
            }
            if (player.challenges > best_player->challenges) {
                best_player = &player;
            }
        } else {
            DoubleKey old_key(player.coins, player.id);
            players_coins.remove(old_key);

            player.coins += coins;
            player.challenges += 1;

            DoubleKey new_key(player.coins, player.id);
            players_coins.insert(&player, new_key);

            if (player.challenges > best_player->challenges) {
                best_player = &player;
            }
        }
    }
    catch (AVLElementNotFound &e) {
        throw OasisFailure();
    }
}

void Oasis::getScoreboard(int clanID, int **players, int *numOfPlayers) {
    if (clanID == 0 || players == nullptr || numOfPlayers == nullptr)
        throw OasisInvalidInput();
    else if (clanID > 0) {
        try {
            Clan& clan = clans.find(clanID);
            Player **members_coins = clan.members_coins.inOrderToArray();
            if (members_coins == nullptr) {
                *players = nullptr;
                *numOfPlayers = 0;
                return;
            }

            int size = clan.members_coins.getVerticesNumber();
            *numOfPlayers = size;
            *players = (int *) malloc(sizeof(int) * size);
            if (*players == nullptr) throw std::bad_alloc();
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
        if (*players == nullptr) throw std::bad_alloc();
        for (int i = 0; i < size; i++) {
            (*players)[i] = players_coins[i]->id;
        }
        delete players_coins;
    }
}

static void mergeClans(Clan *clan_s, Clan *clan_d) {
    clan_d->members_size += clan_s->members_size;
    clan_s->best_player->challenges > clan_d->best_player->challenges
    ? clan_d->best_player = clan_s->best_player : 0;
    AVLTree<Player *, DoubleKey> new_members_coins = clan_d->members_coins.merge(
            clan_s->members_coins, clan_d->members_coins);
    clans.remove(clan_s->id);
}

void Oasis::uniteClans(int clanID1, int clanID2) {
    if (clanID1 <= 0 || clanID2 <= 0 || clanID2 == clanID1) {
        throw OasisInvalidInput();
    }
    Clan& clan1 = clans.find(clanID1);
    Clan& clan2 = clans.find(clanID2);
    Player **clan1_p = clan1->members_coins.inOrderToArray();
    Player **clan2_p = clan2->members_coins.inOrderToArray();
    for (int i = 0; i < clan1->members_size; i++) {
        if (clan1_p[i]->challenges == 0) {
            clan1_p[i]->clan = -1;
            DoubleKey key_c1(clan1_p[i]->id, clan1_p[i]->coins);
            clan1->members_coins.remove(key_c1);
            clan1->members_size--;
        }
        if (clan2_p[i]->challenges == 0) {
            clan2_p[i]->clan = -1;
            DoubleKey key_c2(clan2_p[i]->id, clan2_p[i]->coins);
            clan2->members_coins.remove(key_c2);
            clan2->members_size--;
        }
    }
    if (clan1->members_size > clan2->members_size) {
        mergeClans(clan2, clan1);
    } else if (clan1->members_size < clan2->members_size) {
        mergeClans(clan1, clan2);
    } else {
        if (clan1->id < clan2->id) {
            mergeClans(clan2, clan1);
        } else {
            mergeClans(clan1, clan2);
        }
    }
    delete clan1_p;
    delete clan2_p;
}