// The engine / libraries that will be used for the game

#include "game.h"

#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
#include "world.h"

namespace roame {

Game* game_inst;
Game* get_game_instance() { return game_inst; };

Game::Game(Config& cfg)
    : sdl_data{}, active_world{new World()}, world_init{false} {
    // Set global game instance
    game_inst = this;

    // Set starting scene
    init_sdl(cfg, sdl_data);
}

void Game::run() {
    bool running = true;
    SDL_Event e;
    init();
    while (running) {
        engine_update();

        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }
    }

    SDL_DestroyWindow(sdl_data.window);
    IMG_Quit();
    SDL_Quit();
}

void Game::init_sdl(const Config& cfg, SDLData& sdl_data) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow(
        cfg.win_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        cfg.win_size.width, cfg.win_size.height, 0);

    SDL_Renderer* renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    // Store the sdl data
    sdl_data.window = window;
    sdl_data.renderer = renderer;
}

} // namespace roame