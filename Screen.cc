#include "Screen.hpp"
#include "StateAndBlocks.hpp"
#include <ncurses.h>
#include <vector>
#include <iostream>

void Screen::draw_state(StateTrack &st)
{
    int oRow = st.row();
    int oCol = st.col();

    int space_idx = 0;
    for(auto space : st.gameBoardState){
            std::vector<int> rc = vecToSquare(space_idx, FRAME_WIDTH);
            if(space==1) {
                mvaddch(rc[0] + TOP_LEFT_CORNER_ROW, rc[1] + TOP_LEFT_CORNER_COL, 'o');
            } else {
                mvaddch(rc[0] + TOP_LEFT_CORNER_ROW, rc[1] + TOP_LEFT_CORNER_COL, '.');
            }
            ++space_idx;
    }

    int idx = 0;
    for(auto &occupied : st.iblock->blocksFilled){
        if(occupied){
            std::vector<int> rc = vecToSquare(idx, st.iblock->blockWidth);
            mvaddch(rc[0] + oRow, rc[1] + oCol, '#');
        }
        ++idx;
    }



}


Screen::Screen() 
{
    initscr();
}

void Screen::draw_box()
{
    for(int row = TOP_LEFT_CORNER_ROW-1; row < TOP_LEFT_CORNER_ROW+FRAME_HEIGHT+1;  ++row) { 
        mvaddch(row, TOP_LEFT_CORNER_COL-1, '|'); 
    }
    for(int row = TOP_LEFT_CORNER_ROW-1; row < TOP_LEFT_CORNER_ROW+FRAME_HEIGHT+1;  ++row) { 
        mvaddch(row, TOP_LEFT_CORNER_COL+FRAME_WIDTH, '|'); 
    }
    for(int col = TOP_LEFT_CORNER_COL-1; col < TOP_LEFT_CORNER_COL+FRAME_WIDTH+1; ++col) { 
        mvaddch(TOP_LEFT_CORNER_ROW-1 ,col , '-'); 
    }
    for(int col = TOP_LEFT_CORNER_COL-1; col < TOP_LEFT_CORNER_COL+FRAME_WIDTH+1; ++col) {
        mvaddch(TOP_LEFT_CORNER_ROW+FRAME_HEIGHT,col , '-'); 
    }

}

void Screen::add(){
    printw("hello");
}
