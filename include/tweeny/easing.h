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

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file easing.h
 * The purpose of this file is to list all bundled easings. Each easing is defined
 * in its own header under include/tweeny/detail/easing/. Users may include individual
 * easing headers or this header to get all easings.
 */

#ifndef TWEENY_EASING_H
#define TWEENY_EASING_H

#include "detail/easing/back.h"
#include "detail/easing/bounce.h"
#include "detail/easing/circular.h"
#include "detail/easing/cubic.h"
#include "detail/easing/def.h"
#include "detail/easing/elastic.h"
#include "detail/easing/exponential.h"
#include "detail/easing/linear.h"
#include "detail/easing/quadratic.h"
#include "detail/easing/quartic.h"
#include "detail/easing/quintic.h"
#include "detail/easing/sinusoidal.h"
#include "detail/easing/stepped.h"

/**
 * @namespace tweeny::easing
 * @brief Contains all built-in easing functions for controlling animation curves.
 *
 * Provides 30+ easing functions in In, Out, and InOut variants for creating natural-looking
 * animations. See the @ref easings page for detailed descriptions and usage examples.
 */
namespace tweeny::easing {
 /**
  * @brief Easing function that creates anticipation by pulling back before moving forward.
  *
  * The `backIn` easing function begins by moving backwards slightly (overshooting in the
  * negative direction), then reverses and accelerates toward the target value. This creates
  * an anticipation effect similar to pulling back a slingshot or winding up before a throw.
  *
  * The backward motion at the start makes this easing particularly effective for animations
  * that benefit from telegraphing or anticipation, such as:
  * - UI elements that "wind up" before sliding in
  * - Character movements that show preparation before action
  * - Camera movements that pull back before zooming forward
  *
  * Mathematically, this easing uses the formula: `c * t * t * ((s + 1) * t - s) + b`
  * where `s` controls the overshoot amount (typically 1.70158).
  *
  * @note The animation will briefly have values less than the start value before proceeding
  * to the target. Ensure your animation system can handle values outside the expected range.
  *
  * @code
  * // Create a tween with back-in easing for anticipation effect
  * auto tween = tweeny::from(0.0f)
  *   .to(100.0f)
  *   .via(easing::backIn)
  *   .during(60U)
  *   .build();
  *
  * // The animation will dip below 0.0f briefly before accelerating to 100.0f
  * @endcode
  *
  * @see backOut For overshoot at the end instead of the beginning
  * @see backInOut For anticipation at the start and overshoot at the end
  */
 inline constexpr detail::backInEasing backIn{};

 /**
  * @brief Easing function that overshoots the target before settling back.
  *
  * The `backOut` easing function accelerates toward and past the target value, then pulls
  * back to settle at the final position. This creates an overshoot or "spring-back" effect
  * that adds liveliness and energy to animations.
  *
  * This easing is particularly effective for:
  * - UI elements that pop into place with energy (buttons, dialogs, notifications)
  * - Object arrivals that should feel bouncy and dynamic
  * - Emphasizing the end state of an animation
  * - Adding personality to mechanical movements
  *
  * The overshoot creates a more natural, less rigid feel compared to standard easing
  * functions. It's widely used in iOS, Android, and Material Design animation patterns
  * to make interactions feel more responsive and playful.
  *
  * Mathematically, this is the inverse of backIn, applied at the end of the transition.
  *
  * @note The animation will briefly exceed the target value before settling. Ensure your
  * rendering or logic can handle values beyond the specified range.
  *
  * @code
  * // Animate a button with overshoot for a lively effect
  * auto scale = tweeny::from(0.0f)
  *   .to(1.0f)
  *   .via(easing::backOut)
  *   .during(30U)
  *   .build();
  *
  * // Scale will exceed 1.0f (e.g., 1.1f) before settling back to 1.0f
  * @endcode
  *
  * @see backIn For anticipation at the start instead of overshoot at the end
  * @see backInOut For both anticipation and overshoot
  * @see elasticOut For a more pronounced oscillating overshoot effect
  */
 inline constexpr detail::backOutEasing backOut{};

 /**
  * @brief Easing function combining anticipation at the start and overshoot at the end.
  *
  * The `backInOut` easing function creates a dramatic motion curve by pulling back before
  * the start (anticipation), accelerating through the middle, then overshooting past the
  * target before settling (spring-back). This combines the effects of both backIn and
  * backOut for maximum expressiveness.
  *
  * This easing creates highly dynamic animations suitable for:
  * - Attention-grabbing transitions that need maximum visual interest
  * - Character animations requiring wind-up and follow-through
  * - Scene transitions with dramatic flair
  * - Emphasizing both the start and end states of an animation
  *
  * The dual overshoot (negative at start, positive at end) makes this one of the most
  * expressive easings, but it should be used judiciously as it can feel exaggerated if
  * overused. It works best for focal animations rather than ambient motion.
  *
  * @note The animation will have values outside the start-to-target range at both ends.
  * During the first half, values will dip below the start; during the second half, values
  * will exceed the target before settling.
  *
  * @code
  * // Create a dramatic page transition
  * auto position = tweeny::from(-100.0f)
  *   .to(100.0f)
  *   .via(easing::backInOut)
  *   .during(90U)
  *   .build();
  *
  * // Position will go below -100.0f at start and above 100.0f near end
  * @endcode
  *
  * @see backIn For only anticipation without overshoot
  * @see backOut For only overshoot without anticipation
  * @see elasticInOut For a more extreme oscillating version
  */
 inline constexpr detail::backInOutEasing backInOut{};
 inline constexpr detail::bounceInEasing bounceIn{};
 inline constexpr detail::bounceOutEasing bounceOut{};
 inline constexpr detail::bounceInOutEasing bounceInOut{};
 inline constexpr detail::circularInEasing circularIn{};
 inline constexpr detail::circularOutEasing circularOut{};
 inline constexpr detail::circularInOutEasing circularInOut{};
 inline constexpr detail::cubicInEasing cubicIn{};
 inline constexpr detail::cubicOutEasing cubicOut{};
 inline constexpr detail::cubicInOutEasing cubicInOut{};
 inline constexpr detail::defaultEasing def{};
 inline constexpr detail::elasticInEasing elasticIn{};
 inline constexpr detail::elasticOutEasing elasticOut{};
 inline constexpr detail::elasticInOutEasing elasticInOut{};
 inline constexpr detail::exponentialInEasing exponentialIn{};
 inline constexpr detail::exponentialOutEasing exponentialOut{};
 inline constexpr detail::exponentialInOutEasing exponentialInOut{};
 inline constexpr detail::linearEasing linear{};
 inline constexpr detail::quadraticInEasing quadraticIn{};
 inline constexpr detail::quadraticOutEasing quadraticOut{};
 inline constexpr detail::quadraticInOutEasing quadraticInOut{};
 inline constexpr detail::quarticInEasing quarticIn{};
 inline constexpr detail::quarticOutEasing quarticOut{};
 inline constexpr detail::quarticInOutEasing quarticInOut{};
 inline constexpr detail::quinticInEasing quinticIn{};
 inline constexpr detail::quinticOutEasing quinticOut{};
 inline constexpr detail::quinticInOutEasing quinticInOut{};
 inline constexpr detail::sinusoidalInEasing sinusoidalIn{};
 inline constexpr detail::sinusoidalOutEasing sinusoidalOut{};
 inline constexpr detail::sinusoidalInOutEasing sinusoidalInOut{};
 inline constexpr detail::steppedEasing stepped{};
}

#endif //TWEENY_EASING_H
