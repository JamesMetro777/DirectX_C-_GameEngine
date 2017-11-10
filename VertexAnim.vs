////////////////////////////////////////////////////////////////////////////////
// Filename: VertexAnim.vs
////////////////////////////////////////////////////////////////////////////////


/////////////
// GLOBALS //
/////////////
cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
	float time;
};

cbuffer CamNormBuffer
{
	float3 cameraPosition;
	float3 lightDirection;
};


//////////////
// TYPEDEFS //
//////////////


struct VertexInputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
	float3 viewDirection :TEXCOORD2;
	float3 lightDirection :TEXCOORD3;
   	float3 normal : NORMAL;
};


////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType VertexAnimVertexShader(VertexInputType input)
{
    PixelInputType output;
    float4 worldPosition;
    float4 DisplacementDirection = float4(input.normal.x, input.normal.y,input.normal.z, 0);
    float displacement = 1 * 0.5 * 
                       sin(input.normal.y * 0.05 * (sin(time)/0.000001)) + 1;

    float4 newPosition = input.position + displacement * DisplacementDirection;
	// Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;



	// Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(newPosition, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);	 

	output.lightDirection = lightDirection;
    
	// Store the texture coordinates for the pixel shader.
	output.tex = input.tex;

		 // Calculate the position of the vertex in the world.
    worldPosition = mul(input.position, worldMatrix);

    // Determine the viewing direction based on the position of the camera and the position of the vertex in the world.
    output.viewDirection = cameraPosition.xyz - worldPosition.xyz;

    // Normalize the viewing direction vector.
    output.viewDirection = normalize(output.viewDirection);
    
    // Calculate the normal vector against the world matrix only and then normalize the final value.
    output.normal = mul(input.normal, (float3x3)worldMatrix);
    output.normal = normalize(output.normal);

    return output;
}