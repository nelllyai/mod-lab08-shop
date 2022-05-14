#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <queue>
#include <mutex>
#include <thread>

class Client {
public:
    std::vector<int> receipt;
    Client(std::vector<int> receipt);
};

class Shop {
private:
    // входные данные
    int cashboxAmount; // количество касс
    int clientsIntensity; // интенсивность потока покупателей
    int processingSpeed; // скорость обработки товара на кассе
    int averageQuantity; // среднее количество товаров в тележке покупателя
    int maximumQueue; // максимальная длина очереди


    // внутренние данные
    int queueLength = 3;
    bool isFinished = false;
    int numberOfWorkingCashboxes = 0;
    int numberOfQueues = 0;
    int numberOfReceipts = 0;
    std::vector<std::thread*> cashboxes_WIP;
    std::vector<std::queue<Client*>*> lines;
    std::mutex mutex;

    // сбор статистики
    int servedCustomers; // обслуженные клиенты
    int notServedCustomers; // необслуженные клиенты
    double averageQueueLength; // средняя длина очереди
    double averageClientTime; // среднее время нахождение покупателя в очереди и на кассе
    double averageCashboxWorktime; // среднее время работы кассы
    double averageCashboxDowntime; // среднее время простоя кассы

public:
    Client* getClient();
    Shop(int cashboxAmount, int clientsIntensity, int processingSpeed, int averageQuantity, int maximumQueue);

    void startShopping();
    void serveClient(Client* client, int number);
    void serveQueue(std::queue<Client*>* customers);
    void serveShop();

    int getAmountOfServedCustomers();
    int getAmountOfNotServedCustomers();
    double getAverageQueueLength();
    double getAverageClientTime();
    double getAverageCashboxWorktime();
    double getAverageCashboxDowntime();

    // дополнительные расчеты
    double factorial(double n);
    double getPrej(); // вероятность отказа
    double getQ(); // относительная пропускная способность
    double getA(); // абсолютная пропускная способность
};
