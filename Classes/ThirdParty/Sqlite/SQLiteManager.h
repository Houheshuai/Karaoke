#ifndef _SQLMANAGER_H_
#define _SQLMANAGER_H_

class SQLManager
{
public:
	SQLManager();
	~SQLManager();

	//�洢����ʹ�õ����ݿ⵽�ڴ�


	//�������ӵ�Index�����ݱ�汾
	//DB·��
	//�����汾�����ö�Ӧ��·��
	AddSQLiteDBQueue();

	//����
	//����ɾ�������ӵ�Index
	RemoveSQLiteDBQueue();

	//����
	//DB��·������Index
	//���������ݿ⣬����������ݲ����ڣ��������ݿ�д
	SetPrimaryDB();
	
	//����
	//������е����ݿ�����
	ClearDBQueue();
	
	
	
};

#endif