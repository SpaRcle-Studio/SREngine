

# File Function.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Types**](dir_5acfcf7a6efc565cfce10e624e0935ad.md) **>** [**Function.h**](Function_8h.md)

[Go to the documentation of this file](Function_8h.md)


```C++
//
// Created by Monika on 21.07.2022.
//

#ifndef SR_ENGINE_FUNCTION_H
#define SR_ENGINE_FUNCTION_H

#include <Utils/stdInclude.h>

namespace SR_HTYPES_NS {
    template <typename UnusedType> class Function;

    template <typename ReturnType, typename... ArgumentTypes>
    class Function <ReturnType (ArgumentTypes...)>
    {
        class function_holder_base;
        using invoker_t = std::unique_ptr<function_holder_base>;
    public:
        typedef ReturnType signature_type(ArgumentTypes...);

        Function()
            : mInvoker()
        { }

        template <typename FunctionT> Function(FunctionT f) 
            : mInvoker(new free_function_holder<FunctionT>(f))
        { }

        Function(Function&& function) noexcept
            : mInvoker(std::move(function.mInvoker))
        { }

        Function& operator=(Function&& function) noexcept {
            mInvoker = std::move(function.mInvoker);
            return *this;
        }

        template <typename FunctionType, typename ClassType> Function(FunctionType ClassType::* f) 
            : mInvoker(new member_function_holder<FunctionType, ArgumentTypes ...>(f))
        { }

        Function(const Function& other)
            : mInvoker(other.mInvoker->clone())
        { }

        Function& operator=(const Function& other) {
            mInvoker = (bool)other.mInvoker.get() ? other.mInvoker->clone() : invoker_t();
            return *this;
        }

        ReturnType operator()(ArgumentTypes... args) const noexcept {
            return mInvoker->invoke(args...);
        }

        operator bool() const { 
            return mInvoker.get();
        }

    private:
        class function_holder_base
        {
        public:
            function_holder_base() = default;
            virtual ~function_holder_base() = default;

            virtual ReturnType invoke(ArgumentTypes... args) = 0;
            virtual invoker_t clone() = 0;

        private:
            function_holder_base(const function_holder_base&); 
            void operator=(const function_holder_base&); 

        };

        template <typename FunctionT>
        class free_function_holder : public function_holder_base
        {
        public:
            free_function_holder(FunctionT func) 
                : function_holder_base()
                , mFunction(func)
            { }

            virtual ReturnType invoke(ArgumentTypes... args) {
                return mFunction(args...);
            }

            virtual invoker_t clone() {
                return invoker_t(new free_function_holder(mFunction));
            }

        private:
            FunctionT mFunction;

        };

        template <typename FunctionType, typename ClassType, typename ... RestArgumentTypes>
        class member_function_holder : public function_holder_base
        {
        public:
            typedef FunctionType ClassType::* member_function_signature_t;

            member_function_holder(member_function_signature_t f) 
                : mFunction(f)
            { }

            virtual ReturnType invoke(ClassType obj, RestArgumentTypes... restArgs) {
                return (obj.*mFunction)(restArgs...);
            }

            virtual invoker_t clone() {
                return invoker_t(new member_function_holder(mFunction));
            }

        private:
            member_function_signature_t mFunction;

        };

        invoker_t mInvoker;
    };
}

#endif //SR_ENGINE_FUNCTION_H
```


