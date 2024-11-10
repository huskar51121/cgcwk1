#include <catch2/catch_amalgamated.hpp>

#include <algorithm>

#include "helpers.hpp"
#include <limits>
#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"
TEST_CASE("[!mayfail]", "[!mayfail]")
{
	Surface surface(100, 100);
	surface.clear();
	SECTION("inf_point")
	{
		float a = 0.f;
		draw_line_solid(surface,
			{ 1.f / a, 3 },
			{ 5, 3 },
			{ 255, 255, 255 }
		);
		auto const pixels = max_row_pixel_count(surface);
		REQUIRE(1 < pixels);
	}
}