#include <catch2/catch_amalgamated.hpp>

#include <algorithm>

#include "helpers.hpp"

#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"


TEST_CASE("point_off_surface", "[scenario-2]")
{
	Surface surface(100, 100);
	surface.clear();

	// This has a few simple cases.

	SECTION("left_right")
	{
		draw_line_solid(surface,
			{ -100.f, 5.f },
			{ 200.f, 5.f },
			{ 255, 255, 255 }
		);

		auto const pixels = max_row_pixel_count(surface);
		REQUIRE((99 == pixels || 100 == pixels));
	}

	SECTION("above_and_below")
	{
		draw_line_solid(surface,
			{ 5.f, -100.f },
			{ 5.f, 200.f },
			{ 255, 255, 255 }
		);

		auto const pixels = max_col_pixel_count(surface);
		REQUIRE((99 == pixels || 100 == pixels));
	}
	// Not tested: with slope, etc.
}
