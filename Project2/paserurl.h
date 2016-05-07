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
    std::string html;//������ҳ������
    BloomFliter fliter;//ʹ�ò�¡������ȥ���ظ�url

	std::string tempLeate;
	std::string filename;//������html�ļ�
	std::regex urlMatch;//������url�Ƿ���ȷ
	MyUrl currentUrl;//��ǰҳ���url
	std::string KeyWords;//����ҳ��Ĺؼ���
	std::string title;//����ҳ��ı���
	std::string content;//����ҳ�������
	static const int DEFSIZE = 1000;
};

#endif // PASERURL_H
