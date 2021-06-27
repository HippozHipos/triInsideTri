#pragma once
#include "pixelGameEngine.h"
#include "input.h"

class World
{
public:
	World() = default;
	World(const World&) = delete;
	World& operator=(const World&) = delete;

private:
	static olc::vf2d offset;
	static float scale;
	static WorldInput input;

public:
	static void SetOffset(const olc::vf2d& inoffset) noexcept
	{
		offset = inoffset;
	}

	static const olc::vf2d& GetOffset()  noexcept
	{
		return offset;
	}

	static void SetScale(const float inscale) noexcept
	{
		scale = inscale;
	}

	static const float& GetScale()  noexcept
	{
		return scale;
	}

public:
	static olc::vf2d ScreenToWorld(const olc::vf2d& v) noexcept
	{
		return (v / scale) + offset;
	}

	static olc::vf2d WorldToScreen(const olc::vf2d& v) noexcept
	{
		return (v - offset) * scale;
	}

	static void DragToChangeOffset(olc::PixelGameEngine* pge) noexcept
	{
		input.Drag(pge, offset, scale);
	}

	static void WSToChangeScale(olc::PixelGameEngine* pge) noexcept
	{
		olc::vf2d mousePos = pge->GetMousePos();
		olc::vf2d mouseBeforeZoom = ScreenToWorld(mousePos);

		input.Zoom(pge, scale);

		olc::vf2d mouseAfterZoom = ScreenToWorld(mousePos);

		offset += mouseBeforeZoom - mouseAfterZoom;
	}
};

WorldInput World::input{};
olc::vf2d World::offset = { 0.0f, 0.0f };
float World::scale = 1.0f;
