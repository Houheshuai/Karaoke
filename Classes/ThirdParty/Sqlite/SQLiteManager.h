#ifndef _SQLMANAGER_H_
#define _SQLMANAGER_H_

class SQLManager
{
public:
	SQLManager();
	~SQLManager();

	//存储最终使用的数据库到内存


	//返回连接的Index，数据表版本
	//DB路径
	//分析版本，设置对应的路径
	AddSQLiteDBQueue();

	//返回
	//输入删除的连接的Index
	RemoveSQLiteDBQueue();

	//返回
	//DB的路径或者Index
	//设置主数据库，如果该主数据不存在，则将主数据库写
	SetPrimaryDB();
	
	//返回
	//清除所有的数据库连接
	ClearDBQueue();
	
	
	
};

#endif