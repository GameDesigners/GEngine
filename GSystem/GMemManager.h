#ifndef GMEMMANAGER_H
#define GMEMMANAGER_H
#include "GSystem.h"

namespace GEngine
{
	namespace GSystem
	{
		class GSYSTEM_API GMemManager
		{
		protected:
			virtual void* Allocate(size_t uiSize, size_t uiAlignment, bool bIsArray) = 0;
			virtual void Deallocate(char* pcAddr, unsigned int uiAlignment, bool bIsArray) = 0;
		};

		class GSYSTEM_API GDebugMem : public GMemManager 
		{
		public:
			GDebugMem();
			~GDebugMem();
			virtual void* Allocate(size_t uiSize, size_t uiAlignment, bool bIsArray);
			virtual void Deallocate(char* pcAddr, unsigned int uiAlignment, bool bIsArray);

		private:
			enum
			{
				MEM_BEGIN_MASK = 0xDEADC0DE,
				MEM_END_MASK = 0xDEADC0DE,
				RECORD_NUM = 32,
				CALLSTACK_NUM = 32
			};

			class Block
			{
			public:
				Block()
				{
					for (size_t i = 0; i < CALLSTACK_NUM; ++i)
						pCallStackRecords[i] = nullptr;
					
					m_uiStackInfoNum = 0;
					m_uiMemSize = 0;
					m_bIsArray = false;
					m_bAlignment = false;

					m_pPrev = nullptr;
					m_pNext = nullptr;
				}

				void*  pCallStackRecords[CALLSTACK_NUM];
				size_t m_uiStackInfoNum;
				size_t m_uiMemSize;
				bool   m_bIsArray;
				bool   m_bAlignment;

				Block* m_pPrev;
				Block* m_pNext;

			};

			bool LoadDbgHelpLibrary();
			bool UninstallDbgHelpLibrary();
			static BOOL MyReadProcMem(HANDLE hProcess, DWORD64 qwBaseAddress, PVOID lpBuffer, DWORD nSize, LPDWORD lpNumberOfBytesRead);
		public:
			void PrintMemCallAndReleaseLog();
		private:
			size_t m_uiNumNewCalls;
			size_t m_uiNumDeleteCalls;
			size_t m_uiNumCurrentBlocks;
			size_t m_uiNumBytes;
			size_t m_uiMaxNumBytesInRecord;
			size_t m_uiMaxNumBlocksInRecord;
			size_t m_uiSizeRecords[RECORD_NUM];

			Block* m_pHeadBlock;
			Block* m_pTailBlock;
			bool InsertBlock(Block* pBlock);
			bool RemoveBlock(Block* pBlock);
		};

	}
}



#endif // !GMEMMANAGER_H
