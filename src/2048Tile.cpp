#include "header.h"
#include "2048Tile.h"

tile2048::tile2048(void)
{
}

tile2048::~tile2048(void)
{
}

// Get the size of a tile - width
int tile2048::GetTileWidth()
{
	return 100;
}

// Get the size of a tile - height
int tile2048::GetTileHeight()
{
	return 100;
}

void tile2048::DrawTileAt(
		BaseEngine* pEngine,
		SDL_Surface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY,
		int value )
{
	// Base class implementation just draws some grey tiles
	unsigned int iColour;

	unsigned int iColour0 = 0xD8D8D8;
	unsigned int iColour2 = 0xC8C8C8;
	unsigned int iColour4 = 0xB8B8B8;
	unsigned int iColour8 = 0xA8A8A8;
	unsigned int iColour16 = 0x989898;
	unsigned int iColour32 = 0x888888;
	unsigned int iColour64 = 0x787878;
	unsigned int iColour128 = 0x686868;
	unsigned int iColour256 = 0x585858;
	unsigned int iColour512 = 0x484848;
	unsigned int iColour1024 = 0x383838;
	unsigned int iColour2048 = 0x282828;

    switch(value)
    {
        default:
        case 0:
            iColour = iColour0;
            break;

        case 2:
            iColour = iColour2;
            break;

		case 4:
		    iColour = iColour4;
		    break;

        case 8:
            iColour = iColour8;
		    break;

        case 16:
            iColour = iColour16;
		    break;

        case 32:
            iColour = iColour32;
		    break;

        case 64:
            iColour = iColour64;
		    break;

        case 128:
            iColour = iColour128;
		    break;

        case 256:
            iColour = iColour256;
		    break;

        case 512:
            iColour = iColour512;
		    break;

        case 1024:
            iColour = iColour1024;
		    break;

        case 2048:
            iColour = iColour2048;
		    break;
    }

    pEngine->DrawRectangle(
		iStartPositionScreenX,
		iStartPositionScreenY,
		iStartPositionScreenX + GetTileWidth() - 1,
		iStartPositionScreenY + GetTileHeight() - 1,
		iColour,
		pSurface );

}
