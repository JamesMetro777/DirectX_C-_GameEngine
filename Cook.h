#pragma once


//////////////
// INCLUDES //
//////////////
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
using namespace DirectX;

#include <fstream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Class name: Cook
////////////////////////////////////////////////////////////////////////////////
class Cook
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

	struct CamNormBufferType
	{
		XMFLOAT3 cameraPosition;
		XMFLOAT3 lightDirection;
	};

public:

	Cook();
	Cook(const Cook&);
	~Cook();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, const XMMATRIX&, const XMMATRIX&, const XMMATRIX&, ID3D11ShaderResourceView*, DirectX::XMFLOAT3 &cameraPosition, DirectX::XMFLOAT3 &lightDirection);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);


	bool SetShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &worldMatrix, const XMMATRIX &viewMatrix,
		const XMMATRIX &projectionMatrix, ID3D11ShaderResourceView* texture, DirectX::XMFLOAT3 &cameraPosition, DirectX::XMFLOAT3 &lightDirection);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_camNormBuffer;
	ID3D11SamplerState* m_sampleState;
};

