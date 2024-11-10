#include <catch2/catch_amalgamated.hpp>

#include "helpers.hpp"

#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"
#include "../draw2d/color.hpp"


TEST_CASE("some_point_is_inf", "[interp]")
{
#	if DRAW2D_CFG_SRGB_MODE != DRAW2D_CFG_SRGB_EXACT
#		error "These tests require SRGB_MODE == SRGB_EXACT"
#	endif

	Surface surface(16, 16);
	surface.clear();

	SECTION("one_inf")
	{
		float a = 0.f;
		draw_triangle_interp(surface,
			{ 1.f / a, 1.f / a }, { -1.f, 20.f }, { 20.f, 20.f },
			{ 0.5f, 0.5f, 0.5f },
			{ 0.5f, 0.5f, 0.5f },
			{ 0.5f, 0.5f, 0.5f }
		);

		auto const col = find_most_red_pixel(surface);
	}
}
