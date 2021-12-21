#ifndef ASMS_H
#define ASMS_H

extern "C" 
{
	ULONG64 _stdcall myAdd(ULONG64 u1, ULONG64 u2);
}

void AsmSample()
{
	ULONG64 result = myAdd(0x111111111, 0x333333333);
	printf("result = 0x%I64X\n", result);
}

#endif // !ASMS_H
