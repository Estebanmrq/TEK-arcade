/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-esteban.marques
** File description:
** Allegro
*/

#include <memory>
#include <iostream>
#include "Allegro.hpp"

Allegro::Allegro()
{
    if (not Encapsulation::InitAllegro())
        throw IDisplay::Error("Initatlisation of Allegro5 failed");
    if (not Encapsulation::InitPrimitives())
        throw IDisplay::Error("Initatlisation of Allegro5 primitives failed");
    if (not Encapsulation::InitFont())
        throw IDisplay::Error("Initatlisation of Allegro5 font failed");
    if (not Encapsulation::InitTtf())
        throw IDisplay::Error("Initatlisation of Allegro5 ttf failed");
    if (not Encapsulation::InitImage())
        throw IDisplay::Error("Initatlisation of Allegro5 image failed");
    if (not Encapsulation::InstallKeyboard())
        throw IDisplay::Error("Initatlisation of Allegro5 keyboard failed");
    
    _window = Encapsulation::CreateWindow(WINDOW_SIZE_X, WINDOW_SIZE_Y);
    if (not _window)
        throw IDisplay::Error("Initatlisation of Allegro5 _window failed");
    Encapsulation::SetWindowTitle(_window, "Arcade");

    _queue = Encapsulation::CreateEventQueue();
    if (not _queue)
        throw IDisplay::Error("Initatlisation of Allegro5 event queue failed");

    Encapsulation::RegisterEventSource(_queue, al_get_display_event_source(_window));
    Encapsulation::RegisterEventSource(_queue, al_get_keyboard_event_source());
    Encapsulation::SetStandardFileInterface();
}

Allegro::~Allegro()
{
    Encapsulation::DestroyEventQueue(_queue);
    Encapsulation::DestroyDisplay(_window);
    Encapsulation::UninstallKeyboard();
    Encapsulation::ShutdownImageAddon();
    Encapsulation::ShutdownTtfAddon();
    Encapsulation::ShutdownFontAddon();
    Encapsulation::ShutdownPrimitivesAddon();
    Encapsulation::UninstallSystem();
}

void Allegro::clearWindow()
{
    Encapsulation::ClearWindow();
}

void Allegro::displayText(const std::vector<Text> &texts)
{
    for (auto text : texts) {
        ALLEGRO_FONT *font = Encapsulation::LoadFont ("assets/graphical/ARCADE_R.TTF", 12);
        if (not font)
            throw IDisplay::Error("Initialization of Allegro5 font failed");
        Encapsulation::DrawText(font, text.getIsSelected() ? al_map_rgb(82, 113, 255) : al_map_rgb(255, 255, 255), text.getCoord().getX(), text.getCoord().getY(), 0, text.getText().c_str());
        Encapsulation::DestroyFont(font);
    }
}

void Allegro::displaySprite(const std::vector<Asset> &assets)
{
    for (auto asset : assets) {
        ALLEGRO_BITMAP *sprite = Encapsulation::LoadBitmap(asset.getFormat().getFile().c_str());
    
        if (sprite == nullptr)
            throw IDisplay::Error("Initialization of Allegro5 sprite '" + asset.getFormat().getFile() + "' failed");
        
        Encapsulation::DrawBitmap(sprite, asset.getPosition(), asset.getSize(), 0);
        Encapsulation::DestroyBitmap(sprite);
    }
}


void Allegro::displayAssets(std::vector<Text> texts, std::vector<Asset> assets)
{
    clearWindow();
    displayText(texts);
    displaySprite(assets);

    Encapsulation::Refresh();
}

Coordinate Allegro::getSizeWindow() const
{
    return Coordinate(Encapsulation::GetWindowWidth(_window), Encapsulation::GetWindowHeight(_window));
}

Event::types Allegro::getEvent() const
{
    ALLEGRO_EVENT event;

    if (!Encapsulation::GetEvent(_queue, event))
        return Event::types::UNKNOWN;
    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return Event::types::QUIT;
    }
    if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
                return Event::types::ESCAPE;
            case ALLEGRO_KEY_UP:
                return Event::types::UP;
            case ALLEGRO_KEY_DOWN:
                return Event::types::DOWN;
            case ALLEGRO_KEY_LEFT:
                return Event::types::LEFT;
            case ALLEGRO_KEY_RIGHT:
                return Event::types::RIGHT;
            case ALLEGRO_KEY_ENTER:
                return Event::types::ENTER;
            case ALLEGRO_KEY_SPACE:
                return Event::types::SPACE;
            case ALLEGRO_KEY_BACKSPACE:
                return Event::types::BACKSPACE;
            case ALLEGRO_KEY_A:
                return Event::types::A;
            case ALLEGRO_KEY_B:
                return Event::types::B;
            case ALLEGRO_KEY_C:
                return Event::types::C;
            case ALLEGRO_KEY_D:
                return Event::types::D;
            case ALLEGRO_KEY_E:
                return Event::types::E;
            case ALLEGRO_KEY_F:
                return Event::types::F;
            case ALLEGRO_KEY_G:
                return Event::types::G;
            case ALLEGRO_KEY_H:
                return Event::types::H;
            case ALLEGRO_KEY_I:
                return Event::types::I;
            case ALLEGRO_KEY_J:
                return Event::types::J;
            case ALLEGRO_KEY_K:
                return Event::types::K;
            case ALLEGRO_KEY_L:
                return Event::types::L;
            case ALLEGRO_KEY_M:
                return Event::types::M;
            case ALLEGRO_KEY_N:
                return Event::types::N;
            case ALLEGRO_KEY_O:
                return Event::types::O;
            case ALLEGRO_KEY_P:
                return Event::types::P;
            case ALLEGRO_KEY_Q:
                return Event::types::Q;
            case ALLEGRO_KEY_R:
                return Event::types::R;
            case ALLEGRO_KEY_S:
                return Event::types::S;
            case ALLEGRO_KEY_T:
                return Event::types::T;
            case ALLEGRO_KEY_U:
                return Event::types::U;
            case ALLEGRO_KEY_V:
                return Event::types::V;
            case ALLEGRO_KEY_W:
                return Event::types::W;
            case ALLEGRO_KEY_X:
                return Event::types::X;
            case ALLEGRO_KEY_Y:
                return Event::types::Y;
            case ALLEGRO_KEY_Z:
                return Event::types::Z;
            case ALLEGRO_KEY_F2:
                return Event::types::F2;
            case ALLEGRO_KEY_F3:
                return Event::types::F3;
            case ALLEGRO_KEY_F4:
                return Event::types::F4;
            case ALLEGRO_KEY_F5:
                return Event::types::F5;
            case ALLEGRO_KEY_F6:
                return Event::types::F6;
            default:
                return Event::types::UNKNOWN;
        }
    }
    return Event::types::UNKNOWN;
}

Coordinate Allegro::getResolution() const
{
    return Coordinate{RESOLUTION_X, RESOLUTION_Y};
}

extern "C" std::unique_ptr<IDisplay> getInstance()
{
    return std::make_unique<Allegro>();
}
