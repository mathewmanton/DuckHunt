#include "Crosshair.h"

struct Vertexs
{
	XMFLOAT3 Pos;
	XMFLOAT3 Tangent;
	XMFLOAT3 Normal;
	XMFLOAT2 Tex0;
	XMFLOAT2 Tex1;
	XMCOLOR Color;
};

Crosshair::Crosshair(ID3D11Device* device) 
{
	HR(D3DX11CreateShaderResourceViewFromFile(device,
		L"Textures/ice.dds", 0, 0, &mSRVMap, 0));
	// Create vertex buffer
	Vertexs verticesPos[] =
	{
		{ XMFLOAT3(0.0f, 0.0f, 0.0f) },
		{ XMFLOAT3(0.0f, 0.0625f, 0.0f) },
		{ XMFLOAT3(0.0625f, 0.0625f, 0.0f) },
		{ XMFLOAT3(0.0625f, 0.0f, 0.0f) },
		{ XMFLOAT3(0.125f, 0.0f, 0.0f) },
		{ XMFLOAT3(0.125f, -0.0625f, 0.0f) },
		{ XMFLOAT3(0.0625f, -0.0625f, 0.0f) },
		{ XMFLOAT3(0.0625f, -0.125f, 0.0f) },
		{ XMFLOAT3(0.0f, -0.125f, 0.0f) },
		{ XMFLOAT3(0.0f, -0.0625f, 0.0f) },
		{ XMFLOAT3(-0.0625f, -0.0625f, 0.0f) },
		{ XMFLOAT3(-0.0625f, 0.0f, 0.0f) },

	};

	Vertexs verticesColor[] =
	{
		{ (const float*)&Colors::Black },
	};


	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertexs) * 12;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = verticesPos;


	HR(device->CreateBuffer(&vbd, &vinitData, &mCrosshairVB));



	// Create the index buffer

	UINT indices[] = {

		// bottom face

		0, 3, 6,
		0, 6, 9,

		0, 1, 3,
		1, 2, 3,

		3, 4, 6,
		4, 5, 6,

		6, 7, 9,
		7, 8, 9,

		9, 10, 0,
		10, 11, 0





	};

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * 30;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = indices;
	HR(device->CreateBuffer(&ibd, &iinitData, &mCrosshairIB));


	World = XMMatrixIdentity();
	Scale = XMMatrixScaling(0.125, 0.25, 1);
	Translation = XMMatrixTranslation(50.0f, 50.0f, 1.0f);
	World = XMMatrixMultiply(World, Scale);

}

void Crosshair::Draw(ID3D11DeviceContext* dc, Camera cam)
{

	UINT stride = sizeof(Vertexs);
	UINT offset = 0;
	dc->IASetVertexBuffers(0, 1, &mCrosshairVB, &stride, &offset);
	dc->IASetIndexBuffer(mCrosshairIB, DXGI_FORMAT_R32_UINT, 0);


	
	D3DX11_TECHNIQUE_DESC techDesc;
	Effects::BasicFX->Light3TexAlphaClipTech->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		
		Effects::BasicFX->Light3TexAlphaClipTech->GetPassByIndex(p)->Apply(0, dc);
		Effects::BasicFX->SetWorldViewProj(World);
		Effects::BasicFX->SetDiffuseMap(mSRVMap);
		
		// 36 indices for the box.
		dc->DrawIndexed(30, 0, 0);
	}
}


Crosshair::~Crosshair()
{
	ReleaseCOM(mSRVMap);
}

