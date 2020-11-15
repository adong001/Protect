
#include "stdafx.h"
#include<string>
#include<iostream>
#include "dbConn.h"
using namespace std;
//SQLOLEDB  C:\Program Files\Microsoft SQL Server\MSSQL15.MSSQLSERVER\MSSQL
_bstr_t strConnect = "Provider=SQLNCLI11.1;Server=10.101.11.150\\SQLEXPRESS;Database=ChatTool;uid=sa;pwd=123123";
//"Provider=SQLNCLI11.1;Server=192.168.220.129\\SQLEXPRESS;Database=ChatTool;uid=chatAdmin;pwd=123456";



string selectIp(string table, string column)
{
	CoInitialize(NULL);
	_RecordsetPtr m_pRecordset("ADODB.Recordset");
	_ConnectionPtr m_pConnection("ADODB.Connection");
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pConnection.CreateInstance(__uuidof(Connection));
	string sql;

	sql = "select ip as columnvalue from " + table + " where name= '" + column + "'";

	_bstr_t bstrSQL(sql.c_str());
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");
		m_pConnection->Open(strConnect, "", "", adModeUnknown);
	}
	catch (_com_error e)
	{
		cerr << "\nERROR:" << (char*)e.Description();//抛出异常
	}

	if (m_pConnection == NULL)
		printf("conn error");
	m_pRecordset->Open(bstrSQL, m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
	_variant_t columnvalue;
	while (!m_pRecordset->adoEOF)

	{
		columnvalue = m_pRecordset->GetCollect("columnvalue");
		m_pRecordset->MoveNext(); ///移到下一条记录
	}
	return (char*)(_bstr_t)columnvalue;
}

string selectuername(string table, string column)
{
	CoInitialize(NULL);
	_RecordsetPtr m_pRecordset("ADODB.Recordset");
	_ConnectionPtr m_pConnection("ADODB.Connection");
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pConnection.CreateInstance(__uuidof(Connection));
	string sql;

	sql = "select name as columnvalue from " + table + " where ip= '" + column + "'";

	_bstr_t bstrSQL(sql.c_str());
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");
		m_pConnection->Open(strConnect, "", "", adModeUnknown);
	}
	catch (_com_error e)
	{
		cerr << "\nERROR:" << (char*)e.Description();//抛出异常
	}

	if (m_pConnection == NULL)
		printf("conn error");
	m_pRecordset->Open(bstrSQL, m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
	_variant_t columnvalue;
	while (!m_pRecordset->adoEOF)

	{
		columnvalue = m_pRecordset->GetCollect("columnvalue");
		m_pRecordset->MoveNext(); ///移到下一条记录
	}
	return (char*)(_bstr_t)columnvalue;
}

string rebackusername(string table)
{
	string buf;
	CoInitialize(NULL);
	_RecordsetPtr m_pRecordset("ADODB.Recordset");
	_ConnectionPtr m_pConnection("ADODB.Connection");
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pConnection.CreateInstance(__uuidof(Connection));
	string sql;

	sql = "select name as columnvalue from " + table;

	_bstr_t bstrSQL(sql.c_str());
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");
		m_pConnection->Open(strConnect, "", "", adModeUnknown);
	}
	catch (_com_error e)
	{
		cerr << "\nERROR:" << (char*)e.Description();//抛出异常
	}

	if (m_pConnection == NULL)
		printf("conn error");
	m_pRecordset->Open(bstrSQL, m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
	_variant_t columnvalue;
	while (!m_pRecordset->adoEOF)

	{
		columnvalue = m_pRecordset->GetCollect("columnvalue");
		m_pRecordset->MoveNext(); ///移到下一条记录
		buf += (char*)(_bstr_t)columnvalue;
		buf += "@";
	}

	return buf;
}

bool checkUsername(string table, string workid)
{
	CoInitialize(NULL);
	_RecordsetPtr m_pRecordset("ADODB.Recordset");
	_ConnectionPtr m_pConnection("ADODB.Connection");
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pConnection.CreateInstance(__uuidof(Connection));
	string sql;
	sql = "select count(1) as columnvalue from " + table + " where workid = '" + workid + "'";
	_bstr_t bstrSQL(sql.c_str());
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");
		m_pConnection->Open(strConnect, "", "", adModeUnknown);
	}
	catch (_com_error e)
	{
		cerr << "\nERROR:" << (char*)e.Description();//抛出异常
	}

	if (m_pConnection == NULL)
		printf("conn error");
	try
	{
		m_pRecordset->Open(bstrSQL, m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
	}
	catch (_com_error e)
	{
		cerr << "\nERROR:" << (char*)e.Description();//抛出异常
		return false;
	}
	_variant_t columnvalue;
	while (!m_pRecordset->adoEOF)

	{
		columnvalue = m_pRecordset->GetCollect("columnvalue");
		m_pRecordset->MoveNext(); ///移到下一条记录
	}
	if ((int)columnvalue == 0)
	{
		return false;
	}
	return true;
}

bool checkUser(string table, string workid, string pWord)
{
	CoInitialize(NULL);
	_RecordsetPtr m_pRecordset("ADODB.Recordset");
	_ConnectionPtr m_pConnection("ADODB.Connection");
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pConnection.CreateInstance(__uuidof(Connection));
	string sql;
	sql = "select count(1) as columnvalue from " + table + " where workid = '" + workid + "' and password ='" + pWord  + "'";
	_bstr_t bstrSQL(sql.c_str());
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");
		m_pConnection->Open(strConnect, "", "", adModeUnknown);
	}
	catch (_com_error e)
	{
		cerr << "\nERROR:" << (char*)e.Description();//抛出异常
	}

	if (m_pConnection == NULL)
		printf("conn error");
	m_pRecordset->Open(bstrSQL, m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
	_variant_t columnvalue;
	while (!m_pRecordset->adoEOF)

	{
		columnvalue = m_pRecordset->GetCollect("columnvalue");
		m_pRecordset->MoveNext(); ///移到下一条记录
	}
	if ((int)columnvalue == 0)
	{
		return false;
	}
	return true;
}

void add(string table, string uName, string pWord, string ip, string dept, string post,string name)
{
	CoInitialize(NULL);
	_RecordsetPtr m_pRecordset("ADODB.Recordset");
	_ConnectionPtr m_pConnection("ADODB.Connection");
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pConnection.CreateInstance(__uuidof(Connection));
	string sqlCommand = "insert into " + table + " values('" + uName + "','" + pWord + "','" + ip + "','"+ dept + "','"+post+"','" + name + "')";
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");
		m_pConnection->Open(strConnect, "", "", adModeUnknown);
	}
	catch (_com_error e)
	{
		cerr << "\nERROR:" << (char*)e.Description();//抛出异常
	}

	if (m_pConnection == NULL)
		printf("conn error");

	m_pConnection->Execute(sqlCommand.c_str(), NULL, 1);//执行SQL语句
	m_pConnection->Close();
	::CoUninitialize(); //释放程序占用的COM 资源 
}

void add(string table, string uName, string pWord, string ip)
{
	CoInitialize(NULL);
	_RecordsetPtr m_pRecordset("ADODB.Recordset");
	_ConnectionPtr m_pConnection("ADODB.Connection");
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pConnection.CreateInstance(__uuidof(Connection));
	string sqlCommand = "insert into " + table + " values('" + uName + "','" + pWord + "','" + ip + "')";
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");
		m_pConnection->Open(strConnect, "", "", adModeUnknown);
	}
	catch (_com_error e)
	{
		cerr << "\nERROR:" << (char*)e.Description();//抛出异常
	}

	if (m_pConnection == NULL)
		printf("conn error");

	m_pConnection->Execute(sqlCommand.c_str(), NULL, 1);//执行SQL语句
	m_pConnection->Close();
	::CoUninitialize(); //释放程序占用的COM 资源 
}

void update(string table, string uName, string ip)
{
	CoInitialize(NULL);
	_RecordsetPtr m_pRecordset("ADODB.Recordset");
	_ConnectionPtr m_pConnection("ADODB.Connection");
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pConnection.CreateInstance(__uuidof(Connection));
	string sqlCommand = "update " + table + "  set ip = '" + ip + "'" + " where workid ='" + uName +  "'";
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");
		m_pConnection->Open(strConnect, "", "", adModeUnknown);
	}
	catch (_com_error e)
	{
		cerr << "\nERROR:" << (char*)e.Description();//抛出异常
	}

	if (m_pConnection == NULL)
		printf("conn error");

	m_pConnection->Execute(sqlCommand.c_str(), NULL, 1);//执行SQL语句
	m_pConnection->Close();
	::CoUninitialize(); //释放程序占用的COM 资源 
}

void updateIP(string table, string ip)
{
	CoInitialize(NULL);
	_RecordsetPtr m_pRecordset("ADODB.Recordset");
	_ConnectionPtr m_pConnection("ADODB.Connection");
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pConnection.CreateInstance(__uuidof(Connection));
	string sqlCommand = "update " + table + "  set ip = '0 ' where ip ='" + ip + "'";
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");
		m_pConnection->Open(strConnect, "", "", adModeUnknown);
	}
	catch (_com_error e)
	{
		cerr << "\nERROR:" << (char*)e.Description();//抛出异常
	}

	if (m_pConnection == NULL)
		printf("conn error");

	m_pConnection->Execute(sqlCommand.c_str(), NULL, 1);//执行SQL语句
	m_pConnection->Close();
	::CoUninitialize(); //释放程序占用的COM 资源 
}
void updatePW(string table, string workid,string PW)
{
	CoInitialize(NULL);
	_RecordsetPtr m_pRecordset("ADODB.Recordset");
	_ConnectionPtr m_pConnection("ADODB.Connection");
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pConnection.CreateInstance(__uuidof(Connection));
	string sqlCommand = "update " + table + " set password = '"+PW+" ' where workid ='" + workid + "'";
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");
		m_pConnection->Open(strConnect, "", "", adModeUnknown);
	}
	catch (_com_error e)
	{
		cerr << "\nERROR:" << (char*)e.Description();//抛出异常
	}

	if (m_pConnection == NULL)
		printf("conn error");

	m_pConnection->Execute(sqlCommand.c_str(), NULL, 1);//执行SQL语句
	m_pConnection->Close();
	::CoUninitialize(); //释放程序占用的COM 资源 
}