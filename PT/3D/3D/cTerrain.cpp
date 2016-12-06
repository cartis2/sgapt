#include "stdAfx.h"
#include "cTerrain.h"

cTerrain::cTerrain(void)
{
}

cTerrain::~cTerrain(void)
{
}

//�ʱ�ȭ 
HRESULT cTerrain::Init(int vertexNum, float cellSize)
{
	//������ 
	vertexNumX = vertexNum;
	vertexNumZ = vertexNum;
	vertexTotal = vertexNumX * vertexNumZ;

	//����
	cellNumX = vertexNumX - 1;
	cellNumZ = vertexNumZ - 1;
	cellTotal = cellNumX * cellNumZ;

	//��������
	fCellScale = cellSize;

	//�ﰢ�� ����
	triangleTotal = cellTotal * 2;

	//�ͷ��� ������
	fTerrainSizeX = cellNumX * cellSize;
	fTerrainSizeZ = cellNumZ * cellSize;

	// �ͷ��� ���� ����
	// ���� ����� ���� ��ġ, �ؽ��� ��ġ, ���� ��ְ� �����Ҵ�
	vertexPos =    new D3DXVECTOR3[vertexTotal];
	vertexNormal = new D3DXVECTOR3[vertexTotal];
	TexturePos =   new D3DXVECTOR2[vertexTotal];
	vertex =       new ST_PNT_VERTEX[vertexTotal];
	
	// ���� ��ġ ����
	D3DXVECTOR3 starPos(-125, 0, -125);

	for (int z = 0; z < vertexNumZ; z++)
	{
		for (int x = 0; x < vertexNumX; x++)
		{
			// ���� �ε���
			int Idx = z * vertexNumX + x;

			// ���� ��ġ
			vertexPos[Idx].x = starPos.x + (x * fCellScale);
			vertexPos[Idx].z = starPos.z + (z * fCellScale);
			vertexPos[Idx].y = starPos.y + (HeightVertex[Idx] / 6);
			
			// ���� ��ְ�
			vertexNormal[Idx].x = vertexPos[Idx].x;
			vertexNormal[Idx].z = vertexPos[Idx].z;
			vertexNormal[Idx].y = vertexPos[Idx].y;

			// �ؽ��� ��ġ
			TexturePos[Idx].x = starPos.x + (x * fCellScale) / vertexNumX;
			TexturePos[Idx].y = starPos.y + (z * fCellScale) / vertexNumZ;
			
			vertex[Idx].p = vertexPos[Idx];
			vertex[Idx].n = vertexNormal[Idx];
			vertex[Idx].t = TexturePos[Idx];
		}
	}

	// ���� �ε���
	pIndexData = new TERRAININDEX[triangleTotal]; // �ﰢ�� ������ŭ �Ҵ�

	// ���� �ʱ�ȭ
	for (int z = 0; z < cellNumZ; z++)
	{
		// ���� ��
		int nowZ  = z;
		int nextZ = z + 1;

		for (int x = 0; x < cellNumX; x++)
		{
			// ���� ���� ��
			int nowX  = x;
			int nextX = x + 1;

			// �𼭸� ���� �ε���
			DWORD LeftTop     = nextZ * vertexNumX + nowX;
			DWORD RightTop    = nextZ * vertexNumX + nextX;
			DWORD LeftBottom  = nowZ  * vertexNumX + nowX;
			DWORD RightBottom = nowZ  * vertexNumX + nextX;

			// �ﰢ�� �ε��� �迭 ����
			int Idx = (z * cellNumX + x) * 2;

			// �ﰢ��1
			pIndexData[Idx]._0 = LeftBottom;
			pIndexData[Idx]._1 = LeftTop;
			pIndexData[Idx]._2 = RightTop;

			// �ﰢ��2
			pIndexData[Idx + 1]._0 = LeftBottom;
			pIndexData[Idx + 1]._1 = RightTop;
			pIndexData[Idx + 1]._2 = RightBottom;
		}
	}

	// ���� ����
	g_pD3DDevice->CreateVertexBuffer(sizeof(ST_PNT_VERTEX) * vertexTotal, D3DUSAGE_WRITEONLY,
		0, D3DPOOL_DEFAULT, &vertexBuf, 0);
	
	ST_PNT_VERTEX* pVertex = NULL;
	vertexBuf->Lock(0, 0, (void**)&pVertex, 0);
	memcpy_s(pVertex, sizeof(ST_PNT_VERTEX) * vertexTotal, vertex, sizeof(ST_PNT_VERTEX) * vertexTotal);
	vertexBuf->Unlock();


	// �ε��� ����
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
	// ���̾������� ���
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//���� ��� �ϴ� �ʱ�ȭ
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->SetTexture(0, pTexture);

	// SetStreamSource : ���� ������ ����ִ� �������۸� ���
	g_pD3DDevice->SetStreamSource(0, vertexBuf, 0, sizeof(ST_PNT_VERTEX));


	// SetIndices : �ε��� ������ ����ִµ� �ε������۸� ���
	g_pD3DDevice->SetIndices(indexBuf);

	// DrawIndexedPrimitive(���� Ÿ��, �ε��� ������ ���� �ε���, ���ؽ� ������ ���� �ε���, 
	//                      ���ؽ� ���� ����, �ε��� ������ ���� �ε���, ������ ����)
	g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0,
		                               vertexTotal, 0, triangleTotal);


	// �⺻ ������ ���
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