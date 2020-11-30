#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
                          // in one cpp file
#include <catch2/catch.hpp>
#include "../src/utils/filenamehandler.h"


TEST_CASE("Clean data specifiers", "[specifier]")
{
    REQUIRE(cleanDateSpecifier("") == "%F_%H-%M");
    REQUIRE(cleanDateSpecifier("%F_%H-%M%") == "%F_%H-%M");
    REQUIRE(cleanDateSpecifier("%F_%H-%M%%%%") == "%F_%H-%M");
    REQUIRE(cleanDateSpecifier("%F_%H-%M") == "%F_%H-%M");
}