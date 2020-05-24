/*
使用std::async实现std::for_each
*/
#include <iterator>
#include <algorithm>
#include <future>

template <typename Iterator, typename Func>
void parallel_for_each(Iterator first, Iterator last, Func f)
{
    unsigned long const length = std::distance(first, last);

    if (!length)
        return;

    unsigned long const min_per_thread = 25;

    if (length < (2 * min_per_thread))
    {
        // 如果数据小于两个线程的能力，直接使用单线程for_each
        std::for_each(first, last, f);
    }
    else
    {
        Iterator const mid_point = first + length / 2;
        // 对数据分为两部分，异步执行一部分
        std::future<void> first_half = std::async(&parallel_for_each<Iterator, Func>, first, mid_point, f);
        parallel_for_each(mid_point, last, f); // 迭代执行另一部分
        first_half.get();                      // 通过future传播异常，后面可以跟异常处理
    }
}