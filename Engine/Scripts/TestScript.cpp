//
// Created by Monika on 26.03.2025.
//

#include "TestScript.h"

#include <SpaRcle/Utils/Math/FVector3.h>
#include <SpaRcle/Utils/Math/IVector3.h>
#include <SpaRcle/Utils/StringAtom.h>

void PrintFVector3(const char* name, const SpaRcle::Utils::Math::FVector3& vec) {
    std::cout << name << ": (" << vec.X() << ", " << vec.Y() << ", " << vec.Z() << ")" << std::endl;
}

void RunScriptTest() {
    std::cout << "Running script test..." << std::endl;

    //SpaRcle::Utils::Math::FVector3 vec3(1.0f, 2.0f, 3.0f);
    SpaRcle::Utils::StringAtom str;
    str = "Hello, World!";
    std::cout << "StringAtom: " << str.c_str() << std::endl;

    SpaRcle::Utils::Math::FVector3 vec3(1.0f, 2.0f, 3.0f);
    PrintFVector3("FVector3", vec3);
    vec3.X() = 4.0f;
    PrintFVector3("FVector3", vec3);
    std::cout << "Min: " << vec3.Min() << std::endl;

    SpaRcle::Utils::Math::FVector3 constructorTest = SpaRcle::Utils::Math::FVector3(1.0f, 2.0f, 3.0f);
    PrintFVector3("constructorTest", constructorTest);

    SpaRcle::Utils::Math::FVector3 opTest1;
    opTest1 += SpaRcle::Utils::Math::FVector3(1.0f, 2.0f, 3.0f);
    PrintFVector3("opTest1", opTest1);

    SpaRcle::Utils::Math::FVector3 opTest2;
    opTest2 = SpaRcle::Utils::Math::FVector3(1.0f, 2.0f, 3.0f) + SpaRcle::Utils::Math::FVector3(4.0f, 5.0f, 6.0f);
    PrintFVector3("opTest2", opTest2);
    opTest2 += SpaRcle::Utils::Math::FVector3(1.0f, 1.0f, 1.0f);
    PrintFVector3("opTest2", opTest2);

    std::cout << "Script test completed!" << std::endl;
}