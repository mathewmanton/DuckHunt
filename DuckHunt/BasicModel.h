#ifndef BASICMODEL_H
#define BASICMODEL_H

#include "MeshGeometry.h"
#include "TextureMgr.h"
#include "Vertex.h"
#include "xnacollision.h"
class BasicModel
{
public:
	BasicModel(ID3D11Device* device, TextureMgr& texMgr,
		const std::string& modelFilename, const std::wstring& texturePath,
		MeshGeometry::Type type = MeshGeometry::NORMAL_DIFFUSE);
	~BasicModel();

	UINT SubsetCount;
	XNA::AxisAlignedBox collisionBox;
	std::vector<Material> Mat;
	std::vector<ID3D11ShaderResourceView*> DiffuseMapSRV;
	std::vector<ID3D11ShaderResourceView*> NormalMapSRV;

	// Keep CPU copies of the mesh data to read from.  
	std::vector<Vertex::PosNormalTexTan> Vertices;
	std::vector<Vertex::Basic32> BasicVertices;
	std::vector<USHORT> Indices;
	std::vector<MeshGeometry::Subset> Subsets;

	MeshGeometry ModelMesh;
	void CreateCollisionBox(std::vector<Vertex::Basic32> Vertices);
};

struct BasicModelInstance
{
	BasicModel* Model;
	XMFLOAT4X4 World;
};

#endif // SKINNEDMODEL_H