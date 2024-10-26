/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** SDL2
*/

#ifndef SDL2_HPP_
    #define SDL2_HPP_

    #include <SDL2/SDL.h>
    #include "IDisplay.hpp"

class Encapsulation {
    public:
        static int InitSDL() { return SDL_Init(SDL_INIT_VIDEO); }
        static int InitTTF() { return TTF_Init(); }

        static std::string GetError() { return std::string(SDL_GetError()); }

        static SDL_Window *CreateWindow(const std::string &title, int x, int y, int w, int h, Uint32 flags) { return SDL_CreateWindow(title.c_str(), x, y, w, h, flags); }      
        static SDL_Renderer *CreateRenderer(SDL_Window *window, int index, Uint32 flags) { return SDL_CreateRenderer(window, index, flags); }

        static void DestroyWindow(SDL_Window *window) { SDL_DestroyWindow(window); }
        static void DestroyRenderer(SDL_Renderer *renderer) { SDL_DestroyRenderer(renderer); }

        static void QuitSDL() { SDL_Quit(); }
        static void QuitTTF() { TTF_Quit(); }

        static void SetRenderDrawColor(SDL_Renderer *renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a) { SDL_SetRenderDrawColor(renderer, r, g, b, a); }
        static void RenderClear(SDL_Renderer *renderer) { SDL_RenderClear(renderer); }

        static TTF_Font *LoadFont(const std::string &file, int ptsize) { return TTF_OpenFont(file.c_str(), ptsize); }
        static SDL_Surface *RenderText_Solid(TTF_Font *font, const std::string &text, SDL_Color fg) { return TTF_RenderText_Solid(font, text.c_str(), fg); }
        static SDL_Texture *CreateTextureFromSurface(SDL_Renderer *renderer, SDL_Surface *surface) { return SDL_CreateTextureFromSurface(renderer, surface); }
        static int DrawLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2) { return SDL_RenderDrawLine(renderer, x1, y1, x2, y2); }
        static void RenderCopy(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_Rect *srcrect, const SDL_Rect *dstrect) { SDL_RenderCopy(renderer, texture, srcrect, dstrect); }
        static void FreeSurface(SDL_Surface *surface) { SDL_FreeSurface(surface); }
        static void DestroyTexture(SDL_Texture *texture) { SDL_DestroyTexture(texture); }
        static void CloseFont(TTF_Font *font) { TTF_CloseFont(font); }

        static SDL_Surface *LoadImage(const char *file) { return IMG_Load(file); }

        static void RenderPresent(SDL_Renderer *renderer) { SDL_RenderPresent(renderer); }

        static void GetWindowSize(SDL_Window *window, int *w, int *h) { SDL_GetWindowSize(window, w, h); }
        static bool PollEvent(SDL_Event &event) { return SDL_PollEvent(&event); }
        
};

class SDL2 : public IDisplay {
    public:
        /// @brief Constructor
        SDL2();

        /// @brief Destructor
        virtual ~SDL2();

        /// @brief Clear the window
        virtual void clearWindow();


        /// @brief Get the size of the window
        /// @return Coordinate The size of the window
        virtual Coordinate getSizeWindow() const;

        /// @brief Return all events detected by the display module
        /// @return Event::types The event detected
        virtual Event::types getEvent() const;

        /// @brief Display an asset on the display module
        /// @param std::vector<Asset> A map of asset to display with their position
        virtual void displayAssets(std::vector<Text> texts, std::vector<Asset> assets);

        /// @brief Get the resolution of the display module
        /// @return Coordinate The resolution of the display module
        virtual Coordinate getResolution() const;

    private:
        /// @brief Display text on the display module
        /// @param std::vector<Text> A map of text to display with their position
        void displayText(std::vector<Text> texts);

        /// @brief Display an asset on the display module
        /// @param std::vector<Asset> A map of asset to display with their position
        void displaySprite(std::vector<Asset> assets);
    
    private:
        /// @brief The X resolution of the display module
        const int RESOLUTION_X = 13;

        /// @brief The Y resolution of the display module
        const int RESOLUTION_Y = 20;



        /// @brief The deffault window size X
        const int WINDOW_SIZE_X = 85 * RESOLUTION_X;

        /// @brief The deffault window size Y
        const int WINDOW_SIZE_Y = 40 * RESOLUTION_Y;


        /// @brief The color of the text
        const SDL_Color C_NORMAL = {255, 255, 255, 255};

        /// @brief The color of the text selected
        const SDL_Color C_SELECTED = {82, 113, 255, 255};


        /// @brief The window of the display module
        SDL_Window *_window;

        /// @brief The renderer of the display module
        SDL_Renderer *_renderer;
};

#endif /* !SDL2_HPP_ */
