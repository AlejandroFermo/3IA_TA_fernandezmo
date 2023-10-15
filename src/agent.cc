#include "../include/agent.h"
#include <cstdlib>
#include <stdio.h>

Agent::Agent(Grid* grid) : grid_(grid), x(0), y(0), extra(0) // Inicialización de miembros
{

}

Agent::~Agent()
{
    
}

void Agent::update() {
    unsigned int targetX, targetY;
    grid_->getTarget(targetX, targetY);

    // Mover el agente hacia el objetivo bloque por bloque (1 en x o y a la vez)

    if (x < targetX && grid_->getTile(x + 1, y).state != kWall) {
        // Intenta mover una casilla hacia la derecha si la siguiente casilla no es una pared
        grid_->freeTile(x, y);
        x++; 
    }
    else if (x > targetX && grid_->getTile(x - 1, y).state != kWall) {
        // Intenta mover una casilla hacia la izquierda si la siguiente casilla no es una pared
        grid_->freeTile(x, y);
        x--;
    }
    else if (y < targetY && grid_->getTile(x, y + 1).state != kWall) {
        // Intenta mover una casilla hacia abajo si la siguiente casilla no es una pared
        grid_->freeTile(x, y);
        y++;   
    }
    else if (y > targetY && grid_->getTile(x, y - 1).state != kWall) {
        // Intenta mover una casilla hacia arriba si la siguiente casilla no es una pared
        grid_->freeTile(x, y);
        y--;
    }
    else {
        // Está bloqueado por una pared, intenta rodear el obstáculo
        if (grid_->getTile(x - 1, y).state != kWall) {
            grid_->freeTile(x, y);
            x--;
        }
        else if (grid_->getTile(x + 1, y).state != kWall) {
            grid_->freeTile(x, y);
            x++;
        }
        else if (grid_->getTile(x, y - 1).state != kWall) {
            grid_->freeTile(x, y);
            y--;
        }
        else if (grid_->getTile(x, y + 1).state != kWall) {
            grid_->freeTile(x, y);
            y++;
        }
    }
    if (x == targetX && y == targetY) {
        // El agente ha alcanzado el objetivo, cambiar de lugar aleatoriamente
        grid_->freeTile(x, y); // Libera la casilla actual

       // Generar nuevas coordenadas aleatorias dentro del grid
        int aux_x, aux_y;
        do {
            aux_x = rand() % grid_->width_;
            aux_y = rand() % grid_->height_;
        } while (grid_->getTile(aux_x, aux_y).state == kWall); // Asegúrate de que el nuevo objetivo no esté en una pared

        // Ocupar la nueva casilla
        grid_->setTile(aux_x, aux_y, Tile{ kTarget });

    }
    else {
        grid_->setTile(x, y, Tile{ kOccupied }); // Ocupa la nueva casilla
    }
    if (x >= grid_->width_) {
        x = 0; // Establece x en la posición máxima permitida
    }
    if (y >= grid_->height_) {
        y = 0; // Establece y en la posición máxima permitida
    }
    if (x < 0) {
        x = 0; // Establece x en la posición mínima permitida
    }
    if (y < 0) {
        y = 0; // Establece y en la posición mínima permitida
    }
}

