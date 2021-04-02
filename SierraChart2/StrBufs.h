#pragma once
#define LEN_STRBUF 2048
#define MAX_STRBUFS 64

#include <stdio.h>


extern int(__cdecl *BrokerError)(const char* txt);
extern int(__cdecl *BrokerProgress)(const int percent);
extern char StrBufs[MAX_STRBUFS][LEN_STRBUF];
extern int NextBuf;

bool refresh();

template<typename... Args>
inline int zprintf(Args... args) {
	NextBuf = (NextBuf + 1) % MAX_STRBUFS;
	auto pBuf = &StrBufs[NextBuf][0];
	_snprintf_s(pBuf, LEN_STRBUF, _TRUNCATE, args...);
	return BrokerError(pBuf);
}

template<typename... Args>
inline const char* strf(Args... args) {
	NextBuf = (NextBuf + 1) % MAX_STRBUFS;
	auto pBuf = &StrBufs[NextBuf][0];
	_snprintf_s(pBuf, LEN_STRBUF, _TRUNCATE, args...);
	return pBuf;
}

void saveas(const char* filename, const char* content);
