#pragma once

enum TileState
{
    kInvalid,
    kEmpty,
    kTarget,
    kOccupied,
    kWall, // Nuevo estado para las paredes
};

const float kWallColor[] = { 128.0f, 128.0f, 128.0f };


struct Tile
{
    TileState state;
};

enum Error
{
    kOK = 0,
    kTileAlreadyFreed,
    kTileAlreadyOccupied, 
    kInvalidArgs
    // ...
};

class Grid
{
private:
    Grid(unsigned int w, unsigned int h);

    

public:
    ~Grid();

    static Grid* CreateGrid(unsigned int w, unsigned int h);

    Tile getTile(unsigned int x, unsigned int y);
    int freeTile(unsigned int x, unsigned int y);
    int setTile(unsigned int x, unsigned int y, Tile tile = Tile{ kEmpty });
    void getTarget(unsigned int& x, unsigned int& y);
    unsigned int width_;
    unsigned int height_;
    Tile* tiles_;
};
