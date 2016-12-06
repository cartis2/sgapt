#pragma once
#include <fstream>

// �ε��� ����ü
struct TERRAININDEX
{
	DWORD		_0;
	DWORD		_1;
	DWORD		_2;
};

class cTerrain
{
private:
	LPDIRECT3DVERTEXBUFFER9				vertexBuf;
	LPDIRECT3DINDEXBUFFER9				indexBuf;
																   
	float								fCellScale;				// ���� ����
																   
	int									vertexNumX;				// ���� ������
	int									vertexNumZ;				// ���� ������
	int									vertexTotal;			// �� ������
																   
	int									cellNumX;				// ���� ����
	int									cellNumZ;				// ���� ����
	int									cellTotal;			    // �� ����
	int									triangleTotal;		    // �ﰢ�� ����
																   								   
	float								fTerrainSizeZ;			// �ͷ��� ���� ������
	float								fTerrainSizeX;			// �ͷ��� ���� ������
																   
	D3DXVECTOR3* 				        vertexPos;			    // ���� ��ġ
	D3DXVECTOR3*                        vertexNormal;           // ���� ��ְ�   
	D3DXVECTOR2*                        TexturePos;             // �ؽ��� ��ġ
	TERRAININDEX*                       pIndexData;             // �ε��� ����
	ST_PNT_VERTEX*                      vertex;                 // �������� ����
	LPDIRECT3DTEXTURE9                  pTexture;               // �ؽ���

	// �׽�Ʈ
	vector<int> HeightVertex;

public:
	cTerrain(void);
	~cTerrain(void);

	HRESULT Init(int vertexNum, float cellSize);
	void Release();
	void Render();

	void TextrueSetup(char* TextureName);

	// �׽�Ʈ
	void ReadRawFile(char* fileName);
};