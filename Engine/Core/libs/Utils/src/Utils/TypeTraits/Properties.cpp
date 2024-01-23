//
// Created by Monika on 06.11.2023.
//

#include <Utils/TypeTraits/Properties.h>

namespace SR_UTILS_NS {
    PropertyContainer::PropertyContainer() {
        m_properties.reserve(8);
    }

    PropertyContainer::~PropertyContainer() {
        ClearContainer();
    }

    PropertyContainer& PropertyContainer::AddContainer(const char* name) {
        if (auto&& pProperty = Find(name)) {
            SRHalt("Properties::AddContainer() : property \"" + std::string(name) + "\" already exists!");
            return *dynamic_cast<PropertyContainer*>(pProperty);
        }

        auto&& pProperty = new PropertyContainer();

        pProperty->SetName(name);

        m_properties.emplace_back(pProperty);
        OnPropertyAdded(pProperty);

        return *pProperty;
    }

    void PropertyContainer::ClearContainer() {
        for (auto&& pProperty : m_properties) {
            delete pProperty;
        }
        m_properties.clear();
    }

    void PropertyContainer::SaveProperty(MarshalRef marshal) const noexcept {
        if (auto&& pBlock = AllocatePropertyBlock()) {
            SR_HTYPES_NS::Marshal propertiesMarshal;
            uint16_t count = 0;

            for (auto&& pProperty : GetProperties()) {
                if (pProperty->IsDontSave()) {
                    continue;
                }

                if (!pProperty->IsActive()) {
                    continue;
                }

                ++count;

                SR_HTYPES_NS::Marshal propertyMarshal;
                pProperty->SaveProperty(propertyMarshal);

                propertiesMarshal.Write<StringAtom>(pProperty->GetName());
                propertiesMarshal.Write<uint32_t>(propertyMarshal.Size());
                propertiesMarshal.Append(std::move(propertyMarshal));
            }

            pBlock->Write<uint16_t>(count);
            pBlock->Append(std::move(propertiesMarshal));

            SavePropertyBase(marshal, std::move(pBlock));
        }
    }

    EntityRefProperty& PropertyContainer::AddEntityRefProperty(SpaRcle::Utils::StringAtom name, const EntityRefUtils::OwnerRef& owner) {
        if (auto&& pProperty = Find(name)) {
            SRHalt("Properties::AddEntityRefProperty() : property \"" + name.ToStringRef() + "\" already exists!");
            return *dynamic_cast<EntityRefProperty*>(pProperty);
        }

        auto&& pProperty = new EntityRefProperty();

        pProperty->SetName(name);
        pProperty->GetEntityRef().SetOwner(owner);

        m_properties.emplace_back(pProperty);
        OnPropertyAdded(pProperty);

        return *pProperty;
    }

    void PropertyContainer::LoadProperty(MarshalRef marshal) noexcept {
        if (auto&& pBlock = LoadPropertyBase(marshal)) {
            auto&& count = pBlock->Read<uint16_t>();

            for (uint16_t i = 0; i < count; ++i) {
                auto&& name = pBlock->Read<StringAtom>();
                auto&& size = pBlock->Read<uint32_t>();
                auto&& propertyMarshal = pBlock->ReadBytes(size);

                if (auto&& pProperty = Find(name)) {
                    pProperty->LoadProperty(propertyMarshal);
                }
                else {
                    SR_WARN("PropertyContainer::LoadProperty() : property not found!\n\tContainer: {}\n\tProperty name: {}",
                        GetName().ToCStr(), name.ToCStr()
                    );
                }
            }
        }
    }
}