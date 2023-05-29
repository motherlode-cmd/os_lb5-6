#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define MAX_SIGNALS 10

// Очередь сигналов
int signal_queue[MAX_SIGNALS];
int signal_count = 0;

// Обработчик сигналов обычного типа
void regular_signal_handler(int signal) {
    if (signal_count < MAX_SIGNALS) {
        signal_queue[signal_count] = signal;
        signal_count++;
    }
}

// Обработчик сигналов реального времени
void real_time_signal_handler(int signal) {
    if (signal_count < MAX_SIGNALS) {
        signal_queue[signal_count] = signal;
        signal_count++;
    }
}

int main() {
    // Установка обработчика сигналов обычного типа
    signal(SIGUSR1, regular_signal_handler);
    signal(SIGUSR2, regular_signal_handler);

    // Установка обработчика сигналов реального времени
    struct sigaction sa;
    sa.sa_handler = real_time_signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGRTMIN, &sa, NULL);
    sigaction(SIGRTMIN+1, &sa, NULL);

    // Генерация тестовых сигналов
    kill(getpid(), SIGUSR1);
    kill(getpid(), SIGRTMIN+1);
    kill(getpid(), SIGUSR2);
    kill(getpid(), SIGRTMIN);

    // Обработка сигналов из очереди в порядке FIFO
    for (int i = 0; i < signal_count; i++) {
        printf("Signal %d\n", signal_queue[i]);
    }

    return 0;
}
