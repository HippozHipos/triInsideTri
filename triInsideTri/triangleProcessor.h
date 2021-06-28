#pragma once
#include <functional>
#include "pixelGameEngine.h"
#include "triangle.h"
#include "graphics.h"
#include "input.h"
#include "world.h"

class TriangleProcessor
{
public:
	TriangleProcessor(const int sw, const int sh)
	{
		//Initialize the vector with the first triangle
		vvTris.push_back
		(//vvtris
			{ //vtris
				{ //triangle
					{sw * 0.5f, 0.0f}, //olc::vf2d
					{0.0f, sh * 1.0f}, //olc::vf2d
					{sw * 1.0f, sh * 1.0f} //olc::vf2d
				}
			}
		);
	}
	TriangleProcessor(const TriangleProcessor&) = delete;
	TriangleProcessor& operator=(const TriangleProcessor&) = delete;

private:
	using vTris = std::vector<Triangle>;
	std::vector<vTris> vvTris;
	Gfx gfx{};
	Input input{};

private:
	void GenerateMiddleTriangle(const Triangle& tri, vTris& newVTris) noexcept
	{
		Triangle midTri =
		{
			Triangle::Mid(tri.p1, tri.p2),
			Triangle::Mid(tri.p2, tri.p3),
			Triangle::Mid(tri.p3, tri.p1)
		};

		midTri.flatTop = true;
		newVTris.push_back(midTri);
	}

	void GenerateFlatBottoms(const Triangle& tri, vTris& newVTris) noexcept
	{
		Triangle topTri =
		{
			Triangle::FbTop(tri.p1, tri.p2, tri.p3),
			Triangle::Mid
			(
				Triangle::FbTop(tri.p1, tri.p2, tri.p3), Triangle::Left(tri.p1, tri.p2, tri.p3)
			),
			Triangle::Mid
			(
				Triangle::FbTop(tri.p1, tri.p2, tri.p3), Triangle::Right(tri.p1, tri.p2, tri.p3)
			),
		};

		Triangle bottomLeftTri =
		{
			Triangle::Mid
			(
				Triangle::FbTop(tri.p1, tri.p2, tri.p3), Triangle::Left(tri.p1, tri.p2, tri.p3)
			),
			Triangle::Left(tri.p1, tri.p2, tri.p3),
			Triangle::Mid
			(
				Triangle::Right(tri.p1, tri.p2, tri.p3), Triangle::Left(tri.p1, tri.p2, tri.p3)
			),
		};

		Triangle bottomRightTri =
		{
			Triangle::Mid
			(
				Triangle::FbTop(tri.p1, tri.p2, tri.p3), Triangle::Right(tri.p1, tri.p2, tri.p3)
			),
			Triangle::Right(tri.p1, tri.p2, tri.p3),
			Triangle::Mid
			(
				Triangle::Right(tri.p1, tri.p2, tri.p3), Triangle::Left(tri.p1, tri.p2, tri.p3)
			),
		};

		newVTris.push_back(topTri);
		newVTris.push_back(bottomLeftTri);
		newVTris.push_back(bottomRightTri);
	}

	void GenerateFlatTops(const Triangle& tri, vTris& newVTris) noexcept
	{
		
		Triangle topLeftTri =
		{
			Triangle::Left(tri.p1, tri.p2, tri.p3),
			Triangle::Mid
			(
				Triangle::Left(tri.p1, tri.p2, tri.p3), Triangle::FtBottom(tri.p1, tri.p2,tri.p3)
			),
			Triangle::Mid
			(
				Triangle::Left(tri.p1, tri.p2, tri.p3), Triangle::Right(tri.p1, tri.p2,tri.p3)
			),
		};

		Triangle topRightTri =
		{
			Triangle::Right(tri.p1, tri.p2, tri.p3),
			Triangle::Mid
			(
				Triangle::Right(tri.p1, tri.p2, tri.p3), Triangle::FtBottom(tri.p1, tri.p2,tri.p3)
			),
			Triangle::Mid
			(
				Triangle::Left(tri.p1, tri.p2, tri.p3), Triangle::Right(tri.p1, tri.p2,tri.p3)
			),
		};

		Triangle bottomTri =
		{
			Triangle::FtBottom(tri.p1, tri.p2, tri.p3),
			Triangle::Mid
			(
				Triangle::Right(tri.p1, tri.p2, tri.p3), Triangle::FtBottom(tri.p1, tri.p2,tri.p3)
			),
			Triangle::Mid
			(
				Triangle::Left(tri.p1, tri.p2, tri.p3), Triangle::FtBottom(tri.p1, tri.p2,tri.p3)
			),
		};

		newVTris.push_back(topLeftTri);
		newVTris.push_back(topRightTri);
		newVTris.push_back(bottomTri);
	}

public:
	int GetCurrentIteration() const noexcept
	{
		return (int)vvTris.size() - 1;
	}

	const std::vector<vTris>& GetConstvvTris() const noexcept
	{
		return vvTris;
	}

	std::vector<vTris>& GetvvTris() noexcept
	{
		return vvTris;
	}

	void DoIteration() noexcept
	{
		//retrieve the last vector of triangles
		vTris vtris = vvTris.back(); 

		//holds the triangles generated in this 
		//iteration
		vTris newVTris{};

		//iterate through all the triangles in that vector 
		//and create new vector of inner triangles. Then
		//add that vector to vvTris.
		for (auto& tri : vtris)
		{
			//Each triangle generates four unqiue inner triangle
			GenerateMiddleTriangle(tri, newVTris);
			GenerateFlatTops(tri, newVTris);
			GenerateFlatBottoms(tri, newVTris);
		}

		//Add the vector that contains the triangles form this
		//iteration to vvTris.
		vvTris.push_back(newVTris);
	}
	
	void UndoIteration() noexcept
	{
		//Dont want to be able to remove the first
		//triangle
		if (vvTris.size() > 1)
		{
			vvTris.pop_back();
		}
	}

	void Run(olc::PixelGameEngine* pge) noexcept
	{
		Input::OnDPress(pge, [this]() { this->DoIteration(); });
		Input::OnAPress(pge, [this]() { this->UndoIteration(); });
	}

	void Render(olc::PixelGameEngine* pge) noexcept
	{
		Gfx::Clear(pge);


		//Draw only the last iteration of the triangles + all
		//the flat tops
		for (auto& tri : vvTris.back())
		{
			Gfx::RenderTriangle(pge,
				World::WorldToScreen(tri.p1),
				World::WorldToScreen(tri.p2),
				World::WorldToScreen(tri.p3)
			);
		}

		for (auto& vtris : vvTris)
			for (auto& tri : vtris)
			{
				if (tri.flatTop)
				{
					Gfx::RenderTriangle(pge,
						World::WorldToScreen(tri.p1),
						World::WorldToScreen(tri.p2),
						World::WorldToScreen(tri.p3)
					);
				}
			}

		Gfx::RenderNIterations(pge, (const int)GetCurrentIteration());
	}
};