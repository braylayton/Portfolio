#pragma once
#include "Common.h"

namespace SWGE {
namespace Core {

class MetaClass;

namespace MetaRegistry {

void Register(const MetaClass* metaClass);

const MetaClass* FindMetaClass(const char* className);

}
}
}