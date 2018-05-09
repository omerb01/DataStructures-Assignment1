//
// Created by Omer on 07/05/2018.
//

#include "Oasis.h"
#include "testMacros.h"
#include "exceptions.h"

bool addPlayer(){
    Oasis os();
    ASSERT_EXCEPTION(Player p1(123,-1),OasisInvalidInput);
    ASSERT_EXCEPTION(Player p1(-1,12),OasisInvalidInput);
    ASSERT_NO_EXCEPTION(Player p1(123,12));
    ASSERT_EXCEPTION(Player p1(123,12),OasisInvalidInput);
    return true;
}

int main() {
    RUN_TEST(addPlayer);
    return 0;
}