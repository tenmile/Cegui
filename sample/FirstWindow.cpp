#include "FirstWindow.h"

bool FirstWindow::initialiseSample()
{
	using namespace CEGUI;
	SchemeManager::getSingleton().create("TaharezLook.scheme");
	System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");

	WindowManager &winMgr = WindowManager::getSingleton();
	DefaultWindow *root = (DefaultWindow*)winMgr.createWindow("DefaultWindow", "Root");
	System::getSingleton().setGUISheet(root);
	FrameWindow *wnd = (FrameWindow*)winMgr.createWindow("TaharezLook/FrameWindow", "Demo Window");
	root->addChildWindow(wnd);
	wnd->setPosition(UVector2(cegui_reldim(0.25f), cegui_reldim(0.25f)));
	wnd->setSize(UVector2(cegui_reldim(0.5f), cegui_reldim(0.5f)));
	wnd->setMaxSize(UVector2(cegui_reldim(1.0f), cegui_reldim(1.0f)));
	wnd->setMinSize(UVector2(cegui_reldim(0.1f), cegui_reldim(0.1f)));
	wnd->setText("Hello World!");
	return true;
}

void FirstWindow::cleanupSample()
{

}