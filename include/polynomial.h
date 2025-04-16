#pragma once
#include "List.h"

using namespace std;
const size_t MAX_DEGREE = 9;

class Monom
{
public:
    size_t degree;
    double ind;

    Monom(size_t deg = 0, double ind_ = 0) : degree(deg), ind(ind_)
    {
        if (!is_deg_correct())
            throw invalid_argument("degree is out of range");
    }

    size_t get_x_degree() const noexcept
    {
        return degree / 100;
    }

    double get_ind() const noexcept
    {
        return ind;
    }

    size_t get_y_degree() const noexcept
    {
        return (degree / 10) % 10;
    }

    size_t get_z_degree() const noexcept
    {
        return degree % 10;
    }

    void set_ind(const double ind_) noexcept
    {
        ind = ind_;
    }

    bool is_deg_correct() const noexcept
    {
        return (get_x_degree() <= MAX_DEGREE && get_y_degree() <= MAX_DEGREE && get_z_degree() <= MAX_DEGREE);
    }

    Monom operator+(const Monom& monom)
    {
        if (degree == monom.degree)
            return Monom(degree, ind + monom.ind);
        throw std::domain_error("domain_error");
    }

    Monom operator-(const Monom& monom)
    {
        if (degree == monom.degree)
            return Monom(degree, ind - monom.ind);
        throw std::domain_error("domain_error");
    }

    Monom operator*(const double scalar)
    {
        Monom res(degree, ind * scalar);
        if (res.get_ind() == 0)
            return Monom(0, 0);
        return res;
    }

    Monom operator*(const Monom& monom)
    {
        size_t x_deg = get_x_degree() + monom.get_x_degree();
        size_t y_deg = get_y_degree() + monom.get_y_degree();
        size_t z_deg = get_z_degree() + monom.get_z_degree();
        size_t new_deg = x_deg * 100 + y_deg * 10 + z_deg;
        double new_ind = ind * monom.ind;
        Monom mon(new_deg, new_ind);
        return mon;
    }

    bool operator==(const Monom& other) const 
    {
        return (degree == other.degree) && (ind == other.ind);
    }

    bool operator!=(const Monom& other) const 
    {
        return !(*this == other);
    }
};


class Polinom: public List<Monom>
{
protected:
    List<Monom*> list;
public:
    Polinom(): List<Monom>() {}

    ~Polinom()
    {
        clear();
    }

    Polinom(const Polinom& polinom) : List<Monom>(polinom) {}

    Polinom operator+(const Polinom& polinom) const
    {
        Polinom res; 
        Iterator it1 = begin();
        Iterator it2 = polinom.begin();

        while (it1 != end() && it2 != polinom.end()) {
            if ((*it1).degree == (*it2).degree) {
                Monom sum = (*it1) + (*it2);
                if (sum.get_ind() != 0) {  
                    res.push_back(sum);
                }
                ++it1;
                ++it2;
            }
            else if ((*it1).degree > (*it2).degree) {
                res.push_back(*it1);
                ++it1;
            }
            else {
                res.push_back(*it2);
                ++it2;
            }
        }
        while (it1 != end()) {
            res.push_back(*it1);
            ++it1;
        }
        while (it2 != polinom.end()) {
            res.push_back(*it2);
            ++it2;
        }
        return res;
    }

    Polinom& operator=(const Polinom& polinom)
    {
        if (this != &polinom)
            List<Monom>::operator=(polinom);
        return *this;
    }

    Polinom operator*(double scalar) const
    {
        Polinom res;
        for (Iterator it = begin(); it != end(); ++it)
        {
            res.push_back((*it) * scalar);
        }
        return res;
    }

    Polinom operator*(const Monom& monom) const
    {
        Polinom res;
        for (Iterator it = begin(); it != end(); ++it) 
        {
            Monom product = (*it) * monom;
            if (product.get_ind() != 0) {
                res.push_back(product);
            }
        }
        return res;
    }

    Polinom operator*(const Polinom& polinom) const
    {
        Polinom res;
        for (Iterator it1 = begin(); it1 != end(); ++it1)
        {
            for (Iterator it2 = polinom.begin(); it2 != polinom.end(); ++it2)
            {
                Monom prod;
                prod = (*it1) * (*it2);
                if (prod.get_ind() != 0)
                    res.push_back(prod);
            }
        }
        return res;
    }
};