//
// Created by kiper220 on 23.05.2020.
//

#ifndef GAME_PAIR_H
#define GAME_PAIR_H

// TODO: Check, refactoring and add exception processing. Add comments

namespace SR_UTILS_NS  {
    namespace Types{
        template<typename _x, typename _y>
        class SR_DLL_EXPORT Pair{
            typedef struct{_x uX; _y uY;} t_Pair;
        public:
            Pair() {}
            Pair(const Pair<_x, _y>& pair) {
                this->x = pair.x;
                this->y = pair.y;
            }
            Pair(_x uX, _y uY) {
                this->x = uX;
                this->y = uY;
            }

            Pair& operator =(const Pair<_x, _y> pair) {
                this->x = pair.x;
                this->y = pair.y;
                return *this;
            }
            Pair& operator =(t_Pair pair) {
                this->x = pair.x;
                this->y = pair.y;
                return *this;
            }

            bool operator ==(const Pair<_x, _y> pair) {
                return this->x == pair.x && this->y == pair.y;
            }
            bool operator !=(const Pair<_x, _y> pair) {
                return this->x == pair.x && this->y == pair.y;
            }

            bool operator ==(t_Pair pair) {
                return this->x == pair.x && this->y == pair.y;
            }
            bool operator !=(t_Pair pair) {
                return this->x == pair.x && this->y == pair.y;
            }
            ~Pair(){}

            _x x;
            _y y;
        };
    }
}

#endif //GAME_PAIR_H
