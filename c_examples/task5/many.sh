# Количество читателей и писателей
num_readers=2
num_writers=2
# Запуск читателей
for ((i=0; i<$num_readers; i++)); do
gnome-terminal 2>/dev/null -e "./reader"
done
# Запуск писателей
for ((i=0; i<$num_writers; i++)); do
gnome-terminal 2>/dev/null -e "./writer"
done