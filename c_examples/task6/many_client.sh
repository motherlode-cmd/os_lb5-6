num_clients=$1
# Запуск читателей
gnome-terminal --command="./server" --title="Server"
for i in {1..300}
do
   echo -e "hi $i \n" | ./client & 2>/dev/null
done
