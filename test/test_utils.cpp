#include "doctest.h"
#include <io/utils.h>

TEST_SUITE("Utils") {

	TEST_CASE("Split a simple string by space") {
		auto s = std::string("You'll never walk alone");
		auto sepbyspace = split(s, ' ');

		SUBCASE("size") {
			CHECK_EQ(sepbyspace.size(), 4);
		}

		SUBCASE("values") {
			CHECK_EQ(sepbyspace[0], "You'll");
			CHECK_EQ(sepbyspace[1], "never");
			CHECK_EQ(sepbyspace[2], "walk");
			CHECK_EQ(sepbyspace[3], "alone");
		}

	} // endof TEST_CASE(Split)

}
