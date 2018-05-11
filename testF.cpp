//
// Created by Ilya on 5/9/2018.
//

#include <iostream>
#include "library1.h"
#include <cassert>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define nullptr 0


void checkBadInputs(void* oasis, int the_challenger, int size, int* score_board){
    //for add player
    assert(addPlayer(oasis,1,-1)==INVALID_INPUT);
    assert(addPlayer(oasis,-5,1)==INVALID_INPUT);
    assert(addPlayer(NULL,10,15)==INVALID_INPUT);
    assert(addPlayer(NULL,-1,0)==INVALID_INPUT);
    //for add clan
    assert(addClan(NULL,777)==INVALID_INPUT);
    assert(addClan(oasis,0)==INVALID_INPUT);
    //for joinClan
    assert(joinClan(oasis,0,54)==INVALID_INPUT);
    assert(joinClan(oasis,204,0)==INVALID_INPUT);
    assert(joinClan(NULL,204,54)==INVALID_INPUT);
    //for getBestPlayer
    assert(getBestPlayer(oasis,0,&the_challenger)==INVALID_INPUT);
    assert(getBestPlayer(NULL,1,&the_challenger)==INVALID_INPUT);
    assert(getBestPlayer(oasis,1,NULL)==INVALID_INPUT);
    //for completeChallange(challenge***)
    assert(completeChallange(NULL,204,15)==INVALID_INPUT);
    assert(completeChallange(oasis,0,15)==INVALID_INPUT);
    assert(completeChallange(oasis,204,0)==INVALID_INPUT);
    //for getScoreboard
    assert(getScoreboard(NULL,222,&score_board,&size)==INVALID_INPUT);
    assert(getScoreboard(oasis,0,&score_board,&size)==INVALID_INPUT);
    assert(getScoreboard(oasis,222,NULL,&size)==INVALID_INPUT);
    assert(getScoreboard(oasis,222,&score_board,NULL)==INVALID_INPUT);
    //for uniteClans
    assert(uniteClans(oasis,0,1)==INVALID_INPUT);
    assert(uniteClans(oasis,1,1)==INVALID_INPUT);
    assert(uniteClans(oasis,1,-5)==INVALID_INPUT);
    assert(uniteClans(NULL,2,1)==INVALID_INPUT);
    //for quit
    void** tmp=NULL;
    ///void* temp=NULL;
    quit(tmp);
    //quit(&temp);
    std::cout<<"Passed bad input cases ;)"<<std::endl;
}

void checkAddPlayer(void* oasis,int the_challenger,int size,int* score_board){
    for(int i=0;i<50;i++){
        if(!i)
            assert(addPlayer(oasis,51,i)==SUCCESS);
        else
            assert(addPlayer(oasis,i,i)==SUCCESS);
    }
    for(int i=1;i<50;i++){
        assert(addPlayer(oasis,i,i*i)==FAILURE);
    }
    //assert(getBestPlayer(oasis,-1,&the_challenger)==SUCCESS); //TODO:clan ID =-1? WTF
    //assert(the_challenger==1);
    //assert(getScoreboard(oasis,-50,&score_board,&size)==SUCCESS);
    //assert(size==50);
    assert(score_board[0]==49);
    assert(score_board[49]==51);
    free(score_board);
    std::cout<<"Passed add player test 8)"<<std::endl;

}

void checkAddClan(void* oasis){
    for(int i=0;i<20;i++){
        if(!i)
            assert(addClan(oasis,21)==SUCCESS);
        else
            assert(addClan(oasis,i)==SUCCESS);
    }
    for(int i=1;i<20;i++){
        assert(addClan(oasis,i)==FAILURE);
    }
    std::cout<<"Passed add clan test >:("<<std::endl;
}

void checkJoinClan(void* oasis){
    for(int i=1,j=1;i<41;i++){
        if(i<11){
            assert(joinClan(oasis,i,j)==SUCCESS);
            j= i==10? 2: 1;
        }else if(i<21){
            assert(joinClan(oasis,i,j)==SUCCESS);
            j= i==20? 3: 2;
        }else if(i<31) {
            assert(joinClan(oasis, i, j) == SUCCESS);
            j = i == 30 ? 5 : 3;
        }else if(i<36) {
            assert(joinClan(oasis, i, j) == SUCCESS);
            j = i == 35 ? 4 : 5;
        } else
            assert(joinClan(oasis, i, j) == SUCCESS);
    }
    for(int i=40,j=1;i>0;i--,j++){
        assert(joinClan(oasis,i,j)==FAILURE);
    }
    std::cout<<"Passed join clan test :O"<<std::endl;
}

void checkCompleteChallange(void* oasis){
    for(int i=1;i<45;i++){
        if(i%2==0){
            for(int k=0; k<2; k++){
                assert(completeChallange(oasis,i,1)==SUCCESS);
            }
        }
        if(i%3==0){
            for(int k=0; k<3; k++){
                assert(completeChallange(oasis,i,1)==SUCCESS);
            }
        }
    }
    assert(completeChallange(oasis,52,1)==FAILURE); //player nor exist
    assert(completeChallange(oasis,47,2)==SUCCESS);
    std::cout<<"Passed complete challenge test :P"<<std::endl;
}

void checkGetBestPlayer(void* oasis,int the_challenger){
    assert(getBestPlayer(oasis,1,&the_challenger)==SUCCESS);
    assert(the_challenger==6);

    assert(getBestPlayer(oasis,2,&the_challenger)==SUCCESS);
    assert(the_challenger==12);

    assert(getBestPlayer(oasis,3,&the_challenger)==SUCCESS);
    assert(the_challenger==24);

    assert(getBestPlayer(oasis,4,&the_challenger)==SUCCESS);
    assert(the_challenger==36);

    assert(getBestPlayer(oasis,5,&the_challenger)==SUCCESS);
    assert(the_challenger==33);

    assert(getBestPlayer(oasis,100,&the_challenger)==FAILURE);

    std::cout<<"Passed best player test :D"<<std::endl;
}

void checkGetScoreboardFirst(void* oasis,int size, int* score_board){
    assert(getScoreboard(oasis,19,&score_board,&size)==SUCCESS);
    assert(size==0);
    assert(score_board==NULL);
    free(score_board);

    assert(getScoreboard(oasis,1,&score_board,&size)==SUCCESS);
    assert(size==10);
    assert(score_board[0]==9); //12 coins
    assert(score_board[1]==10); //12 coins
    assert(score_board[2]==6); //11 coins
    assert(score_board[3]==8); //10 coins
    assert(score_board[4]==7); //7 coins
    assert(score_board[5]==3); //6 coins
    assert(score_board[6]==4); //6 coins
    assert(score_board[7]==5); //5 coins
    assert(score_board[8]==2); //4 coins
    assert(score_board[9]==1); //1 coin
    free(score_board);

    assert(getScoreboard(oasis,2,&score_board,&size)==SUCCESS);
    assert(size==10);
    assert(score_board[0]==18);
    assert(score_board[1]==20);
    assert(score_board[2]==19);
    assert(score_board[3]==15);
    assert(score_board[4]==16);
    assert(score_board[5]==12);
    assert(score_board[6]==17);
    assert(score_board[7]==14);
    assert(score_board[8]==13);
    assert(score_board[9]==11);
    free(score_board);

    assert(getScoreboard(oasis,3,&score_board,&size)==SUCCESS);
    assert(size==10);
    assert(score_board[0]==30);
    assert(score_board[1]==27);
    assert(score_board[2]==28);
    assert(score_board[3]==24);
    assert(score_board[4]==29);
    assert(score_board[5]==26);
    assert(score_board[6]==25);
    assert(score_board[7]==21);
    assert(score_board[8]==22);
    assert(score_board[9]==23);
    free(score_board);

    assert(getScoreboard(oasis,4,&score_board,&size)==SUCCESS);
    assert(size==5);
    assert(score_board[0]==39);
    assert(score_board[1]==40);
    assert(score_board[2]==36);
    assert(score_board[3]==38);
    assert(score_board[4]==37);
    free(score_board);

    assert(getScoreboard(oasis,5,&score_board,&size)==SUCCESS);
    assert(size==5);
    assert(score_board[0]==33);
    assert(score_board[1]==34);
    assert(score_board[2]==35);
    assert(score_board[3]==32);
    assert(score_board[4]==31);
    free(score_board);

    assert(getScoreboard(oasis,6,&score_board,&size)==SUCCESS);
    assert(size==0);

    assert(getScoreboard(oasis,100,&score_board,&size)==FAILURE);

    std::cout<<"Passed score board test ^_^"<<std::endl;
}

void checkUniteClans(void* oasis,int size, int* score_board, int the_challenger){
    assert(uniteClans(oasis,4,5)==SUCCESS);
    assert(getScoreboard(oasis,5,&score_board,&size)==FAILURE);
    assert(getScoreboard(oasis,4,&score_board,&size)==SUCCESS);
    assert(size==7);
    assert(score_board[0]==39);
    assert(score_board[1]==40);
    assert(score_board[2]==36);
    assert(score_board[3]==38);
    assert(score_board[4]==33);
    assert(score_board[5]==34);
    assert(score_board[6]==32);
    free(score_board);
    assert(getBestPlayer(oasis,4,&the_challenger)==SUCCESS);
    assert(the_challenger==36);

    assert(uniteClans(oasis,2,1)==SUCCESS);
    assert(getScoreboard(oasis,2,&score_board,&size)==FAILURE);
    assert(getScoreboard(oasis,1,&score_board,&size)==SUCCESS);
    assert(size==13);
    free(score_board);
    assert(getBestPlayer(oasis,1,&the_challenger)==SUCCESS);
    assert(the_challenger==6);

    assert(uniteClans(oasis,1,15)==SUCCESS);
    assert(getScoreboard(oasis,15,&score_board,&size)==FAILURE);
    assert(getScoreboard(oasis,1,&score_board,&size)==SUCCESS);
    assert(size==13);
    free(score_board);
    assert(getBestPlayer(oasis,1,&the_challenger)==SUCCESS);
    assert(the_challenger==6);

    assert(uniteClans(oasis,4,3)==SUCCESS);
    assert(getScoreboard(oasis,4,&score_board,&size)==FAILURE);
    assert(getScoreboard(oasis,3,&score_board,&size)==SUCCESS);
    assert(size==14);
    free(score_board);
    assert(getBestPlayer(oasis,3,&the_challenger)==SUCCESS);
    assert(the_challenger==24);

    assert(uniteClans(oasis,3,1)==SUCCESS);
    assert(getScoreboard(oasis,1,&score_board,&size)==FAILURE);
    assert(getScoreboard(oasis,3,&score_board,&size)==SUCCESS);
    assert(size==27);
    free(score_board);
    assert(getBestPlayer(oasis,3,&the_challenger)==SUCCESS);
    assert(the_challenger==6);

    assert(uniteClans(oasis,16,17)==SUCCESS);
    assert(getScoreboard(oasis,17,&score_board,&size)==FAILURE);
    assert(getScoreboard(oasis,16,&score_board,&size)==SUCCESS);
    assert(size==0);
    free(score_board);
    assert(getBestPlayer(oasis,16,&the_challenger)==SUCCESS);
    assert(the_challenger==-1);

    assert(getBestPlayer(oasis,-1,&the_challenger)==SUCCESS);
    assert(the_challenger==6);
    assert(getScoreboard(oasis,-10000,&score_board,&size)==SUCCESS);
    assert(size==50);
    assert(score_board[0]==47);
    assert(score_board[49]==51);
    free(score_board);

    assert(uniteClans(oasis,100,1)==FAILURE);
    assert(uniteClans(oasis,3,100)==FAILURE);

    std::cout<<"Passed unite clan test :3"<<std::endl;
}

void printSomeChar(char c, int amount){
    for(int i=0; i<amount*2; i++)
        std::cout<<c;
}

void printPenguin(char c){
    std::cout<<std::endl;

    printSomeChar(' ', 6);printSomeChar(c, 8);std::cout<<std::endl;

    printSomeChar(' ', 4);printSomeChar(c, 12);std::cout<<std::endl;

    printSomeChar(' ', 3);printSomeChar(c, 14);std::cout<<std::endl;

    printSomeChar(' ', 2);printSomeChar(c, 16);std::cout<<std::endl;

    printSomeChar(' ', 1);printSomeChar(c, 3);printSomeChar(' ', 2);printSomeChar(c, 8);printSomeChar(' ', 2);
    printSomeChar(c, 3);std::cout<<std::endl;

    printSomeChar(' ', 1);printSomeChar(c, 2);printSomeChar(' ',4);printSomeChar(c, 6);printSomeChar(' ', 4);
    printSomeChar(c, 2);std::cout<<std::endl;

    printSomeChar(c, 2);printSomeChar(' ',5);printSomeChar(c, 6);printSomeChar(' ', 5);printSomeChar(c, 2);std::cout<<std::endl;

    printSomeChar(c, 2);printSomeChar(' ',2);printSomeChar(c, 2);printSomeChar(' ', 2);printSomeChar(c, 4);
    printSomeChar(' ',2);printSomeChar(c,2);printSomeChar(' ',2);printSomeChar(c,2);std::cout<<std::endl;

    printSomeChar(c, 2);printSomeChar(' ',2);printSomeChar(c, 2);printSomeChar(' ', 2);printSomeChar(c, 4);
    printSomeChar(' ',2);printSomeChar(c,2);printSomeChar(' ',2);printSomeChar(c,2);std::cout<<std::endl;

    printSomeChar(c, 2);printSomeChar(' ',6);printSomeChar(c, 4);printSomeChar(' ',6);printSomeChar(c,2);std::cout<<std::endl;

    printSomeChar(c, 2);printSomeChar(' ',6);printSomeChar(c, 4);printSomeChar(' ',6);printSomeChar(c,2);std::cout<<std::endl;

    printSomeChar(c, 2);printSomeChar(' ',5);printSomeChar(c, 6);printSomeChar(' ',5);printSomeChar(c,2);std::cout<<std::endl;

    printSomeChar(c, 2);printSomeChar(' ',5);printSomeChar(c, 2);printSomeChar(' ',2);printSomeChar(c, 2);
    printSomeChar(' ',5);printSomeChar(c,2);std::cout<<std::endl;

    printSomeChar(c, 2);printSomeChar(' ',5);printSomeChar(c, 2);printSomeChar(' ',2);printSomeChar(c, 2);
    printSomeChar(' ',5);printSomeChar(c,2);std::cout<<std::endl;

    printSomeChar(' ',1);printSomeChar(c, 2);printSomeChar(' ',4);printSomeChar(c,6);
    printSomeChar(' ',4);printSomeChar(c,2);std::cout<<std::endl;

    printSomeChar(' ',1);printSomeChar(c, 3);printSomeChar(' ',4);printSomeChar(c,4);
    printSomeChar(' ',4);printSomeChar(c,3);std::cout<<std::endl;

    printSomeChar(' ',2);printSomeChar(c, 3);printSomeChar(' ',10);printSomeChar(c,3);std::cout<<std::endl;

    printSomeChar(' ',3);printSomeChar(c, 3);printSomeChar(' ',8);printSomeChar(c,3);std::cout<<std::endl;

    printSomeChar(' ',4);printSomeChar(c, 12);std::cout<<std::endl;

    printSomeChar(' ',6);printSomeChar(c, 8);std::cout<<std::endl;

}

int main() {
    void* oasis = init();
    if (oasis == NULL) {
        printf("init failed.\n");
    };
    int the_challenger=0,size=-1,*score_board= nullptr;
    checkBadInputs(oasis,the_challenger,size,score_board);
    checkAddPlayer(oasis,the_challenger,size,score_board);
    checkAddClan(oasis);
    checkJoinClan(oasis);
    checkCompleteChallange(oasis);
    checkGetBestPlayer(oasis,the_challenger);
    checkGetScoreboardFirst(oasis,size,score_board);
    checkUniteClans(oasis,size,score_board,the_challenger);
    quit(&oasis);
    assert(oasis==NULL);
    std::cout<<"all good, take a penguin:"<<std::endl;
    printPenguin('@');
    return 0;
}