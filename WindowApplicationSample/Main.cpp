#include <GWindowApplication.h>
#include <DirectXMath.h>
using namespace GEngine::GApp;
using namespace DirectX;



class CustomWindowApplication : public GWindowApplication
{
	DECLARE_WINDOW_APPLICATION(CustomWindowApplication)

	virtual bool OnDraw();
	virtual void OnKeyDown(KeyCode uiKey);
	/*virtual void OnKeyUp(KeyCode uiKey);
	virtual void OnLButtonDown(int xPos, int yPos);
	virtual void OnLButtonUp(int xPos, int yPos);
	virtual void OnRButtonDown(int xPos, int yPos);
	virtual void OnRButtonUp(int xPos, int yPos);
	virtual void OnMButtonDown(int xPos, int yPos);
	virtual void OnMButtonUp(int xPos, int yPos);
	virtual void OnMouseMove(int xPos, int yPos);
	virtual void OnMouseWheel(int xPos, int yPos, int zDet);*/
};

REGIST_WINDOW_APPLICATION(CustomWindowApplication, L"GENGINE")

bool CustomWindowApplication::OnDraw()
{
	return false;
}

void CustomWindowApplication::OnKeyDown(KeyCode uiKey)
{
	if (uiKey == KeyCode::A)
	{
		MessageBox(m_hwnd, L"Hello GEngine.", L"Hello", MB_OK);
	}
}
