#include "Precompiled.h"
#include "Particle.h"

using namespace SWGE;
using namespace SWGE::Physics;

Particle::Particle(const Math::Vector3& pos, float radius)
	: position(pos)
	, radius(radius)
{
}

void Particle::DebugDraw() const
{
	SWGE::Graphics::SimpleDraw::AddSphere(position, radius, Math::Vector4::Blue(), 8,4);
}

void Particle::SetPosition(const Math::Vector3& pos)
{
	position = pos;
	positionOld = pos;
}

void Particle::SetVelocity(const Math::Vector3& velocity)
{
	positionOld = position - velocity;
}