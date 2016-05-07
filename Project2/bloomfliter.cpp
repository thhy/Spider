#include "bloomfliter.h"


int BloomFliter::seed[] = {7,11,13,31,37,61};
BloomFliter::BloomFliter()
{
    fun = new SimpleHash[sizeof(seed)];
    for(int i = 0 ; i < 6;++i)
    {
        fun[i] = new SimpleHash(DEFAULT_SIZE,seed[i]);
    }
}

bool BloomFliter::contain(std::string url)
{
	if(url.empty())
        return false;
    bool ret = true;
	for (int i = 0;i<sizeof(seed);++i) {
        ret = ret && (bits[fun->hash(url)]);
		if(ret == false)
			return ret;
    }
    return ret;
}

void BloomFliter::add(std::string url)
{
	for (int i = 0;i<sizeof(fun);++i) {
		bits = bits.set(fun->hash(url),1);
    }
}

