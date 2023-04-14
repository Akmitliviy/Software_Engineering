#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <ctype.h>
#include <Windows.h>

using namespace std;

#define N 100
#define STR 200

typedef struct book {

	char mAuthor[N];
	char mBook[N];
	int mYear;
	int mPages;
	int mPrice;

	struct book* mNext;
} SBook;

void SetStruct(SBook** p_sbFirstBook, char* p_cString);
void Show(SBook* p_sbFirstBook);
void Print(SBook* p_sbFirstBook);
void Sort(SBook** p_sbFirstBook);
SBook* GetConcrete(SBook* p_sbFirstBook, int nIndex);
void DeleteElement(SBook** p_sbFirstBook, int nIndex);
void AddElement(SBook** p_sbFirstBookS);
void DeletePKL(SBook** p_sbFirstBook);
SBook* GetLast(SBook* p_sbFirstBook);