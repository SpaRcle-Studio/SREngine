//
// Created by Monika on 25.06.2022.
//

#ifndef EVOSCRIPTLIB_BEHAVIOUR_H
#define EVOSCRIPTLIB_BEHAVIOUR_H

#include <Libraries/Utils/BehaviourRegistration.h>
#include <Libraries/Types/SafePointer.h>
#include <Libraries/GameObject.h>
#include <Libraries/Scene.h>

class Behaviour : public NonCopyable {
public:
    using GameObjectPtr = SharedPtr<GameObject>;
    using ScenePtr = SafePtr<Scene>;
    using Any = std::any;
    using Property = std::pair<
        std::function<Any(void)>, /// getter
        std::function<void(const Any&)> /// setter
    >;
public:
    virtual void Awake() { }
    virtual void OnEnable() { }
    virtual void OnDisable() { }
    virtual void Start() { }
    virtual void FixedUpdate() { }
    virtual void Update(float_t dt) { }
    virtual void Close() { }

    virtual void OnCollisionEnter(const CollisionData& data) { }
    virtual void OnCollisionStay(const CollisionData& data) { }
    virtual void OnCollisionExit(const CollisionData& data) { }

    virtual void OnTriggerEnter(const CollisionData& data) { }
    virtual void OnTriggerStay(const CollisionData& data) { }
    virtual void OnTriggerExit(const CollisionData& data) { }

    bool HasProperty(const std::string& id) {
        return m_properties.count(id) == 1;
    }

    Any GetProperty(const std::string& id) {
        return m_properties.at(id).first();
    }

    std::vector<std::string> GetProperties() const {
        return m_propertyIds;
    }

    void SetProperty(const std::string& id, const Any& val) {
        m_properties.at(id).second(val);
    }

    void SetGameObject(GameObjectPtr ptr) {
        if ((gameObject = ptr)) {
            transform = gameObject->GetTransform();
            scene = gameObject->GetScene();
        }
    }

    void SetScene(ScenePtr ptr) {
        scene = ptr;
    }

protected:
    template<typename T> bool AddProperty(const std::string& id, T* ref) {
        gBehaviourContext->propertiesRegistrations.emplace_back([this, ref, id]() {
            if (m_properties.count(id) == 1) {
            #ifdef EVK_DEBUG
                std::cerr << "Behaviour::AddProperty() : property already registered!\n\tId: " << id << '\n';
            #endif
                return;
            }

            m_properties.insert(std::make_pair(
                id,
                std::make_pair(
                    [pProperty = ref]() -> Any
                    {
                        return Any(*pProperty);
                    }, /// getter
                    [id, pProperty = ref](const Any& val)
                    {
                        try
                        {
                            *pProperty = std::any_cast<T>(val);
                        }
                        catch(const std::bad_any_cast& e)
                        {
                        #ifdef EVK_DEBUG
                            std::cerr << "Behaviour::AddProperty() : failed to cast std::any!"
                                         "\n\tException: " << e.what() <<
                                         "\n\tType: " << typeid(T).name() <<
                                         "\n\tAny: " << val.type().name() <<
                                         "\n\tId: " << id << "\n";
                        #endif
                        }
                    } /// setter
                )
            ));

            m_propertyIds.emplace_back(id);
        });

        return true;
    }

protected:
    GameObjectPtr gameObject;
    ScenePtr scene;
    Transform* transform = nullptr;
    const float fixedDeltaTime = 1.f/60.f;

private:
    std::unordered_map<std::string, Property> m_properties;
    std::vector<std::string> m_propertyIds;

};

#define SR_PROPERTY(id) const bool CODEGEN_PROPERTY_REGISTRATION_##id = [this]() -> bool { return AddProperty(#id, &id); }();

#endif //EVOSCRIPTLIB_BEHAVIOUR_H
