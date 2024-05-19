#include "PolicyBasedDesign.cpp"

#include <gtest/gtest.h>

#include <string>
#include <iostream>

class Test1 {
    int a;
    int b;
public:
    Test1(int a, int b) : a(a), b(b) {}
    ~Test1() {}
    int getA() {
        return a;
    }
    int getB() {
        return b;
    }
};

TEST(PolicyBasedDesign_01, SmartPtr) {
    PolicyBasedDesign_01::SmartPtr<Test1> sp1 (new Test1(10, 20));
    EXPECT_EQ(sp1->getA(), 10);
    EXPECT_EQ(sp1->getB(), 20);
    EXPECT_NE(sp1->getB(), sp1->getA());
    PolicyBasedDesign_01::SmartPtr<int> sp2{ new int{ 123 } };
    PolicyBasedDesign_01::SmartPtr<int> sp3{ new int[5] { 1, 2, 3, 4, 5 } };
}

TEST(PolicyBasedDesign_02, SmartPtr) {
    PolicyBasedDesign_02::SmartPtr<Test1, PolicyBasedDesign_02::ScalarDeletePolicy<Test1>> ptr(new Test1(100, 20));
    EXPECT_EQ(100, ptr->getA());
    EXPECT_EQ(20, ptr->getB());
    PolicyBasedDesign_02::SmartPtr<int, PolicyBasedDesign_02::ScalarDeletePolicy<int>> sp1{ new int{ 123 } };
    PolicyBasedDesign_02::SmartPtr<int, PolicyBasedDesign_02::VectorDeletePolicy<int>> sp2{ new int[5] { 1, 2, 3, 4, 5 } };
    
}

TEST(PolicyBasedDesign, LogToFile) {
    PolicyBasedDesign_10::Logger<PolicyBasedDesign_10::LogToFile> fileLogger{};
    fileLogger.log("Important information");
    std::ifstream file;
    file.open("trace.txt");
    std::string message;
    while (file.peek() != EOF) {
        std::getline(file, message, '\n');
    }
    std::cout << message << std::endl;
    EXPECT_EQ(message, "Important information");
}
