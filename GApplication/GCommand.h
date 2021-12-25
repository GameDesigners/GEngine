#ifndef GCOMMAND_H
#define GCOMMAND_H
#include "GAppMacr.h"

namespace GEngine {
	namespace GApp {
		class GAPPLICATION_API GCommand
		{
		public:
			GCommand();
			GCommand(PSTR pCmdLine);
			GCommand(int argc, char* argv[]);
			~GCommand();
		};
	}
}

#endif // !GCOMMAND_H



