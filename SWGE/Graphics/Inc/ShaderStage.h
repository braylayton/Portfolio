#pragma once

namespace SWGE {
namespace Graphics {

enum class ShaderStage : uint32_t
{
	None = 0,
	Vertex = 1 << 0,
	Domain = 1 << 1,
	Hull = 1 << 2,
	Geometry = 1 << 3,
	Pixel = 1 << 4,
	Compute = 1 << 5,
	All = Vertex | Domain | Hull | Geometry | Pixel | Compute
};

constexpr ShaderStage operator|(const ShaderStage lhs, const ShaderStage rhs)
{
	using UnderlyingType = typename std::underlying_type<ShaderStage>::type;
	return static_cast<ShaderStage>(
		static_cast<UnderlyingType>(lhs) | static_cast<UnderlyingType>(rhs));
}

inline ShaderStage& operator|=(ShaderStage& lhs, const ShaderStage rhs)
{
	using UnderlyingType = typename std::underlying_type<ShaderStage>::type;
	lhs = static_cast<ShaderStage>(
		static_cast<UnderlyingType>(lhs) | static_cast<UnderlyingType>(rhs));
	return lhs;
}

constexpr ShaderStage operator&(const ShaderStage lhs, const ShaderStage rhs)
{
	using UnderlyingType = typename std::underlying_type<ShaderStage>::type;
	return static_cast<ShaderStage>(
		static_cast<UnderlyingType>(lhs) & static_cast<UnderlyingType>(rhs));
}

inline ShaderStage& operator&=(ShaderStage& lhs, const ShaderStage rhs)
{
	using UnderlyingType = typename std::underlying_type<ShaderStage>::type;
	lhs = static_cast<ShaderStage>(
		static_cast<UnderlyingType>(lhs) & static_cast<UnderlyingType>(rhs));
	return lhs;
}


}
}