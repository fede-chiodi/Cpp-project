#include "queue.hpp"

int main() {
    Queue<int> queue;

    std::cout << "La coda è vuota? " << (queue.is_empty() ? "Sì" : "No") << std::endl;

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    std::cout << "Coda dopo l'enqueue: ";
    queue.print_queue();

    std::cout << "Dimensione della coda: " << queue.get_size() << std::endl;

    std::cout << "Peek (testa della coda): " << queue.peek() << std::endl;

    std::cout << "Dequeue: " << queue.dequeue() << std::endl;
    std::cout << "Coda dopo il dequeue: ";
    queue.print_queue();

    std::cout << "Dimensione della coda dopo il dequeue: " << queue.get_size() << std::endl;

    std::cout << "Iterazione con for_each: ";
    queue.for_each([](int data) {
        std::cout << data << " ";
    });
    std::cout << std::endl;

    std::cout << "Dequeue: " << queue.dequeue() << std::endl;
    std::cout << "Dequeue: " << queue.dequeue() << std::endl;

    std::cout << "La coda è vuota? " << (queue.is_empty() ? "Sì" : "No") << std::endl;

    try {
        std::cout << "Tentativo di Peek su coda vuota: ";
        std::cout << queue.peek() << std::endl;
    } catch (const std::underflow_error &e) {
        std::cout << "Errore: " << e.what() << std::endl;
    }

    try {
        std::cout << "Tentativo di Dequeue su coda vuota: ";
        std::cout << queue.dequeue() << std::endl;
    } catch (const std::underflow_error &e) {
        std::cout << "Errore: " << e.what() << std::endl;
    }

    return 0;
}