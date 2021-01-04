#pragma once
#include <optional>
#include <functional>
#include <vector>
#include <utility>

#include <cppcoro/generator.hpp>

namespace itertools {

template <typename Container>
using Predicate = std::function<bool(typename Container::const_reference)>;

// =======================================================================================
//    BUILTINS
// =======================================================================================

template <typename T>
cppcoro::generator<typename T::reference>
reversed(T& iterable)
{
    for (auto it = iterable.rbegin(); it != iterable.rend(); ++it) {
        co_yield *it;
    }
}

template <typename T>
cppcoro::generator<typename T::const_reference>
reversed(const T& iterable)
{
    for (auto it = iterable.crbegin(); it != iterable.crend(); ++it) {
        co_yield *it;
    }
}

template <typename T>
cppcoro::generator<std::pair<const std::size_t, typename T::reference>>
enumerate(T& iterable, std::size_t start = 0)
{
    std::size_t index = start;
    for (auto& elem : iterable) {
        co_yield {index, elem};
        ++index;
    }
}

template <typename T>
cppcoro::generator<std::pair<const std::size_t, typename T::const_reference>>
enumerate(const T& iterable, std::size_t start = 0)
{
    std::size_t index = start;
    for (const auto& elem : iterable) {
        co_yield {index, elem};
        ++index;
    }
}

template <typename Left, typename Right>
cppcoro::generator<std::pair<typename Left::reference, typename Right::reference>>
zip(Left& left, Right& right)
{
    auto left_it = left.begin();
    auto right_it = right.begin();
    while (left_it != left.end() && right_it != right.end()) {
        co_yield {*left_it, *right_it};
        ++left_it;
        ++right_it;
    }
}

template <typename Left, typename Right>
cppcoro::generator<std::pair<typename Left::const_reference, typename Right::const_reference>>
zip(const Left& left, const Right& right)
{
    auto itl = left.cbegin();
    auto itr = right.cbegin();
    while (itl != left.cend() && itr != right.cend()) {
        co_yield {*itl, *itr};
        ++itl;
        ++itr;
    }
}

template <typename T>
cppcoro::generator<typename T::const_reference>
filter(std::function<bool(typename T::const_reference)> predicate, const T& iterable)
{
    for (const auto& elem : iterable) {
        if (predicate(elem)) {
            co_yield elem;
        }
    }
}

// =======================================================================================
//    INFINITE ITERATORS
// =======================================================================================

template <typename T>
cppcoro::generator<T>
count(const T& start = T{0}, const T& step = T{1})
{
    T val = start;
    while (true) {
        co_yield val;
        val += step;
    }
}

template <typename T>
cppcoro::generator<typename T::const_reference>
cycle(const T& iterable)
{
    while (true) {
        for (const auto& elem : iterable) {
            co_yield elem;
        }
    }
}

template <typename T>
cppcoro::generator<const T&>
repeat(const T& object, const std::optional<std::size_t>& times = {})
{
    if (times.has_value()) {
        for (std::size_t i = 0; i != times.value(); ++i) {
            co_yield object;
        }
    } else {
        while (true) {
            co_yield object;
        }
    }
}

// =======================================================================================
//    FINITE ITERATORS
// =======================================================================================

template <typename Data, typename Selectors>
cppcoro::generator<typename Data::const_reference>
compress(const Data& data, const Selectors& selectors)
{
    for (const auto& [object, selector] : zip(data, selectors)) {
        if (bool(selector)) {
            co_yield object;
        }
    }
}

template <typename T>
cppcoro::generator<typename T::const_reference>
dropwhile(Predicate<T> predicate, const T& iterable)
{
    auto it = iterable.begin();
    while (it != iterable.end() && predicate(*it)) {
        ++it;
    }
    while (it != iterable.end()) {
        co_yield *it;
        ++it;
    }

}

template <typename T>
cppcoro::generator<typename T::const_reference>
filterfalse(Predicate<T> predicate, const T& iterable)
{
    for (const auto& elem : iterable) {
        if (!predicate(elem)) {
            co_yield elem;
        }
    }
}

template <typename Func, typename... Args>
cppcoro::generator<typename std::result_of<Func(Args&&...)>::type>
starmap(Func&& function, const std::vector<std::tuple<Args...>>& args)
{
    for (const auto& signature : args) {
        co_yield std::apply(function, signature);
    }
}

template <typename T>
cppcoro::generator<typename T::const_reference>
takewhile(Predicate<T> predicate, const T& iterable)
{
    for (auto it = iterable.begin(); it != iterable.end() && predicate(*it); ++it) {
        co_yield *it;
    }
}

// =======================================================================================
//    COMBINATORIC ITERATORS
// =======================================================================================

}