//#ifndef _SOUND_H
//#define _SOUND_H

#pragma once

//�ʿ��� �����
//������ ���
//Windows MultiMedia ���̺귯��
//#pragma comment(lib,"winmm")
//Windows MultiMedia DigitalVideo Command set ���
//#include <Digitalv.h>



//���� ������ ������ ����ü
//����ü�� ���� ���� �����ϸ� �ȵ˴ϴ�.
typedef struct _SoundInfo
{
	UINT DeviceID;
	BOOL isPause;
}SoundInfo;

//���� ������ ���ϴ�.
//������ ��� TRUE�� �����մϴ�.
BOOL soundOpen(SoundInfo* sound, LPSTR FileName);
//���� ������ �ݽ��ϴ�. 
//������ ��� TRUE�� �����մϴ�.
BOOL soundClose(SoundInfo* sound);
//�����ִ� ��� ���� ������ �ݽ��ϴ�.
//������ ��� TRUE�� �����մϴ�.
BOOL soundCloseAll();
//���带 ����մϴ�.
//���� ����� �����ϸ� FALSE�� �����մϴ�.
BOOL soundPlay(SoundInfo* sound);
//���带 �ݺ�����մϴ�.(wav������ �ݺ����� �ʰ� �ѹ��� ����մϴ�.) 
//���� ����� �����ϸ� FALSE�� �����մϴ�.
BOOL soundPlayLooping(SoundInfo* sound);
//���� ����� �Ͻ������մϴ�.
//���尡 ������� �ƴѰ�� FALSE�� �����մϴ�.
BOOL soundPause(SoundInfo* sound);
//���� ����� �簳�մϴ�.
//���尡 ������� ��� FALSE�� �����մϴ�.
BOOL soundResume(SoundInfo* sound);
//������ ������ �����ɴϴ�.
//�����Ұ�� ������ �����ϰ� �����ϸ� -1�� ��ȯ�մϴ�.
DWORD soundGetVolume(SoundInfo* sound);
//������ ������ �����մϴ�. ������ 0 ~ 1000 ������ ���� ���� �� �ֽ��ϴ�.
//���������� ������ ��� TRUE�� �����մϴ�.
BOOL soundSetVolume(SoundInfo* sound, DWORD volume);

BOOL soundSeek(SoundInfo* sound, DWORD seekTo);
BOOL soundPlayLoopingWav(SoundInfo* sound);
//#endif // !_SOUND_H