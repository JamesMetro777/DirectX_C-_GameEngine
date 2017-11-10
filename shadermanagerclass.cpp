////////////////////////////////////////////////////////////////////////////////
// Filename: shadermanagerclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "shadermanagerclass.h"


ShaderManagerClass::ShaderManagerClass()
{
	m_TextureShader = 0;
	m_LightShader = 0;
	m_BumpMapShader = 0;
	m_TerrainShader = 0;
	m_SkyDomeShader = 0;
	m_SkyPlaneShader = 0;
	m_ReflectionShader = 0;
	m_WaterShader = 0;
	m_BeckmannShader = 0;
	m_FontShader = 0;
	m_PhongShader = 0;
	m_Cook = 0;
	m_VertexAnimShader = 0;
}


ShaderManagerClass::ShaderManagerClass(const ShaderManagerClass& other)
{
}


ShaderManagerClass::~ShaderManagerClass()
{
}


bool ShaderManagerClass::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;


	// Create the texture shader object.
	m_TextureShader = new (_aligned_malloc(sizeof(TextureShaderClass),16)) TextureShaderClass;
	if(!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	//Create Font Shader
	m_FontShader = new (_aligned_malloc(sizeof(FontShaderClass), 16)) FontShaderClass;
	if (!m_FontShader)
	{
		return false;
	}
	//Initialise Font shader
	result = m_FontShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Font shader object.", L"Error", MB_OK);
		return false;
	}


	// Create the light shader object.
	m_LightShader = new (_aligned_malloc(sizeof(LightShaderClass), 16))LightShaderClass;
	if(!m_LightShader)
	{
		return false;
	}


	// Initialize the light shader object.
	result = m_LightShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the bump map shader object.
	m_BumpMapShader = new(_aligned_malloc(sizeof(BumpMapShaderClass), 16)) BumpMapShaderClass;
	if(!m_BumpMapShader)
	{
		return false;
	}

	// Initialize the bump map shader object.
	result = m_BumpMapShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the bump map shader object.", L"Error", MB_OK);
		return false;
	}


	//Create Terrain shader
	m_TerrainShader = new (_aligned_malloc(sizeof(TerrainShaderClass), 16))TerrainShaderClass;
	if (!m_TerrainShader)
	{
		return false;
	}

	//Initialise the terrainShader
	result = m_TerrainShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain shader object.", L"Error", MB_OK);
		return false;
	}


	//Create the Sky dome Shader

	m_SkyDomeShader = new (_aligned_malloc(sizeof(SkyDomeShaderClass), 16))SkyDomeShaderClass;
	if (!m_SkyDomeShader)
	{
		return false;
	}

	// Intialise sky dome shader

	result = m_SkyDomeShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome shader object.", L"Error", MB_OK);
		return false;
	}

	//Create Sky Plane Shader

	m_SkyPlaneShader = new (_aligned_malloc(sizeof(SkyPlaneShaderClass), 16))SkyPlaneShaderClass;
	if (!m_SkyPlaneShader)
	{
		return false;
	}

	// IntialiseSky Plane shader

	result = m_SkyPlaneShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky Plane shader object.", L"Error", MB_OK);
		return false;
	}


	// Create the reflection shader object.
	m_ReflectionShader = new (_aligned_malloc(sizeof(ReflectionShaderClass), 16))ReflectionShaderClass;
	if (!m_ReflectionShader)
	{
		return false;
	}

	// Initialize the reflection shader object.
	result = m_ReflectionShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the reflection shader object.", L"Error", MB_OK);
		return false;
	}


	// Create the water shader object.
	m_WaterShader = new(_aligned_malloc(sizeof(WaterShaderClass), 16)) WaterShaderClass;
	if (!m_WaterShader)
	{
		return false;
	}

	// Initialize the water shader object.
	result = m_WaterShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the water shader object.", L"Error", MB_OK);
		return false;
	}

	m_BeckmannShader = new(_aligned_malloc(sizeof(BeckmannShader), 16)) BeckmannShader;
	result = m_BeckmannShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Beckmann Shader.", L"Error", MB_OK);
		return false;
	}

	m_PhongShader = new(_aligned_malloc(sizeof(PhongShader), 16)) PhongShader;
	result = m_PhongShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Phong Shader.", L"Error", MB_OK);
		return false;
	}

	m_Cook = new(_aligned_malloc(sizeof(Cook), 16)) Cook;
	result = m_Cook->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Phong Shader.", L"Error", MB_OK);
		return false;
	}

	m_VertexAnimShader = new(_aligned_malloc(sizeof(VertexAnimShader), 16)) VertexAnimShader;
	result = m_VertexAnimShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Vertex Anim Shader.", L"Error", MB_OK);
		return false;
	}
	return true;
}


void ShaderManagerClass::Shutdown()
{
	// Release Font Shader object.
	if (m_FontShader)
	{
		m_FontShader->Shutdown();
		_aligned_free(m_FontShader);
		m_FontShader = 0;
	}
	if (m_VertexAnimShader)
	{
		m_VertexAnimShader->Shutdown();
		_aligned_free(m_VertexAnimShader);
		m_VertexAnimShader = 0;
	}

	// Release the bump map shader object.
	if(m_BumpMapShader)
	{
		m_BumpMapShader->Shutdown();
		_aligned_free( m_BumpMapShader);
		m_BumpMapShader = 0;
	}

	// Release the light shader object.
	if(m_LightShader)
	{
		m_LightShader->Shutdown();
		_aligned_free( m_LightShader);
		m_LightShader = 0;
	}

	// Release the texture shader object.
	if(m_TextureShader)
	{
		m_TextureShader->Shutdown();
		_aligned_free( m_TextureShader);
		m_TextureShader = 0;
	}

	// Release the water shader object.
	if (m_WaterShader)
	{
		m_WaterShader->Shutdown();
		_aligned_free( m_WaterShader);
		m_WaterShader = 0;
	}

	// Release the reflection shader object.
	if (m_ReflectionShader)
	{
		m_ReflectionShader->Shutdown();
		_aligned_free( m_ReflectionShader);
		m_ReflectionShader = 0;
	}

	if (m_SkyPlaneShader)
	{
		m_SkyPlaneShader->Shutdown();
		_aligned_free( m_SkyPlaneShader);
		m_SkyPlaneShader = 0;
	}

	// Release the sky dome shader object.
	if (m_SkyDomeShader)
	{
		m_SkyDomeShader->Shutdown();
		_aligned_free( m_SkyDomeShader);
		m_SkyDomeShader = 0;
	}

	// Release the terrain shader object.
	if (m_TerrainShader)
	{
		m_TerrainShader->Shutdown();
		_aligned_free( m_TerrainShader);
		m_TerrainShader = 0;
	}

	if (m_BeckmannShader)
	{
		m_BeckmannShader->Shutdown();
		_aligned_free( m_BeckmannShader);
		m_BeckmannShader = 0;
	}

	if (m_PhongShader)
	{
		m_PhongShader->Shutdown();
		_aligned_free(m_PhongShader);
		m_PhongShader = 0;
	}

	if (m_Cook)
	{
		m_Cook->Shutdown();
		_aligned_free(m_Cook);
		m_Cook = 0;
	}
	return;
}


bool ShaderManagerClass::RenderTextureShader(ID3D11DeviceContext* device, int indexCount, const XMMATRIX &worldMatrix, const XMMATRIX &viewMatrix, const XMMATRIX &projectionMatrix,
											 ID3D11ShaderResourceView* texture)
{
	bool result;


	// Render the model using the texture shader.
	result = m_TextureShader->Render(device, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture);
	if(!result)
	{
		return false;
	}

	return true;
}


bool ShaderManagerClass::RenderLightShader(ID3D11DeviceContext* deviceContext, int indexCount, const XMMATRIX &worldMatrix, const XMMATRIX &viewMatrix, const XMMATRIX &projectionMatrix,
	ID3D11ShaderResourceView* texture, XMFLOAT3 lightDirection, XMFLOAT4 ambient, XMFLOAT4 diffuse,
	XMFLOAT3 cameraPosition, XMFLOAT4 specular, float specularPower)
{
	bool result;


	// Render the model using the light shader.
	result = m_LightShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, lightDirection, ambient, diffuse, cameraPosition, 
								   specular, specularPower);
	if(!result)
	{
		return false;
	}

	return true;
}


bool ShaderManagerClass::RenderBumpMapShader(ID3D11DeviceContext* deviceContext, int indexCount, const XMMATRIX &worldMatrix, const XMMATRIX &viewMatrix, const XMMATRIX &projectionMatrix,
	ID3D11ShaderResourceView* colorTexture, ID3D11ShaderResourceView* normalTexture, XMFLOAT3 lightDirection,
											 XMFLOAT4 diffuse)
{
	bool result;


	// Render the model using the bump map shader.
	result = m_BumpMapShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, colorTexture, normalTexture, lightDirection, diffuse);
	if(!result)
	{
		return false;
	}

	return true;
}