#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define CONFIG_NAME "read_config/config.txt"

void parseFile(const char  * filePath)
{

	struct ConfigInfo
	{
		char key[64];
		char value[64];
	};
	
	FILE * file = fopen(filePath, "r");
	char buf[1024] = { 0 };
	while (fgets(buf, sizeof(buf), file) != NULL)
	{
		if ((buf[0] != '#') && (buf[0] != '\0') && (strchr(buf,':') != NULL))
		{
			struct ConfigInfo config_info;
			memset(&config_info, 0, sizeof(struct ConfigInfo));
			char * pos = strchr(buf, ':');
			strncpy(config_info.key, buf, pos - buf);
			strncpy(config_info.value, pos + 1, strlen(pos + 1) - 1); 
			printf("key = %s\t:\t", config_info.key);
			printf("value = %s\n", config_info.value);
		}
		memset(buf, 0, sizeof(buf));
	}
	fclose(file);

}





int main()
{
	char *home_env = getenv("HOME");
	char config_path[1024];
	memset(config_path,0,sizeof(config_path));
	snprintf(config_path,sizeof(config_path),"%s/%s",home_env,CONFIG_NAME);
	parseFile(config_path);

	return 0;
}
