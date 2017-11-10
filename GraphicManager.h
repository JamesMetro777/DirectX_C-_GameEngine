#pragma once

#include "modelclass.h"
#include "bumpmodelclass.h"
#include "waterclass.h"
#include "terrainclass.h"
#include "skydomeclass.h"
#include "skyplaneclass.h"
#include "d3dclass.h"
#include "lightclass.h"
#include "rendertextureclass.h"
#include "cameraclass.h"
#include "textclass.h"
#include "d3dclass.h"

#include <d3d11_1.h>
#include <DirectXMath.h> 

#include "shadermanagerclass.h"
using namespace DirectX;
using namespace std;

class GraphicManager
{
public:
	GraphicManager();
	~GraphicManager();

	bool Initialise(ID3D11Device*, ID3D11DeviceContext*, HWND, int, int, float, float, DirectX::XMMATRIX &baseViewMatrix, DirectX::XMMATRIX &worldMatrix);
	bool Render(D3DClass* D3d, DirectX::XMMATRIX &worldMatrix, DirectX::XMMATRIX &viewMatrix, DirectX::XMMATRIX &projectionMatrix, DirectX::XMMATRIX &orthoMatrix, DirectX::XMMATRIX &reflectionViewMatrix, CameraClass* camera, LightClass* light, char* videoCard, int videoMemory, int FPS, int CPU);
	bool Shutdown();

	void Frame(float, const float &Time);

	void RenderReflectionToTexture(CameraClass* camera,D3DClass* D3d, LightClass* light);

	void RenderRefractionToTexture(CameraClass* camera, D3DClass* D3d, LightClass* light);

	WaterClass* GetWaterModel();
	SkyPlaneClass* GetSkyPlaneModel();

private:
	ShaderManagerClass* m_ShaderManager;
	D3DClass* m_D3D;

	ModelClass* m_Model_TankBody;
	ModelClass* m_Model_TankBodyTwo;
	ModelClass* m_Model_TankTurret;
	ModelClass* m_Model_TankGun;
	ModelClass* m_Model_Boat;
	ModelClass* m_Model_BlueEyesDragon;
	ModelClass* m_Model_Stargate;
	ModelClass* m_modelText;
	

	TextClass* m_text;

	WaterClass* m_Water;
	TerrainClass* m_Terrain;
	SkyDomeClass* m_SkyDome;
	SkyPlaneClass *m_SkyPlane;

	RenderTextureClass* m_RefractionTexture;
	RenderTextureClass* m_ReflectionTexture;
	XMMATRIX boatTranslation;
	

	bool BoatDir;
	bool m_renderHeli = true;
	float BoatZPos;
	float m_time;
	

	void TranslateBoat(float);
	

};

