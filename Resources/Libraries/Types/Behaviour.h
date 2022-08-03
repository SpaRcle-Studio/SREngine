//
// Created by Monika on 25.06.2022.
//

#ifndef EVOSCRIPTLIB_BEHAVIOUR_H
#define EVOSCRIPTLIB_BEHAVIOUR_H

#include "../Utils/BehaviourRegistration.h"

class Behaviour : public NonCopyable {
    using Property = std::pair<
        std::function<std::any(void)>, /// getter
        std::function<void(const std::any&)> /// setter
    >;
public:
    virtual void Awake() { }
    virtual void OnEnable() { }
    virtual void OnDisable() { }
    virtual void Start() { }
    virtual void Update(float_t dt) { }
    virtual void Close() { }

    bool HasProperty(const std::string& id) {
        return m_properties.count(id) == 1;
    }

    std::any GetProperty(const std::string& id) {
        /// TODO: unsafe
        return m_properties.at(id).first();
    }

    std::vector<std::string> GetProperties() const {
        return m_propertyIds;
    }

    void SetProperty(const std::string& id, const std::any& val) {
        /// TODO: unsafe
        m_properties.at(id).second(val);
    }

protected:
    template<typename T> bool AddProperty(const std::string& id, T* property) {
        if (m_properties.count(id) == 1) {
            std::cerr << "Behaviour::AddProperty() : property already registered!\n\tId: " << id << '\n';
            return false;
        }

        m_properties.insert(std::make_pair(
            id,
            std::make_pair(
                [pProperty = property]() -> std::any
                {
                    return *pProperty;
                }, /// getter
                [pProperty = property](const std::any& val)
                {
                    try
                    {
                        *pProperty = std::any_cast<T>(val);
                    }
                    catch(const std::bad_any_cast& e)
                    {
                        std::cerr << "Behaviour::AddProperty() : failed to cast std::any!\n\tException: " << e.what() << '\n';
                    }
                } /// setter
            )
        ));

        m_propertyIds.emplace_back(id);

        return true;
    }

private:
    std::unordered_map<std::string, Property> m_properties;
    std::vector<std::string> m_propertyIds;

};

#define SR_PROPERTY(id) const bool CODEGEN_PROPERTY_REGISTRATION_##id = [this]() -> bool { return AddProperty(#id, &id); }();

#endif //EVOSCRIPTLIB_BEHAVIOUR_H
