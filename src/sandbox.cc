#include <cstdio>

#include "event.h"
#include "tweeny.h"

int main() {
  const auto builder = tweeny
                       ::from(0.0f)
                       .to(35.0f)
                       .via(tweeny::easing::linear)
                       .during(100U);
  auto x = builder.build();

  const auto v = x.step(1);

  printf("%f\n", static_cast<double>(v));

  return 0;
}
