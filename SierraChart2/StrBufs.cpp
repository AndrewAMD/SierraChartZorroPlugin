#include "pch.h"
#include "framework.h"
#include "StrBufs.h"
#undef min
#undef max
#include <chrono>
#include "banned.h" //must include last

#define ZORRO_WINDOW_REFRESH_MS 250

namespace cro = std::chrono;
typedef cro::steady_clock clo;


int(__cdecl *BrokerError)(const char* txt) = NULL;
int(__cdecl *BrokerProgress)(const int percent) = NULL;
char StrBufs[MAX_STRBUFS][LEN_STRBUF];
int NextBuf = 0;

bool refresh() {
	static auto last_refresh = clo::now();
	auto now = clo::now();
	auto dur_ms = cro::duration_cast<cro::milliseconds>(now - last_refresh);
	if (dur_ms >= cro::milliseconds(ZORRO_WINDOW_REFRESH_MS)) {
		last_refresh = now;
		if (BrokerProgress(0)) {
			return true;
		}
		else return false;
	}
	return true;
}

#include <fstream>
#include <string>
#include <iostream>
void saveas(const char* filename, const char* content) {
	try {
		std::ofstream out(filename);
		out << content;
		out.close();
	}
	catch (std::exception const& e) {
		zprintf("saveas error: %s", e.what());
	}
}
