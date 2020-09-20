#ifndef _QCL_LOG_H
#define _QCL_LOG_H
#include <cstdarg>
/************************************************************************/
/* 
const char *file���ļ�����
int line���ļ��к�
int level�����󼶱�
		0 -- û����־
		1 -- debug����
		2 -- info����
		3 -- warning����
		4 -- err����
int status��������
const char *fmt���ɱ����
*/
/************************************************************************/
// ��־��
class QclLog
{
public:
	enum LogLevel{NOLOG, DEBUG, INFO, WARNING, ERROR};
	void WriteLog(const char *file, int line, int level, int status, const char *fmt, ...);
	QclLog();
	~QclLog();
private:
	int OpenFile(int &fd);
	int GetCurTime(char* strTime);
    void InsideWrite(const char *file, int line, int level, int status, const char *fmt, va_list args);
};

#endif