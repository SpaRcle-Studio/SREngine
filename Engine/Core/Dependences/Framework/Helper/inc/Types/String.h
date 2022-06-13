//
// Created by kiper220 on 22.05.2020.
//

#ifndef GAME_STRING_H
#define GAME_STRING_H

#include <Debug.h>

// TODO: Check, refactoring and add exception processing

namespace Framework::Helper::Types{
    /**
 *
 * \brief Red Template Library String class
 * \authors WetGrape | kiper220
 *
 */
    class String{
    public:
        /**
         * \brief Standart String constructor
         * */
        String();
        /**
         * \brief String copy constructor
         * \arg string - target string;
         * */
        String(const String& string);
        /**
         * \brief String move constructor
         * \arg string - target string;
         * */
        String(String&& string);
        /**
         * \brief String (const char*) constructor
         * \arg string - target string;
         * */
        String(const char* string);

         /**
         * \brief Standart String destructor
         * \arg string - target string;
         * */
        ~String();

        /**
         * \brief String overload operator of copy
         * \arg string - target string;
         * */
        String& operator =(const String& string);
        /**
         * \brief String overload operator of move
         * \arg string - target string;
         * */
        String& operator =(String&& string);
        /**
         * \brief String overload operator=(const char*)
         * \arg string - target string;
         * */
        String& operator =(const char* string);

        /**
         * \brief String overload operator+=
         * \arg string - target string;
         * */
        String& operator +=(const String& string);
        /**
         * \brief String overload operator+=
         * \arg string - target string;
         * */
        String& operator +=(String&& string);
        /**
         * \brief String overload operator+=
         * \arg string - target string;
         * */
        String& operator +=(const char* string);

        /**
         * \brief String overload operator+
         * \arg string - target string;
         * */
        String operator +(const String& string) const;
        /**
         * \brief String overload operator+
         * \arg string - target string;
         * */
        String operator +(String&& string) const;
        /**
         * \brief String overload operator+
         * \arg string - target string;
         * */
        String operator +(const char* string) const;

        /**
         * \brief String overload operator()
         * \arg string - target string;
         * */
        void operator ()(const String& string);
        /**
         * \brief String overload operator()
         * \arg string - target string;
         * */
        void operator ()(String&& string);
        /**
         * \brief String overload operator()
         * \arg string - target string;
         * */
        void operator ()(const char* string);

        /**
         * \brief String overload operator==
         * \arg string - target string;
         * */
        bool operator ==(const String& string);
        /**
         * \brief String overload operator==
         * \arg string - target string;
         * */
        bool operator ==(String&& string);
        /**
         * \brief String overload operator==
         * \arg string - target string;
         * */
        bool operator ==(const char* string);

        /**
         * \brief String overload operator!=
         * \arg string - target string;
         * */
        bool operator !=(const String& string);
        /**
         * \brief String overload operator!=
         * \arg string - target string;
         * */
        bool operator !=(String&& string);
        /**
         * \brief String overload operator!=
         * \arg string - target string;
         * */
        bool operator !=(const char* string);

        /**
         * \brief String overload operator>
         * \arg string - target string;
         * */
        bool operator >(const String& string);
        /**
         * \brief String overload operator>
         * \arg string - target string;
         * */
        bool operator >(String&& string);
        /**
         * \brief String overload operator>
         * \arg string - target string;
         * */
        bool operator >(const char* string);

        /**
         * \brief String overload operator>=
         * \arg string - target string;
         * */
        bool operator >=(const String& string);
        /**
         * \brief String overload operator>=
         * \arg string - target string;
         * */
        bool operator >=(String&& string);
        /**
         * \brief String overload operator>=
         * \arg string - target string;
         * */
        bool operator >=(const char* string);

        /**
         * \brief String overload operator<
         * \arg string - target string;
         * */
        bool operator <(const String& string);
        /**
         * \brief String overload operator<
         * \arg string - target string;
         * */
        bool operator <(String&& string);
        /**
         * \brief String overload operator<
         * \arg string - target string;
         * */
        bool operator <(const char* string);

        /**
         * \brief String overload operator<=
         * \arg string - target string;
         * */
        bool operator <=(const String& string);
        /**
         * \brief String overload operator<=
         * \arg string - target string;
         * */
        bool operator <=(String&& string);
        /**
         * \brief String overload operator<=
         * \arg string - target string;
         * */
        bool operator <=(const char* string);

        /**
         * \brief String overload operator[]
         * \arg string - target string;
         * */
        char& operator [](size_t position);

        /**
         * \brief String set method
         * \arg string - target string;
         * */
        void Set(const String& string);
        /**
         * \brief String set method
         * \arg string - target string;
         * */
        void Set(String&& string);
        /**
         * \brief String set method
         * \arg string - target string;
         * */
        void Set(const char* string);

        /**
         * \brief String concatenate method
         * \arg string - target string;
         * */
        void Concatenate(const String& string);
        /**
         * \brief String concatenate method
         * \arg string - target string;
         * */
        void Concatenate(String&& string);
        /**
         * \brief String concatenate method
         * \arg string - target string;
         * */
        void Concatenate(const char* string);

        /**
         * \brief String insert method
         * \arg string - target string;
         * */
        void Insert(String& string, size_t pos);
        /**
         * \brief String insert method
         * \arg string - target string;
         * */
        void Insert(String&& string, size_t pos);
        /**
         * \brief String insert method
         * \arg string - target string;
         * */
        void Insert(const char* string, size_t pos);

        /**
         * \brief String trim in begin method
         * \arg string - target string;
         * */
        void TrimBegin();
        /**
         * \brief String trim in end method
         * \arg string - target string;
         * */
        void TrimEnd();
        /**
         * \brief String trim method
         * \arg string - target string;
         * */
        void Trim();

        /**
         * \brief STATIC String concatenate method
         * \arg string - target string;
         * */
        static String Concatenate(String& string1, String& string2);
        /**
         * \brief STATIC String concatenate method
         * \arg string - target string;
         * */
        static String Concatenate(String& string1, const char* string2);
        /**
         * \brief STATIC String concatenate method
         * \arg string - target string;
         * */
        static String Concatenate(const char* string1, String& string2);
        /**
         * \brief STATIC String concatenate method
         * \arg string - target string;
         * */
        static String Concatenate(const char* string1, const char* string2);

        /**
         * \brief STATIC String insert method
         * \arg string - target string;
         * */
        static String Insert(String& string1, String& string2, size_t pos);
        /**
         * \brief STATIC String insert method
         * \arg string - target string;
         * */
        static String Insert(String& string1, const char* string2, size_t pos);
        /**
         * \brief STATIC String insert method
         * \arg string - target string;
         * */
        static String Insert(const char* string1, String& string2, size_t pos);
        /**
         * \brief STATIC String insert method
         * \arg string - target string;
         * */
        static String Insert(const char* string1, const char* string2, size_t pos);
        /**
         * \brief STATIC String insert method
         * \arg string - target string;
         * */

        /**
         * \brief STATIC String trim in begin method
         * \arg string - target string;
         * */
        static void TrimBegin(String &string1);
        /**
         * \brief STATIC String trim in end method
         * \arg string - target string;
         * */
        static void TrimEnd(String &string1);
        /**
         * \brief STATIC String trim method
         * \arg string - target string;
         * */
        static void Trim(String &string1);

        /**
         * \brief String cut method
         * \arg _start - new string start;
         * */
        void Cut(size_t _start);
        /**
         * \brief String cut method
         * \arg _start - new string start;
         * \arg _end - new string end;
         * */
        void Cut(size_t _start, size_t _end);

        /**
         * \brief String wrest method
         * \arg _start - new string start;
         * */
        [[nodiscard]] String Wrest(size_t _start) const;
        /**
         * \brief String wrest method
         * \arg _start - new string start;
         * \arg _end - new string end;
         * */
        [[nodiscard]] String Wrest(size_t _start, size_t _end) const;
        /**
         * \brief String size method
         * \return Size of String
         * */
        [[nodiscard]] size_t Size() const;

        /**
         * \brief String clear method
         * */
        void Clear();

        /**
         * \brief String is empty
         * \return is empty
         * */
        [[nodiscard]] bool IsEmpty() const;

        /**
         * \brief String overload operator(const char*)
         * \arg string - target string;
         * */
        explicit operator const char*() const;
    private:
        char* str;
    };
}

#endif //GAME_STRING_H
