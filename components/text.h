#pragma once

#include "component.h"
#include "font.h"
#include "textcharacter.h"
#include "uicomponent.h"

#include <glm/glm.hpp>

#include <string>
#include <vector>

namespace pong
{

class Text : public UIComponent, public Component<Text>
{
public:
    Text() = default;
    Text(const std::string& text, Font* font, float scale);

    std::vector<OffsetGraphic> GetRenderables() override;
    BaseComponent* GetBaseComponent() override;

    std::string GetText() const;
    void SetText(const std::string& text);
    void SetFont(Font* font);
    void SetScale(float scale);
    void SetColor(const GLRGBAColor& color);
    void RecomputeText();

private:
    std::string mText {};
    Font* mFont { nullptr };
    float mScale { 1.0f };
    GLRGBAColor mColor { GLRGBA_WHITE };
    std::vector<TextCharacter> mCharacters {};

    friend class ComponentDeserializer;
};

} // namespace pong
