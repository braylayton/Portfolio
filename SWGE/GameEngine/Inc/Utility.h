#pragma once

namespace Util
{
	class XMLReader
	{
	public:
		static bool Read(void* instance, const SWGE::Core::MetaClass* metaClass, const tinyxml2::XMLNode* node);
		static bool Read(void* instance, const SWGE::Core::MetaType* metaType, const tinyxml2::XMLNode* node);
		static bool ReadPrimitive(void* instance, const SWGE::Core::MetaType* metaType, const tinyxml2::XMLNode* node);
	};
}

