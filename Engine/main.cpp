//
// Created by Nikita on 29.12.2020.
// Looked by Drakeme on 26.06.2022.
// Changed by Monika on 20.11.2022
// Approved and improved by innerviewer on 09.03.2023
//

#include <Core/Application.h>
#include <Utils/Platform/Platform.h>
#include <Utils/Tests/SharedPtrAutotests.h>

int main(int argc, char** argv) {
    if (!SR_UTILS_NS::RunTestSharedPtr()) {
        SR_PLATFORM_NS::WriteConsoleError("Application::PreInit() : shared pointer autotests failed!\n");
        return 10;
    }

    int32_t code = 0;

    {
        auto&& pApplication = SR_CORE_NS::Application::MakeShared();

        if (!pApplication->PreInit(argc, argv)) {
            SR_PLATFORM_NS::WriteConsoleError("Failed to pre-initialize application!\n");
            code = 1;
        }

        if (code == 0 && !pApplication->Init()) {
            SR_ERROR("Failed to initialize application!");
            code = 2;
        }

        if (code == 0 && !pApplication->Execute()) {
            SR_ERROR("Failed to execute application!");
            code = 3;
        }

        pApplication.AutoFree([](auto&& pData) {
            delete pData;
        });
    }

    SR_HTYPES_NS::SharedPtrDynamicDataCounter::CheckMemoryLeaks();

    return code;
}