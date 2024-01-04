#include "componentdeserializer.h"

#include "ball.h"
#include "behavior.h"
#include "button.h"
#include "checkbox.h"
#include "circle.h"
#include "colliderbox.h"
#include "component.h"
#include "graphic.h"
#include "mesh.h"
#include "player.h"
#include "opponent.h"
#include "rectangle.h"
#include "scorearea.h"
#include "scorecontroller.h"
#include "settingsscreencontroller.h"
#include "slider.h"
#include "text.h"
#include "titlescreencontroller.h"
#include "transform.h"

namespace pong
{

void ComponentDeserializer::DeserializeComponent(BaseComponent* component, const nlohmann::json& json)
{
    mCurrentJson = json;
    component->Accept(*this);
    mCurrentJson = nullptr;
}

void ComponentDeserializer::VisitComponent(Button* component)
{
    const float width = mCurrentJson["width"];
    const float height = mCurrentJson["height"];
    component->Resize(width, height);
}

void ComponentDeserializer::VisitComponent(CheckBox* component)
{
    const float width = mCurrentJson["width"];
    const float height = mCurrentJson["height"];
    component->Resize(width, height);

    if (mCurrentJson.contains("value"))
    {
        component->SetValue(mCurrentJson["value"]);
    }
}

void ComponentDeserializer::VisitComponent(ColliderBox* component)
{
    const float width = mCurrentJson["width"];
    const float height = mCurrentJson["height"];
    component->Resize(width, height);
}

void ComponentDeserializer::VisitComponent(Mesh* component)
{
    const std::string meshType = mCurrentJson["mesh_type"];

    std::unique_ptr<Graphic> graphic = nullptr;
    if (meshType == "Rectangle")
    {
        const float width = mCurrentJson["width"];
        const float height = mCurrentJson["height"];
        graphic = std::make_unique<Rectangle>(width, height);
    }
    else if (meshType == "Circle")
    {
        const float radius = mCurrentJson["radius"];
        const int sides = mCurrentJson["sides"];
        graphic = std::make_unique<Circle>(radius, sides);
    }
    component->SetGraphic(std::move(graphic));
}

void ComponentDeserializer::VisitComponent(Slider* component)
{
    const float width = mCurrentJson["width"];
    const float height = mCurrentJson["height"];
    component->Resize(width, height);

    const float min = mCurrentJson["min"];
    const float max = mCurrentJson["max"];
    const float step = mCurrentJson["step"];
    const float startValue = mCurrentJson["start_value"];
    component->SetVariables(min, max, step, startValue);
}

void ComponentDeserializer::VisitComponent(Text* component)
{
    component->mText =  mCurrentJson["text"];

    if (mCurrentJson.contains("scale"))
    {
        component->mScale = mCurrentJson["scale"];
    }

    if (mCurrentJson.contains("color"))
    {
        ASSERT(mCurrentJson["color"].is_object());
        const auto& color = mCurrentJson["color"];
        component->mColor = {color["r"], color["g"], color["b"], color["a"]};
    }

    Font* font = nullptr;
    if (mCurrentJson.contains("font"))
    {
        const std::string fontName = mCurrentJson["font"];
        font = Pong::GetInstance().GetFontBank().GetFont(fontName);
    }
    else
    {
        font = Pong::GetInstance().GetFontBank().GetDefaultFont();
    }
    ASSERT(font != nullptr);
    component->mFont = font;

    component->RecomputeText();

    if (mCurrentJson.contains("order_layer"))
    {
        const int orderLayer = mCurrentJson["order_layer"];
        component->SetOrderLayer(orderLayer);
    }
}

void ComponentDeserializer::VisitComponent(Transform* component)
{
    const float x = mCurrentJson["x"];
    const float y = mCurrentJson["y"];
    component->mPosition = glm::vec3(x, y, 0.0f);
}

void ComponentDeserializer::VisitComponent(Behavior* /*component*/)
{
}

void ComponentDeserializer::VisitComponent(Opponent* component)
{
    const float speed = mCurrentJson["speed"];
    component->mSpeed = speed;
}

void ComponentDeserializer::VisitComponent(Player* component)
{
    const float speed = mCurrentJson["speed"];
    component->mSpeed = speed;
}

void ComponentDeserializer::VisitComponent(Ball* component)
{
    const float speed = mCurrentJson["speed"];
    component->mStartSpeed = speed;
}

void ComponentDeserializer::VisitComponent(ScoreArea* component)
{
    const bool playerSide = mCurrentJson["player_side"];
    component->mIsPlayerScoreArea = playerSide;
}

void ComponentDeserializer::VisitComponent(ScoreController* /*component*/)
{

}

} // namespace pong
