#pragma once
#include <fstream>

// 인덱스 구조체
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
																   
	float								fCellScale;				// 셀의 간격
																   
	int									vertexNumX;				// 가로 정점수
	int									vertexNumZ;				// 깊이 정점수
	int									vertexTotal;			// 총 정점수
																   
	int									cellNumX;				// 가로 셀수
	int									cellNumZ;				// 깊이 셀수
	int									cellTotal;			    // 총 셀수
	int									triangleTotal;		    // 삼각형 갯수
																   								   
	float								fTerrainSizeZ;			// 터레인 가로 사이즈
	float								fTerrainSizeX;			// 터레인 세로 사이즈
																   
	D3DXVECTOR3* 				        vertexPos;			    // 정점 위치
	D3DXVECTOR3*                        vertexNormal;           // 정점 노멀값   
	D3DXVECTOR2*                        TexturePos;             // 텍스쳐 위치
	TERRAININDEX*                       pIndexData;             // 인덱스 정보
	ST_PNT_VERTEX*                      vertex;                 // 최종적인 정점
	LPDIRECT3DTEXTURE9                  pTexture;               // 텍스쳐

	// 테스트
	vector<int> HeightVertex;

public:
	cTerrain(void);
	~cTerrain(void);

	HRESULT Init(int vertexNum, float cellSize);
	void Release();
	void Render();

	void TextrueSetup(char* TextureName);

	// 테스트
	void ReadRawFile(char* fileName);
};