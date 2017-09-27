#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "StateAndBlocks.hpp"
class Screen {
    public:
        Screen();
        void add();
        void draw_box();
        void draw_state(StateTrack &st);
    private:
        int height;
        int width;
        int numcell{height*width};
};
#endif
