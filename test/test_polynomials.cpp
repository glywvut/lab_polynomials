#include "gtest.h"
#include "polynomial.h"

TEST(TestMonom, can_create_monom)
{
    ASSERT_NO_THROW(Monom m(111, 1));
}

TEST(TestMonom, can_create_zero_monom)
{
    ASSERT_NO_THROW(Monom m);
}

TEST(TestMonom, cant_create_monom_with_too_large_degree)
{
    ASSERT_ANY_THROW(Monom m(1100, 5));
}

TEST(TestMonom,can_get_x_degree)
{
    Monom m(123, 1);

    EXPECT_EQ(m.get_x_degree(), 1);
}

TEST(TestMonom, can_get_y_degree)
{
    Monom m(123, 1);

    EXPECT_EQ(m.get_y_degree(), 2);
}

TEST(TestMonom, can_get_z_degree)
{
    Monom m(123, 1);

    EXPECT_EQ(m.get_z_degree(), 3);
}

TEST(TestMonom, can_addict_monoms)
{
    Monom m1(123, 1);
    Monom m2(123, 2);
    Monom res = m1 + m2;

    EXPECT_EQ(res.degree, 123);
    EXPECT_EQ(res.get_ind(), 3);
}

TEST(TestMonom, cant_addict_monoms_with_different_degrees)
{
    Monom m1(321, 1);
    Monom m2(123, 1);

    ASSERT_ANY_THROW(m1 + m2);
}

TEST(TestMonom, can_sub_monoms)
{
    Monom m1(123, 1);
    Monom m2(123, 2);
    Monom res = m2 - m1;

    EXPECT_EQ(res.degree, 123);
    EXPECT_EQ(res.get_ind(), 1);
}

TEST(TestMonom, can_myltiply_with_a_scalar)
{
    Monom m1(123, 1);
    Monom m2 = m1 * 5;

    EXPECT_EQ(m2.degree, 123);
    EXPECT_EQ(m2.get_ind(), 5);
}

TEST(TestMonom, can_myltiply_monoms)
{
    Monom m1(123, 1);
    Monom m2 = m1 * 5;
    Monom m3 = m1 * m2;
    EXPECT_EQ(m3.degree, 246);
    EXPECT_EQ(m2.get_ind(), 5);
}

TEST(TestPolinom, can_create_polynom)
{
    ASSERT_NO_THROW(Polinom p);
}

class TestPolinomF : public ::testing::Test
{
protected:
    Polinom* p1, * p2;
public:
    void SetUp()
    {
        p1 = new Polinom;
        (*p1).push_back(Monom(102, -3));
        (*p1).push_back(Monom(137, 1.5));
        p2 = new Polinom;
        (*p2).push_back(Monom(102, 2));
        (*p2).push_back(Monom(721, -10));
        (*p2).push_back(Monom(300, 0.5));

    }
    void TearDown()
    {
        delete p1;
        delete p2;
    }
};

TEST_F(TestPolinomF, can_mult_with_scalar)
{
    Polinom res = *(this->p1) * 2;

    List<Monom>::Iterator it = res.begin();
    EXPECT_EQ((*it).degree, 102);
    EXPECT_EQ((*it).get_ind(), -6);

    ++it;
    EXPECT_EQ((*it).degree, 137);
    EXPECT_EQ((*it).get_ind(), 3);
}

TEST_F(TestPolinomF, can_mult_polynoms)
{
    Polinom res = *(this->p1) * *(this->p2);

    List<Monom>::Iterator it = res.begin();
    EXPECT_EQ((*it).degree, 204);
    EXPECT_EQ((*it).get_ind(), -6);

    ++it;
    EXPECT_EQ((*it).degree, 823);
    EXPECT_EQ((*it).get_ind(), 30);

    ++it;
    EXPECT_EQ((*it).degree, 402);
    EXPECT_EQ((*it).get_ind(), -1.5);
}