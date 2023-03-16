#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <io.h>
using namespace std;

void getFiles(string path, vector<string>& files)
{
	//�ļ����  
	long   hFile = 0;
	//�ļ���Ϣ  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("/*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//�����Ŀ¼,����֮  
			//�������,�����б�  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("/").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(p.assign(path).append("/").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

int HandleProc(vector<string>& vImgFiles,string TxtFileName, int BeginIndex, int EndIndex)
{

	ifstream readFile;
	readFile.open(TxtFileName.c_str(), ios::in);

	if (readFile.is_open())
	{
		//cout << "�ļ��򿪳ɹ���" << endl;
		string str;
		while (getline(readFile, str))
		{
			cout << str << endl;
		}
	}
	else
	{
		//cout << "�ļ���ʧ�ܣ�" << endl;
	}

	return 0;
}

int main(void)
{
	//��ȡ��ǰ�ļ����������ļ�
	vector<string> vImgFiles;
	vector<string> vTxtFiles;
	getFiles("./TxtRc", vTxtFiles);
	getFiles("./ImgRc", vImgFiles);
	//���������ļ�
	for (int i = 0; i < vTxtFiles.size(); i += 1)
	{
		string FilePath = vTxtFiles[i];
		int Index = FilePath.find('_');
		if (Index == -1)
		{
			//log that file xxx is analysic error
		}
		else
		{
			string BeginIndexStr=FilePath.substr(0, Index);
			string EndIndexStr= FilePath.substr(Index);
			int BeginIndex = atoi(BeginIndexStr.c_str());
			int EndIndex= atoi(EndIndexStr.c_str());
			if (HandleProc(vImgFiles,FilePath, BeginIndex, EndIndex) == -1)
			{
				//log that error
			}
			else
			{
				//success
			}
		}
	}

	return 0;

}