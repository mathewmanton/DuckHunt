#include "d3dUtil.h"
#include "d3dApp.h"
#include "Vertex.h"
#include "Effects.h"
#include "Camera.h"
#include "RenderStates.h"
#ifndef CROSSHAIR_H
#define CROSSHAIR_H

//class Camera;
class Crosshair
{
public:
	Crosshair(ID3D11Device* device);
	~Crosshair();


	void Draw(ID3D11DeviceContext* dc, const Camera& cam,float viewWidth, float viewHeight);

private:
	ID3D11Buffer* mCrosshairVB;
	ID3D11Buffer* mCrosshairIB;
	ID3DX11EffectTechnique* mTech;




	XMFLOAT4X4 mWorld;
	XMFLOAT4X4 mView;
	XMFLOAT4X4 mProj;
};

#endif // CROSSHAIR_H


