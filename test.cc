#include <ncurses.h>
#include <vector>
#include <iostream>
int squareToVec(int row, int col, int size) { return row*size + col; }
std::vector<int> vecToSquare(int idx, int size) { 
    std::vector<int> rc;
    rc.push_back((int)(idx/size));
    rc.push_back(idx - rc[0]*size);
    return rc;
}

class Block{
    public:
        virtual void rotate_cw() = 0;
        virtual void rotate_countercw() = 0;
};

class I_Block : public Block {
    public:
        I_Block();
        void rotate_cw();
        void rotate_countercw();
        std::vector<int> blocksFilled;
};

I_Block::I_Block() : blocksFilled{0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0} { }
void I_Block::rotate_cw(){
    std::vector<int> original(this->blocksFilled);
    for(int row = 0; row < 4; ++row)
    {
        for(int col = 0; col < 4; ++col)
        {
            this->blocksFilled[squareToVec(row,col,4)] =
                original[squareToVec(col,(~row & 3),4)];
            //some cool bit manipulation to get 3 from 0 and 1 from 2 and vice
            //versa
        }
    }
}
void I_Block::rotate_countercw(){
    //just rotate three times lol
    rotate_cw();
    rotate_cw();
    rotate_cw();
}

class Screen {
    public:
        Screen(int h, int w, I_Block b);
        void add();
        void draw_box();
        void draw_block(int originRow, int originCol);
        I_Block currentBlock;
    private:
        int height;
        int width;
        int numcell{height*width};
        std::vector<int> gameBoard;
};

void Screen::draw_block(int oRow, int oCol)
{

    int idx = 0;
    for(auto &occupied : currentBlock.blocksFilled){
        if(occupied){
            std::vector<int> rc = vecToSquare(idx, 4);
            mvaddch(rc[0] + oRow, rc[1] + oCol, '#');
        }
        ++idx;
    }
}
Screen::Screen(int h, int w, I_Block b)
    : height(h), width(w), gameBoard(height*width, 0), currentBlock(b)
{
    initscr();
}
void Screen::draw_box()
{
    int topLeftRow = 10;
    int topLeftCol = 30;
    int h = this->height;
    int w = this->width;

    for(int row = topLeftRow; row < topLeftRow+h; ++row){ 
        mvaddch(row, topLeftCol, '|'); 
    }
    for(int row = topLeftRow; row < topLeftRow+h; ++row){
        mvaddch(row, topLeftCol+w, '|'); 
    }
    for(int col = topLeftCol; col < topLeftCol+w+1; ++col){
        mvaddch(topLeftRow  ,col , '-'); 
    }
    for(int col = topLeftCol; col < topLeftCol+w+1; ++col){
        mvaddch(topLeftRow+h,col , '-'); 
    }
}

void Screen::add(){
    printw("hello");
}
void erase(int y, int x, Screen &curscr)
{
    erase();
    curscr.draw_box();
    curscr.draw_block(y,x);
}
void game_loop(char main_char, int row, int col, int ch, Screen &curscr)
{
    if(ch == 'q') return;

    mvaddch(row, col, main_char);
    refresh();

    for(;;)
    {
        ch = getch();
/* vimkeys*/   if (ch == 'h') { //left
            erase(row, col, curscr);
            col = col - 1;
//            mvaddch(row, col, main_char);
            refresh();
        } else if(ch == 'j') { //down
            erase(row, col, curscr);
            row = row + 1;
  //          mvaddch(row, col, main_char);
            refresh();
        } else if(ch == 'k') { //up
            erase(row, col, curscr);
            row = row - 1;
   //         mvaddch(row, col, main_char);
            refresh();
        } else if(ch == 'l') { //right
            erase(row, col,curscr);
            col = col + 1;
    //        mvaddch(row, col, main_char);
            refresh();
        } else if(ch == 'q') {
            break;
        } else if(ch == 'c') {
            curscr.currentBlock.rotate_countercw();
            erase(row, col,curscr);
            refresh();
        }
    }
}
int main() 
{
    I_Block testBlock;
    Screen scr(40,40,testBlock);
    int ch =   getch();
    game_loop('@', 50,50, ch, scr);
    endwin();
    return 0;
}
