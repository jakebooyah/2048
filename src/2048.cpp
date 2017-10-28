#include "header.h"
#include "BaseEngine.h"
#include "JPGImage.h"
#include "TileManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include "2048.h"
#include "2048Tile.h"

main2048::main2048(void)
: BaseEngine( 50 )
, m_state(stateInit)
, score( 0 )
, highscore1( 0 )
, highscore2( 0 )
, highscore3( 0 )
, data({
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}})
, tiles()
{
    loadHS();
    addRandom();
	addRandom();
}

main2048::~main2048(void)
{
}

void main2048::SetupBackgroundBuffer()
{
	switch( m_state )
	{
        case stateInit:
            FillBackground( 0x707070 );
            break;

        case stateMain:
            FillBackground( 0xFFFFCC );
            drawTiles();
            break;

        case statePaused:
            FillBackground( 0xFFFFCC );
            break;

        case stateEnd:
            FillBackground( 0xFFFFCC );
            break;

        case stateWin:
            FillBackground( 0x707070 );
            break;
	}
}

void main2048::DrawStrings()
{
    int xStart = 85;
    int yStart = 105;

    char buffer [10];
    int value = data[0][0];

    switch( m_state )
	{
        case stateInit:
            CopyBackgroundPixels( 310, 180, GetScreenWidth(), 30/*Height*/ );
            DrawScreenString( 310, 180, "2048", 0xFFFFFF, GetFont("04B_19__.ttf", 70) );
            SetNextUpdateRect( 310, 180, GetScreenWidth(), 30/*Height*/ );

            CopyBackgroundPixels( 280, 280, GetScreenWidth(), 30/*Height*/ );
            DrawScreenString( 280, 280, "Select level to Start!", 0xFFFFFF, GetFont("04B_19__.ttf", 20) );
            SetNextUpdateRect( 280, 280, GetScreenWidth(), 30/*Height*/ );

            CopyBackgroundPixels( 310, 310, GetScreenWidth(), 30/*Height*/ );
            DrawScreenString( 310, 310, "Press 1 : Level 1", 0xFFFFFF, GetFont("04B_19__.ttf", 20) );
            SetNextUpdateRect( 310, 310, GetScreenWidth(), 30/*Height*/ );

            CopyBackgroundPixels( 307, 330, GetScreenWidth(), 30/*Height*/ );
            DrawScreenString( 307, 330, "Press 2 : Level 2", 0xFFFFFF, GetFont("04B_19__.ttf", 20) );
            SetNextUpdateRect( 307, 330, GetScreenWidth(), 30/*Height*/ );

            CopyBackgroundPixels( 306, 350, GetScreenWidth(), 30/*Height*/ );
            DrawScreenString( 306, 350, "Press 3 : Level 3", 0xFFFFFF, GetFont("04B_19__.ttf", 20) );
            SetNextUpdateRect( 306, 350, GetScreenWidth(), 30/*Height*/ );
            break;

        case stateMain:
            switch (levels){
            case 1:
                CopyBackgroundPixels( 80, 20, GetScreenWidth(), 30/*Height*/ );
                DrawScreenString( 80, 20, "Level 1 : Get the 512 tile!", 0x707070, GetFont("04B_19__.ttf", 50) );
                SetNextUpdateRect( 80, 20, GetScreenWidth(), 30/*Height*/ );

                CopyBackgroundPixels( 550, 360, GetScreenWidth(), 30/*Height*/ );
                DrawScreenString( 550, 360, itoa (highscore1,buffer,10), 0x707070, GetFont("04B_19__.ttf", 50) );
                SetNextUpdateRect( 550, 360, GetScreenWidth(), 30/*Height*/ );

                break;

            case 2:
                CopyBackgroundPixels( 80, 20, GetScreenWidth(), 30/*Height*/ );
                DrawScreenString( 80, 20, "Level 2 : Get the 1024 tile!", 0x707070, GetFont("04B_19__.ttf", 50) );
                SetNextUpdateRect( 80, 20, GetScreenWidth(), 30/*Height*/ );

                CopyBackgroundPixels( 550, 360, GetScreenWidth(), 30/*Height*/ );
                DrawScreenString( 550, 360, itoa (highscore2,buffer,10), 0x707070, GetFont("04B_19__.ttf", 50) );
                SetNextUpdateRect( 550, 360, GetScreenWidth(), 30/*Height*/ );

                break;

            case 3:
                CopyBackgroundPixels( 80, 20, GetScreenWidth(), 30/*Height*/ );
                DrawScreenString( 80, 20, "Level 3 : Get the 2048 tile!", 0x707070, GetFont("04B_19__.ttf", 50) );
                SetNextUpdateRect( 80, 20, GetScreenWidth(), 30/*Height*/ );

                CopyBackgroundPixels( 550, 360, GetScreenWidth(), 30/*Height*/ );
                DrawScreenString( 550, 360, itoa (highscore3,buffer,10), 0x707070, GetFont("04B_19__.ttf", 50) );
                SetNextUpdateRect( 550, 360, GetScreenWidth(), 30/*Height*/ );

                break;
            }

            CopyBackgroundPixels( 590, 130, GetScreenWidth(), 30/*Height*/ );
            DrawScreenString( 590, 130, "R: Reset", 0x707070, GetFont("04B_19__.ttf", 20) );
            SetNextUpdateRect( 590, 130, GetScreenWidth(), 30/*Height*/ );

            CopyBackgroundPixels( 570, 160, GetScreenWidth(), 30/*Height*/ );
            DrawScreenString( 570, 160, "SPACE: Pause", 0x707070, GetFont("04B_19__.ttf", 20) );
            SetNextUpdateRect( 570, 160, GetScreenWidth(), 30/*Height*/ );

            CopyBackgroundPixels( 580, 190, GetScreenWidth(), 30/*Height*/ );
            DrawScreenString( 580, 190, "ESC: Menu", 0x707070, GetFont("04B_19__.ttf", 20) );
            SetNextUpdateRect( 580, 190, GetScreenWidth(), 30/*Height*/ );

            CopyBackgroundPixels( 540, 220, GetScreenWidth(), 30/*Height*/ );
            DrawScreenString( 540, 220, "ARROW KEYS: Move", 0x707070, GetFont("04B_19__.ttf", 20) );
            SetNextUpdateRect( 540, 220, GetScreenWidth(), 30/*Height*/ );

            CopyBackgroundPixels( 550, 320, GetScreenWidth(), 30/*Height*/ );
            DrawScreenString( 550, 320, "HighScore:", 0x707070, GetFont("04B_19__.ttf", 20) );
            SetNextUpdateRect( 550, 320, GetScreenWidth(), 30/*Height*/ );

            CopyBackgroundPixels( 550, 420, GetScreenWidth(), 30/*Height*/ );
            DrawScreenString( 550, 420, "Score:", 0x707070, GetFont("04B_19__.ttf", 20) );
            SetNextUpdateRect( 550, 420, GetScreenWidth(), 30/*Height*/ );

            CopyBackgroundPixels( 550, 460, GetScreenWidth(), 30/*Height*/ );
            DrawScreenString( 550, 460, itoa (score,buffer,10), 0x707070, GetFont("04B_19__.ttf", 50) );
            SetNextUpdateRect( 550, 460, GetScreenWidth(), 30/*Height*/ );

            if (value!=0)
            {
                CopyBackgroundPixels( xStart, yStart, 30, 30/*Height*/ );
                DrawScreenString( xStart, yStart, itoa (value,buffer,10), 0xFFFFFF, GetFont("04B_19__.ttf", 40) );
                SetNextUpdateRect( xStart, yStart, 30, 30/*Height*/ );
            }
            xStart = xStart + 110;

            value = data[0][1];
            if (value!=0)
            {
                CopyBackgroundPixels( xStart, yStart, 30, 30/*Height*/ );
                DrawScreenString( xStart, yStart, itoa (value,buffer,10), 0xFFFFFF, GetFont("04B_19__.ttf", 40) );
                SetNextUpdateRect( xStart, yStart, 30, 30/*Height*/ );
            }
            xStart = xStart + 110;

            value = data[0][2];
            if (value!=0)
            {
                CopyBackgroundPixels( xStart, yStart, 30, 30/*Height*/ );
                DrawScreenString( xStart, yStart, itoa (value,buffer,10), 0xFFFFFF, GetFont("04B_19__.ttf", 40) );
                SetNextUpdateRect( xStart, yStart, 30, 30/*Height*/ );
            }
            xStart = xStart + 110;

            value = data[0][3];
            if (value!=0)
            {
                CopyBackgroundPixels( xStart, yStart, 30, 30/*Height*/ );
                DrawScreenString( xStart, yStart, itoa (value,buffer,10), 0xFFFFFF, GetFont("04B_19__.ttf", 40) );
                SetNextUpdateRect( xStart, yStart, 30, 30/*Height*/ );
            }
            xStart = 85;
            yStart = yStart + 110;

            value = data[1][0];
            if (value!=0)
            {
                CopyBackgroundPixels( xStart, yStart, 30, 30/*Height*/ );
                DrawScreenString( xStart, yStart, itoa (value,buffer,10), 0xFFFFFF, GetFont("04B_19__.ttf", 40) );
                SetNextUpdateRect( xStart, yStart, 30, 30/*Height*/ );
            }
            xStart = xStart + 110;

            value = data[1][1];
            if (value!=0)
            {
                CopyBackgroundPixels( xStart, yStart, 30, 30/*Height*/ );
                DrawScreenString( xStart, yStart, itoa (value,buffer,10), 0xFFFFFF, GetFont("04B_19__.ttf", 40) );
                SetNextUpdateRect( xStart, yStart, 30, 30/*Height*/ );
            }
            xStart = xStart + 110;

            value = data[1][2];
            if (value!=0)
            {
                CopyBackgroundPixels( xStart, yStart, 30, 30/*Height*/ );
                DrawScreenString( xStart, yStart, itoa (value,buffer,10), 0xFFFFFF, GetFont("04B_19__.ttf", 40) );
                SetNextUpdateRect( xStart, yStart, 30, 30/*Height*/ );
            }
            xStart = xStart + 110;

            value = data[1][3];
            if (value!=0)
            {
                CopyBackgroundPixels( xStart, yStart, 30, 30/*Height*/ );
                DrawScreenString( xStart, yStart, itoa (value,buffer,10), 0xFFFFFF, GetFont("04B_19__.ttf", 40) );
                SetNextUpdateRect( xStart, yStart, 30, 30/*Height*/ );
            }
            xStart = 85;
            yStart = yStart + 110;

            value = data[2][0];
            if (value!=0)
            {
                CopyBackgroundPixels( xStart, yStart, 30, 30/*Height*/ );
                DrawScreenString( xStart, yStart, itoa (value,buffer,10), 0xFFFFFF, GetFont("04B_19__.ttf", 40) );
                SetNextUpdateRect( xStart, yStart, 30, 30/*Height*/ );
            }
            xStart = xStart + 110;

            value = data[2][1];
            if (value!=0)
            {
                CopyBackgroundPixels( xStart, yStart, 30, 30/*Height*/ );
                DrawScreenString( xStart, yStart, itoa (value,buffer,10), 0xFFFFFF, GetFont("04B_19__.ttf", 40) );
                SetNextUpdateRect( xStart, yStart, 30, 30/*Height*/ );
            }
            xStart = xStart + 110;

            value = data[2][2];
            if (value!=0)
            {
                CopyBackgroundPixels( xStart, yStart, 30, 30/*Height*/ );
                DrawScreenString( xStart, yStart, itoa (value,buffer,10), 0xFFFFFF, GetFont("04B_19__.ttf", 40) );
                SetNextUpdateRect( xStart, yStart, GetScreenWidth(), 30/*Height*/ );
            }
            xStart = xStart + 110;

            value = data[2][3];
            if (value!=0)
            {
                CopyBackgroundPixels( xStart, yStart, 30, 30/*Height*/ );
                DrawScreenString( xStart, yStart, itoa (value,buffer,10), 0xFFFFFF, GetFont("04B_19__.ttf", 40) );
                SetNextUpdateRect( xStart, yStart, 30, 30/*Height*/ );
            }
            xStart = 85;
            yStart = yStart + 110;

            value = data[3][0];
            if (value!=0)
            {
                CopyBackgroundPixels( xStart, yStart, 30, 30/*Height*/ );
                DrawScreenString( xStart, yStart, itoa (value,buffer,10), 0xFFFFFF, GetFont("04B_19__.ttf", 40) );
                SetNextUpdateRect( xStart, yStart, 30, 30/*Height*/ );
            }
            xStart = xStart + 110;

            value = data[3][1];
            if (value!=0)
            {
                CopyBackgroundPixels( xStart, yStart, 30, 30/*Height*/ );
                DrawScreenString( xStart, yStart, itoa (value,buffer,10), 0xFFFFFF, GetFont("04B_19__.ttf", 40) );
                SetNextUpdateRect( xStart, yStart, 30, 30/*Height*/ );
            }
            xStart = xStart + 110;

            value = data[3][2];
            if (value!=0)
            {
                CopyBackgroundPixels( xStart, yStart, 30, 30/*Height*/ );
                DrawScreenString( xStart, yStart, itoa (value,buffer,10), 0xFFFFFF, GetFont("04B_19__.ttf", 40) );
                SetNextUpdateRect( xStart, yStart, 30, 30/*Height*/ );
            }
            xStart = xStart + 110;

            value = data[3][3];
            if (value!=0)
            {
                CopyBackgroundPixels( xStart, yStart, 30, 30/*Height*/ );
                DrawScreenString( xStart, yStart, itoa (value,buffer,10), 0xFFFFFF, GetFont("04B_19__.ttf", 40) );
                SetNextUpdateRect( xStart, yStart, 30, 30/*Height*/ );
            }
            xStart = xStart + 110;
            break;

        case statePaused:
            CopyBackgroundPixels( 310, 180, GetScreenWidth(), 30/*Height*/ );
            DrawScreenString( 310, 180, "2084", 0x707070, GetFont("04B_19__.ttf", 70) );
            SetNextUpdateRect( 310, 180, GetScreenWidth(), 30/*Height*/ );

            CopyBackgroundPixels( 310, 280, GetScreenWidth(), 30/*Height*/ );
            DrawScreenString( 310, 280, "Game is Paused", 0x707070, GetFont("04B_19__.ttf", 20) );
            SetNextUpdateRect( 310, 280, GetScreenWidth(), 30/*Height*/ );

            CopyBackgroundPixels( 280, 310, GetScreenWidth(), 30/*Height*/ );
            DrawScreenString( 280, 310, "Press SPACE : Resume", 0x707070, GetFont("04B_19__.ttf", 20) );
            SetNextUpdateRect( 280, 310, GetScreenWidth(), 30/*Height*/ );

            break;

        case stateEnd:
            CopyBackgroundPixels( 310, 180, GetScreenWidth(), 30/*Height*/ );
            DrawScreenString( 310, 180, "2084", 0x707070, GetFont("04B_19__.ttf", 70) );
            SetNextUpdateRect( 310, 180, GetScreenWidth(), 30/*Height*/ );

            CopyBackgroundPixels( 270, 280, GetScreenWidth(), 30/*Height*/ );
            DrawScreenString( 270, 280, "No more possible moves", 0x707070, GetFont("04B_19__.ttf", 20) );
            SetNextUpdateRect( 270, 280, GetScreenWidth(), 30/*Height*/ );

            CopyBackgroundPixels( 290, 310, GetScreenWidth(), 30/*Height*/ );
            DrawScreenString( 290, 310, "Press SPACE : Retry", 0x707070, GetFont("04B_19__.ttf", 20) );
            SetNextUpdateRect( 290, 310, GetScreenWidth(), 30/*Height*/ );

            CopyBackgroundPixels( 300, 340, GetScreenWidth(), 30/*Height*/ );
            DrawScreenString( 300, 340, "Press ESC : Menu", 0x707070, GetFont("04B_19__.ttf", 20) );
            SetNextUpdateRect( 300, 340, GetScreenWidth(), 30/*Height*/ );

            CopyBackgroundPixels( 340, 400, GetScreenWidth(), 30/*Height*/ );
            DrawScreenString( 340, 400, "Score:", 0x707070, GetFont("04B_19__.ttf", 20) );
            SetNextUpdateRect( 340, 400, GetScreenWidth(), 30/*Height*/ );

            CopyBackgroundPixels( 410, 400, GetScreenWidth(), 30/*Height*/ );
            DrawScreenString( 410, 400, itoa (score,buffer,10), 0x707070, GetFont("04B_19__.ttf", 20) );
            SetNextUpdateRect( 410, 400, GetScreenWidth(), 30/*Height*/ );

            CopyBackgroundPixels( 300, 370, GetScreenWidth(), 30/*Height*/ );
            DrawScreenString( 300, 370, "HighScore:", 0x707070, GetFont("04B_19__.ttf", 20) );
            SetNextUpdateRect( 300, 370, GetScreenWidth(), 30/*Height*/ );

            switch (levels){
            case 1:
                CopyBackgroundPixels( 410, 370, GetScreenWidth(), 30/*Height*/ );
                DrawScreenString( 410, 370, itoa (highscore1,buffer,10), 0x707070, GetFont("04B_19__.ttf", 20) );
                SetNextUpdateRect( 410, 370, GetScreenWidth(), 30/*Height*/ );
                break;

            case 2:
                CopyBackgroundPixels( 410, 370, GetScreenWidth(), 30/*Height*/ );
                DrawScreenString( 410, 370, itoa (highscore2,buffer,10), 0x707070, GetFont("04B_19__.ttf", 20) );
                SetNextUpdateRect( 410, 370, GetScreenWidth(), 30/*Height*/ );
                break;

            case 3:
                CopyBackgroundPixels( 410, 370, GetScreenWidth(), 30/*Height*/ );
                DrawScreenString( 410, 370, itoa (highscore3,buffer,10), 0x707070, GetFont("04B_19__.ttf", 20) );
                SetNextUpdateRect( 410, 370, GetScreenWidth(), 30/*Height*/ );
                break;
            }
            break;

        case stateWin:
            CopyBackgroundPixels( 310, 180, GetScreenWidth(), 30/*Height*/ );
            DrawScreenString( 310, 180, "2084", 0xFFFFFF, GetFont("04B_19__.ttf", 70) );
            SetNextUpdateRect( 310, 180, GetScreenWidth(), 30/*Height*/ );

            CopyBackgroundPixels( 340, 280, GetScreenWidth(), 30/*Height*/ );
            DrawScreenString( 340, 280, "You WON!", 0xFFFFFF, GetFont("04B_19__.ttf", 20) );
            SetNextUpdateRect( 340, 280, GetScreenWidth(), 30/*Height*/ );

            CopyBackgroundPixels( 300, 310, GetScreenWidth(), 30/*Height*/ );
            DrawScreenString( 300, 310, "Your score: ", 0xFFFFFF, GetFont("04B_19__.ttf", 20) );
            SetNextUpdateRect( 300, 310, GetScreenWidth(), 30/*Height*/ );

            CopyBackgroundPixels( 420, 310, GetScreenWidth(), 30/*Height*/ );
            DrawScreenString( 420, 310, itoa (score,buffer,10), 0xFFFFFF, GetFont("04B_19__.ttf", 20) );
            SetNextUpdateRect( 420, 310, GetScreenWidth(), 30/*Height*/ );

            CopyBackgroundPixels( 270, 340, GetScreenWidth(), 30/*Height*/ );
            DrawScreenString( 270, 340, "Press ESC : Main Menu", 0xFFFFFF, GetFont("04B_19__.ttf", 20) );
            SetNextUpdateRect( 270, 340, GetScreenWidth(), 30/*Height*/ );
            break;
	}
}

void main2048::drawTiles()
{
    int xStart = 80;
    int yStart = 100;

	// Set up the tiles
    int value = data[0][0];
    tiles.DrawTileAt(this, this->GetBackground(), 0, 0, xStart, yStart, value);
    xStart = xStart + 110;

    value = data[0][1];
    tiles.DrawTileAt(this, this->GetBackground(), 0, 0, xStart, yStart, value);
    xStart = xStart + 110;

    value = data[0][2];
    tiles.DrawTileAt(this, this->GetBackground(), 0, 0, xStart, yStart, value);
    xStart = xStart + 110;

    value = data[0][3];
    tiles.DrawTileAt(this, this->GetBackground(), 0, 0, xStart, yStart, value);
    xStart = 80;
    yStart = yStart + 110;

    value = data[1][0];
    tiles.DrawTileAt(this, this->GetBackground(), 0, 0, xStart, yStart, value);
    xStart = xStart + 110;

    value = data[1][1];
    tiles.DrawTileAt(this, this->GetBackground(), 0, 0, xStart, yStart, value);
    xStart = xStart + 110;

    value = data[1][2];
    tiles.DrawTileAt(this, this->GetBackground(), 0, 0, xStart, yStart, value);
    xStart = xStart + 110;

    value = data[1][3];
    tiles.DrawTileAt(this, this->GetBackground(), 0, 0, xStart, yStart, value);
    xStart = 80;
    yStart = yStart + 110;

    value = data[2][0];
    tiles.DrawTileAt(this, this->GetBackground(), 0, 0, xStart, yStart, value);
    xStart = xStart + 110;

    value = data[2][1];
    tiles.DrawTileAt(this, this->GetBackground(), 0, 0, xStart, yStart, value);
    xStart = xStart + 110;

    value = data[2][2];
    tiles.DrawTileAt(this, this->GetBackground(), 0, 0, xStart, yStart, value);
    xStart = xStart + 110;

    value = data[2][3];
    tiles.DrawTileAt(this, this->GetBackground(), 0, 0, xStart, yStart, value);
    xStart = 80;
    yStart = yStart + 110;

    value = data[3][0];
    tiles.DrawTileAt(this, this->GetBackground(), 0, 0, xStart, yStart, value);
    xStart = xStart + 110;

    value = data[3][1];
    tiles.DrawTileAt(this, this->GetBackground(), 0, 0, xStart, yStart, value);
    xStart = xStart + 110;

    value = data[3][2];
    tiles.DrawTileAt(this, this->GetBackground(), 0, 0, xStart, yStart, value);
    xStart = xStart + 110;

    value = data[3][3];
    tiles.DrawTileAt(this, this->GetBackground(), 0, 0, xStart, yStart, value);
}

int8_t main2048::findTarget(uint16_t array[4], int8_t x,int8_t stop) {
	int8_t t;
	// if the position is already on the first, don't evaluate
	if (x==0) {
		return x;
	}
	for(t=x-1;t>=0;t--) {
		if (array[t]!=0) {
			if (array[t]!=array[x]) {
				// merge is not possible, take next position
				return t+1;
			}
			return t;
		} else {
			// we should not slide further, return this one
			if (t==stop) {
				return t;
			}
		}
	}
	// we did not find a
	return x;
}

bool main2048::slideArray(uint16_t array[4]) {
	bool success = false;
	int8_t x,t,stop=0;

	for (x=0;x<4;x++) {
		if (array[x]!=0) {
			t = findTarget(array, x, stop);
			// if target is not original position, then move or merge
			if (t!=x) {
				// if target is not zero, set stop to avoid double merge
				if (array[t]!=0) {
					score+=array[t]+array[x];
					stop = t+1;
				}
				array[t]+=array[x];
				array[x]=0;
				success = true;
			}
		}
	}
	return success;
}

void main2048::rotateBoard() {
	int8_t i,j,n=4;
	uint16_t tmp;
	for (i=0; i<n/2; i++){
		for (j=i; j<n-i-1; j++){
			tmp = data[i][j];
			data[i][j] = data[j][n-i-1];
			data[j][n-i-1] = data[n-i-1][n-j-1];
			data[n-i-1][n-j-1] = data[n-j-1][i];
			data[n-j-1][i] = tmp;
		}
	}
}

bool main2048::moveLeft() {
	bool success = false;
	int8_t x;
	for (x=0;x<4;x++) {
		success |= slideArray(data[x]);
	}
	return success;
}

bool main2048::moveUp() {
	bool success;
	rotateBoard();
	success = moveLeft();
	rotateBoard();
	rotateBoard();
	rotateBoard();
	return success;
}

bool main2048::moveRight() {
	bool success;
	rotateBoard();
	rotateBoard();
	success = moveLeft();
	rotateBoard();
	rotateBoard();
	return success;
}

bool main2048::moveDown() {
	bool success;
	rotateBoard();
	rotateBoard();
	rotateBoard();
	success = moveLeft();
	rotateBoard();
	return success;
}

bool main2048::findPairDown() {
	bool success = false;
	int8_t x,y;
	for (x=0;x<4;x++) {
		for (y=0;y<4-1;y++) {
			if (data[x][y]==data[x][y+1]) return true;
		}
	}
	return success;
}

int16_t main2048::countEmpty() {
	int8_t x,y;
	int16_t count=0;
	for (x=0;x<4;x++) {
		for (y=0;y<4;y++) {
			if (data[x][y]==0) {
				count++;
			}
		}
	}
	return count;
}

void main2048::addRandom() {
	static bool initialized = false;
	int8_t x,y;
	int16_t r,len=0;
	uint16_t n,list[4*4][2];

	if (!initialized) {
		srand(time(NULL));
		initialized = true;
	}

	for (x=0;x<4;x++) {
		for (y=0;y<4;y++) {
			if (data[x][y]==0) {
				list[len][0]=x;
				list[len][1]=y;
				len++;
			}
		}
	}

	if (len>0) {
		r = rand()%len;
		x = list[r][0];
		y = list[r][1];
		n = ((rand()%10)/9+1)*2;
		data[x][y]=n;
	}
}

bool main2048::gameEnded() {
	bool ended = true;
	if (countEmpty()>0) return false;
	if (findPairDown()) return false;
	rotateBoard();
	if (findPairDown()) ended = false;
	rotateBoard();
	rotateBoard();
	rotateBoard();
	return ended;
}

void main2048::reset() {
    score = 0;
    for (int x=0;x<4;x++){
        for (int y=0;y<4;y++){
            data[x][y]=0;
        }
    }
}

void main2048::check() {
    switch (levels)
    {
        case 1:
            for (int x=0;x<4;x++){
                for (int y=0;y<4;y++){
                    if (data[x][y]==512)
                        m_state = stateWin;
                }
            }
            break;

        case 2:
            for (int x=0;x<4;x++){
                for (int y=0;y<4;y++){
                    if (data[x][y]==1024)
                        m_state = stateWin;
                }
            }
            break;

        case 3:
            for (int x=0;x<4;x++){
                for (int y=0;y<4;y++){
                    if (data[x][y]==2048)
                        m_state = stateWin;
                }
            }
            break;
    }
}

void main2048::updateHS() {
    switch (levels)
    {
        case 1:
            if (score>=highscore1)
                highscore1=score;
            break;

        case 2:
            if (score>=highscore2)
                highscore2=score;
            break;

        case 3:
            if (score>=highscore3)
                highscore3=score;
            break;
    }
}

void main2048::saveHS(){
    std::ofstream myfile;
    myfile.open ("highscore.txt");
    myfile << highscore1;
    myfile << "\n";
    myfile << highscore2;
    myfile << "\n";
    myfile << highscore3;
    myfile.close();
}

void main2048::loadHS(){
    std::ifstream file("highscore.txt");
    std::string str;
    std::string scores[3];

    for (int x=0;x<3 && std::getline(file, str);x++){
        scores[x] = str;
    }

    highscore1= atoi(scores[0].c_str());
    highscore2= atoi(scores[1].c_str());
    highscore3= atoi(scores[2].c_str());
}

void main2048::KeyDown(int iKeyCode)
{
    switch ( iKeyCode )
	{
        default:
            success = false;
            break;

        case SDLK_ESCAPE:
            switch ( m_state )
            {
                default:
                    success = false;
                    break;

                case stateMain:
                    reset();
                    m_state = stateInit;
                    success = false;
                    SetupBackgroundBuffer();
                    Redraw(true);
                    break;

                case statePaused:
                    m_state = stateMain;
                    success = false;
                    SetupBackgroundBuffer();
                    Redraw(true);
                    break;

                case stateWin:
                    m_state = stateInit;
                    success = false;
                    SetupBackgroundBuffer();
                    Redraw(true);
                    break;

                case stateEnd:
                    m_state = stateInit;
                    success = false;
                    SetupBackgroundBuffer();
                    Redraw(true);
                    break;
            }
            break;

        case SDLK_LEFT:
            switch ( m_state )
            {
                default:
                    success = false;
                    break;

                case stateMain:
                    success = moveLeft();
                    break;
            }
            break;

        case SDLK_RIGHT:
            switch ( m_state )
            {
                default:
                    success = false;
                    break;

                case stateMain:
                    success = moveRight();
                    break;
            }
            break;

        case SDLK_UP:
            switch ( m_state )
            {
                default:
                    success = false;
                    break;

                case stateMain:
                    success = moveUp();
                    break;
            }
            break;

        case SDLK_DOWN:
            switch ( m_state )
            {
                default:
                    success = false;
                    break;

                case stateMain:
                    success = moveDown();
                    break;
            }
            break;

        case SDLK_r:
            switch ( m_state )
            {
                default:
                    success = false;
                    break;

                case stateMain:
                    success = false;
                    reset();
                    addRandom();
                    addRandom();
                    SetupBackgroundBuffer();
                    Redraw(true);
                    break;
            }
            break;

        case SDLK_1:
            switch ( m_state )
            {
                default:
                    success = false;
                    break;

                case stateInit:
                    m_state = stateMain;
                    success = false;
                    reset();
                    addRandom();
                    addRandom();
                    levels = 1;
                    SetupBackgroundBuffer();
                    Redraw(true);
                    break;
            }
            break;

        case SDLK_2:
            switch ( m_state )
            {
                default:
                    success = false;
                    break;

                case stateInit:
                    m_state = stateMain;
                    success = false;
                    reset();
                    addRandom();
                    addRandom();
                    levels = 2;
                    SetupBackgroundBuffer();
                    Redraw(true);
                    break;
            }
            break;

        case SDLK_3:
            switch ( m_state )
            {
                default:
                    success = false;
                    break;

                case stateInit:
                    m_state = stateMain;
                    success = false;
                    reset();
                    addRandom();
                    addRandom();
                    levels = 3;
                    SetupBackgroundBuffer();
                    Redraw(true);
                    break;
            }
            break;

        case SDLK_SPACE:
            switch ( m_state )
            {
                default:
                    success = false;
                    break;

                case stateMain:
                    m_state = statePaused;
                    success = false;
                    SetupBackgroundBuffer();
                    Redraw(true);
                    break;

                case statePaused:
                    m_state = stateMain;
                    success = false;
                    SetupBackgroundBuffer();
                    Redraw(true);
                    break;

                case stateEnd:
                    m_state = stateMain;
                    reset();
                    addRandom();
                    addRandom();
                    success = false;
                    SetupBackgroundBuffer();
                    Redraw(true);
                    break;
            }
            break;
	}

	if (success)
    {
        updateHS();
        saveHS();
        check();
        addRandom();
        SetupBackgroundBuffer();
        Redraw(true);
        if (gameEnded())
        {
            m_state = stateEnd;
            SetupBackgroundBuffer();
            Redraw(true);
        }
    }

}
