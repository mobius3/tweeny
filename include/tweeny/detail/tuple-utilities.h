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

#ifndef TWEENY_TUPLE_UTILITIES_H
#define TWEENY_TUPLE_UTILITIES_H
#include <cstddef>
#include <tuple>

namespace tweeny::detail {

  /**
   * Implements the creation of a tuple with repeated elements of the given value.
   *
   * @param v The value to be repeated in the tuple.
   * @param sequence An index sequence used to generate the tuple with the required size.
   * @return A tuple where each element is a copy of the input value.
   *
   * @warning This function is private and shouldn't be used directly
   */
  template <typename T, std::size_t... I>
  static auto make_repeated_tuple_impl(const T & v, std::index_sequence<I...> sequence) {
    (void) sequence;
    return std::make_tuple(((void) I, v)...);
  }

  /**
   * Creates a tuple of size N where each element is a copy of the given value.
   *
   * @param v The value to be repeated in the tuple.
   * @return A tuple of size N with each element being a copy of the input value.
   *
   * @warning This function is private and shouldn't be used directly
   */
  template <typename T, std::size_t N>
  static auto make_repeated_tuple(const T & v) {
    return make_repeated_tuple_impl(v, std::make_index_sequence<N>{});
  }
}

#endif //TWEENY_TUPLE_UTILITIES_H
