// KiwiCTester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../KiwiC/KiwiC.h"
#include <windows.h>
#include <locale.h>

int reader(int id, kchar16_t* buf, void* user)
{
	if (id >= 10)
	{
		return 0;
	}
	if (buf == nullptr) return 20;
	swprintf_s((wchar_t*)buf, 20, L"테스트 %d입니다.", id);
}

int receiver(int id, PKIWIRESULT kr, void* user)
{
	int size = kiwiResult_getSize(kr);
	for (int i = 0; i < size; i++)
	{
		printf("%g\t", kiwiResult_getProb(kr, i));
		int num = kiwiResult_getWordNum(kr, i);
		for (int j = 0; j < num; j++)
		{
			wprintf(L"%s/%s(%d~%d)\t", kiwiResult_getWordFormW(kr, i, j), kiwiResult_getWordTagW(kr, i, j),
				kiwiResult_getWordPosition(kr, i, j), kiwiResult_getWordPosition(kr, i, j) + kiwiResult_getWordLength(kr, i, j));
		}
		printf("\n");
	}

	kiwiResult_close(kr);
	return 0;
}

int main()
{
	system("chcp 65001");
	_wsetlocale(LC_ALL, L"korean");
	PKIWI kw = kiwi_init("../ModelGenerator/", 0, 0);
	kiwi_prepare(kw);
	kiwi_analyzeMW(kw, reader, receiver, nullptr, 10);
	PKIWIRESULT kr = kiwi_analyzeW(kw, (const kchar16_t*)L"1:1 한처음에 하느님께서 하늘과 땅을 창조하셨다. ", 1);
	kiwiResult_close(kr);
	kr = kiwi_analyzeW(kw, (const kchar16_t*)L"1:3 하느님께서 말씀하시기를 “빛이 생겨라.” 하시자 빛이 생겼다. ", 1);
	kiwiResult_close(kr);
	kr = kiwi_analyzeW(kw, (const kchar16_t*)L"1:3 하느님께서 말씀하시기를 “빛이 생겨라.” 하시자 빛이 생겼다. ", 1);
	int size = kiwiResult_getSize(kr);
	for (int i = 0; i < size; i++)
	{
		printf("%g\t", kiwiResult_getProb(kr, i));
		int num = kiwiResult_getWordNum(kr, i);
		for (int j = 0; j < num; j++)
		{
			wprintf(L"%s/%s(%d~%d)\t", kiwiResult_getWordFormW(kr, i, j), kiwiResult_getWordTagW(kr, i, j), 
				kiwiResult_getWordPosition(kr, i, j), kiwiResult_getWordPosition(kr, i, j) + kiwiResult_getWordLength(kr, i, j));
		}
		printf("\n");
	}
	kiwiResult_close(kr);
	kiwi_close(kw);
	getchar();
    return 0;
}

