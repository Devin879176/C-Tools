
/*
函数功能说明：
getFiles(string path, vector<pair<string, int> >& files)
path：文件夹路径 
例如：char folder[] = "G:\\Paper\\FaceRecognition\\Face verification code\\lfw_funneled123";
files:存储获取到的文件名 
例如：vector<pair<string, int> > files; 前一项string表示文件名，后一项int 为序号 
调用方法：getFiles(folder, files);
*/


void getFiles(string path, vector<pair<string, int> >& files) {
	//文件句柄
	long   hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;

	string p;
	string s;

	static int auto_label = 0;
	int label = 0;
	p.clear();
	s.clear();

	FILE *fp = fopen(p.assign(path).append("\\label.txt").c_str(), "r");
	if (fp == NULL)
	{
		label = auto_label++;
		//cout << path << " label:" << label << endl;
	}
	else
	{
		fscanf(fp, "%d", &label);
		if (auto_label < label) auto_label = label + 1;
		fclose(fp);
	}


	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)  {
		do  {
			//如果是目录,迭代之
			//如果不是,加入列表
			if ((fileinfo.attrib   &   _A_SUBDIR)) {
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else  {
				if (strstr(fileinfo.name, "png") != NULL || strstr(fileinfo.name, "bmp") != NULL || strstr(fileinfo.name, "jpg") != NULL || strstr(fileinfo.name, "tif") != NULL)
					files.push_back(make_pair(p.assign(path).append("\\").append(fileinfo.name), label));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}