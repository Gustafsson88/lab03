// Copyright 2021 Alexsand Guchkov <firer.a45@gmail.com>

#include <gtest/gtest.h>
#include <SharedPtr.hpp>

class Testing
{
public:
    int x;
};

TEST(Example, EmptyTest) {
    EXPECT_TRUE(true);
}

TEST(Constructor_test, point_test) {
    SharedPtr <int> pointer1;
    int* p = pointer1.get();
    EXPECT_EQ(p, nullptr);
}

TEST(Method_test, test_get) {
    int* point = new int(111);
    SharedPtr <int> pointer1(point);
    int* tmp = pointer1.get();
    EXPECT_EQ(tmp, point);
}

TEST(Method_test, test_reset) {
    int *point1 = new int (111);
    int *point2 = new int (111);
    SharedPtr <int> pointer1(point1);
    SharedPtr <int> pointer2(point2);
    pointer1.reset();
    EXPECT_EQ(pointer1.get(), nullptr);
}

TEST(Method_test, test_reset_point) {
    int *point = new int (111);
    int *point1 = new int (111);
    SharedPtr <int> pointer(point);
    pointer.reset(point1);
    EXPECT_EQ(pointer.get(), point1);
}

TEST(Method_test, test_swap) {
    int *point1 = new int (111);
    int *point2 = new int (111);
    SharedPtr <int> pointer1(point1);
    SharedPtr <int> pointer2(point2);
    pointer1.swap(pointer2);
    EXPECT_EQ(pointer1.get(), point2);
    EXPECT_EQ(pointer2.get(), point1);
}

TEST(Operator_test, test_bool) {
    SharedPtr <int> pointer;
    bool ptr = pointer;
    int* point = new int(111);
    SharedPtr <int> pointer2(point);
    bool ptr2 = pointer2;
    EXPECT_EQ(ptr, false);
    EXPECT_EQ(ptr2, true);
}

TEST(Operator_test, test_arrow) {
    auto test_arrow = new Testing;
    test_arrow->x = 111;
    SharedPtr <Testing> pointer(test_arrow);
    EXPECT_EQ(pointer->x, test_arrow->x);
}

TEST(Operator_test, test_equality) {
    int *point = new int (111);
    SharedPtr <int> pointer(point);
    SharedPtr <int> pointer2;
    pointer2 = pointer;
    EXPECT_EQ(pointer2.get(), pointer.get());
}

TEST(Move_test, test_assign_construct) {
    EXPECT_EQ(std::is_move_assignable<SharedPtr<int>>::value, true);
    EXPECT_EQ(std::is_move_constructible<SharedPtr<int>>::value, true);
    EXPECT_EQ(std::is_move_assignable<SharedPtr<double>>::value, true);
    EXPECT_EQ(std::is_move_constructible<SharedPtr<double>>::value,true);
}
