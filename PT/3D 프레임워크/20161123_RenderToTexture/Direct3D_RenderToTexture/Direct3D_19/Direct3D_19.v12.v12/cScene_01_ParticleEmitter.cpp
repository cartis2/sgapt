#include "stdafx.h"
#include "cScene_01_ParticleEmitter.h"
#include "cCamera.h"
#include "cParticleEmitter.h"

cScene_01_ParticleEmitter::cScene_01_ParticleEmitter()
{
}


cScene_01_ParticleEmitter::~cScene_01_ParticleEmitter()
{
}


HRESULT cScene_01_ParticleEmitter::Scene_Init()
{
	m_pParticle = new cParticleEmitter();

	m_pParticle->SetActive(true);

	//
	// 레이져 셋팅
	//

	//
	//배열을 2 개이상
	//VEC_COLOR colors;
	//colors.push_back( D3DXCOLOR( 0.1f, 1.0f, 1.0f, 1.0f ) );
	//colors.push_back( D3DXCOLOR( 0.1f, 1.0f, 1.0f, 1.0f ) );
	//colors.push_back( D3DXCOLOR( 0.1f, 1.0f, 1.0f, 1.0f ) );

	//VEC_SCALE scales;
	//scales.push_back( 1.0f );
	//scales.push_back( 1.0f );
	//scales.push_back( 1.0f );

	//LPDIRECT3DTEXTURE9 pTex = RESOURCE_TEXTURE->GetResource(
	//"../../Resources/Testures/particle_0.png" );

	//파티클 랜더러 셋팅
	//m_pParticle->Init(
	//1000,				//최대 파티클 수
	//200.0f,				//초당 파티클 발생 량
	//5,					//하나의 파티클 입자 라이프 최소값
	//5,					//하나의 파티클 입자 라이프 최대값
	//D3DXVECTOR3(  0, 0, 5 ),	//파티클 입자 속도 최소값 ( 로컬기준 )
	//D3DXVECTOR3(  0, 0, 5 ),	//파티클 입자 속도 최대값 ( 로컬기준 )
	//D3DXVECTOR3(  0, 0, 0 ),	//파티클 입자 가속 최소값 ( 로컬기준 )
	//D3DXVECTOR3(  0, 0, 0 ), //파티클 입자 가속 최대값 ( 로컬기준 )
	//colors,				//컬러 배열
	//scales,				//스케일 배열
	//1.0f,				//입자크기 최소값
	//1.0f,				//최대값
	//pTex,				//텍스쳐
	//true );
	//

	//
	// 간지 셋팅
	//
	
	//배열을 2 개이상
	VEC_COLOR colors;
	colors.push_back( D3DXCOLOR( 0.1f, 1.0f, 1.0f, 1.0f ) );
	colors.push_back( D3DXCOLOR( 0.1f, 1.0f, 1.0f, 1.0f ) );
	colors.push_back( D3DXCOLOR( 0.1f, 1.0f, 1.0f, 1.0f ) );
	colors.push_back( D3DXCOLOR( 0.1f, 1.0f, 1.0f, 0.9f ) );
	colors.push_back( D3DXCOLOR( 0.1f, 1.0f, 1.0f, 0.1f ) );
	colors.push_back( D3DXCOLOR( 0.1f, 1.0f, 1.0f, 0.0f ) );

	VEC_SCALE scales;
	scales.push_back( 3.0f );
	scales.push_back( 1.0f );
	scales.push_back( 1.0f );
	scales.push_back( 0.5f );
	scales.push_back( 0.1f );

	LPDIRECT3DTEXTURE9 pTex = RESOURCE_TEXTURE->GetResource(
	"../../Resources/Testures/particle_0.png" );

	//파티클 랜더러 셋팅
	m_pParticle->Init(
	1000,				//최대 파티클 수
	200.0f,				//초당 파티클 발생 량
	3,					//하나의 파티클 입자 라이프 최소값
	5,					//하나의 파티클 입자 라이프 최대값
	D3DXVECTOR3(  0, 0, 0 ),	//파티클 입자 속도 최소값 ( 로컬기준 )
	D3DXVECTOR3(  0, 0, 0 ),	//파티클 입자 속도 최대값 ( 로컬기준 )
	D3DXVECTOR3(  1, 1, 1 ),	//파티클 입자 가속 최소값 ( 로컬기준 )
	D3DXVECTOR3(  -1, -1, -1 ), //파티클 입자 가속 최대값 ( 로컬기준 )
	colors,				//컬러 배열
	scales,				//스케일 배열
	0.1f,				//입자크기 최소값
	0.2f,				//최대값
	pTex,				//텍스쳐
	false );
	


	//
	// 화염 방사기
	//
	//
	//VEC_COLOR colors;
	//colors.push_back( D3DXCOLOR( 0.0f, 0.0f, 1.0f, 0.0f ) );
	//colors.push_back( D3DXCOLOR( 1.0f, 0.0f, 1.0f, 0.5f ) );
	//colors.push_back( D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
	//colors.push_back( D3DXCOLOR( 0.0f, 1.0f, 1.0f, 1.0f ) );
	//colors.push_back( D3DXCOLOR( 0.0f, 1.0f, 1.0f, 1.0f ) );
	//colors.push_back( D3DXCOLOR( 1.0f, 1.0f, 0.0f, 1.0f ) );
	//colors.push_back( D3DXCOLOR( 1.0f, 1.0f, 0.0f, 0.0f ) );


	//VEC_SCALE scales;
	//scales.push_back( 0.0f );
	//scales.push_back( 0.1f );
	//scales.push_back( 0.3f );
	//scales.push_back( 0.8f );
	//scales.push_back( 1.0f );
	//scales.push_back( 1.5f );

	//LPDIRECT3DTEXTURE9 pTex = RESOURCE_TEXTURE->GetResource(
	//"../../Resources/Testures/FireExplosionBlurredGray.png" );

	////파티클 랜더러 셋팅
	//m_pParticle->Init(
	//1000,
	//100.0f,
	//3,
	//3.5f,
	//D3DXVECTOR3(  0, 0, 3 ),
	//D3DXVECTOR3(  0, 0, 3 ),
	//D3DXVECTOR3(  0, 0.2f, -0.5f ),
	//D3DXVECTOR3(  0, 0.4f, -1.0f ),
	//colors,
	//scales,
	//2.3f,
	//3.0f,
	//pTex
	//);
	//

	//
	// 폭팔
	//

	////배열을 2 개이상 
	//VEC_COLOR colors;
	//colors.push_back(D3DXCOLOR(0.1f, 1.0f, 1.0f, 1.0f));
	//colors.push_back(D3DXCOLOR(0.1f, 1.0f, 1.0f, 1.0f));
	//colors.push_back(D3DXCOLOR(0.1f, 1.0f, 1.0f, 1.0f));
	//colors.push_back(D3DXCOLOR(0.1f, 1.0f, 1.0f, 0.9f));
	//colors.push_back(D3DXCOLOR(0.1f, 1.0f, 1.0f, 0.1f));
	//colors.push_back(D3DXCOLOR(0.1f, 1.0f, 1.0f, 0.0f));

	//VEC_SCALE scales;
	//scales.push_back(0.1f);
	//scales.push_back(0.5f);
	//scales.push_back(1.0f);
	//scales.push_back(2.5f);
	//scales.push_back(3.1f);

	//LPDIRECT3DTEXTURE9 pTex = RESOURCE_TEXTURE->GetResource(
	//	"../../Resources/Testures/particle_0.png");

	////파티클 랜더러 셋팅
	//m_pParticle->Init(
	//	1000,				//최대 파티클 수
	//	200.0f,				//초당 파티클 발생 량
	//	3,					//하나의 파티클 입자 라이프 최소값
	//	5,					//하나의 파티클 입자 라이프 최대값
	//	D3DXVECTOR3(0, 0, 0),	//파티클 입자 속도 최소값 ( 로컬기준 )
	//	D3DXVECTOR3(0, 0, 0),	//파티클 입자 속도 최대값 ( 로컬기준 )
	//	D3DXVECTOR3(1, 1, 1),	//파티클 입자 가속 최소값 ( 로컬기준 )
	//	D3DXVECTOR3(-1, -1, -1), //파티클 입자 가속 최대값 ( 로컬기준 )
	//	colors,				//컬러 배열
	//	scales,				//스케일 배열
	//	1.1f,				//입자크기 최소값
	//	3.2f,				//최대값
	//	pTex,				//텍스쳐
	//	false);


	return S_OK;
}

void cScene_01_ParticleEmitter::Scene_Release()
{
	m_pParticle->Release();
	SAFE_DELETE(m_pParticle);
}

void cScene_01_ParticleEmitter::Scene_Update(float timeDelta)
{
	m_pParticle->Update(timeDelta);
	m_pParticle->pTransform->DefaultControl2(timeDelta);

	if (KEY_MGR->IsStayDown(VK_SPACE))
		m_pParticle->StartEmission();
	else
		m_pParticle->StopEmission();

	if (KEY_MGR->IsOnceDown(VK_RETURN))
		m_pParticle->Burst(100, 1.4f, 2.7f, 0.1f, 0.5f);
}

void cScene_01_ParticleEmitter::Scene_Render1()
{
	m_pParticle->Render();
	m_pParticle->pTransform->RenderGimozo(Device);
}


void cScene_01_ParticleEmitter::Scene_RenderSprite()
{

}