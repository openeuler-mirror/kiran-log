#pragma once

/* config为NULL的情况（建议）： 使用默认配置(/etc/kiran-log/zlog.conf)，
   project_name建议为项目名称；program_name建议为二进制程序名。这两个值分别对应配置中的PROJECT_NAME和PROGRAM_NAME */
int dzlog_init_ex(const char *config, const char *cname, const char *project_name, const char *program_name);
