#include "tweeny.h"

int main() {
  auto builder = tweeny::from(0.0f).to(1.0f).via(tweeny::easing::linear).during(100U);
  auto x = builder.build();

  auto v = x.step(50);

  return 0;
}
