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
    // âõîäíûå äàííûå
    int cashboxAmount; // êîëè÷åñòâî êàññ
    int clientsIntensity; // èíòåíñèâíîñòü ïîòîêà ïîêóïàòåëåé
    int processingSpeed; // ñêîðîñòü îáðàáîòêè òîâàðà íà êàññå
    int averageQuantity; // ñðåäíåå êîëè÷åñòâî òîâàðîâ â òåëåæêå ïîêóïàòåëÿ
    int maximumQueue; // ìàêñèìàëüíàÿ äëèíà î÷åðåäè


    // âíóòðåííèå äàííûå
    int queueLength = 3;
    bool isFinished = false;
    int numberOfWorkingCashboxes = 0;
    int numberOfQueues = 0;
    int numberOfReceipts = 0;
    std::vector<std::thread*> cashboxes_WIP;
    std::vector<std::queue<Client*>*> lines;
    std::mutex mutex;

    // ñáîð ñòàòèñòèêè
    int servedCustomers; // îáñëóæåííûå êëèåíòû
    int notServedCustomers; // íåîáñëóæåííûå êëèåíòû
    double averageQueueLength; // ñðåäíÿÿ äëèíà î÷åðåäè
    double averageClientTime; // ñðåäíåå âðåìÿ íàõîæäåíèå ïîêóïàòåëÿ â î÷åðåäè è íà êàññå
    double averageCashboxWorktime; // ñðåäíåå âðåìÿ ðàáîòû êàññû
    double averageCashboxDowntime; // ñðåäíåå âðåìÿ ïðîñòîÿ êàññû

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

    // äîïîëíèòåëüíûå ðàñ÷åòû
    double factorial(double n);
    double getPrej(); // âåðîÿòíîñòü îòêàçà
    double getQ(); // îòíîñèòåëüíàÿ ïðîïóñêíàÿ ñïîñîáíîñòü
    double getA(); // àáñîëþòíàÿ ïðîïóñêíàÿ ñïîñîáíîñòü
};
