#pragma once

#include "header.h"
#include "BaseEngine.h"
#include "JPGImage.h"
#include "TileManager.h"
#include "2048Tile.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

class main2048 :
    public BaseEngine
{
public:
    main2048(void);
    ~main2048(void);

    void SetupBackgroundBuffer();
    void DrawStrings();
    void drawTiles();
    int8_t findTarget(uint16_t array[4], int8_t x,int8_t stop);
    bool slideArray(uint16_t array[4]);
    void rotateBoard();
    bool moveUp();
    bool moveLeft();
    bool moveDown();
    bool moveRight();
    bool findPairDown();
    int16_t countEmpty();
    bool gameEnded();
    void addRandom();
    void reset();
    void check();
    void updateHS();
    void loadHS();
    void saveHS();
    void KeyDown(int iKeyCode);
    enum State { stateInit, stateMain, statePaused, stateWin, stateEnd };

private:
    tile2048 tiles;
    uint16_t data[4][4];
    bool success;
    State m_state;
    int levels;
    int score;
    int highscore1;
    int highscore2;
    int highscore3;
};
