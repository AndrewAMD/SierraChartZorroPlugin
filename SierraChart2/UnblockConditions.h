#pragma once

/*
Unblock conditions return true to unblock and false for continue to block.
*/

#include "dtc.h"


typedef int t_feedid;
//typedef int32_t t_ReqId;

//bool ubc_example (t_feedid id, void* pMsg, uint16_t Type, int32_t request_id, void* pAuxiliary);
typedef bool(*t_fpUnblockContition)(t_feedid id, void* pMsg, uint16_t Type, int32_t request_id, void* pAuxiliary);

