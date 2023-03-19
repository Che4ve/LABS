#include <stdlib.h>
#include <stdio.h>
#include "myqueue.h" // Подключаем собственный заголовочный файл

void scan_queue(MyQueue* queue, int size) // Ввод очереди
{
    for (int i = 0; i < size; i++) {
        printf("\t(Adding node №%d...) Enter node value : ", i + 1);
        int value;
        scanf("%d", &value);
        push_back(queue, newNode(value));
    }
}

int main() {

    printf("How many queue structures would you like to merge?\n");
    int q_num;
    scanf("%d", &q_num);

    if (q_num <= 0) {
        printf("You've chosen not to merge any queues\n");
        return 0;
    }

    MyQueue* merged_queue = createQueue(); // Результирующая очередь
    MyQueue* new_queue; // Следующая очередь по списку

    for (int i = 0; i < q_num; i++) {
        new_queue = createQueue();
        MyQueue* temp_q = merged_queue;
        // Ввод количества узлов в очереди
        printf("Please, enter the amount of nodes that queue <%d> will contain: ", i + 1);
        int nodes_num;
        scanf("%d", &nodes_num);
        scan_queue(new_queue, nodes_num); // Чтение очереди
        // Вывод полученной очереди
        printf("You've constructed a queue:\n");
        print_queue(new_queue);
        printf("\n");
        // Функция join также очищает память двух входных очередей после слияния
        merged_queue = join(temp_q, new_queue); // Конкатенация двух очередей
    }

    printf("Merging queues...\n");
    print_queue(merged_queue);
    printf("\n");

    printf("Sorting queue using quick_sort...\n");
    merged_queue = quick_sort(merged_queue); // Быстрая сортировка Хоара
    print_queue(merged_queue);

    return 0;
}