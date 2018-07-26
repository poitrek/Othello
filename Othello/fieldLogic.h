#pragma once
#include "Field.h"

typedef std::pair<int, int> pair_;
extern std::vector <pair_> Versor;

void setup_Versor();
Field *neighbr(Field tab[][8], Field *F, pair_ versor);
State opponentIndex(State playerIndex);
bool isMoveValid(Field tab[][8], Field *F, State plInd);
void moveOn(Field tab[][8], Field *F, State plInd);

std::pair <int, int> findIndex(Field tab[][8], Field *F);
Field *left(Field tab[][8], Field *F);
Field *right(Field tab[][8], Field *F);
Field *top(Field tab[][8], Field *F);
Field *bottom(Field tab[][8], Field *F);