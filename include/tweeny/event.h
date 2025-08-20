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

#ifndef TWEENY_EVENT_H
#define TWEENY_EVENT_H

namespace tweeny::event {
  struct sectionIn {
    size_t key_frame;
    explicit sectionIn(const size_t key_frame_input) : key_frame(key_frame_input) {}
  };

  struct sectionOut {
    size_t key_frame;
    explicit sectionOut(const size_t key_frame_input) : key_frame(key_frame_input) {}
  };

  inline struct step_t {} step;
  inline struct seek_t {} seek;
  inline struct jump_t {} jump;
  inline struct update_t {} update;
  inline struct complete_t {} complete;

  enum class response {
    ok = 0,
    unsubscribe = 1,
  };
}

#endif //TWEENY_EVENT_H
