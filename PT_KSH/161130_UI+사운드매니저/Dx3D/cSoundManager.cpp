#include "stdAfx.h"
#include "cSoundManager.h"


cSoundManager::cSoundManager()
	:m_soundType(SOUNDNULL)
{
}

cSoundManager::~cSoundManager()
{
}
HRESULT cSoundManager::SoundInit2D(void)
{
	//���� �ý��� ����
	System_Create(&m_2Dsystem);

	//maxchannels : fomd ���� ����ϴ� �ִ� ä���� ���� ����
	//���� ä�μ� ����
	m_2Dsystem->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);



	//3d ���� ���� �ʿ�
	//m_2Dsystem->set3DSettings()
	//



	//���� , ä�� �����Ҵ�
	m_2Dsound = new FMOD::Sound *[TOTALSOUNDBUFFER];
	m_2Dchannel = new FMOD::Channel *[TOTALSOUNDBUFFER];

	//�޸� �ʱ�ȭ
	memset(m_2Dsound, 0, sizeof(FMOD::Sound*)* (TOTALSOUNDBUFFER));
	memset(m_2Dchannel, 0, sizeof(FMOD::Channel*)* (TOTALSOUNDBUFFER));

	return S_OK;
}
void cSoundManager::SoundRelease2D(void)
{
	//���� �� ä�� ����
	if (m_2Dchannel != NULL || m_2Dsound != NULL)
	{
		for (int i = 0; i < TOTALSOUNDBUFFER; i++)
		{
			if (m_2Dchannel != NULL)
			{
				if (m_2Dchannel[i]) m_2Dchannel[i]->stop();
			}

			if (m_2Dsound != NULL)
			{
				if (m_2Dsound[i]) m_2Dsound[i]->release();
			}
		}
	}

	//�޸� �����
	SAFE_DELETE(m_2Dchannel);
	SAFE_DELETE(m_2Dsound);

	//�ý��� �ݱ�
	if (m_2Dsystem != NULL)
	{
		m_2Dsystem->release();
		m_2Dsystem->close();
	}
}
void cSoundManager::SoundUpdate2D(void)
{
	/*
	���� �ý����� ��� ������Ʈ ����� ������ �ٲ�ų�
	�缺�� ���� ���带 ä�ο��� ������ �� �پ��� �۾��� �ڵ����� ���ش�
	*/
	//���ΰ��ӿ��� ����Ŵ����� ������Ʈ ���ش�
	m_2Dsystem->update();
}
//void cSoundManager::render(void)
//{
//}

//���� �߰�(Ű��, �����̸�, BGM?, ������?, 2D�� 3D��?)
void cSoundManager::addSound2D(std::string keyName, std::string soundName, bool bgm, bool loop, bool type)
{
	//type �Ű������� ������ ������ 2D(false), 3D(true)
	if (type)
	{
		//3D sound
		//3d ���� �߰�
		//m_2Dsystem->set3DSettings(1.0, 1.0, 1.0);
		//m_2Dsystem->createSound(soundName.c_str(), FMOD_3D, 0, &m_2Dsound[m_2DTotalSounds.size()]);
		//m_2Dsound[m_2DTotalSounds.size()]->set3DMinMaxDistance(0.5f, 5000.0f);
		//m_2Dsound[m_2DTotalSounds.size()]->setMode(FMOD_LOOP_NORMAL);
		//
	}
	else
	{
		//2D Sound
		if (loop)//��� or ����Ʈ
		{
			if (bgm)
			{
				//1: ���� URL�� �̸� 
				//2: ���带 ���� ���� �ɼ�	
				//3: ���带 ����ϴ� ���� �������� ������ �����ϴ� FMOD_CREATESOUNDEXINFO�� ������ , �̿ɼ��� �����Ϸ��� 0 �Ǵ� NULL�� �����ϸ� ��
				//4: FMOD::SOUND ������Ʈ�� �޴� ������ �ּ�
				m_2Dsystem->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &m_2Dsound[m_2DTotalSounds.size()]);
			}
			else
			{
				m_2Dsystem->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &m_2Dsound[m_2DTotalSounds.size()]);
			}
		}
		else  //����Ʈ
		{
			m_2Dsystem->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &m_2Dsound[m_2DTotalSounds.size()]);
		}		

		//�ʿ� ���带 Ű���� �Բ� ����ش�
		m_2DTotalSounds.insert(make_pair(keyName, &m_2Dsound[m_2DTotalSounds.size()]));
	}
	
}

//���� �÷���(Ű��, ����) 0.0f~ 1.0f
void cSoundManager::play2D(std::string keyName, float volume)
{
	int count = 0;
	arrSoundIter iter = m_2DTotalSounds.begin();
	for (iter; iter != m_2DTotalSounds.end(); count++)
	{
		if (keyName == iter->first)
		{
			//���� �÷���
			m_2Dsystem->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &m_2Dchannel[count]);
			

			////3d ���� ����
			//FMOD_VECTOR pos = { -10.0f * 0.1f, 0.0f, 0.0f };
			//FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };

			//m_2Dchannel[count]->set3DAttributes(&pos, &vel);

			////


			//��������
			m_2Dchannel[count]->setVolume(volume);
			break;
		}
	}
}
//���� ����
void cSoundManager::stop2D(std::string keyName)
{
	int count = 0;
	arrSoundIter iter = m_2DTotalSounds.begin();
	for (iter; iter != m_2DTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� ����
			m_2Dchannel[count]->stop();
			break;
		}
	}
}
//���� �Ͻ�����
void cSoundManager::pause2D(std::string keyName)
{
	int count = 0;
	arrSoundIter iter = m_2DTotalSounds.begin();
	for (iter; iter != m_2DTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� ����
			m_2Dchannel[count]->setPaused(true);
			break;
		}
	}
}
//���� �ٽ� ���
void cSoundManager::resume2D(std::string keyName)
{
	int count = 0;
	arrSoundIter iter = m_2DTotalSounds.begin();
	for (iter; iter != m_2DTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� �Ͻ�����(�ٽ����)
			m_2Dchannel[count]->setPaused(false);
			break;
		}
	}
}

//�÷��� ���̳�?
bool cSoundManager::isPlaySound2D(std::string keyName)
{
	bool isPlay;
	int count = 0;
	arrSoundIter iter = m_2DTotalSounds.begin();
	for (iter; iter != m_2DTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//�÷��� ���̳�?
			m_2Dchannel[count]->isPlaying(&isPlay);
			break;
		}
	}
	return isPlay;
}
//�Ͻ����� ���̳�?
bool cSoundManager::isPauseSound2D(std::string keyName)
{
	bool isPause;
	int count = 0;
	arrSoundIter iter = m_2DTotalSounds.begin();
	for (iter; iter != m_2DTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//�÷��� ���̳�? (�Ͻ�����)
			m_2Dchannel[count]->isPlaying(&isPause);
			break;
		}
	}
	return isPause;
}



HRESULT cSoundManager::SoundInit3D(void)
{
	System_Create(&m_3Dsystem);

	m_3Dsystem->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	//3d ���� ���� �ʿ�
	//m_3Dsystem->set3DSettings()
	//

	//���� , ä�� �����Ҵ�
	m_3Dsound = new FMOD::Sound *[TOTALSOUNDBUFFER];
	m_3Dchannel = new FMOD::Channel *[TOTALSOUNDBUFFER];

	//�޸� �ʱ�ȭ
	memset(m_3Dsound, 0, sizeof(FMOD::Sound*)* (TOTALSOUNDBUFFER));
	memset(m_3Dchannel, 0, sizeof(FMOD::Channel*)* (TOTALSOUNDBUFFER));

	return S_OK;
}
void cSoundManager::SoundRelease3D(void)
{
	//���� �� ä�� ����
	if (m_3Dchannel != NULL || m_3Dsound != NULL)
	{
		for (int i = 0; i < TOTALSOUNDBUFFER; i++)
		{
			if (m_3Dchannel != NULL)
			{
				if (m_3Dchannel[i]) m_3Dchannel[i]->stop();
			}

			if (m_3Dsound != NULL)
			{
				if (m_3Dsound[i]) m_3Dsound[i]->release();
			}
		}
	}

	//�޸� �����
	SAFE_DELETE(m_3Dchannel);
	SAFE_DELETE(m_3Dsound);

	//�ý��� �ݱ�
	if (m_3Dsystem != NULL)
	{
		m_3Dsystem->release();
		m_3Dsystem->close();
	}
}
void cSoundManager::SoundUpdate3D(void)
{
	m_3Dsystem->update();
}

//���� �߰�(Ű��, �����̸�, BGM?, ������?, 2D�� 3D��?)
void cSoundManager::addSound3D(std::string keyName, std::string soundName, bool bgm, bool loop, bool type, FMOD_VECTOR pos, FMOD_VECTOR vel)
{
	//type �Ű������� ������ ������ 2D(false), 3D(true)
	if (type)
	{
		//3D sound
		//3d ���� �߰�
		//m_2Dsystem->set3DSettings(1.0, 1.0, 1.0);
		//m_2Dsystem->createSound(soundName.c_str(), FMOD_3D, 0, &m_2Dsound[m_2DTotalSounds.size()]);
		//m_2Dsound[m_2DTotalSounds.size()]->set3DMinMaxDistance(0.5f, 5000.0f);
		//m_2Dsound[m_2DTotalSounds.size()]->setMode(FMOD_LOOP_NORMAL);
		//
	}
	else
	{
		//2D Sound
		if (loop)//��� or ����Ʈ
		{
			if (bgm)
			{
				//1: ���� URL�� �̸� 
				//2: ���带 ���� ���� �ɼ�	
				//3: ���带 ����ϴ� ���� �������� ������ �����ϴ� FMOD_CREATESOUNDEXINFO�� ������ , �̿ɼ��� �����Ϸ��� 0 �Ǵ� NULL�� �����ϸ� ��
				//4: FMOD::SOUND ������Ʈ�� �޴� ������ �ּ�
				//3Dsystem->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &m_3Dsound[m_3DTotalSounds.size()]);
			}
			else
			{
				m_3Dsystem->createSound(soundName.c_str(), FMOD_3D, 0, &m_3Dsound[m_3DTotalSounds.size()]);
				m_3Dsound[m_3DTotalSounds.size()]->set3DMinMaxDistance(0.5f, 5000.0f);
				m_3Dsound[m_3DTotalSounds.size()]->setMode(FMOD_DEFAULT);
				
				//m_3Dsystem->set3DListenerAttributes(
				//	0,		// listener ID, 0�� ��� listener�� �ϳ�
				//	&pos,	// ���� �����̽������� listener position
				//	&vel,	// �ʴ� listener�� �ӵ�
				//	&dir,	// listener�� ���� ����
				//	&up		// listener�� ��� ����
				//);	
					
			}
		}
		else  //����Ʈ
		{
			m_3Dsystem->createSound(soundName.c_str(), FMOD_3D, 0, &m_3Dsound[m_3DTotalSounds.size()]);
			m_3Dsound[m_3DTotalSounds.size()]->set3DMinMaxDistance(0.5f, 5000.0f);
			m_3Dsound[m_3DTotalSounds.size()]->setMode(FMOD_DEFAULT);
			//m_3Dsystem->set3DListenerAttributes(0, &pos, &vel, &dir, &up);
		}
		//3d ���� listener ����
		FMOD_VECTOR pos = { 0.0f, 0.0f, 0.0f };
		FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };
		FMOD_VECTOR dir = { 0.0f, 1.0f, 0.0f };
		FMOD_VECTOR up = { 0.0f, 0.0f, 1.0f };

		m_3Dsystem->set3DListenerAttributes(
				0,		// listener ID, 0�� ��� listener�� �ϳ�
				&pos,	// ���� �����̽������� listener position
				&vel,	// �ʴ� listener�� �ӵ�
				&dir,	// listener�� ���� ����
				&up		// listener�� ��� ����
			);	

		//3d ���� ����
		FMOD_VECTOR vPos = pos;
		FMOD_VECTOR vVel = vel;
		
		//m_3Dpos.insert(keyName, vPos);
		m_3Dpos.push_back(vPos);
		m_3Dpos.push_back(vVel);
		//�ʿ� ���带 Ű���� �Բ� ����ش�
		m_3DTotalSounds.insert(make_pair(keyName, &m_3Dsound[m_3DTotalSounds.size()]));
	}

}
//���� �÷���(Ű��, ����) 0.0f~ 1.0f
void cSoundManager::play3D(std::string keyName, float volume)
{
	int count = 0;
	arrSoundIter iter = m_3DTotalSounds.begin();
	for (iter; iter != m_3DTotalSounds.end(); count++)
	{
		if (keyName == iter->first)
		{
			//���� �÷���
			m_3Dsystem->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &m_3Dchannel[count]);


			//3d ���� ����
			FMOD_VECTOR pos = m_3Dpos[count];
			FMOD_VECTOR vel = m_3Dvel[count];
			
			m_3Dchannel[count]->set3DAttributes(&pos, &vel);

			//
			//��������
			m_3Dchannel[count]->setVolume(volume);
			break;
		}
	}
}
//���� ����
void cSoundManager::stop3D(std::string keyName)
{
	int count = 0;
	arrSoundIter iter = m_3DTotalSounds.begin();
	for (iter; iter != m_3DTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� ����
			m_3Dchannel[count]->stop();
			break;
		}
	}
}
//���� �Ͻ�����
void cSoundManager::pause3D(std::string keyName)
{
	int count = 0;
	arrSoundIter iter = m_3DTotalSounds.begin();
	for (iter; iter != m_3DTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� ����
			m_3Dchannel[count]->setPaused(true);
			break;
		}
	}
}
//���� �ٽ� ���
void cSoundManager::resume3D(std::string keyName)
{
	int count = 0;
	arrSoundIter iter = m_3DTotalSounds.begin();
	for (iter; iter != m_3DTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� �Ͻ�����(�ٽ����)
			m_3Dchannel[count]->setPaused(false);
			break;
		}
	}
}

//�÷��� ���̳�?
bool cSoundManager::isPlaySound3D(std::string keyName)
{
	bool isPlay;
	int count = 0;
	arrSoundIter iter = m_3DTotalSounds.begin();
	for (iter; iter != m_3DTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//�÷��� ���̳�?
			m_3Dchannel[count]->isPlaying(&isPlay);
			break;
		}
	}
	return isPlay;
}
//�Ͻ����� ���̳�?
bool cSoundManager::isPauseSound3D(std::string keyName)
{
	bool isPause;
	int count = 0;
	arrSoundIter iter = m_3DTotalSounds.begin();
	for (iter; iter != m_3DTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//�÷��� ���̳�? (�Ͻ�����)
			m_3Dchannel[count]->isPlaying(&isPause);
			break;
		}
	}
	return isPause;
}

void cSoundManager::Destroy()
{
	for each(auto it in m_2DTotalSounds)
	{
		SAFE_DELETE(it.second);
	}

	for each(auto it in m_3DTotalSounds)
	{
		SAFE_DELETE(it.second);
	}
}