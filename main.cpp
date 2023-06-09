#include <iostream>
#include <future>
#include <thread>
using namespace std;

void producer(promise<string> prm) {
    // Instrucciones
    // ....
    this_thread::sleep_for(chrono::seconds(3));
    prm.set_value("Resultado del Producer");

}

void consumer(future<string> fut) {
    // Instrucciones
    // ....
    auto resultado = fut.get();
    cout << resultado << endl;
}

void factory_promise_future() {
    promise<string> prm;
    future<string> fut = prm.get_future();

    thread hproducer(producer, std::move(prm));
    thread hconsumer(consumer, std::move(fut));

    hproducer.join();
    hconsumer.join();
}

void sumar(int a, int b, int& total) {
    total = a + b;
}

int sumar(int a, int b) {
    return a + b;
}

void ejemplo_hilo_vs_async() {

    int total = 0;

    // Con hilos
    thread t1([a=10, b=20, &total] {
        sumar(a, b, total);
    });
    t1.join();
    cout << total << endl;

    // Async
    auto f = async([a=10, b=20]{
        return sumar(a, b);
    });
    cout << f.get() << endl;

}

int main() {
//    factory_promise_future();
    ejemplo_hilo_vs_async();
    return 0;
}
