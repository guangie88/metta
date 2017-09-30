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
    THEN("And check for concatenate result") {
        REQUIRE(strcmp(RESULT.data(), "Key: Value") == 0);
    }}}}
}
