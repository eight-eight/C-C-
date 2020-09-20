#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <unistd.h>
#include "QclLog.h"
using namespace std;
const string LOG_FILE  = "log_file_for_app.log";
const int MAX_LEN =  10240;
const string LevelName[] = { "NOLOG", "DEBUG", "INFO", "WARNING", "ERROR" };
QclLog::QclLog()
{
	
}
QclLog::~QclLog()
{
	
}
void QclLog::WriteLog(const char *file, int line, int level, int status, const char *fmt, ...)
{
    va_list args;
    //判断是否需要写LOG
    if (level == NOLOG)
    {
        return;
    }

    //调用内部写LOG函数
    va_start(args, fmt);
    InsideWrite(file, line, level, status, fmt, args);
    va_end(args);

    return;
}
int QclLog::GetCurTime(char* strTime)
{
	struct tm*	TimeInfo = NULL;
    size_t		TimeLen = 0;
    time_t		NowTime = 0;

    NowTime = time(NULL);
    TimeInfo = localtime(&NowTime);
    TimeLen = strftime(strTime, 64, "%Y.%m.%d %H:%M:%S", TimeInfo);
    return TimeLen;
}
void QclLog::InsideWrite(const char *file, int line, int level, int status, const char *fmt, va_list args)
{
    char str[MAX_LEN];
    int	 strLen = 0;
    char tmpStr[64];
    int	 tmpStrLen = 0;
    int  fd = 0;

    //初始化
    memset(str,0,sizeof(str));
    memset(tmpStr, 0, sizeof(tmpStr));

    //加入LOG时间
    tmpStrLen = GetCurTime(tmpStr);
    tmpStrLen = sprintf(str, "[%s] ", tmpStr);
    strLen = tmpStrLen;

    //加入LOG等级
    tmpStrLen = sprintf(str + strLen, "[%s] ", LevelName[level].c_str());
    strLen += tmpStrLen;

    //加入LOG状态
    if (status != 0)
    {
        tmpStrLen = sprintf(str + strLen, "[ERRNO is %d] ", status);
    }
    else
    {
        tmpStrLen = sprintf(str + strLen, "[SUCCESS] ");
    }
    strLen += tmpStrLen;

    //加入LOG信息
    tmpStrLen = vsprintf(str + strLen, fmt, args);
    strLen += tmpStrLen;

    //加入LOG发生文件
    tmpStrLen = sprintf(str + strLen, " [%s]", file);
    strLen += tmpStrLen;

    //加入LOG发生行数
    tmpStrLen = sprintf(str + strLen, " [%d]\n", line);
    strLen += tmpStrLen;

    //打开LOG文件
    if (OpenFile(fd))
    {
        return;
    }

    //写入LOG文件
    write(fd, str, strLen);

    //关闭文件
    close(fd);
    return;
}
int QclLog::OpenFile(int &fd)
{
	char FileName[1024];
	memset(FileName,0,sizeof(FileName));
	char *HomeEnv = getenv("HOME");
    sprintf(FileName, "%s/var/log/%s",HomeEnv, LOG_FILE.c_str());
    fd = open(FileName, O_WRONLY | O_CREAT | O_APPEND, 0666);
    if (fd < 0)
    {
        perror("打开日志文件失败");
		return -1;
    }
	return 0;
}