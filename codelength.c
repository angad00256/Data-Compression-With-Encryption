#include"headers.h"
#include"prototypes.h"

int codelength(int ndc)
{
	if(ndc<2)
	return 1;

	if(ndc<4)
	return 2;

	if(ndc<8)
	return 3;

	if(ndc<16)
	return 4;

	if(ndc<32)
	return 5;

	if(ndc<64)
	return 6;

	if(ndc<128)
	return 7;
}
