//
//  window.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/28/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "window.h"
#include <iostream>

ncursesWindow::ncursesWindow(int height, int length, int ypos, int xpos){
    
    m_window = newwin(height, length, ypos, xpos);
    setborder('|', '|', '=', '=', '+', '+', '+', '+');
    
    
}


void ncursesWindow::close(){
    
    if(m_window){
        /* box(local_win, ' ', ' '); : This won't produce the desired
         * result of erasing the window. It will leave it's four corners
         * and so an ugly remnant of window.
         */
        wborder(m_window, ' ', ' ', ' ',' ',' ',' ',' ',' ');
        /* The parameters taken are
         * 1. win: the window on which to operate
         * 2. ls: character to be used for the left side of the window
         * 3. rs: character to be used for the right side of the window
         * 4. ts: character to be used for the top side of the window
         * 5. bs: character to be used for the bottom side of the window
         * 6. tl: character to be used for the top left corner of the window
         * 7. tr: character to be used for the top right corner of the window
         * 8. bl: character to be used for the bottom left corner of the window
         * 9. br: character to be used for the bottom right corner of the window
         */
        wrefresh(m_window);
        delwin(m_window);
    
    }
    else{
        //std::cerr << "Attempted to close null window!" << std::endl;
    }
}

void ncursesWindow::setborder(char ls, char rs, char ts, char bs, char tl, char tr, char bl, char br){

    wborder(m_window, ls, rs, ts, bs, tl, tr, bl, br);

}