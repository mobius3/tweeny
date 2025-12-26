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

 /**
  * @brief Bounce easing simulating a ball bouncing with increasing height at the start.
  *
  * The `bounceIn` easing function creates a bouncing effect before the animation begins,
  * like a ball dropped from above that bounces progressively higher before launching into
  * the main motion. This is the reverse of bounceOut's natural physics.
  *
  * Characteristics:
  * - Multiple discrete "bounces" at the start
  * - Each bounce is higher than the previous
  * - Creates anticipation through impact-based motion
  * - Less commonly used than bounceOut
  *
  * This easing works well for:
  * - **Landing preparation**: Elements about to drop into place
  * - **Impact anticipation**: Building up to a collision
  * - **Reverse playback effects**: Bounced animations played backward
  * - **Stylized entrances**: Cartoon-style wind-up effects
  *
  * BounceIn is less intuitive than bounceOut because it reverses natural physics (balls
  * don't normally bounce higher each time). Consider backIn for more natural anticipation.
  *
  * @code
  * // Element that bounces before sliding in
  * auto position = tweeny::from(0.0f)
  *   .to(200.0f)
  *   .via(easing::bounceIn)
  *   .during(50U)
  *   .build();
  * @endcode
  *
  * @see bounceOut For natural ball-drop bouncing at the end
  * @see bounceInOut For bouncing at both start and end
  * @see backIn For simpler anticipation without discrete impacts
  */
 inline constexpr detail::bounceInEasing bounceIn{};

 /**
  * @brief Bounce easing simulating a ball dropping and bouncing to rest.
  *
  * The `bounceOut` easing function creates the classic ball-drop effect where an object
  * bounces several times with decreasing height before coming to rest. This mimics real-world
  * physics of an inelastic collision and is one of the most recognizable easing patterns.
  *
  * Characteristics:
  * - Multiple discrete bounces with decreasing amplitude
  * - Simulates impact and energy loss
  * - Creates playful, physical motion
  * - Widely recognized and understood by users
  *
  * This easing excels at:
  * - **Object drops**: Items falling into place
  * - **Landing animations**: Characters, UI elements touching down
  * - **Playful interactions**: Buttons, icons, notifications
  * - **Game elements**: Collectibles, power-ups, score displays
  * - **Error/success feedback**: Visual confirmation with personality
  * - **Cartoon physics**: Exaggerated, entertaining motion
  *
  * BounceOut is more popular than elasticOut when you want discrete impacts rather than
  * smooth oscillation. It conveys weight and physicality better than spring-based easings.
  *
  * The bouncing creates natural emphasis on the final position, making it excellent for
  * drawing attention to where something lands.
  *
  * @code
  * // Notification dropping in from above
  * auto y = tweeny::from(-100.0f)
  *   .to(0.0f)
  *   .via(easing::bounceOut)
  *   .during(45U)
  *   .build();
  *
  * // Button that bounces into place
  * auto scale = tweeny::from(0.0f)
  *   .to(1.0f)
  *   .via(easing::bounceOut)
  *   .during(40U)
  *   .build();
  * @endcode
  *
  * @see bounceIn For inverse bouncing at the start
  * @see bounceInOut For bouncing at both ends
  * @see elasticOut For smooth spring-like alternative
  */
 inline constexpr detail::bounceOutEasing bounceOut{};

 /**
  * @brief Bounce easing with bouncing at both start and end.
  *
  * The `bounceInOut` easing function combines reverse bouncing at the start with natural
  * bouncing at the end. The motion bounces with increasing height initially, accelerates
  * through the middle, then bounces to rest at the target.
  *
  * Motion profile:
  * - First half: Bounces with increasing amplitude (bounceIn)
  * - Midpoint: Smooth transition
  * - Second half: Bounces with decreasing amplitude (bounceOut)
  * - Creates playful, impact-based motion at both ends
  *
  * This easing is appropriate for:
  * - **Playful transitions**: Fun, energetic scene changes
  * - **Game UI**: High-energy, cartoon-style interfaces
  * - **Children's applications**: Whimsical, entertaining motion
  * - **Attention-grabbing effects**: Elements that need maximum personality
  *
  * BounceInOut is quite dramatic and can feel excessive for business applications,
  * productivity tools, and enterprise software where subtlety is preferred. The dual
  * bouncing works best in contexts where playfulness is a design goal.
  *
  * @code
  * // Playful modal transition
  * auto scale = tweeny::from(0.0f)
  *   .to(1.0f)
  *   .via(easing::bounceInOut)
  *   .during(60U)
  *   .build();
  * @endcode
  *
  * @see bounceIn For bouncing only at the start
  * @see bounceOut For bouncing only at the end (more commonly useful)
  * @see elasticInOut For spring-like alternative
  */
 inline constexpr detail::bounceInOutEasing bounceInOut{};

 /**
  * @brief Circular easing based on quarter-circle arc for smooth acceleration.
  *
  * The `circularIn` easing function accelerates following the curve of a quarter circle,
  * creating smooth, gradual acceleration. The motion follows the equation `1 - sqrt(1 - t²)`,
  * which traces a circular arc.
  *
  * Characteristics:
  * - Smooth, continuous acceleration
  * - More gradual than quadratic, less than cubic
  * - No sharp transitions in velocity
  * - Mathematically elegant curve
  *
  * This easing is ideal for:
  * - **Natural motion**: Movements that need organic feel
  * - **Camera movements**: Smooth pans and zooms
  * - **Scroll animations**: Gentle acceleration for reading comfort
  * - **Subtle UI transitions**: Motion with moderate acceleration
  *
  * Circular easings strike a balance between the gentle quadratic and the more aggressive
  * cubic curves, making them versatile for many contexts.
  *
  * @code
  * // Smooth camera pan
  * auto cameraX = tweeny::from(0.0f)
  *   .to(1000.0f)
  *   .via(easing::circularIn)
  *   .during(90U)
  *   .build();
  * @endcode
  *
  * @see circularOut For circular deceleration
  * @see circularInOut For circular acceleration and deceleration
  * @see quadraticIn For gentler acceleration
  * @see cubicIn For stronger acceleration
  */
 inline constexpr detail::circularInEasing circularIn{};

 /**
  * @brief Circular easing based on quarter-circle arc for smooth deceleration.
  *
  * The `circularOut` easing function decelerates following a circular curve, creating
  * smooth, natural-looking motion that settles gently to rest. Popular for UI animations
  * requiring moderate deceleration without dramatic emphasis.
  *
  * Characteristics:
  * - Smooth, continuous deceleration
  * - Natural feeling without being too soft or aggressive
  * - Balanced between gentle and pronounced
  * - Widely used in production interfaces
  *
  * This easing excels at:
  * - **Modern UI animations**: Cards, panels, menus
  * - **Material Design patterns**: Following Google's motion guidelines
  * - **Content transitions**: Page changes, tab switches
  * - **Professional applications**: Business and productivity software
  * - **General-purpose motion**: Versatile for many animation types
  *
  * CircularOut works well in most contexts. It's less dramatic than cubic but with
  * smoother deceleration than quadratic.
  *
  * @code
  * // Menu panel sliding in
  * auto x = tweeny::from(-300.0f)
  *   .to(0.0f)
  *   .via(easing::circularOut)
  *   .during(35U)
  *   .build();
  * @endcode
  *
  * @see circularIn For circular acceleration
  * @see circularInOut For circular motion at both ends
  * @see quadraticOut For gentler alternative
  * @see cubicOut For more pronounced alternative
  */
 inline constexpr detail::circularOutEasing circularOut{};

 /**
  * @brief Circular easing with smooth acceleration and deceleration.
  *
  * The `circularInOut` easing function uses circular curves for both acceleration and
  * deceleration, creating balanced motion suitable for general UI work. This is a
  * popular all-purpose easing.
  *
  * Motion profile:
  * - First half: Circular acceleration
  * - Midpoint: Maximum velocity
  * - Second half: Circular deceleration
  * - Creates smooth S-curve
  *
  * This easing is appropriate for:
  * - **All-purpose UI animations**: Buttons, dialogs, drawers
  * - **Material Design**: Recommended in Google's motion guidelines
  * - **Business applications**: Productivity tools, enterprise apps
  * - **Default animation choice**: Safe, versatile motion curve
  *
  * CircularInOut is often recommended as a starting point for animations because it
  * provides polish without being too subtle or too dramatic.
  *
  * @code
  * // Modal dialog appearance
  * auto opacity = tweeny::from(0.0f)
  *   .to(1.0f)
  *   .via(easing::circularInOut)
  *   .during(25U)
  *   .build();
  * @endcode
  *
  * @see circularIn For only acceleration
  * @see circularOut For only deceleration
  * @see quadraticInOut For gentler motion
  * @see cubicInOut For more dramatic motion
  */
 inline constexpr detail::circularInOutEasing circularInOut{};

 /**
  * @brief Cubic polynomial easing (t³) with moderate acceleration.
  *
  * The `cubicIn` easing function uses a cubic power curve for acceleration, providing
  * smooth, noticeable easing that's more pronounced than quadratic but less extreme
  * than quartic or exponential.
  *
  * Characteristics:
  * - Polynomial acceleration with power of 3
  * - Balanced between gentle and dramatic
  * - Widely used and well-understood
  * - Good default for many animation types
  *
  * This easing is ideal for:
  * - **Standard UI animations**: Menus, panels, overlays
  * - **Easing beginners**: Easy to understand and predict
  * - **General-purpose acceleration**: Versatile for many contexts
  * - **Medium-length animations**: 200-500ms durations
  *
  * CubicIn is a popular choice because it provides clear easing without being subtle
  * (like quadratic) or extreme (like quartic/exponential).
  *
  * Mathematically: `f(t) = t³`
  *
  * @code
  * // Dropdown menu opening
  * auto height = tweeny::from(0.0f)
  *   .to(200.0f)
  *   .via(easing::cubicIn)
  *   .during(30U)
  *   .build();
  * @endcode
  *
  * @see cubicOut For cubic deceleration
  * @see cubicInOut For cubic motion at both ends
  * @see quadraticIn For gentler acceleration
  * @see quarticIn For stronger acceleration
  */
 inline constexpr detail::cubicInEasing cubicIn{};

 /**
  * @brief Cubic polynomial easing (t³) with moderate deceleration.
  *
  * The `cubicOut` easing function provides smooth, balanced deceleration that's popular
  * across many design systems. It's pronounced enough to be noticeable but not dramatic.
  *
  * Characteristics:
  * - Smooth, natural-feeling deceleration
  * - More pronounced than quadratic, gentler than quartic
  * - Industry-standard motion curve
  * - Works well for most animation types
  *
  * This easing excels at:
  * - **Web interfaces**: Following CSS animation best practices
  * - **Mobile UI**: iOS and Android design patterns
  * - **Content animations**: Cards, lists, grids
  * - **Default easing choice**: Safe for most situations
  * - **User-triggered actions**: Button presses, toggles, switches
  *
  * CubicOut is one of the most commonly used easings in production interfaces. It
  * provides clear polish without drawing excessive attention to the motion itself.
  *
  * Mathematically: `f(t) = 1 - (1-t)³`
  *
  * @code
  * // Button press feedback
  * auto scale = tweeny::from(1.0f)
  *   .to(0.95f)
  *   .via(easing::cubicOut)
  *   .during(10U)
  *   .build();
  *
  * // Card appearing
  * auto opacity = tweeny::from(0.0f)
  *   .to(1.0f)
  *   .via(easing::cubicOut)
  *   .during(25U)
  *   .build();
  * @endcode
  *
  * @see cubicIn For cubic acceleration
  * @see cubicInOut For cubic motion at both ends
  * @see quadraticOut For gentler deceleration
  * @see quarticOut For stronger deceleration
  */
 inline constexpr detail::cubicOutEasing cubicOut{};

 /**
  * @brief Cubic polynomial easing with balanced acceleration and deceleration.
  *
  * The `cubicInOut` easing function combines cubic acceleration and deceleration for
  * smooth, professional motion. This is one of the most popular general-purpose easings.
  *
  * Motion profile:
  * - First half: Cubic acceleration (t³)
  * - Midpoint: Maximum velocity
  * - Second half: Cubic deceleration
  * - Creates smooth, balanced S-curve
  *
  * This easing is appropriate for:
  * - **All-purpose animations**: When in doubt, use this
  * - **Web standards**: CSS ease-in-out equivalent
  * - **Design system defaults**: Common in component libraries
  * - **Cross-platform consistency**: Works well everywhere
  * - **Medium animations**: 200-500ms sweet spot
  *
  * CubicInOut is frequently the default easing in design systems and animation libraries
  * because it provides clear, professional motion that works for most scenarios.
  *
  * Mathematically: Combines cubicIn for t < 0.5 and cubicOut for t >= 0.5
  *
  * @code
  * // Page transition
  * auto x = tweeny::from(0.0f)
  *   .to(1920.0f)
  *   .via(easing::cubicInOut)
  *   .during(40U)
  *   .build();
  * @endcode
  *
  * @see cubicIn For only acceleration
  * @see cubicOut For only deceleration
  * @see quadraticInOut For gentler motion
  * @see quarticInOut For more dramatic motion
  */
 inline constexpr detail::cubicInOutEasing cubicInOut{};
 /**
  * @brief Default easing function, alias for linear easing.
  *
  * The `def` easing is a convenience alias for `linear`, providing the same constant-velocity
  * interpolation with no acceleration or deceleration. It exists as a semantic indicator that
  * the default easing behavior is being explicitly chosen.
  *
  * Using `def` instead of `linear` can make code intent clearer in contexts where you want to
  * explicitly state "use the default behavior" rather than specifically requesting linear motion.
  * However, both are functionally identical.
  *
  * This is the easing applied when no via() call is made in the tween builder.
  *
  * @code
  * // These three tweens are functionally identical:
  * auto t1 = tweeny::from(0).to(100).during(60U).build();  // Implicit default
  * auto t2 = tweeny::from(0).to(100).via(easing::def).during(60U).build();
  * auto t3 = tweeny::from(0).to(100).via(easing::linear).during(60U).build();
  * @endcode
  *
  * @see linear For the primary documentation of this easing behavior
  */
 inline constexpr detail::defaultEasing def{};

 /**
  * @brief Elastic easing with oscillating spring-like motion at the start.
  *
  * The `elasticIn` easing function creates a spring or elastic band effect that oscillates
  * with increasing amplitude before reaching the starting point of the animation. The motion
  * resembles pulling back an elastic band that vibrates as tension builds.
  *
  * The oscillation characteristics:
  * - Multiple back-and-forth swings before the main motion begins
  * - Amplitude increases as the animation progresses
  * - Creates a "winding up" or "charging" effect
  * - More pronounced than backIn's single overshoot
  *
  * This easing is particularly effective for:
  * - **Magical or fantasy effects**: Spell charging, energy gathering
  * - **Exaggerated cartoon animations**: Extreme anticipation and wind-up
  * - **Attention-grabbing entrances**: Elements that need dramatic introduction
  * - **Game power-ups**: Visual feedback for charging actions
  * - **Playful UI elements**: Whimsical, high-energy interactions
  *
  * The elastic effect is more dramatic than back easing, making it suitable for contexts
  * where strong visual emphasis or entertainment value is desired. It's less appropriate
  * for subtle or professional interfaces.
  *
  * Mathematically, this uses a decaying sine wave with exponential amplitude growth.
  *
  * @warning This easing creates significant overshoot in both directions. Values will
  * oscillate well beyond the start value in both positive and negative directions. Ensure
  * your rendering system can handle these extreme values gracefully.
  *
  * @code
  * // Magical charging effect before an action
  * auto glow = tweeny::from(0.0f)
  *   .to(1.0f)
  *   .via(easing::elasticIn)
  *   .during(45U)
  *   .build();
  *
  * // The glow will oscillate negative before reaching 1.0f
  * // producing a "charging" visual effect
  * @endcode
  *
  * @see elasticOut For spring-like oscillation at the end
  * @see elasticInOut For oscillation at both start and end
  * @see backIn For a simpler single-overshoot alternative
  */
 inline constexpr detail::elasticInEasing elasticIn{};

 /**
  * @brief Elastic easing with spring-like oscillation at the end.
  *
  * The `elasticOut` easing function creates a natural spring or rubber band effect that
  * overshoots and oscillates around the target value before settling. This is one of the
  * most visually distinctive and playful easings, mimicking real-world elastic physics.
  *
  * The oscillation characteristics:
  * - Overshoots the target value multiple times
  * - Amplitude decreases with each oscillation (damped motion)
  * - Settles naturally at the final value
  * - Creates a bouncy, energetic feel without the hard impacts of bounce easing
  *
  * This easing excels at:
  * - **Playful UI animations**: Buttons, toggles, modal appearances
  * - **Game elements**: Power-up notifications, achievement popups, score displays
  * - **Cartoon-style motion**: Exaggerated, entertaining character movements
  * - **Attention direction**: Drawing eyes to important elements
  * - **Spring simulation**: Rubber bands, diving boards, springy objects
  * - **Joyful interactions**: Adding personality to standard UI patterns
  *
  * ElasticOut is widely used in modern mobile UI design to add energy and delight to
  * interactions. It's more pronounced than backOut but smoother than bounceOut.
  *
  * The spring feel makes animations memorable and adds perceived responsiveness, making
  * interfaces feel "alive" rather than mechanical.
  *
  * Mathematically, this uses a decaying sine wave with exponentially decreasing amplitude.
  *
  * @warning Values will oscillate beyond the target in both directions before settling.
  * For example, animating from 0 to 100 might temporarily reach 110, then 95, then 102,
  * before settling at 100. Ensure clipping or overflow handling is appropriate.
  *
  * @code
  * // Springy button press feedback
  * auto scale = tweeny::from(1.0f)
  *   .to(1.2f)
  *   .via(easing::elasticOut)
  *   .during(40U)
  *   .build();
  *
  * // Scale will overshoot 1.2f (maybe 1.3f) then oscillate
  * // down and up before settling at exactly 1.2f
  *
  * // Modal dialog with playful entrance
  * auto opacity = tweeny::from(0.0f)
  *   .to(1.0f)
  *   .via(easing::elasticOut)
  *   .during(50U)
  *   .build();
  * @endcode
  *
  * @see elasticIn For spring anticipation at the start
  * @see elasticInOut For oscillation at both ends
  * @see backOut For a subtler single-overshoot alternative
  * @see bounceOut For a similar but impact-based bouncing effect
  */
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
