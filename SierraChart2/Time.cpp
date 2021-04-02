#include "pch.h"
#include "framework.h"


#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Time.h"
#include "StrBufs.h"
#include "client.h"

#include "banned.h" //must include last

int g_RequestRateLimit_ms = 100;
namespace cro = std::chrono;
cro::steady_clock::time_point g_NextRequestTp = cro::steady_clock::now();

bool can_request_now() { return cro::steady_clock::now() > g_NextRequestTp; }

bool delay_request(bool double_delay) {
	auto limit_ms = g_RequestRateLimit_ms;
	if (double_delay) limit_ms *= 2;
	while (!can_request_now()) {
		cl_drain();
		if (!refresh()) return false;
		cl_loiter();
	}
	g_NextRequestTp = cro::steady_clock::now() + cro::milliseconds(limit_ms);
	return true;
}


DATE vEpochSeconds_to_date(double vEpochSeconds){
	return vEpochSeconds / (24ll * 60ll * 60ll) + 25569ll; // 25569. = DATE(1.1.1970 00:00)
}
DATE llEpochMicroseconds_to_date(long long llEpochMicroseconds) {
	return ((double)llEpochMicroseconds) / (1000000ll * (24ll * 60ll * 60ll)) + 25569ll; // 25569. = DATE(1.1.1970 00:00)
}


double date_to_vEpochSeconds(DATE date){
	return (double)((date - 25569ll) * (24ll * 60ll * 60ll));
}

void set_time_zone(const char* sTZ) {
	_putenv_s("TZ", sTZ);
	_tzset();
	return;
}
int epochmilli_str_to_yyyymmdd(const char* emilli) {
	__time32_t t32 = (__time32_t)(strtod(emilli, NULL) / 1000);
	if (!t32) return 0; // parse failure
	struct tm tm1 = { 0 };
	set_time_zone("UTC0");
	if (_localtime32_s(&tm1, &t32)) {
		return 0;// error
	}
	int y = tm1.tm_year + 1900;
	int m = tm1.tm_mon + 1;
	int d = tm1.tm_mday;
	return y * 10000 + m * 100 + d;
}

int get_todays_date_yyyymmdd() {
	__time32_t t32 = 0;
	struct tm tm1 = { 0 };
	_time32(&t32);
	set_time_zone("UTC0");
	_localtime32_s(&tm1, &t32);

	int y = tm1.tm_year + 1900;
	int m = tm1.tm_mon + 1;
	int d = tm1.tm_mday;
	return y * 10000 + m * 100 + d;
}
int vEpochSeconds_to_todays_date_yyyymmdd(double vEpochSeconds) {
	__time32_t t32 = lround(vEpochSeconds);
	struct tm tm1 = { 0 };
	set_time_zone("UTC0");
	_localtime32_s(&tm1, &t32);
	int y = tm1.tm_year + 1900;
	int m = tm1.tm_mon + 1;
	int d = tm1.tm_mday;
	return y * 10000 + m * 100 + d;
}


char get_monthchar(int monthnum) { //0=jan, 1=feb ... 11=dec.
	switch (monthnum) {
	case 0:  return 'F';//jan
	case 1:  return 'G';//feb
	case 2:  return 'H';
	case 3:  return 'J';
	case 4:  return 'K';
	case 5:  return 'M';
	case 6:  return 'N';
	case 7:  return 'Q';
	case 8:  return 'U';
	case 9:  return 'V';
	case 10: return 'X';
	case 11: return 'Z'; //dec
	default: return '_'; //fail
	}
}
const char* get_monthcode_string(int month_flags) {
	static char out[13];
	memset(out, 0, 13);
	int i = 0;
	char ch[2] = { 0,0 };
	for (i = 0; i < 12; i++) {
		if ((1 << i) & month_flags) {
			ch[0] = get_monthchar(i);
			strcat_s(out,13, ch);
		}
	}
	return out;
}