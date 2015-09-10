#include "d3dUtil.h"
#include "d3dApp.h"
#include "Vertex.h"
#include "Effects.h"
#include "Camera.h"
#ifndef CROSSHAIR_H
#define CROSSHAIR_H

class Camera;
class Crosshair
{
public:
	Crosshair(ID3D11Device* device);
	~Crosshair();


	void Draw(ID3D11DeviceContext* dc, Camera cam,float viewWidth, float viewHeight);

private:
	ID3D11Buffer* mCrosshairVB;
	ID3D11Buffer* mCrosshairIB;
	ID3DX11EffectTechnique* mTech;

    XMMATRIX Scale;
	XMMATRIX Translation;
    XMMATRIX World;
	XMMATRIX WVP;


	XMFLOAT4X4 mWorld;
	XMFLOAT4X4 mView;
	XMFLOAT4X4 mProj;
	ID3D11ShaderResourceView* mSRVMap;
};

#endif // CROSSHAIR_H


