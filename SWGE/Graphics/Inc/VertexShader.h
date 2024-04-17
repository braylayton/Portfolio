#ifndef INCLUDED_GRAPHICS_VERTEXSHADER_H
#define INCLUDED_GRAPHICS_VERTEXSHADER_H
namespace SWGE {
namespace Graphics {

class VertexShader
{
public:
	VertexShader();
	~VertexShader();

	VertexShader(const VertexShader&) = delete;
	VertexShader& operator=(const VertexShader&) = delete;

	void Initialize(LPCWSTR filename, const char* entrypoint, LPCSTR shadermodel, uint32_t vertexformat);
	//void Initialize(LPCWSTR filename, uint32_t vertexformat);
	void Bind();
	void Terminate();
private:
	ID3D11VertexShader* mVertexShader;
	ID3D11InputLayout* mInputLayout;
};

} //Graphics
} //SWGE
#endif // INCLUDED_GRAPHICS_VERTEXSHADER_H
