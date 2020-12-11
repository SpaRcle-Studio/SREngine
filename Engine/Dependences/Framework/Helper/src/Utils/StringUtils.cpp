//
// Created by Nikita on 17.11.2020.
//

#include "Utils/StringUtils.h"

namespace Framework::Helper {
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
        glm::vec2		position = glm::vec3();
        unsigned char   found_floats = 0;

        unsigned short	count = 0;
        unsigned short	found = start;

        static short t = 0;
        static short len = 0;

        len = FastStrLen(source);

        for (t = start; t < len; t++) {
            count++;

            if (t + 1 == len) {
                if (found_floats == 2)
                    return position;

                char* temp = new char[count + 1]; strcpy(temp, "");

                strncat(temp, source + found, count);
                position[found_floats] = (float)atof(temp);
                found_floats++;

                delete[] temp;

                return position;
            }
            else if (source[t] == chr) {
                if (found_floats == 2) //if (found_floats + 1 == 2) - bug
                    return position;

                char* temp = new char[count + 1]; strcpy(temp, "");

                strncat(temp, source + found, count - 1);
                position[found_floats] = (float)atof(temp);
                found_floats++;

                delete[] temp;

                found = t + 1;
                count = 0;
            }
        }
        return position;
    }
    glm::vec3 StringUtils::MakeVec3FromString(const char *source, char chr, unsigned short start) {
        glm::vec3		position		= glm::vec3();
        unsigned char   found_floats	= 0;

        unsigned short	count			= 0;
        unsigned short	found			= start;

        static short t					= 0;
        static short len				= 0;

        len = FastStrLen(source);

        for (t = start; t < len; t++) {
            count++;

            if (t + 1 == len) {
                if (found_floats == 3)
                    return position;

                char* temp = new char[count + 1]; strcpy(temp, "");

                strncat(temp, source + found, count);
                position[found_floats] = (float)atof(temp);
                found_floats++;

                delete[] temp;

                return position;
            }
            else if (source[t] == chr) {
                if (found_floats + 1 == 3)
                    return position;

                char* temp = new char[count + 1]; strcpy(temp, "");

                strncat(temp, source + found, count - 1);
                position[found_floats] = (float)atof(temp);
                found_floats++;

                delete[] temp;

                found = t + 1;
                count = 0;
            }
        }
        return position;
    }
}
