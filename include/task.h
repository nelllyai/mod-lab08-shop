#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <queue>
#include <mutex>
#include <list>
#include <thread>
#include <condition_variable>
#include <functional>

class Client {
public:
    std::vector<int> receipt;
    Client(std::vector<int> receipt);
};

class Shop {
private:
    // ������� ������
    int cashboxAmount; // ���������� ����
    int clientsIntensity; // ������������� ������ �����������
    int processingSpeed; // �������� ��������� ������ �� �����
    int averageQuantity; // ������� ���������� ������� � ������� ����������
    int maximumQueue; // ������������ ����� �������


    // ���������� ������
    int queueLength = 3;
    bool isFinished = false;
    int numberOfWorkingCashboxes = 0;
    int numberOfQueues = 0;
    int numberOfReceipts = 0;
    std::vector<std::thread*> cashboxes_WIP;
    std::vector<std::queue<Client*>*> lines;
    std::mutex mutex;

    // ���� ����������
    int servedCustomers; // ����������� �������
    int notServedCustomers; // ������������� �������
    double averageQueueLength; // ������� ����� �������
    double averageClientTime; // ������� ����� ���������� ���������� � ������� � �� �����
    double averageCashboxWorktime; // ������� ����� ������ �����
    double averageCashboxDowntime; // ������� ����� ������� �����

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

    // �������������� �������
    double factorial(double n);
    double getPrej(); // ����������� ������
    double getQ(); // ������������� ���������� �����������
    double getA(); // ���������� ���������� �����������
};