#include "../include/grid.h"
#include <stdio.h>
#include <cstdlib>
Grid::Grid(unsigned int w, unsigned int h) {
    width_ = w;
    height_ = h;
    tiles_ = new Tile[w * h];

    for (unsigned int row = 0; row < h; ++row) {
        for (unsigned int col = 0; col < w; ++col) {
            tiles_[col + row * w].state = kEmpty;
        }
    }
    for (unsigned int i = 0; i < w * h; ++i) {
        if (rand() % 10 == 0) { // Controla la probabilidad de que una casilla sea una pared (cuanto mayor menos paredes)
            tiles_[i].state = kWall;
        }
    }
    // Establece un objetivo en una posición específica (por ejemplo, en el centro)
   // Establece un objetivo en una posición aleatoria que no sea una pared
    unsigned int targetX, targetY;
    do {
        targetX = rand() % w;
        targetY = rand() % h;
    } while (tiles_[targetY * w + targetX].state == kWall);

    setTile(targetX, targetY, Tile{ kTarget });
}


Grid::~Grid()
{
    delete[] tiles_; // Liberar la memoria cuando se destruye el objeto
}

Grid* Grid::CreateGrid(unsigned int w, unsigned int h)
{
    if (w <= 0 || h <= 0)
    {
        return nullptr;
    }
    Grid* grid = new Grid(w, h);
    return grid;
}

Tile Grid::getTile(unsigned int x, unsigned int y)
{
    int index = y * width_ + x;
    return tiles_[index];
}

int Grid::freeTile(unsigned int x, unsigned int y)
{
    if (x >= width_ || y >= height_)
    {
        return kInvalidArgs; // Manejo de error para coordenadas inválidas
    }

    int index = y * width_ + x;
    if (tiles_[index].state != kOccupied)
    {
        return kTileAlreadyFreed; // Manejo de error para tiles ya libres
    }

    tiles_[index].state = kEmpty;
    return kOK;
}

int Grid::setTile(unsigned int x, unsigned int y, Tile tile) {
    if (x >= width_ || y >= height_) {
        return kInvalidArgs; // Manejo de error para coordenadas inválidas
    }

    int index = y * width_ + x;
    if (tiles_[index].state == kOccupied) {
        return kTileAlreadyOccupied; // Manejo de error para tiles ya ocupados
    }
    tiles_[index].state = tile.state;

    // Si el estado del tile es kTarget, establece el objetivo en esta casilla
    if (tile.state == kTarget) {
        // Asegúrate de que no haya otro objetivo antes de establecer uno nuevo
        for (unsigned int i = 0; i < width_ * height_; i++) {
            if (i != index && tiles_[i].state == kTarget) {
                tiles_[i].state = kEmpty; // Elimina el objetivo anterior
            }
        }
    }

    return kOK;
}

void Grid::getTarget(unsigned int& x, unsigned int& y)
{
    for (unsigned int i = 0; i < width_; i++) {
        for (unsigned int j = 0; j < height_; j++) {
            if (tiles_[j * width_ + i].state == kTarget) {
                x = i;
                y = j;
                
                return; // Se encontró el objetivo
            }
        }
    }
}
