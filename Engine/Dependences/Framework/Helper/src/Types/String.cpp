//
// Created by kiper220 on 22.05.2020.
//

#include <Types/String.h>
#include <cstring>
#include <algorithm>

namespace Framework::Helper { namespace Types{
    String::String() {
        this->str = nullptr;
    }
    String::String(const String& string) {
        if(string.str == nullptr) {
            this->str = nullptr;
            return;
        }
        size_t s = strlen(string.str);
        this->str = new char[s + 1];

        for(size_t i = 0; i < s; i++)
            this->str[i] = string.str[i];

        this->str[s] = '\0';
    }
    String::String(String&& string) {
        this->str = string.str;
        string.str = nullptr;
    }
    String::String(const char* string) {
        if(string == nullptr) {
            this->str = nullptr;
            return;
        }
        size_t s = strlen(string);
        this->str = new char[s + 1];

        for(size_t i = 0; i < s; i++)
            this->str[i] = string[i];

        this->str[s] = '\0';
    }

    String& String::operator =(const String& string) {
        delete [] this->str;
        if(string.str == nullptr || &string == nullptr) {
            this->str = nullptr;
            return *this;
        }
        size_t s = strlen(string.str);
        this->str = new char[s + 1];

        for(size_t i = 0; i < s; i++)
            this->str[i] = string.str[i];

        this->str[s] = '\0';
        return *this;
    }
    String& String::operator =(String&& string) {
        delete [] this->str;

        this->str = string.str;
        string.str = nullptr;
        return *this;
    }
    String& String::operator =(const char* string) {
        delete [] this->str;
        if(string == nullptr) {
            this->str = nullptr;
            return *this;
        }
        size_t s = strlen(string);
        this->str = new char[s + 1];

        for(size_t i = 0; i < s; i++)
            this->str[i] = string[i];

        this->str[s] = '\0';
        return *this;
    }

    String& String::operator +=(const String& string) {
        this->Concatenate(string);
        return *this;
    }
    String& String::operator +=(String&& string) {
        this->Concatenate(string);
        return *this;
    }
    String& String::operator +=(const char* string) {
        this->Concatenate(string);
        return *this;
    }

    String String::operator +(const String& string) const{
        String tmp = *this;
        tmp.Concatenate(string);
        return tmp;
    }
    String String::operator +(String&& string) const{
        String tmp = *this;
        tmp.Concatenate(string);
        return tmp;
    }
    String String::operator +(const char* string) const{
        String tmp = *this;
        tmp.Concatenate(string);
        return tmp;
    }

    void String::operator ()(const String& string) {
        delete [] this->str;
        if(string.str == nullptr) {
            this->str = nullptr;
        }
        size_t s = strlen(string.str);
        this->str = new char[s + 1];

        for(size_t i = 0; i < s; i++)
            this->str[i] = string.str[i];

        this->str[s] = '\0';
    }
    void String::operator ()(String&& string) {
        delete [] this->str;
        if(string.str == nullptr) {
            this->str = nullptr;
        }

        this->str = string.str;
        string.str = nullptr;
    }
    void String::operator ()(const char* string) {
        delete [] this->str;
        if(string == nullptr) {
            this->str = nullptr;
        }
        size_t s = strlen(string);
        this->str = new char[s + 1];

        for(size_t i = 0; i < s; i++)
            this->str[i] = string[i];

        this->str[s] = '\0';
    }

    bool String::operator ==(const String& string) {
        if(this->str == nullptr) {
            if(string.str == nullptr)
                return true;
            return false;
        }
        size_t s1 = strlen(this->str);
        if(s1 != strlen(string.str))
            return false;
        for (size_t i = 0; i < s1; ++i)
            if(this->str[i] != string.str[i])
                return false;

        return true;
    }
    bool String::operator ==(String&& string) {
        if(this->str == nullptr) {
            if(string.str == nullptr)
                return true;
            return false;
        }
        size_t s1 = strlen(this->str);
        if(s1 != strlen(string.str))
            return false;
        for (size_t i = 0; i < s1; ++i)
            if(this->str[i] != string.str[i])
                return false;

        return true;
    }
    bool String::operator ==(const char* string) {
        if(this->str == nullptr) {
            if(string == nullptr)
                return true;
            return false;
        }
        size_t s1 = strlen(this->str);
        if(s1 != strlen(string))
            return false;
        for (size_t i = 0; i < s1; ++i)
            if(this->str[i] != string[i])
                return false;

        return true;
    }

    bool String::operator !=(const String& string) {
        if(this->str == nullptr) {
            if(string.str == nullptr)
                return false;
            return true;
        }
        size_t s1 = strlen(this->str);
        if(s1 != strlen(string.str))
            return true;
        for (size_t i = 0; i < s1; ++i)
            if(this->str[i] != string.str[i])
                return true;

        return false;
    }
    bool String::operator !=(String&& string) {
        if(this->str == nullptr) {
            if(string.str == nullptr)
                return false;
            return true;
        }
        size_t s1 = strlen(this->str);
        if(s1 != strlen(string.str))
            return true;
        for (size_t i = 0; i < s1; ++i)
            if(this->str[i] != string.str[i])
                return true;

        return false;
    }
    bool String::operator !=(const char* string) {
        if(this->str == nullptr) {
            if(string == nullptr)
                return false;
            return true;
        }
        size_t s1 = strlen(this->str);
        if(s1 != strlen(string))
            return true;
        for (size_t i = 0; i < s1; ++i)
            if(this->str[i] != string[i])
                return true;

        return false;
    }

    bool String::operator >(const String& string) {
        if(this->str == nullptr) {
            if(string.str == nullptr)
                return false;
            return false;
        }
        size_t s1 = strlen(this->str), s2 = strlen(string.str);
        if(s1 == strlen(string.str)){
            size_t sum1 = 0, sum2 = 0;

            for(size_t i = 0; i < s1; i++){
                sum1 += this->str[i];
                sum2 += string.str[i];
            }
            if(sum1 > sum2)
                return true;
        }
        else if(s1 > s2)
            return true;
        return false;
    }
    bool String::operator >(String&& string) {
        if(this->str == nullptr) {
            if(string.str == nullptr)
                return false;
            return false;
        }
        size_t s1 = strlen(this->str), s2 = strlen(string.str);
        if(s1 == strlen(string.str)){
            size_t sum1 = 0, sum2 = 0;

            for(size_t i = 0; i < s1; i++){
                sum1 += this->str[i];
                sum2 += string.str[i];
            }
            if(sum1 > sum2)
                return true;
        }
        else if(s1 > s2)
            return true;
        return false;
    }
    bool String::operator >(const char* string) {
        if(this->str == nullptr) {
            if(string == nullptr)
                return false;
            return false;
        }
        size_t s1 = strlen(this->str), s2 = strlen(string);
        if(s1 == strlen(string)){
            size_t sum1 = 0, sum2 = 0;

            for(size_t i = 0; i < s1; i++){
                sum1 += this->str[i];
                sum2 += string[i];
            }
            if(sum1 > sum2)
                return true;
        }
        else if(s1 > s2)
            return true;
        return false;
    }

    bool String::operator >=(const String& string) {
        if(this->str == nullptr) {
            if(string.str == nullptr)
                return true;
            return false;
        }
        size_t s1 = strlen(this->str), s2 = strlen(string.str);
        if(s1 == strlen(string.str)){
            size_t sum1 = 0, sum2 = 0;

            for(size_t i = 0; i < s1; i++){
                sum1 += this->str[i];
                sum2 += string.str[i];
            }
            if(sum1 >= sum2)
                return true;
        }
        else if(s1 >= s2)
            return true;
        return false;
    }
    bool String::operator >=(String&& string) {
        if(this->str == nullptr) {
            if(string.str == nullptr)
                return true;
            return false;
        }
        size_t s1 = strlen(this->str), s2 = strlen(string.str);
        if(s1 == strlen(string.str)){
            size_t sum1 = 0, sum2 = 0;

            for(size_t i = 0; i < s1; i++){
                sum1 += this->str[i];
                sum2 += string.str[i];
            }
            if(sum1 >= sum2)
                return true;
        }
        else if(s1 >= s2)
            return true;
        return false;
    }
    bool String::operator >=(const char* string) {
        if(this->str == nullptr) {
            if(string == nullptr)
                return true;
            return false;
        }
        size_t s1 = strlen(this->str), s2 = strlen(string);
        if(s1 == strlen(string)){
            size_t sum1 = 0, sum2 = 0;

            for(size_t i = 0; i < s1; i++){
                sum1 += this->str[i];
                sum2 += string[i];
            }
            if(sum1 >= sum2)
                return true;
        }
        else if(s1 >= s2)
            return true;
        return false;
    }

    bool String::operator <(const String& string) {
        if(this->str == nullptr) {
            if(string.str == nullptr)
                return false;
            return true;
        }
        size_t s1 = strlen(this->str), s2 = strlen(string.str);
        if(s1 == strlen(string.str)){
            size_t sum1 = 0, sum2 = 0;

            for(size_t i = 0; i < s1; i++){
                sum1 += this->str[i];
                sum2 += string.str[i];
            }
            if(sum1 < sum2)
                return true;
        }
        else if(s1 < s2)
            return true;
        return false;
    }

    bool String::operator <(String&& string) {
        if(this->str == nullptr) {
            if(string.str == nullptr)
                return false;
            return true;
        }
        size_t s1 = strlen(this->str), s2 = strlen(string.str);
        if(s1 == strlen(string.str)){
            size_t sum1 = 0, sum2 = 0;

            for(size_t i = 0; i < s1; i++){
                sum1 += this->str[i];
                sum2 += string.str[i];
            }
            if(sum1 < sum2)
                return true;
        }
        else if(s1 < s2)
            return true;
        return false;
    }

    bool String::operator <(const char* string) {
        if(this->str == nullptr) {
            if(string == nullptr)
                return false;
            return true;
        }
        size_t s1 = strlen(this->str), s2 = strlen(string);
        if(s1 == strlen(string)){
            size_t sum1 = 0, sum2 = 0;

            for(size_t i = 0; i < s1; i++){
                sum1 += this->str[i];
                sum2 += string[i];
            }
            if(sum1 < sum2)
                return true;
        }
        else if(s1 < s2)
            return true;
        return false;
    }


    bool String::operator <=(const String& string) {
        if(this->str == nullptr) {
            if(string.str == nullptr)
                return true;
            return true;
        }
        size_t s1 = strlen(this->str), s2 = strlen(string.str);
        if(s1 == strlen(string.str)){
            size_t sum1 = 0, sum2 = 0;

            for(size_t i = 0; i < s1; i++){
                sum1 += this->str[i];
                sum2 += string.str[i];
            }
            if(sum1 <= sum2)
                return true;
        }
        else if(s1 <= s2)
            return true;
        return false;
    }

    bool String::operator <=(String&& string) {
        if(this->str == nullptr) {
            if(string.str == nullptr)
                return true;
            return true;
        }
        size_t s1 = strlen(this->str), s2 = strlen(string.str);
        if(s1 == strlen(string.str)){
            size_t sum1 = 0, sum2 = 0;

            for(size_t i = 0; i < s1; i++){
                sum1 += this->str[i];
                sum2 += string.str[i];
            }
            if(sum1 <= sum2)
                return true;
        }
        else if(s1 <= s2)
            return true;
        return false;
    }

    bool String::operator <=(const char* string) {
        if(this->str == nullptr) {
            if(string == nullptr)
                return true;
            return true;
        }
        size_t s1 = strlen(this->str), s2 = strlen(string);
        if(s1 == strlen(string)){
            size_t sum1 = 0, sum2 = 0;

            for(size_t i = 0; i < s1; i++){
                sum1 += this->str[i];
                sum2 += string[i];
            }
            if(sum1 <= sum2)
                return true;
        }
        else if(s1 <= s2)
            return true;
        return false;
    }

    char& String::operator [](size_t position){
        static char NULL_CHAR = '\0';
        if(this->str == nullptr) return NULL_CHAR;
        return this->str[std::min(position, strlen(this->str) - 1)];
    }

    void String::Set(const String& string) {
        delete [] this->str;
        if(string.str == nullptr) {
            this->str = nullptr;
            return;
        }
        size_t s = strlen(string.str);
        this->str = new char[s + 1];

        for(size_t i = 0; i < s; i++)
            this->str[i] = string.str[i];

        this->str[s] = '\0';

    }
    void String::Set(String&& string) {
        delete [] this->str;

        this->str = string.str;
        string.str = nullptr;
    }
    void String::Set(const char* string) {
        delete [] this->str;
        if(string == nullptr) {
            this->str = nullptr;
            return;
        }
        size_t s = strlen(string);
        this->str = new char[s + 1];

        for(size_t i = 0; i < s; i++)
            this->str[i] = string[i];

        this->str[s] = '\0';
    }

    void String::Concatenate(const String& string) {
        if(string.str == nullptr) {
            return;
        }else if(this->str == nullptr){
            *this = string;
            return;
        }
        size_t s1 = strlen(this->str), s2 = strlen(string.str), i = 0;
        char * tmp = new char[s1 + s2 + 1];

        for(; i < s1; i++)
            tmp[i] = this->str[i];

        for(size_t j = 0; j < s2; j++, i++)
            tmp[i] = string.str[j];

        tmp[i] = 0;

        delete [] this->str;
        this->str = tmp;
    }
    void String::Concatenate(String&& string) {
        if(string.str == nullptr) {
            return;
        }else if(this->str == nullptr){
            *this = string;
            return;
        }
        size_t s1 = strlen(this->str), s2 = strlen(string.str), i = 0;
        char * tmp = new char[s1 + s2 + 1];

        for(; i < s1; i++)
            tmp[i] = this->str[i];

        for(size_t j = 0; j < s2; j++, i++)
            tmp[i] = string.str[j];

        tmp[i] = 0;

        delete [] this->str;
        delete [] string.str;
        this->str = tmp;
        string.str = nullptr;
    }
    void String::Concatenate(const char* string) {
        if(string == nullptr) {
            return;
        }else if(this->str == nullptr){
            *this = string;
            return;
        }
        size_t s1 = strlen(this->str), s2 = strlen(string), i = 0;
        char * tmp = new char[s1 + s2 + 1];

        for(; i < s1; i++)
            tmp[i] = this->str[i];

        for(size_t j = 0; j < s2; j++, i++)
            tmp[i] = string[j];

        tmp[i] = 0;

        delete [] this->str;
        this->str = tmp;
    }

    void String::Insert(String& string, size_t pos) {
        if(string.str == nullptr) {
            return;
        }
        size_t s1 = strlen(this->str), s2 = strlen(string.str), s3 = s1 + s2 + 1, i = 0;
        char * tmp = new char[s1 + s2 + 1];


        for(; i < pos; i++)
            tmp[i] = this->str[i];

        for(size_t j = 0; j < s2; j++, i++)
            tmp[i] = string.str[j];

        for(size_t j = pos; j < s1; j++, i++)
            tmp[i] = this->str[i];

        tmp[i] = '\0';

        delete [] this->str;
        this->str = tmp;
    }
    void String::Insert(String&& string, size_t pos) {
        if(string.str == nullptr) {
            return;
        }
        size_t s1 = strlen(this->str), s2 = strlen(string.str), s3 = s1 + s2 + 1, i = 0;
        char * tmp = new char[s1 + s2 + 1];


        for(; i < pos; i++)
            tmp[i] = this->str[i];

        for(size_t j = 0; j < s2; j++, i++)
            tmp[i] = string.str[j];

        for(size_t j = pos; j < s1; j++, i++)
            tmp[i] = this->str[i];

        tmp[i] = '\0';

        delete [] this->str;
        this->str = tmp;
    }
    void String::Insert(const char* string, size_t pos) {
        if(string == nullptr) {
            return;
        }
        size_t s1 = strlen(this->str), s2 = strlen(string), s3 = s1 + s2 + 1, i = 0;
        char * tmp = new char[s1 + s2 + 1];


        for(; i < pos; i++)
            tmp[i] = this->str[i];

        for(size_t j = 0; j < s2; j++, i++)
            tmp[i] = string[j];

        for(size_t j = pos; j < s1; j++, i++)
            tmp[i] = this->str[i];

        tmp[i] = '\0';

        delete [] this->str;
        this->str = tmp;
    }


    void String::TrimBegin() {
        size_t i = 0;
        while((this->str[i] == ' ' || this->str[i] == '\t' || this->str[i] == '\n') && this->str[i] != '\0') i++;
        if(this->str[i] == '\0'){
            delete [] this->str;
            this->str = nullptr;
        }

        size_t s1 = strlen(this->str);
        char* tmp = new char[s1 - i + 1];

        for(size_t j = 0; i < s1; i++, j++)
            tmp[j] = this->str[i];

        delete [] this->str;
        this->str = tmp;
    }
    void String::TrimEnd() {
        size_t i = strlen(this->str);

        do i--;
        while((this->str[i] == ' ' || this->str[i] == '\t' || this->str[i] == '\n') && i != 0);

        if(i == 0){
            if(this->str[i] == ' ' && this->str[i] == '\t' && this->str[i] == '\n'){
                delete [] this->str;
                this->str = nullptr;
            }
            else{
                char s = this->str[0];
                delete[] this->str;
                this->str = new char[2];
                this->str[0] = s;
                this->str[1] = '\0';
            }
        }
        else{
            i++;
            char* tmp = new char[i + 1];

            for(size_t j = 0; j < i; j++)
                tmp[j] = this->str[j];

            tmp[i] = '\0';
            delete [] this->str;
            this->str = tmp;
        }
    }
    void String::Trim() {
        this->TrimBegin();
        this->TrimEnd();
    }

/*static*/ String String::Concatenate(String& string1, String& string2) {
        if(string2.str == nullptr) {
            return string1;
        }
        if(string1.str == nullptr) {
            return string2;
        }
        size_t s1 = strlen(string1.str), s2 = strlen(string2.str), i = 0;
        String tmp;
        tmp.str = new char[s1 + s2 + 1];

        for(; i < s1; i++)
            tmp.str[i] = string1.str[i];

        for(size_t j = 0; j < s2; j++, i++)
            tmp.str[i] = string2.str[j];

        tmp.str[i] = 0;

        return tmp;
    }
/*static*/ String String::Concatenate(String& string1, const char* string2) {
        if(string2 == nullptr) {
            return string1;
        }
        if(string1.str == nullptr) {
            return string2;
        }
        size_t s1 = strlen(string1.str), s2 = strlen(string2), i = 0;
        String tmp;
        tmp.str = new char[s1 + s2 + 1];

        for(; i < s1; i++)
            tmp.str[i] = string1.str[i];

        for(size_t j = 0; j < s2; j++, i++)
            tmp.str[i] = string2[j];

        tmp.str[i] = 0;

        return tmp;
    }
/*static*/ String String::Concatenate(const char* string1, String& string2) {
        if(string2.str == nullptr) {
            return string1;
        }
        if(string1 == nullptr) {
            return string2;
        }
        size_t s1 = strlen(string1), s2 = strlen(string2.str), i = 0;
        String tmp;
        tmp.str = new char[s1 + s2 + 1];

        for(; i < s1; i++)
            tmp.str[i] = string1[i];

        for(size_t j = 0; j < s2; j++, i++)
            tmp.str[i] = string2.str[j];

        tmp.str[i] = 0;

        return tmp;
    }
/*static*/ String String::Concatenate(const char* string1, const char* string2) {
        if(string2 == nullptr) {
            return string1;
        }
        if(string1 == nullptr) {
            return string2;
        }
        size_t s1 = strlen(string1), s2 = strlen(string2), i = 0;
        String tmp;
        tmp.str = new char[s1 + s2 + 1];

        for(; i < s1; i++)
            tmp.str[i] = string1[i];

        for(size_t j = 0; j < s2; j++, i++)
            tmp.str[i] = string2[j];

        tmp.str[i] = 0;

        return tmp;
    }

/*static*/ String String::Insert(String& string1, String& string2, size_t pos) {
        if(string2.str == nullptr) {
            return string1;
        }
        if(string1.str == nullptr) {
            return string2;
        }
        size_t s1 = strlen(string1.str), s2 = strlen(string2.str), s3 = s1 + s2 + 1, i = 0;
        String tmp;
        tmp.str = new char[s1 + s2 + 1];

        for(; i < pos; i++)
            tmp.str[i] = string1.str[i];

        for(size_t j = 0; j < s2; j++, i++)
            tmp.str[i] = string2.str[j];

        for(size_t j = pos; j < s1; j++, i++)
            tmp.str[i] = string1.str[i];

        tmp.str[i] = '\0';

        return tmp;
    }
/*static*/ String String::Insert(String& string1, const char* string2, size_t pos) {
        if(string2 == nullptr) {
            return string1;
        }
        if(string1.str == nullptr) {
            return string2;
        }
        size_t s1 = strlen(string1.str), s2 = strlen(string2), s3 = s1 + s2 + 1, i = 0;
        String tmp;
        tmp.str = new char[s1 + s2 + 1];

        for(; i < pos; i++)
            tmp.str[i] = string1.str[i];

        for(size_t j = 0; j < s2; j++, i++)
            tmp.str[i] = string2[j];

        for(size_t j = pos; j < s1; j++, i++)
            tmp.str[i] = string1.str[i];

        tmp.str[i] = '\0';

        return tmp;
    }
/*static*/ String String::Insert(const char* string1, String& string2, size_t pos) {
        if(string2.str == nullptr) {
            return string1;
        }
        if(string1 == nullptr) {
            return string2;
        }
        size_t s1 = strlen(string1), s2 = strlen(string2.str), s3 = s1 + s2 + 1, i = 0;
        String tmp;
        tmp.str = new char[s1 + s2 + 1];

        for(; i < pos; i++)
            tmp.str[i] = string1[i];

        for(size_t j = 0; j < s2; j++, i++)
            tmp.str[i] = string2.str[j];

        for(size_t j = pos; j < s1; j++, i++)
            tmp.str[i] = string1[i];

        tmp.str[i] = '\0';

        return tmp;
    }
/*static*/ String String::Insert(const char* string1, const char* string2, size_t pos) {
        if(string2 == nullptr) {
            return string1;
        }
        if(string1 == nullptr) {
            return string2;
        }
        size_t s1 = strlen(string1), s2 = strlen(string2), s3 = s1 + s2 + 1, i = 0;
        String tmp;
        tmp.str = new char[s1 + s2 + 1];

        for(; i < pos; i++)
            tmp.str[i] = string1[i];

        for(size_t j = 0; j < s2; j++, i++)
            tmp.str[i] = string2[j];

        for(size_t j = pos; j < s1; j++, i++)
            tmp.str[i] = string1[i];

        tmp.str[i] = '\0';

        return tmp;
    }
/*static*/ void String::TrimBegin(String &string1) {
        return string1.TrimBegin();
    }
/*static*/ void String::TrimEnd(String &string1) {
        return string1.TrimEnd();
    }
/*static*/ void String::Trim(String &string1) {
        return; string1.Trim();
    }

    void String::Cut(size_t _start) {
        size_t s = strlen(this->str);
        if(_start == s) {
            delete[] this->str;
            this->str = nullptr;
        }
        char* tmp = new char[s - _start + 1];

        for(size_t i = 0, j = _start; j < s; i++, j++)
            tmp[i] = this->str[j];

        tmp[s - _start] = '\0';
        delete [] this->str;
        this->str = tmp;
    }
    void String::Cut(size_t _start, size_t _end) {
        if(_start == _end) {
            delete[] this->str;
            this->str = nullptr;
        }
        size_t s = strlen(this->str);
        char* tmp = new char[s - _start - (s - _end) + 1];

        for(size_t i = 0, j = _start; j < _end; i++, j++)
            tmp[i] = this->str[j];

        tmp[s - _start - (s - _end)] = '\0';
        delete [] this->str;
        this->str = tmp;
    }


    String String::Wrest(size_t _start) const{
        size_t s = strlen(this->str), ns = s - _start;
        if(_start == s) return String();
        String string;
        string.str = new char[ns + 1];

        for(size_t i = _start, j = 0; i < s; i++, j++)
            string.str[j] = this->str[i];

        string.str[ns] = '\0';
        return string;
    }
    String String::Wrest(size_t _start, size_t _end) const{
        if(_start == _end) return String();
        size_t s = strlen(this->str), ns = s - (_start + (s - _end));
        String string;
        string.str = new char[ns + 1];

        for(size_t i = _start, j = 0; i < _end; i++, j++)
            string.str[j] = this->str[i];

        string.str[ns] = '\0';
        return string;
    }

    size_t String::Size() const{
        if(this->str == nullptr)
            return 0;
        return strlen(this->str);
    }

    void String::Clear(){
        delete [] this->str;
        this->str = nullptr;
    }

    bool String::IsEmpty() const{
        return this->str == nullptr;
    }

    String::operator const char*() const{
        return this->str;
    }

    String::~String() {
        delete [] this->str;
        this->str = nullptr;
    }
} }