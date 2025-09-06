

# File ReflectionTestComponent.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Tests**](dir_c9bf2873816ed2ebb5fd18269f2ea03a.md) **>** [**ReflectionTestComponent.h**](ReflectionTestComponent_8h.md)

[Go to the documentation of this file](ReflectionTestComponent_8h.md)


```C++
//
// Created by Monika on 19.01.2025.
//

#ifndef SR_ENGINE_UTILS_REFLECTION_TEST_COMPONENT_H
#define SR_ENGINE_UTILS_REFLECTION_TEST_COMPONENT_H

#include <Utils/ECS/Component.h>
#include <Utils/ECS/ComponentManager.h>

namespace SR_UTILS_NS::Tests {
    struct ReflectionTestComponentAssociative : public SR_UTILS_NS::Serializable {
        SR_STRUCT()

        
        std::map<SR_UTILS_NS::StringAtom, int> associativeMapAtom;
        std::map<std::string, int> associativeMapString;
        std::map<int, std::string> associativeMap2;
        std::map<SR_UTILS_NS::PlatformType, int> associativeMap33;
        std::map<SR_UTILS_NS::PlatformType, std::string> associativeMap3;
        std::map<SR_UTILS_NS::PlatformType, SR_UTILS_NS::Path> associativeMap4;

    };

    struct ReflectionTestComponentDataBase : public SR_UTILS_NS::Serializable {
        SR_STRUCT()

        
        bool baseField = false;

    };

    struct ReflectionTestComponentData : public ReflectionTestComponentDataBase {
        SR_STRUCT()

        
        bool testField = false;
        SR_MATH_NS::FVector3 vector;
        int32_t m_width = 100;
        std::vector<float> m_test;
    };

    class ReflectionTestComponentLogicBase : public SR_UTILS_NS::Serializable, public SR_HTYPES_NS::SharedPtr<ReflectionTestComponentLogicBase> {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<ReflectionTestComponentLogicBase>;

        ReflectionTestComponentLogicBase()
            : SR_HTYPES_NS::SharedPtr<ReflectionTestComponentLogicBase>(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
        { }

    private:
        bool m_baseBoolValue = false;

    };

    class ReflectionTestComponentLogicSimple : public ReflectionTestComponentLogicBase {
        SR_CLASS()
    private:
        float_t m_simpleFloat = 0.0f;
        int32_t m_simpleInt = 0;
    };

    class ReflectionTestComponentLogicComplex : public ReflectionTestComponentLogicBase {
        SR_CLASS()
    private:
        std::vector<int> m_complexInts;
        SR_MATH_NS::FVector3 m_complexVector;
        ReflectionTestComponentLogicBase::Ptr m_other;
        std::vector<ReflectionTestComponentLogicBase::Ptr> m_others;

    };

    class ReflectionTestComponent : public SR_UTILS_NS::Component {
        using Super = Component;
        SR_CLASS()
    public:
        SR_NODISCARD const bool& IsWidthChangeable() const { return m_isWidthChangeable; }
        std::vector<float>& GetTest() { return m_test; }

        void OnChanged() {
            m_hasChanged = true;
        }

    private:
        ReflectionTestComponentAssociative m_associative;
        std::string m_string = "Hello world!";
        SR_UTILS_NS::PlatformType m_platformType = SR_UTILS_NS::PlatformType::Windows;
        ReflectionTestComponentData m_data;
        ReflectionTestComponentLogicBase::Ptr m_logic;
        std::vector<ReflectionTestComponentData> m_datas;
        bool m_isWidthChangeable = true;
        bool m_isHeightChangeable = true;
        int32_t m_width = 100;
        int8_t m_int8 = 5;
        uint64_t m_uint64 = 500 + 400;
        float_t m_height = 200.0f;
        SR_MATH_NS::FVector3 m_position;
        SR_MATH_NS::FVector6 m_6d;
        SR_MATH_NS::FVector2 m_2d;
        SR_MATH_NS::BVector4 m_4db;
        bool m_hasChanged = false;
        SR_MATH_NS::FSize m_size;
        SR_MATH_NS::FSize2 m_size2;
        std::vector<float> m_test;
        std::vector<std::vector<int>> m_test2;
        std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<float_t>>>>>> m_test4;
        std::vector<int> m_test3 = { 1, 2, 3 };
        std::vector<SR_MATH_NS::FVector3> m_testMathVector3;
        std::vector<std::vector<SR_MATH_NS::FVector4>> m_testMathVector4;
        std::vector<SR_UTILS_NS::PlatformType> m_testPlatformType;
        std::vector<SR_MATH_NS::FSize> m_testSize;
        std::vector<SR_MATH_NS::FSize2> m_testSize2;
        std::vector<bool> m_bitSet;

    };
}

#endif //SR_ENGINE_UTILS_REFLECTION_TEST_COMPONENT_H
```


