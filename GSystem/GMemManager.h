#ifndef GMEMMANAGER_H
#define GMEMMANAGER_H
#include <type_traits>  //引用了stl
#include <new>
#include "GSystem.h"
#include "GStackWalker.h"

namespace GEngine{
	namespace GSystem{

#pragma region 静态类型判断
        #define HAS_TRIVIAL_CONSTRUCTOR(T) std::is_trivially_constructible<T>::value
        #define HAS_TRIVIAL_DESTRUCTOR(T) std::is_trivially_destructible<T>::value
        #define IS_POD(T) std::is_pod<T>::value

	/**
	* TIsPODType
	*/
	template<typename T> struct TIsPODType
	{
		enum { Value = IS_POD(T) };
	};

	template<typename T> struct ValueBase
	{
	public:
		enum { NeedsConstructor = !HAS_TRIVIAL_CONSTRUCTOR(T) && !TIsPODType<T>::Value };
		enum { NeedsDestructor = !HAS_TRIVIAL_DESTRUCTOR(T) && !TIsPODType<T>::Value };
	};
#pragma endregion

		class GSYSTEM_API GMemManager
		{
		public:
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
			enum : unsigned int
			{
				MEM_BEGIN_MASK = 0xDEADC0DE,
				MEM_END_MASK = 0xDEADC0DE,
				RECORD_NUM = 64,
				CALLSTACK_NUM = 64
			};

			class Block
			{
			public:
				Block()
				{
					for (size_t i = 0; i < CALLSTACK_NUM; ++i)
						pCallStackRecords[i] = NULL;
					
					m_uiStackInfoNum = 0;
					m_uiMemSize = 0;
					m_bIsArray = false;
					m_bAlignment = false;

					m_pPrev = nullptr;
					m_pNext = nullptr;
				}

				DWORD64  pCallStackRecords[CALLSTACK_NUM];
				size_t   m_uiStackInfoNum;
				size_t   m_uiMemSize;
				bool     m_bIsArray;
				bool     m_bAlignment;

				Block* m_pPrev;
				Block* m_pNext;

			};

		public:
			void PrintMemCallAndReleaseLog();
		private:
			size_t m_uiNumNewCalls;                //New调用的次数
			size_t m_uiNumDeleteCalls;             //Delete调用的次数
			size_t m_uiNumCurrentBlocks;           //当前内存块的数量
			size_t m_uiNumBytes;                   //当前管理的内存大小（byte）
			size_t m_uiMaxNumBytesInRecord;        //分配过最大内存块的大小
			size_t m_uiMaxNumBlocksInRecord;       //内存块数量的峰值
			size_t m_uiSizeRecords[RECORD_NUM];    //内存块大小散列

			Block* m_pHeadBlock;
			Block* m_pTailBlock;
			GStackWalker m_sw;

			bool InsertBlock(Block* pBlock);
			bool RemoveBlock(Block* pBlock);
		};

		class GSYSTEM_API GMemObject
		{
		public:
			GMemObject() {}
			~GMemObject() {}

			static GMemManager& GetMemManager();
		};  

		//定义内存分配器函数类型
		typedef GMemManager& (*GMemManagerFun)();

	}
}

//重载内存分配运算符
FORCEINLINE void* operator new(size_t uiSize)
{
	return GEngine::GSystem::GMemObject::GetMemManager().Allocate((unsigned int)uiSize, 0, false);
}

FORCEINLINE void operator delete(void* pcAddr)
{
	return GEngine::GSystem::GMemObject::GetMemManager().Deallocate((char*)pcAddr, 0, false);
}

FORCEINLINE void* operator new[](size_t uiSize)
{
	return GEngine::GSystem::GMemObject::GetMemManager().Allocate((unsigned int)uiSize, 0, true);
}

FORCEINLINE void operator delete[](void* pcAddr)
{
	return GEngine::GSystem::GMemObject::GetMemManager().Deallocate((char*)pcAddr, 0, true);
}



#endif // !GMEMMANAGER_H
