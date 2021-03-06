#include "StdAfx.h"
#include "cAllocateHierarchy.h"
#include "cMtlTex.h"

cAllocateHierarchy::cAllocateHierarchy(void)
{
}

cAllocateHierarchy::~cAllocateHierarchy(void)
{
}

STDMETHODIMP cAllocateHierarchy::CreateFrame(
	THIS_ LPCSTR Name,
	LPD3DXFRAME *ppNewFrame )
{
	ST_BONE* pBone = new ST_BONE;
	// TODO : 이름을 복사해주세요.
	pBone->Name = NULL;
	if(Name)
	{
		pBone->Name = new char[strlen(Name) + 1];
		strcpy(pBone->Name, Name);
	}
	
	D3DXMatrixIdentity(&pBone->CombinedTransformationMatrix);
	D3DXMatrixIdentity(&pBone->TransformationMatrix);
	pBone->pFrameFirstChild = NULL;
	pBone->pFrameSibling = NULL;
	pBone->pMeshContainer = NULL;

	*ppNewFrame = pBone;

	return S_OK;
}

STDMETHODIMP cAllocateHierarchy::CreateMeshContainer( 
	THIS_ LPCSTR Name,
	CONST D3DXMESHDATA *pMeshData, 
	CONST D3DXMATERIAL *pMaterials,
	CONST D3DXEFFECTINSTANCE *pEffectInstances,
	DWORD NumMaterials, 
	CONST DWORD *pAdjacency,
	LPD3DXSKININFO pSkinInfo,
	LPD3DXMESHCONTAINER *ppNewMeshContainer )
{
	ST_BONE_MESH* pBoneMesh = new ST_BONE_MESH;

	assert(pMeshData->Type == D3DXMESHTYPE_MESH);
	
	pBoneMesh->MeshData.pMesh = NULL;

	SAFE_ADD_REF(pMeshData->pMesh);

	// step 1. pSkinInfo 저장
	pBoneMesh->pSkinInfo = NULL;
	if(pSkinInfo)
	{
		SAFE_ADD_REF(pSkinInfo);
		pBoneMesh->pSkinInfo = pSkinInfo;
	}
	pBoneMesh->pOrigMesh = pMeshData->pMesh;

	// step 2. 원본 메쉬 복사
	pBoneMesh->pOrigMesh->CloneMeshFVF(
		pBoneMesh->pOrigMesh->GetOptions(),
		pBoneMesh->pOrigMesh->GetFVF(),
		g_pD3DDevice,
		&pBoneMesh->pWorkMesh);

	pBoneMesh->Name = NULL;
	pBoneMesh->NumMaterials = NumMaterials;
	pBoneMesh->pAdjacency = NULL;
	pBoneMesh->pEffects = NULL;
	for (DWORD i = 0; i < NumMaterials; ++i)
	{
		cMtlTex* pMtlTex = new cMtlTex;
		pMtlTex->SetMtl(pMaterials[i].MatD3D);
		std::string sFullPath = m_sFolder + "/" + std::string(pMaterials[i].pTextureFilename);
		pMtlTex->SetTexture(g_pTextureManager->GetTexture(sFullPath));
		pBoneMesh->vecMtlTex.push_back(pMtlTex);
	}
	pBoneMesh->pNextMeshContainer = NULL;

	// step 3. pSkinInfo->GetNumBones()를 통해
	// 영향력을 미치는 모든 본에 대한 매트릭스 들을 세팅
	// ppBoneMatrixPtrs, pBoneOffsetMatrices, pCurrentBoneMatrices를 동적할당
	if (pSkinInfo)
	{
		DWORD dwNumBones = pSkinInfo->GetNumBones();
		pBoneMesh->pBoneOffsetMatrices = new D3DXMATRIX[dwNumBones];
		pBoneMesh->pCurrentBoneMatrices = new D3DXMATRIX[dwNumBones];
		pBoneMesh->ppBoneMatrixPtrs = new D3DXMATRIX*[dwNumBones];

		// step 4. 동적 할당된 pBoneOffsetMatrices 매트릭스에 값 저장.
		// pSkinInfo->GetBoneOffsetMatrix(i)
		for (DWORD i = 0; i < dwNumBones; ++i)
		{
			LPD3DXMATRIX pmat = pSkinInfo->GetBoneOffsetMatrix(i);
			pBoneMesh->pBoneOffsetMatrices[i] = *pmat;
		}
	}

	*ppNewMeshContainer = pBoneMesh;
	return S_OK;
}

STDMETHODIMP cAllocateHierarchy::DestroyFrame( 
	THIS_ LPD3DXFRAME pFrameToFree )
{
	// TODO : 해제 잘 합시다.
	SAFE_DELETE_ARRAY(pFrameToFree->Name);
	SAFE_DELETE(pFrameToFree);
	
	return S_OK;
}

STDMETHODIMP cAllocateHierarchy::DestroyMeshContainer( 
	THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree )
{
	// TODO : 해제 잘 합시다.
	ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pMeshContainerToFree;
	
	SAFE_RELEASE(pBoneMesh->pOrigMesh);
	SAFE_RELEASE(pBoneMesh->pWorkMesh);

	for each(auto p in pBoneMesh->vecMtlTex)
	{
		SAFE_RELEASE(p);
	}
	pBoneMesh->vecMtlTex.clear();
	SAFE_RELEASE(pBoneMesh->pSkinInfo);
	
	SAFE_DELETE_ARRAY(pBoneMesh->pBoneOffsetMatrices);
	SAFE_DELETE_ARRAY(pBoneMesh->pCurrentBoneMatrices);
	SAFE_DELETE_ARRAY(pBoneMesh->ppBoneMatrixPtrs);

	SAFE_DELETE(pMeshContainerToFree);

	return S_OK;
}
