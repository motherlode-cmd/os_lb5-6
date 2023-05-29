#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void real_time_signal_handler(int signal) {
    printf("Real-time Signal %d\n", signal);
}

int main() {
    // Установка обработчика для сигналов реального времени
    struct sigaction sa;
    sa.sa_handler = real_time_signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    int sigs[30];
    // Генерация сигналов реального времени с номерами меньше 32
    int arr [] = {0,1,2,3,4,5,6,7,8,10,11,12,13,14,15,16, 17, 18, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
    for (int i = 0; i <  30; i++) {
        int ind = rand() % (30 - i);
        int signal = arr[ind];
        sigs[i] = signal;
        //printf("curr sig = %d\n", signal);
        arr[ind] = arr[30 - i - 1];
        arr[30 - i - 1] = -1;
            sigaction(signal, &sa, NULL);
            kill(getpid(), signal);
            usleep(1000); // Задержка 1 миллисекунда

    }
    printf("Порядок вызовов сигналов\n");
    for(int i = 0; i < 30; i++) {
        printf(" %d ", sigs[i]);
    }

    return 0;
}