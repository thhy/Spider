#include "myurl.h"


MyUrl::MyUrl()
{

}

MyUrl::MyUrl(std::string url,int priority)
{
    this->url = url;
    this->isVisit = false;
    this->priority = priority;

	this->count = 0;
	pattern = "/";
}

bool MyUrl::isVisited()
{
    return isVisit;
}

void MyUrl::visit()
{
    this->isVisit = true;
}

std::string MyUrl::getUrl()
{
    return this->url;
}

bool operator >( const MyUrl &url1,const MyUrl &url2)
{
    return url1.priority > url2.priority;
}

bool operator <(const MyUrl &url1,const MyUrl &url2)
{
    return url1.priority<url2.priority;
}

std::string MyUrl::getFilename()
{
	int pos = url.find_last_of(pattern);
	if(pos == -1)
	{
		return url+".html";
	}
	int len = url.length() - pos;
	std::string result = url.substr(pos+1,len-1);
	int subpos = result.find_last_of(".");
	if(subpos == -1)
	{
		return url+".html";
	}
	len = result.length() - subpos + 1;
	result = index + result.substr(subpos-1,len);
	return result;
}

bool MyUrl::isTooDepth()
{
	std::regex pattern("/");
	std::smatch result;
	std::regex_match(this->url,result,pattern);
	return result.length()>6? true:false;
}

void MyUrl::setUrl(std::string url)
{
	this->url = url;
}

void MyUrl::setDepth(int depth)
{
	this->depth = depth;
}