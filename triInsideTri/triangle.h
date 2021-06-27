#pragma once
#include "pixelGameEngine.h"

class Triangle
{
public:
	Triangle() = default;
	Triangle(olc::vf2d p1, olc::vf2d p2, olc::vf2d p3):
		p1(p1), p2(p2), p3(p3)
	{
	}

private:
	static constexpr float oneFourth = 0.25f;
	static constexpr float half = 0.50f;
	static constexpr float threeFourth = 0.75f;

private:
	static olc::vf2d Lerp(const olc::vf2d& p1, const olc::vf2d& p2, const float alpha) noexcept
	{
		return p1 + (p2 - p1) * alpha;
	}

public:
	//Inner triangles for flat tops are generated differently
	//to flat bottoms.
	bool flatTop = false;

public:
	//First and last are not Used. Just for messing around
	//to make wierd triangles
	//static olc::vf2d First(const olc::vf2d& p1, const olc::vf2d& p2) noexcept
	//{
	//	return Lerp(p1, p2, oneFourth);
	//}

	static olc::vf2d Mid(const olc::vf2d& p1, const olc::vf2d& p2) noexcept
	{
		return Lerp(p1, p2, half);
	}

	//static olc::vf2d Last(const olc::vf2d& p2, const olc::vf2d& p1) noexcept
	//{
	//	return Lerp(p1, p2, threeFourth);
	//}

public:
	//left and right and the same for flat top and 
	//bottom. FbTop is flat bottom's top point and
	//Ftbottom is flat top's bottom point. 
	static olc::vf2d FbTop(olc::vf2d p1, olc::vf2d p2, olc::vf2d p3) noexcept
	{
		if (p1.y > p2.y) std::swap(p1, p2);
		if (p2.y > p3.y) std::swap(p2, p3);
		if (p1.y > p2.y) std::swap(p1, p2);
		return p1;
	}

	static olc::vf2d FtBottom(olc::vf2d p1, olc::vf2d p2, olc::vf2d p3) noexcept
	{
		if (p1.y < p2.y) std::swap(p1, p2);
		if (p2.y < p3.y) std::swap(p2, p3);
		if (p1.y < p2.y) std::swap(p1, p2);
		return p1;
	}

	static olc::vf2d Right(olc::vf2d p1, olc::vf2d p2, olc::vf2d p3) noexcept
	{
		if (p1.x > p2.x) std::swap(p1, p2);
		if (p2.x > p3.x) std::swap(p2, p3);
		if (p1.x > p2.x) std::swap(p1, p2);
		return p1;
	}

	static olc::vf2d Left(olc::vf2d p1, olc::vf2d p2, olc::vf2d p3) noexcept
	{
		if (p1.x < p2.x) std::swap(p1, p2);
		if (p2.x < p3.x) std::swap(p2, p3);
		if (p1.x < p2.x) std::swap(p1, p2);
		return p1;
	}

public:
	olc::vf2d p1{}, p2{}, p3{};
};
