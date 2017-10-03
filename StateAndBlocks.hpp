#ifndef _STATEBLOCKS_H_
#define _STATEBLOCKS_H_
#include <memory>
#include <vector>

constexpr int FRAME_HEIGHT        = 20;
constexpr int FRAME_WIDTH         = 20;
constexpr int TOP_LEFT_CORNER_ROW = 05; 
constexpr int TOP_LEFT_CORNER_COL = 30;

int squareToVec(int row, int col, int size); 
std::vector<int> vecToSquare(int idx, int size); 

class Block{
    public:
        Block(int blockw, std::vector<int> bF) 
            : blockWidth(blockw), blocksFilled(bF) {}
        virtual void rotate_cw();
        virtual void rotate_countercw();
        int blockWidth;
        std::vector<int> blocksFilled;
};

class O_Block : public Block { public: O_Block(); void rotate_cw() override {}; }; 
class I_Block : public Block { public: I_Block(); void rotate_cw() override;    }; 
class T_Block : public Block { public: T_Block();                               }; 
class L_Block : public Block { public: L_Block();                               }; 
class J_Block : public Block { public: J_Block();                               }; 
class S_Block : public Block { public: S_Block();                               }; 
class Z_Block : public Block { public: Z_Block();                               };


class StateTrack {
    public:
        StateTrack();
        void clearRows();
        void addScore() { ++score; };
        void fillSpace();
        void updateRow(int newrow) { curRow = newrow;}
        void updateCol(int newcol) { curCol = newcol;}
        void renewTetronimoBlock();
        int curScore(){ return score;}
        int row() { return curRow; }
        int col() { return curCol; }
        std::vector<int> gameBoardState;
        std::unique_ptr<Block> iblock; //Current Block
    private:
        int score;
        int curRow;
        int curCol;
};

#endif
