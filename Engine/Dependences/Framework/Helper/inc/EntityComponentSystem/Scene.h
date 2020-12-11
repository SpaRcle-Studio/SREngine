//
// Created by Nikita on 30.11.2020.
//

#ifndef GAMEENGINE_SCENE_H
#define GAMEENGINE_SCENE_H

#include <iostream>
#include <string>
#include <map>
#include <mutex>
#include "GameObject.h"


namespace Framework::Helper {
    class GameObject;
    class Scene {
    private:
        Scene();
        ~Scene();
    public:
        static Scene* New(std::string name);
        static Scene* Load(const std::string& name);
        bool Destroy();
        bool Free();
    private:
        bool m_isDestroy = false;
        std::mutex m_mutex;
        std::string m_name = "Unnamed";
        std::map<GameObject*, GameObject*> m_gameObjects;
    public:
        GameObject* Instance(std::string name);
        bool Destroy(GameObject* gameObject);
    };
}

#endif //GAMEENGINE_SCENE_H
