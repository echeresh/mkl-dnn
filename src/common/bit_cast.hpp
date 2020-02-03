/*******************************************************************************
* Copyright 2020 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#ifndef BIT_CAST_HPP
#define BIT_CAST_HPP

#include <cstring>
#include <type_traits>

namespace dnnl {
namespace impl {
namespace utils {

template <typename T, typename U>
inline T bit_cast(const U &u) {
    static_assert(sizeof(T) == sizeof(U), "Bit-casting must preserve size.");
    static_assert(std::is_trivially_copyable<T>::value,
            "T must be trivially copyable.");
    static_assert(std::is_trivially_copyable<U>::value,
            "U must be trivially copyable.");

    T t;
    std::memcpy(&t, &u, sizeof(U));
    return t;
}

} // namespace utils
} // namespace impl
} // namespace dnnl

#endif
