#include "BoundingBox.h"

CBoundingBox::CBoundingBox(void)
{
	  WHITE_MTRL  = InitMtrl(WHITE, WHITE, WHITE, BLACK, 2.0f);
	  RED_MTRL    = InitMtrl(RED, RED, RED, BLACK, 2.0f);
	  GREEN_MTRL  = InitMtrl(GREEN, GREEN, GREEN, BLACK, 2.0f);
	  BLUE_MTRL   = InitMtrl(BLUE, BLUE, BLUE, BLACK, 2.0f);
	  YELLOW_MTRL = InitMtrl(YELLOW, YELLOW, YELLOW, BLACK, 2.0f);

	  BoxMesh    = NULL;
	  AABBBoxMesh = NULL;
}
CBoundingBox::~CBoundingBox(void)
{

}
D3DMATERIAL9 CBoundingBox::InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p)
{
	D3DMATERIAL9 mtrl;
	mtrl.Ambient  = a;
	mtrl.Diffuse  = d;
	mtrl.Specular = s;
	mtrl.Emissive = e;
	mtrl.Power    = p;
	return mtrl;
}
bool CBoundingBox::BoundingBox_Compute(ID3DXMesh* mesh, BoundingBox* box)
{
	HRESULT hr = 0;

	BYTE* v = 0;
	mesh->LockVertexBuffer(0, (void**)&v);

	hr = D3DXComputeBoundingBox(
		(D3DXVECTOR3*)v,
		mesh->GetNumVertices(),
		D3DXGetFVFVertexSize(mesh->GetFVF()),
		&box->_min,
		&box->_max);

	mesh->UnlockVertexBuffer();

	if( FAILED(hr) )
		return false;

	return true;
}

bool CBoundingBox::BoundingBox::isPointInside(D3DXVECTOR3& p)
{
	if( p.x >= _min.x && p.y >= _min.y && p.z >= _min.z &&
		p.x <= _max.x && p.y <= _max.y && p.z <= _max.z )
	{
		return true;
	}
	else
	{
		return false;
	}
}
void CBoundingBox::Bounding_Box_Render(LPDIRECT3DDEVICE9 device, ID3DXMesh* mesh, D3DMATERIAL9 matColor)
{
	// Draw bounding volume in yellow and at 50% opacity
	D3DMATERIAL9 color = matColor;
	color.Diffuse.a = 0.50f; // 50% opacity

	device->SetMaterial(&color);
	device->SetTexture(0, 0); // disable texture

	device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//BoxMesh->DrawSubset(0);
	mesh->DrawSubset(0);
}

CBoundingBox::BoundingBox::BoundingBox()
{
	//*
	// infinite small 
	_min.x = INFTY;
	_min.y = INFTY;
	_min.z = INFTY;

	_max.x = -INFTY;
	_max.y = -INFTY;
	_max.z = -INFTY;
	//*/
}
void	CBoundingBox::Bounding_Box_Create(LPDIRECT3DDEVICE9 device, ID3DXMesh* mesh)
{
	//******************** Compute Bounding Sphere and Bounding Box.
	BoundingBox    boundingBox;

	BoundingBox_Compute(mesh, &boundingBox);

	D3DXCreateBox(
		device,
		boundingBox._max.x - boundingBox._min.x,
		boundingBox._max.y - boundingBox._min.y,
		boundingBox._max.z - boundingBox._min.z,
		&BoxMesh,
		NULL);
}


//Xu-Test

/*********************************************************************************
Desc: Given the 8 corners of a OBB bounding box in world space, create a AABB bounding box in world space
*********************************************************************************/
void CBoundingBox::CalcAABBFromOBB(const D3DXVECTOR3 *obb,D3DXVECTOR3 *minB,D3DXVECTOR3 *maxB)
{
      minB->x=maxB->x=obb[0].x;
      minB->y=maxB->y=obb[0].y;
      minB->z=maxB->z=obb[0].z;

      for (int i=1;i<8;i++)
      {
          if (obb[i].x < minB->x) minB->x=obb[i].x;
          if (obb[i].x > maxB->x) maxB->x=obb[i].x;
          if (obb[i].y < minB->y) minB->y=obb[i].y;
          if (obb[i].y > maxB->y) maxB->y=obb[i].y;
          if (obb[i].z < minB->z) minB->z=obb[i].z;
          if (obb[i].z > maxB->z) maxB->z=obb[i].z;
      }

}
