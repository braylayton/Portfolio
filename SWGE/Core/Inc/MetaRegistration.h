#pragma once

#include "Common.h"
#include "Meta.h"

META_TYPE_DECLARE(int)
META_TYPE_DECLARE(float)
META_TYPE_DECLARE(bool)
META_TYPE_DECLARE(std::string)

namespace SWGE {
namespace Core
{
	void MetaRegistration();
}
}
//color
// math::vector3