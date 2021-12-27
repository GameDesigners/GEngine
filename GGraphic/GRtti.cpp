#include "GRtti.h"

GEngine::GGraphic::GRtti::GRtti(const TCHAR* _className, GRtti* _parent, FactoryFunction* cof)
{
	m_className = _className;
	m_pParent = _parent;
	__cof = cof;
}

GEngine::GGraphic::GRtti::~GRtti() {}

bool GEngine::GGraphic::GRtti::operator==(const GRtti& rhs) const
{
	return &rhs == this;
}

bool GEngine::GGraphic::GRtti::operator!=(const GRtti& rhs) const
{
	return &rhs != this;
}

bool GEngine::GGraphic::GRtti::IsSampleType(const GRtti& rhs) const
{
	return &rhs == this;
}

bool GEngine::GGraphic::GRtti::IsDerived(const GRtti& rhs) const
{
	const GRtti* pTemp = this;
	while (pTemp != nullptr)
	{
		if (pTemp != &rhs)
			pTemp = pTemp->m_pParent;
		else
			return true;
	}
	return false;
}

const GEngine::GStl::GTString& GEngine::GGraphic::GRtti::Name() const
{
	return m_className;
}

void GEngine::GGraphic::GRtti::InitialGenerateFun(FactoryFunction* cof)
{
	__cof = cof;
}
