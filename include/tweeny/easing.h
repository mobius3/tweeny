/*
This file is part of the Tweeny library.

Copyright (c) 2016-2026 Leonardo Guilherme Lucena de Freitas
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
 * animations.
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
  * @see Visualize at https://easings.net/#easeInBack
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
  * @see Visualize at https://easings.net/#easeOutBack
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
  * @see Visualize at https://easings.net/#easeInOutBack
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
  * @see Visualize at https://easings.net/#easeInBounce
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
  * @see Visualize at https://easings.net/#easeOutBounce
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
  * @see Visualize at https://easings.net/#easeInOutBounce
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
  * @see Visualize at https://easings.net/#easeInCirc
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
  * @see Visualize at https://easings.net/#easeOutCirc
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
  * @see Visualize at https://easings.net/#easeInOutCirc
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
  * @see Visualize at https://easings.net/#easeInCubic
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
  * @see Visualize at https://easings.net/#easeOutCubic
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
  * @see Visualize at https://easings.net/#easeInOutCubic
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
  * @see Visualize at https://easings.net/#easeInElastic
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
  * @see Visualize at https://easings.net/#easeOutElastic
  */
 inline constexpr detail::elasticOutEasing elasticOut{};

 /**
  * @brief Elastic easing combining spring oscillation at both start and end.
  *
  * The `elasticInOut` easing function creates dramatic elastic motion with oscillation
  * during both the initial acceleration and final deceleration phases. The animation
  * winds up with spring-like vibration, accelerates smoothly through the middle, then
  * oscillates around the target before settling.
  *
  * The motion profile:
  * - First half: Oscillates with increasing amplitude (elasticIn behavior)
  * - Middle: Smooth transition through the midpoint
  * - Second half: Oscillates with decreasing amplitude (elasticOut behavior)
  * - Creates the most dramatic elastic effect available
  *
  * This easing is appropriate for:
  * - **Hero animations**: Focal transitions that demand attention
  * - **Game events**: Critical moments, boss appearances, dramatic reveals
  * - **Cartoon physics**: Exaggerated, entertaining motion for stylized visuals
  * - **Transitions with flair**: Scene changes that need maximum personality
  * - **Experimental UI**: Interfaces prioritizing delight over convention
  *
  * ElasticInOut is the most expressive elastic variant but also the most extreme. It works
  * best for animations that are:
  * - Intentionally playful or whimsical
  * - The primary focus of user attention
  * - Part of a stylized, high-energy aesthetic
  * - Not repeated frequently (can become tiresome)
  *
  * Use sparingly; the dual oscillation can feel excessive for everyday interactions.
  * Consider elasticOut or backInOut for a more balanced alternative.
  *
  * @warning This easing produces extreme value overshoots in both directions throughout
  * the animation. During the first half, values oscillate around the start; during the
  * second half, around the target. Plan for values far outside the expected range.
  *
  * @code
  * // Dramatic screen transition
  * auto position = tweeny::from(0.0f)
  *   .to(1920.0f)
  *   .via(easing::elasticInOut)
  *   .during(90U)
  *   .build();
  *
  * // Position will oscillate around 0.0f at start and 1920.0f at end
  *
  * // Game title appearing with maximum impact
  * auto scale = tweeny::from(0.0f)
  *   .to(2.0f)
  *   .via(easing::elasticInOut)
  *   .during(75U)
  *   .build();
  * @endcode
  *
  * @see elasticIn For oscillation only at the start
  * @see elasticOut For oscillation only at the end (more commonly useful)
  * @see backInOut For a less extreme but still expressive alternative
  * @see Visualize at https://easings.net/#easeInOutElastic
  */
 inline constexpr detail::elasticInOutEasing elasticInOut{};

 /**
  * @brief Exponential easing with very slow start and explosive acceleration.
  *
  * The `exponentialIn` easing function starts extremely slowly and builds to a very rapid
  * acceleration toward the end. Based on exponential growth (2^x), this creates one of the
  * most dramatic acceleration curves available, with velocity increasing exponentially over time.
  *
  * Characteristics:
  * - Almost no visible motion for the first portion of the animation
  * - Sudden, explosive acceleration in the final phase
  * - Change rate doubles repeatedly as time progresses
  * - Creates extreme contrast between start and end velocity
  *
  * This easing is ideal for:
  * - **Dramatic reveals**: Elements that burst into view
  * - **Explosive effects**: Particle systems, energy blasts, explosions
  * - **Fade-ins with impact**: Starting invisible and suddenly appearing
  * - **Speed-up effects**: Rockets launching, vehicles accelerating
  * - **Tension building**: Slow build-up to sudden release
  *
  * The extreme acceleration curve makes this feel more dramatic than polynomial easings
  * (quadratic, cubic, etc.). The motion appears to "explode" into existence rather than
  * gradually accelerate.
  *
  * Use exponentialIn when you want maximum contrast between the patient start and the
  * explosive finish. For most UI work, cubic or quartic easings provide sufficient
  * acceleration with less extreme behavior.
  *
  * Mathematically: `f(t) = 2^(10 * (t - 1))`
  *
  * @code
  * // Fade in that suddenly snaps to full visibility
  * auto opacity = tweeny::from(0.0f)
  *   .to(1.0f)
  *   .via(easing::exponentialIn)
  *   .during(45U)
  *   .build();
  *
  * // Rocket launch with explosive acceleration
  * auto velocity = tweeny::from(0.0f)
  *   .to(1000.0f)
  *   .via(easing::exponentialIn)
  *   .during(120U)
  *   .build();
  * @endcode
  *
  * @see exponentialOut For explosive deceleration at the end
  * @see exponentialInOut For dramatic acceleration and deceleration
  * @see quarticIn For strong but less extreme acceleration
  * @see Visualize at https://easings.net/#easeInExpo
  */
 inline constexpr detail::exponentialInEasing exponentialIn{};

 /**
  * @brief Exponential easing with explosive start and gradual slow-down.
  *
  * The `exponentialOut` easing function starts with maximum velocity and decelerates
  * exponentially, creating a smooth glide to a stop. The initial burst of speed followed
  * by gradual settling creates a powerful, energetic feel.
  *
  * Characteristics:
  * - Immediate, explosive motion at the start
  * - Exponentially decreasing velocity
  * - Long, smooth deceleration phase
  * - Settles gently to final value
  *
  * This easing excels at:
  * - **Quick UI responses**: Instant feedback that settles smoothly
  * - **Impact effects**: Objects hitting and settling into place
  * - **Momentum-based motion**: Thrown objects, swipe gestures
  * - **Energetic entrances**: Elements that burst in with energy
  * - **Modern UI patterns**: iOS-style animations with quick start
  *
  * ExponentialOut is popular in modern mobile design because it provides immediate
  * visual feedback (the fast start) while ending smoothly. Users perceive the interface
  * as highly responsive due to the instant motion.
  *
  * The long tail of deceleration gives animations a "quality feel" - nothing stops
  * abruptly. This is gentler on the eyes than linear or even cubic deceleration.
  *
  * Mathematically: `f(t) = 1 - 2^(-10 * t)`
  *
  * @code
  * // Responsive drawer that slides out quickly then settles
  * auto position = tweeny::from(-300.0f)
  *   .to(0.0f)
  *   .via(easing::exponentialOut)
  *   .during(35U)
  *   .build();
  *
  * // Notification that pops in with energy
  * auto scale = tweeny::from(0.0f)
  *   .to(1.0f)
  *   .via(easing::exponentialOut)
  *   .during(25U)
  *   .build();
  * @endcode
  *
  * @see exponentialIn For explosive acceleration at the start
  * @see exponentialInOut For explosive motion at both ends
  * @see quarticOut For strong but less extreme deceleration
  * @see Visualize at https://easings.net/#easeOutExpo
  */
 inline constexpr detail::exponentialOutEasing exponentialOut{};

 /**
  * @brief Exponential easing with extreme acceleration and deceleration.
  *
  * The `exponentialInOut` easing function combines explosive acceleration in the first
  * half with explosive deceleration in the second half. This creates one of the most
  * dramatic, high-energy motion curves available, with rapid changes at both ends and
  * smooth motion through the middle.
  *
  * Motion profile:
  * - First half: Exponential acceleration from near-zero velocity
  * - Midpoint: Maximum velocity
  * - Second half: Exponential deceleration to rest
  * - Creates extreme S-curve shape
  *
  * This easing is appropriate for:
  * - **High-impact transitions**: Scene changes, screen swipes
  * - **Dramatic animations**: Hero elements, focal content
  * - **Fast-paced interfaces**: Games, action-oriented apps
  * - **Attention-grabbing motion**: Elements that need maximum visibility
  * - **Strong transitions**: For elements moving significant distances or longer durations (500ms+)
  *
  * ExponentialInOut creates a powerful sense of momentum and energy. The motion feels
  * purposeful and confident. However, the extreme acceleration can be disorienting if
  * overused or applied to large elements.
  *
  * Best practices:
  * - Use for animations under 1 second duration
  * - Apply to elements that move short to medium distances
  * - Reserve for important, infrequent transitions
  * - Consider quarticInOut or quinticInOut as less extreme alternatives
  *
  * Mathematically: Combines exponentialIn for t < 0.5 and exponentialOut for t >= 0.5
  *
  * @code
  * // Page transition with explosive motion
  * auto position = tweeny::from(0.0f)
  *   .to(1920.0f)
  *   .via(easing::exponentialInOut)
  *   .during(40U)
  *   .build();
  *
  * // Modal dialog with dramatic appearance
  * auto opacity = tweeny::from(0.0f)
  *   .to(1.0f)
  *   .via(easing::exponentialInOut)
  *   .during(30U)
  *   .build();
  * @endcode
  *
  * @see exponentialIn For only explosive acceleration
  * @see exponentialOut For only explosive deceleration
  * @see quinticInOut For slightly less extreme alternative
  * @see Visualize at https://easings.net/#easeInOutExpo
  */
 inline constexpr detail::exponentialInOutEasing exponentialInOut{};
 /**
  * @brief Linear easing function with constant velocity throughout the animation.
  *
  * The `linear` easing function produces uniform motion with no acceleration or deceleration.
  * The interpolation progresses at a constant rate from start to finish, creating mechanical,
  * predictable movement.
  *
  * Linear easing is characterized by:
  * - Constant velocity: the rate of change never varies
  * - No ease-in or ease-out: motion starts and stops abruptly
  * - Simple mathematical relationship: output = start + (end - start) * progress
  * - Predictable timing: halfway through time means halfway through distance
  *
  * This easing is appropriate for:
  * - **Mechanical objects**: Conveyor belts, pistons, automated systems
  * - **Progress indicators**: Loading bars, timers, countdowns
  * - **Continuous loops**: Rotating objects, scrolling backgrounds
  * - **Data visualization**: Graph animations where consistency is important
  * - **Debug and testing**: Predictable behavior for verification
  *
  * Linear easing is generally **not recommended** for most UI animations because:
  * - Lacks the natural feel of acceleration/deceleration
  * - Abrupt starts and stops can feel jarring
  * - Missing visual polish that easing provides
  * - Human perception expects objects to ease into and out of motion
  *
  * However, it serves as the foundation for all other easing functions and is essential
  * when mechanical precision is more important than natural motion feel.
  *
  * Mathematically, this implements: `f(t) = t` where t is normalized progress [0, 1].
  *
  * @code
  * // Constant velocity scrolling background
  * auto scroll = tweeny::from(0.0f)
  *   .to(1000.0f)
  *   .via(easing::linear)
  *   .during(600U)
  *   .build();
  *
  * // Progress indicator that matches time exactly
  * auto progress = tweeny::from(0)
  *   .to(100)
  *   .via(easing::linear)
  *   .during(100U)
  *   .build();
  *
  * // At frame 50, progress will be exactly 50
  * @endcode
  *
  * @note Linear is the default easing when no via() is specified, though using def is
  * more explicit in code.
  *
  * @see def Alias for linear easing
  * @see quadraticInOut For a gentle alternative with ease-in and ease-out
  * @see sinusoidalInOut For smooth, natural-feeling motion
  */
 inline constexpr detail::linearEasing linear{};

 /**
  * @brief Quadratic polynomial easing (t²) with gentle acceleration.
  *
  * The `quadraticIn` easing function uses a squared power curve for acceleration,
  * providing the gentlest polynomial easing. It's more subtle than cubic but still
  * provides noticeable easing.
  *
  * Characteristics:
  * - Gentle, smooth acceleration
  * - Polynomial with power of 2
  * - Subtle but perceptible easing
  * - Good for beginners and subtle animations
  *
  * This easing is ideal for:
  * - **Subtle UI motion**: When easing should be felt but not seen
  * - **Quick animations**: Short durations where gentle curves work best
  * - **Minimal designs**: Interfaces prioritizing restraint
  * - **Learning easings**: Easy to understand and predict
  *
  * Mathematically: `f(t) = t²`
  *
  * @code
  * // Gentle fade in
  * auto opacity = tweeny::from(0.0f)
  *   .to(1.0f)
  *   .via(easing::quadraticIn)
  *   .during(20U)
  *   .build();
  * @endcode
  *
  * @see quadraticOut For gentle deceleration
  * @see quadraticInOut For gentle motion at both ends
  * @see cubicIn For more pronounced acceleration
  * @see Visualize at https://easings.net/#easeInQuad
  */
 inline constexpr detail::quadraticInEasing quadraticIn{};

 /**
  * @brief Quadratic polynomial easing (t²) with gentle deceleration.
  *
  * The `quadraticOut` easing function provides subtle, smooth deceleration. It's the
  * gentlest polynomial easing, perfect when you want polish without drama.
  *
  * Characteristics:
  * - Gentle, smooth deceleration
  * - Subtle but professional feel
  * - Never feels too slow or too fast
  * - Safe choice for any context
  *
  * This easing excels at:
  * - **Subtle UI polish**: Adding refinement without drawing attention
  * - **Fast animations**: 100-200ms durations
  * - **Minimal interfaces**: Clean, understated design systems
  * - **Accessibility-friendly**: Gentle motion reduces disorientation
  * - **Background animations**: Motion that shouldn't distract
  *
  * QuadraticOut is great when you want animations to stay out of the way. It's less
  * dramatic than cubic but smoother than linear due to gradual deceleration.
  *
  * Mathematically: `f(t) = 1 - (1-t)²`
  *
  * @code
  * // Subtle tooltip appearance
  * auto opacity = tweeny::from(0.0f)
  *   .to(1.0f)
  *   .via(easing::quadraticOut)
  *   .during(15U)
  *   .build();
  * @endcode
  *
  * @see quadraticIn For gentle acceleration
  * @see quadraticInOut For gentle motion at both ends
  * @see cubicOut For more pronounced deceleration
  * @see Visualize at https://easings.net/#easeOutQuad
  */
 inline constexpr detail::quadraticOutEasing quadraticOut{};

 /**
  * @brief Quadratic polynomial easing with gentle acceleration and deceleration.
  *
  * The `quadraticInOut` easing function provides the most subtle polynomial S-curve.
  * Perfect for animations that need easing but should remain understated.
  *
  * Motion profile:
  * - First half: Gentle acceleration (t²)
  * - Midpoint: Maximum velocity
  * - Second half: Gentle deceleration
  * - Creates subtle S-curve
  *
  * This easing is appropriate for:
  * - **Minimal design systems**: Understated, refined motion
  * - **Fast animations**: Under 200ms where gentle curves shine
  * - **Accessibility**: Motion-sensitive users
  * - **Background motion**: Animations that shouldn't dominate
  *
  * Mathematically: Combines quadraticIn for t < 0.5 and quadraticOut for t >= 0.5
  *
  * @code
  * // Subtle menu transition
  * auto x = tweeny::from(0.0f)
  *   .to(100.0f)
  *   .via(easing::quadraticInOut)
  *   .during(20U)
  *   .build();
  * @endcode
  *
  * @see quadraticIn For only gentle acceleration
  * @see quadraticOut For only gentle deceleration
  * @see cubicInOut For more pronounced motion
  * @see Visualize at https://easings.net/#easeInOutQuad
  */
 inline constexpr detail::quadraticInOutEasing quadraticInOut{};

 /**
  * @brief Quartic polynomial easing (t⁴) with strong acceleration.
  *
  * The `quarticIn` easing function uses a power-4 curve for acceleration, creating
  * pronounced easing that's stronger than cubic but less extreme than exponential.
  *
  * Characteristics:
  * - Strong acceleration curve
  * - Polynomial with power of 4
  * - Very slow start, rapid finish
  * - More dramatic than cubic
  *
  * This easing is ideal for:
  * - **Dramatic entrances**: Elements that burst into view
  * - **Emphasis**: Drawing attention to motion start
  * - **Game animations**: Action-oriented interfaces
  * - **Long animations**: Over 500ms where strong curves work
  *
  * Mathematically: `f(t) = t⁴`
  *
  * @code
  * // Panel sliding in with emphasis
  * auto x = tweeny::from(-400.0f)
  *   .to(0.0f)
  *   .via(easing::quarticIn)
  *   .during(50U)
  *   .build();
  * @endcode
  *
  * @see quarticOut For strong deceleration
  * @see quarticInOut For strong motion at both ends
  * @see cubicIn For gentler acceleration
  * @see quinticIn For even stronger acceleration
  * @see Visualize at https://easings.net/#easeInQuart
  */
 inline constexpr detail::quarticInEasing quarticIn{};

 /**
  * @brief Quartic polynomial easing (t⁴) with strong deceleration.
  *
  * The `quarticOut` easing function provides pronounced deceleration that's popular
  * for animations needing clear emphasis without being as extreme as exponential.
  *
  * Characteristics:
  * - Strong deceleration curve
  * - Smooth, extended slowdown
  * - Emphasizes final position
  * - Balanced between cubic and exponential
  *
  * This easing excels at:
  * - **Emphasized arrivals**: Elements settling with impact
  * - **Current design patterns**: Strong deceleration suitable for emphasized arrivals
  * - **Medium-length animations**: 300-600ms sweet spot
  * - **Purposeful motion**: Clear acceleration and deceleration
  *
  * QuarticOut provides more "oomph" than cubic while remaining smooth and
  * professional. It's a good choice when cubic feels too subtle.
  *
  * Mathematically: `f(t) = 1 - (1-t)⁴`
  *
  * @code
  * // Card sliding into place with emphasis
  * auto y = tweeny::from(200.0f)
  *   .to(0.0f)
  *   .via(easing::quarticOut)
  *   .during(40U)
  *   .build();
  * @endcode
  *
  * @see quarticIn For strong acceleration
  * @see quarticInOut For strong motion at both ends
  * @see cubicOut For gentler deceleration
  * @see quinticOut For even stronger deceleration
  * @see Visualize at https://easings.net/#easeOutQuart
  */
 inline constexpr detail::quarticOutEasing quarticOut{};

 /**
  * @brief Quartic polynomial easing with strong acceleration and deceleration.
  *
  * The `quarticInOut` easing function combines strong acceleration and deceleration
  * for confident, purposeful motion. More dramatic than cubic, less extreme than quintic.
  *
  * Motion profile:
  * - First half: Strong acceleration (t⁴)
  * - Midpoint: Maximum velocity
  * - Second half: Strong deceleration
  * - Creates pronounced S-curve
  *
  * This easing is appropriate for:
  * - **Emphasized transitions**: Strong acceleration and deceleration
  * - **Current design patterns**: Strong deceleration curves
  * - **Important animations**: Focal transitions
  * - **Medium durations**: 300-600ms range
  *
  * Mathematically: Combines quarticIn for t < 0.5 and quarticOut for t >= 0.5
  *
  * @code
  * // Page transition with impact
  * auto x = tweeny::from(0.0f)
  *   .to(1920.0f)
  *   .via(easing::quarticInOut)
  *   .during(45U)
  *   .build();
  * @endcode
  *
  * @see quarticIn For only strong acceleration
  * @see quarticOut For only strong deceleration
  * @see cubicInOut For gentler motion
  * @see quinticInOut For more dramatic motion
  * @see Visualize at https://easings.net/#easeInOutQuart
  */
 inline constexpr detail::quarticInOutEasing quarticInOut{};

 /**
  * @brief Quintic polynomial easing (t⁵) with very strong acceleration.
  *
  * The `quinticIn` easing function uses a power-5 curve, creating the strongest
  * polynomial acceleration. It's more extreme than quartic but less than exponential.
  *
  * Characteristics:
  * - Very strong acceleration
  * - Polynomial with power of 5
  * - Extremely slow start
  * - Dramatic finish
  *
  * This easing is ideal for:
  * - **Maximum polynomial emphasis**: Strongest polynomial option
  * - **Dramatic effects**: Hero animations, focal transitions
  * - **Long animations**: Over 600ms durations
  * - **Alternative to exponential**: Slightly less extreme
  *
  * Mathematically: `f(t) = t⁵`
  *
  * @code
  * // Dramatic hero section reveal
  * auto scale = tweeny::from(0.0f)
  *   .to(1.0f)
  *   .via(easing::quinticIn)
  *   .during(60U)
  *   .build();
  * @endcode
  *
  * @see quinticOut For very strong deceleration
  * @see quinticInOut For very strong motion at both ends
  * @see quarticIn For slightly gentler acceleration
  * @see exponentialIn For even more extreme acceleration
  * @see Visualize at https://easings.net/#easeInQuint
  */
 inline constexpr detail::quinticInEasing quinticIn{};

 /**
  * @brief Quintic polynomial easing (t⁵) with very strong deceleration.
  *
  * The `quinticOut` easing function provides the strongest polynomial deceleration,
  * creating smooth but dramatic slowdown. Popular for animations with long durations
  * (500ms+) requiring strong deceleration.
  *
  * Characteristics:
  * - Very strong deceleration
  * - Long, smooth tail
  * - Very strong deceleration with extended slowdown phase
  * - Strongest polynomial option
  *
  * This easing excels at:
  * - **Applications prioritizing strong visual emphasis**: Galleries, portfolios, marketing sites
  * - **Animations with extended durations**: Requiring maximum polynomial deceleration
  * - **Longer animations**: 500ms+ durations
  * - **Emphasized arrivals**: Strong focus on end state
  *
  * QuinticOut provides the strongest polynomial deceleration while maintaining a
  * smooth, continuous curve.
  *
  * Mathematically: `f(t) = 1 - (1-t)⁵`
  *
  * @code
  * // Premium modal entrance
  * auto opacity = tweeny::from(0.0f)
  *   .to(1.0f)
  *   .via(easing::quinticOut)
  *   .during(45U)
  *   .build();
  * @endcode
  *
  * @see quinticIn For very strong acceleration
  * @see quinticInOut For very strong motion at both ends
  * @see quarticOut For slightly gentler deceleration
  * @see exponentialOut For even more extreme deceleration
  * @see Visualize at https://easings.net/#easeOutQuint
  */
 inline constexpr detail::quinticOutEasing quinticOut{};

 /**
  * @brief Quintic polynomial easing with very strong acceleration and deceleration.
  *
  * The `quinticInOut` easing function provides the strongest polynomial S-curve,
  * creating powerful motion with maximum polynomial emphasis.
  *
  * Motion profile:
  * - First half: Very strong acceleration (t⁵)
  * - Midpoint: Maximum velocity
  * - Second half: Very strong deceleration
  * - Creates dramatic S-curve
  *
  * This easing is appropriate for:
  * - **Applications prioritizing strong visual emphasis**: Galleries, portfolios, marketing sites
  * - **Animations requiring maximum polynomial emphasis**: At both acceleration and deceleration phases
  * - **Important transitions**: Focal, memorable moments
  * - **Longer animations**: 500ms+ durations
  *
  * Mathematically: Combines quinticIn for t < 0.5 and quinticOut for t >= 0.5
  *
  * @code
  * // Premium screen transition
  * auto x = tweeny::from(0.0f)
  *   .to(1920.0f)
  *   .via(easing::quinticInOut)
  *   .during(50U)
  *   .build();
  * @endcode
  *
  * @see quinticIn For only very strong acceleration
  * @see quinticOut For only very strong deceleration
  * @see quarticInOut For gentler motion
  * @see exponentialInOut For more extreme motion
  * @see Visualize at https://easings.net/#easeInOutQuint
  */
 inline constexpr detail::quinticInOutEasing quinticInOut{};

 /**
  * @brief Sinusoidal easing based on sine wave for smooth acceleration.
  *
  * The `sinusoidalIn` easing function uses a sine curve for acceleration, creating
  * extremely smooth, natural motion. Based on trigonometric functions rather than
  * polynomials.
  *
  * Characteristics:
  * - Very smooth acceleration
  * - Natural, organic feel
  * - No abrupt velocity changes
  * - Gentle but noticeable
  *
  * This easing is ideal for:
  * - **Natural motion**: Organic, flowing animations
  * - **Smooth camera moves**: Pans, zooms, orbits
  * - **Elegant transitions**: Refined, sophisticated feel
  * - **Accessible animations**: Gentle on motion sensitivity
  *
  * Mathematically: `f(t) = 1 - cos(t * π/2)`
  *
  * @code
  * // Smooth camera pan
  * auto x = tweeny::from(0.0f)
  *   .to(1000.0f)
  *   .via(easing::sinusoidalIn)
  *   .during(60U)
  *   .build();
  * @endcode
  *
  * @see sinusoidalOut For smooth deceleration
  * @see sinusoidalInOut For smooth motion at both ends
  * @see quadraticIn For similar gentleness
  * @see Visualize at https://easings.net/#easeInSine
  */
 inline constexpr detail::sinusoidalInEasing sinusoidalIn{};

 /**
  * @brief Sinusoidal easing based on sine wave for smooth deceleration.
  *
  * The `sinusoidalOut` easing function uses a sine curve for deceleration, creating
  * extremely smooth, natural motion that settles gently.
  *
  * Characteristics:
  * - Very smooth deceleration
  * - Natural, flowing motion
  * - Gentle slowdown
  * - Mathematically elegant
  *
  * This easing excels at:
  * - **Natural UI motion**: Smooth, organic feel
  * - **Continuous animations**: Loops, cycles, repeated motion
  * - **Gentle transitions**: Calm, relaxed interfaces
  * - **Accessible design**: Motion-sensitivity friendly
  *
  * SinusoidalOut is excellent when you want smoothness above all else. It's
  * gentler than quadratic while still providing clear easing.
  *
  * Mathematically: `f(t) = sin(t * π/2)`
  *
  * @code
  * // Smooth fade in
  * auto opacity = tweeny::from(0.0f)
  *   .to(1.0f)
  *   .via(easing::sinusoidalOut)
  *   .during(30U)
  *   .build();
  * @endcode
  *
  * @see sinusoidalIn For smooth acceleration
  * @see sinusoidalInOut For smooth motion at both ends
  * @see quadraticOut For similar gentleness
  * @see Visualize at https://easings.net/#easeOutSine
  */
 inline constexpr detail::sinusoidalOutEasing sinusoidalOut{};

 /**
  * @brief Sinusoidal easing with smooth acceleration and deceleration.
  *
  * The `sinusoidalInOut` easing function uses sine curves for both acceleration
  * and deceleration, creating the smoothest possible S-curve motion.
  *
  * Motion profile:
  * - First half: Smooth sine-based acceleration
  * - Midpoint: Maximum velocity
  * - Second half: Smooth sine-based deceleration
  * - Creates extremely smooth S-curve
  *
  * This easing is appropriate for:
  * - **Natural, organic motion**: Smoothest easing available
  * - **Continuous loops**: Seamless repeated animations
  * - **Calm interfaces**: Relaxed, gentle design systems
  * - **Accessible animations**: Minimal motion stress
  *
  * SinusoidalInOut is the smoothest InOut easing, making it perfect when
  * fluid, natural motion is the priority.
  *
  * Mathematically: `f(t) = (1 - cos(t * π)) / 2`
  *
  * @code
  * // Ultra-smooth transition
  * auto x = tweeny::from(0.0f)
  *   .to(100.0f)
  *   .via(easing::sinusoidalInOut)
  *   .during(40U)
  *   .build();
  * @endcode
  *
  * @see sinusoidalIn For only smooth acceleration
  * @see sinusoidalOut For only smooth deceleration
  * @see quadraticInOut For similar gentleness
  * @see Visualize at https://easings.net/#easeInOutSine
  */
 inline constexpr detail::sinusoidalInOutEasing sinusoidalInOut{};

 /**
  * @brief Stepped easing that holds the start value until the keyframe completes.
  *
  * The `stepped` easing function returns the starting value throughout the entire
  * duration of the keyframe segment, only jumping to the target value when moving
  * to the next keyframe. This creates instant transitions between keyframes without
  * any interpolation within each segment.
  *
  * Characteristics:
  * - No interpolation within keyframe segments
  * - Holds start value until keyframe ends
  * - Instant jumps between keyframes
  * - Creates discrete, stair-step motion
  *
  * This easing is ideal for:
  * - **Discrete state transitions**: Values that shouldn't interpolate smoothly
  * - **Keyframe-based animations**: Step through distinct poses or states
  * - **Frame-by-frame effects**: Hold each frame without blending
  * - **Boolean-like values**: Properties that need instant changes
  * - **Sprite switching**: Change sprites at keyframe boundaries
  * - **Cut transitions**: Instant changes without fading
  *
  * Stepped is fundamentally different from other easings because it eliminates
  * interpolation entirely within each keyframe segment, creating hard cuts between
  * animation states.
  *
  * @code
  * // Hold value at each keyframe, jump instantly between them
  * auto value = tweeny::from(0)
  *   .to(10).via(easing::stepped).during(100U)
  *   .to(20).via(easing::stepped).during(100U)
  *   .to(30).via(easing::stepped).during(100U)
  *   .build();
  *
  * // During frames 0-99: returns 0
  * // During frames 100-199: returns 10
  * // During frames 200-299: returns 20
  * // At frame 300: returns 30
  *
  * // Useful for sprite animation indices
  * auto spriteIndex = tweeny::from(0)
  *   .to(1).via(easing::stepped).during(10U)
  *   .to(2).via(easing::stepped).during(10U)
  *   .to(3).via(easing::stepped).during(10U)
  *   .build();
  * // Holds each sprite index for 10 frames, then instantly switches
  * @endcode
  *
  * @see linear For smooth constant-velocity interpolation
  */
 inline constexpr detail::steppedEasing stepped{};
}

#include "detail/easing/by-name.h"

#endif //TWEENY_EASING_H

