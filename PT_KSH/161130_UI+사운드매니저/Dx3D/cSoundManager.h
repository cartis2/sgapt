#pragma once

#include "inc/fmod.h"
#include "inc/fmod.hpp"		//fomd.hpp �߰�
#pragma comment(lib, "lib/fmodex_vc.lib")	//lib ��ũ
//using namespace FMOD;			//FMOD ���ӽ����̽� ���

//ä�ι���, �������
#define EXTRACHANNELBUFFER 5
#define SOUNDBUFFER 20
#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER	//�ѻ��� ���ۼ���: ���۰� �۾Ƽ� ������ ������ �ذ����ֱ� ����

#define g_pSoundManager cSoundManager::GetInstance()

enum SOUNDTYPE
{
	SOUNDNULL = 0,
	BGM,		//�������
	SPEECH,		//���
	EFFECT,		//ȿ����
	AMBIENT		//ȯ����
};

class cSoundManager
{
private:
	typedef std::map<std::string, FMOD::Sound**> arrSounds;
	typedef std::map<std::string, FMOD::Sound**>::iterator arrSoundIter;

	
private:
	SOUNDTYPE		m_soundType;

	//2D Sound
	FMOD::System*	m_2Dsystem;			//fmod�� �ý��� Ŭ����
	FMOD::Sound**	m_2Dsound;			//fmod�� ���� Ŭ����
	FMOD::Channel** m_2Dchannel;		//fmod�� ä�� Ŭ����

	arrSounds		m_2DTotalSounds;	//�ʿ� ��� ���� ���
	
	//3D Sound
	FMOD::System*	m_3Dsystem;			//fmod�� �ý��� Ŭ����
	FMOD::Sound**	m_3Dsound;			//fmod�� ���� Ŭ����
	FMOD::Channel** m_3Dchannel;		//fmod�� ä�� Ŭ����

	arrSounds		m_3DTotalSounds;	//�ʿ� ��� ���� ���

	//FMOD_VECTOR		m_3Dpos;			//������ ��ġ
	//FMOD_VECTOR		m_3Dvel;			//������ ��ġ
	//typedef std::map<std::string, FMOD_VECTOR> arr3DSoundPos;
	//typedef std::map<std::string, FMOD_VECTOR> arr3DSoundVel;
	//arr3DSoundPos	m_3Dpos;
	//arr3DSoundVel	m_3Dvel;

	std::vector<FMOD_VECTOR>	m_3Dpos;	
	std::vector<FMOD_VECTOR>	m_3Dvel;

private:
	SINGLETONE(cSoundManager);

public:
	//2D Sound
	HRESULT SoundInit2D(void);
	void SoundRelease2D(void);
	void SoundUpdate2D(void);
	//void render(void);

	//3D Sound
	HRESULT SoundInit3D(void);
	void SoundRelease3D(void);
	void SoundUpdate3D(void);

	//���� �߰�(Ű��, �����̸�, BGM?, ������?)
	void addSound2D(std::string keyName, std::string soundName, bool bgm = FALSE, bool loop = FALSE, bool type = FALSE);
	//���� �÷���(Ű��, ����) 0.0f~ 1.0f
	void play2D(std::string keyName, float volume = 1.0f);
	//���� ����
	void stop2D(std::string keyName);
	//���� �Ͻ�����
	void pause2D(std::string keyName);
	//���� �ٽ� ���
	void resume2D(std::string keyName);

	//�÷��� ���̳�?
	bool isPlaySound2D(std::string keyName);
	//�Ͻ����� ���̳�?
	bool isPauseSound2D(std::string keyName);
	//



	//���� �߰�(Ű��, �����̸�, BGM?, ������?)
	void addSound3D(std::string keyName, std::string soundName, bool bgm = FALSE, bool loop = FALSE, bool type = FALSE, FMOD_VECTOR pos = { 0,0,0 }, FMOD_VECTOR vel = { 0,0,0 });
	//���� �÷���(Ű��, ����) 0.0f~ 1.0f
	void play3D(std::string keyName, float volume = 1.0f);
	//���� ����
	void stop3D(std::string keyName);
	//���� �Ͻ�����
	void pause3D(std::string keyName);
	//���� �ٽ� ���
	void resume3D(std::string keyName);
	                                                                 
	//�÷��� ���̳�?
	bool isPlaySound3D(std::string keyName);
	//�Ͻ����� ���̳�?
	bool isPauseSound3D(std::string keyName);
	//
	void Destroy();
	
};
