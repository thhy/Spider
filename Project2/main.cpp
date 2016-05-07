#include "mainwindow.h"
//#include <QApplication>
#include "downloadurl.h"
#include "paserurl.h"

int main(int argc, char *argv[])
{
	std::priority_queue<MyUrl> downloadQueue;//���ô����ض���
	std::ifstream urlFile("url.txt");//������url�ļ�
	std::string urlStream,urlsStream;
	std::string tmpHtmlFile = "out.html";//��ʱ�洢����html�ļ�
	while(!urlFile.eof())
	{
		urlStream.clear();
		urlFile>>urlStream;
		urlsStream.append(urlStream);
		urlsStream.append("\r\n");
	}
	if(urlFile.is_open())
		urlFile.close();
	PaserUrl paser(tmpHtmlFile);
	//paser.getUrl(downloadQueue);
	/*DownloadUrl download;
	download.init();*/

	MyUrl tmpUrl("http://www.baidu.com",1);
	downloadQueue.push(tmpUrl);
	tmpUrl.setUrl("http://www.csdn.com");
	downloadQueue.push(tmpUrl);
	tmpUrl.setUrl("http://www.bing.com");
	downloadQueue.push(tmpUrl);
	curl_global_init(CURL_GLOBAL_WIN32);
	while(!downloadQueue.empty())
	{
		DownloadUrl download(downloadQueue.top(),tmpHtmlFile);
		paser = PaserUrl(tmpHtmlFile,downloadQueue.top());

		download.init();
		//download = downloadQueue.top();//��ȡ���ȼ���ߵ�url
		download.run();
		downloadQueue.pop();
		paser.parser(download.htmlData(),downloadQueue);//�ӷ��ص�html�ļ���ɸѡ��URL����������뵽�����ض���
		std::cout<<paser.getTitle()<<std::endl;
		std::cout<<paser.getContent()<<std::endl;
	}
	//QApplication a(argc, argv);
	//MainWindow w;
	//w.show();
	curl_global_cleanup();

	//return a.exec();
	system("pause");
}
