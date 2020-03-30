#include"client.h"

bool FileTool::Read(const std::string& filename, std::string& body)//从文件读取所有内容
{
	std::ifstream ifs(filename, std::ios::binary);

	if (ifs.is_open() == false)
	{
		std::cout << "open Readfile " << filename << " failed\n";
		return false;
	}
	//boost::filesysem::file_size(); 获取文件大小
	int64_t fsize = boost::filesystem::file_size(filename);
	body.resize(fsize);
	ifs.read(&body[0], fsize);
	if (ifs.good() == false)
	{
		std::cout << "file " << filename << " read data failed\n";
		return false;
	}
	ifs.close();
	return true;
}

bool FileTool::Write(const std::string& filename, const std::string& body)//向文件写入内容
{
	std::ofstream ofs(filename, std::ios::binary);
	//ofstream打开文件默认会清空原有内容
	//当前策略是覆盖写入,无需更改
	if (ofs.is_open() == false)
	{
		std::cout << "open Writefile " << filename << " failed\n";
		return false;
	}

	ofs.write(&body[0], body.size());
	if (ofs.good() == false)
	{
		std::cout << "write file" << filename << " failed\n";
		return false;
	}

	ofs.close();
	return true;
}




bool DataManager::Insert(const std::string& key, const std::string& val)//插入/更新信息
{
	m_backup_list[key] = val;
	return true;
}

bool DataManager::GetEtag(const std::string& key, std::string& val)//通过文件名获取原有的etag信息
{
	auto it = m_backup_list.find(key);
	if (it == m_backup_list.end())
	{
		return false;
	}
	val = it->second;
	return true;
}
bool DataManager::Storage()//持久化存储
{
	//1.读取
	std::stringstream tmp;
	for (auto it = m_backup_list.begin(); it != m_backup_list.end(); ++it)
	{
		//存储源文件名和压缩包名，以"间隔",与下一个文件以"\r\n"间隔
		tmp << it->first << " " << it->second << "\r\n";
	}
	FileTool::Write(m_store_file, tmp.str());
	return true;
}

bool DataManager::InitLoad()//初始化加载原有数据
{
	// 1.将这个备份文件的数据读取出来
	std::string body;
	if (FileTool::Read(m_store_file, body) == false)
	{
		return false;
	}
	// 2.进行字符串处理，按照\r\n进行分割
	//boost::split(vector,src,sep,flag)
	//将src按照sep分割存放在vector中
	//flag --token_compress_off(vector不保存sep) token_compress_on(vector中保存sep)
	std::vector<std::string> list;
	boost::split(list, body, boost::is_any_of(" "), boost::token_compress_off);

	// 3.每一行按照空格进行分割,前面是key,后面是val
	for (auto i : list)
	{
		size_t pos = i.find(" ");
		if (pos == std::string::npos)
		{
			continue;
		}
		const std::string key = i.substr(0, pos);
		const std::string val = i.substr(pos + 1);

		// 4.将key-val添加到m_file_list中
		Insert(key, val);
	}
	return true;
}

bool ClouClient::Start()//主控流程
{
	m_data_manage.InitLoad();
	std::vector<std::string> list;
	GetBackupFileList(list);//获取所有需要备份的文件名
	for (int i = 0; i < list.size(); ++i)
	{
		std::string name = list[i];//获取需要备份文件名
		std::string pathname = m_listen_dir + name;//获取需要备份文件路径名
		std::string body;
		FileTool::Read(pathname, body);//读取备份文件内容
		httplib::Client client(m_srv_ip,m_srv_port);//
		std::string req_path = "/" + name;//
		auto rsp = client.Put(req_path.c_str(), body, "application/octet-stream");
		if (rsp == NULL || (rsp != NULL && rsp->status != 200))//文件上传失败
		{
			continue;
		}
		std::string etag;
		GetEtag(pathname,etag);
		m_data_manage.Insert(name, etag);//备份成功，插入/更新信息
	}
	return true;
}

bool ClouClient::GetBackupFileList(std::vector<std::string>& list)//获取需要备份的文件列表
{

	boost::filesystem::directory_iterator begin(m_listen_dir);
	boost::filesystem::directory_iterator end;
	for (; begin != end; ++begin)
	{
		if (boost::filesystem::is_directory(begin->status()))
		{
			continue;//当前还不支持目录备份
		}

		//1.进行目录监控，获取指定目录下的所有文件名称
		std::string pathname = begin->path.string();//获取文件路径名
		std::string name = begin->path().filename().string();//获取纯文件名

		//2.逐个文件计算自身当前的etag
		std::string cur_etag;
		GetEtag(pathname, cur_etag);//获取当前文件etag信息
		std::string old_etag;
		data_manage.GetEtag(name, old_etag);//获取之前备份文件etag信息

		//3.与data_manage中保存的原有etag进行比对
		    //3.1.没有找到原有etag，则新文件需要备份
		    //3.2.找到原有etag，但是当前的etag和原有的etag不相等，需要备份
		    //3.3.找到原有etag，并且与当前etag相等，则不需要备份
		if (cur_etag != old_etag)
		{
			list.push_back(name);//当前etag与原有的etag不同需要备份
		}
	}
	return true;
}
bool ClouClient::GetEtag(const std::string& pathname, std::string& etag)//计算文件的etag信息
{	
	//最好用MD5判断(自定义/ssl库接口)
	//etag:文件大小-文件最后一次修改时间
	int64_t fsize = boost::filesystem::file_size(pathname);//文件大小
	time_t mtime = boost::filesystem::last_write_time(pathname);//最后一次修改时间
	etag = std::to_string(fsize) + "-" + std::to_string(mtime);


	return true;
}