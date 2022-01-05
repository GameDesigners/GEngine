#ifndef GOPENGL_RENDER_H
#define GOPENGL_RENDER_H
#include "GRender.h"
namespace GEngine {
	namespace GRender {
		class GRENDER_API GOpenGLRender : public GRender
		{
		public:
			GOpenGLRender(HINSTANCE hInstance, HWND hwnd, UINT width = DEFAULT_SCREEN_WIDTH, UINT height = DEFAULT_SCREEN_HEIGHT, bool bWindow = true);
		};
	}
}

#endif // !GOPENGL_RENDER_H


