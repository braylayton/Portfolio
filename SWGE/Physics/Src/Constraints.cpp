#include "Precompiled.h"
#include "Particle.h"
#include "Constraints.h"

using namespace SWGE;
using namespace Physics;

Fixed::Fixed(Particle* p)
{

}
Fixed::Fixed(Particle* p, const Math::Vector3& location)
	: mParticle(p)
	, mPosition(location)
{
}

void Fixed::Apply() const
{
	mParticle->position = mPosition;
}

void Fixed::DebugDraw() const
{
	SWGE::Graphics::SimpleDraw::AddSphere(mPosition, mParticle->radius*2, Math::Vector4::Red());
}

Spring::Spring(Particle* a, Particle* b, float restLength)
	: mParticalA(a)
	, mParticalB(b)
	, mRestLength(restLength)
{
	if (mRestLength <= 0.0f)
	{
		mRestLength = Math::Distance(a->position, b->position);
	}
}

void Spring::Apply() const
{
	Math::Vector3 delta = mParticalB->position - mParticalA->position;
	float dist = Math::Magnitude(delta);
	float diff = (dist - mRestLength) / (dist *(mParticalA->invMass + mParticalB->invMass));
	mParticalA->position += delta * diff * mParticalA->invMass;
	mParticalB->position -= delta * diff * mParticalB->invMass;
}
void Spring::DebugDraw() const
{
	Graphics::SimpleDraw::AddLine(mParticalA->position, mParticalB->position, Math::Vector4::Green());
}
// add function to add constraints

// use formulas for constraints 
