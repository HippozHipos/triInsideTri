#define OLC_PGE_APPLICATION
//Link to pixel game engine header file
//https://github.com/OneLoneCoder/olcPixelGameEngine/blob/master/olcPixelGameEngine.h
#include "pixelGameEngine.h"
#include "triangleProcessor.h"

class TriInsideTri : public olc::PixelGameEngine
{
public:
	TriInsideTri(int sw, int sh) :
		sw(sw), sh(sh)
	{
		sAppName = "TriInsideTri";
	}
private:
	int sw;
	int sh;
	TriangleProcessor triangleProcessor{ sw, sh };

public:
	bool OnUserCreate() override
	{
		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		World::DragToChangeOffset(this);
		World::WSToChangeScale(this);
		triangleProcessor.Run(this);
		triangleProcessor.Render(this);
		return true;
	}
};

int main()
{
	int screenWidth = 600;
	int screenHeight = 600;
	int pixelSize = 1;
	TriInsideTri tritnsidetri{ screenWidth / pixelSize, screenHeight / pixelSize };
	if (tritnsidetri.Construct(screenWidth / pixelSize, screenHeight / pixelSize, 
		pixelSize, pixelSize))
	{
		tritnsidetri.Start();
	}
}