// Copyright 2022 UNN-IASR
#include "../include/task.h"

Client::Client(std::vector<int> receipt) {
    this->receipt = receipt;
}

Shop::Shop(int cashboxAmount, int clientsIntensity, int processingSpeed, int averageQuantity, int maximumQueue) {
    this->cashboxAmount = cashboxAmount;
    this->clientsIntensity = clientsIntensity;
    this->processingSpeed = processingSpeed;
    this->averageQuantity = averageQuantity;
    this->maximumQueue = maximumQueue;
}

Client *Shop::getClient() {
    std::vector<int> check(averageQuantity);

    for (int i = 0; i < averageQuantity; i++) {
        check[i] = std::rand() % 40 + 1;
    }

    return new Client(check);
}

void Shop::startShopping() {
    serveShop();

    for (auto current_line : cashboxes_WIP) {
        current_line->join();
    }

    averageQueueLength = static_cast<double>(numberOfQueues / numberOfReceipts);
}

void Shop::serveClient(Client* client, int number) {
    for (auto i = 0; i < client->receipt.size(); i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(processingSpeed));
        std::unique_lock<std::mutex> lock(mutex);

        averageCashboxWorktime += static_cast<double>(processingSpeed * static_cast<std::int64_t>(numberOfWorkingCashboxes) / static_cast<double>(cashboxAmount));
        averageCashboxDowntime += static_cast<double>(processingSpeed * (cashboxAmount - static_cast<std::int64_t>(numberOfWorkingCashboxes)) / static_cast<double>(cashboxAmount));

        std::cout << "Cashbox #" << std::this_thread::get_id() << ". Client #" << number << " with product #" << i + 1 << "\n";

        lock.unlock();
    }

    servedCustomers++;
}

void Shop::serveQueue(std::queue<Client*>* client) {
    int number_of_served_customers = 1;
    while (!isFinished) {
        if (!client->empty()) {
            int count = 0;
            std::queue<int>* prevs = new std::queue<int>();

            while (!client->empty()) {
                auto customer = client->front();
                serveClient(customer, number_of_served_customers);
                client->pop();
                count++;
                number_of_served_customers++;
            }

            std::unique_lock<std::mutex> my_lock(mutex);
            numberOfQueues += count;
            numberOfReceipts++;
            my_lock.unlock();
        }
    }
}

void Shop::serveShop() {
    srand(time(NULL));
    int active_lines = 0;

    for (int i = 0; i < maximumQueue; i++) {
        numberOfWorkingCashboxes = 0;

        for (auto it = lines.begin(); it != lines.end(); it++) {
            if ((*it)->size() > 0) {
                numberOfWorkingCashboxes++;
            }
        }

        bool free_line = false;
        std::this_thread::sleep_for(std::chrono::milliseconds(clientsIntensity));

        for (auto it = lines.begin(); it != lines.end(); it++) {
            if ((*it)->size() < queueLength) {
                (*it)->push(getClient());
                free_line = true;
                break;
            }
        }

        if (!free_line) {
            if (active_lines < cashboxAmount) {
                active_lines++;
                auto new_line = new std::queue <Client*>;
                new_line->push(getClient());
                lines.push_back(new_line);
                cashboxes_WIP.push_back(new std::thread(&Shop::serveQueue, this, new_line));
            }
            else {
                notServedCustomers++;
            }
        }
    }

    isFinished = true;
}


int Shop::getAmountOfServedCustomers() {
    return servedCustomers;
}

int Shop::getAmountOfNotServedCustomers() {
    return notServedCustomers;
}

double Shop::getAverageQueueLength() {
    return averageQueueLength;
}

double Shop::getAverageClientTime() {
    double result = 0;

    for (int i = 1; i <= averageQueueLength; i++) {
        result += i * static_cast<double>(averageQuantity * processingSpeed);
    }

    return result / averageQueueLength;
}

double Shop::getAverageCashboxWorktime() {
    return averageCashboxWorktime;
}

double Shop::getAverageCashboxDowntime() {
    return averageCashboxDowntime;
}

double Shop::getPrej() {
    double p = static_cast<double>(clientsIntensity) / static_cast<double>(processingSpeed);

    double P0 = 1.0;
    for (int i = 1; i <= cashboxAmount; i++) {
        P0 = P0 + pow(p, i) / factorial(i);
    }

    for (int i = cashboxAmount + 1; i < cashboxAmount + maximumQueue; i++) {
        P0 = P0 + pow(p, i) / (factorial(cashboxAmount) * pow(cashboxAmount, i - cashboxAmount));
    }

    P0 = 1.0 / P0;

    double Prej = P0 * pow(p, (cashboxAmount + maximumQueue)) / static_cast<double>(pow(cashboxAmount, maximumQueue) * factorial(cashboxAmount));
    return Prej;
}

double Shop::getQ() {
    double Prej = getPrej();
    return 1.0 - Prej;
}

double Shop::getA() {
    double Q = getQ();
    return static_cast<double>(processingSpeed) * Q;
}

double Shop::factorial(double n) {
    if (n == 0)
        return 1;
    else
        return n * factorial(n - 1);
}
