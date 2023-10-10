//
// Created by Nikita on 16.11.2020.
//

#ifndef HELPER_RESOURCEMANAGER_H
#define HELPER_RESOURCEMANAGER_H

#include <Utils/Debug.h>
#include <Utils/Types/Thread.h>
#include <Utils/Types/SharedPtr.h>
#include <Utils/Common/Singleton.h>
#include <Utils/ResourceManager/IResource.h>
#include <Utils/ResourceManager/ResourceInfo.h>

namespace SR_UTILS_NS {
    class IResourceReloader;
    class FileWatcher;

    class SR_DLL_EXPORT ResourceManager final : public Singleton<ResourceManager> {
        friend class Singleton<ResourceManager>;
        using Hash = uint64_t;
    public:
        static const uint64_t ResourceLifeTime;

    public:
        SR_NODISCARD bool IsLastResource(IResource* resource);
        SR_NODISCARD Path GetResPath() const { return m_folder; }
        SR_NODISCARD const Path& GetResPathRef() const { return m_folder; }
        SR_NODISCARD Path GetCachePath() const { return m_folder.Concat("Cache"); }
        SR_NODISCARD std::string_view GetTypeName(Hash hashName) const;

        SR_NODISCARD const std::string& GetResourceId(Hash hashId) const;
        SR_NODISCARD Hash RegisterResourceId(const std::string& resourceId);

        SR_NODISCARD const Path& GetResourcePath(Hash hashPath) const;
        SR_NODISCARD Hash RegisterResourcePath(const Path& path);

        SR_NODISCARD SR_HTYPES_NS::SharedPtr<FileWatcher> StartWatch(const Path& path);

        SR_NODISCARD IResource* Find(uint64_t hashTypeName, const std::string& ID);

        void Synchronize(bool force);
        void SetWatchingEnabled(bool enabled) { m_isWatchingEnabled = enabled; }

        void ReloadResource(IResource* pResource);

        void Execute(const SR_HTYPES_NS::Function<void()>& fun);
        void InspectResources(const SR_HTYPES_NS::Function<void(const ResourcesTypes &)>& callback);

        template<typename T> T* Find(const std::string& id) {
            return dynamic_cast<T*>(Find(SR_COMPILE_TIME_CRC32_TYPE_NAME(T), id));
        }

        template<typename T> T* Find(const Path& path) {
            return dynamic_cast<T*>(Find(SR_COMPILE_TIME_CRC32_TYPE_NAME(T), path.ToStringRef()));
        }

        template<typename T> bool RegisterType() {
            return RegisterType(typeid(T).name(), SR_COMPILE_TIME_CRC32_TYPE_NAME(T));
        }

        template<typename ResourceT, typename ReloaderT, typename ...Args> bool RegisterReloader(Args&&... args) {
            return RegisterReloader(new ReloaderT(std::forward<Args>(args)...), SR_COMPILE_TIME_CRC32_TYPE_NAME(ResourceT));
        }

        /** \warning Call only from IResource parents \brief Register resource in resource manager */
        void RegisterResource(IResource *resource);

        /** \warning Call only from IResource parents \brief Register resource to destroy in resource manager */
        bool Destroy(IResource *resource);

    public:
        bool Init(const SR_UTILS_NS::Path& resourcesFolder);
        bool Run();

        void OnSingletonDestroy() override;

        /// Проверить хэши ресурсов и перезагрузить их, если это требуется
        void ReloadResources(float_t dt);
        void UpdateWatchers(float_t dt);

        void PrintMemoryDump();

    private:
        bool RegisterType(const std::string& name, uint64_t hashTypeName);
        bool RegisterReloader(IResourceReloader* pReloader, uint64_t hashTypeName);

        void Remove(IResource *resource);
        void GC();
        void AsyncUpdateWatchers();
        void Thread();

    private:
        ResourcesList m_destroyed;
        ResourcesTypes m_resources;

        ska::flat_hash_map<Hash, Path> m_hashPaths;

        IResourceReloader* m_defaultReloader = nullptr;

    private:
        std::list<SR_HTYPES_NS::SharedPtr<FileWatcher>> m_watchers;
        std::queue<SR_HTYPES_NS::SharedPtr<FileWatcher>> m_dirtyWatchers;
        std::queue<ResourceInfo::WeakPtr> m_dirtyResources;

        std::atomic<bool> m_isWatchingEnabled = true;
        std::atomic<bool> m_isInit = false;
        std::atomic<bool> m_isRun = false;
        std::atomic<bool> m_force = false;

        Path m_folder;
        Types::Thread::Ptr m_thread = nullptr;
        uint64_t m_lastTime = 0;
        uint64_t m_deltaTime = 0;

        uint64_t m_GCDt = 0;
        uint64_t m_hashCheckDt = 0;

    };
}

#endif //HELPER_RESOURCEMANAGER_H
