#include <cstdio>
#include "tweeny.h"

int main() {
  // Create a tween from 0 to 100 over 100 frames
  auto tween = tweeny::from(0.0f)
                 .to(100.0f)
                 .via(tweeny::easing::linear)
                 .during(100U)
                 .build();

  // Demonstrate peek() - query without mutating
  printf("Initial value (peek): %f\n", static_cast<double>(tween.peek()));
  printf("Progress: %f%%\n", static_cast<double>(tween.progress() * 100.0f));

  // Peek at frame 50 without changing state
  printf("Value at frame 50 (peek): %f\n", static_cast<double>(tween.peek(50U)));
  printf("Still at start, progress: %f%%\n", static_cast<double>(tween.progress() * 100.0f));

  // Step forward
  tween.step(25);
  printf("\nAfter stepping 25 frames:\n");
  printf("Current value: %f\n", static_cast<double>(tween.peek()));
  printf("Progress: %f%%\n", static_cast<double>(tween.progress() * 100.0f));

  // Seek to specific frame
  tween.seek(75U);
  printf("\nAfter seeking to frame 75:\n");
  printf("Current value: %f\n", static_cast<double>(tween.peek()));
  printf("Progress: %f%%\n", static_cast<double>(tween.progress() * 100.0f));

  // Complete the tween
  tween.seek(100U);
  printf("\nAt end:\n");
  printf("Final value: %f\n", static_cast<double>(tween.peek()));
  printf("Progress: %f%%\n", static_cast<double>(tween.progress() * 100.0f));

  return 0;
}
