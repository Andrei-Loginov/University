#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Chess.h"
#include <cstdio>
#include <cstring>


int main()
{
    InitConsole("Chess", 140, 25);
    Chess game("en_passant.txt");
    game.print();
    bool go_on = true;
    std::string s;
    while (go_on) {
        game.print();
        ColorPrint(0, 8, F_L_WHITE, "%s", (game.get_turn()) ? "White" : "Black");
        ColorPrint(0, 10, F_L_WHITE, "Enter the move: ");
        
        std::cin >> s;
        step_results t = game.make_step(s);
        switch (t) {
        game.print();
        case err: ClearConsole(); game.print();  ColorPrint(0, 9, F_L_WHITE, "Incorrect"); break;
        case ok: ClearConsole(); ColorPrint(0,11, F_L_WHITE, "%d", game.is_check()); break;
        case checkmate: go_on = false; break;
        case written: ClearConsole(); break;
        }
    }
    return 0;
}

