/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-esteban.marques
** File description:
** Allegro
*/

#ifndef ALLEGRO_HPP_
    #define ALLEGRO_HPP_
    #include <allegro5/allegro.h>
    #include <allegro5/allegro_primitives.h>
    #include <allegro5/allegro_font.h>
    #include <allegro5/allegro_ttf.h>
    #include <allegro5/allegro_image.h>
    #include "Clock.hpp"
    #include "IDisplay.hpp"

class Encapsulation {
    public:
        static bool InitAllegro() { return al_init(); }
        static bool InitPrimitives() { return al_init_primitives_addon(); }
        static bool InitFont() { return al_init_font_addon(); }
        static bool InitTtf() { return al_init_ttf_addon(); }
        static bool InitImage() { return al_init_image_addon(); }
        static bool InstallKeyboard() { return al_install_keyboard(); }
        static ALLEGRO_DISPLAY *CreateWindow(int w, int h) { return al_create_display(w, h); }
        static void SetWindowTitle(ALLEGRO_DISPLAY *display, const std::string &title) { al_set_window_title(display, title.c_str()); }
        static ALLEGRO_EVENT_QUEUE *CreateEventQueue() { return al_create_event_queue(); }
        static void RegisterEventSource(ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_EVENT_SOURCE *source) { al_register_event_source(queue, source); }
        static void SetStandardFileInterface() { al_set_standard_file_interface(); }

        static void DestroyEventQueue(ALLEGRO_EVENT_QUEUE *queue) { al_destroy_event_queue(queue); }
        static void DestroyDisplay(ALLEGRO_DISPLAY *display) { al_destroy_display(display); }
        static void DestroyFont(ALLEGRO_FONT *font) { al_destroy_font(font); }
        static void DestroyBitmap(ALLEGRO_BITMAP *bitmap) { al_destroy_bitmap(bitmap); }

        static void ShutdownImageAddon() { al_shutdown_image_addon(); }
        static void ShutdownTtfAddon() { al_shutdown_ttf_addon(); }
        static void ShutdownFontAddon() { al_shutdown_font_addon(); }
        static void ShutdownPrimitivesAddon() { al_shutdown_primitives_addon(); }
        static void UninstallKeyboard() { al_uninstall_keyboard(); }
        static void UninstallSystem() { al_uninstall_system(); }

        static void ClearWindow() { al_clear_to_color(al_map_rgb(0, 0, 0)); }

        static ALLEGRO_FONT *LoadFont(const std::string &path, int size) { return al_load_font(path.c_str(), size, 0); }
        static void DrawText(ALLEGRO_FONT *font, ALLEGRO_COLOR color, float x, float y, int flags, const std::string &text) { al_draw_text(font, color, x, y, flags, text.c_str()); }

        static ALLEGRO_BITMAP *LoadBitmap(const std::string &path) { return al_load_bitmap(path.c_str()); }
        static void DrawBitmap(ALLEGRO_BITMAP *bitmap, Coordinate coordinate, Coordinate size, int flags) { al_draw_scaled_bitmap(bitmap, 0, 0, al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap), coordinate.getX(), coordinate.getY(), size.getX(), size.getY(), flags); }

        static void Refresh() { al_flip_display(); }
        static int GetWindowWidth(ALLEGRO_DISPLAY *display) { return al_get_display_width(display); }
        static int GetWindowHeight(ALLEGRO_DISPLAY *display) { return al_get_display_height(display); }

        static bool GetEvent(ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_EVENT &event) { return al_wait_for_event_timed(queue, &event, 0.0001); }
};

class Allegro : public IDisplay {
    public:
        /// @brief Constructor
        Allegro();
        
        /// @brief Destructor
        virtual ~Allegro();

        /// @brief Clear the window
        virtual void clearWindow();

        /// @brief Display an asset on the display module
        /// @param std::vector<Asset> A map of asset to display with their position
        virtual void displayAssets(std::vector<Text> texts, std::vector<Asset> assets);

        /// @brief Get the size of the window
        /// @return Coordinate The size of the window
        virtual Coordinate getSizeWindow() const;

        /// @brief Return all events detected by the display module
        /// @return Event::types The event detected
        virtual Event::types getEvent() const;

        /// @brief Get the resolution of the display module
        /// @return Coordinate The resolution of the display module
        virtual Coordinate getResolution() const;

    private:
        /// @brief The X resolution of the display module
        const int RESOLUTION_X = 13;

        /// @brief The Y resolution of the display module
        const int RESOLUTION_Y = 20;


        /// @brief The deffault window size X
        const int WINDOW_SIZE_X = 100 * RESOLUTION_X;

        /// @brief The deffault window size Y
        const int WINDOW_SIZE_Y = 45 * RESOLUTION_Y;

        void displayText(const std::vector<Text> &texts);
        void displaySprite(const std::vector<Asset> &assets);

        ALLEGRO_DISPLAY *_window;
        ALLEGRO_EVENT_QUEUE *_queue;
};

#endif /* !ALLEGRO_HPP_ */
