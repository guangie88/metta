# metta
Compile-time string / char array with constexpr methods only.

[![Build Status](https://travis-ci.org/guangie88/metta.svg?branch=master)](https://travis-ci.org/guangie88/metta)
[![Build status](https://ci.appveyor.com/api/projects/status/6xjxiuwi62cj7bls/branch/master?svg=true)](https://ci.appveyor.com/project/guangie88/metta/branch/master)
[![codecov](https://codecov.io/gh/guangie88/metta/branch/master/graph/badge.svg)](https://codecov.io/gh/guangie88/metta)

## Motivation
Allows for named string reuse at different sites at compile-time, which could be useful for error messages with similar headings.

## How to build
```
mkdir build
cd build
cmake ..
cmake --build .
```

## How to run unit tests
Assumes that the unit tests have been compiled and linked.

```
cd build
./bin/unit_test
```

## Code examples
```c++
#include "metta/str.h"
#include <cstring>

int main() {
    using metta::make_str;

    constexpr auto LHS = make_str("Key: ");
    constexpr auto RESULT = LHS + "Value";
    constexpr auto ANOTHER_RESULT = LHS + "Another value";

    // below are comparisons that return true
    // RESULT == "Key: Value";
    // strcmp(ANOTHER_RESULT.c_str(), "Key: Another value") == 0;
}
```
