#include <numeric>
#include <iostream>
#include "StateAndBlocks.hpp"

// matrix to linear idx transformations
int squareToVec(int row, int col, int size) { 
    return row*size + col; 
}

std::vector<int> vecToSquare(int idx, int size) { 
    std::vector<int> rc;
    rc.push_back((int)(idx/size));
    rc.push_back(idx - rc[0]*size);
    return rc;
}

Block* randomBlockPiece()
{
    srand(time(NULL)); //set random seed
    int output = rand() % 7;
    switch (output){
        case 0: return new I_Block(); 
        case 1: return new T_Block(); 
        case 2: return new L_Block(); 
        case 3: return new J_Block(); 
        case 4: return new S_Block(); 
        case 5: return new Z_Block(); 
        case 6: return new O_Block(); 
    }
    return nullptr;
}


StateTrack::StateTrack() 
    : gameBoardState(FRAME_HEIGHT*FRAME_WIDTH, 0)
    , score(0)
    , iblock(randomBlockPiece())
    , curRow(TOP_LEFT_CORNER_ROW + 1)
    , curCol(TOP_LEFT_CORNER_COL + 1)
{
}

void StateTrack::renewTetronimoBlock()
{
    iblock.reset(randomBlockPiece());
}

I_Block::I_Block() : Block(4, std::vector<int>{0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0}) { }
T_Block::T_Block() : Block(3, std::vector<int>{0,1,0,1,1,1,0,0,0})               { }
L_Block::L_Block() : Block(3, std::vector<int>{0,1,0,0,1,0,0,1,1})               { }
J_Block::J_Block() : Block(3, std::vector<int>{0,1,0,0,1,0,1,1,0})               { }
S_Block::S_Block() : Block(3, std::vector<int>{0,0,0,0,1,1,1,1,0})               { }
Z_Block::Z_Block() : Block(3, std::vector<int>{0,0,0,1,1,0,0,1,1})               { }
O_Block::O_Block() : Block(2, std::vector<int>{1,1,1,1})                         { }

void Block::rotate_cw(){
    std::vector<int> original(blocksFilled);
    for(int row = 0; row < 3; ++row) {
        for(int col = 0; col < 3; ++col) {
            blocksFilled[squareToVec(row,col,3)] =
                original[squareToVec(col,abs(row-2),3)];
        }
    }
}

void I_Block::rotate_cw(){
    std::vector<int> original(blocksFilled);
    for(int row = 0; row < 4; ++row) {
        for(int col = 0; col < 4; ++col) {
            blocksFilled[squareToVec(row,col,4)] =
                original[squareToVec(col,(~row & 3),4)];
            //some cool bit manipulation to get 3 from 0 and 1 from 2 and vice
            //versa
        }
    }
}
void Block::rotate_countercw(){
    //just rotate three times lol
    rotate_cw(); rotate_cw(); rotate_cw();
}

void StateTrack::fillSpace()
{
    int blockIndex = 0;
    for(auto &block : iblock->blocksFilled){
        if(block){
            std::vector<int> rc = vecToSquare(blockIndex, iblock->blockWidth);
            int gameBoardRow = rc[0] + row() - TOP_LEFT_CORNER_ROW; 
            int gameBoardCol = rc[1] + col() - TOP_LEFT_CORNER_COL;
            gameBoardState[squareToVec(gameBoardRow, gameBoardCol, FRAME_WIDTH)]=1;
        }
        ++blockIndex;
    }
    clearRows();
    renewTetronimoBlock();
    updateRow(TOP_LEFT_CORNER_ROW);
    updateCol(TOP_LEFT_CORNER_COL + FRAME_WIDTH/2);
}

void StateTrack::clearRows()
{
   //Scan through each row and check if row is filled
   for(int r = 0; r < FRAME_HEIGHT; ++r){
       std::vector<int>::iterator startrow = gameBoardState.begin() + r*FRAME_WIDTH;
       std::vector<int>::iterator endrow = gameBoardState.begin() + (r+1)*FRAME_WIDTH;
       int checkFull = accumulate(startrow, endrow, 0);
       if( accumulate(startrow, endrow, 0) >= FRAME_WIDTH)
       {
           for( auto it = startrow; it != endrow; ++it)
               *it = 0;
       }
   }
   //TODO: add functionality for moving all pieces down when a row is cleared
}
