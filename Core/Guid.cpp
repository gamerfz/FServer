#include "Guid.h"
#include <chrono>

InitSingleton(Guid)
Guid::Guid()
{
	m32Order = 0;
	m64Order = 0;
}

Guid::~Guid()
{
}

unsigned long long Guid::Generate64Guid(short key /* = 0 */)
{
	unsigned long long gid = 0;
	auto nt = std::chrono::system_clock::now();
	unsigned long long value = std::chrono::duration_cast<std::chrono::seconds>(nt.time_since_epoch()).count() - EPOCH_TIME;
	
	gid |= (value * 1000/*∫¡√Î*/) << 24;
	gid |= key & 0xfff << 12;
	gid |= m64Order++ & 0xfff;
	if (m64Order == 0x1000)
		m64Order = 0;
	
	return gid;
}

int Guid::Generate32Guid(unsigned char key /* = 0 */)
{
// 	auto nt = time(NULL);
// 	auto lt = localtime(&nt);
	int gid = 0;
	gid |= key << 23;
	gid |= m32Order++ & 0xffffff;
	if (m32Order == 0x1000000)
		m32Order = 0;

	return gid;
}