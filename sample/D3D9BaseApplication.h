#pragma once

#include "BaseApplicaton"
#include "GeometryBuffer"

#include <windows.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "Direct3DRenderer_d.lib")

struct BaseApplicationImpl;

class D3D9BaseApplication: public BaseApplication
{
public:
	D3D9BaseApplication();
	~D3D9BaseApplication();

	bool execute(Sample *sampleApp);
	void cleanup();

protected:
	bool initialiseDirect3D(unsigned int width, unsigned int height, unsigned int adapter, bool windowed);
	bool resetDirect3D();
	bool doFPSUpdate();
	bool overlayHandler(const CEGUI::EventArgs &args);

	BaseApplicationImpl *pimpl;
	DWORD d_lastFrameTime;
	int d_fps_frames;
	int d_fps_value;
	int d_fps_textbuff[16];
	CEGUI::GeometryBuffer *d_fps_geometry;
	CEGUI::GeometryBuffer *d_logo_geometry;
};