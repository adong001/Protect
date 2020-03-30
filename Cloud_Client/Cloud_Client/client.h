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

class FileTool   //文件读写工具类
{
public:
	static bool Read(const std::string& filename, std::string& body);//从文件读取所有内容
	static bool Write(const std::string& filename, const std::string& body);//向文件写入内容
};


class DataManager  //文件信息管理类
{
private:
		std::string m_store_file;//持久化存储文件名称
		std::unordered_map<std::string, std::string> m_backup_list;//备份文件信息列表
	
public:
	DataManager(const std::string& filename) :
		m_store_file(filename)
	{}
	bool Insert(const std::string& key, const std::string& val);//插入/更新信息
	bool GetEtag(const std::string& key, std::string& val);//通过文件名获取原有的etag信息
	bool Storage();//持久化存储
	bool InitLoad();//初始化加载原有数据
};


class ClouClient   //目录监控类
{
private:
	std::string m_srv_ip;//服务端ip和port
	uint16_t m_srv_port;
	std::string m_listen_dir;//监控目录名称
	DataManager m_data_manage;
public:
	ClouClient(const std::string& filename, const std::string& store_file
		,const std::string& srv_ip,const uint16_t& srv_port) :
		m_listen_dir(filename),
		m_data_manage(store_file),
		m_srv_ip(srv_ip),
		m_srv_port(srv_port)
	{}

	bool Start();//主控流程
	bool GetBackupFileList(std::vector<std::string>& list);//获取需要备份的文件列表
	bool GetEtag(const std::string& filename, std::string& etag);//计算文件的etag信息
};
