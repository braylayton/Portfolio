#include "Precompiled.h"
#include "SceneNodeInc\CameraNode.h"
#include "Input/Inc/Input.h"

using namespace SWGE;
using namespace Graphics;

CameraNode::CameraNode(const Camera& cam, const bool Orthographic, const bool LightCamera)
	: SceneNode("CameraNode")
	, mCamera(cam)
	, isOrthographic(Orthographic)
	, mIndex(0)
	, isLightCamera(LightCamera)
{
}

CameraNode::~CameraNode()
{
	Terminate();
}

void CameraNode::Initialize()
{
	mConstantBuffer.Initialize();
}

void CameraNode::Terminate()
{
	mConstantBuffer.Terminate();
}

void CameraNode::OnUpdate(float deltaTime)
{
	auto inputSystem = Input::InputSystem::Get();
	const float moveSpeed = 10.0f;
	const float turnSpeed = 10.0f;
	if (!isLightCamera)
	{
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::W))
		mCamera.Walk(deltaTime * moveSpeed);
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::S))
		mCamera.Walk(deltaTime * -moveSpeed);
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::D))
		mCamera.Strafe(deltaTime * moveSpeed);
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::A))
		mCamera.Strafe(deltaTime * -moveSpeed);
	mCamera.Yaw(inputSystem->GetMouseMoveX() * deltaTime * turnSpeed);
	mCamera.Pitch(inputSystem->GetMouseMoveY() * deltaTime * turnSpeed);
	}

}

void CameraNode::OnRender()
{
	ConstantBuffer constants;
	constants.matView = Math::Transpose(mCamera.GetViewMatrix());
	if(!isOrthographic)
	{ 
		constants.matProjection = Math::Transpose(mCamera.GetPerspectiveMatrix());
	}
	else
	{
		constants.matProjection = Math::Transpose(mCamera.GetOrthographicMatrix(50,50));
	}

	constants.viewPosition = Math::Vector4(mCamera.GetPosition(),1);
	mConstantBuffer.Set(constants);

	mConstantBuffer.BindVS(mIndex);
	mConstantBuffer.BindPS(mIndex);
}