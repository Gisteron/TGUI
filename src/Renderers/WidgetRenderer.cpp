/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2022 Bruno Van de Velde (vdv_b@tgui.eu)
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


#include <TGUI/Renderers/WidgetRenderer.hpp>
#include <TGUI/RendererDefines.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    std::shared_ptr<RendererData> RendererData::create(const std::map<String, ObjectConverter>& init)
    {
        auto data = std::make_shared<RendererData>();
        data->propertyValuePairs = init;
        return data;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::shared_ptr<RendererData> RendererData::createFromDataIONode(const DataIO::Node* rendererNode)
    {
        auto rendererData = std::make_shared<RendererData>();
        rendererData->shared = false;

        for (const auto& pair : rendererNode->propertyValuePairs)
            rendererData->propertyValuePairs[pair.first] = ObjectConverter(pair.second->value); // Did not compile with VS2015 Update 2 when using braces

        for (const auto& nestedProperty : rendererNode->children)
        {
            std::stringstream ss;
            DataIO::emit(nestedProperty, ss);
            rendererData->propertyValuePairs[nestedProperty->name] = {String("{\n" + ss.str() + "}")};
        }

        return rendererData;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    TGUI_RENDERER_PROPERTY_BOOL(WidgetRenderer, TransparentTexture, false)

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    TGUI_RENDERER_PROPERTY_GET_NUMBER(WidgetRenderer, Opacity, 1)

    void WidgetRenderer::setOpacity(float opacity)
    {
        setProperty("Opacity", ObjectConverter{std::max(0.f, std::min(1.f, opacity))});
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    TGUI_RENDERER_PROPERTY_GET_NUMBER(WidgetRenderer, OpacityDisabled, -1)

    void WidgetRenderer::setOpacityDisabled(float opacity)
    {
        if (opacity != -1.f)
            setProperty("OpacityDisabled", ObjectConverter{std::max(0.f, std::min(1.f, opacity))});
        else
            setProperty("OpacityDisabled", ObjectConverter{-1.f});
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void WidgetRenderer::setFont(Font font)
    {
        setProperty("Font", font);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Font WidgetRenderer::getFont() const
    {
        auto it = m_data->propertyValuePairs.find("Font");
        if (it != m_data->propertyValuePairs.end())
            return it->second.getFont();
        else
            return {};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void WidgetRenderer::setTextSize(unsigned int size)
    {
        setProperty("TextSize", static_cast<float>(size));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int WidgetRenderer::getTextSize() const
    {
        auto it = m_data->propertyValuePairs.find("TextSize");
        if (it != m_data->propertyValuePairs.end())
            return static_cast<unsigned int>(it->second.getNumber());
        else
            return 0;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void WidgetRenderer::setProperty(const String& property, ObjectConverter&& value)
    {
        if (m_data->propertyValuePairs[property] == value)
            return;

        const ObjectConverter oldValue = m_data->propertyValuePairs[property];
        m_data->propertyValuePairs[property] = value;

        try
        {
            for (const auto& observer : m_data->observers)
                observer.second(property);
        }
        catch (const Exception&)
        {
            m_data->propertyValuePairs[property] = oldValue;
            throw;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ObjectConverter WidgetRenderer::getProperty(const String& property) const
    {
        auto it = m_data->propertyValuePairs.find(property);
        if (it != m_data->propertyValuePairs.end())
            return it->second;
        else
            return {};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const std::map<String, ObjectConverter>& WidgetRenderer::getPropertyValuePairs() const
    {
        return m_data->propertyValuePairs;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void WidgetRenderer::subscribe(const void* id, const std::function<void(const String& property)>& function)
    {
        m_data->observers[id] = function;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void WidgetRenderer::unsubscribe(const void* id)
    {
        m_data->observers.erase(id);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void WidgetRenderer::setData(const std::shared_ptr<RendererData>& data)
    {
        m_data = data;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::shared_ptr<RendererData> WidgetRenderer::getData() const
    {
        return m_data;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::shared_ptr<RendererData> WidgetRenderer::clone() const
    {
        auto data = std::make_shared<RendererData>(*m_data);
        data->observers = {};
        return data;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
