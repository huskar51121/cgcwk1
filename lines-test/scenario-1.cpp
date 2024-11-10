#include <catch2/catch_amalgamated.hpp>

#include <algorithm>

#include "helpers.hpp"

#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"
TEST_CASE("inf length", "[scenario-1]")
{
	Surface surface(100, 100);
	surface.clear();
	SECTION("right")
	{
		float a = 0.f;
		draw_line_solid(surface,
			{ 1.f / a, 1.f / a },
			{ 1.f / a, 1.f / a },
			{ 255, 255, 255 }
		);

	}
}
