#include <gtest/gtest.h>
#include "ros/ros.h"
#include "../include/order_manager.h"

TEST(order_manager_test,checkOrderSize) {
    OrderManager manager;
    manager.generateOrder();
    EXPECT_EQ(manager.getOrderSize(),4);
}