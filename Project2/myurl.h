#ifndef MYURL_H
#define MYURL_H

#include <iostream>
#include <regex>

const std::string index = "\\html\\";

class MyUrl
{
public:
	MyUrl();
    MyUrl(std::string url,int priority);
    bool isVisited();
    void visit();
	void setPriority(int priority);
    std::string getUrl();
    friend bool operator > (const MyUrl &url1,const MyUrl &url2);
    friend bool operator < (const MyUrl &url1,const MyUrl &url2);
	std::string getFilename();
	bool isTooDepth();
	void setUrl(std::string url);
	void setDepth(int depth);

private:

    std::string url;
    bool isVisit;
    int priority;
	std::string pattern;
	int count;
	std::string keyWods;
	int depth;	
};
bool operator > (const MyUrl &url1,const MyUrl &url2);
bool operator < (const MyUrl &url1,const MyUrl &url2);
#endif // MYURL_H
