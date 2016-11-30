#include <cstdio>
#include <iostream>

#include <GL/gl3w.h>
#include <SDL.h>

#include "renderer.h"
#include "scene.h"

extern "C" int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);

    SDL_Window *window = SDL_CreateWindow(
        "opengl-playground", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window) {
        fprintf(stderr, "SDL_CreateWindow: %s\n", SDL_GetError());
        exit(1);
    }

    Uint32 windowID = SDL_GetWindowID(window);

    SDL_GLContext glctx = SDL_GL_CreateContext(window);

    if (!glctx) {
        fprintf(stderr, "SDL_GL_CreateContext: %s\n", SDL_GetError());
        exit(1);
    }

    gl3wInit();

    Scene scene;
    scene.init();

    std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
    renderer->init(&scene);

    // Initial resize
    {
        int initialWidth, initialHeight;
        SDL_GL_GetDrawableSize(window, &initialWidth, &initialHeight);
        renderer->resize(initialWidth, initialHeight);
    }

    while (true) {
        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) {
                goto mainloop_end;
            } else if (ev.type == SDL_WINDOWEVENT) {
                if (ev.window.windowID == windowID) {
                    if (ev.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                        renderer->resize(ev.window.data1, ev.window.data2);
                    }
                }
            } else if (ev.type == SDL_KEYDOWN) {
                if (ev.key.keysym.sym == SDLK_RETURN) {
                    if (ev.key.keysym.mod & KMOD_ALT) {
                        Uint32 wflags = SDL_GetWindowFlags(window);
                        if (wflags & SDL_WINDOW_FULLSCREEN_DESKTOP) {
                            SDL_SetWindowFullscreen(window, 0);
                        } else {
                            SDL_SetWindowFullscreen(
                                window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                        }
                    }
                }
                if (ev.key.keysym.sym == SDLK_SPACE) {
                    renderer->toggleWireFrame();
                }
            }
        }

        renderer->paint();

        SDL_GL_SwapWindow(window);
    }
mainloop_end:

    return 0;
}
