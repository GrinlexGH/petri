#include <cassert>
#include <vector>

#include <fmt/format.h>

#include "sort.hpp"

template <auto Func>
void Test() {
    // 1. Уже отсортирован
    {
        int a[] = { 1, 2, 3, 4, 5 };

        Func(a, a + 5);

        assert(a[0] == 1);
        assert(a[1] == 2);
        assert(a[2] == 3);
        assert(a[3] == 4);
        assert(a[4] == 5);
    }

    // 2. Обратный порядок
    {
        int a[] = { 5, 4, 3, 2, 1 };

        Func(a, a + 5);

        assert(a[0] == 1);
        assert(a[1] == 2);
        assert(a[2] == 3);
        assert(a[3] == 4);
        assert(a[4] == 5);
    }

    // 3. Один элемент
    {
        int a[] = { 42 };

        Func(a, a + 1);

        assert(a[0] == 42);
    }

    // 4. Два элемента, не отсортированы
    {
        int a[] = { 2, 1 };

        Func(a, a + 2);

        assert(a[0] == 1);
        assert(a[1] == 2);
    }

    // 5. Повторяющиеся элементы
    {
        int a[] = { 3, 1, 2, 1, 3 };

        Func(a, a + 5);

        assert(a[0] == 1);
        assert(a[1] == 1);
        assert(a[2] == 2);
        assert(a[3] == 3);
        assert(a[4] == 3);
    }
}

int main() {
    Test<QuickSort>();
    Test<InsertionSort>();
    Test<MergeSort>();
    Test<CountingSort>();
    Test<SelectionSort>();
    Test<LSDRadixSort>();
}
