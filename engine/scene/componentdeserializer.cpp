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
    mCurrentJson.clear();
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
}

void ComponentDeserializer::VisitComponent(ColliderBox* component)
{
    const float width = mCurrentJson["width"];
    const float height = mCurrentJson["height"];
    component->Resize(width, height);
}

void ComponentDeserializer::VisitComponent(Mesh* component)
{
    const std::string meshName = mCurrentJson["meshName"];

    std::unique_ptr<Graphic> graphic = nullptr;
    if (meshName == "Rectangle")
    {
        const float width = mCurrentJson["width"];
        const float height = mCurrentJson["height"];
        std::unique_ptr<Graphic> graphic = std::make_unique<Rectangle>(width, height);
    }
    else if (meshName == "Circle")
    {
        const float radius = mCurrentJson["radius"];
        const int sides = mCurrentJson["sides"];
        std::unique_ptr<Graphic> graphic = std::make_unique<Circle>(radius, sides);
    }
    component->SetGraphic(std::move(graphic));
}

void ComponentDeserializer::VisitComponent(Slider* component)
{
    const float width = mCurrentJson["width"];
    const float height = mCurrentJson["height"];
    component->Resize(width, height);
}

void ComponentDeserializer::VisitComponent(Text* component)
{
    const std::string text = mCurrentJson["text"];
    component->SetText(text);
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

void ComponentDeserializer::VisitComponent(Opponent* /*component*/)
{

}

void ComponentDeserializer::VisitComponent(Player* /*component*/)
{

}

void ComponentDeserializer::VisitComponent(Ball* /*component*/)
{

}

void ComponentDeserializer::VisitComponent(ScoreArea* /*component*/)
{

}

void ComponentDeserializer::VisitComponent(ScoreController* /*component*/)
{

}

} // namespace pong
