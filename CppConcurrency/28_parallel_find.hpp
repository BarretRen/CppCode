//使用std::async实现的并行find算法
#include <atomic>
#include <future>

template <typename Iterator, typename MatchType> // done为已经找到的标识
Iterator parallel_find_impl(Iterator first, Iterator last, MatchType match,
                            std::atomic<bool> &done)
{
    try
    {
        unsigned long const length = std::distance(first, last);
        unsigned long const min_per_thread = 25;
        if (length < (2 * min_per_thread)) // 如果数据不足以分成两部分，直接单线程查找
        {
            for (; (first != last) && !done.load(); ++first) // 4
            {
                if (*first == match)
                {
                    done = true; // 如果找到，将done置为true，这样其他线程在进入for循环时判断done为true会直接返回
                    return first;
                }
            }
            return last; // 6
        }
        else
        {
            Iterator const mid_point = first + (length / 2); // 7数据分成两部分
            // 异步查找第一部分，同时继续传递原子bool done
            std::future<Iterator> async_result = std::async(&parallel_find_impl<Iterator, MatchType>,
                                                            mid_point, last, match, std::ref(done));
            // 迭代执行另一部分
            Iterator const direct_result = parallel_find_impl(first, mid_point, match, done);
            // 返回结果，direct_result == mid_point，意味着结果在第一部分中，返回future期望值结果
            return (direct_result == mid_point) ? async_result.get() : direct_result;
        }
    }
    catch (...)
    {
        done = true; // 11
        throw;
    }
}

template <typename Iterator, typename MatchType>
Iterator parallel_find(Iterator first, Iterator last, MatchType match)
{
    std::atomic<bool> done(false);                       // 原子bool类型，用于标识已经找到
    return parallel_find_impl(first, last, match, done); // 12
}