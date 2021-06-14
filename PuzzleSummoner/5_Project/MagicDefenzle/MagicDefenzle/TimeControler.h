#pragma once

void zzInitializeTime(float FPStoSet);

void zzCheckNowTime();

DWORD zzGetCheckedTime();

DWORD zzGetElapsedTime();

float zzGetFPS();

int zzGetTick();
float zzGetmyFPS();
DWORD zzGetTotalTime();
void zzCheckStartTime();

DWORD zzCheckEndTime();

BOOL zzCheckTimeForNextFrame();
void zzGetGameOpenTime();
DWORD zzGetGameElapsedTime();