/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** SDL2
*/

#include <memory>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>
#include "SDL2.hpp"

SDL2::SDL2()
{
    if (Encapsulation::InitSDL() || Encapsulation::InitTTF())
        throw IDisplay::Error("SDL2: Failed to initialize: " + Encapsulation::GetError());

    _window = Encapsulation::CreateWindow("Arcade", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_SIZE_X, WINDOW_SIZE_Y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (_window == nullptr)
        throw IDisplay::Error("SDL2: Failed to create window: " + Encapsulation::GetError());

    _renderer = Encapsulation::CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
        if (_renderer == nullptr)
            throw IDisplay::Error("SDL2: Failed to create renderer: " + Encapsulation::GetError());
    
    clearWindow();
}

SDL2::~SDL2()
{
    if (_window)
        Encapsulation::DestroyWindow(_window);
    if (_renderer)
        Encapsulation::DestroyRenderer(_renderer);
    Encapsulation::QuitTTF();
    Encapsulation::QuitSDL();
}

Coordinate SDL2::getResolution() const
{
    return Coordinate(RESOLUTION_X, RESOLUTION_Y);
}

void SDL2::clearWindow()
{
    Encapsulation::SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    Encapsulation::RenderClear(_renderer);
}

void SDL2::displayText(std::vector<Text> texts)
{
    TTF_Font *font = Encapsulation::LoadFont("assets/graphical/ARCADE_R.TTF", 12);
    if (font == nullptr)
        throw IDisplay::Error("SDL2: Failed to load font: " + Encapsulation::GetError());

    for (auto text : texts) {
        SDL_Surface *surface = Encapsulation::RenderText_Solid(font, text.getText(), text.getIsSelected() ? C_SELECTED : C_NORMAL);
        if (surface == nullptr)
            throw IDisplay::Error("SDL2: Failed to render text: " + Encapsulation::GetError());
        SDL_Texture *texture = Encapsulation::CreateTextureFromSurface(_renderer, surface);
        if (texture == nullptr)
            throw IDisplay::Error("SDL2: Failed to create texture: " + Encapsulation::GetError());

        SDL_Rect rect = {text.getCoord().getX(), text.getCoord().getY(), surface->w, surface->h};
        if (text.getIsSelected()) {
            Encapsulation::SetRenderDrawColor(_renderer, C_SELECTED.r, C_SELECTED.g, C_SELECTED.b, C_SELECTED.a);
            Encapsulation::DrawLine(_renderer, rect.x, rect.y + rect.h, rect.x + rect.w, rect.y + rect.h);
        }
        Encapsulation::RenderCopy(_renderer, texture, NULL, &rect);
        Encapsulation::FreeSurface(surface);
        Encapsulation::DestroyTexture(texture);
    }
    Encapsulation::CloseFont(font);
}

void SDL2::displaySprite(std::vector<Asset> assets)
{
    for (auto asset : assets) {
        SDL_Surface *surface = Encapsulation::LoadImage(asset.getFormat().getFile().c_str());
        if (surface == nullptr)
            throw IDisplay::Error("SDL2: Failed to load image: " + Encapsulation::GetError());
        
        SDL_Texture *texture = Encapsulation::CreateTextureFromSurface(_renderer, surface);
        if (texture == nullptr)
            throw IDisplay::Error("SDL2: Failed to create texture: " + Encapsulation::GetError());
    
        SDL_Rect rect = {asset.getPosition().getX(), asset.getPosition().getY(), asset.getSize().getX(), asset.getSize().getY()};

        Encapsulation::RenderCopy(_renderer, texture, NULL, &rect);
        Encapsulation::FreeSurface(surface);
        Encapsulation::DestroyTexture(texture);
    }
}

void SDL2::displayAssets(std::vector<Text> texts, std::vector<Asset> assets)
{
    clearWindow();
    displayText(texts);
    displaySprite(assets);

    Encapsulation::RenderPresent(_renderer);
}

Coordinate SDL2::getSizeWindow() const
{
    int width = 0;
    int height = 0;

    Encapsulation::GetWindowSize(_window, &width, &height);
    return Coordinate(width, height);
}
Event::types SDL2::getEvent() const
{
    SDL_Event event;

    if (Encapsulation::PollEvent(event)) {
        if (event.type == SDL_QUIT) {
            return Event::types::QUIT;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    return Event::types::UP;
                case SDLK_DOWN:
                    return Event::types::DOWN; 
                case SDLK_RIGHT:
                    return Event::types::RIGHT;
                case SDLK_LEFT:
                    return Event::types::LEFT;
                case SDLK_RETURN:
                    return Event::types::ENTER;
                case SDLK_ESCAPE:
                    return Event::types::ESCAPE;
                case SDLK_SPACE:
                    return Event::types::SPACE;
                case SDLK_BACKSPACE:
                    return Event::types::BACKSPACE;
                case SDLK_a:
                    return Event::types::A;
                case SDLK_b:
                    return Event::types::B;
                case SDLK_c:
                    return Event::types::C;
                case SDLK_d:
                    return Event::types::D;
                case SDLK_e:
                    return Event::types::E;
                case SDLK_f:
                    return Event::types::F;
                case SDLK_g:
                    return Event::types::G;
                case SDLK_h:
                    return Event::types::H;
                case SDLK_i:
                    return Event::types::I;
                case SDLK_j:
                    return Event::types::J;
                case SDLK_k:
                    return Event::types::K;
                case SDLK_l:
                    return Event::types::L;
                case SDLK_m:
                    return Event::types::M;
                case SDLK_n:
                    return Event::types::N;
                case SDLK_o:
                    return Event::types::O;
                case SDLK_p:
                    return Event::types::P;
                case SDLK_q:
                    return Event::types::Q;
                case SDLK_r:
                    return Event::types::R;
                case SDLK_s:
                    return Event::types::S;
                case SDLK_t:
                    return Event::types::T;
                case SDLK_u:
                    return Event::types::U;
                case SDLK_v:
                    return Event::types::V;
                case SDLK_w:
                    return Event::types::W;
                case SDLK_x:
                    return Event::types::X;
                case SDLK_y:
                    return Event::types::Y;
                case SDLK_z:
                    return Event::types::Z;
                case SDLK_F2:
                    return Event::types::F2;
                case SDLK_F3:
                    return Event::types::F3;
                case SDLK_F4:
                    return Event::types::F4;
                case SDLK_F5:
                    return Event::types::F5;
                case SDLK_F6:
                    return Event::types::F6;
                default:
                    return Event::types::UNKNOWN;
            }
        } else {
            return Event::types::UNKNOWN;
        }
    }
    return Event::types::UNKNOWN;
}

extern "C" std::unique_ptr<IDisplay> getInstance()
{
    return std::make_unique<SDL2>();
}
