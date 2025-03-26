//
// Created by Monika on 26.03.2025.
//

#include "TestScript.h"

#include <SpaRcle/Utils/Math/FVector3.h>
#include <SpaRcle/Utils/Math/IVector3.h>
#include <SpaRcle/Utils/StringAtom.h>

void RunScriptTest() {
    std::cout << "Running script test..." << std::endl;

    //SpaRcle::Utils::Math::FVector3 vec3(1.0f, 2.0f, 3.0f);
    SpaRcle::Utils::StringAtom str;
    str = "Hello, World!";
    std::cout << "StringAtom: " << str.c_str() << std::endl;
}