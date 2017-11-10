////////////////////////////////////////////////////////////////////////////////
// Filename: shadermanagerclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SHADERMANAGERCLASS_H_
#define _SHADERMANAGERCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "textureshaderclass.h"
#include "lightshaderclass.h"
#include "bumpmapshaderclass.h"
#include "watershaderclass.h"
#include "reflectionshaderclass.h"
#include "skyplaneshaderclass.h"
#include "skydomeshaderclass.h"
#include "terrainshaderclass.h"
#include "BeckmannShader.h"
#include "fontshaderclass.h"
#include "PhongShader.h"
#include "Cook.h"
#include "VertexAnimShader.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: ShaderManagerClass
////////////////////////////////////////////////////////////////////////////////
class ShaderManagerClass
{
public:
	ShaderManagerClass();
	ShaderManagerClass(const ShaderManagerClass&);
	~ShaderManagerClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();

	bool RenderTextureShader(ID3D11DeviceContext*, int, const XMMATRIX&, const XMMATRIX&, const XMMATRIX&, ID3D11ShaderResourceView*);

	bool RenderLightShader(ID3D11DeviceContext*, int, const XMMATRIX&, const XMMATRIX&, const XMMATRIX&, ID3D11ShaderResourceView*,
		XMFLOAT3, XMFLOAT4, XMFLOAT4, XMFLOAT3, XMFLOAT4, float);

	bool RenderBumpMapShader(ID3D11DeviceContext*, int, const XMMATRIX&, const XMMATRIX&, const XMMATRIX&, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT4);

	TextureShaderClass* m_TextureShader;
	LightShaderClass* m_LightShader;
	BumpMapShaderClass* m_BumpMapShader;
	WaterShaderClass* m_WaterShader;
	ReflectionShaderClass* m_ReflectionShader;
	SkyPlaneShaderClass* m_SkyPlaneShader;
	TerrainShaderClass* m_TerrainShader;
	SkyDomeShaderClass* m_SkyDomeShader;
	BeckmannShader* m_BeckmannShader;
	FontShaderClass* m_FontShader;
	PhongShader* m_PhongShader;
	Cook* m_Cook;
	VertexAnimShader* m_VertexAnimShader;
};

#endif