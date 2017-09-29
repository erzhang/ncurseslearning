#include <ncurses.h>
#include <vector>
#include <iostream>
#include <memory>
#include "StateAndBlocks.hpp"
#include "Screen.hpp"



void erase(int y, int x, Screen &curscr, StateTrack &curstate)
{
    erase();
    curscr.draw_state(curstate);
    curscr.draw_box();
}
int updateRow(int position, int update)
{
    if(position + update > -2+ FRAME_HEIGHT + TOP_LEFT_CORNER_ROW) return position;
    if(position + update < 1 + TOP_LEFT_CORNER_ROW) return position;
    return position + update;
}

int updateCol(int position, int update)
{
    if(position + update > -2+ FRAME_WIDTH + TOP_LEFT_CORNER_COL) return position;
    if(position + update < 1 + TOP_LEFT_CORNER_COL) return position;
    return position + update;
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
            col = updateCol(col,-1); state.updateRow(row); state.updateCol(col);
            erase(row, col, curscr, state);
            refresh();
        } else if(ch == 'j') { //down
            row = updateRow(row, 1); state.updateRow(row); state.updateCol(col);
            erase(row, col, curscr, state);
            refresh();
        } else if(ch == 'k') { //up
            row = updateRow(row, -1); state.updateRow(row); state.updateCol(col);
            erase(row, col, curscr, state);
            refresh();
        } else if(ch == 'l') { //right
            col = updateCol(col,1); state.updateRow(row); state.updateCol(col);
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
    std::unique_ptr<Block> testBlockPtr(new I_Block());
    for(auto &x : testBlockPtr->blocksFilled) std::cout<< x << std::endl;
    StateTrack testState(testBlockPtr);
    Screen scr;
    int ch =   getch();
    game_loop('@', 25,40, ch, scr, testState);
    endwin();
    return 0;
}
