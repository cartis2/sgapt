#include "stdafx.h"
#include "cScene_00_PointParticle.h"
#include "cCamera.h"

cScene_00_PointParticle::cScene_00_PointParticle()
{
}


cScene_00_PointParticle::~cScene_00_PointParticle()
{
}

HRESULT cScene_00_PointParticle::Scene_Init()
{
	m_ParticleVertex[0].pos = D3DXVECTOR3(-3, 0, 0);
	m_ParticleVertex[1].pos = D3DXVECTOR3(0, 0, 0);
	m_ParticleVertex[2].pos = D3DXVECTOR3(3, 0, 0);
	m_ParticleVertex[0].size = 2.0f;
	m_ParticleVertex[1].size = 2.0f;
	m_ParticleVertex[2].size = 2.0f;

	//정점에 컬러 먹였다....
	m_ParticleVertex[0].color = 0xffff0000;
	m_ParticleVertex[1].color = 0xff00ff00;
	m_ParticleVertex[2].color = 0xffffffff;

	//Patricle 에 사용될 Texture 로딩
	m_pTexture = RESOURCE_TEXTURE->GetResource("../../Resources/Testures/alpha.png");

	return S_OK;
}

void cScene_00_PointParticle::Scene_Release()
{
	
}

void cScene_00_PointParticle::Scene_Update(float timeDelta)
{

}

void cScene_00_PointParticle::Scene_Render1()
{
	Device->SetRenderState(D3DRS_LIGHTING, false);						//라이팅을 끈다.
	Device->SetRenderState(D3DRS_POINTSPRITEENABLE, true);				//포인트 스플라이트 활성화
	Device->SetRenderState(D3DRS_POINTSCALEENABLE, true);				//포인트의 스케일값 먹이겠다. FVF 에 D3DFVF_PSIZE 있는경우
	Device->SetRenderState(D3DRS_POINTSIZE_MIN, FloatToDWORD(0.0f));	//포인트의 최소 크기 ( 화면기준 )
	Device->SetRenderState(D3DRS_POINTSIZE_MAX, FloatToDWORD(500.0f));	//포인트의 최대 크기 ( 화면기준 )

	//출력되는 POINT size 
	//finalSize = viewportHeight * pointSize *  sqrt( 1 / ( A + B(D) + C(D^2) )  );
	//아래와 같이 하면 자연스러운 거리에 따른 스케일이 나타남
	Device->SetRenderState(D3DRS_POINTSCALE_A, FloatToDWORD(0.0f));
	Device->SetRenderState(D3DRS_POINTSCALE_B, FloatToDWORD(0.0f));
	Device->SetRenderState(D3DRS_POINTSCALE_C, FloatToDWORD(1.0f));

	//Texture 의 값과 Diffuse 여기서는 정점컬러의 알파값 을 섞어 최종 출력을 한다.
	Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);

	//알파 블렌딩 셋팅
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	////다음과 같은 알파블렌딩 옵션은 일반 적인 알파블렌딩 ( 알파소팅이 필요할수 있다 )
	//Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//다음과 같은 알파블렌딩 옵션은 색을 태운다 ( 불 화염 레이져 같은거 표현 ) ( 알파소팅이 필요 없다 )
	Device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );			
	Device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
	Device->SetRenderState( D3DRS_ZWRITEENABLE, false );	//z 버퍼의 쓰기를 막는다.

	//파티클 Texture 셋팅
	Device->SetTexture(0, m_pTexture);

	//파티클 정점 출력
	Device->SetFVF(PARTICLE_VERTEX::FVF);

	//버퍼통하지 않고 바로 그린다 ( 자주움직이는 정점에 대해 쓰기편하고 좋다 )
	Device->DrawPrimitiveUP(
		D3DPT_POINTLIST,		//PT
		3,						//그릴갯수 점이 3개다
		m_ParticleVertex,		//VERTEX 배열 
		sizeof(PARTICLE_VERTEX)	//VERTEX 하나 Size 
		);


	//다시 돌려놔
	Device->SetRenderState(D3DRS_LIGHTING, true);
	Device->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	Device->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	Device->SetRenderState(D3DRS_ZWRITEENABLE, true);

}


void cScene_00_PointParticle::Scene_RenderSprite()
{

}