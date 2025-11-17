//
// Created by Hosea on 11/16/2025.
//

#include "gtest/gtest.h"
#include "../src/DataStructs/Vector/vector.h"

struct Foo1 {
    int bob;
    double larry;
};
struct Foo2 {
    char frank;
    float jill;
    unsigned long long harry;
};
struct Foo3 {
    Foo1 foo1;
    Foo2 foo2;
};

TEST(Vector, InitAndFree_WorksWithStanderdTypes) {
    Vector<int> vector{};

    EXPECT_TRUE(Vector_Init(vector, 8));

    EXPECT_TRUE(vector.size == 0);
    EXPECT_TRUE(vector.capacity == 8);
    EXPECT_TRUE(vector.data);
}

TEST(Vector, InitAndFree_WorksWithCostomTypes) {
    Vector<Foo1> vector{};

    EXPECT_TRUE(Vector_Init(vector, 8));

    EXPECT_TRUE(vector.size == 0);
    EXPECT_TRUE(vector.capacity == 8);
    EXPECT_TRUE(vector.data);
}

TEST(Vector, InitAndFree_WorksWithCostomComposetTypes) {
    Vector<Foo3> vector{};

    EXPECT_TRUE(Vector_Init(vector, 8));

    EXPECT_TRUE(vector.size == 0);
    EXPECT_TRUE(vector.capacity == 8);
    EXPECT_TRUE(vector.data);
}

TEST(Vector, Reserve_WorksStanderdTypes){
    Vector<int> vector;
    EXPECT_TRUE(Vector_Init(vector, 8));

    EXPECT_TRUE(Vector_Reserve(vector, 62));

    EXPECT_TRUE(vector.capacity == 62);
    int foo;
    EXPECT_NO_THROW(foo = vector.data[61]);

    Vector_Free(vector);
}

TEST(Vector, Reserve_WorksCostomTypes){
    Vector<Foo1> vector;
    EXPECT_TRUE(Vector_Init(vector, 8));

    EXPECT_TRUE(Vector_Reserve(vector, 62));

    EXPECT_TRUE(vector.capacity == 62);

    EXPECT_NO_THROW(vector.data[61]);

    Vector_Free(vector);
}

TEST(Vector, PushBack_WorksStanderdTypes) {
    Vector<char> vector;
    EXPECT_TRUE(Vector_Init(vector, 8));
    
    EXPECT_TRUE(Vector_PushBack(vector, 'h'));
    EXPECT_TRUE(Vector_PushBack(vector, 'W'));
    EXPECT_TRUE(Vector_PushBack(vector, '8'));

    EXPECT_EQ(vector.data[0], 'h');
    EXPECT_EQ(vector.data[1], 'W');
    EXPECT_EQ(vector.data[2],  '8');

    Vector_Free(vector);
}

TEST(Vector, PushBackCostomTypes) {
    Vector<Foo3> vector;
    EXPECT_TRUE(Vector_Init(vector, 8));

    Foo3 foo {
        {876, 876.876},
        {'u', 98.87, 98765432}
    };

    Foo3 foo2 = {
        {98548, 765.53},
        {'h', 9.76, 987654345678765}
    };

    EXPECT_TRUE(Vector_PushBack(vector, foo));
    EXPECT_TRUE(Vector_PushBack(vector, foo2));

    EXPECT_EQ(vector.data[0].foo1.bob, foo.foo1.bob);
    EXPECT_EQ(vector.data[0].foo1.larry, foo.foo1.larry);
    EXPECT_EQ(vector.data[0].foo2.jill, foo.foo2.jill);
    EXPECT_EQ(vector.data[1].foo2.harry, foo2.foo2.harry);
    EXPECT_EQ(vector.data[1].foo2.frank, foo2.foo2.frank);
    EXPECT_EQ(vector.data[1].foo2.jill, foo2.foo2.jill);

    Vector_Free(vector);
}

TEST(Vector, PopBack_WorksWithStanderdTypes) {
    Vector<long long> vector;
    EXPECT_TRUE(Vector_Init(vector, 8));

    long long foo1 = 7645653466;
    long long foo2 = 123456789876567;
    Vector_PushBack(vector, foo1);
    Vector_PushBack(vector, foo2);

    long long out;
    EXPECT_TRUE(Vector_PopBack(vector, out));
    EXPECT_EQ(vector.size, 1);
    EXPECT_EQ(out, foo2);
    EXPECT_TRUE(Vector_PopBack(vector, out));
    EXPECT_EQ(vector.size, 0);
    EXPECT_EQ(out, foo1);

    Vector_Free(vector);
}

TEST(Vector, PopBack_WorksWithCostomTypes) {
    Vector<Foo2> vector;
    EXPECT_TRUE(Vector_Init(vector, 8));

    Foo2 foo1 = {'g', 3.14f, 9876};
    Foo2 foo2 = {'3', 2.159, 10876543345};
    Vector_PushBack(vector, foo1);
    Vector_PushBack(vector, foo2);

    Foo2 out;
    EXPECT_TRUE(Vector_PopBack(vector, out));
    EXPECT_EQ(vector.size, 1);
    EXPECT_EQ(out.frank, foo2.frank);
    EXPECT_EQ(out.harry, foo2.harry);
    EXPECT_EQ(out.jill, foo2.jill);
    EXPECT_TRUE(Vector_PopBack(vector, out));
    EXPECT_EQ(vector.size, 0);
    EXPECT_EQ(out.frank, foo1.frank);
    EXPECT_EQ(out.harry, foo1.harry);
    EXPECT_EQ(out.jill, foo1.jill);

    Vector_Free(vector);
}

TEST(Vector, At_worksWithStanderdTypes) {
    Vector<char> vector;
    Vector_Init(vector, 8);

    Vector_PushBack(vector, 'h');
    Vector_PushBack(vector, 'e');
    Vector_PushBack(vector, 'l');
    Vector_PushBack(vector, 'l');
    Vector_PushBack(vector, 'o');
    Vector_PushBack(vector, 'o');

    char foo;
    EXPECT_TRUE(Vector_At(vector, 0, foo));
    EXPECT_EQ(foo, 'h');
    EXPECT_TRUE(Vector_At(vector, 1, foo));
    EXPECT_EQ(foo, 'e');
    EXPECT_TRUE(Vector_At(vector, 2, foo));
    EXPECT_EQ(foo, 'l');
    EXPECT_TRUE(Vector_At(vector, 3, foo));
    EXPECT_EQ(foo, 'l');
    EXPECT_TRUE(Vector_At(vector, 4, foo));
    EXPECT_EQ(foo, 'o');
    EXPECT_TRUE(Vector_At(vector, 5, foo));
    EXPECT_EQ(foo, 'o');

    Vector_Free(vector);
}

TEST(Vector, At_worksWithCostomTypes) {
    Vector<Foo1> vector;
    Vector_Init(vector, 8);

    Foo1 foo0 = {83, 2.3499283};
    Foo1 foo1 = {23, 345.234};
    Foo1 foo2 = {2546, 645.354};

    Vector_PushBack(vector, foo0);
    Vector_PushBack(vector, foo1);
    Vector_PushBack(vector, foo2);

    Foo1 foo;
    EXPECT_TRUE(Vector_At(vector, 0, foo));
    EXPECT_EQ(foo.bob, foo0.bob);
    EXPECT_EQ(foo.larry, foo0.larry);
    EXPECT_TRUE(Vector_At(vector, 1, foo));
    EXPECT_EQ(foo.bob, foo1.bob);
    EXPECT_EQ(foo.larry, foo1.larry);
    EXPECT_TRUE(Vector_At(vector, 2, foo));
    EXPECT_EQ(foo.bob, foo2.bob);
    EXPECT_EQ(foo.larry, foo2.larry);

    Vector_Free(vector);
}

TEST(Vector, Back_Works) {
    Vector<char> vector;
    Vector_Init(vector, 8);

    Vector_PushBack(vector, 'h');
    Vector_PushBack(vector, 'e');
    Vector_PushBack(vector, 'l');
    Vector_PushBack(vector, 'l');
    Vector_PushBack(vector, 'o');

    char* out;
    EXPECT_TRUE(Vector_Back(vector, out));
    EXPECT_EQ(out, &vector.data[vector.size - 1]);

    Vector_PopBack(vector);

    EXPECT_TRUE(Vector_Back(vector, out));
    EXPECT_EQ(out, &vector.data[vector.size - 1]);


    Vector_Free(vector);

}

TEST(Vector, Back_FailsOnEmptyVector) {
    Vector<char> vector;
    Vector_Init(vector, 8);

    char* out;

    EXPECT_FALSE(Vector_Back(vector, out));
    EXPECT_EQ(out, nullptr);

    Vector_Free(vector);
}

TEST(Vector, Front_Works) {
    Vector<int> vector;
    Vector_Init(vector, 8);

    Vector_PushBack(vector, 32);
    Vector_PushBack(vector, 700);
    Vector_PushBack(vector, 4545);

    int* out;
    EXPECT_TRUE(Vector_Front(vector, out));
    EXPECT_EQ(out, &vector.data[0]);

    Vector_Free(vector);
}

TEST(Vector, Front_FailsOnEmptyVector) {
    Vector<char> vector;
    Vector_Init(vector, 8);

    char* out;

    EXPECT_FALSE(Vector_Front(vector, out));
    EXPECT_EQ(out, nullptr);

    Vector_Free(vector);
}