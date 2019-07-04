//
//
// Created by pinsk on 5/8/2018.
//
#include<iostream>
using std::cout;
using std::endl;

#include "../testMacros.h"
#include "../library1.h"







bool testInit(){
    void* oasis = init();
    quit(&oasis);
    return true;
}

/* Description:   Adds a new Player.
 * Input:         DS - A pointer to the data structure.
 *                playerID - The ID of the Player to add.
 *				  initialCoins - The amount of coins the Player has.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, playerID <= 0, initialCoins < 0.
 *                FAILURE - If playerID is already in the DS.
 *                SUCCESS - Otherwise.
 */
StatusType addPlayer(void *DS, int playerID, int initialCoins);

bool testAddPlayer(){
    void* oasis = init();
    ASSERT_TRUE(addPlayer(oasis,1,0) == SUCCESS);
    ASSERT_TRUE(addPlayer(oasis,1,0) == FAILURE);
    ASSERT_TRUE(addPlayer(oasis,2,0) == SUCCESS);
    ASSERT_TRUE(addPlayer(oasis,2,0) == FAILURE);

    ASSERT_TRUE(addPlayer(oasis,0,0) == INVALID_INPUT);
    ASSERT_TRUE(addPlayer(oasis,-1,0) == INVALID_INPUT);

    ASSERT_TRUE(addPlayer(oasis,4,-1) == INVALID_INPUT);
    ASSERT_TRUE(addPlayer(oasis,6,-2) == INVALID_INPUT);

    ASSERT_TRUE(addPlayer(NULL,6,-2) == INVALID_INPUT);
    quit(&oasis);
    return true;
}


bool testAddClan(){
    void* oasis = init();
    ASSERT_TRUE(addClan(NULL,1)==INVALID_INPUT);
    ASSERT_TRUE(addClan(oasis,0)==INVALID_INPUT);
    ASSERT_TRUE(addClan(oasis,-1)==INVALID_INPUT);

    ASSERT_TRUE(addClan(oasis,1)==SUCCESS);
    ASSERT_TRUE(addClan(oasis,1)==FAILURE);
    ASSERT_TRUE(addClan(oasis,1)==FAILURE);


    ASSERT_TRUE(addClan(oasis,2)==SUCCESS);
    ASSERT_TRUE(addClan(oasis,3)==SUCCESS);

    // check i added
    ASSERT_TRUE(addClan(oasis,2)==FAILURE);
    ASSERT_TRUE(addClan(oasis,3)==FAILURE);
    quit(&oasis);
    return  true;
}



/* Description:   Moves Player playerID to Clan clanID.
 * Input:         DS - A pointer to the data structure.
 *                playerID - The ID of the Player.
 *				  clanID - The ID of the Clan to assign the Player to
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, playerID <= 0 or clanID <= 0.
 *                FAILURE - If playerID or clanID aren't in the DS, or if playID is already in a Clan.
 *                SUCCESS - Otherwise.
 */
StatusType joinClan(void *DS, int playerID, int clanID);

bool joinClan(){
    void* oasis = init();
    ASSERT_TRUE(joinClan(NULL,1,1)==INVALID_INPUT);
    ASSERT_TRUE(joinClan(oasis,0,1)==INVALID_INPUT);
    ASSERT_TRUE(joinClan(oasis,-1,1)==INVALID_INPUT);
    ASSERT_TRUE(joinClan(oasis,1,0)==INVALID_INPUT);
    ASSERT_TRUE(joinClan(oasis,1,-1)==INVALID_INPUT);

    ASSERT_TRUE(joinClan(oasis,1,1)==FAILURE);
    ASSERT_TRUE(joinClan(oasis,1,2)==FAILURE);
    quit(&oasis);
    return true;
}







bool testGetScoreBoard(){
    void* oasis = init();


    int x=5;
    int* scoreboard = &x;
    int num_players=0;
    ASSERT_TRUE(getScoreboard(oasis, 5, &scoreboard,&num_players)==FAILURE);
    addPlayer(oasis,1,1);
    addPlayer(oasis,2,2);
    addPlayer(oasis,3,3);
    ASSERT_TRUE(getScoreboard(oasis, -5, &scoreboard,&num_players)==SUCCESS);
   ASSERT_TRUE(scoreboard[0]==3 && scoreboard[1] == 2 && scoreboard[2] == 1);
    free(scoreboard);
    ASSERT_TRUE(getScoreboard(oasis, 5, NULL,&num_players)==INVALID_INPUT);
    ASSERT_TRUE(getScoreboard(NULL, 5, &scoreboard,&num_players)==INVALID_INPUT);
    ASSERT_TRUE(getScoreboard(oasis, 5, &scoreboard,NULL)==INVALID_INPUT);

    ASSERT_TRUE(getScoreboard(oasis, 5, &scoreboard,&num_players)==FAILURE);

    ASSERT_TRUE(addClan(oasis,1)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,1,1)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,3,1)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,2,1)==SUCCESS);
    scoreboard = &x;
    ASSERT_TRUE(getScoreboard(oasis, 1, &scoreboard,&num_players)==SUCCESS);
    ASSERT_TRUE(num_players==3);
    ASSERT_TRUE(scoreboard[0]==3 && scoreboard[1]==2 && scoreboard[2]==1);

    free(scoreboard);
    addPlayer(oasis,4,1);
    addPlayer(oasis,5,2);
    addPlayer(oasis,6,3);
    ASSERT_TRUE(addClan(oasis,2)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,4,2)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,5,2)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,6,2)==SUCCESS);
    scoreboard = &x;
    ASSERT_TRUE(getScoreboard(oasis, 2, &scoreboard,&num_players)==SUCCESS);
    ASSERT_TRUE(num_players==3);
    ASSERT_TRUE(scoreboard[0]==6 && scoreboard[1]==5 && scoreboard[2]==4);
    free(scoreboard);

    addPlayer(oasis,7,6);
    addPlayer(oasis,8,5);
    addPlayer(oasis,9,5);
    addPlayer(oasis,10,10);
    addPlayer(oasis,11,10);
    ASSERT_TRUE(joinClan(oasis,10,2)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,11,2)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,9,2)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,8,2)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,7,2)==SUCCESS);

    ASSERT_TRUE(getScoreboard(oasis, 2, &scoreboard,&num_players)==SUCCESS);
    ASSERT_TRUE(num_players==8);
    ASSERT_TRUE( scoreboard[0]==10 && scoreboard[1]==11 && scoreboard[2]==7 && scoreboard[3] == 8  && scoreboard[4] == 9
                 && scoreboard[5]== 6  && scoreboard[6] == 5   && scoreboard[7] == 4 );

    free(scoreboard);

    ASSERT_TRUE(getScoreboard(oasis, -2, &scoreboard,&num_players)==SUCCESS)
    ASSERT_TRUE(num_players==11);
    ASSERT_TRUE( scoreboard[0]==10 && scoreboard[1]==11 && scoreboard[2]==7 && scoreboard[3] == 8  && scoreboard[4] == 9
                 && scoreboard[5]== 3  && scoreboard[6] == 6  && scoreboard[7] == 2  && scoreboard[8] == 5
                 && scoreboard[9] == 1 && scoreboard[10] == 4);


    free(scoreboard);
    quit(&oasis);

    return true;
}



/* Description:   Adds coins to playerID
* Input:         DS - A pointer to the data structure.
*                playerID - The Player that has completed a challange
*                coins - The amount of coins playerID received for completing the challange
* Output:        None.
* Return Values: INVALID_INPUT - If DS==NULL, or if playerID <= 0, or if coins <= 0.
*                FAILURE - if playerID > 0 and playerID doesn't exist in the DS
*                SUCCESS - Otherwise.
*/
StatusType completeChallange(void *DS, int playerID, int coins);

bool completeChallange(){
    void* oasis = init();

    ASSERT_TRUE(completeChallange(NULL, 1, 1) == INVALID_INPUT);
    ASSERT_TRUE(completeChallange(oasis, 0, 1) == INVALID_INPUT);
    ASSERT_TRUE(completeChallange(oasis, 1, 0) == INVALID_INPUT);
    ASSERT_TRUE(completeChallange(oasis, 1, 1) == FAILURE);

    addPlayer(oasis,1,1);
    addPlayer(oasis,2,2);
    addPlayer(oasis,3,3);
    ASSERT_TRUE(addClan(oasis,1)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,1,1)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,3,1)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,2,1)==SUCCESS);
    ASSERT_TRUE(completeChallange(oasis, 4, 1) == FAILURE);
    ASSERT_TRUE(completeChallange(oasis, 1, 2) == SUCCESS);

    int x=0;
    int* scoreboard = &x;
    int num_players=0;
    ASSERT_TRUE(getScoreboard(oasis, 1, &scoreboard,&num_players)==SUCCESS);
    ASSERT_TRUE(num_players==3);
    ASSERT_TRUE(scoreboard[0]==1 && scoreboard[1]==3 && scoreboard[2]==2);


    free(scoreboard);
    ASSERT_TRUE(completeChallange(oasis, 2, 4) == SUCCESS);
    ASSERT_TRUE(getScoreboard(oasis, 1, &scoreboard,&num_players)==SUCCESS);
    ASSERT_TRUE(num_players==3);
    ASSERT_TRUE(scoreboard[0]==2 && scoreboard[1]==1 && scoreboard[2]==3);
    free(scoreboard);
    quit(&oasis);
    return true;
}


/* Description:   Returns the Player that has completed the most challanges in clanID
 * 			      If clanID < 0, returns the Player that has completed the most challanges in the entire DS.
 * Input:         DS - A pointer to the data structure.
 *                clanID - The Clan that we would like to get the data for.
 * Output:        playerID - A pointer to a variable that should be updated to the ID of the Player with the most completed challanges.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, or if playerID == NULL, or if clanID == 0.
 *                FAILURE - If clanID > 0 and clanID doesn't exist in the DS
 *                SUCCESS - Otherwise.
 */
StatusType getBestPlayer(void *DS, int clanID, int *playerID);



bool testBestPlayer(){
    void* oasis = init();
    int x=0;
    ASSERT_TRUE(getBestPlayer(oasis, 1, &x)==FAILURE);
    ASSERT_TRUE(getBestPlayer(NULL, 1, &x)==INVALID_INPUT);
    ASSERT_TRUE(getBestPlayer(oasis, 1, NULL)==INVALID_INPUT);

    addPlayer(oasis,1,1);
    addPlayer(oasis,2,2);
    addPlayer(oasis,3,3);
    ASSERT_TRUE(addClan(oasis,1)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,1,1)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,3,1)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,2,1)==SUCCESS);
    ASSERT_TRUE(getBestPlayer(oasis, 1, &x) == SUCCESS);
    ASSERT_TRUE(x==1);

    //addd another clan and players
    addPlayer(oasis,4,4);
    addPlayer(oasis,5,5);
    addPlayer(oasis,6,6);
    ASSERT_TRUE(addClan(oasis,2)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,4,2)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,5,2)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,6,2)==SUCCESS);
    ASSERT_TRUE(getBestPlayer(oasis, 2, &x) == SUCCESS);
    ASSERT_TRUE(x==4);

    ASSERT_TRUE(getBestPlayer(oasis, -1, &x) == SUCCESS);
    ASSERT_TRUE(x==1);

    ASSERT_TRUE(completeChallange(oasis, 3, 1 )== SUCCESS);
    ASSERT_TRUE(getBestPlayer(oasis, 1, &x) == SUCCESS);
    ASSERT_TRUE(x==3);

    ASSERT_TRUE(getBestPlayer(oasis, -1, &x) == SUCCESS);
    ASSERT_TRUE(x==3);

    ASSERT_TRUE(completeChallange(oasis, 5, 1 )== SUCCESS);
    ASSERT_TRUE(getBestPlayer(oasis, 2, &x) == SUCCESS);
    ASSERT_TRUE(x==5);

    ASSERT_TRUE(getBestPlayer(oasis, -1, &x) == SUCCESS);
    ASSERT_TRUE(x==3);

    ASSERT_TRUE(completeChallange(oasis, 4, 3 )== SUCCESS);
    ASSERT_TRUE(completeChallange(oasis, 4, 3 )== SUCCESS);
    ASSERT_TRUE(getBestPlayer(oasis, 2, &x) == SUCCESS);
    ASSERT_TRUE(x==4);

    ASSERT_TRUE(getBestPlayer(oasis, -1, &x) == SUCCESS);
    ASSERT_TRUE(x==4);

    quit(&oasis);
    return true;
}



/* Description:   Joins two clans, leaving the players with no comlpeted challanges out of the new Clan.
 * Input:         DS - A pointer to the data structure.
 *                clanID1 - ID of the first Clan.
 *		          clanID2 - ID of the second Clan.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, or if clanID1<=0, or if clanID2<=0
 *                FAILURE - If clanID1 or clanID2 are not in the DS.
 *                SUCCESS - Otherwise.
 */
StatusType uniteClans(void *DS, int clanID1, int clanID2);

bool testUniteClans(){
    void* oasis = init();
    ASSERT_TRUE(uniteClans(oasis, 0,1) == INVALID_INPUT);
    ASSERT_TRUE(uniteClans(oasis, 1,0) == INVALID_INPUT);
    ASSERT_TRUE(uniteClans(NULL, 1,0) == INVALID_INPUT);
    ASSERT_TRUE(uniteClans(oasis, 1,-1) == INVALID_INPUT);


    addPlayer(oasis,1,1);
    addPlayer(oasis,2,2);
    addPlayer(oasis,3,3);
    ASSERT_TRUE(addClan(oasis,1)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,1,1)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,3,1)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,2,1)==SUCCESS);

    int x=-5;
    //addd another clan and players
    addPlayer(oasis,4,4);
    addPlayer(oasis,5,5);
    addPlayer(oasis,6,6);
    addPlayer(oasis,7,7);
    ASSERT_TRUE(addClan(oasis,2)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,4,2)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,5,2)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,6,2)==SUCCESS);
    ASSERT_TRUE(uniteClans(oasis, 1,2) == SUCCESS);
    ASSERT_TRUE(getBestPlayer(oasis, 1, &x) == SUCCESS);
    ASSERT_TRUE(x==-1);


    ASSERT_TRUE(joinClan(oasis,7,2)==FAILURE);
    ASSERT_TRUE(joinClan(oasis,7,1)==SUCCESS);

    addPlayer(oasis,10,10);
    addPlayer(oasis,11,11);
    addPlayer(oasis,12,12);

    ASSERT_TRUE(addClan(oasis,2)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,10,2)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,11,2)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,12,2)==SUCCESS);


    addPlayer(oasis,13,4);
    addPlayer(oasis,14,5);
    addPlayer(oasis,15,6);
    addPlayer(oasis,16,7);
    ASSERT_TRUE(addClan(oasis,3)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,13,3)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,14,3)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,15,3)==SUCCESS);
    ASSERT_TRUE(joinClan(oasis,16,3)==SUCCESS);

    ASSERT_TRUE(completeChallange(oasis, 11, 3 )== SUCCESS);
    ASSERT_TRUE(completeChallange(oasis, 13, 3 )== SUCCESS);
    ASSERT_TRUE(uniteClans(oasis, 2,3) == SUCCESS);
    ASSERT_TRUE(getBestPlayer(oasis, 3, &x) == SUCCESS);
    ASSERT_TRUE(x==11);


    int* scoreboard = &x;
    int num_players=0;
    ASSERT_TRUE(getScoreboard(oasis, 3, &scoreboard,&num_players)==SUCCESS);
    ASSERT_TRUE(num_players==2);
    free(scoreboard);
    quit(&oasis);
    return true;
}


/* Description:   Quits and deletes the database.
 *                DS should be set to NULL.
 * Input:         DS - A pointer to the data structure.
 * Output:        None.
 * Return Values: None.
 */
void quit(void** DS);

bool testQuit(){
    void* oasis = init();
    quit(&oasis);
    return true;
}


int main() {

    RUN_TEST(testInit)
    RUN_TEST(testAddPlayer);
    RUN_TEST(testAddClan);
    RUN_TEST(joinClan);
    RUN_TEST(testGetScoreBoard);
    RUN_TEST(testBestPlayer);
    RUN_TEST(completeChallange);
    RUN_TEST(testUniteClans);
    RUN_TEST(testQuit);

}
