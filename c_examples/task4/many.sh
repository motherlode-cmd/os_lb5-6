
#!/bin/bash
g++ -o server server.cpp
g++ -o client client.cpp

# Создание 2 пар сервер-клиент
for i in {1..3}
do
key=$i
# Запуск сервера
gnome-terminal -e "bash -c ./client $key;bash" --title="Client$i"
sleep 1
gnome-terminal -e "bash -c ./server $key;bash" --title="Server$i"
sleep 1
done