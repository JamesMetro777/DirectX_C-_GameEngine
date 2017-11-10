////////////////////////////////////////////////////////////////////////////////
// Filename: applicationclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "applicationclass.h"


ApplicationClass::ApplicationClass()
{
	m_Input = 0;
	m_Direct3D = 0;
	m_Timer = 0;
	m_Position = 0;
	m_Camera = 0;
	m_Light = 0;
	m_Fps = 0;
	m_Cpu = 0;
	m_GraphicManager =0;
	m_videoCardName = new char[140];
	m_VideoMemory = 0;
}


ApplicationClass::ApplicationClass(const ApplicationClass& other)
{
}


ApplicationClass::~ApplicationClass()
{
}


bool ApplicationClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;
	XMMATRIX baseViewMatrix, TempMatrix;

	
	// Create the input object.  The input object will be used to handle reading the keyboard and mouse input from the user.
	m_Input = new (_aligned_malloc(sizeof(InputClass), 16)) InputClass;
	if(!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the Direct3D object.
	m_Direct3D = new (_aligned_malloc(sizeof(D3DClass), 16))D3DClass;
	if(!m_Direct3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR); //FULL_SCREEN
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize DirectX 11.", L"Error", MB_OK);
		return false;
	}

	// Retrieve the video card information.
	m_Direct3D->GetVideoCardInfo(m_videoCardName, m_VideoMemory);

	// Create the timer object.
	m_Timer = new (_aligned_malloc(sizeof(TimerClass), 16))TimerClass;
	if(!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	// Create the position object.
	m_Position = new(_aligned_malloc(sizeof(PositionClass), 16)) PositionClass;
	if(!m_Position)
	{
		return false;
	}

	// Set the initial position and rotation of the viewer.
	m_Position->SetPosition(280.379f, 24.5225f, 367.018f);
	m_Position->SetRotation(19.6834f, 222.013f, 0.0f);
	
	// Create the camera object.
	m_Camera = new (_aligned_malloc(sizeof(CameraClass), 16))CameraClass;

	if(!m_Camera)
	{
		return false;
	}

	// Initialize a base view matrix with the camera for 2D user interface rendering.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	m_Camera->GenerateBaseViewMatrix();
	m_Camera->GetBaseViewMatrix(baseViewMatrix);

	// Create the light object.
	m_Light = new (_aligned_malloc(sizeof(LightClass), 16))LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(1.0f, -1.0f, 1.0f);
	
	
	
	// Create the fps object.
	m_Fps = new (_aligned_malloc(sizeof(FpsClass), 16))FpsClass;
	if(!m_Fps)
	{
		return false;
	}

	// Initialize the fps object.
	m_Fps->Initialize();

	// Create the cpu object.
	m_Cpu = new (_aligned_malloc(sizeof(CpuClass), 16))CpuClass;
	if(!m_Cpu)
	{
		return false;
	}
	
	m_Direct3D->GetWorldMatrix(TempMatrix);

	//Initialise Model Manager
	m_GraphicManager = new (_aligned_malloc(sizeof(GraphicManager), 16)) GraphicManager;
	result = m_GraphicManager->Initialise(m_Direct3D->GetDevice(),m_Direct3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, SCREEN_DEPTH, SCREEN_NEAR, baseViewMatrix,TempMatrix);
	if (!result)
	{
		return false;
	}


	// Initialize the cpu object.
	m_Cpu->Initialize();
	m_Position->SetPosition(133, 92, 47);
	m_Position->SetRotation(11, 23, 0);

	return true;
}


void ApplicationClass::Shutdown()
{
	
	// Release the fps object.
	if(m_Fps)
	{
		delete m_Fps;
		m_Fps = 0;
	}
		
	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}
	
	// Release the position object.
	if(m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the timer object.
	if(m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}


	// Release the D3D object.
	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}

	// Release the input object.
	if(m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}
	if (m_GraphicManager)
	{
		m_GraphicManager->Shutdown();
		delete m_GraphicManager;
		m_GraphicManager = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	return;
}


bool ApplicationClass::Frame()
{

	bool result;


	// Update the system stats.
	
		m_Fps->Frame();
		m_Cpu->Frame();
		m_Timer->Frame();

		// Read the user input.
		result = m_Input->Frame();
		if (!result)
		{
			return false;
		}

		// Check if the user pressed escape and wants to exit the application.
		if (m_Input->IsEscapePressed() == true)
		{
			return false;
		}

		// Do the frame input processing.
		result = HandleMovementInput(m_Timer->GetTime());
		if (!result)
		{
			return false;
		}

		// Do the water frame processing.
		m_GraphicManager->GetWaterModel()->Frame();

		// Do the sky plane frame processing.
		m_GraphicManager->GetSkyPlaneModel()->Frame();

		m_GraphicManager->Frame(m_Timer->GetTimeDelta(),m_Timer->GetTime());

		// Render the refraction of the scene to a texture.
		m_GraphicManager->RenderRefractionToTexture(m_Camera,m_Direct3D,m_Light);

		// Render the reflection of the scene to a texture.
		m_GraphicManager->RenderReflectionToTexture(m_Camera,m_Direct3D,m_Light);

		// Render the graphics.
		result = Render();
		if (!result)
		{
			return false;
		}


	return result;
}


bool ApplicationClass::HandleMovementInput(float frameTime)
{
	bool keyDown, result;
	float posX, posY, posZ, rotX, rotY, rotZ;


	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	// Handle the input.
	keyDown = m_Input->IsLeftPressed();
	m_Position->TurnLeft(keyDown);

	keyDown = m_Input->IsRightPressed();
	m_Position->TurnRight(keyDown);

	keyDown = m_Input->IsUpPressed();
	m_Position->MoveForward(keyDown);

	keyDown = m_Input->IsDownPressed();
	m_Position->MoveBackward(keyDown);

	keyDown = m_Input->IsAPressed();
	m_Position->MoveUpward(keyDown);

	keyDown = m_Input->IsZPressed();
	m_Position->MoveDownward(keyDown);

	keyDown = m_Input->IsWPressed();
	m_Position->LookUpward(keyDown);

	keyDown = m_Input->IsSPressed();
	m_Position->LookDownward(keyDown);
	
	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	// HandleMouse Rotations
	m_Position->MouseRotate(m_Input->GetMouseXDelta(), m_Input->GetMouseYDelta());

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);
	m_Input->ResetCursorPos();

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);
	return true;
}

bool ApplicationClass::Render()
{
	
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, baseViewMatrix, reflectionViewMatrix, translateMatrix;
	bool result;
	XMFLOAT3 cameraPosition;

	// the colours for the fog to make it look like a dust cloud
	

	// Clear the scene.
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Generate the reflection matrix based on the camera's position and the height of the water.
	m_Camera->RenderReflection(m_GraphicManager->GetWaterModel()->GetWaterHeight());

	// Get the world, view, projection, ortho, and base view matrices from the camera and Direct3D objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);
	m_Direct3D->GetOrthoMatrix(orthoMatrix);
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	m_Camera->GetReflectionViewMatrix(reflectionViewMatrix);

	// Get the position of the camera.
	cameraPosition = m_Camera->GetPosition();

	result = m_GraphicManager->Render(m_Direct3D, worldMatrix, viewMatrix, projectionMatrix, reflectionViewMatrix, orthoMatrix, m_Camera, m_Light,m_videoCardName,m_VideoMemory,m_Fps->GetFps(),m_Cpu->GetCpuPercentage());
	if (!result)
	{
		return false;
	}

	//Present the scene
	m_Direct3D->EndScene();

	return true;
}