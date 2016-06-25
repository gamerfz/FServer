/***********************************************************************
*FileName	:  Guid
*Author		:  fz
*Date		:  2016.4.9
*Description:  生成Guid
************************************************************************/
#pragma once
#include <Singleton.h>

/*时效为2016.1.1日0点起的34年315天,此非失效时间,只是超过此时效后理论上有重复的可能,如真出现此情况可重新批量生成新ID,替换老ID,并设置新时效即可*/
#define EPOCH_TIME 1451577600000

#define theGuid Guid::GetInstance()
class Guid : public Singleton<Guid>
{
	int m32Order;
	int m64Order;
public:
	Guid();
	~Guid();
	/*40位时效 + 12位key + 12位计数*/
	unsigned long long Generate64Guid(short key = 0);
	/*8位key + 23位计数 注意使用超过23位计数后有较低的概率会重复,建议只用于一些在线ID,并定期对服务器重启维护,或者直接生成64位ID*/
	int Generate32Guid(unsigned char key = 0);
};
