#include "StdAfx.h"
#include "cObjLoader.h"
#include "cMtlTex.h"

cObjLoader::cObjLoader(void)
{
}

cObjLoader::~cObjLoader(void)
{
}

LPD3DXMESH cObjLoader::Load(char* szPath, vector<cMtlTex*>& vecMtlTex, vector<D3DXVECTOR3>& vertex, D3DXMATRIXA16* pmat /*= NULL*/)
{
	vector<D3DXVECTOR3>	vecV;
	vector<D3DXVECTOR3>	vecVN;
	vector<D3DXVECTOR2>	vecVT;
	vector<ST_PNT_VERTEX> vecVertex;
	vector<DWORD> vecAttr;
	string sMtlName;

	FILE* fp = NULL;

	fopen_s(&fp, szPath, "r");

	while (!feof(fp))
	{
		char szBuf[1024] = { '\0', };
		fgets(szBuf, 1024, fp);

		if (strlen(szBuf) == 0) continue;
		else if (szBuf[0] == '#') continue;
		else if (szBuf[0] == 'm')
		{
			char szMtlPath[1024];
			sscanf_s(szBuf, "%*s %s", szMtlPath, 1024);
			LoadMtlLib(szMtlPath, vecMtlTex);
		}
		else if (szBuf[0] == 'u')
		{
			char szMtlName[1024];
			sscanf_s(szBuf, "%*s %s", szMtlName, 1024);
			sMtlName = string(szMtlName);
		}
		else if (szBuf[0] == 'g')
		{

		}
		else if (szBuf[0] == 'v')
		{
			if (szBuf[1] == 't')
			{
				float u, v;
				sscanf_s(szBuf, "%*s %f %f %*f", &u, &v);
				vecVT.push_back(D3DXVECTOR2(u, v));
			}
			else if (szBuf[1] == 'n')
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
			else
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (szBuf[0] == 'f')
		{
			int aIndex[3][3];
			sscanf_s(szBuf, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&aIndex[0][0], &aIndex[0][1], &aIndex[0][2],
				&aIndex[1][0], &aIndex[1][1], &aIndex[1][2],
				&aIndex[2][0], &aIndex[2][1], &aIndex[2][2]);

			for (int i = 0; i < 3; ++i)
			{
				ST_PNT_VERTEX v;
				v.p =  vecV[aIndex[i][0] - 1];
				v.t = vecVT[aIndex[i][1] - 1];
				v.n = vecVN[aIndex[i][2] - 1];
				if (pmat)
				{
					D3DXVec3TransformCoord(&v.p, &v.p, pmat);
					D3DXVec3TransformNormal(&v.n, &v.n, pmat);
				}
				vecVertex.push_back(v);
				vertex.push_back(v.p);
			}

			vecAttr.push_back(m_mapMtlTex[sMtlName]->GetAttrID());
		}
	}

	fclose(fp);

	LPD3DXMESH pMesh = NULL;
	D3DXCreateMeshFVF(vecVertex.size() / 3,
		vecVertex.size(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		ST_PNT_VERTEX::FVF,
		g_pD3DDevice,
		&pMesh);

	ST_PNT_VERTEX* pV = NULL;
	pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	pMesh->UnlockVertexBuffer();

	DWORD* pI = NULL;
	pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	for (size_t i = 0; i < vecVertex.size(); ++i) { pI[i] = i;}
	pMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	pMesh->LockAttributeBuffer(0, &pA);
	memcpy(pA, &vecAttr[0], vecAttr.size() * sizeof(DWORD));
	pMesh->UnlockAttributeBuffer();

	vector<DWORD> vecAdj(pMesh->GetNumFaces() * 3);
	pMesh->OptimizeInplace(
		D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,
		&vecAdj[0],
		NULL, NULL, NULL);

	return pMesh;
}

void cObjLoader::LoadMtlLib(char* szPath, vector<cMtlTex*>& vecMtlTex)
{
	m_mapMtlTex.clear();

	FILE* fp = NULL;
	string sMtlName;

	fopen_s(&fp, szPath, "r");

	while (!feof(fp))
	{
		char szBuf[1024];
		fgets(szBuf, 1024, fp);
	
		if (szBuf[0] == '#') continue;
		else if (szBuf[0] == 'n')
		{
			char szMtlName[1024];
			sscanf_s(szBuf, "%*s %s", szMtlName, 1024);
			sMtlName = string(szMtlName);

			m_mapMtlTex[sMtlName] = new cMtlTex;
			m_mapMtlTex[sMtlName]->SetAttrID(vecMtlTex.size());
			vecMtlTex.push_back(m_mapMtlTex[sMtlName]);
		}
		else
		{
			if (szBuf[1] == 'K')
			{
				D3DMATERIAL9& stMtl = m_mapMtlTex[sMtlName]->GetMtl();
				float r, g, b;
				if (szBuf[2] == 'a')
				{
					sscanf_s(szBuf, "%*s %f %f %f", &r, &g, &b);
					stMtl.Ambient = D3DXCOLOR(r, g, b, 1.0f);
				}
				else if (szBuf[2] == 'd')
				{
					sscanf_s(szBuf, "%*s %f %f %f", &r, &g, &b);
					stMtl.Diffuse = D3DXCOLOR(r, g, b, 1.0f);
				}
				else if (szBuf[2] == 's')
				{
					sscanf_s(szBuf, "%*s %f %f %f", &r, &g, &b);
					stMtl.Specular = D3DXCOLOR(r, g, b, 1.0f);
				}
			}
			else if (szBuf[1] == 'm')
			{
				char TextureName[1024];
				string sFileName, sFolder;
				sscanf_s(szBuf, "%*s %s", TextureName, 1024);

				sFolder = "./Test/Texture/";
				sFileName = TextureName;
				string sFullPath = sFolder + sFileName;

				m_mapMtlTex[sMtlName]->SetTexture(g_pTextureManager->GetTexture(sFullPath));
			}
		}
	}

	fclose(fp);
}