#ifndef PASERURL_H
#define PASERURL_H

#include <iostream>
#include <regex>
#include <unordered_set>
#include <fstream>
#include <queue>
#include "myurl.h"
#include <Windows.h>
#include "bloomfliter.h"
#include "include\LJHtmlParser.h"


#pragma comment(lib,"LJHtmlParser.lib")

class PaserUrl
{
public:
    PaserUrl();
	PaserUrl(std::string filename);
	PaserUrl(std::string filename,MyUrl url);

	PaserUrl &operator = (const PaserUrl &paser);
	void getUrl(std::priority_queue<MyUrl> &downloadQueue);
	void parser(std::string htmldata,std::priority_queue<MyUrl> &downloadQueue);
	void findAll(const char *ch,int length,const char *match,int *result);
	int find_first(const char *ch,const char *match);
	std::string getRelUrl(std::string index,std::string relUrl);
	void paserKeyWords();
	std::string getKeyWords();

	~PaserUrl();
	void init();
	void paserTitleAndContent();

	std::string getTitle();
	std::string getContent();
    
private:
    std::string html;//解析网页的内容
    BloomFliter fliter;//使用布隆过滤器去除重复url

	std::string tempLeate;
	std::string filename;//解析的html文件
	std::regex urlMatch;//解析的url是否正确
	MyUrl currentUrl;//当前页面的url
	std::string KeyWords;//解析页面的关键词
	std::string title;//解析页面的标题
	std::string content;//解析页面的内容
	static const int DEFSIZE = 1000;
};

#endif // PASERURL_H
