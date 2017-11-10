#include <d3dx9.h>

// Colors
const D3DXCOLOR      WHITE( D3DCOLOR_XRGB(255, 255, 255) );
const D3DXCOLOR      BLACK( D3DCOLOR_XRGB(  0,   0,   0) );
const D3DXCOLOR        RED( D3DCOLOR_XRGB(255,   0,   0) );
const D3DXCOLOR      GREEN( D3DCOLOR_XRGB(  0, 255,   0) );
const D3DXCOLOR       BLUE( D3DCOLOR_XRGB(  0,   0, 255) );
const D3DXCOLOR     YELLOW( D3DCOLOR_XRGB(255, 255,   0) );
const D3DXCOLOR       CYAN( D3DCOLOR_XRGB(  0, 255, 255) );
const D3DXCOLOR    MAGENTA( D3DCOLOR_XRGB(255,   0, 255) );

const float INFTY = FLT_MAX;

class CBoundingBox
{
public:
	CBoundingBox(void);
	virtual ~CBoundingBox(void);

		// Materials
		D3DMATERIAL9 InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p);

		// Bounding Objects
		struct BoundingBox
		{
			BoundingBox();
			bool isPointInside(D3DXVECTOR3& p);
			D3DXVECTOR3 _min;
			D3DXVECTOR3 _max;
		};

		void Bounding_Box_Create(LPDIRECT3DDEVICE9 device, ID3DXMesh* mesh);
		bool BoundingBox_Compute(ID3DXMesh* mesh, BoundingBox* box);
		void Bounding_Box_Render(LPDIRECT3DDEVICE9 device, ID3DXMesh* mesh, D3DMATERIAL9 matColor);

		//Xu Test
		void CalcAABBFromOBB(const D3DXVECTOR3 *obb,D3DXVECTOR3 *minB,D3DXVECTOR3 *maxB);

public:
	D3DMATERIAL9 WHITE_MTRL;
	D3DMATERIAL9 RED_MTRL;
	D3DMATERIAL9 GREEN_MTRL;
	D3DMATERIAL9 BLUE_MTRL;
	D3DMATERIAL9 YELLOW_MTRL;

	LPD3DXMESH BoxMesh;
	LPD3DXMESH AABBBoxMesh;
};

