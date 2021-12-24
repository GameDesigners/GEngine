#ifndef GPRIORITY_H
#define GPRIORITY_H
#include <GVector.h>
#include "GGraphics.h"

namespace GEngine {
	namespace GGraphic {
		class GGRAPHIC_API GPriority
		{
		public:
			GPriority();
			GPriority(unsigned int priority);
			~GPriority();

			bool AddPriorityThan(GPriority* pPriority);
			unsigned int GetPriorityNum();

			GPriority& operator=(GPriority& rv);
			bool operator==(GPriority& rv);
			bool operator!=(GPriority& rv);
			bool operator>(GPriority& rv);
			bool operator<(GPriority& rv);
			bool operator>=(GPriority& rv);
			bool operator<=(GPriority& rv);
		private:
			bool __check_is_circle(const GPriority* pChecked) {
				if (pChecked == nullptr)
					return false;

				for (unsigned int index = 0; index < m_PriorityThanList.size(); index++)
				{
					if (pChecked == m_PriorityThanList[index])
						return true;
					else
						return m_PriorityThanList[index]->__check_is_circle(pChecked);
				}
				return false;
			}
			unsigned int __update_priority_num() 
			{
				if (m_uiPriorityNum == 0 || m_PriorityThanList.size() == 0)
					return m_uiPriorityNum;
				else
				{
					unsigned int uiMax = 0;
					for (unsigned int index = 0; index < m_PriorityThanList.size(); index++)
					{
						if (uiMax < m_PriorityThanList[index]->__update_priority_num())
							uiMax = m_PriorityThanList[index]->m_uiPriorityNum;
					}
					m_uiPriorityNum = uiMax + 1;
					return m_uiPriorityNum;
				}
			}

			unsigned int m_uiPriorityNum;
			GStl::GVector<GPriority*> m_PriorityThanList;
		};
	}
}
#endif // !GPRIORITY_H
