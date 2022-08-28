#include <catch2/catch_test_macros.hpp>
#include "chaintester.h"
#include "test.h"
#include "utils.h"

TEST_CASE( "test jsonobject", "[jsonobject]" ) {
    auto js = R""""(
    {
        "a": { "b": [1, 2, 3, 4, 5] }
    }
    )"""";

    auto o = JsonObject(js);

    REQUIRE(o.has_value("a", "b", 0));//, 0, "data", "s");
    REQUIRE(!o.has_value("a", "b", 5));//, 0, "data", "s");
    REQUIRE(o.get_uint64("a", "b", 0) == 1);//, 0, "data", "s");
    return;
}
