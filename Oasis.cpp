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
    if (best_player == nullptr) {
        best_player = &p;
    } else if (best_player->challenges == 0) {
        if (best_player->id > p.id) best_player = &p;
    }
}

void Oasis::addClan(int clanID) {
    if (clanID <= 0) throw OasisInvalidInput();
    Clan clan(clanID);
    if (!clans.insert(clan, clanID)) throw OasisFailure();
}

void Oasis::joinClan(int playerID, int clanID) {
    if (playerID <= 0 || clanID <= 0) {
        throw OasisInvalidInput();
    }
    try {
        Player &player = players.find(playerID);
        Clan &players_clan = clans.find(clanID);

        if (player.clan != nullptr) {
            throw OasisFailure(); //player is already in a different clan
        }

        DoubleKey player_key(player.coins, player.id);
        players_clan.members_coins.insert(&player, player_key);
        players_clan.members_size++;

        if (players_clan.best_player == nullptr) {
            players_clan.best_player = &player;
        } else if (player.challenges > players_clan.best_player->challenges) {
            players_clan.best_player = &player;
        } else if (player.challenges == players_clan.best_player->challenges) {
            if (player.id < players_clan.best_player->id) players_clan.best_player = &player;
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
            if (clan.members_size == 0) {
                return -1;
            } else if (clan.best_player == nullptr) {
                throw OasisFailure();
            }
            return clan.best_player->id;
        }
        catch (AVLElementNotFound &e) {
            throw OasisFailure();
        }
    } else { // clanID < 0
        if (players.getTreeSize() == 0) {
            return -1;
        } else if (best_player == nullptr) {
            throw OasisFailure();
        }
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
            } else if (player.challenges == players_clan.best_player->challenges) {
                if (player.id < players_clan.best_player->id) players_clan.best_player = &player;
            }

            if (player.challenges > best_player->challenges) {
                best_player = &player;
            } else if (player.challenges == best_player->challenges) {
                if (player.id < best_player->id) best_player = &player;
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
            } else if (player.challenges == best_player->challenges) {
                if (player.id < best_player->id) best_player = &player;
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
            Clan &clan = clans.find(clanID);
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
                (*players)[i] = members_coins[size - i - 1]->id;
            }
            delete[] members_coins;
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
            (*players)[i] = players_coins[size - i - 1]->id;
        }
        delete[] players_coins;
    }
}

class FilterChallenges {
    Clan *clan;

public:
    explicit FilterChallenges(Clan *clan) {
        this->clan = clan;
    }

    bool operator()(Player *player) {
        if (player->challenges == 0) {
            player->clan = nullptr;
            return false;
        }
        player->clan = this->clan;
        return true;
    }
};

void Oasis::uniteClans(int clanID1, int clanID2) {
    if (clanID1 <= 0 || clanID2 <= 0 || clanID2 == clanID1) {
        throw OasisInvalidInput();
    }
    try {
        Clan &clan1 = clans.find(clanID1);
        Clan &clan2 = clans.find(clanID2);
        Clan *new_merged_clan = nullptr;
        Clan *clan_to_remove = nullptr;
        if (clan1.members_size > clan2.members_size) {
            new_merged_clan = &clan1;
            clan_to_remove = &clan2;
        } else if (clan1.members_size == clan2.members_size) {
            if (clan1.id > clan2.id) {
                new_merged_clan = &clan2;
                clan_to_remove = &clan1;
            } else {
                new_merged_clan = &clan1;
                clan_to_remove = &clan2;
            }
        } else {
            new_merged_clan = &clan2;
            clan_to_remove = &clan1;
        }

        AVLTree<Player *, DoubleKey> tree = clan1.members_coins.merge(clan1.members_coins,
                                                                      clan2.members_coins,
                                                                      FilterChallenges(
                                                                              new_merged_clan));

        new_merged_clan->members_size = tree.getTreeSize();

        if (clan_to_remove->best_player != nullptr) {
            if (new_merged_clan->best_player != nullptr) {
                if (clan1.best_player->challenges == 0 && clan2.best_player->challenges == 0) {
                    new_merged_clan->best_player = nullptr;
                } else {
                    if (clan1.best_player->challenges > clan2.best_player->challenges) {
                        new_merged_clan->best_player = clan1.best_player;
                    } else if (clan1.best_player->challenges == clan2.best_player->challenges) {
                        if (clan1.best_player->id > clan2.best_player->id) {
                            new_merged_clan->best_player = clan2.best_player;
                        } else {
                            new_merged_clan->best_player = clan1.best_player;
                        }
                    } else {
                        new_merged_clan->best_player = clan2.best_player;
                    }
                }
            } else {
                new_merged_clan->best_player = clan_to_remove->best_player;
            }
        } else {
            if (new_merged_clan->best_player != nullptr) {
                if (new_merged_clan->best_player->challenges == 0)
                    new_merged_clan->best_player = nullptr;
            }
        }

        new_merged_clan->members_coins = tree;

        clans.remove(clan_to_remove->id);
    } catch (AVLTreeException &e) {
        throw OasisFailure();
    }


}