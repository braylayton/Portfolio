#include "Precompiled.h"
#include "MetaRegistration.h"
#include "MetaRegistry.h"

// Components
//#include "Component.h"
//#include "ColliederComponent.h"
//#include "TransformComponent.h"

META_TYPE_DEFINE(int, "Int")
META_TYPE_DEFINE(float, "Float")
META_TYPE_DEFINE(bool, "Bool")
META_TYPE_DEFINE(std::string, "String")

//META_TYPE_DEFINE(color, "Color")

void SWGE::Core::MetaRegistration()
{
	#define REGISTER(x) MetaRegistry::Register(x::StaticGetMetaClass())

	//REGISTER(Camera);

	//Components
	//REGISTER(Component);

	//REGISTER(ColliderComponent);
	//ReGISTER(TransformComponent);
#undef REGISTER
}