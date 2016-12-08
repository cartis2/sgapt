#include "stdAfx.h"
#include "cTerrain.h"

cTerrain::cTerrain(void)
{
}

cTerrain::~cTerrain(void)
{
}

//초기화 
HRESULT cTerrain::Init(int vertexNum, float cellSize)
{
	//정점수 
	vertexNumX = vertexNum;
	vertexNumZ = vertexNum;
	vertexTotal = vertexNumX * vertexNumZ;

	//셀수
	cellNumX = vertexNumX - 1;
	cellNumZ = vertexNumZ - 1;
	cellTotal = cellNumX * cellNumZ;

	//셀사이즈
	fCellScale = cellSize;

	//삼각형 갯수
	triangleTotal = cellTotal * 2;

	//터레인 사이즈
	fTerrainSizeX = cellNumX * cellSize;
	fTerrainSizeZ = cellNumZ * cellSize;

	// 터레인 정보 생성
	// 정점 수대로 정점 위치, 텍스쳐 위치, 정점 노멀값 동적할당
	vertexPos =    new D3DXVECTOR3[vertexTotal];
	vertexNormal = new D3DXVECTOR3[vertexTotal];
	TexturePos =   new D3DXVECTOR2[vertexTotal];
	vertex =       new ST_PNT_VERTEX[vertexTotal];
	
	// 시작 위치 설정
	D3DXVECTOR3 starPos(-125, 0, -125);

	for (int z = 0; z < vertexNumZ; z++)
	{
		for (int x = 0; x < vertexNumX; x++)
		{
			// 정점 인덱스
			int Idx = z * vertexNumX + x;

			// 정점 위치
			vertexPos[Idx].x = starPos.x + (x * fCellScale);
			vertexPos[Idx].z = starPos.z + (z * fCellScale);
			vertexPos[Idx].y = starPos.y + (HeightVertex[Idx] / 6);
			
			// 정점 노멀값
			vertexNormal[Idx].x = vertexPos[Idx].x;
			vertexNormal[Idx].z = vertexPos[Idx].z;
			vertexNormal[Idx].y = vertexPos[Idx].y;

			// 텍스쳐 위치
			TexturePos[Idx].x = starPos.x + (x * fCellScale) / vertexNumX;
			TexturePos[Idx].y = starPos.y + (z * fCellScale) / vertexNumZ;
			
			vertex[Idx].p = vertexPos[Idx];
			vertex[Idx].n = vertexNormal[Idx];
			vertex[Idx].t = TexturePos[Idx];
		}
	}

	// 정점 인덱스
	pIndexData = new TERRAININDEX[triangleTotal]; // 삼각형 개수만큼 할당

	// 정점 초기화
	for (int z = 0; z < cellNumZ; z++)
	{
		// 수평 선
		int nowZ  = z;
		int nextZ = z + 1;

		for (int x = 0; x < cellNumX; x++)
		{
			// 현재 수직 선
			int nowX  = x;
			int nextX = x + 1;

			// 모서리 정점 인덱스
			DWORD LeftTop     = nextZ * vertexNumX + nowX;
			DWORD RightTop    = nextZ * vertexNumX + nextX;
			DWORD LeftBottom  = nowZ  * vertexNumX + nowX;
			DWORD RightBottom = nowZ  * vertexNumX + nextX;

			// 삼각형 인덱스 배열 설정
			int Idx = (z * cellNumX + x) * 2;

			// 삼각형1
			pIndexData[Idx]._0 = LeftBottom;
			pIndexData[Idx]._1 = LeftTop;
			pIndexData[Idx]._2 = RightTop;

			// 삼각형2
			pIndexData[Idx + 1]._0 = LeftBottom;
			pIndexData[Idx + 1]._1 = RightTop;
			pIndexData[Idx + 1]._2 = RightBottom;
		}
	}

	// 정점 버퍼
	g_pD3DDevice->CreateVertexBuffer(sizeof(ST_PNT_VERTEX) * vertexTotal, D3DUSAGE_WRITEONLY,
		0, D3DPOOL_DEFAULT, &vertexBuf, 0);
	
	ST_PNT_VERTEX* pVertex = NULL;
	vertexBuf->Lock(0, 0, (void**)&pVertex, 0);
	memcpy_s(pVertex, sizeof(ST_PNT_VERTEX) * vertexTotal, vertex, sizeof(ST_PNT_VERTEX) * vertexTotal);
	vertexBuf->Unlock();


	// 인덱스 버퍼
	g_pD3DDevice->CreateIndexBuffer(sizeof(TERRAININDEX) * triangleTotal, D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX32, D3DPOOL_DEFAULT, &indexBuf, NULL);

	void* pIndex = NULL;
	indexBuf->Lock(0, 0, &pIndex, 0);
	memcpy(pIndex, pIndexData, sizeof(TERRAININDEX) * triangleTotal);
	memcpy_s(pIndex, sizeof(TERRAININDEX) * triangleTotal, pIndexData, sizeof(TERRAININDEX) * triangleTotal);

	indexBuf->Unlock();

	return S_OK;
}

void cTerrain::Release()
{
	SAFE_DELETE_ARRAY(vertexPos);
	SAFE_DELETE_ARRAY(vertexNormal);
	SAFE_DELETE_ARRAY(TexturePos);
	SAFE_DELETE_ARRAY(vertex);
	SAFE_DELETE_ARRAY(pIndexData);

	SAFE_RELEASE(pTexture);
	SAFE_RELEASE(vertexBuf);
	SAFE_RELEASE(indexBuf);
}

void cTerrain::Render()
{
	// 와이어프레임 출력
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//월드 행렬 일단 초기화
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->SetTexture(0, pTexture);

	// SetStreamSource : 정점 정보가 담겨있는 정점버퍼를 사용
	g_pD3DDevice->SetStreamSource(0, vertexBuf, 0, sizeof(ST_PNT_VERTEX));


	// SetIndices : 인덱스 정보가 담겨있는데 인덱스버퍼를 사용
	g_pD3DDevice->SetIndices(indexBuf);

	// DrawIndexedPrimitive(도형 타입, 인덱스 버퍼의 시작 인덱스, 버텍스 버퍼의 시작 인덱스, 
	//                      버텍스 버퍼 개수, 인덱스 버퍼의 시작 인덱스, 도형의 개수)
	g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0,
		                               vertexTotal, 0, triangleTotal);


	// 기본 면으로 출력
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void cTerrain::ReadRawFile(char* fileName)
{
	int size = 256 * 256;

	vector<BYTE> In(size);
	ifstream InFile(fileName, ios_base::binary);
	InFile.read(
		(char*)&In[0], In.size());

	InFile.close();

	HeightVertex.resize(size);
	for (int i = 0; i < In.size(); i++)
		HeightVertex[i] = In[i];
}

void cTerrain::TextrueSetup(char* TextureName)
{
	pTexture = NULL;
	D3DXCreateTextureFromFile(g_pD3DDevice, TextureName, &pTexture);
}