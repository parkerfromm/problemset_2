#include <bit>
#include <bitset>
#include <bit>
#include <map>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include "time.h"

// (i)
using namespace std;

template <size_t N>
unsigned int popcount_1(bitset<N> &b)
{

    unsigned int count = 0;
    for (int i = 0; i < N; i++)
    {
        // if (b[i] == 1)
        // {
        //     count++;
        // }
        // else
        // {
        //     continue;
        // }

        if (b.test(i))
        {
            count++;
        }
    }

    return count;
};

template <size_t N>
unsigned int countr_zero_1(bitset<N> &b)
{

    unsigned int count = 0;
    int i = 0;

    while (i < N && !b.test(i))
    {
        count++;
        i++;
    }
    return count;
};

// (ii)

template <size_t N>
unsigned int popcount_recursive(const std::bitset<N> &b, unsigned long long total_count, size_t split_count)
{
    // constexpr size_t num_bits= 64;
    constexpr size_t num_even_splits = N / 64;
    size_t remainder_bits = N % 64;

    // starting number for split count should be 0;

    if (split_count == num_even_splits && remainder_bits == 0)
    {
        return total_count;
    }

    unsigned long long count;

    if (split_count < num_even_splits)
    {

        bitset<N> mask = bitset<N>().set();
        bitset<N> masked = (mask >> (N - 64));
        // mask = mask - 1;

        bitset<N> shifted = b >> (64 * split_count);

        // count = std::__popcount((b >> (64 * split_count)).to_ullong());
        count = __popcount((shifted & masked).to_ullong());
        return popcount_recursive(b, total_count + count, split_count + 1);
    }
    else if (split_count == num_even_splits && remainder_bits != 0)
    {
        // count = std::__popcount((b >> ((64 * split_count))).to_ullong());
        // remainder_bits = 0;
        // return popcount_recursive(b, total_count + count, split_count);

        std::bitset<N> mask = bitset<N>().set();
        //(bitset<N>(1) << remainder_bits) - 1;
        bitset<N> masked = (mask >> (64 * split_count));
        bitset<N> shifted = b >> (64 * split_count);
        count = __popcount((shifted & mask).to_ullong());
        return total_count + count;
    }

    return total_count;
};

template <size_t N>
unsigned int popcount_2(bitset<N> &b)
{
    return popcount_recursive(b, 0, 0);
};

template <size_t N>
unsigned int countr_zeros_recurssive(const std::bitset<N> &b, unsigned long long total_count, size_t split_count)
{
    size_t num_even_splits = N / 64;
    size_t remainder_bits = N % 64;
    if (split_count == num_even_splits && remainder_bits == 0)
    {
        return total_count;
    }

    if (split_count < num_even_splits)
    {
        bitset<N> mask = bitset<N>().set();
        bitset<N> masked = mask >> (N - 64);
        bitset<N> shifted = b >> (64 * split_count);

        unsigned long long count = std::__countr_zero((shifted & masked).to_ullong());
        if (total_count + count != (split_count + 1) * 64)
        {
            return total_count + count;
        }
        else
        {
            return countr_zeros_recurssive(b, total_count + count, split_count + 1);
        }
    }
    else if (split_count == num_even_splits && remainder_bits != 0)
    {
        bitset<N> mask = bitset<N>().set();

        bitset<N> masked = mask >> (N - 64);

        bitset<N> shifted2 = b >> (64 * split_count) + remainder_bits;

        unsigned long long count1 = std::__countr_zero((shifted2 & mask).to_ullong());
        return total_count + count1;
    }

    return total_count;
};

template <size_t N>
unsigned long long countr_zeros_2(const bitset<N> &b)
{
    return countr_zeros_recurssive(b, 0, 0);
};

template <size_t N>
struct BitSetLess
{
    // checks if bit1 is less than bit2, returns false otherwise
    bool operator()(const bitset<N> &bit1, const bitset<N> &bit2) const
    {
        bool status = false;
        for (int i = N; i > 0; i--)
        {
            if (bit1[i - 1] == bit2[i - 1])
            {
                continue;
            }
            else if (bit1[i - 1] > bit2[i - 1])
            {
                return status;
            }
            else
            {
                status = true;
                return status;
            }
        }
    }
};

template <size_t N>
struct BitSetLessThan
{

    bool operator()(const bitset<N> &bit1, const bitset<N> &bit2) const
    {

        if (N <= 64)
        {
            return bit1.to_ullong() < bit2.to_ullong();
        }

        bool status = false;
        size_t num_splits;
        size_t remainder_bits = N % 64;
        if (remainder_bits != 0)
        {
            num_splits = (N / 64) + 1;
        }
        else
        {
            num_splits = N / 64;
        }

        // if (split_count != num_splits){

        // start split_count at zero still

        for (int i = 0; i < num_splits; i++)
        {

            size_t shift_amount = (N - 64 * (i + 1));

            if (shift_amount < 0)
            {
                shift_amount = 0;
            }

            auto shifted1 = bit1 >> shift_amount;
            auto shifted2 = bit2 >> shift_amount;

            if (shifted1.to_ullong() == shifted2.to_ullong() && i + 1 < num_splits)
            {
                // recursiveCheck(bit1, bit2, split_count + 1);
                continue;
            }
            else if (shifted1.to_ullong() < shifted2.to_ullong())
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
};

template <size_t N>
unsigned long long count_occupied_orbitals_i(size_t start, size_t end, const bitset<N> &bit)
{
    unsigned long long count = 0;
    int i = start;

    while (i < end + 1)
    {
        if (bit[i] == 1)
        {
            count++;
        }
        i++;
    }
    // for (int i = start; i < end + 1; i++)
    // {
    //     if (bit[i] == 1)
    //     {
    //         count++;
    //     }
    // }
    return count;
};

template <size_t N>
unsigned long long count_occupied_orbitals_ii(size_t start, size_t end, const bitset<N> &bits)
{
    unsigned long long count = 0;

    const size_t dist = end - start + 1;

    size_t num_splits = dist / 64;
    size_t remainder_bits = dist % 64;

    bitset<N> shifted = bits >> start;

    // bitset<N> mask((1ULL << ((end - start) + 1)) - 1);

    if (remainder_bits != 0)
    {
        num_splits++;
        bitset<N> mask((1ULL << ((end - start) + 1)) - 1);
        shifted = (bits >> start) & mask;
    }

    // bitset<N> shifted = bits >> start;

    // bitset<N> mask((1ULL << ((end - start) + 1)) - 1);

    // bitset<N> masked = (bits >> start) & mask;

    for (int i = 0; i < num_splits; i++)
    {

        count += std::__popcount((shifted >> (64 * i)).to_ullong());
    }

    return count;
};

void test_occupied_orbitals(int i)
{

    std::bitset<128> orbitals1(std::string("100101100101"));
    std::bitset<128> orbitals2(std::string("11111111111111111111111111111111"));

    struct test
    {
        std::bitset<128> orbitals;
        size_t start;
        size_t end;
        size_t expected;
    };

    std::vector<test> tests = {
        {orbitals1, 0, 11, 6},
        {orbitals2, 0, 31, 32},
        {orbitals1, 3, 8, 3},
        {orbitals2, 4, 20, 17},
    };

    for (const auto &test : tests)
    {
        unsigned long long result;
        //timer t("orbitials " + str(i));
        if (i == 1)
        {
           // timer t1("orbitials 1");
            //t1.start();
            result = count_occupied_orbitals_i(test.start, test.end, test.orbitals);
            //t1.stop();
            //t1.print();

            //t1.reset();
        }
        else
        {
            //t.start();
            result = count_occupied_orbitals_ii(test.start, test.end, test.orbitals);
            //t.stop();
            //t.print();

            //t.reset();
        }
        if (result != test.expected)
        {
            std::cout << "Test Failed: Expected " << test.expected << ", got " << result << std::endl;
        }
        else
        {
            std::cout << "Test Passed: Expected " << test.expected << ", got " << result << std::endl;
        }
    }
}

int main()
{

    std::bitset<128> test1;
    test1.set(8);
    test1.set(101);
    test1.set(55);
    test1.set(120);

    // timer t("Popcount loop");
    // t.start();
    unsigned int pop_count_i = popcount_1(test1);
    // t.stop();
    // t.print();

    // t.reset();
    // t.set_label("Countr loop");
    // t.start();
    unsigned int countr_zero_i = countr_zero_1(test1);
    // t.stop();
    // t.print();

    // t.reset();
    // t.set_label("Popcount Recursive");
    // t.start();
    unsigned int pop_count_ii = popcount_2(test1);
    // t.stop();
    // t.print();

    // t.reset();
    // t.set_label("Countr Recursive");
    // t.start();
    unsigned int countr_zero_ii = countr_zeros_2(test1);
    // t.stop();
    // t.print();

    cout << " test 1 (i): set bits = " << pop_count_i << ", trailing zeros = "
         << countr_zero_i << endl;

    cout << " test 1 (iI): set bits = " << pop_count_ii << ", trailing zeros = "
         << countr_zero_ii << endl;
    // should have 4 ones, and 8 trailing zeros

    // test on larger to see time difference sorry i dont realy have time but 128 was showing no
    // time difference that was noticabel enough to see on the computer

    std::map<std::bitset<8>, int, BitSetLess<8>> map_i;
    map_i[std::bitset<8>("00100110")] = 1;
    map_i[std::bitset<8>("11100010")] = 2;
    map_i[std::bitset<8>("01010101")] = 3;

    // Verify the map is properly sorted
    for (const auto &pair : map_i)
    {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    std::map<std::bitset<8>, int, BitSetLessThan<8>> map_ii;
    map_ii[std::bitset<8>("00100110")] = 1;
    map_ii[std::bitset<8>("11100010")] = 2;
    map_ii[std::bitset<8>("01010101")] = 3;

    // Verify the map is properly sorted
    for (const auto &pair_ii : map_ii)
    {
        std::cout << pair_ii.first << ": " << pair_ii.second << std::endl;
    }

    test_occupied_orbitals(1);
    test_occupied_orbitals(2);

    std::bitset<12800> test4 = std::bitset<12800>().set();

    timer t("Popcount loop");
    t.start();
    unsigned long long popcount1 = popcount_1(test4);
    t.stop();
    t.print();

    t.reset();

    t.set_label("Popcount Recursive");
    t.start();
    unsigned long long popcounnt2 = popcount_2(test4);
    t.stop();
    t.print();

    std::bitset<12800> test5;

    t.set_label("Countr loop");
    t.start();
    unsigned int countr_1 = countr_zero_1(test5);
    t.stop();
    t.print();

    t.reset();

    t.reset();
    t.set_label("Countr Recursive");
    t.start();
    unsigned int countr_2 = countr_zeros_2(test5);
    t.stop();
    t.print();

    return 0;
}