#include "lib/zlog-ex.h"
#include <pthread.h>
#include <zlog.h>
#include <iostream>

static pthread_rwlock_t zlog_env_lock_ex = PTHREAD_RWLOCK_INITIALIZER;

int dzlog_init_ex(const char* config,
                  const char* cname,
                  const char* project_name,
                  const char* program_name)
{
    int rc;

    if (project_name)
    {
        setenv("PROJECT_NAME", project_name, 1);
    }

    if (program_name)
    {
        setenv("PROGRAM_NAME", program_name, 1);
    }

    rc = pthread_rwlock_wrlock(&zlog_env_lock_ex);
    if (rc)
    {
        std::cerr << "Failed to call pthread_rwlock_wrlock. result: " << rc << "." << std::endl;
        return -1;
    }

    if (!config)
    {
        rc = dzlog_init("/etc/kiran-log/zlog.conf", cname);
    }
    else
    {
        rc = dzlog_init(config, cname);
    }

    if (rc) goto err;

    rc = pthread_rwlock_unlock(&zlog_env_lock_ex);
    if (rc)
    {
        std::cerr << "Failed to call pthread_rwlock_unlock. result: " << rc << "." << std::endl;
        return -1;
    }
    return 0;
err:
    rc = pthread_rwlock_unlock(&zlog_env_lock_ex);
    if (rc)
    {
        std::cerr << "Failed to call pthread_rwlock_unlock. result: " << rc << "." << std::endl;
        return -1;
    }
    return -1;
}
