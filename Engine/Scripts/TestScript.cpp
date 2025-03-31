//
// Created by Monika on 26.03.2025.
//

#include "TestScript.h"

#include <SpaRcle/Utils/Math/FVector3.h>
#include <SpaRcle/Utils/Math/IVector3.h>
#include <SpaRcle/Utils/StringAtom.h>
#include <SpaRcle/Utils/Debug.h>
#include <SpaRcle/Core/Engine.h>
#include <SpaRcle/Core/ScriptableContext.h>

void PrintVector3(const char* name, const SpaRcle::Utils::Math::FVector3& vec) {
    std::cout << name << ": (" << vec.X() << ", " << vec.Y() << ", " << vec.Z() << ")" << std::endl;
}

void PrintVector3(const char* name, const SpaRcle::Utils::Math::IVector3& vec) {
    std::cout << name << ": (" << vec.X() << ", " << vec.Y() << ", " << vec.Z() << ")" << std::endl;
}

void RunScriptTest() {
    std::cout << "Running script test..." << std::endl;

    UnsafeRef<SpaRcle::Core::ScriptableContext> pContext(CoreAPI::Instance().GetScriptContextHandle());
    UnsafeRef<SpaRcle::Core::Engine> pEngine = pContext->GetEngine();
    // pEngine->GetDebugger()->TestPrint();
    // pEngine->GetDebugger()->MakeCrash();

    //SpaRcle::Utils::Math::FVector3 vec3(1.0f, 2.0f, 3.0f);
    SpaRcle::Utils::StringAtom str;
    str = "Hello, World!";
    std::cout << "StringAtom: " << str.c_str() << std::endl;

    SpaRcle::Utils::Math::FVector3 vec3(1.0f, 2.0f, 3.0f);
    PrintVector3("FVector3", vec3);
    vec3.X() = 4.0f;
    PrintVector3("FVector3", vec3);
    std::cout << "Min: " << vec3.Min() << std::endl;

    SpaRcle::Utils::Math::FVector3 constructorTest = SpaRcle::Utils::Math::FVector3(1.0f, 2.0f, 3.0f);
    PrintVector3("constructorTest", constructorTest);

    SpaRcle::Utils::Math::FVector3 opTest1;
    opTest1 += SpaRcle::Utils::Math::FVector3(1.0f, 2.0f, 3.0f);
    PrintVector3("opTest1", opTest1);

    SpaRcle::Utils::Math::FVector3 opTest2;
    opTest2 = SpaRcle::Utils::Math::FVector3(1.0f, 2.0f, 3.0f) + SpaRcle::Utils::Math::FVector3(4.0f, 5.0f, 6.0f);
    PrintVector3("opTest2", opTest2);
    opTest2 += SpaRcle::Utils::Math::FVector3(1.2f, 1.4f, 1.6f);
    PrintVector3("opTest2", opTest2);

    SpaRcle::Utils::Math::FVector3 sinTest = opTest2.Sin();
    PrintVector3("sinTest", sinTest);

    SpaRcle::Utils::Math::IVector3 castTest = opTest2.CastToInt();
    PrintVector3("castTest", castTest);

    std::cout << "Script test completed!" << std::endl;
}