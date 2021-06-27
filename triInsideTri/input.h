#pragma once
#include "pixelGameEngine.h"
#include <functional>

class Input
{
public:
	Input() = default;
	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;

public:
	static void OnDPress(olc::PixelGameEngine* pge, std::function<void()> DoIteration) noexcept
	{
		if (pge->GetKey(olc::D).bPressed)
		{
			DoIteration();
		}
	}

	static void OnAPress(olc::PixelGameEngine* pge, std::function<void()> UndoIteration) noexcept
	{
		if (pge->GetKey(olc::A).bPressed)
		{
			UndoIteration();
		}
	}
};

class WorldInput
{

public:
	WorldInput() = default;
	WorldInput(const WorldInput&) = delete;
	WorldInput& operator=(const WorldInput&) = delete;

private:
	static olc::vf2d startMousePan;

public:
	static void Drag(olc::PixelGameEngine* pge, olc::vf2d& offset, const float scale)
	{
		olc::vf2d mousePos = pge->GetMousePos();
		if (pge->GetMouse(0).bPressed)
		{
			startMousePan = mousePos;
		}
		if (pge->GetMouse(0).bHeld)
		{
			offset -= (mousePos - startMousePan) / scale;
			startMousePan = mousePos;
		}
	}

	static void Zoom(olc::PixelGameEngine* pge, float& scale)
	{	

		if (pge->GetKey(olc::W).bHeld)
		{
			scale *= 1.01f;
		}
		if (pge->GetKey(olc::S).bHeld)
		{
			scale *= 0.99f;
		}

		olc::vf2d afterZoom;
	}
};

olc::vf2d WorldInput::startMousePan{};