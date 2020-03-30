#include"client.h"

bool FileTool::Read(const std::string& filename, std::string& body)//���ļ���ȡ��������
{
	std::ifstream ifs(filename, std::ios::binary);

	if (ifs.is_open() == false)
	{
		std::cout << "open Readfile " << filename << " failed\n";
		return false;
	}
	//boost::filesysem::file_size(); ��ȡ�ļ���С
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

bool FileTool::Write(const std::string& filename, const std::string& body)//���ļ�д������
{
	std::ofstream ofs(filename, std::ios::binary);
	//ofstream���ļ�Ĭ�ϻ����ԭ������
	//��ǰ�����Ǹ���д��,�������
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




bool DataManager::Insert(const std::string& key, const std::string& val)//����/������Ϣ
{
	m_backup_list[key] = val;
	return true;
}

bool DataManager::GetEtag(const std::string& key, std::string& val)//ͨ���ļ�����ȡԭ�е�etag��Ϣ
{
	auto it = m_backup_list.find(key);
	if (it == m_backup_list.end())
	{
		return false;
	}
	val = it->second;
	return true;
}
bool DataManager::Storage()//�־û��洢
{
	//1.��ȡ
	std::stringstream tmp;
	for (auto it = m_backup_list.begin(); it != m_backup_list.end(); ++it)
	{
		//�洢Դ�ļ�����ѹ����������"���",����һ���ļ���"\r\n"���
		tmp << it->first << " " << it->second << "\r\n";
	}
	FileTool::Write(m_store_file, tmp.str());
	return true;
}

bool DataManager::InitLoad()//��ʼ������ԭ������
{
	// 1.����������ļ������ݶ�ȡ����
	std::string body;
	if (FileTool::Read(m_store_file, body) == false)
	{
		return false;
	}
	// 2.�����ַ�����������\r\n���зָ�
	//boost::split(vector,src,sep,flag)
	//��src����sep�ָ�����vector��
	//flag --token_compress_off(vector������sep) token_compress_on(vector�б���sep)
	std::vector<std::string> list;
	boost::split(list, body, boost::is_any_of(" "), boost::token_compress_off);

	// 3.ÿһ�а��տո���зָ�,ǰ����key,������val
	for (auto i : list)
	{
		size_t pos = i.find(" ");
		if (pos == std::string::npos)
		{
			continue;
		}
		const std::string key = i.substr(0, pos);
		const std::string val = i.substr(pos + 1);

		// 4.��key-val��ӵ�m_file_list��
		Insert(key, val);
	}
	return true;
}

bool ClouClient::Start()//��������
{
	m_data_manage.InitLoad();
	std::vector<std::string> list;
	GetBackupFileList(list);//��ȡ������Ҫ���ݵ��ļ���
	for (int i = 0; i < list.size(); ++i)
	{
		std::string name = list[i];//��ȡ��Ҫ�����ļ���
		std::string pathname = m_listen_dir + name;//��ȡ��Ҫ�����ļ�·����
		std::string body;
		FileTool::Read(pathname, body);//��ȡ�����ļ�����
		httplib::Client client(m_srv_ip,m_srv_port);//
		std::string req_path = "/" + name;//
		auto rsp = client.Put(req_path.c_str(), body, "application/octet-stream");
		if (rsp == NULL || (rsp != NULL && rsp->status != 200))//�ļ��ϴ�ʧ��
		{
			continue;
		}
		std::string etag;
		GetEtag(pathname,etag);
		m_data_manage.Insert(name, etag);//���ݳɹ�������/������Ϣ
	}
	return true;
}

bool ClouClient::GetBackupFileList(std::vector<std::string>& list)//��ȡ��Ҫ���ݵ��ļ��б�
{

	boost::filesystem::directory_iterator begin(m_listen_dir);
	boost::filesystem::directory_iterator end;
	for (; begin != end; ++begin)
	{
		if (boost::filesystem::is_directory(begin->status()))
		{
			continue;//��ǰ����֧��Ŀ¼����
		}

		//1.����Ŀ¼��أ���ȡָ��Ŀ¼�µ������ļ�����
		std::string pathname = begin->path.string();//��ȡ�ļ�·����
		std::string name = begin->path().filename().string();//��ȡ���ļ���

		//2.����ļ���������ǰ��etag
		std::string cur_etag;
		GetEtag(pathname, cur_etag);//��ȡ��ǰ�ļ�etag��Ϣ
		std::string old_etag;
		data_manage.GetEtag(name, old_etag);//��ȡ֮ǰ�����ļ�etag��Ϣ

		//3.��data_manage�б����ԭ��etag���бȶ�
		    //3.1.û���ҵ�ԭ��etag�������ļ���Ҫ����
		    //3.2.�ҵ�ԭ��etag�����ǵ�ǰ��etag��ԭ�е�etag����ȣ���Ҫ����
		    //3.3.�ҵ�ԭ��etag�������뵱ǰetag��ȣ�����Ҫ����
		if (cur_etag != old_etag)
		{
			list.push_back(name);//��ǰetag��ԭ�е�etag��ͬ��Ҫ����
		}
	}
	return true;
}
bool ClouClient::GetEtag(const std::string& pathname, std::string& etag)//�����ļ���etag��Ϣ
{	
	//�����MD5�ж�(�Զ���/ssl��ӿ�)
	//etag:�ļ���С-�ļ����һ���޸�ʱ��
	int64_t fsize = boost::filesystem::file_size(pathname);//�ļ���С
	time_t mtime = boost::filesystem::last_write_time(pathname);//���һ���޸�ʱ��
	etag = std::to_string(fsize) + "-" + std::to_string(mtime);


	return true;
}