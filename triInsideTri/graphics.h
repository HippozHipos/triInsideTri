#pragma once
#include "pixelGameEngine.h"

class Gfx
{
public:
	Gfx() = default;
	Gfx(const Gfx&) = delete;
	Gfx& operator=(const Gfx&) = delete;

public:
	static void Clear(olc::PixelGameEngine* pge) noexcept
	{
		pge->Clear(olc::BLACK);
	}

	static void RenderTriangle(olc::PixelGameEngine* pge, const olc::vf2d& p1, const olc::vf2d& p2, 
		const olc::vf2d& p3, olc::Pixel c = olc::WHITE) noexcept
	{
		auto testInScreen = [pge](const olc::vf2d& point)
		{
			return (
				point.x > 0 && point.x < pge->ScreenWidth() ||
				point.y > 0 && point.y < pge->ScreenHeight()
				);
		};

		if (testInScreen(p1) || testInScreen(p2) || testInScreen(p3))
		{
			pge->DrawTriangle(p1, p2, p3, c);
		}
	}

	static void RenderNIterations(olc::PixelGameEngine* pge, const int nIterations) noexcept
	{
		pge->DrawString({ 10, 10 }, "Iterations: " + std::to_string(nIterations));
	}
};