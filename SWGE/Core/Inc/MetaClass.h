#pragma once
#include "MetaType.h"
#include "Debug.h"

namespace SWGE {
namespace Core {

class MetaField;

class MetaClass : public MetaType
{
public:
	MetaClass(const char* const name, 
		size_t size,
		MetaType::CreateFunc create,
		MetaType::DestroyFunc destroy,
		const MetaClass* const parent,
		const MetaField* const fields, 
		size_t numFields);

	const MetaClass* GetParent() const;
	const MetaField* FindField(const char* name) const;

private:
	const MetaClass* const mParent{nullptr};
	const MetaField* const mFields{nullptr};
	const size_t mNumFields{0};
	void Dump() const;

};

}
}