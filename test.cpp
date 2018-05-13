//
// Created by Ilya on 5/13/2018.
//

#include "Oasis.h"
#include <assert.h>
#include "library1.h"

int main(){
    int the_challenger=0,size=-1,*score_board= nullptr;
    void* oasis = init();
    for(int i=0;i<50;i++){
        if(!i)
            (addPlayer(oasis,51,i)==SUCCESS);
        else
            (addPlayer(oasis,i,i)==SUCCESS);
    }
    for(int i=1;i<50;i++){
        (addPlayer(oasis,i,i*i)==FAILURE);
    }
    (getBestPlayer(oasis,-1,&the_challenger)==SUCCESS);
    (the_challenger==1);
    (getScoreboard(oasis,-50,&score_board,&size)==SUCCESS);
    (size==50);
    (score_board[49]==51);
    free(score_board);
    for(int i=0;i<20;i++){
        if(!i)
            (addClan(oasis,21)==SUCCESS);
        else
            (addClan(oasis,i)==SUCCESS);
    }
    for(int i=1;i<20;i++){
        (addClan(oasis,i)==FAILURE);
    }
    for(int i=1,j=1;i<41;i++){
        if(i<11){
            (joinClan(oasis,i,j)==SUCCESS);
            j= i==10? 2: 1;
        }else if(i<21){
            (joinClan(oasis,i,j)==SUCCESS);
            j= i==20? 3: 2;
        }else if(i<31) {
            (joinClan(oasis, i, j) == SUCCESS);
            j = i == 30 ? 5 : 3;
        }else if(i<36) {
            (joinClan(oasis, i, j) == SUCCESS);
            j = i == 35 ? 4 : 5;
        } else
            (joinClan(oasis, i, j) == SUCCESS);
    }
    for(int i=40,j=1;i>0;i--,j++){
        (joinClan(oasis,i,j)==FAILURE);
    }

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
    assert(getScoreboard(oasis,1,&score_board,&size)==SUCCESS);
    assert(size==10);
    return 0;
}
