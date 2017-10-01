#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "metta/str.h"

#include <cstring>

using metta::make_str;

SCENARIO("Concatenate compile-time strings", "[concat]") {
    GIVEN("Two simple metta::str") {
    WHEN("Try to concatenate") {
        constexpr auto LHS = make_str("Key: ");
    THEN("Should be able to compile-time concatenate") {
        constexpr auto RESULT = LHS + "Value";
    THEN("And check for concatenation result using compile-time comparison") {
        REQUIRE(RESULT == "Key: Value");
    THEN("And also check for concatenation result using strcmp runtime comparison") {
        REQUIRE(strcmp(RESULT.c_str(), "Key: Value") == 0);
    }}}}}
}
