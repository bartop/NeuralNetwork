#pragma once

#include <thread>
#include <algorithm>

/** Dla poprawy składni - makro, helpery */

template <typename Container>
struct __pforeach__helper {
    Container &&c;
    template <typename Arg>
    void operator=(Arg&& arg) {
        parallel_for_each(std::forward<Container>(c), std::forward<Arg>(arg));
    }
};

template <typename Container>
__pforeach__helper<Container> __create__pforeach__helper(Container &&c)
{
    return __pforeach__helper<Container>(__pforeach__helper<Container>{c});
}

#define pforeach(Z,C) __create__pforeach__helper(C)=[&](Z)

/** Właściwe pętle */

template <typename Iterator, typename Task>
void parallel_for(Iterator first, Iterator last, const Task &task,
                   unsigned number_of_threads = std::thread::hardware_concurrency())
{
    std::vector<std::thread> threads;
    unsigned size = std::distance(first, last);
    unsigned tasks_per_thread = size/number_of_threads;

    auto tasks_set = [&task](Iterator first, Iterator last)
                            {
                                std::for_each(first, last, task);
                            };
    Iterator next;

    //każdy wątek dostaje zbiór zadań
    for (unsigned i = 0; i < number_of_threads-1; ++i)
    {
        next = first;
        std::advance(next, tasks_per_thread);
        threads.emplace_back(std::thread(tasks_set, first, next));
        first = next;
    }

    //w wątku głównym brakujące iteracje
    tasks_set(first, last);

    for (auto &t : threads)
    {
        t.join();
    }
}

template <typename Container, typename Task>
void parallel_for_each(Container &container, const Task &task, unsigned number_of_threads = std::thread::hardware_concurrency())
{
    parallel_for(std::begin(container), std::end(container), task, number_of_threads);
}
