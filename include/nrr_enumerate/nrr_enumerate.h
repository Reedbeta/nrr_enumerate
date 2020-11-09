// nrr_enumerate: iterate indices and items at the same time
// See http://www.reedbeta.com/blog/python-like-enumerate-in-cpp17/

// Copyright 2020 Nathan Reed
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once
#include <tuple>

// Hide requires clauses from pre-C++20 compilers and MSVC Intellisense
#if (__cplusplus >= 201709L) || (defined(_MSVC_LANG) && (_MSVC_LANG >= 201705L))
#   define NRR_REQUIRES(...)   requires(__VA_ARGS__)
#else
#   define NRR_REQUIRES(...)
#endif

namespace nrr
{
    template <typename T>
    NRR_REQUIRES(requires { std::begin(std::declval<T>()); std::end(std::declval<T>()); })
    constexpr auto enumerate(T&& iterable)
    {
        struct iterator
        {
            size_t i;
            decltype(std::begin(iterable)) iter;
            bool operator != (const iterator & other) const { return iter != other.iter; }
            void operator ++ () { ++i; ++iter; }
            auto operator * () const { return std::tie(i, *iter); }
        };
        struct iterable_wrapper
        {
            T iterable;
            auto begin() { return iterator{ 0, std::begin(iterable) }; }
            auto end() { return iterator{ 0, std::end(iterable) }; }
        };
        return iterable_wrapper{ std::forward<T>(iterable) };
    }

    template <typename T>
    NRR_REQUIRES(requires { std::cbegin(std::declval<T>()); std::cend(std::declval<T>()); })
    constexpr auto cenumerate(T&& iterable)
    {
        struct iterator
        {
            size_t i;
            decltype(std::cbegin(iterable)) iter;
            bool operator != (const iterator & other) const { return iter != other.iter; }
            void operator ++ () { ++i; ++iter; }
            auto operator * () const { return std::tie(i, *iter); }
        };
        struct iterable_wrapper
        {
            T iterable;
            auto begin() { return iterator{ 0, std::cbegin(iterable) }; }
            auto end() { return iterator{ 0, std::cend(iterable) }; }
        };
        return iterable_wrapper{ std::forward<T>(iterable) };
    }
} // namespace nrr

#undef NRR_REQUIRES
