#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void sig_handler(int signo) {
    // выводим информацию о полученном сигнале и идентификаторе родительского процесса
    printf("Received signal %d in process %d\n", signo, getpid());

    // восстанавливаем диспозицию сигнала
    signal(signo, SIG_DFL);

    // отправляем сигнал родительскому процессу
    if (kill(getppid(), SIGUSR1) == -1) {
        printf("Error sending signal to parent process\n");
    } else {
        printf("Successfully sent signal to parent process\n");
    }
}

int main() {
    pid_t pid;

    // устанавливаем обработчики пользовательских сигналов
    signal(SIGUSR1, sig_handler);
    signal(SIGUSR2, sig_handler);

    // устанавливаем реакцию по умолчанию на сигнал SIGINT
    signal(SIGINT, SIG_DFL);

    // игнорируем сигнал SIGCHLD
    signal(SIGCHLD, SIG_IGN);

    // порождаем процесс-копию
    pid = fork();
    if (pid == -1) {
        printf("Error creating child process\n");
        exit(1);
    }

    if (pid == 0) {
        // процесс-потомок ждет сигналов
        while(1) {
            sleep(1);
        }
    } else {
        // процесс-родитель отправляет сигналы
        if (kill(pid, SIGUSR1) == -1) {
            printf("Error sending signal to child process\n");
        } else {
            printf("Successfully sent signal to child process\n");
        }

        // ожидаем сигнала от процесса-потомка
        wait(NULL);
    }

    return 0;
}
