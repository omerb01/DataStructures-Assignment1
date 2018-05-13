//
// Created by Omer on 09/05/2018.
//

#include "library1.h"
#include "Oasis.h"

#define GENERIC_OUTPUT($$command$$) \
if(DS == nullptr) return INVALID_INPUT; \
try { \
$$command$$; \
return SUCCESS; \
} \
catch (OasisInvalidInput &e) { \
return INVALID_INPUT; \
} \
catch (std::bad_alloc &e) { \
return ALLOCATION_ERROR; \
} \
catch (OasisFailure &e) { \
return FAILURE; \
}

void *init() {
    Oasis *DS = new Oasis();
    return (void *) DS;
}

StatusType addPlayer(void *DS, int playerID, int initialCoins) {
    GENERIC_OUTPUT(((Oasis *) DS)->addPlayer(playerID, initialCoins));
}

StatusType addClan(void *DS, int clanID) {
    GENERIC_OUTPUT(((Oasis *) DS)->addClan(clanID));
}

StatusType joinClan(void *DS, int playerID, int clanID) {
    GENERIC_OUTPUT(((Oasis *) DS)->joinClan(playerID, clanID));
}

StatusType getBestPlayer(void *DS, int clanID, int *playerID) {
    if(playerID == nullptr) return INVALID_INPUT;
    GENERIC_OUTPUT(*playerID = ((Oasis *) DS)->getBestPlayer(clanID));
}

StatusType completeChallange(void *DS, int playerID, int coins) {
    GENERIC_OUTPUT(((Oasis *) DS)->completeChallenge(playerID, coins));
}

StatusType getScoreboard(void *DS, int clanID, int **players, int *numOfPlayers) {
    GENERIC_OUTPUT(((Oasis *) DS)->getScoreboard(clanID, players, numOfPlayers));
}

StatusType uniteClans(void *DS, int clanID1, int clanID2) {
    GENERIC_OUTPUT(((Oasis *) DS)->uniteClans(clanID1, clanID2));
}

void quit(void** DS) {
    if(DS == nullptr) return;
    if(*DS == nullptr) return;
    delete (Oasis*)(*DS);
}