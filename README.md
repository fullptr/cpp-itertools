# cpp-itertools
A C++20 single-header that implements Python's itertools library (and some standard builtins)
using C++20 coroutines. Built on top of [cppcoro](https://github.com/lewissbaker/cppcoro).

See the `example.cpp` file for a closer look.

## reversed
A Python builtin for looping backwards through a container. In C++ world, this generator works
on any object implementing `cbegin` and `cend`.

Python:
```
numbers = [1, 2, 3, 4, 5]
for x in reversed(numbers):
    foo(x)
```

C++:
```
std::vector<int> numbers{1, 2, 3, 4, 5};
for (auto x : itertools::reversed(numbers)) {
    foo(x);
}
```

## enumerate
Another builtin that loops through a container and provides a second value acting as a counter.
Works for any object with forward iterators.

Python:
```
words = ["Person", "Man", "Woman", "Camera", "TV"]
for i, x in enumerate(words):
    foo(i, x)
```

C++:
```
std::vector<std::string> words{"Person", "Man", "Woman", "Camera", "TV"};
for (auto& [i, x] : itertools::enumerate(words)) {
    foo(i, x);
}
```