#include <ncurses.h>
class Screen {
    public:
        void initialize();
        void add();
        void draw_box(int height, int width);
};

void Screen::draw_box(int h, int w)
{
    int topLeftRow = topLeftCol = 10;

    for(int row = topLeftRow; row < h; ++row){ 
        mvaddch(row, topLeftCol, '|'); 
    }
    for(int row = topLeftRow; row < h; ++row){
        mvaddch(row, topLeftCol+w, '|'); 
    }
    for(int col = topLeftCol+1; col < borderOffset+w+1; ++col){
        mvaddch(topLeftRow  ,col , '-'); 
    }
    for(int col = topLeftCol+1; col < borderOffset+w+1; ++col){
        mvaddch(topLeftRow+h,col , '-'); 
    }
}
void Screen::initialize(){
    initscr();
}
void Screen::add(){
    printw("hello");
}
void erase(int y, int x)
{
    erase();
}
void game_loop(char main_char, int row, int col, int ch)
{
    if(ch == 'q') return;

    mvaddch(row, col, main_char);
    refresh();

    for(;;)
    {
        ch = getch();
/* vimkeys*/   if (ch == 'h') { //left
            erase(row, col);
            col = col - 1;
            mvaddch(row, col, main_char);
            refresh();
        } else if(ch == 'j') { //down
            erase(row, col);
            row = row + 1;
            mvaddch(row, col, main_char);
            refresh();
        } else if(ch == 'k') { //up
            erase(row, col);
            row = row - 1;
            mvaddch(row, col, main_char);
            refresh();
        } else if(ch == 'l') { //right
            erase(row, col);
            col = col + 1;
            mvaddch(row, col, main_char);
            refresh();
        } else if(ch == 'q') {
            break;
        }

    }
}
int main() 
{
    Screen scr;
    scr.initialize();
    scr.add();
    scr.draw_box(40,40);
    getch();
    endwin();
    return 0;
}
