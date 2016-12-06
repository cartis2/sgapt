#include "stdAfx.h"
#include "cCrtController.h"

cCrtController::cCrtController(void)
	//: m_vPosition(5, 0, 0)
	: m_vPosition(-10, 4, 0)
	, m_vDirection(0, 0, 1)
	, m_fSpeed(0.2f)
	, m_fAngle(0.0f)
{
}

cCrtController::~cCrtController(void)
{
}

void cCrtController::Setup(vector<D3DXVECTOR3> vertex)
{
	for (size_t i = 0; i < vertex.size(); i++)
		m_vecVertex.push_back(vertex[i]);

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matT;
}

void cCrtController::Update()
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) m_fAngle -= 0.1f;
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))  m_fAngle += 0.1f;
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationY(&matR, m_fAngle);
	D3DXVec3TransformNormal(&m_vDirection, &D3DXVECTOR3(0, 0, 1), &matR);	
	vPosition = m_vPosition;

	if (KEYMANAGER->isStayKeyDown(VK_UP))   vPosition = m_vPosition - (m_vDirection * m_fSpeed);
	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) vPosition = m_vPosition + (m_vDirection * m_fSpeed);

	if (!GetHeight(vPosition.x, vPosition.y, vPosition.z)) m_vPosition = vPosition;
	
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matR * matT;

	RayY[1].p = m_vPosition;
	RayY[1].c = RGB(0, 255, 0);

	RayX[0].p = m_vPosition;
	RayX[0].c = RGB(0, 0, 255);
	RayX[1].p = D3DXVECTOR3(m_vPosition.x - m_vDirection.x, m_vPosition.y - m_vDirection.y, m_vPosition.z - m_vDirection.z);
	RayX[1].c = RGB(0, 0, 255);

	if (KEYMANAGER->isOnceKeyDown('3')) m_vPosition =  D3DXVECTOR3(-10, 4, 0);

	// ���� ��ư
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE)) PostMessage(g_hWnd, WM_DESTROY, NULL, NULL);
}

bool cCrtController::GetHeight(IN float x, OUT float& y, IN float z)
{
	D3DXVECTOR3 vRayPos(x, y + 0.5f, z);
	//D3DXVECTOR3 vRayPos(x, y + 1.5f, z);
	D3DXVECTOR3 vRayDir(0, -1, 0);
	float dist = 0.f;

	RayY[0].p = vRayPos;
	RayY[0].c = RGB(0, 255, 0);

	float u, v, d;
	for (size_t i = 0; i < m_vecVertex.size(); i += 3)
	{
		D3DXVECTOR3 v0 = m_vecVertex[i];
		D3DXVECTOR3 v1 = m_vecVertex[i + 1];
		D3DXVECTOR3 v2 = m_vecVertex[i + 2];
		if (D3DXIntersectTri(&v0, &v1, &v2, &vRayPos, &vRayDir, &u, &v, &d))
		{ 
			dist = vRayPos.y - d;
			if (EPSILON < dist && dist < vRayPos.y)
			{
				m_vPosition.x = vPosition.x;
				m_vPosition.z = vPosition.z;
				m_vPosition.y = dist;
			}
			return true;
		}
	}

	//y = y;
	return false;
}

void cCrtController::RayRender()
{
	D3DXMATRIXA16 world;
	D3DXMatrixIdentity(&world);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &world);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, 2, &RayY[0], sizeof(ST_PC_VERTEX));
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, 2, &RayX[0], sizeof(ST_PC_VERTEX));

	//char str[256];
	//sprintf_s(str, "%f", m_vPosition.x);
	//SetWindowText(g_hWnd, str);
}

// D3DXIntersectTri
// (�˻��ϴ� �ﰢ�� ����1, �˻��ϴ� �ﰢ�� ����2, �˻��ϴ� �ﰢ�� ����3,
//  Ray��ġ, Ray����, )

// ��ǥ �� �ʿ��� ��Ȳ
// 1. �����Ȳ
// 2. ����ֿ� ������ �Ұ��ΰ�
// 3. �����ϴ°ſ� ���ϴ� ������
// 4. ���±��� �۾��� Ŀ�� �α�
// 5. ������ �����ڷ�

// �ٿ���ڽ� �浹�ȵǴ� �κп� ����
// true�������� vector�� ��Ƽ� ���̰� ���ϸ鼭 �浹
// 2���̸� 2���� ó��