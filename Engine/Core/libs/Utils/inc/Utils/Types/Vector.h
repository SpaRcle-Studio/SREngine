//
// Created by kiper220 on 22.05.2020.
//
#ifndef EVOENGINE_VECTOR_H
#define EVOENGINE_VECTOR_H

#include <Utils/stdInclude.h>

// TODO: Check, refactoring and add exception processing

namespace SR_HTYPES_NS {
    /**
     *
     * \brief Red Template Library Vector
     * \authors WetGrape | Kiper220
     * \copyright GNU LGPL
     *
     **/

    template<typename type>
    class SR_DLL_EXPORT Vector {
        typedef const type* const_iterator;
        typedef type* iterator;
        typedef Vector<type> && Move_Type;
    public:
        /**
         * Standart zero constructor
         */
        Vector(): _array(nullptr), _size(0) {}
        /**
         * Standard copy constructor
         * \arg vector - target copy;
         */
        Vector(const Vector& vector): _size(vector._size) {
            this->_array = new type[this->_size];
            if(this->_array == nullptr) exit(11);

            for(size_t i = 0; i < this->_size; i++)
                this->_array[i] = vector._array[i];
        }
        /**
         * Standard move constructor
         * \arg vector - target move;
         */
        Vector(Vector&& vector): _array(vector._array), _size(vector._size) {
            vector._array = nullptr;
            vector._size = 0;
        }
        /**
         * Standard constructor copy of static array
         * \arg array - static array;
         */
        Vector(std::initializer_list<type> array){
            this->_array = new type[this->_size];
            if(this->_array == nullptr) exit(11);

            for(size_t i = 0; i < this->_size; i++)
                this->_array[i] = array.begin()[i];
        }
        /**
         * Constructor with a dynamic array argument
         * \arg array - dynamic array;
         * \arg size - size of array;
         */
        Vector(const_iterator array, size_t size):_size(size) {
            this->_array = new type[this->_size];
            if(this->_array == nullptr) exit(11);

            for(size_t i = 0; i < this->_size; i++)
                this->_array[i] = array[i];
        }
        /**
         * Constructor with an argument for the beginning and end of the array
         * \arg _begin - begin of array;
         * \arg _end - end of array;
         */
        Vector(const_iterator _begin, const_iterator _end): _size(_end - _begin) {
            this->_array = new type[this->_size];
            if(this->_array == nullptr) exit(11);

            for(size_t i = 0; i < this->_size; i++)
                this->_array[i] = _begin[i];
        }

        /**
         * Overload operator copy
         * \arg vector - target copy;
         */
        Vector& operator=(const Vector& vector) {
            delete [] this->_array;

            _size = vector._size;
            this->_array = new type[this->_size];
            if(this->_array == nullptr) exit(11);

            for(size_t i = 0; i < this->_size; i++)
                this->_array[i] = vector._array[i];

            return *this;
        }
        /**
         * Overload operator move
         * \arg vector - target move;
         */
        Vector& operator=(Vector&& vector) {
            delete [] this->_array;

            _size = vector._size;
            this->_array = vector._array;

            vector._array = nullptr;
            vector._size = 0;

            return *this;
        }

        /**
         * Insert vector method
         * \arg type1 - insert data;
         * \arg element - insert element position;
         */
        void Insert(const type &&type1, size_t element) {
            if(element > this->_size) element = this->_size;
            iterator tmp = new type[++this->_size];
            if(tmp == nullptr) exit(11);
            size_t i = 0;
            for(; i < element; i++)
                tmp[i] = this->_array[i];
            tmp[i] = type1;
            for(++i; i < this->_size; i++)
                tmp[i] = this->_array[i - 1];

            delete [] this->_array;
            this->_array = tmp;
        }
        /**
         * Insert vector method
         * \arg type1 - insert Data;
         * \arg element - insert element position;
         */
        void Erase(size_t element) {
            m_mutex.lock();

            if(element >= this->_size) element = this->_size - 1;
            iterator tmp = new type[--this->_size];
            if(tmp == nullptr) exit(11);

            size_t i = 0;
            for(; i < element; i++)
                tmp[i] = this->_array[i];
            i++;
            for(; i < this->_size; i++)
                tmp[i] = this->_array[i];

            delete [] this->_array;
            this->_array = tmp;

            m_mutex.unlock();
        }
        /**
         * Insert move method
         * \arg type1 - insert data;
         * \arg element - insert element position;
         */
        void Move(type &&type1, size_t element) {
            this->_array[element] = type1;
        }
        /**
         * Get method of vector siye
         * \return size of array
         */
        size_t Size() const{
            return this->_size;
        }

        /**
         * Begin method for foreach
         * \return size of array
         */
        type* begin(){
            return &this->_array[0];
        }
        /**
         * Begin(const) method for foreach
         * \return size of array
         */
        const type* begin() const{
            return &this->_array[0];
        }

        /**
         * End method for foreach
         * \return size of array
         */
        type* end(){
            if(this->_array != nullptr)
                return &this->_array[this->_size];
            return nullptr;
        }
        /**
         * End(const) method for foreach
         * \return size of array
         */
        const type* end() const{
            if(this->_array != nullptr)
                return &this->_array[this->_size];
            return nullptr;
        }

        /**
         * Set size method
         * \arg _size - New vector size;
         */
        void SetSize(size_t _size) {
            iterator tmp = new type[_size];
            if(tmp == nullptr) exit(11);

#ifdef min
            size_t t = min(this->_size, _size);
#else
            size_t t = std::min(this->_size, _size);
#endif

            for(size_t i = 0; i < t; i++)
                tmp[i] = this->_array[i];

            delete [] this->_array;
            this->_array = tmp;
        }
        /**
         * Push back method
         * \arg type1 - target data to insert in end of vector;
         */
        void Push_Back(type type1) {
            m_mutex.lock();

            this->Insert(std::move(type1), this->_size);

            m_mutex.unlock();
        }
        /**
         * Pop back method
         * \arg element -  target element position to erase;
         */
        void Pop_Back() {
            this->Erase(this->_size);
        }
        /**
         * The overloading operator method of the "[]"
         * \arg _element - element id in vector;
         * \return Reference to an vector element;
         * \warning If vector is clear, then this method return (nullptr);
         */
        type& operator[](size_t _element) {
            m_mutex.lock();

            if(this->_array == nullptr) {
                m_mutex.unlock();
                std::cout << "Types::Vector::operator[] : _array is nullptr!\n";
                return *static_cast<type *>(nullptr);
            }
            if(_element >= this->_size)
                _element = this->_size - 1;

            m_mutex.unlock();
            return this->_array[_element];
        }
        /**
         * The overloading operator method of the "[]"
         * \arg _element - element id in vector;
         * \return Reference to an vector element;
         * \warning If vector is clear, then this method return (nullptr);
         *//*
        const type& operator[](size_t _element) const{
            m_mutex.lock();

            if(this->_array == nullptr) {
                m_mutex.unlock();
                std::cout << "Types::Vector::operator[] : _array is nullptr!\n";
                return *static_cast<type *>(nullptr);
            }
            if(_element >= this->_size)
                _element = this->_size - 1;

            m_mutex.unlock();
            return this->_array[_element];
        }*/
        /**
         * Is empty function
         * \return Return vector is empty
         */
        bool IsEmpty() {
            return this->_size == 0;
        }
        /**
         * Clear vector function
         */
        void Clear() {
            delete [] this->_array;
            this->_array = nullptr;
            this->_size = 0;
        }
        /**
         * Vector Data
         */
        iterator Data() {
            return this->_array;
        }
        /**
         * Standart vector destructor
         */
        ~Vector() {
            delete [] this->_array;
            this->_array = nullptr;
            _size = 0;
        }

    private:
        iterator _array;
        size_t _size;
        std::mutex m_mutex;
    };
}

#endif //EVOENGINE_VECTOR_H
