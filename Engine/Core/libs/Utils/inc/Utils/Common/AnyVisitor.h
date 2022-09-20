//
// Created by Monika on 28.06.2022.
//

#ifndef SRENGINE_ANYVISITOR_H
#define SRENGINE_ANYVISITOR_H

#include <Utils/stdInclude.h>

namespace SR_UTILS_NS {
    template<class...Ts>
    struct AnyVisitor;

    template<>
    struct AnyVisitor<> {
        template<class F>
        decltype(auto) operator()( std::any& a, F&& f ) const {
            return std::forward<F>(f)(a);
        }
    };

    template<class...Ts>
    struct AnyVisitor {
    private:
        struct accum {
            std::size_t x = 0;
            friend accum operator+( accum lhs, accum rhs ) {
                if (lhs.x || rhs.x) return {lhs.x+1};
                else return {};
            }
        };
    public:
        template<class Any, class F>
        void operator()(Any&& any, F&& f) const {
            // sizeof...(Ts) none in the list
            // otherwise, index of which any is in the list
            std::size_t which = sizeof...(Ts) - (accum{} + ... + accum{ any.type() == typeid(Ts) }).x;

            using table_entry = void(*)(Any&&, F&&);

            static const table_entry table[] = {
                    +[](Any&& any, F&& f) {
                        std::forward<F>(f)( std::any_cast<Ts>( std::forward<Any>(any) ) );
                    }...,
                    +[](Any&& any, F&& f) {
                        std::forward<F>(f)( std::forward<Any>(any) );
                    }
            };

            table[which]( std::forward<Any>(any), std::forward<F>(f) );
        }
    };

    template<class...Fs>
    struct Overloaded:Fs... {
        using Fs::operator()...;
    };
    template<class...Fs>
    Overloaded(Fs&&...)->Overloaded<std::decay_t<Fs>...>;
}

#endif //SRENGINE_ANYVISITOR_H
