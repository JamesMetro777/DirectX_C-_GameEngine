#include "GraphicManager.h"


GraphicManager::GraphicManager()
{
	m_ShaderManager = 0;
	m_Model_TankBody = 0;
	m_Model_TankBodyTwo = 0;
	m_Model_TankTurret = 0;
	m_Model_TankGun = 0;
	m_Water = 0;
	m_Terrain = 0;
	m_SkyDome = 0;
	m_SkyPlane = 0;
	m_ReflectionTexture = 0;
	m_RefractionTexture = 0;
	m_Model_Boat = 0;
	m_text = 0;
	BoatDir = 0;
	boatTranslation = XMMatrixTranslation(200.0f, 3.8f, 300.0f);
	BoatZPos = 400.0f;
	m_time = 0;
	m_Model_BlueEyesDragon = 0;
	m_Model_Stargate = 0;

}


bool GraphicManager::Initialise(ID3D11Device* device, ID3D11DeviceContext* deviceContext, HWND hwnd, int screenWidth, int screenHeight, float screenDepth, float screenNear, DirectX::XMMATRIX &baseViewMatrix, DirectX::XMMATRIX &worldMatrix)
{

	bool result = true;



	m_ShaderManager = new (_aligned_malloc(sizeof(ShaderManagerClass), 16)) ShaderManagerClass;
	if (!m_ShaderManager)
	{
		return false;
	}
	result = m_ShaderManager->Initialize(device, hwnd);
	if(!result){
		MessageBox(hwnd, L"Could not initialize the Shader Manager.", L"Error", MB_OK);
		return false;
	}

	// Create the terrain object.
	m_Terrain = new (_aligned_malloc(sizeof(TerrainClass), 16)) TerrainClass;
	if (!m_Terrain)
	{
		return false;
	}

	// Initialize the terrain object.
	result = m_Terrain->Initialize(device, "../Engine/data/hm.bmp", "../Engine/data/cm.bmp", 20.0f, L"../Engine/data/dirt.dds",
		L"../Engine/data/normal.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
		return false;
	}


	// Create the sky dome object.
	m_SkyDome = new (_aligned_malloc(sizeof(SkyDomeClass), 16)) SkyDomeClass;
	if (!m_SkyDome)
	{
		return false;
	}

	// Initialize the sky dome object.
	result = m_SkyDome->Initialize(device);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome object.", L"Error", MB_OK);
		return false;
	}

	// Create the sky plane object.
	m_SkyPlane = new (_aligned_malloc(sizeof(SkyPlaneClass), 16)) SkyPlaneClass;
	if (!m_SkyPlane)
	{
		return false;
	}

	// Initialize the sky plane object.
	result = m_SkyPlane->Initialize(device, L"../Engine/data/cloud001.dds", L"../Engine/data/perturb001.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky plane object.", L"Error", MB_OK);
		return false;
	}


	// Create the water object.
	m_Water = new (_aligned_malloc(sizeof(WaterClass), 16)) WaterClass;
	if (!m_Water)
	{
		return false;
	}

	// Initialize the water object.
	result = m_Water->Initialize(device, L"../Engine/data/waternormal.dds", 3.75f, 400.0f);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the water object.", L"Error", MB_OK);
		return false;
	}

	//Initlialise TankGub
	m_Model_TankGun = new (_aligned_malloc(sizeof(ModelClass), 16)) ModelClass;
	result = m_Model_TankGun->Initialize(device, "../Engine/data/TankGun.txt", L"../Engine/data/TankGun.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialise Tank Model!", L"ERROR", MB_OK);
		return false;
	}


	//Initialise Tank Object Two
	m_Model_TankBodyTwo = new(_aligned_malloc(sizeof(ModelClass), 16))  ModelClass;
	result = m_Model_TankBodyTwo->Initialize(device, "../Engine/data/TankBody2.txt", L"../Engine/data/TankTwo.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialise Tank Model!", L"ERROR", MB_OK);
		return false;
	}

	// Initialise Tank Turret
	m_Model_TankTurret = new(_aligned_malloc(sizeof(ModelClass), 16))  ModelClass;
	result = m_Model_TankTurret->Initialize(device, "../Engine/data/TankTurret.txt", L"../Engine/data/TankTurret.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialise Tank Model!", L"ERROR", MB_OK);
		return false;
	}

	m_modelText = new(_aligned_malloc(sizeof(ModelClass), 16))  ModelClass;
	result = m_modelText->Initialize(device, "../Engine/data/Text.txt", L"../Engine/data/Text.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialise Text Model!", L"ERROR", MB_OK);
		return false;
	}
	//Initialise Tank main body
	m_Model_TankBody = new (_aligned_malloc(sizeof(ModelClass), 16)) ModelClass;
	result = m_Model_TankBody->Initialize(device, "../Engine/data/TankBody.txt", L"../Engine/data/Tank.dds");
	if (!result){

		MessageBox(hwnd, L"Could not initialise Tank Model", L"ERROR", MB_OK);
		return false;
	}

	m_Model_Boat = new (_aligned_malloc(sizeof(ModelClass), 16)) ModelClass;
	result = m_Model_Boat->Initialize(device, "../Engine/data/Boat.txt", L"../Engine/data/Boat.dds");
	if (!result){

		MessageBox(hwnd, L"Could not initialise Boat Model", L"ERROR", MB_OK);
		return false;
	}
	
	
	// Create the dragon object.
	m_Model_BlueEyesDragon = new ModelClass;
	if (!m_Model_BlueEyesDragon)
	{
		return false;
	}

	// Initialize the dragon object.
	result = m_Model_BlueEyesDragon->Initialize(m_D3D->GetDevice(), "../Engine/data/BlueEyesDragon.txt", L"../Engine/data/m32_UltimateBlueE_A_.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	
	// Create the Stargate object.
	m_Model_Stargate = new ModelClass;
	if (!m_Model_Stargate)
	{
		return false;
	}

	// Initialize the stargate object.
	result = m_Model_Stargate->Initialize(m_D3D->GetDevice(), "../Engine/data/Stargate.txt", L"../Engine/data/StargateRingC_D.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	
	//Initialise Reflection Texture
	m_ReflectionTexture = new (_aligned_malloc(sizeof(RenderTextureClass),16)) RenderTextureClass;
	result = m_ReflectionTexture->Initialize(device, screenWidth, screenHeight, screenDepth, screenNear);

	//Initialise Refraction Texture
	m_RefractionTexture = new (_aligned_malloc(sizeof(RenderTextureClass), 16))RenderTextureClass;
	result = m_RefractionTexture->Initialize(device, screenWidth, screenHeight, screenDepth, screenNear);
	
	//Initialise Font
	m_text = new (_aligned_malloc(sizeof(TextClass), 16)) TextClass;
	result = m_text->Initialize(device, deviceContext, hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result){

		MessageBox(hwnd, L"Could not initialise Text Object", L"ERROR", MB_OK);
		return false;
	}

	return result;
}

bool GraphicManager::Shutdown()
{
	if (m_modelText)
	{
		m_modelText->Shutdown();
		delete m_modelText;
		m_modelText = 0;
	}
	if (m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}
	
	// Release the model objects. what i've added
		
	if (m_Model_BlueEyesDragon)
	{
		m_Model_BlueEyesDragon->Shutdown();
		delete m_Model_BlueEyesDragon;
		m_Model_BlueEyesDragon = 0;
	}
	
	if (m_Model_Stargate)
	{
		m_Model_Stargate->Shutdown();
		delete m_Model_Stargate;
		m_Model_Stargate = 0;
	}

	if (m_Model_TankBody)
	{
		m_Model_TankBody->Shutdown();
		delete m_Model_TankBody;
		m_Model_TankBody = 0;
	}
	if (m_Model_TankBodyTwo)
	{
		m_Model_TankBodyTwo->Shutdown();
		delete m_Model_TankBodyTwo;
		m_Model_TankBodyTwo = 0;
	}
	if (m_Model_TankTurret)
	{
		m_Model_TankTurret->Shutdown();
		delete m_Model_TankTurret;
		m_Model_TankTurret = 0;
	}
	if (m_Model_TankGun)
	{
		m_Model_TankGun->Shutdown();
		delete m_Model_TankGun;
		m_Model_TankGun = 0;
	}
	if (m_Water)
	{
		m_Water->Shutdown();
		delete m_Water;
		m_Water = 0;
	}
	if (m_Terrain)
	{
		m_Terrain->Shutdown();
		delete m_Terrain;
		m_Terrain = 0;
	}
	if (m_SkyDome)
	{
		m_SkyDome->Shutdown();
		delete m_SkyDome;
		m_SkyDome = 0;
	}
	if (m_SkyPlane)
	{
		m_SkyPlane->Shutdown();
		delete m_SkyPlane;
		m_SkyPlane = 0;
	}

	if (m_ReflectionTexture)
	{
		m_ReflectionTexture->Shutdown();
		delete m_ReflectionTexture;
		m_ReflectionTexture = 0;
	}

	if (m_RefractionTexture)
	{
		m_RefractionTexture->Shutdown();
		delete m_RefractionTexture;
		m_RefractionTexture = 0;
	}
	if (m_Model_Boat)
	{
		m_Model_Boat->Shutdown();
		delete m_Model_Boat;
		m_Model_Boat = 0;
	}
	if (m_text)
	{
		m_text->Shutdown();
		delete m_text;
		m_text = 0;
	}

	return true;
}

GraphicManager::~GraphicManager()
{
}


void GraphicManager::Frame(float deltaTime, const float &Time)
{
	m_time = Time;
	this->TranslateBoat(deltaTime);
	this->TranslateX47(deltaTime);
}

void GraphicManager::RenderReflectionToTexture(CameraClass* camera, D3DClass* D3d, LightClass* light)
{
	XMFLOAT4 clipPlane;
	XMMATRIX reflectionViewMatrix, worldMatrix, projectionMatrix, translateMatrix;
	XMFLOAT3 cameraPosition;




	// Setup a clipping plane based on the height of the water to clip everything below it.
	clipPlane = XMFLOAT4(0.0f, 1.0f, 0.0f, -m_Water->GetWaterHeight());

	// Set the render target to be the reflection render to texture.
	m_ReflectionTexture->SetRenderTarget(D3d->GetDeviceContext());

	// Clear the reflection render to texture.
	m_ReflectionTexture->ClearRenderTarget(D3d->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Use the camera to render the reflection and create a reflection view matrix.
	camera->RenderReflection(m_Water->GetWaterHeight());

	// Get the camera reflection view matrix instead of the normal view matrix.
	camera->GetReflectionViewMatrix(reflectionViewMatrix);

	// Get the world and projection matrices from the d3d object.
	D3d->GetWorldMatrix(worldMatrix);
	D3d->GetProjectionMatrix(projectionMatrix);

	// Get the position of the camera.
	cameraPosition = camera->GetPosition();

	// Invert the Y coordinate of the camera around the water plane height for the reflected camera position.
	cameraPosition.y = -cameraPosition.y + (m_Water->GetWaterHeight() * 2.0f);

	// Translate the sky dome and sky plane to be centered around the reflected camera position.
	worldMatrix = XMMatrixTranslation(cameraPosition.x, cameraPosition.y, cameraPosition.z);

	// Turn off back face culling and the Z buffer.
	D3d->TurnOffCulling();
	D3d->TurnZBufferOff();

	// Render the sky dome using the reflection view matrix.
	m_SkyDome->Render(D3d->GetDeviceContext());
	m_ShaderManager->m_SkyDomeShader->Render(D3d->GetDeviceContext(), m_SkyDome->GetIndexCount(), worldMatrix, reflectionViewMatrix, projectionMatrix,
		m_SkyDome->GetApexColor(), m_SkyDome->GetCenterColor());



	// Enable back face culling.
	D3d->TurnOnCulling();

	// Enable additive blending so the clouds blend with the sky dome color.
	D3d->EnableSecondBlendState();

	// Render the sky plane using the sky plane shader.
	m_SkyPlane->Render(D3d->GetDeviceContext());
	m_ShaderManager->m_SkyPlaneShader->Render(D3d->GetDeviceContext(), m_SkyPlane->GetIndexCount(), worldMatrix, reflectionViewMatrix, projectionMatrix,
		m_SkyPlane->GetCloudTexture(), m_SkyPlane->GetPerturbTexture(), m_SkyPlane->GetTranslation(), m_SkyPlane->GetScale(),
		m_SkyPlane->GetBrightness());

	// Turn off blending and enable the Z buffer again.
	D3d->TurnOffAlphaBlending();
	D3d->TurnZBufferOn();

	// Reset the world matrix.
	D3d->GetWorldMatrix(worldMatrix);

	// Render the terrain using the reflection view matrix and reflection clip plane.
	m_Terrain->Render(D3d->GetDeviceContext());
	m_ShaderManager->m_ReflectionShader->Render(D3d->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, reflectionViewMatrix, projectionMatrix,
		m_Terrain->GetColorTexture(), m_Terrain->GetNormalTexture(), light->GetDiffuseColor(), light->GetDirection(), 2.0f,
		clipPlane);


	m_Model_Boat->Render(D3d->GetDeviceContext());
	m_ShaderManager->m_Cook->Render(D3d->GetDeviceContext(), m_Model_Boat->GetIndexCount(), boatTranslation, reflectionViewMatrix, projectionMatrix, m_Model_Boat->GetTexture(), cameraPosition, light->GetDirection());

	m_Model_X47->Render(D3d->GetDeviceContext());
	m_ShaderManager->m_Cook->Render(D3d->GetDeviceContext(), m_Model_X47->GetIndexCount(), boatTranslation, reflectionViewMatrix, projectionMatrix, m_Model_X47->GetTexture(), cameraPosition, light->GetDirection());



	///Render the tank Model
	translateMatrix = XMMatrixTranslation(255.f, 7.0f, 374.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(-154.0f / 57));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(3, 3, 3));
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);


	//Render Tank
	m_Model_TankBody->Render(D3d->GetDeviceContext());
	m_ShaderManager->m_TextureShader->Render(D3d->GetDeviceContext(), m_Model_TankBody->GetIndexCount(), worldMatrix, reflectionViewMatrix, projectionMatrix, m_Model_TankBody->GetTexture());

	m_Model_TankBodyTwo->Render(D3d->GetDeviceContext());
	m_ShaderManager->m_TextureShader->Render(D3d->GetDeviceContext(), m_Model_TankBodyTwo->GetIndexCount(), worldMatrix, reflectionViewMatrix, projectionMatrix, m_Model_TankBodyTwo->GetTexture());

	m_Model_TankTurret->Render(D3d->GetDeviceContext());
	m_ShaderManager->m_TextureShader->Render(D3d->GetDeviceContext(), m_Model_TankTurret->GetIndexCount(), worldMatrix, reflectionViewMatrix, projectionMatrix, m_Model_TankTurret->GetTexture());

	m_Model_TankGun->Render(D3d->GetDeviceContext());
	m_ShaderManager->m_TextureShader->Render(D3d->GetDeviceContext(), m_Model_TankGun->GetIndexCount(), worldMatrix, reflectionViewMatrix, projectionMatrix, m_Model_TankGun->GetTexture());

	D3d->GetWorldMatrix(worldMatrix);

	
	D3d->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(1));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(266, 9, 190));


	m_modelText->Render(D3d->GetDeviceContext());
	m_ShaderManager->m_BeckmannShader->Render(D3d->GetDeviceContext(), m_modelText->GetIndexCount(), worldMatrix, reflectionViewMatrix, projectionMatrix, m_modelText->GetTexture(), cameraPosition, light->GetDirection());
	D3d->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixTranslation(124, 4, 301);


	D3d->GetWorldMatrix(worldMatrix);


	// Reset the render target back to the original back buffer and not the render to texture anymore.
	D3d->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	D3d->ResetViewport();

	return;
}

void GraphicManager::RenderRefractionToTexture(CameraClass* camera, D3DClass* D3d, LightClass* light)
{
	XMFLOAT4 clipPlane;
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;


	// Setup a clipping plane based on the height of the water to clip everything above it to create a refraction.
	clipPlane = XMFLOAT4(0.0f, -1.0f, 0.0f, m_Water->GetWaterHeight() + 0.1f);

	// Set the render target to be the refraction render to texture.
	m_RefractionTexture->SetRenderTarget(D3d->GetDeviceContext());

	// Clear the refraction render to texture.
	m_RefractionTexture->ClearRenderTarget(D3d->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	camera->Render();

	// Get the matrices from the camera and d3d objects.
	D3d->GetWorldMatrix(worldMatrix);
	camera->GetViewMatrix(viewMatrix);
	D3d->GetProjectionMatrix(projectionMatrix);

	// Render the terrain using the reflection shader and the refraction clip plane to produce the refraction effect.
	m_Terrain->Render(D3d->GetDeviceContext());
	m_ShaderManager->m_ReflectionShader->Render(D3d->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Terrain->GetColorTexture(), m_Terrain->GetNormalTexture(), light->GetDiffuseColor(), light->GetDirection(), 2.0f,
		clipPlane);

	m_Model_Boat->Render(D3d->GetDeviceContext());
	m_ShaderManager->m_Cook->Render(D3d->GetDeviceContext(), m_Model_Boat->GetIndexCount(), boatTranslation, viewMatrix, projectionMatrix, m_Model_Boat->GetTexture(), camera->GetPosition(), light->GetDirection());

	m_Model_X47->Render(D3d->GetDeviceContext());
	m_ShaderManager->m_Cook->Render(D3d->GetDeviceContext(), m_Model_X47->GetIndexCount(), boatTranslation, viewMatrix, projectionMatrix, m_Model_X47->GetTexture(), camera->GetPosition(), light->GetDirection());


	// Reset the render target back to the original back buffer and not the render to texture anymore.
	D3d->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	D3d->ResetViewport();

	return;
}

bool GraphicManager::Render(D3DClass* D3d, DirectX::XMMATRIX &worldMatrix, DirectX::XMMATRIX &viewMatrix, DirectX::XMMATRIX &projectionMatrix, DirectX::XMMATRIX &reflectionViewMatrix, DirectX::XMMATRIX &orthoMatrix, CameraClass* camera, LightClass* light, char* videoCard, int videoMemory,int FPS, int CPU)
{
	XMMATRIX translateMatrix;
	bool result = true;

	XMFLOAT3 cameraPosition = camera->GetPosition();
	XMFLOAT3 cameraRotation = camera->GetRotation();

	// Translate the sky dome to be centered around the camera position.
	worldMatrix = XMMatrixTranslation(cameraPosition.x, cameraPosition.y, cameraPosition.z);
	// Turn off back face culling and the Z buffer.
	D3d->TurnOffCulling();
	D3d->TurnZBufferOff();

	//Render SkyDome with Skydome Shader

	m_SkyDome->Render(D3d->GetDeviceContext());
	m_ShaderManager->m_SkyDomeShader->Render(D3d->GetDeviceContext(), m_SkyDome->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_SkyDome->GetApexColor(), m_SkyDome->GetCenterColor());

	//Turn Culling back on
	D3d->TurnOnCulling();

	//Enable Additive blending so the clouds blend with sky dome color
	D3d->EnableSecondBlendState();

	//Render Skyplane with skyplane shader

	m_SkyPlane->Render(D3d->GetDeviceContext());
	m_ShaderManager->m_SkyPlaneShader->Render(D3d->GetDeviceContext(), m_SkyPlane->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_SkyPlane->GetCloudTexture(), m_SkyPlane->GetPerturbTexture(), m_SkyPlane->GetTranslation(), m_SkyPlane->GetScale(),
		m_SkyPlane->GetBrightness());

	//Switch off blending
	D3d->TurnOffAlphaBlending();

	//Enable Zbuffer
	D3d->TurnZBufferOn();

	//Reset world matrix
	D3d->GetWorldMatrix(worldMatrix);

	//Render Terrain with terrain Shader
	m_Terrain->Render(D3d->GetDeviceContext());
	m_ShaderManager->m_TerrainShader->Render(D3d->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Terrain->GetColorTexture(), m_Terrain->GetNormalTexture(), light->GetDiffuseColor(), light->GetDirection(),
		2.0f);


	//Setup Rotation and Translation of Tank Model
	translateMatrix = XMMatrixTranslation(255.f, 7.0f, 374.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(-154.0f / 57));
	worldMatrix = XMMatrixMultiply(worldMatrix,XMMatrixScaling(3, 3, 3));
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);



	/////////////////////////////////////////////////////////////////////
	///// RENDER TANK
	/////////////////////////////////////////////////////////////////////
	m_Model_TankBody->Render(D3d->GetDeviceContext());
	m_ShaderManager->m_BeckmannShader->Render(D3d->GetDeviceContext(), m_Model_TankBody->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model_TankBody->GetTexture(),cameraPosition,light->GetDirection());

	m_Model_TankBodyTwo->Render(D3d->GetDeviceContext());
	m_ShaderManager->m_BeckmannShader->Render(D3d->GetDeviceContext(), m_Model_TankBodyTwo->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model_TankBodyTwo->GetTexture(), cameraPosition, light->GetDirection());

	m_Model_TankTurret->Render(D3d->GetDeviceContext());
	m_ShaderManager->m_BeckmannShader->Render(D3d->GetDeviceContext(), m_Model_TankTurret->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model_TankTurret->GetTexture(), cameraPosition, light->GetDirection());

	m_Model_TankGun->Render(D3d->GetDeviceContext());
	m_ShaderManager->m_BeckmannShader->Render(D3d->GetDeviceContext(), m_Model_TankGun->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model_TankGun->GetTexture(), cameraPosition, light->GetDirection());


	//Reset world matrix
	D3d->GetWorldMatrix(worldMatrix);
	m_Model_Boat->Render(D3d->GetDeviceContext());
	m_ShaderManager->m_Cook->Render(D3d->GetDeviceContext(), m_Model_Boat->GetIndexCount(), boatTranslation, viewMatrix, projectionMatrix, m_Model_Boat->GetTexture(),cameraPosition,light->GetDirection());

	// Translate to the location of the water and render it.
	worldMatrix = XMMatrixTranslation(240.0f, m_Water->GetWaterHeight(), 250.0f);

	m_Water->Render(D3d->GetDeviceContext());
	m_ShaderManager->m_WaterShader->Render(D3d->GetDeviceContext(), m_Water->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, reflectionViewMatrix,
		m_RefractionTexture->GetShaderResourceView(), m_ReflectionTexture->GetShaderResourceView(), m_Water->GetTexture(),
		cameraPosition, m_Water->GetNormalMapTiling(), m_Water->GetWaterTranslation(), m_Water->GetReflectRefractScale(),
		m_Water->GetRefractionTint(), light->GetDirection(), m_Water->GetSpecularShininess());

	//Reset World matrix
	D3d->GetWorldMatrix(worldMatrix);

	
	

	D3d->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(1));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(266, 9, 190));


	m_modelText->Render(D3d->GetDeviceContext());
	m_ShaderManager->m_BeckmannShader->Render(D3d->GetDeviceContext(), m_modelText->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_modelText->GetTexture(), cameraPosition, light->GetDirection());
	D3d->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixTranslation(124,4,301);

	m_Model_Stargate->Render(D3d->GetDeviceContext());
	translateMatrix = XMMatrixTranslation(190.f, 7.0f, 280.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(-154.0f / 57));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(4, 10, 4));
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);
	
	// Render the first model using the texture shader.
	m_Model_Stargate->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_Model_Stargate->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
												  m_Model_Stargate->GetTexture());
	if(!result)
	{
		return false;
	}

	m_Model_BlueEyesDragon->Render(D3d->GetDeviceContext());
	translateMatrix = XMMatrixTranslation(150.f, 9.0f, 100.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(-154.0f / 57));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(7, 11, 7));
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);
	
	// Render the first model using the texture shader.
	m_Model_BlueEyesDragon->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_Model_BlueEyesDragon->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
												  m_Model_BlueEyesDragon->GetTexture());
	if(!result)
	{
		return false;
	}

	

	D3d->GetWorldMatrix(worldMatrix);


	// Turn off the Z buffer to begin all 2D rendering.
	D3d->TurnZBufferOff();

	// Turn on the alpha blending before rendering the text.
	D3d->TurnOnAlphaBlending();
	
	// Render the text user interface elements.
	
	m_text->SetVideoCardInfo(videoCard,videoMemory,D3d->GetDeviceContext());
	m_text->SetCameraPosition(cameraPosition.x,cameraPosition.y,cameraPosition.z,D3d->GetDeviceContext());
	m_text->SetCameraRotation(cameraRotation.x,cameraRotation.y,cameraRotation.z,D3d->GetDeviceContext());
	m_text->SetFps(FPS,D3d->GetDeviceContext());
	m_text->SetCpu(CPU, D3d->GetDeviceContext());
	result = m_text->Render(D3d->GetDeviceContext(), m_ShaderManager->m_FontShader, worldMatrix, orthoMatrix);
	if(!result)
	{
	return false;
	}
	
	//
	// Turn off alpha blending after rendering the text.
	D3d->TurnOffAlphaBlending();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	D3d->TurnZBufferOn();

	return result;
}

WaterClass* GraphicManager::GetWaterModel()
{
	return m_Water;
}

SkyPlaneClass* GraphicManager::GetSkyPlaneModel()
{
	return m_SkyPlane;
}

void GraphicManager::TranslateBoat(float deltaTime)
{
	this->BoatZPos -= (float)(deltaTime * 0.01000300);
	boatTranslation = XMMatrixTranslation(200.0f, 3.8f, this->BoatZPos);

	if (this->BoatZPos <= 0) this->BoatZPos = 500.0f;
}

