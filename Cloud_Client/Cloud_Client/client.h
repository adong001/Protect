#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"httplib.h"
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<fstream>
#include<sstream>
#include<boost/algorithm/string.hpp>
#include<boost/filesystem.hpp>
#define STORE_FILE "./list.backup"
#define LISTEN_DIR "./backup"

class FileTool   //�ļ���д������
{
public:
	static bool Read(const std::string& filename, std::string& body);//���ļ���ȡ��������
	static bool Write(const std::string& filename, const std::string& body);//���ļ�д������
};


class DataManager  //�ļ���Ϣ������
{
private:
		std::string m_store_file;//�־û��洢�ļ�����
		std::unordered_map<std::string, std::string> m_backup_list;//�����ļ���Ϣ�б�
	
public:
	DataManager(const std::string& filename) :
		m_store_file(filename)
	{}
	bool Insert(const std::string& key, const std::string& val);//����/������Ϣ
	bool GetEtag(const std::string& key, std::string& val);//ͨ���ļ�����ȡԭ�е�etag��Ϣ
	bool Storage();//�־û��洢
	bool InitLoad();//��ʼ������ԭ������
};


class ClouClient   //Ŀ¼�����
{
private:
	std::string m_srv_ip;//�����ip��port
	uint16_t m_srv_port;
	std::string m_listen_dir;//���Ŀ¼����
	DataManager m_data_manage;
public:
	ClouClient(const std::string& filename, const std::string& store_file
		,const std::string& srv_ip,const uint16_t& srv_port) :
		m_listen_dir(filename),
		m_data_manage(store_file),
		m_srv_ip(srv_ip),
		m_srv_port(srv_port)
	{}

	bool Start();//��������
	bool GetBackupFileList(std::vector<std::string>& list);//��ȡ��Ҫ���ݵ��ļ��б�
	bool GetEtag(const std::string& filename, std::string& etag);//�����ļ���etag��Ϣ
};
