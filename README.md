# tiny-vector

A lightweight, header-only, templated C++ vector class built from scratch as a learning project — implemented with an emphasis on correct resource management (RAII, the Rule of Five), const-correctness, and test coverage under AddressSanitizer.

## Motivation

This project exists to build real, from-first-principles understanding of C++ memory management, object semantics, and generic programming — not to reimplement `std::vector` for production use. Every design decision below was made deliberately, usually after working through the underlying mechanism (why a shallow copy causes a double-free, why `const` needs enforcing at compile time, why templates must live in headers, etc.) rather than copying idiom without understanding it.

## Features

- **Templated** (`Vector<T>`) — works with `int`, `float`, `double`, and other types satisfying basic arithmetic/default-construction requirements
- **Full Rule of Five** — copy constructor, copy assignment, move constructor, move assignment, and destructor, all implemented explicitly and guarded against self-assignment
- **Const-correctness** — `operator[]`, `at()`, and `size()` each have const and non-const overloads where appropriate, so the class behaves correctly whether accessed through a `Vector<T>&` or a `const Vector<T>&`
- **Bounds-checked access** via `.at(i)`, which throws `std::out_of_range` on an invalid index, alongside unchecked `operator[]` for performance-sensitive access (mirroring the `std::vector` convention)
- **Elementwise addition** via `operator+`, with a thrown `std::invalid_argument` on mismatched lengths
- **Forward iterator support** (`begin()`/`end()`) for range-based `for` loops and basic STL algorithm compatibility (e.g. `std::accumulate`)
## Examples
 
### Construction and element access
```cpp
Vector<double> v(5);   // 5 elements, zero-initialized
v[0] = 1.0;
v[1] = 2.0;
 
std::cout << v[0];     // 1.0
```
 
### Bounds-checked access
```cpp
Vector<int> v(3);
v.at(0) = 10;
 
try {
    v.at(5) = 1;        // out of range
} catch (const std::out_of_range& e) {
    std::cout << e.what();
}
```
 
### Copying vs. moving
```cpp
Vector<double> a(3);
a[0] = 1.0; a[1] = 2.0; a[2] = 3.0;
 
Vector<double> b = a;              // copy constructor — deep copy, a is unchanged
Vector<double> c = std::move(a);   // move constructor — steals a's data, a is now empty
 
std::cout << a.size();             // 0
std::cout << b[0];                 // 1.0 (independent of c)
std::cout << c[0];                 // 1.0
```
 
### Elementwise addition
```cpp
Vector<int> a(3);
Vector<int> b(3);
a[0] = 1; a[1] = 2; a[2] = 3;
b[0] = 10; b[1] = 20; b[2] = 30;
 
Vector<int> sum = a + b;   // {11, 22, 33}
 
Vector<int> mismatched(5);
a + mismatched;            // throws std::invalid_argument
```
 
### Iterating
```cpp
Vector<double> v(4);
for (int i = 0; i < v.size(); ++i) v[i] = i * i;
 
for (auto x : v) {
    std::cout << x << " ";   // 0 1 4 9
}
 
double total = std::accumulate(v.begin(), v.end(), 0.0);
```
 
### Working with different types
```cpp
Vector<int> ints(3);
Vector<float> floats(3);
// Vector<T> works with any T supporting default construction and basic arithmetic
```

## Building

```bash
cmake -B build
cmake --build build
```

## Testing

Tests are written with [Catch2](https://github.com/catchorg/Catch2) (fetched automatically via CMake's `FetchContent`) and cover construction, zero-initialization, copy/move semantics (including self-assignment for both), `operator+`, and `.at()` bounds checking — using `TEMPLATE_TEST_CASE` to run each test across `int` and `float`.

```bash
cd tiny-vector
cmake -B build
cmake --build build
build/tests
```

The build is compiled with `-fsanitize=address` to catch memory errors (double-frees, use-after-free, out-of-bounds access) at the point they occur, rather than relying on tests happening to observe incorrect output.