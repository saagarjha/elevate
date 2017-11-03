# elevate

## What is elevate?
Elevate is a header-only C++ library designed to make working with C++ easier and more natural. It's designed for conciseness at the call site by providing sensible defaults for common use cases. Here's a few examples of it in use:

```cpp
// Sort an entire collection without needing std::begin or std::end.
int a[] = {3, 1, 2};
elvt::sort(a);

// Filter a collection.
std::vector<int> b = {1, 2, 3};
elvt::filter(b, elvt::is_prime<int>());

// Check your version of C++.
#if CXX_VERSION == CXX_11
std::cout << "Hello from C++11!" << std::endl;
#endif

// Cycle through a collection.
auto cycle = std::cycle(a, 6);
for (auto n : cycle) {
	std::cout << n << endl;
}

// Print a collection natively.
std::map<int, std::string> c = {{1, "a"}, {2, "b"}};
std::cout << c << std::endl;
```

While all of these things are possible with the standard library, it requires extra code that reduces readability. Elevate aims to handle this for you so you can focus on the bigger picture instead.

## Usage
You can use elevate like you would any other header library by downloading it and copying it to a directory on your include path. Elevate is written for C++11 and above.
COMING SOON: Use elevate on systems that don't have it by including it in your source files.
