#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// Обработчик сигналов реального времени
void real_time_signal_handler(int signal) {
    printf("Real-time Signal %d\n", signal);
}

int main() {
    // Установка обработчика сигналов реального времени
    struct sigaction sa;
    sa.sa_handler = real_time_signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGRTMIN, &sa, NULL);
    sigaction(SIGRTMIN+1, &sa, NULL);
    for(int i = 0; i < 32; i++) {
        sigaction(SIGRTMIN+i, &sa, NULL);
    }
    for(int i = 32; i >= 0; i--) {
        kill(getpid(), SIGRTMIN+i);
        usleep(1000); // Задержка 1 миллисекунда
    }
    // Генерация сигналов реального времени разных приоритетов
    return 0;
}
/*    sigaction(SIGRTMIN+1, &sa, NULL);
    sigaction(SIGRTMIN+2, &sa, NULL);
    sigaction(SIGRTMIN+3, &sa, NULL);
    sigaction(SIGRTMIN+4, &sa, NULL);
    sigaction(SIGRTMAX-1, &sa, NULL);
    sigaction(SIGRTMAX-2, &sa, NULL);
    sigaction(SIGRTMAX-3, &sa, NULL);
    sigaction(SIGRTMAX-4, &sa, NULL);*/