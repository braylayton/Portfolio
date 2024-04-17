#include "Precompiled.h"
//#include "Utility.h"
//
//
//using namespace SWGE;
//using namespace Util;
//
//
//
//bool XMLReader::Read(void* instance, const Core::MetaClass* metaClass, const tinyxml2::XMLNode* node)
//{
//	/*while (node != nullptr)
//	{
//		const tinyxml2::XMLElement* element = node->ToElement();
//		if (element != nullptr)
//		{
//			const char* fieldName = element->Attribute("name");
//			const Core::MetaField* metaField = metaClass->FindField(fieldName);
//			if (metaField != nullptr)
//			{
//				void* member = (uint8_t*)instance + metaField->GetOffset();
//				bool success = XMLReader::Read(member, metaField->GetMetaType(), element->FirstChild());
//				if (!success)
//				{
//					return false;
//				}
//			}
//		}
//		node = node->NextSibling();
//	}*/
//
//	return true;
//}
//
//bool XMLReader::Read(void* instance, const Core::MetaType* metaType, const tinyxml2::XMLNode* node)
//{
//	if (node == nullptr)
//	{
//		return false;
//	}
//
//	switch (metaType->GetCategory())
//	{
//		case Core::MetaType::Category::Primitive:
//		{
//			return ReadPrimitive(instance, metaType, node);
//		}
//		case Core::MetaType::Category::Class:
//		{
//			return XMLReader::Read(instance, (const Core::MetaClass*)metaType, node);
//		}
//
//		// add support for Array and Pointer
//
//		return false;
//	}
//}
//
//bool XMLReader::ReadPrimitive(void* instance, const Core::MetaType* metaType, const tinyxml2::XMLNode* node)
//{
//	if (node != nullptr)
//	{
//		const char* value;
//		value = node->Value();
//		
//		if (value != nullptr)
//		{
//			const char* typeName = metaType->GetName();
//			if (typeName == "String")
//			{
//				memcpy(instance, &value, sizeof(value));
//				return true;
//			}
//			if (typeName == "Int")
//			{
//				int tempInt = atoi(value);
//				memcpy(instance, &tempInt, sizeof(bool));
//		
//				return true;
//			}
//			if (typeName == "Float")
//			{
//				float tempFloat = static_cast<float>(atof(value));
//				memcpy(instance, &tempFloat, sizeof(bool));
//				return true;
//			}
//			if (typeName == "bool")
//			{
//				bool state;
//				if (value == "True" || value == "T" || value == "t")
//				{
//					state = true;
//					memcpy(instance, &state, sizeof(bool));
//				}
//				else
//				{
//					state = false;
//					memcpy(instance, &state , sizeof(bool));
//				}
//				
//				return true;
//			}
//			
//			
//			
//			
//
//		}
//	
//	}
//}
