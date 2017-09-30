#include <ncurses.h>
#include <vector>
#include <iostream>
#include <memory>
#include <ctime>
#include "StateAndBlocks.hpp"
#include "Screen.hpp"

void erase(int y, int x, Screen &curscr, StateTrack &curstate)
{
    erase();
    curscr.draw_box();
    curscr.draw_state(curstate);
}

//Position is top left position of block
int updateRow(int row, int col, int update, StateTrack &st)
{
    int blockIdx = 0;
    for(auto &block : st.iblock-> blocksFilled)
    {
        if(block){
            std::vector<int> rc = vecToSquare(blockIdx, st.iblock->blockWidth);
            if(rc[0] + row + update < TOP_LEFT_CORNER_ROW) return row;
            if(rc[0] + row + update >= FRAME_HEIGHT + TOP_LEFT_CORNER_ROW) return row;
        }
        ++blockIdx;
    }
    return row + update;
}

int updateCol(int row, int col, int update, StateTrack &st)
{

    int blockIdx = 0;
    for(auto &block : st.iblock-> blocksFilled)
    {
        if(block){
            std::vector<int> rc = vecToSquare(blockIdx, st.iblock->blockWidth);
            if(rc[1] + col + update < TOP_LEFT_CORNER_COL) return col;
            if(rc[1] + col + update >= FRAME_WIDTH + TOP_LEFT_CORNER_COL) return col;
        }
        ++blockIdx;
    }
    return col + update;
}

void attemptRotate(int row, int col, StateTrack &st)
{
    st.iblock->rotate_countercw();

    int blockIdx = 0;
    for(auto &block : st.iblock-> blocksFilled)
    {
        if(block==1)
        {
            std::vector<int> rc = vecToSquare(blockIdx, st.iblock->blockWidth);
            if( rc[1] + col <  TOP_LEFT_CORNER_COL                  ||
              ( rc[1] + col >= FRAME_WIDTH + TOP_LEFT_CORNER_COL)   ||
              ( rc[0] + row <  TOP_LEFT_CORNER_ROW)                 ||
              ( rc[0] + row >= FRAME_HEIGHT + TOP_LEFT_CORNER_ROW)   ) 
            {
                //Rotate to original
                st.iblock ->rotate_cw();
                return;
            }
        }
        ++blockIdx;
    }
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
            col = updateCol(row, col,-1, state); state.updateRow(row); state.updateCol(col);
            erase(row, col, curscr, state);
            refresh();
        } else if(ch == 'j') { //down
            row = updateRow(row, col, 1, state); state.updateRow(row); state.updateCol(col);
            erase(row, col, curscr, state);
            refresh();
        } else if(ch == 'k') { //up
            row = updateRow(row, col, -1, state); state.updateRow(row); state.updateCol(col);
            erase(row, col, curscr, state);
            refresh();
        } else if(ch == 'l') { //right
            col = updateCol(row, col,1, state); state.updateRow(row); state.updateCol(col);
            erase(row, col, curscr, state);
            refresh();
        } else if(ch == 'q') {
            break;
        } else if(ch == 'c') {
            attemptRotate(row, col, state);
            erase(row, col,curscr, state);
            refresh();
        } else if(ch == 'i') {
           state.updateRow(row); state.updateCol(col); 
           state.fillSpace();
            erase(row, col,curscr, state);
            refresh();
        }
    }
}

int main() 
{
    StateTrack testState;
    Screen scr;
    int ch =   getch();
    game_loop('@', 25,40, ch, scr, testState);
    endwin();
    return 0;
}
