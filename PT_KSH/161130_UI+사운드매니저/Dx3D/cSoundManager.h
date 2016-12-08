#pragma once

#include "inc/fmod.hpp"		//fomd.hpp �߰�
#pragma comment(lib, "lib/fmodex_vc.lib")	//lib ��ũ
using namespace FMOD;			//FMOD ���ӽ����̽� ���

								//ä�ι���, �������
#define EXTRACHANNELBUFFER 5
#define SOUNDBUFFER 20
								//�ѻ��� ���ۼ���: ���۰� �۾Ƽ� ������ ������ �ذ����ֱ� ����
#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER

#define g_pSoundManager cSoundManager::GetInstance()

class cSoundManager
{
private:
	typedef std::map<std::string, Sound**> arrSounds;
	typedef std::map<std::string, Sound**>::iterator arrSoundIter;

private:
	System* _system;		//fmod�� �ý��� Ŭ����
	Sound** _sound;			//fmod�� ���� Ŭ����
	Channel** _channel;		//fmod�� ä�� Ŭ����

	arrSounds _mTotalSounds;//�ʿ� ��� ���� ���


	
private:
	SINGLETONE(cSoundManager);

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//���� �߰�(Ű��, �����̸�, BGM?, ������?)
	void addSound(std::string keyName, std::string soundName, bool bgm = FALSE, bool loop = FALSE);

	//���� �÷���(Ű��, ����) 0.0f~ 1.0f
	void play(std::string keyName, float volume = 1.0f);
	//���� ����
	void stop(std::string keyName);
	//���� �Ͻ�����
	void pause(std::string keyName);
	//���� �ٽ� ���
	void resume(std::string keyName);

	//�÷��� ���̳�?
	bool isPlaySound(std::string keyName);
	//�Ͻ����� ���̳�?
	bool isPauseSound(std::string keyName);
	//
	void Destroy();
	
};
