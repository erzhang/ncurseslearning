#include "Screen.hpp"
#include "StateAndBlocks.hpp"
#include <ncurses.h>
#include <vector>
#include <iostream>

void Screen::draw_state(StateTrack &st)
{
    int oRow = st.row();
    int oCol = st.col();
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
    for(int row = TOP_LEFT_CORNER_ROW; row < TOP_LEFT_CORNER_ROW+FRAME_HEIGHT;  ++row) { 
        mvaddch(row, TOP_LEFT_CORNER_COL, '|'); 
    }
    for(int row = TOP_LEFT_CORNER_ROW; row < TOP_LEFT_CORNER_ROW+FRAME_HEIGHT;  ++row) { 
        mvaddch(row, TOP_LEFT_CORNER_COL+FRAME_WIDTH, '|'); 
    }
    for(int col = TOP_LEFT_CORNER_COL; col < TOP_LEFT_CORNER_COL+FRAME_WIDTH+1; ++col) { 
        mvaddch(TOP_LEFT_CORNER_ROW  ,col , '-'); 
    }
    for(int col = TOP_LEFT_CORNER_COL; col < TOP_LEFT_CORNER_COL+FRAME_WIDTH+1; ++col) {
        mvaddch(TOP_LEFT_CORNER_ROW+FRAME_HEIGHT,col , '-'); 
    }
}

void Screen::add(){
    printw("hello");
}
