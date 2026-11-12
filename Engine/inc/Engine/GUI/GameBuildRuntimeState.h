//
// Created by OpenAI Codex on 12.11.2026.
//

#ifndef SR_ENGINE_GAME_BUILD_RUNTIME_STATE_H
#define SR_ENGINE_GAME_BUILD_RUNTIME_STATE_H

#include <Engine/GUI/GameBuildRuntime.h>
#include <Utils/Network/HttpFileServer.h>
#include <Utils/FileSystem/IVFSBackend.h>

namespace SR_CORE_GUI_NS {
    struct GameBuildRuntime::State {
        State();
        ~State();
        void Message(SR_UTILS_NS::String text, bool error = false);
        bool Task(SR_HTYPES_NS::Function<void()> job, bool quiet = false);
        void Work();
        void StopPreviews();
        void UpdateDevices();
        void UpdateSystemImages();

        mutable std::mutex mutex;
        Status status;
        std::atomic<bool> busy = false;
        std::atomic<bool> cancel = false;
        SR_HTYPES_NS::Thread::Ptr worker = nullptr;
        std::mutex jobMutex;
        std::condition_variable workAvailable;
        SR_HTYPES_NS::Function<void()> pendingJob;
        bool exiting = false;
        SR_UTILS_NS::String logcatScope;
        SR_UTILS_NS::Path artifactDirectory;
        SR_UTILS_NS::RawPointerHolder<SR_UTILS_NS::IVFSBackend> artifactBackend;
        SR_PLATFORM_NS::Process desktop;
        SR_PLATFORM_NS::Process emulator;
        SR_PLATFORM_NS::AndroidSDK android;
        SR_NETWORK_NS::HttpFileServer web;
    };
}

#endif
