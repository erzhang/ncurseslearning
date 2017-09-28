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


StateTrack::StateTrack(Block* b) 
    : gameBoardState(FRAME_HEIGHT*FRAME_WIDTH, 0)
    , score(0)
    , iblock(b)
    , curRow(TOP_LEFT_CORNER_ROW + 1)
    , curCol(TOP_LEFT_CORNER_COL + 1)
{
}

void StateTrack::fillSpace(std::vector<int> indices)
{
    for(auto &idx : indices){ ++(this->gameBoardState[idx]); }
}

Tetronimo::Tetronimo()
    : blocksFilled{0,1,1,0,1,1,0,1,1,0,0}
{
}

I_Block::I_Block() 
    : blocksFilled{0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0}
{ 
}
void Tetronimo::rotate_cw(){
    std::vector<int> original(blocksFilled);
    for(int row = 0; row < 3; ++row)
    {
        for(int col = 0; col < 3; ++col)
        {
            blocksFilled[squareToVec(row,col,3)] =
                original[squareToVec(col,row,3)];
            //some cool bit manipulation to get 3 from 0 and 1 from 2 and vice
            //versa
        }
    }
}
void Tetronimo::rotate_countercw(){
    //just rotate three times lol
    rotate_cw();
    rotate_cw();
    rotate_cw();
}

void I_Block::rotate_cw(){
    std::vector<int> original(blocksFilled);
    for(int row = 0; row < 4; ++row)
    {
        for(int col = 0; col < 4; ++col)
        {
            blocksFilled[squareToVec(row,col,4)] =
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

