#ifndef _STATEBLOCKS_H_
#define _STATEBLOCKS_H_

#include <vector>
constexpr int FRAME_HEIGHT        = 40;
constexpr int FRAME_WIDTH         = 20;
constexpr int TOP_LEFT_CORNER_ROW = 05; 
constexpr int TOP_LEFT_CORNER_COL = 30;

int squareToVec(int row, int col, int size); 
std::vector<int> vecToSquare(int idx, int size); 

class Block{
    public:
        std::vector<int> blocksFilled{0,0,0,0,0,1,0,0,0,0,0};
        int blockWidth = 3;
        virtual void rotate_cw() = 0;
        virtual void rotate_countercw() = 0;
};

class Tetronimo : public Block {
    public:
        Tetronimo();
        void rotate_cw();
        void rotate_countercw();
        std::vector<int> blocksFilled;
        int blockWidth = 3;
};

class I_Block : public Block {
    public:
        I_Block();
        void rotate_cw();
        void rotate_countercw();
        std::vector<int> blocksFilled;
        int blockWidth = 4;
};

class StateTrack {
    public:
        StateTrack(Block *b);
        void removeRows(std::vector<int> rows);
        void removeRows(int row);
        void addScore(int numRows);
        void fillSpace(std::vector<int> indices);
        Block *iblock; //Current Block
        void updateRow(int newrow) { curRow = newrow;}
        void updateCol(int newcol) { curCol = newcol;}
        int row() { return curRow; }
        int col() { return curCol; }
    private:
        int score;
        int curRow;
        int curCol;
        std::vector<int> gameBoardState;
};

#endif
