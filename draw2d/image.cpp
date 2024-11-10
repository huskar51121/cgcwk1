#include "image.hpp"

#include <memory>
#include <algorithm>

#include <cstdio>
#include <cstring>
#include <cassert>

#include <stb_image.h>

#include "surface.hpp"

#include "../support/error.hpp"

namespace
{
	struct STBImageRGBA_ : public ImageRGBA
	{
		STBImageRGBA_( Index, Index, std::uint8_t* );
		virtual ~STBImageRGBA_();
	};
}

ImageRGBA::ImageRGBA()
	: mWidth( 0 )
	, mHeight( 0 )
	, mData( nullptr )
{}

ImageRGBA::~ImageRGBA() = default;


std::unique_ptr<ImageRGBA> load_image( char const* aPath )
{
	assert( aPath );

	stbi_set_flip_vertically_on_load( true );

	int w, h, channels;
	stbi_uc* ptr = stbi_load( aPath, &w, &h, &channels, 4 );
	if( !ptr )
		throw Error( "Unable to load image \"%s\"", aPath );

	return std::make_unique<STBImageRGBA_>(
		ImageRGBA::Index(w),
		ImageRGBA::Index(h),
		ptr
	);
}

void blit_masked( Surface& aSurface, ImageRGBA const& aImage, Vec2f aPosition )
{
	if (aPosition.x > aSurface.get_width() || aPosition.x + aImage.get_width() < 0) {
		return;
	}
	if (aPosition.y > aSurface.get_height() || aPosition.y + aImage.get_height() < 0) {
		return;
	}
	for (int i = 0; i < aImage.get_height();i++) {
		for (int j = 0; j < aImage.get_width(); j++) {
			ColorU8_sRGB_Alpha color = aImage.get_pixel(j, i);
			if (color.a >= 128) {
				ColorU8_sRGB acolor = ColorU8_sRGB{ color.r,color.g,color.b };
				Surface::Index aX = j + aPosition.x;
				Surface::Index aY = i + aPosition.y;
				if (!(aX < 0 || aY < 0 || aX >= aSurface.get_width() || aY >= aSurface.get_height())) {
					aSurface.set_pixel_srgb(aX, aY, acolor);
				}
			}

			/*ColorU8_sRGB acolor = ColorU8_sRGB{ color.r,color.g,color.b };
			Surface::Index aX = j + aPosition.x;
			Surface::Index aY = i + aPosition.y;
			if (!(aX < 0 || aY < 0 || aX >= aSurface.get_width() || aY >= aSurface.get_height())) {
				aSurface.set_pixel_srgb(aX, aY, acolor);
			}*/
		}
	}

	/*for (int i = 0; i < aImage.get_height(); i++) {
		Surface::Index aX = aPosition.x;
		Surface::Index aY = i + aPosition.y;
		Surface::Index length = std::min(aSurface.get_width() - aX, aImage.get_width());
		ImageRGBA::Index src = aImage.get_linear_index(0, i);
		const std::uint8_t* ptr_src = aImage.get_image_ptr();
		Surface::Index dest = aSurface.get_linear_index(aX, aY);
		const std::uint8_t* ptr_dest = aSurface.get_surface_ptr();
		if (!(aX <= 0 || aY <= 0 || length <= 0 || aY >= aSurface.get_height())) {
			std::memcpy(const_cast<std::uint8_t*>(ptr_dest) + dest, ptr_src + src, length*4);
		}
	}*/
}

namespace
{
	STBImageRGBA_::STBImageRGBA_( Index aWidth, Index aHeight, std::uint8_t* aPtr )
	{
		mWidth = aWidth;
		mHeight = aHeight;
		mData = aPtr;
	}

	STBImageRGBA_::~STBImageRGBA_()
	{
		if( mData )
			stbi_image_free( mData );
	}
}
