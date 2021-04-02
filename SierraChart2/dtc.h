#pragma once
#include <float.h>
#include <limits.h>
#include <string.h>
#include <memory.h> 
#include <stddef.h>

#include "../dtc/DTCProtocol.h"
using namespace DTC;

struct s_Header {
	uint16_t Size;
	uint16_t Type;
};