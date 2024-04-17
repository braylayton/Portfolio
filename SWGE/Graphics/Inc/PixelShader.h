#ifndef INCLUDED_GRAPHICS_PIXELSHADER_H
#define INCLUDED_GRAPHICS_PIXELSHADER_H


namespace SWGE {
namespace Graphics {

class PixelShader
{
public:
	PixelShader();
	~PixelShader();

	PixelShader(const PixelShader&) = delete;
	PixelShader& operator=(const PixelShader&) = delete;

	void Initialize(LPCWSTR filename, const char* entrypoint, LPCSTR shadermodel, uint32_t vertexformat);
	void Bind();
	void Terminate();
private:
	ID3D11PixelShader* mPixelShader;
};

} //Graphics
} //SWGE




#endif //INCLUDED_GRAPHICS_PIXELSHADER_H