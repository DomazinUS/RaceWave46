#pragma once
// Native arithmetic/control flow is unchanged. Only RDRAM accesses gain a
// fixture bounds check, so a malformed fixture fails instead of escaping RAM.
void* wr64_test_address(uint8_t*, uint64_t, unsigned, const char*, int);
#undef MEM_W
#undef MEM_H
#undef MEM_HU
#undef MEM_B
#undef MEM_BU
#define MEM_W(o,r) (*(int32_t*)wr64_test_address(rdram,(r)+(o),4,__FILE__,__LINE__))
#define MEM_H(o,r) (*(int16_t*)wr64_test_address(rdram,((r)+(o))^2,2,__FILE__,__LINE__))
#define MEM_HU(o,r) (*(uint16_t*)wr64_test_address(rdram,((r)+(o))^2,2,__FILE__,__LINE__))
#define MEM_B(o,r) (*(int8_t*)wr64_test_address(rdram,((r)+(o))^3,1,__FILE__,__LINE__))
#define MEM_BU(o,r) (*(uint8_t*)wr64_test_address(rdram,((r)+(o))^3,1,__FILE__,__LINE__))
