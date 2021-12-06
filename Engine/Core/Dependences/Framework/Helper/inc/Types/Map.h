//
// Created by kiper220 on 23.05.2020.
//

#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <Types/Vector.h>
#include <Types/Pair.h>

#include <mutex>

// TODO: Check, refactoring and add exception processing

namespace Framework::Helper::Types {
    /**
    *
    * \brief Red Template Library Map
    * \authors WetGrape | Kiper220
    * \copyright GNU LGPL
    *
    **/
    template<typename ClassType>
    bool ClassIsValid(const ClassType* _class) {
        return _class != nullptr;
    }
    template<typename ClassType>
    bool ClassIsValid(const ClassType& _class) {
        return &_class != nullptr;
    }

    template<typename key, typename value>
    class Map{
    public:
        /**
         * \brief Standart zero constructor
         */
        Map() = default;
        /**
         * \brief Standart copy constructor
         */
        Map(const Map& map): Data(map.Data){}
        /**
         * \brief Standart move constructor
         */
        Map(Map&& map): Data(std::move(map.Data)){}
        /**
         * \brief Standart copy constructor
         */
        Map(const Vector<Pair<key, value>>& _data): Data(_data){}
        /**
         * \brief Standart move constructor
         */
        Map(const Vector<Pair<key, value>>&& _data): Data(std::move(_data)){}

        /**
         * \brief Map overload copy operator
         */
        Map& operator = (const Map& map){
        m_mutex.lock();
        Data = map.Data;
        m_mutex.unlock();
        };
        /**
         * \brief Map overload copy operator
         */
        Map& operator = (const Vector<Pair<key, value>>& _data){
        m_mutex.lock();
        Data = _data;
        m_mutex.unlock();
        };

        /**
         * \brief Map overload operator[](key)
         * \arg _Key - key to get value reference
         */
        value& operator[](const key &_Key) {
        m_mutex.lock();

        if (Data.Size() == 0) {
            Data.Push_Back(Pair<key, value>());
            Data[0].x = _Key;
            m_mutex.unlock();
            return Data[0].y;
        } else if (Data.Size() == 1) {
            if (Data[0].x == _Key) {
            m_mutex.unlock();
            return Data[0].y;
            }
            else {
            if (Data[0].x < _Key) {
                Data.Insert(Pair<key, value>(), 1);
                Data[1].x = _Key;
                m_mutex.unlock();
                return Data[1].y;
            } else {
                Data.Insert(Pair<key, value>(), 0);
                Data[0].x = _Key;
                m_mutex.unlock();
                return Data[0].y;
            }
            }
        } else if (Data.Size() == 2) {
            if (Data[0].x == _Key) {
            m_mutex.unlock();
            return Data[0].y;
            }
            if (Data[1].x == _Key) {
            m_mutex.unlock();
            return Data[1].y;
            }

            if(Data[0].x > _Key) {
            Data.Insert(Pair<key, value>(), 0);
            Data[0].x = _Key;
            m_mutex.unlock();
            return Data[0].y;
            }
            else if (Data[0].x < _Key) {
            if (Data[1].x > _Key) {
                Data.Insert(Pair<key, value>(), 1);
                Data[1].x = _Key;
                m_mutex.unlock();
                return Data[1].y;
            } else {
                Data.Insert(Pair<key, value>(), 2);
                Data[2].x = _Key;
                m_mutex.unlock();
                return Data[2].y;
            }
            }
        } else {
            size_t l = 0, r = Data.Size(), p = (l + r) / 2;

            if (Data[l].x == _Key) {
            m_mutex.unlock();
            return Data[l].y;
            }
            if (Data[r].x == _Key) {
            m_mutex.unlock();
            return Data[r].y;
            }
            if (Data[p].x == _Key) {
            m_mutex.unlock();
            return Data[p].y;
            }

            while (true) {
            if (Data[p].x == _Key) {
                m_mutex.unlock();
                return Data[p].y;
            }

            else if (Data[p].x > _Key)
                r = p;
            else l = p;

            p = (l + r) / 2;
            if (p == l || p == r)
                break;
            }
            if (Data[p].x < _Key) {
            Data.Insert(Pair<key, value>(), p + 1);
            Data[p + 1].x = _Key;
            m_mutex.unlock();
            return Data[p + 1].y;
            }else{
            Data.Insert(Pair<key, value>(), p);
            Data[p].x = _Key;
            m_mutex.unlock();
            return Data[p].y;
            }
        }
        m_mutex.unlock();
        return *(value*)nullptr;
        }
        value& GetValueWithKey(const key &_Key, bool &isNew) {
        isNew = false;
        if (Data.Size() == 0) {
            Data.Push_Back(Pair<key, value>());
            isNew = true;
            Data[0].x = _Key;
            return Data[0].y;
        } else if (Data.Size() == 1) {
            if (Data[0].x == _Key)
            return Data[0].y;
            else {
            if (Data[0].x < _Key) {
                Data.Insert(Pair<key, value>(), 1);
                isNew = true;
                Data[1].x = _Key;
                return Data[1].y;
            } else {
                Data.Insert(Pair<key, value>(), 0);
                isNew = true;
                Data[0].x = _Key;
                return Data[0].y;
            }
            }
        } else if (Data.Size() == 2) {
            if (Data[0].x == _Key)
            return Data[0].y;
            if (Data[1].x == _Key)
            return Data[1].y;

            if(Data[0].x > _Key) {
            Data.Insert(Pair<key, value>(), 0);
            isNew = true;
            Data[0].x = _Key;
            return Data[0].y;
            }
            else if (Data[0].x < _Key) {
            if (Data[1].x > _Key) {
                Data.Insert(Pair<key, value>(), 1);
                isNew = true;
                Data[1].x = _Key;
                return Data[1].y;
            } else {
                Data.Insert(Pair<key, value>(), 2);
                isNew = true;
                Data[2].x = _Key;
                return Data[2].y;
            }
            }
        } else {
            size_t l = 0, r = Data.Size(), p = (l + r) / 2;

            if (Data[l].x == _Key)
            return Data[l].y;
            if (Data[r].x == _Key)
            return Data[r].y;
            if (Data[p].x == _Key)
            return Data[p].y;

            while (true) {
            if (Data[p].x == _Key)
                return Data[p].y;

            else if (Data[p].x > _Key)
                r = p;
            else l = p;

            p = (l + r) / 2;
            if (p == l || p == r)
                break;
            }
            if (Data[p].x < _Key) {
            Data.Insert(Pair<key, value>(), p + 1);
            isNew = true;
            Data[p + 1].x = _Key;
            return Data[p + 1].y;
            }else{
            Data.Insert(Pair<key, value>(), p);
            isNew = true;
            Data[p].x = _Key;
            return Data[p].y;
            }
        }
        }
        /**
        * \brief Map overload operator[](key)
        * \arg _Key - key to get value reference
        */
        bool GetOnly(const key &_Key, value* value1){
        m_mutex.lock();

        if (Data.Size() == 0) {
            m_mutex.unlock();
            return false;
        } else if (Data.Size() == 1) {
            if (Data[0].x == _Key){
            (*value1) = Data[0].y;
            m_mutex.unlock();
            return true;
            }
            else {
            m_mutex.unlock();
            return false;
            }
        } else if (Data.Size() == 2) {
            if (Data[0].x == _Key){
            (*value1) = Data[0].y;
            m_mutex.unlock();
            return true;
            }
            if (Data[1].x == _Key){
            (*value1) = Data[1].y;
            m_mutex.unlock();
            return true;
            }

            if(Data[0].x > _Key) {
            m_mutex.unlock();
            return false;
            }
            else if (Data[0].x < _Key) {
            m_mutex.unlock();
            return false;
            }
        } else {
            size_t l = 0, r = Data.Size(), p = (l + r) / 2;

            if (Data[l].x == _Key){
            (*value1) = Data[l].y;
            m_mutex.unlock();
            return true;
            }
            if (Data[r].x == _Key){
            (*value1) = Data[r].y;
            m_mutex.unlock();
            return true;
            }
            if (Data[p].x == _Key){
            (*value1) = Data[p].y;
            m_mutex.unlock();
            return true;
            }

            while (true) {
            if (Data[p].x == _Key) {
                (*value1) = Data[p].y;
                m_mutex.unlock();
                return true;
            }

            else if (Data[p].x > _Key)
                r = p;
            else l = p;

            p = (l + r) / 2;
            if (p == l || p == r)
                break;
            }
            m_mutex.unlock();
            return false;
        }
        m_mutex.unlock();
        return false;
        }

        /**
         * \brief Map is empty function
         */
        bool IsEmpty(){
        return this->Data.IsEmpty();
        }
        /**
         * \brief Map clear function
         */
        void Clear(){
        m_mutex.lock();
        this->Data.Clear();
        m_mutex.unlock();
        }

        /**
         * \brief Map begin method
         */
        Pair<key, value>* begin(){
        return Data.begin();
        }
        /**
         * \brief Map end method
         */
        Pair<key, value>* end(){
        return Data.end();
        }

    private:
        std::mutex m_mutex = std::mutex();
        Vector<Pair<key, value>> Data;
    };
    }

#endif //GAME_MAP_H
