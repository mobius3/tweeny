/*
This file is part of the Tweeny library.

Copyright (c) 2016-2025 Leonardo Guilherme Lucena de Freitas
Copyright (c) 2016 Guilherme R. Costa

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:
#
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef TWEENY_VALUE_CONTAINER_H
#define TWEENY_VALUE_CONTAINER_H

#include <array>
#include <type_traits>

namespace tweeny::detail {
  /**
   * @struct all_same
   * @brief A type trait that evaluates to `std::true_type`.
   *
   * This specialization of the `all_same` struct is used when no template parameters
   * are provided. It serves as a base case for type pack evaluation and always evaluates
   * to `true_type`, representing that an empty pack is trivially considered to have
   * "all the same" types.
   *
   * This type trait is mainly used as a base case in conjunction with other
   * template specializations that check for type consistency within a parameter pack.
   *
   * @warning This structure is private and shouldn't be used directly
   */
  template<typename...>
  struct all_same : std::true_type {};


  /**
   * @struct all_same
   * @brief A type trait to check if all types in a parameter pack are the same.
   *
   * This struct inherits from `std::conjunction` with the result of comparing all
   * types in the parameter pack `Rest...` using `std::is_same`, relative to the first
   * type `First`. The resulting value will evaluate to `true_type` if all types are the
   * same, otherwise to `false_type`.
   *
   * @tparam First The first type in the parameter pack to compare against.
   * @tparam Rest The remaining types in the parameter pack.
   *
   * @warning This structure is private and shouldn't be used directly
   */
  template<typename First, typename... Rest>
  struct all_same<First, Rest...> : std::conjunction<std::is_same<First, Rest>...> {};

  /**
   * @brief A compile-time boolean that is true if all types in the provided parameter pack are the same, false otherwise.
   *
   * Determines whether all types in the template parameter pack `Ts...` are the same type. This is evaluated at
   * compile-time using the `all_same` trait.
   *
   * Example usage:
   * @code
   * static_assert(all_same_v<int, int, int> == true);
   * static_assert(all_same_v<int, double, int> == false);
   * @endcode
   *
   * @tparam Ts pack of types to be evaluated
   *
   * @warning This value is private and shouldn't be used directly
   */
  template<typename... Ts>
  inline constexpr bool all_same_v = all_same<Ts...>::value;

  template<typename... Ts>
  using value_container_t =
      std::conditional_t<
        all_same_v<Ts...>,
        std::array<std::tuple_element_t<0, std::tuple<Ts...>>, sizeof...(Ts)>,
        std::tuple<Ts...>
    >;
}

#endif //TWEENY_VALUE_CONTAINER_H
