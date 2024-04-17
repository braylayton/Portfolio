#ifndef INCLUDED_GRAPHICS_MATRIXSTACK_H
#define INCLUDED_GRAPHICS_MATRIXSTACK_H

namespace SWGE {
namespace Graphics {

class MatrixStack
{
public:
	MatrixStack();
	~MatrixStack();
	void PushMatrix(Math::Matrix4& matrix);
	void PopMatrix();
	Math::Matrix4& GetMatrixTranspose();
private:
	std::vector<Math::Matrix4> mMatrixStack;
	int mMatrixCount;
};

}
}
#endif //INCLUDED_GRAPHICS_MATRIXSTACK_H

