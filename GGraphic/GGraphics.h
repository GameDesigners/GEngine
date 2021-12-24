#ifndef GGRAPHIC_H
#define GGRAPHIC_H

#define GGRAPHIC_EXPORTS
#ifdef GGRAPHIC_EXPORTS
#define GGRAPHIC_API __declspec(dllexport) 
#else 
#define GGRAPHIC_API __declspec(dllimport) 
#endif

namespace GEngine {
	namespace GGraphic {
		class GGRAPHIC_API GGraphics
		{

		};
	}
}
#endif // !GGRAPHIC_H
