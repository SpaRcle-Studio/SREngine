//
// Created by Nikita on 17.11.2020.
//

#include <Utils/Common/StringUtils.h>

namespace SR_UTILS_NS {
    std::string StringUtils::GetExtensionFromFilePath(std::string path) {
        size_t size = path.size() - 1;
        std::string result;
        bool found = false;
        for (long long l = size; l >= 0; l--) {
            if (path[l] == '/' || path[l] == '\\')
                break;
            else if (path[l] == '.') {
                found = true;
                break;
            } else
                result += path[l];
        }

        if (!found) return "";

        result = Reverse(result);
        return result;
    }

    std::string StringUtils::Reverse(std::string str) {
        std::string result;
        for (size_t t = str.size(); t > 0; t--)
            result += str[t - 1];

        return result;
    }

    glm::vec2 StringUtils::MakeVec2FromString(const char *source, char chr, unsigned short start) {
        glm::vec2 position = glm::vec3();
        unsigned char found_floats = 0;

        unsigned short count = 0;
        unsigned short found = start;

        static short t = 0;
        static short len = 0;

        len = FastStrLen(source);

        for (t = start; t < len; t++) {
            count++;

            if (t + 1 == len) {
                if (found_floats == 2)
                    return position;

                char *temp = new char[count + 1];
                strcpy(temp, "");

                strncat(temp, source + found, count);
                position[found_floats] = (float) atof(temp);
                found_floats++;

                delete[] temp;

                return position;
            } else if (source[t] == chr) {
                if (found_floats == 2) //if (found_floats + 1 == 2) - bug
                    return position;

                char *temp = new char[count + 1];
                strcpy(temp, "");

                strncat(temp, source + found, count - 1);
                position[found_floats] = (float) atof(temp);
                found_floats++;

                delete[] temp;

                found = t + 1;
                count = 0;
            }
        }
        return position;
    }

    glm::vec3 StringUtils::MakeVec3FromString(const char *source, char chr, unsigned short start) {
        glm::vec3 position = glm::vec3();
        unsigned char found_floats = 0;

        unsigned short count = 0;
        unsigned short found = start;

        static short t = 0;
        static short len = 0;

        len = FastStrLen(source);

        for (t = start; t < len; t++) {
            count++;

            if (t + 1 == len) {
                if (found_floats == 3)
                    return position;

                char *temp = new char[count + 1];
                strcpy(temp, "");

                strncat(temp, source + found, count);
                position[found_floats] = (float) atof(temp);
                found_floats++;

                delete[] temp;

                return position;
            } else if (source[t] == chr) {
                if (found_floats + 1 == 3)
                    return position;

                char *temp = new char[count + 1];
                strcpy(temp, "");

                strncat(temp, source + found, count - 1);
                position[found_floats] = (float) atof(temp);
                found_floats++;

                delete[] temp;

                found = t + 1;
                count = 0;
            }
        }
        return position;
    }

    std::string StringUtils::ReadFrom(const std::string &str, const char &c, uint32_t start) {
        if (start >= str.size())
            return std::string();

        std::string newStr = str.substr(start, str.size() - 1);

        int32_t to = IndexOf(newStr, c);
        if (to <= 0)
            return std::string();

        return newStr.substr(0, to);
    }

    std::vector<std::string> StringUtils::Split(std::string source, const std::string &delimiter)  {
        size_t pos = 0;
        std::vector<std::string> tokens = {};
        while ((pos = source.find(delimiter)) != std::string::npos) {
            if (auto&& token = source.substr(0, pos); !token.empty())
                tokens.emplace_back(std::move(token));
            source.erase(0, pos + delimiter.length());
        }

        if (!source.empty())
            tokens.emplace_back(source);

        return tokens;
    }

    std::string StringUtils::Tab(std::string code, uint32_t count) {
        if (!code.empty()) {
            code = std::string(count, '\t') + code;

            uint64_t lastPos = 0;

            do {
                const auto pos = code.find("\n", lastPos);
                lastPos = pos + 1;

                if (pos == std::string::npos || pos + 1 == code.size()) {
                    break;
                }

                code.insert(pos + 1, std::string(count, '\t'));
            }
            while (true);
        }

        return code;
    }

    std::string StringUtils::Base64Encode(const std::string &data) {
        int in_len = data.size();
        char* bytes_to_encode = (char*)(data.data());

        std::string ret;
        int i = 0;
        int j = 0;
        unsigned char char_array_3[3];
        unsigned char char_array_4[4];

        while (in_len--) {
            char_array_3[i++] = *(bytes_to_encode++);
            if (i == 3) {
                char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
                char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
                char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
                char_array_4[3] = char_array_3[2] & 0x3f;

                for(i = 0; (i <4) ; i++)
                    ret += base64_chars[char_array_4[i]];
                i = 0;
            }
        }

        if (i)
        {
            for(j = i; j < 3; j++)
                char_array_3[j] = '\0';

            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (j = 0; (j < i + 1); j++)
                ret += base64_chars[char_array_4[j]];

            while((i++ < 3))
                ret += '=';

        }

        return ret;
    }

    std::string StringUtils::Base64Decode(const std::string & base64) {
        int in_len = base64.size();
        int i = 0;
        int j = 0;
        int in_ = 0;
        unsigned char char_array_4[4], char_array_3[3];
        std::string ret;

        while (in_len-- && (base64[in_] != '=') && is_base64(base64[in_])) {
            char_array_4[i++] = base64[in_]; in_++;
            if (i ==4) {
                for (i = 0; i <4; i++)
                    char_array_4[i] = base64_chars.find(char_array_4[i]);

                char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
                char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
                char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

                for (i = 0; (i < 3); i++)
                    ret += char_array_3[i];
                i = 0;
            }
        }

        if (i) {
            for (j = i; j <4; j++)
                char_array_4[j] = 0;

            for (j = 0; j <4; j++)
                char_array_4[j] = base64_chars.find(char_array_4[j]);

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
        }

        return ret;
    }

    std::string StringUtils::Remove(std::string source, uint32_t count) {
        return source.substr(count, source.size() - count);
    }

    std::string StringUtils::Remove(std::string source, uint32_t start, uint32_t count) {
        const uint64_t size = source.size();

        if (static_cast<int64_t>(size) - count < 0) {
            SRHalt("StringUtils::Remove() : out of range!");
            return std::string();
        }

        return source.substr(count + start, size - count);
    }
}
