#ifndef __CMORDOR_DAEMON_H__
#define __CMORDOR_DAEMON_H__

#include <sys/types.h>

#include <boost/function.hpp>


namespace CMordor {

int run(int argc, char **argv,
        boost::function<int (int, char **)> daemon_func,
        bool enable_watch_dog = false);
/**
 * @return 用户可以控制是否重新启动子进程
 */
extern boost::function<bool (pid_t, int)> callback_child_exit;

} // CMordor

#endif //__CMORDOR_DAEMON_H__
