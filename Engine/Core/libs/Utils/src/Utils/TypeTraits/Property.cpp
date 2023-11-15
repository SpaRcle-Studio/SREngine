//
// Created by Monika on 07.11.2023.
//

#include <Utils/TypeTraits/Property.h>

namespace SR_UTILS_NS {
    bool Property::IsActive() const noexcept {
        if (!m_activeCondition) {
            return true;
        }
        return m_activeCondition();
    }

    void Property::SavePropertyBase(MarshalRef marshal, MarshalUniquePtr pBlock) const {
        if  (m_dontSave) {
            SRHalt("Trying to save un-savable property!");
            return;
        }

        marshal.Write<uint16_t>(GetPropertyVersion());
        marshal.Write<SR_UTILS_NS::StringAtom>(GetPropertyTypeName());

        marshal.Write<uint32_t>(pBlock ? pBlock->Size() : 0);
        marshal.Append(std::move(pBlock));
    }

    Property::MarshalUniquePtr Property::AllocatePropertyBlock() const {
        if (IsDontSave()) {
            return nullptr;
        }

        if (!IsActive()) {
            return nullptr;
        }

        return std::make_unique<SR_HTYPES_NS::Marshal>();
    }

    Property::MarshalUniquePtr Property::LoadPropertyBase(MarshalRef marshal) const {
        if (m_dontSave) {
            return nullptr;
        }

        auto&& version = marshal.Read<uint16_t>();
        auto&& typeName = marshal.Read<SR_UTILS_NS::StringAtom>();

        auto&& size = marshal.Read<uint32_t>();
        auto&& pBlock = std::unique_ptr<SR_HTYPES_NS::Marshal>(marshal.ReadBytesPtr(size));

        if (version != GetPropertyVersion()) {
            return nullptr;
        }

        if (typeName != GetPropertyTypeName()) {
            return nullptr;
        }

        return std::move(pBlock);
    }

    void ExternalProperty::SaveProperty(MarshalRef marshal) const noexcept {
        if (auto&& pBlock = AllocatePropertyBlock()) {
            SR_HTYPES_NS::Marshal externalBlock;

            if (auto&& pExternal = GetExternalProperty()) {
                pExternal->SaveProperty(externalBlock);
            }

            marshal.Write<uint32_t>(externalBlock.Size());
            marshal.Append(std::move(externalBlock));

            SavePropertyBase(marshal, std::move(pBlock));
        }
    }

    void ExternalProperty::LoadProperty(MarshalRef marshal) noexcept {
        if (auto&& pBlock = LoadPropertyBase(marshal)) {
            auto&& blockSize = pBlock->Read<uint32_t>();
            auto&& externalBlock = pBlock->ReadBytes(blockSize);

            if (auto&& pExternal = GetExternalProperty()) {
                pExternal->LoadProperty(externalBlock);
            }
        }
    }

    Property* ExternalProperty::GetExternalProperty() const noexcept {
        return m_getter ? m_getter() : nullptr;
    }
}
