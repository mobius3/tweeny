/*
 This file is part of the Tweeny library.

 Copyright (c) 2016-2021 Leonardo Guilherme Lucena de Freitas
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

/*
 * The purpose of this file is to hold implementations for the tween.h file, s
 * pecializing on the single value case.
 */
#ifndef TWEENY_TWEENONE_TCC
#define TWEENY_TWEENONE_TCC

namespace tweeny {
    template<typename T> tween<T> tween<T>::from(T t) { return tween(t); }
    template<typename T> tween<T>::tween() = default;
    template<typename T> tween<T>::tween(T t) {
        points.emplace_back(t);
    }

    template<typename T> tween<T> & tween<T>::to(T t) {
        points.emplace_back(t);
        return *this;
    }

    template<typename T>
    template<typename... Fs>
    tween<T> & tween<T>::via(Fs... fs) {
        points.at(points.size() - 2).via(fs...);
        return *this;
    }

    template<typename T>
    template<typename... Fs>
    tween<T> & tween<T>::via(const int index, Fs... fs) {
        points.at(static_cast<size_t>(index)).via(fs...);
        return *this;
    }




    template<typename T>
    template<typename... Ds>
    tween<T> & tween<T>::during(Ds... ds) {
        total = 0;
        points.at(points.size() - 2).during(ds...);
        for (detail::tweenpoint<T> & p : points) {
            total += p.duration();
            p.stacked = total;
        }
        return *this;
    }

    template<typename T>
    const T & tween<T>::step(const int32_t dt, const bool suppressCallbacks) {
        return step(static_cast<float>(dt)/static_cast<float>(total), suppressCallbacks);
    }

    template<typename T>
    const T & tween<T>::step(const uint32_t dt, const bool suppressCallbacks) {
        return step(static_cast<int32_t>(dt), suppressCallbacks);
    }

    template<typename T>
    const T & tween<T>::step(float dp, const bool suppressCallbacks) {
        dp *= currentDirection;
        seek(currentProgress + dp, true);
        if (!suppressCallbacks) dispatch(onStepCallbacks);
        return current;
    }

    template<typename T>
    const T & tween<T>::seek(float p, const bool suppressCallbacks) {
        p = detail::clip(p, 0.0f, 1.0f);
        currentProgress = p;
        render(p);
        if (!suppressCallbacks) dispatch(onSeekCallbacks);
        return current;
    }

    template<typename T>
    const T & tween<T>::seek(const int32_t d, const bool suppressCallbacks) {
        return seek(static_cast<float>(d) / static_cast<float>(total), suppressCallbacks);
    }

    template<typename T>
    const T & tween<T>::seek(const uint32_t d, const bool suppressCallbacks) {
        return seek(static_cast<float>(d) / static_cast<float>(total), suppressCallbacks);
    }

    template<typename T>
    uint32_t tween<T>::duration() const {
        return total;
    }

    template<typename T>
    void tween<T>::interpolate(const float prog, unsigned point, T & value) const {
        auto & p = points.at(point);
        const auto pointDuration = static_cast<uint32_t>(p.duration() - (p.stacked - prog * static_cast<float>(total)));
        float pointTotal = static_cast<float>(pointDuration) / static_cast<float>(p.duration());
        if (pointTotal > 1.0f) pointTotal = 1.0f;
        auto easing = std::get<0>(p.easings);
        value = easing(pointTotal, std::get<0>(p.values), std::get<0>(points.at(point+1).values));
    }

    template<typename T>
    void tween<T>::render(const float p) {
        currentPoint = pointAt(p);
        interpolate(p, currentPoint, current);
    }

    template<typename T>
    tween<T> & tween<T>::onStep(typename detail::tweentraits<T>::callbackType callback) {
        onStepCallbacks.push_back(callback);
        return *this;
    }

    template<typename T>
    tween<T> & tween<T>::onStep(typename detail::tweentraits<T>::noValuesCallbackType callback) {
        onStepCallbacks.push_back([callback](tween & tween, T) { return callback(tween); });
        return *this;
    }

    template<typename T>
    tween<T> & tween<T>::onStep(typename detail::tweentraits<T>::noTweenCallbackType callback) {
        onStepCallbacks.push_back([callback](tween &, T v) { return callback(v); });
        return *this;
    }

    template<typename T>
    tween<T> & tween<T>::onSeek(typename detail::tweentraits<T>::callbackType callback) {
        onSeekCallbacks.push_back(callback);
        return *this;
    }

    template<typename T>
    tween<T> & tween<T>::onSeek(typename detail::tweentraits<T>::noValuesCallbackType callback) {
        onSeekCallbacks.push_back([callback](tween & t, T) { return callback(t); });
        return *this;
    }

    template<typename T>
    tween<T> & tween<T>::onSeek(typename detail::tweentraits<T>::noTweenCallbackType callback) {
        onSeekCallbacks.push_back([callback](tween &, T v) { return callback(v); });
        return *this;
    }

    template<typename T>
    void tween<T>::dispatch(std::vector<typename traits::callbackType> & cbVector) {
        std::vector<size_t> dismissed;
        for (size_t i = 0; i < cbVector.size(); ++i) {
            auto && cb = cbVector[i];
            if (cb(*this, current)) dismissed.push_back(i);
        }

        if (!dismissed.empty()) {
            for (size_t i = 0; i < dismissed.size(); ++i) {
                size_t index = dismissed[i];
                cbVector[index] = cbVector.at(cbVector.size() - 1 - i);
            }
            cbVector.resize(cbVector.size() - dismissed.size());
        }
    }

    template<typename T>
    const T & tween<T>::peek() const {
        return current;
    }


    template<typename T>
    T tween<T>::peek(const float progress) const {
        T value;
        interpolate(progress, pointAt(progress), value);
        return value;
    }

    template<typename T>
    T tween<T>::peek(const uint32_t time) const {
        T value;
        const float progress = static_cast<float>(time) / static_cast<float>(total);
        interpolate(progress, pointAt(progress), value);
        return value;
    }


  template<typename T>
    float tween<T>::progress() const {
        return currentProgress;
    }

    template<typename T>
    tween<T> & tween<T>::forward() {
        currentDirection = 1;
        return *this;
    }

    template<typename T>
    tween<T> & tween<T>::backward() {
        currentDirection = -1;
        return *this;
    }

    template<typename T>
    int tween<T>::direction() const {
        return currentDirection;
    }

    template<typename T>
    const T & tween<T>::jump(size_t point, bool suppressCallbacks) {
        point = detail::clip(point, static_cast<size_t>(0), points.size() -1);
        return seek(points.at(point).stacked, suppressCallbacks);
    }

    template<typename T> uint16_t tween<T>::point() const {
        return currentPoint;
    }

    template<typename T> uint16_t tween<T>::pointAt(float progress) const {
        progress = detail::clip(progress, 0.0f, 1.0f);
        auto t = static_cast<uint32_t>(progress * total);
        uint16_t point = 0;
        while (t > points.at(point).stacked) point++;
        if (point > 0 && t <= points.at(point - 1u).stacked) point--;
        return point;
    }
}
#endif //TWEENY_TWEENONE_TCC
