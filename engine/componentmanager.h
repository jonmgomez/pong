#pragma once

#include "component.h"
#include "uielement.h"

#include "button.h"
#include "checkbox.h"
#include "slider.h"
#include "text.h"

#include <memory>
#include <vector>

namespace pong
{

// The purpose of this class is to manage all components in the game.
// Generally each component manages itself using CRTP, but this class manages
// more complicated components like UIElements, which need to be stored in a certain
// order to be rendered correctly. So this class manages the order of UIElements and stores
// them generically in a vector.
class ComponentManager
{
public:
    void Reset();

    template<typename T>
    void AddComponent(std::unique_ptr<T> component)
    {
        T::AddComponent(std::move(component));
    }

    template<>
    void AddComponent<Button>(std::unique_ptr<Button> component)
    {
        Button* checkBox = component.get();
        Button::AddComponent(std::move(component));
        mUIComponents.push_back(checkBox);
    }

    template<>
    void AddComponent<CheckBox>(std::unique_ptr<CheckBox> component)
    {
        CheckBox* checkBox = component.get();
        CheckBox::AddComponent(std::move(component));
        mUIComponents.push_back(checkBox);
    }

    template<>
    void AddComponent<Slider>(std::unique_ptr<Slider> component)
    {
        Slider* checkBox = component.get();
        Slider::AddComponent(std::move(component));
        mUIComponents.push_back(checkBox);
    }

    template<>
    void AddComponent<Text>(std::unique_ptr<Text> component)
    {
        Text* checkBox = component.get();
        Text::AddComponent(std::move(component));
        mUIComponents.push_back(checkBox);
    }

    const std::vector<UIElement*>& GetUIComponents() const;
    void UpdateUIElementOrderLayers();

private:
    std::vector<UIElement*> mUIComponents {};
};

} // namespace pong
