// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include "../include/task.h"

TEST(TEST1, test1) {
    int cashboxes = 2;
    int intensity = 30;
    int speed = 10;
    int averageProducts = 3;
    int clients = 4;
  
    Shop supermarket(cashboxes, intensity, speed, averageProducts, clients);
    supermarket.startShopping();
  
    int result = supermarket.getAmountOfNotServedCustomers();
    ASSERT_EQ(0, result);
}

TEST(TEST2, test2) {
    int cashboxes = 2;
    int intensity = 30;
    int speed = 10;
    int averageProducts = 3;
    int clients = 4;
  
    Shop supermarket(cashboxes, intensity, speed, averageProducts, clients);
    supermarket.startShopping();
  
    int result = 2 + 2;
    EXPECT_EQ(4, result);
}
