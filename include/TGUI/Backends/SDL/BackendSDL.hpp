/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2021 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TGUI_BACKEND_SDL_HPP
#define TGUI_BACKEND_SDL_HPP

#include <TGUI/Backend.hpp>
#include <map>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

union SDL_Event;
struct SDL_Window;
struct SDL_Cursor;
typedef unsigned int GLuint;

namespace tgui
{
    class GuiSDL;
    class BackendRenderTargetSDL;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Backend that uses SDL
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API BackendSDL : public BackendBase
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Helper function that converts an SDL event to a TGUI event
        /// @param eventSFML  The input SDL event
        /// @param eventTGUI  The output TGUI event
        /// @return Did the SDL event match on a TGUI event and has the output event been written to?
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static bool convertEvent(const SDL_Event& eventSDL, Event& eventTGUI);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        BackendSDL();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ~BackendSDL();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Informs the backend that a new gui object has been created.
        /// @param gui  Newly created gui
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void attachGui(GuiBase* gui) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Informs the backend that a gui object is being destroyed.
        /// @param gui  Gui object that is about to be deconstructed
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void detatchGui(GuiBase* gui) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates and returns the default font for all widgets
        /// @return Default font
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Font createDefaultFont() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a new font object
        /// @return Font that is specific to the backend
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::shared_ptr<BackendFontBase> createFont() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a new text object
        /// @return Text that is specific to the backend
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::shared_ptr<BackendTextBase> createText() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a new texture object
        /// @return Texture that is specific to the backend
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::shared_ptr<BackendTextureBase> createTexture() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the look of a certain mouse cursor by using a bitmap
        ///
        /// @param type    Cursor that should make use of the bitmap
        /// @param pixels  Pointer to an array with 4*size.x*size.y elements, representing the pixels in 32-bit RGBA format
        /// @param size    Size of the cursor
        /// @param hotspot Pixel coordinate within the cursor image which will be located exactly at the mouse pointer position
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMouseCursorStyle(Cursor::Type type, const std::uint8_t* pixels, Vector2u size, Vector2u hotspot) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the look of a certain mouse cursor back to the system theme
        ///
        /// @param type  Cursor that should no longer use a custom bitmap
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void resetMouseCursorStyle(Cursor::Type type) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the mouse cursor when the mouse is on top of the window to which the gui is attached
        ///
        /// @param gui   The gui that represents the window for which the mouse cursor should be changed
        /// @param type  Which cursor to use
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMouseCursor(GuiBase* gui, Cursor::Type type) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Opens the virtual keyboard on Android and iOS
        /// @param inputRect Part of the screen where the text input is located
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void openVirtualKeyboard(const FloatRect& inputRect) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Closes the virtual keyboard on Android and iOS
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void closeVirtualKeyboard() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Checks the state for one of the modifier keys
        ///
        /// @param modifierKey  The modifier key of which the state is being queried
        ///
        /// @return Whether queries modifier key is being pressed
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool isKeyboardModifierPressed(Event::KeyModifier modifierKey) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the contents of the clipboard
        ///
        /// @param contents  New contents of the clipboard
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setClipboard(const String& contents) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the contents of the clipboard
        ///
        /// @return Clipboard contents
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        String getClipboard() const override;

#ifdef TGUI_SYSTEM_ANDROID
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Uses the AssetManager on Android to read a file and return its contents
        ///
        /// @param filename      Filename of the file to read
        /// @param fileContents  Reference to empty string stream that will be filled with the contents of the file on success
        ///
        /// @return True if the file was successfully read. False on failure or if platform isn't Android.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool readFileFromAndroidAssets(const String& filename, std::stringstream& fileContents) const override;
#endif

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the SDL window to which the gui will render and returns a new render target object to interact with
        ///
        /// @param gui     The gui for which the render target should be created
        /// @param window  SDL window to draw on
        ///
        /// @return Render target that abstracts the SDL drawing code
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::shared_ptr<BackendRenderTargetSDL> createGuiRenderTarget(GuiSDL* gui, SDL_Window* window);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the bound texture if another texture was currently set
        ///
        /// @param textureId  Texture to pass to glBindTexture
        /// @param force      Call glBindTexture even if the id was still the same. This is required when calling this function
        ///                   after creating a new texture, as it could be reusing the id that was previously cached.
        ///
        /// This function has to be used instead of glBindTexture so that the backend knows the last used texture
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void changeTexture(GLuint textureId, bool force);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Helper function to create a system cursor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        SDL_Cursor* createSystemCursor(Cursor::Type type);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Helper function to update the mouse cursors on all attached guis
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateMouseCursorStyle(Cursor::Type type, SDL_Cursor* cursor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Helper function to update the mouse cursor on a window
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateShownMouseCursor(SDL_Window* window, Cursor::Type type);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

        struct GuiResources
        {
            SDL_Window* window = nullptr;
            Cursor::Type mouseCursor = Cursor::Type::Arrow;
        };

        std::map<GuiBase*, GuiResources> m_guis;
        std::map<Cursor::Type, SDL_Cursor*> m_mouseCursors;

        GLuint m_currentTexture = 0;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_BACKEND_SDL_HPP
