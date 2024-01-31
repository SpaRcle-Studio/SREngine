//
// Created by Monika on 21.09.2021.
//

#ifndef SR_ENGINE_UTILS_ISAVABLE_H
#define SR_ENGINE_UTILS_ISAVABLE_H

#include <Utils/Types/Marshal.h>
#include <Utils/Xml.h>

namespace SR_UTILS_NS {
    typedef uint64_t SavableFlags;

    enum SavableFlagBits {
        SAVABLE_FLAG_NONE = 1 << 0,
        SAVABLE_FLAG_ECS_NO_ID = 1 << 1,
    };

    struct SavableContext {
        SavableContext() = default;

        SavableContext(SR_HTYPES_NS::Marshal::Ptr pMarshal, SavableFlags flags)
            : pMarshal(pMarshal)
            , flags(flags)
        { }

        SR_HTYPES_NS::Marshal::Ptr pMarshal = nullptr;
        SavableFlags flags = SAVABLE_FLAG_NONE;
    };

    struct SavableLoadData {

    };

    class SR_DLL_EXPORT ISavable {
    protected:
        ISavable() = default;
        virtual ~ISavable() = default;

    public:
        void SetDontSave(bool value) { m_dontSave = value; }

        SR_NODISCARD bool IsDontSave() const noexcept { return m_dontSave; }

        SR_NODISCARD virtual SR_HTYPES_NS::Marshal::Ptr Save(SavableContext data) const {
            if (IsDontSave()) {
                return nullptr;
            }

            if (data.pMarshal) {
                return data.pMarshal;
            }
            
            return new SR_HTYPES_NS::Marshal();
        }

    private:
        bool m_dontSave = false;

    };
}

#endif //SR_ENGINE_UTILS_ISAVABLE_H
