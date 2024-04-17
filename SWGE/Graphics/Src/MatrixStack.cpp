#include "Precompiled.h"
#include "MatrixStack.h"

using namespace SWGE;
using namespace Graphics;

MatrixStack::MatrixStack()
{
	mMatrixCount = 0;
}

MatrixStack::~MatrixStack()
{

}

void MatrixStack::PushMatrix(Math::Matrix4& matrix)
{
	if (mMatrixCount == 0)
	{
		mMatrixStack.push_back(matrix);

	}
	else
	{
		mMatrixStack.push_back(mMatrixStack.back() * matrix);
	}
}
void MatrixStack::PopMatrix()
{
	mMatrixStack.pop_back();
}

Math::Matrix4& MatrixStack::GetMatrixTranspose()
{
	return Math::Transpose(mMatrixStack.back());
}