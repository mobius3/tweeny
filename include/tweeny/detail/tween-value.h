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

#ifndef TWEENY_TWEEN_VALUE_H
#define TWEENY_TWEEN_VALUE_H

#include <type_traits>
#include "value-container.h"

namespace tweeny::detail {

  /**
   * @struct tween_value
   * @brief Metafunction that resolves to a type based on the provided template arguments.
   *
   * This struct determines the appropriate type depending on the number and types
   * of its template parameters. If there is only one parameter (First), it resolves
   * to that type. Otherwise, it resolves to a `value_container_t` type, which is
   * constructed using the provided `First` and additional `Rest` types.
   *
   * @tparam First The first type parameter used for evaluation.
   * @tparam Rest Additional type parameters provided for consideration. These are
   *         used to construct a `value_container_t` if more than one parameter is passed.
   *
   * @see value_container_t
   * @see tween_value_t
   *
   * @warning This structure is private and shouldn't be used directly
   */
  template <typename First, typename... Rest>
  struct tween_value {
    using type = std::conditional_t<
      sizeof...(Rest) == 0,
      First,
      value_container_t<First, Rest...>
    >;
  };

  template <typename First, typename... Rest>
  using tween_value_t = typename tween_value<First, Rest...>::type;

}

#endif // TWEENY_TWEEN_VALUE_H
