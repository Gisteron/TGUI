/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012-2014 Bruno Van de Velde (vdv_b@tgui.eu)
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


#ifndef TGUI_CHAT_BOX_HPP
#define TGUI_CHAT_BOX_HPP


#include <TGUI/Widget.hpp>
#include <TGUI/Panel.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    class Scrollbar;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class TGUI_API ChatBox : public Widget, public WidgetBorders
    {
      public:

        typedef SharedWidgetPtr<ChatBox> Ptr;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ChatBox();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Copy constructor
        ///
        /// \param copy  Instance to copy
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ChatBox(const ChatBox& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Virtual destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~ChatBox() {}


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Overload of assignment operator
        ///
        /// \param right  Instance to assign
        ///
        /// \return Reference to itself
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ChatBox& operator= (const ChatBox& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        // Makes a copy of the widget by calling the copy constructor.
        // This function calls new and if you use this function then you are responsible for calling delete.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ChatBox* clone() override
        {
            return new ChatBox(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Loads the widget.
        ///
        /// \param configFileFilename  Filename of the config file.
        ///
        /// \throw Exception when the config file couldn't be opened.
        /// \throw Exception when the config file didn't contain a "ChatBox" section with the needed information.
        /// \throw Exception when one of the images, described in the config file, couldn't be loaded.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void load(const std::string& configFileFilename);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the filename of the config file that was used to load the widget.
        ///
        /// \return Filename of loaded config file.
        ///         Empty string when no config file was loaded yet.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const std::string& getLoadedConfigFile() const
        {
            return m_loadedConfigFile;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the size of the chat box.
        ///
        /// This size does not include the borders.
        ///
        /// \param size   The new size of the chat box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(const sf::Vector2f& size) override;
        using Transformable::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the size of the chat box.
        ///
        /// This size does not include the borders.
        ///
        /// \return Size of the chat box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual sf::Vector2f getSize() const override
        {
            return m_panel->getSize();
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the full size of the chat box.
        ///
        /// This is the size including the borders.
        ///
        /// \return Full size of the chat box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual sf::Vector2f getFullSize() const override
        {
            return {getSize().x + m_borders.left + m_borders.right, getSize().y + m_borders.top + m_borders.bottom};
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Add a new line of text to the chat box.
        ///
        /// The whole text passed to this function will be considered as one line for the \a getLine and \a removeLine functions,
        /// even if it is too long and gets split over multiple lines.
        ///
        /// The default text color and character size will be used.
        ///
        /// \param text  Text that will be added to the chat box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void addLine(const sf::String& text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Add a new line of text to the chat box.
        ///
        /// The whole text passed to this function will be considered as one line for the \a getLine and \a removeLine functions,
        /// even if it is too long and gets split over multiple lines.
        ///
        /// The default text color will be used.
        ///
        /// \param text      Text that will be added to the chat box
        /// \param textSize  Size of the text
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void addLine(const sf::String& text, unsigned int textSize);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Add a new line of text to the chat box.
        ///
        /// The whole text passed to this function will be considered as one line for the \a getLine and \a removeLine functions,
        /// even if it is too long and gets split over multiple lines.
        ///
        /// The default character size will be used.
        ///
        /// \param text   Text that will be added to the chat box
        /// \param color  Color of the text
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void addLine(const sf::String& text, const sf::Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Add a new line of text to the chat box.
        ///
        /// The whole text passed to this function will be considered as one line for the \a getLine and \a removeLine functions,
        /// even if it is too long and gets split over multiple lines.
        ///
        /// \param text      Text that will be added to the chat box
        /// \param color     Color of the text
        /// \param textSize  Size of the text
        /// \param font      Font of the text (nullptr to use default font)
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void addLine(const sf::String& text, const sf::Color& color, unsigned int textSize, const sf::Font* font = nullptr);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the contents of the requested line.
        ///
        /// \param lineIndex  The index of the line of which you request the contents.
        ///                   The first line has index 0.
        ///
        /// \return The contents of the requested line.
        ///         An empty string will be returned when the index is too high.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::String getLine(unsigned int lineIndex);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Removes the requested line.
        ///
        /// \param lineIndex  The index of the line that should be removed.
        ///                   The first line has index 0.
        ///
        /// \return True if the line was removed, false if no such line existed (index too high).
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool removeLine(unsigned int lineIndex);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Removes all lines from the chat box.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeAllLines();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the amount of lines in the chat box.
        ///
        /// \return Number of lines in the chat box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getLineAmount()
        {
            return m_panel->getWidgets().size();
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set a maximum amount of lines in the chat box.
        ///
        /// Only the last \a maxLines lines will be kept. Lines above those will be removed.
        /// Set to 0 to disable the line limit (default).
        ///
        /// \param maxLines  The maximum amount of lines that the chat box can contain.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setLineLimit(unsigned int maxLines);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the default font of the text.
        ///
        /// When you don't call this function then the global font will be use.
        /// This global font can be changed with the setGlobalFont function from the parent.
        ///
        /// \param font  The new font
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextFont(const sf::Font& font);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the default font of the text.
        ///
        /// \return  Pointer to the font that is currently being used
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Font* getTextFont() const
        {
            return m_panel->getGlobalFont();
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the default character size of the text.
        ///
        /// \param size  The new default text size.
        ///              The minimum text size is 8.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextSize(unsigned int size);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the default character size of the text.
        ///
        /// \return The currently used default text size.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getTextSize() const
        {
            return m_textSize;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the default color of the text.
        ///
        /// \param color  The new default text color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextColor(const sf::Color& color)
        {
            m_textColor = color;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the default color of the text.
        ///
        /// \return The currently used default text color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getTextColor() const
        {
            return m_textColor;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the background color that will be used inside the chat box.
        ///
        /// \param backgroundColor  The new background color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBackgroundColor(const sf::Color& backgroundColor)
        {
            m_panel->setBackgroundColor(backgroundColor);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the border color that will be used inside the chat box.
        ///
        /// \param borderColor  The color of the borders
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBorderColor(const sf::Color& borderColor)
        {
            m_borderColor = borderColor;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the background color that is currently being used inside the chat box.
        ///
        /// \return The color of the background of the chat box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getBackgroundColor() const
        {
            return m_panel->getBackgroundColor();
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the border color that is currently being used inside the chat box.
        ///
        /// \return The color of the borders
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getBorderColor() const
        {
            return m_borderColor;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the line spacing of all lines.
        ///
        /// By default, line spacing is chosen based on the font and character size. This also means that when mixing different
        /// text styles in ChatBox, lines can have different line spacings.
        /// By calling this function, all line spacings will be set to the value passed to this function.
        ///
        /// The line spacing should be equal or greater than the text size to avoid overlapping lines.
        ///
        /// \param lineSpacing  New line spacing for all lines
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setLineSpacing(unsigned int lineSpacing);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the scrollbar of the chat box.
        ///
        /// \param scrollbarConfigFileFilename  Filename of the config file.
        ///                                     The config file must contain a Scrollbar section with the needed information.
        ///
        /// \throw Exception when the config file couldn't be opened.
        /// \throw Exception when the config file didn't contain a "Scrollbar" section with the needed information.
        /// \throw Exception when one of the images, described in the config file, couldn't be loaded.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setScrollbar(const std::string& scrollbarConfigFileFilename);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Removes the scrollbar from the chat box (if there is one).
        ///
        /// When there are too many lines to fit in the chat box then some lines will be removed.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeScrollbar();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the transparency of the widget.
        ///
        /// \param transparency  The transparency of the widget.
        ///                      0 is completely transparent, while 255 (default) means fully opaque.
        ///
        /// Note that this will only change the transparency of the images. The parts of the widgets that use a color will not
        /// be changed. You must change them yourself by setting the alpha channel of the color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setTransparency(unsigned char transparency) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool mouseOnWidget(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMousePressed(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMouseReleased(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseMoved(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseWheelMoved(int delta, int x, int y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseNotOnWidget() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseNoLongerDown() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        // This function is a (slow) way to set properties on the widget, no matter what type it is.
        // When the requested property doesn't exist in the widget then the functions will return false.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setProperty(std::string property, const std::string& value) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        // This function is a (slow) way to get properties of the widget, no matter what type it is.
        // When the requested property doesn't exist in the widget then the functions will return false.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void getProperty(std::string property, std::string& value) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        // Returns a list of all properties that can be used in setProperty and getProperty.
        // The second value in the pair is the type of the property (e.g. int, uint, string, ...).
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual std::list< std::pair<std::string, std::string> > getPropertyList() const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      private:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Retrieve the space of one of the lines.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getLineSpacing(unsigned int lineNumber);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        // This function is called when the widget is added to a container.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void initialize(Container *const parent) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        // Update the position of the labels.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateDisplayedText();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        // Draws the widget on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Defines specific triggers to ChatBox.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        enum ChatBoxCallbacks
        {
            AllChatBoxCallbacks = WidgetCallbacksCount - 1, ///< All triggers defined in ChatBox and its base classes
            ChatBoxCallbacksCount = WidgetCallbacksCount
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        std::string m_loadedConfigFile;

        unsigned int m_lineSpacing = 0;
        unsigned int m_textSize = 16;
        sf::Color m_textColor = sf::Color::Black;
        sf::Color m_borderColor = sf::Color::Black;

        unsigned int m_maxLines = 0;

        float m_fullTextHeight = 0;

        // The panel containing the labels
        Panel* m_panel = nullptr;

        // The scrollbar
        Scrollbar* m_scroll = nullptr;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_TEXT_BOX_HPP
