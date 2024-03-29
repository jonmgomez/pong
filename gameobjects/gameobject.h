#pragma once

#include "behavior.h"
#include "component.h"
#include "componentmanager.h"
#include "pong.h"
#include "utils.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace pong
{

class GameObject
{
public:
    GameObject() = default;
    virtual ~GameObject() = default;

    int GetId() const;
    std::string GetInstanceName() const;
    void SetInstanceName(const std::string& name);
    bool ShouldDestroyOnLoad() const;
    void SetDestroyOnLoad(const bool destroyOnLoad);

    std::vector<Behavior*> GetBehaviorComponents() const;

    void Destroy();

    template<typename T>
    T* GetComponent()
    {
        const int componentId = GetComponentTypeId<T>();

        auto iterator = mComponents.find(componentId);
        if (iterator != mComponents.end())
        {
            return static_cast<T*>(mComponents[componentId]);
        }

        return nullptr;
    }

    template<typename T, typename = std::enable_if_t<std::is_base_of_v<BaseComponent, T>>, typename... Args>
    T* AddComponent(Args&&... args)
    {
        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        T* componentPtr = component.get();
        component->SetGameObject(this);

        const int componentId = GetComponentTypeId<T>();
        mComponents.insert(std::make_pair(componentId, componentPtr));
        globals::game::GetPongInstance()->GetComponentManager().AddComponent<T>(std::move(component));

        return componentPtr;
    }

private:
    static int sId;

    int mId { sId++ };
    bool mDestroyOnLoad { true };
    std::unordered_map<int, BaseComponent*> mComponents {};
    std::string mInstanceName { "" };
};

} // namespace pong
