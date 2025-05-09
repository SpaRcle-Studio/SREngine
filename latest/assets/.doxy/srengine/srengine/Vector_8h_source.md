

# File Vector.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Types**](dir_e2eff6081ed67c5bc03a553ef17d8efc.md) **>** [**Vector.h**](Vector_8h.md)

[Go to the documentation of this file](Vector_8h.md)


```C++
//
// Created by Monika on 10.10.2024.
//

#ifndef SR_COMMON_VECTOR_H
#define SR_COMMON_VECTOR_H

#include <Utils/stdInclude.h>

/*
namespace SR_UTILS_NS {
    template<typename T, class Alloc = std::allocator<T>> class SR_COMMON_DLL_API Vector {
        using AllocType = RebindAllocT<Alloc, T>;
        using AllocTypeTraits = std::allocator_traits<AllocType>;
    public:
        SR_CONSTEXPR Vector() noexcept(std::is_nothrow_default_constructible_v<AllocType>) {
        }

    _CONSTEXPR20 explicit vector(const _Alloc& _Al) noexcept : _Mypair(_One_then_variadic_args_t{}, _Al) {
        _Mypair._Myval2._Alloc_proxy(_GET_PROXY_ALLOCATOR(_Alty, _Getal()));
    }

    _CONSTEXPR20 explicit vector(_CRT_GUARDOVERFLOW const size_type _Count, const _Alloc& _Al = _Alloc())
        : _Mypair(_One_then_variadic_args_t{}, _Al) {
        _Construct_n(_Count);
    }

    _CONSTEXPR20 vector(_CRT_GUARDOVERFLOW const size_type _Count, const _Ty& _Val, const _Alloc& _Al = _Alloc())
        : _Mypair(_One_then_variadic_args_t{}, _Al) {
        _Construct_n(_Count, _Val);
    }

    template <class _Iter, enable_if_t<_Is_iterator_v<_Iter>, int> = 0>
    _CONSTEXPR20 vector(_Iter _First, _Iter _Last, const _Alloc& _Al = _Alloc())
        : _Mypair(_One_then_variadic_args_t{}, _Al) {
        _Adl_verify_range(_First, _Last);
        auto _UFirst = _Get_unwrapped(_First);
        auto _ULast  = _Get_unwrapped(_Last);
        if constexpr (_Is_cpp17_fwd_iter_v<_Iter>) {
            const auto _Length = static_cast<size_t>(_STD distance(_UFirst, _ULast));
            const auto _Count  = _Convert_size<size_type>(_Length);
            _Construct_n(_Count, _STD move(_UFirst), _STD move(_ULast));
#ifdef __cpp_lib_concepts
        } else if constexpr (forward_iterator<_Iter>) {
            const auto _Length = _To_unsigned_like(_RANGES distance(_UFirst, _ULast));
            const auto _Count  = _Convert_size<size_type>(_Length);
            _Construct_n(_Count, _STD move(_UFirst), _STD move(_ULast));
#endif // __cpp_lib_concepts
        } else {
            auto&& _Alproxy = _GET_PROXY_ALLOCATOR(_Alty, _Getal());
            _Container_proxy_ptr<_Alty> _Proxy(_Alproxy, _Mypair._Myval2);
            _Tidy_guard<vector> _Guard{this};

            _Append_uncounted_range(_STD move(_UFirst), _STD move(_ULast));

            _Guard._Target = nullptr;
            _Proxy._Release();
        }
    }

    _CONSTEXPR20 vector(initializer_list<_Ty> _Ilist, const _Alloc& _Al = _Alloc())
        : _Mypair(_One_then_variadic_args_t{}, _Al) {
        _Construct_n(_Convert_size<size_type>(_Ilist.size()), _Ilist.begin(), _Ilist.end());
    }

#if _HAS_CXX23 && defined(__cpp_lib_concepts) // TRANSITION, GH-395
    template <_Container_compatible_range<_Ty> _Rng>
    constexpr vector(from_range_t, _Rng&& _Range, const _Alloc& _Al = _Alloc())
        : _Mypair(_One_then_variadic_args_t{}, _Al) {
        if constexpr (_RANGES sized_range<_Rng> || _RANGES forward_range<_Rng>) {
            const auto _Length = _To_unsigned_like(_RANGES distance(_Range));
            const auto _Count  = _Convert_size<size_type>(_Length);
            _Construct_n(_Count, _RANGES _Ubegin(_Range), _RANGES _Uend(_Range));
        } else {
            auto&& _Alproxy = _GET_PROXY_ALLOCATOR(_Alty, _Getal());
            _Container_proxy_ptr<_Alty> _Proxy(_Alproxy, _Mypair._Myval2);
            _Tidy_guard<vector> _Guard{this};

            _Append_uncounted_range(_RANGES _Ubegin(_Range), _RANGES _Uend(_Range));

            _Guard._Target = nullptr;
            _Proxy._Release();
        }
    }
#endif // _HAS_CXX23 && defined(__cpp_lib_concepts)

    _CONSTEXPR20 vector(const vector& _Right)
        : _Mypair(_One_then_variadic_args_t{}, _Alty_traits::select_on_container_copy_construction(_Right._Getal())) {
        const auto& _Right_data = _Right._Mypair._Myval2;
        const auto _Count       = static_cast<size_type>(_Right_data._Mylast - _Right_data._Myfirst);
        _Construct_n(_Count, _Right_data._Myfirst, _Right_data._Mylast);
    }

    _CONSTEXPR20 vector(const vector& _Right, const _Identity_t<_Alloc>& _Al)
        : _Mypair(_One_then_variadic_args_t{}, _Al) {
        const auto& _Right_data = _Right._Mypair._Myval2;
        const auto _Count       = static_cast<size_type>(_Right_data._Mylast - _Right_data._Myfirst);
        _Construct_n(_Count, _Right_data._Myfirst, _Right_data._Mylast);
    }

    _CONSTEXPR20 vector(vector&& _Right) noexcept
        : _Mypair(_One_then_variadic_args_t{}, _STD move(_Right._Getal()),
            _STD exchange(_Right._Mypair._Myval2._Myfirst, nullptr),
            _STD exchange(_Right._Mypair._Myval2._Mylast, nullptr),
            _STD exchange(_Right._Mypair._Myval2._Myend, nullptr)) {
        _Mypair._Myval2._Alloc_proxy(_GET_PROXY_ALLOCATOR(_Alty, _Getal()));
        _Mypair._Myval2._Swap_proxy_and_iterators(_Right._Mypair._Myval2);
    }

    _CONSTEXPR20 vector(vector&& _Right, const _Identity_t<_Alloc>& _Al_) noexcept(
        _Alty_traits::is_always_equal::value) // strengthened
        : _Mypair(_One_then_variadic_args_t{}, _Al_) {
        _Alty& _Al        = _Getal();
        auto&& _Alproxy   = _GET_PROXY_ALLOCATOR(_Alty, _Al);
        auto& _My_data    = _Mypair._Myval2;
        auto& _Right_data = _Right._Mypair._Myval2;
        _Container_proxy_ptr<_Alty> _Proxy(_Alproxy, _My_data);

        if constexpr (!_Alty_traits::is_always_equal::value) {
            if (_Al != _Right._Getal()) {
                const auto _Count = static_cast<size_type>(_Right_data._Mylast - _Right_data._Myfirst);
                if (_Count != 0) {
                    _Buy_raw(_Count);
                    _Tidy_guard<vector> _Guard{this};
                    _My_data._Mylast =
                        _Uninitialized_move(_Right_data._Myfirst, _Right_data._Mylast, _My_data._Myfirst, _Al);

                    _ASAN_VECTOR_CREATE;
                    _Guard._Target = nullptr;
                }
                _Proxy._Release();
                return;
            }
        }

        _My_data._Take_contents(_Right_data);
        _Proxy._Release();
    }

    _CONSTEXPR20 vector& operator=(vector&& _Right) noexcept(
        _Choose_pocma_v<_Alty> != _Pocma_values::_No_propagate_allocators) {
        if (this == _STD addressof(_Right)) {
            return *this;
        }

        _Alty& _Al                = _Getal();
        _Alty& _Right_al          = _Right._Getal();
        constexpr auto _Pocma_val = _Choose_pocma_v<_Alty>;
        if constexpr (_Pocma_val == _Pocma_values::_No_propagate_allocators) {
            if (_Al != _Right_al) {
                _Move_assign_unequal_alloc(_Right);
                return *this;
            }
        }

        _Tidy();
#if _ITERATOR_DEBUG_LEVEL != 0
        if constexpr (_Pocma_val == _Pocma_values::_Propagate_allocators) {
            if (_Al != _Right_al) {
                // intentionally slams into noexcept on OOM, TRANSITION, VSO-466800
                _Mypair._Myval2._Reload_proxy(_GET_PROXY_ALLOCATOR(_Alty, _Al), _GET_PROXY_ALLOCATOR(_Alty, _Right_al));
            }
        }
#endif // _ITERATOR_DEBUG_LEVEL != 0

        _Pocma(_Al, _Right_al);
        _Mypair._Myval2._Take_contents(_Right._Mypair._Myval2);
        return *this;
    }

    _CONSTEXPR20 ~vector() noexcept {
        _Tidy();
#if _ITERATOR_DEBUG_LEVEL != 0
        auto&& _Alproxy = _GET_PROXY_ALLOCATOR(_Alty, _Getal());
        _Delete_plain_internal(_Alproxy, _STD exchange(_Mypair._Myval2._Myproxy, nullptr));
#endif // _ITERATOR_DEBUG_LEVEL != 0
    }
    public:
        SR_NODISCARD uint64_t size() const noexcept { return m_size; }
        SR_NODISCARD uint64_t capacity() const noexcept { return m_capacity; }

    public:
        SR_CONSTEXPR void push_back(const T& value) {
            EmplaceOneAtBack(value);
        }

        template <class... ValueType> SR_CONSTEXPR decltype(auto) emplace_back(ValueType&&... value) {
            return EmplaceOneAtBack(_STD forward<ValueType>(value)...);
        }

        T* find(const T& value) {
            for (uint64_t i = 0; i < m_size; ++i) {
                if (m_data[i] == value) {
                    return m_data + i;
                }
            }
            return nullptr;
        }

        SR_NODISCARD bool empty() const noexcept { return m_size == 0; }

        T* begin() noexcept { return m_data; }
        T* end() noexcept { return m_data + m_size; }
        const T* begin() const noexcept { return m_data; }
        const T* end() const noexcept { return m_data + m_size; }

        T& operator[](uint64_t index) noexcept { return m_data[index]; }
        const T& operator[](uint64_t index) const noexcept { return m_data[index]; }

        T* data() noexcept { return m_data; }

        T& back() noexcept { return m_data[m_size - 1]; }

        T* erase(T* pElement) {
            if (pElement < m_data || pElement >= m_data + m_size) {
                return nullptr;
            }

            DestroyInPlace(pElement);
            std::memmove(pElement, pElement + 1, (m_size - 1) * sizeof(T));
            --m_size;
            return pElement;
        }

        void pop_back() {
            if (m_size > 0) {
                DestroyInPlace(m_data + m_size - 1);
                --m_size;
            }
        }

        SR_NODISCARD static uint64_t max_size() noexcept { return std::numeric_limits<uint64_t>::max(); }

        void clear() {
            DestroyRange(m_data, m_data + m_size);
            m_size = 0;
        }

        void reserve(uint64_t newCapacity) {
            if (newCapacity > capacity()) {
                if (newCapacity > max_size()) {
                    throw std::length_error("Vector<T> too long!");
                }

                ReallocateExactly(newCapacity);
            }
        }

    private:
        SR_CONSTEXPR void ReallocateExactly(uint64_t newCapacity) {
            const T* pNewData = m_allocator.allocate(newCapacity);

            if constexpr (std::is_nothrow_move_constructible_v<T> || !std::is_copy_constructible_v<T>) {
                UninitializedMove(_Myfirst, _Mylast, _Newvec, m_allocator);
            }
            else {
                UninitializedCopy(_Myfirst, _Mylast, _Newvec, m_allocator);
            }

            ChangeArray(pNewData, m_size, newCapacity);
        }

        SR_CONSTEXPR void ChangeArray(const T* pNewData, const uint64_t newSize, const uint64_t newCapacity) {
            if (m_data) { // destroy and deallocate old array
                DestroyRange(m_data, m_data + m_size);
                m_allocator.deallocate(m_data, static_cast<uint64_t>(m_capacity));
            }

            m_data = pNewData;
            m_size = newSize;
            m_capacity = newCapacity;
        }

        SR_CONSTEXPR void DestroyRange(T* pFirst, const T* pLast) noexcept {
            using Type = typename Alloc::value_type;
            if constexpr (!std::conjunction_v<std::is_trivially_destructible<Type>, std::_Uses_default_destroy<Alloc, Type*>>) {
                for (; pFirst != pLast; ++pFirst) {
                    std::allocator_traits<Alloc>::destroy(m_allocator, std::_Unfancy(pFirst));
                }
            }
        }

        template <class... ValueType> SR_CONSTEXPR T& EmplaceOneAtBack(ValueType&&... value) {
            if (m_size < m_capacity) {
                return EmplaceBackWithUnusedCapacity(std::forward<ValueType>(value)...);
            }

            return *EmplaceReallocate(std::forward<ValueType>(value)...);
        }

        template <class... ValueType> SR_CONSTEXPR T& EmplaceBackWithUnusedCapacity(ValueType&&... value) {
            if constexpr (std::conjunction_v<std::is_nothrow_constructible<T, ValueType...>, std::_Uses_default_construct<Alloc, T*, ValueType...>>) {
                _Construct_in_place(*_Mylast, _STD forward<ValueType>(value)...);
            } else {
                _ASAN_VECTOR_EXTEND_GUARD(static_cast<size_type>(_Mylast - _My_data._Myfirst) + 1);
                _Alty_traits::construct(_Getal(), _Unfancy(_Mylast), _STD forward<_Valty>(_Val)...);
                _ASAN_VECTOR_RELEASE_GUARD;
            }

            _Orphan_range(_Mylast, _Mylast);
            _Ty& _Result = *_Mylast;
            ++_Mylast;

            return _Result;
        }

        template <class... _Valty> _CONSTEXPR20 pointer EmplaceReallocate(const pointer _Whereptr, _Valty&&... _Val) {
            // reallocate and insert by perfectly forwarding _Val at _Whereptr
            _Alty& _Al        = _Getal();
            auto& _My_data    = _Mypair._Myval2;
            pointer& _Myfirst = _My_data._Myfirst;
            pointer& _Mylast  = _My_data._Mylast;

            _STL_INTERNAL_CHECK(_Mylast == _My_data._Myend); // check that we have no unused capacity

            const auto _Whereoff = static_cast<size_type>(_Whereptr - _Myfirst);
            const auto _Oldsize  = static_cast<size_type>(_Mylast - _Myfirst);

            if (_Oldsize == max_size()) {
                _Xlength();
            }

            const size_type _Newsize     = _Oldsize + 1;
            const size_type _Newcapacity = _Calculate_growth(_Newsize);

            const pointer _Newvec           = _Al.allocate(_Newcapacity);
            const pointer _Constructed_last = _Newvec + _Whereoff + 1;
            pointer _Constructed_first      = _Constructed_last;

            _TRY_BEGIN
            _Alty_traits::construct(_Al, _Unfancy(_Newvec + _Whereoff), _STD forward<_Valty>(_Val)...);
            _Constructed_first = _Newvec + _Whereoff;

            if (_Whereptr == _Mylast) { // at back, provide strong guarantee
                if constexpr (is_nothrow_move_constructible_v<_Ty> || !is_copy_constructible_v<_Ty>) {
                    _Uninitialized_move(_Myfirst, _Mylast, _Newvec, _Al);
                } else {
                    _Uninitialized_copy(_Myfirst, _Mylast, _Newvec, _Al);
                }
            } else { // provide basic guarantee
                _Uninitialized_move(_Myfirst, _Whereptr, _Newvec, _Al);
                _Constructed_first = _Newvec;
                _Uninitialized_move(_Whereptr, _Mylast, _Newvec + _Whereoff + 1, _Al);
            }
            _CATCH_ALL
            _Destroy_range(_Constructed_first, _Constructed_last, _Al);
            _Al.deallocate(_Newvec, _Newcapacity);
            _RERAISE;
            _CATCH_END

            _Change_array(_Newvec, _Newsize, _Newcapacity);
            return _Newvec + _Whereoff;
        }


    private:
        Alloc m_allocator;
        uint64_t m_capacity = 0;
        uint64_t m_size = 0;
        T* m_data = nullptr;

    };
}
*/
#endif //SR_COMMON_VECTOR_H
```


