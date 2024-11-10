#include "draw.hpp"

#include <algorithm>

#include <cmath>

#include "surface.hpp"
#include <iostream>
Vec2f get_cross_point(float k1, float k2, Vec2f aP1, Vec2f aP2)
{
	double b;
	double b1;
	if (std::isinf(k1)) {
		b = aP1.x;
	}
	else {
		b = aP1.y - k1 * aP1.x;
	}
	
	if (std::isinf(k2)) {
		b1 = aP2.x;
	}
	else {
		b1 = aP2.y - k2 * aP2.x;
	}

	float x;
	if (std::isinf(k1)) {
		x = b;
	}
	else if(std::isinf(k2)){
		x = b1;
	}
	else {
		x = (b1 - b) / (k1 - k2);
	}
	
	float y = k1 * x + b;
	/*printf("the cross is");*/
	return Vec2f{ x,y };
}

void draw_line_solid( Surface& aSurface, Vec2f aBegin, Vec2f aEnd, ColorU8_sRGB aColor )
{
	if (std::isinf(aBegin.x) || std::isinf(aBegin.y)) {
		//printf("somepoint is inf");
		return;
	}
	if (std::isinf(aEnd.x) || std::isinf(aEnd.y)) {
		//printf("somepoint is inf");
		return;
	}

	/*int dx = aEnd.x - aBegin.x;
	int dy = aEnd.y - aBegin.y;
	int steps = std::max(std::abs(dx), std::abs(dy));
	float xIncrement = float(dx) / float(steps);
	float yIncrement = float(dy) / float(steps);
	float x = aBegin.x;
	float y = aBegin.y;

	for (int k = 0; k < steps; k++) {
		x += xIncrement;
		y += yIncrement;
		if (!(round(x) < 0 || round(y) < 0 || round(x) >= aSurface.get_width() || round(y) >= aSurface.get_height())) {
			aSurface.set_pixel_srgb(round(x), round(y), aColor);
		}
	}*/

	int thesize = std::abs(aBegin.x - aEnd.x) + 1;
	float slope = (aEnd.y - aBegin.y) / (aEnd.x - aBegin.x);
	if (std::abs(slope)<1) {
		for (int i = 0; std::abs(i) < thesize;) {
			int the_y = floor(i * slope);
			if (!(i + aBegin.x < 0|| the_y + aBegin.y<0 ||i + aBegin.x >= aSurface.get_width() || the_y + aBegin.y >= aSurface.get_height())) {
				aSurface.set_pixel_srgb(i + aBegin.x, the_y + aBegin.y, aColor);
			}
			if (aBegin.x > aEnd.x) {
				i--;
			}
			else {
				i++;
			}
		}
	}
	else {
		for (int i = 0; std::abs(i) <= std::abs(aBegin.y - aEnd.y);) {
			int the_x = floor(i / slope);
			if (!(the_x + aBegin.x <0|| i + aBegin.y<0 ||the_x + aBegin.x >= aSurface.get_width() || i + aBegin.y >= aSurface.get_height())) {
				aSurface.set_pixel_srgb(the_x + aBegin.x, i + aBegin.y, aColor);
			}
			if (aBegin.y > aEnd.y) {
				i--;
			}
			else {
				i++;
			}
		}
	}
}

void draw_triangle_wireframe( Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorU8_sRGB aColor )
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

	//TODO: remove the following when you start your implementation
	(void)aSurface; // Avoid warnings about unused arguments until the function
	(void)aP0;   // is properly implemented.
	(void)aP1;
	(void)aP2;
	(void)aColor;
}
void draw_triangle_solid( Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorU8_sRGB aColor )
{
	if (std::isinf(aP0.x) || std::isinf(aP0.y) || std::isinf(aP1.x) || std::isinf(aP1.y) || std::isinf(aP2.x) || std::isinf(aP2.y)) {
		return;
	}
	if ((pow(aP2.x - aP0.x, 2) + pow(aP2.x - aP0.x, 2)) < (pow(aP1.x - aP0.x, 2) + pow(aP1.x - aP0.x, 2))) {
		Vec2f aP4 = aP2;
		aP2 = aP1;
		aP1 = aP4;
	}
	float slope12 = (aP2.y - aP1.y) / (aP2.x - aP1.x);
	float slope01 = (aP1.y - aP0.y) / (aP1.x - aP0.x);
	float slope02 = (aP2.y - aP0.y) / (aP2.x - aP0.x);
	
	if (std::abs(slope02) < 1) {
		for (int i = 0; std::abs(i) <= std::abs(aP0.x - aP2.x);) {
			int the_y = floor(i * slope02);
			Vec2f thispoint = Vec2f(i + aP0.x, the_y + aP0.y);
			Vec2f cross = get_cross_point(slope12, slope01, thispoint, aP0);
			if (std::isinf(cross.x) || std::isinf(cross.y)) {
				draw_line_solid(aSurface, aP0, aP1, aColor);
			}
			else {
				draw_line_solid(aSurface, thispoint, cross, aColor);
			}
			if (aP0.x > aP2.x) {
				i--;
			}
			else {
				i++;
			}
		}
	}
	else {
		for (int i = 0; std::abs(i) <= std::abs(aP0.y - aP2.y);) {
			
			int the_x = floor(i / slope02);
			Vec2f thispoint = Vec2f(the_x + aP0.x, i + aP0.y);
			Vec2f cross = get_cross_point(slope12, slope01, thispoint, aP0);
			if (std::isinf(cross.x) || std::isinf(cross.y)) {
				draw_line_solid(aSurface, aP0, aP1, aColor);
			}
			else {
				draw_line_solid(aSurface, thispoint, cross, aColor);
			}
			
			if (aP0.y > aP2.y) {
				i--;
			}
			else {
				i++;
			}
		}
	}
	draw_line_solid(aSurface, aP0, aP1, aColor);
	draw_line_solid(aSurface, aP2, aP1, aColor);
	draw_line_solid(aSurface, aP0, aP2, aColor);
}
std::uint8_t floatToUint8(float value) {
	int roundedValue = static_cast<int>(value * 256 + 0.5);
	if (roundedValue < 0) {
		return 0;
	}
	else if (roundedValue > 255) {
		return 255;
	}
	else {
		return static_cast<std::uint8_t>(roundedValue);
	}
}
void draw_point_with_color(Surface& aSurface, Vec2f thepoint, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorF aC0, ColorF aC1, ColorF aC2){
	float x = thepoint.x;
	float y = thepoint.y;
	float xa = aP0.x;
	float ya = aP0.y;
	float xb = aP1.x;
	float yb = aP1.y;
	float xc = aP2.x;
	float yc = aP2.y;
	float power0 = ((-(x - xb) * (yc - yb)) + ((y - yb) * (xc - xb))) / ((-(xa - xb) * (yc - yb)) + ((ya - yb) * (xc - xb)));
	float power1 = ((-(x - xc) * (ya - yc)) + ((y - yc) * (xa - xc))) / ((-(xb - xc) * (ya - yc)) + ((yb - yc) * (xa - xc)));
	float power2 = (1 - power1) - power0;
	/*printf("%f  %f  %f\n", power0, power1, power2);*/
	float r = power0 * aC0.r + power1 * aC1.r + power2 * aC2.r;
	float g = power0 * aC0.g + power1 * aC1.g + power2 * aC2.g;
	float b = power0 * aC0.b + power1 * aC1.b + power2 * aC2.b;
	std::uint8_t ther = floatToUint8(r);
	std::uint8_t theg = floatToUint8(g);
	std::uint8_t theb = floatToUint8(b);
	ColorU8_sRGB thecolor = ColorU8_sRGB{ ther,theg,theb };
	aSurface.set_pixel_srgb(thepoint.x,thepoint.y,thecolor);
}
void draw_line_with_color(Surface& aSurface, Vec2f aBegin, Vec2f aEnd, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorF aC0, ColorF aC1, ColorF aC2) {
	if(std::isinf(aEnd.y) || std::isinf(aEnd.x)){
		//printf("cross is inf");
		return;
	}
	int thesize = std::abs(aBegin.x - aEnd.x) + 1;
	float slope = (aEnd.y - aBegin.y) / (aEnd.x - aBegin.x);
	if (std::abs(slope) < 1) {
		//printf("draw begin start with %f,%f and end at %f,%f\n", aBegin.x,aBegin.y,aEnd.x, aEnd.y);
		for (int i = 0; std::abs(i) < thesize;) {
			int the_y1 = floor(i * slope);
			int the_y2 = floor(i * slope) + 1;
			if (!(i + aBegin.x < 0 || the_y1 + aBegin.y < 0 || i + aBegin.x >= aSurface.get_width() || the_y1 + aBegin.y >= aSurface.get_height())) {
				Vec2f thepoint = Vec2f{ i + aBegin.x, the_y1 + aBegin.y };
				draw_point_with_color(aSurface, thepoint, aP0, aP1, aP2, aC0, aC1, aC2);
			}
			if (!(i + aBegin.x < 0 || the_y2 + aBegin.y < 0 || i + aBegin.x >= aSurface.get_width() || the_y2 + aBegin.y >= aSurface.get_height())) {
				Vec2f thepoint = Vec2f{ i + aBegin.x, the_y2 + aBegin.y };
				draw_point_with_color(aSurface, thepoint, aP0, aP1, aP2, aC0, aC1, aC2);
			}
			if (aBegin.x > aEnd.x) {
				i--;
			}
			else {
				i++;
			}
		}
	}
	else {
		//printf("draw begin start with %f and end at %f", aBegin.x, aEnd.x);
		for (int i = 0; std::abs(i) < std::abs(aBegin.y - aEnd.y);) {
			int the_x1 = floor(i / slope);
			int the_x2 = floor(i / slope) + 1;
			if (!(the_x1 + aBegin.x <= 0 || i + aBegin.y <= 0 || the_x1 + aBegin.x >= aSurface.get_width() || i + aBegin.y >= aSurface.get_height())) {
				Vec2f thepoint = Vec2f{ the_x1 + aBegin.x, i + aBegin.y };
				draw_point_with_color(aSurface, thepoint, aP0, aP1, aP2, aC0, aC1, aC2);
			}
			if (!(the_x2 + aBegin.x <= 0 || i + aBegin.y <= 0 || the_x2 + aBegin.x >= aSurface.get_width() || i + aBegin.y >= aSurface.get_height())) {
				Vec2f thepoint = Vec2f{ the_x2 + aBegin.x, i + aBegin.y };
				draw_point_with_color(aSurface, thepoint, aP0, aP1, aP2, aC0, aC1, aC2);
			}
			if (aBegin.y > aEnd.y) {
				i--;
			}
			else {
				i++;
			}
		}
	}
}
void draw_triangle_interp( Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorF aC0, ColorF aC1, ColorF aC2 )
{
	if (std::isinf(aP0.x) || std::isinf(aP0.y) || std::isinf(aP1.x) || std::isinf(aP1.y) || std::isinf(aP2.x) || std::isinf(aP2.y)) {
		return;
	}
	/*printf("aP0 is %f and %f\n", aP0.x, aP0.y);
	printf("aP1 is %f and %f\n", aP1.x, aP1.y);
	printf("aP2 is %f and %f\n", aP2.x, aP2.y);*/
	if ((pow(aP2.x - aP0.x, 2) + pow(aP2.x - aP0.x, 2)) < (pow(aP1.x - aP0.x, 2) + pow(aP1.x - aP0.x, 2))) {
		Vec2f aP4 = {aP2.x,aP2.y};
		aP2 = { aP1.x, aP1.y };
		aP1 = { aP4.x, aP4.y};
		ColorF aC4 = aC2;
		aC2 = aC1;
		aC1 = aC4;
	}
	/*printf("aP0 is %f and %f\n", aP0.x, aP0.y);
	printf("aP1 is %f and %f\n", aP1.x, aP1.y);
	printf("aP2 is %f and %f\n", aP2.x, aP2.y);*/
	float slope12 = (aP2.y - aP1.y) / (aP2.x - aP1.x);
	float slope01 = (aP1.y - aP0.y) / (aP1.x - aP0.x);
	float slope02 = (aP2.y - aP0.y) / (aP2.x - aP0.x);
	
	if (std::abs(slope02) < 1) {
		for (int i = 0; std::abs(i) <= std::abs(aP0.x - aP2.x);) {
			int the_y = floor(i * slope02);
			Vec2f thispoint = Vec2f(i + aP0.x, the_y + aP0.y);
			Vec2f cross = get_cross_point(slope12, slope01, thispoint, aP0);
			if (std::isinf(cross.x) || std::isinf(cross.y)) {
				draw_line_with_color(aSurface, aP0, aP1, aP0, aP1, aP2, aC0, aC1, aC2);
			}
			else {
				draw_line_with_color(aSurface, thispoint, cross, aP0, aP1, aP2, aC0, aC1, aC2);
			}
			if (aP0.x > aP2.x) {
				i--;
			}
			else {
				i++;
			}
		}
	}
	else {
		for (int i = 0; std::abs(i) <= std::abs(aP0.y - aP2.y);) {
			int the_x = floor(i / slope02);
			Vec2f thispoint = Vec2f(the_x + aP0.x, i + aP0.y);
			Vec2f cross = get_cross_point(slope12, slope01, thispoint, aP0);
			if (std::isinf(cross.x) || std::isinf(cross.y)) {
				draw_line_with_color(aSurface, aP0, aP1, aP0, aP1, aP2, aC0, aC1, aC2);
			}
			else {
				draw_line_with_color(aSurface, thispoint, cross, aP0, aP1, aP2, aC0, aC1, aC2);
			}
			if (aP0.y > aP2.y) {
				i--;
			}
			else {
				i++;
			}
		}
	}
	draw_line_with_color(aSurface, aP0, aP1, aP0, aP1, aP2, aC0, aC1, aC2);
	draw_line_with_color(aSurface, aP1, aP2, aP0, aP1, aP2, aC0, aC1, aC2);
	draw_line_with_color(aSurface, aP0, aP2, aP0, aP1, aP2, aC0, aC1, aC2);
}


void draw_rectangle_solid( Surface& aSurface, Vec2f aMinCorner, Vec2f aMaxCorner, ColorU8_sRGB aColor )
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

	//TODO: remove the following when you start your implementation
	(void)aSurface; // Avoid warnings about unused arguments until the function
	(void)aMinCorner;   // is properly implemented.
	(void)aMaxCorner;
	(void)aColor;
}

void draw_rectangle_outline( Surface& aSurface, Vec2f aMinCorner, Vec2f aMaxCorner, ColorU8_sRGB aColor )
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

	//TODO: remove the following when you start your implementation
	(void)aSurface; // Avoid warnings about unused arguments
	(void)aMinCorner;
	(void)aMaxCorner;
	(void)aColor;
}


