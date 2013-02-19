#include "daemon.h"

#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <sys/wait.h>

#include <iostream>

namespace CMordor {

static sigset_t block_signals() {
    sigset_t result;
    sigemptyset(&result);
    sigaddset(&result, SIGTERM); // 程序正常退出
    sigaddset(&result, SIGINT); // ctrl+c
    sigaddset(&result, SIGHUP); // 退出shell
    sigaddset(&result, SIGTSTP); // ctrl+z
    sigaddset(&result, SIGCONT); // 继续运行
    return result;
}

static void unblock_signals(int signal) {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, signal);
    pthread_sigmask(SIG_UNBLOCK, &set, 0);
    raise(signal);
    pthread_sigmask(SIG_BLOCK, &set, 0);
}

#define STRSIGNAL(signal) #signal

static void *thread_signal_headler(void *arg) {
    sigset_t mask = block_signals();
    while (true) {
        int caught = 0;
        int rc = sigwait(&mask, &caught);
        if (rc != 0) {
            continue;
        }
        switch (caught) {
            case SIGTERM: {
                std::cout << STRSIGNAL(SIGTREM) << std::endl;
                unblock_signals(caught);
                break;
            }
            case SIGINT: {
                std::cout << STRSIGNAL(SIGINT) << std::endl;
                unblock_signals(caught);
                continue;
            }
            case SIGHUP: {
                std::cout << STRSIGNAL(SIGHUP) << std::endl;
                unblock_signals(caught);
                break;
            }
            case SIGTSTP: {
                std::cout << STRSIGNAL(SIGTSTP) << std::endl;
                unblock_signals(caught);
                break;
            }
            case SIGCONT: {
                std::cout << STRSIGNAL(SIGCONT) << std::endl;
                unblock_signals(caught);
                break;
            }
            default: {
                break;
            }
        }

    }
    return 0;
}

int user_main(int argc, char **argv,
              boost::function<int (int, char **)> daemon_func) {
    // 系统信号处理
    sigset_t mask = block_signals();
    int rc = pthread_sigmask(SIG_BLOCK, &mask, 0);
    if (rc != 0) {
        return errno;
    }
    pthread_t signal_thread_id;
    rc = pthread_create(&signal_thread_id, 0, thread_signal_headler, 0);
    if (rc != 0) {
        return errno;
    }
    // 启动用户函数
    return daemon_func(argc, argv);
}

boost::function<bool (pid_t, int)> callback_child_exit;

int watch_dog(int argc, char **argv,
              boost::function<int (int, char **)> daemon_func) {
    while (true) {
        pid_t pid = fork();
        switch (pid) {
            case -1: {
                return errno;
            }
            case 0: { //子进程
                return user_main(argc, argv, daemon_func);
            }
            default: {
                int status = 0;
                if (waitpid(pid, &status, 0) == -1) {
                    return errno;
                }
                // 子进程结束，检查用户是否需要额外处理
                if (callback_child_exit.empty()) {
                    if (callback_child_exit(pid, status)) {
                        continue; // Reboot child
                    } else {
                        return 0;
                    }
                } else {
                    // Default is "reboot"
                    continue;
                }
            }
        }
    }
    return 0;
}

int run(int argc, char **argv,
        boost::function<int (int, char **)> daemon_func,
        bool enable_watch_dog/* = false*/) {
    if (enable_watch_dog) {
        watch_dog(argc, argv, daemon_func);
    } else {
        user_main(argc, argv, daemon_func);
    }
    return 0;
}

} // CMordor
