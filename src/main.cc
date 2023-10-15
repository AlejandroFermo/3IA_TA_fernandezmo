#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "esat/window.h"
#include "esat/draw.h"
#include "esat/input.h"
#include "esat/sprite.h"
#include "esat/time.h"
#include "../include/grid.h"
#include "../include/agent.h"

const unsigned int kWindowWidth = 800;
const unsigned int kWindowHeight = 600;

void RenderQuadWithVariables(float startingx, float startingy, float width, float height, float color[3]) {
    float p[] = {
        startingx, startingy,
        startingx + width, startingy,
        startingx + width, startingy + height,
        startingx, startingy + height,
        startingx, startingy
    };

    // Establecer el color del relleno según el valor del parámetro color
    esat::DrawSetFillColor(color[0], color[1], color[2]);

    esat::DrawSetStrokeColor(255, 255, 0, 255); // Color de borde

    esat::DrawSolidPath(p, 5, true);
}


int esat::main(int argc, char** argv) {
    srand(time(nullptr));
    double current_time = 0.0;
    double last_time = 0.0;
    double dt = 0.0;
    double fps = 60.0;
    esat::WindowInit(kWindowWidth, kWindowHeight);
    WindowSetMouseVisibility(true);

    // Crear un objeto Grid con las dimensiones adecuadas
    Grid* grid = Grid::CreateGrid(kWindowWidth / 40, kWindowHeight / 40); // 40 es el tamaño de cada cuadro del grid

    // Crear un objeto Agent y pasar el puntero al grid
    Agent agent(grid);

    last_time = esat::Time();

    while (!esat::IsSpecialKeyDown(esat::kSpecialKey_Escape) && esat::WindowIsOpened()) {
        dt = (esat::Time() - last_time) * 0.001f;
        last_time = esat::Time();

        esat::DrawBegin();
        esat::DrawClear(120, 120, 120);


        // Llama al método update del agente
        agent.update();

        _sleep(100);

        // Obtén la posición del objetivo desde el grid
        unsigned int targetX = 0, targetY = 0;
        grid->getTarget(targetX, targetY);

        

        // Dibujar el grid
        for (unsigned int x = 0; x < grid->width_; x++) {
            for (unsigned int y = 0; y < grid->height_; y++) {
                float color[] = { 0.0f, 0.0f, 255.0f }; // Color azul para casillas vacías
                if (grid->getTile(x, y).state == kOccupied) {
                    color[0] = 0.0f; // Color verde para el agente
                    color[1] = 255.0f;
                }
                else if (grid->getTile(x, y).state == kWall) {
                    // Utiliza el nuevo color para representar las paredes
                    color[0] = kWallColor[0];
                    color[1] = kWallColor[1];
                    color[2] = kWallColor[2];
                }

                // Dibuja la casilla
                float startingX = x * (kWindowWidth / grid->width_);
                float startingY = y * (kWindowHeight / grid->height_);
                float quadWidth = kWindowWidth / grid->width_;
                float quadHeight = kWindowHeight / grid->height_;
                RenderQuadWithVariables(startingX, startingY, quadWidth, quadHeight, color);
            }
        }
        // Dibujar el objetivo
        float targetColor[] = { 255.0f, 0.0f, 0.0f }; // Color rojo para el objetivo
        float targetXPos = targetX * (kWindowWidth / grid->width_);
        float targetYPos = targetY * (kWindowHeight / grid->height_);
        float targetWidth = kWindowWidth / grid->width_;
        float targetHeight = kWindowHeight / grid->height_;
        RenderQuadWithVariables(targetXPos, targetYPos, targetWidth, targetHeight, targetColor);

        esat::DrawEnd();
        esat::WindowFrame();

    }

    
    // Limpieza
    delete grid;
    esat::WindowDestroy();
    return 0;
}
