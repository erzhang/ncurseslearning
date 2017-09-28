#include <ncurses.h>
#include <vector>
#include <iostream>
#include "StateAndBlocks.hpp"
#include "Screen.hpp"



void erase(int y, int x, Screen &curscr, StateTrack &curstate)
{
    erase();
    curscr.draw_state(curstate);
    curscr.draw_box();
}

void game_loop(char main_char, int row, int col, int ch, Screen &curscr, StateTrack &state)
{
    if(ch == 'q') return;

    mvaddch(row, col, main_char);
    refresh();

    for(;;)
    {
        ch = getch();
        if (ch == 'h') {       //left
            col = col - 1;
            state.updateRow(row);
            state.updateCol(col);
            erase(row, col, curscr, state);
            refresh();
        } else if(ch == 'j') { //down
            row = row + 1;
            state.updateRow(row);
            state.updateCol(col);
            erase(row, col, curscr, state);
            refresh();
        } else if(ch == 'k') { //up
            row = row - 1;
            state.updateRow(row);
            state.updateCol(col);
            erase(row, col, curscr, state);
            refresh();
        } else if(ch == 'l') { //right
            col = col + 1;
            state.updateRow(row);
            state.updateCol(col);
            erase(row, col, curscr, state);
            refresh();
        } else if(ch == 'q') {
            break;
        } else if(ch == 'c') {
            state.iblock->rotate_countercw();
            erase(row, col,curscr, state);
            refresh();
        } else if(ch == 'e') {
            refresh();
        }
    }
}
int main() 
{
    Block* testBlock = new I_Block;
    StateTrack testState(testBlock);
    Screen scr;
    int ch =   getch();
    game_loop('@', 50,50, ch, scr, testState);
    endwin();
    return 0;
}
