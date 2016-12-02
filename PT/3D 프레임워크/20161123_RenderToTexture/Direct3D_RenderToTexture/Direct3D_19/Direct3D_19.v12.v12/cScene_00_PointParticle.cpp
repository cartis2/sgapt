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

	//������ �÷� �Կ���....
	m_ParticleVertex[0].color = 0xffff0000;
	m_ParticleVertex[1].color = 0xff00ff00;
	m_ParticleVertex[2].color = 0xffffffff;

	//Patricle �� ���� Texture �ε�
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
	Device->SetRenderState(D3DRS_LIGHTING, false);						//�������� ����.
	Device->SetRenderState(D3DRS_POINTSPRITEENABLE, true);				//����Ʈ ���ö���Ʈ Ȱ��ȭ
	Device->SetRenderState(D3DRS_POINTSCALEENABLE, true);				//����Ʈ�� �����ϰ� ���̰ڴ�. FVF �� D3DFVF_PSIZE �ִ°��
	Device->SetRenderState(D3DRS_POINTSIZE_MIN, FloatToDWORD(0.0f));	//����Ʈ�� �ּ� ũ�� ( ȭ����� )
	Device->SetRenderState(D3DRS_POINTSIZE_MAX, FloatToDWORD(500.0f));	//����Ʈ�� �ִ� ũ�� ( ȭ����� )

	//��µǴ� POINT size 
	//finalSize = viewportHeight * pointSize *  sqrt( 1 / ( A + B(D) + C(D^2) )  );
	//�Ʒ��� ���� �ϸ� �ڿ������� �Ÿ��� ���� �������� ��Ÿ��
	Device->SetRenderState(D3DRS_POINTSCALE_A, FloatToDWORD(0.0f));
	Device->SetRenderState(D3DRS_POINTSCALE_B, FloatToDWORD(0.0f));
	Device->SetRenderState(D3DRS_POINTSCALE_C, FloatToDWORD(1.0f));

	//Texture �� ���� Diffuse ���⼭�� �����÷��� ���İ� �� ���� ���� ����� �Ѵ�.
	Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);

	//���� ���� ����
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	////������ ���� ���ĺ��� �ɼ��� �Ϲ� ���� ���ĺ��� ( ���ļ����� �ʿ��Ҽ� �ִ� )
	//Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//������ ���� ���ĺ��� �ɼ��� ���� �¿�� ( �� ȭ�� ������ ������ ǥ�� ) ( ���ļ����� �ʿ� ���� )
	Device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );			
	Device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
	Device->SetRenderState( D3DRS_ZWRITEENABLE, false );	//z ������ ���⸦ ���´�.

	//��ƼŬ Texture ����
	Device->SetTexture(0, m_pTexture);

	//��ƼŬ ���� ���
	Device->SetFVF(PARTICLE_VERTEX::FVF);

	//���������� �ʰ� �ٷ� �׸��� ( ���ֿ����̴� ������ ���� �������ϰ� ���� )
	Device->DrawPrimitiveUP(
		D3DPT_POINTLIST,		//PT
		3,						//�׸����� ���� 3����
		m_ParticleVertex,		//VERTEX �迭 
		sizeof(PARTICLE_VERTEX)	//VERTEX �ϳ� Size 
		);


	//�ٽ� ������
	Device->SetRenderState(D3DRS_LIGHTING, true);
	Device->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	Device->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	Device->SetRenderState(D3DRS_ZWRITEENABLE, true);

}


void cScene_00_PointParticle::Scene_RenderSprite()
{

}