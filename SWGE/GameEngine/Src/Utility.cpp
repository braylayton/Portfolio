//#include "Precompiled.h"
//#include "Utility.h"
//
//using namespace Util;
//
//bool XMLReader::Read(void* instance, const SWGE::Core::MetaClass* metaClass, const tinyxml2::XMLNode* node)
//{
//	while (node != nullptr)
//	{
//		const tinyxml2::XMLElement* element = node->ToElement();
//		if (element != nullptr)
//		{
//			const char* fieldName = element->Attribute("name");
//			const SWGE::Core::MetaField* metaField = metaClass->FindField(fieldName);
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
//	}
//
//	return true;
//}
//
//bool XMLReader::Read(void* instance, const SWGE::Core::MetaType* metaType, const tinyxml2::XMLNode* node)
//{
//	if (node == nullptr)
//	{
//		return false;
//	}
//
//	switch (metaType->GetCategory())
//	{
//		case SWGE::Core::MetaType::Category::Primitive:
//		{
//			return ReadPrimitive(instance, metaType, node);
//		}
//		case SWGE::Core::MetaType::Category::Class:
//		{
//			return XMLReader::Read(instance, (const SWGE::Core::MetaClass*)metaType, node);
//		}
//		return false;
//	}
//}
//
//bool XMLReader::ReadPrimitive(void* instance, const SWGE::Core::MetaType* metaType, const tinyxml2::XMLNode* node)
//{
//	if (node != nullptr)
//	{
//		const char* value;
//		value = node->FirstChild()->Value();
//		
//		if (value != nullptr)
//		{
//			const char* typeName = metaType->GetName();
//			if (typeName == "String")
//			{
//				std::string* var = (std::string*)instance;
//				*var = value;
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
//			if (typeName == "Vector2")											
//			{																	
//				const tinyxml2::XMLNode* node1 = node->FirstChild();			
//				VERIFY(node1 != nullptr, "[XMLRead] node is Nullptr.");			
//				const tinyxml2::XMLNode* node2 = node->NextSibling();			
//				VERIFY(node2 != nullptr, "[XMLRead] node is Nullptr.");			
//									
//				float vecX = static_cast<float>(atof(node1->Value()));
//				float vecY = static_cast<float>(atof(node2->Value()));
//				SWGE::Math::Vector2* vec2 = reinterpret_cast<SWGE::Math::Vector2*>(instance);
//				vec2->x = vecX;
//				vec2->y = vecY;
//				 																
//			}
//			if (typeName == "Vector3")
//			{
//				const tinyxml2::XMLNode* node1 = node->FirstChild();
//				VERIFY(node1 != nullptr, "[XMLRead] node is Nullptr.");
//				const tinyxml2::XMLNode* node2 = node->NextSibling();
//				VERIFY(node2 != nullptr, "[XMLRead] node is Nullptr.");
//				const tinyxml2::XMLNode* node3 = node2->NextSibling();
//				VERIFY(node3 != nullptr, "[XMLRead] node is Nullptr.");
//
//				float vecX = static_cast<float>(atof(node1->Value()));
//				float vecY = static_cast<float>(atof(node2->Value()));
//				float vecZ = static_cast<float>(atof(node3->Value()));
//
//				SWGE::Math::Vector3* vec3 = reinterpret_cast<SWGE::Math::Vector3*>(instance);
//				vec3->x = vecX;
//				vec3->y = vecY;
//				vec3->z = vecZ;
//
//			}
//			if (typeName == "Vector4")
//			{
//				const tinyxml2::XMLNode* node1 = node->FirstChild();
//				VERIFY(node1 != nullptr, "[XMLRead] node is Nullptr.");
//				const tinyxml2::XMLNode* node2 = node->NextSibling();
//				VERIFY(node2 != nullptr, "[XMLRead] node is Nullptr.");
//				const tinyxml2::XMLNode* node3 = node2->NextSibling();
//				VERIFY(node3 != nullptr, "[XMLRead] node is Nullptr.");
//				const tinyxml2::XMLNode* node4 = node3->NextSibling();
//				VERIFY(node4 != nullptr, "[XMLRead] node is Nullptr.");
//
//				float vecX = static_cast<float>(atof(node1->Value()));
//				float vecY = static_cast<float>(atof(node2->Value()));
//				float vecZ = static_cast<float>(atof(node3->Value()));
//				float vecW = static_cast<float>(atof(node4->Value()));
//
//				SWGE::Math::Vector4* vec4 = reinterpret_cast<SWGE::Math::Vector4*>(instance);
//				vec4->x = vecX;
//				vec4->y = vecY;
//				vec4->z = vecZ;
//				vec4->w = vecW;
//			}
//			// Matrix 
//			// Quarternion
//		}
//	}
//}
