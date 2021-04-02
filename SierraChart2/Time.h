#pragma once
#include "zorro_incl.h"
#include <chrono>

DATE vEpochSeconds_to_date(double vEpochSeconds);
DATE llEpochMicroseconds_to_date(long long llEpochMicroseconds);
double date_to_vEpochSeconds(DATE date);

int epochmilli_str_to_yyyymmdd(const char* emilli);

int get_todays_date_yyyymmdd();
int vEpochSeconds_to_todays_date_yyyymmdd(double vEpochSeconds);


extern int g_RequestRateLimit_ms;

extern std::chrono::steady_clock::time_point g_LastRequestTp;
bool delay_request(bool double_delay);
bool can_request_now();

//for futures month codes
const char* get_monthcode_string(int month_flags);
