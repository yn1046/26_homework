#include <iostream>
#include <time.h>
#include <vector>
#include <chrono>
#include <thread>
#include <execution>

using namespace std;
namespace chr = std::chrono;
using cl = chr::steady_clock;

void part_sum(vector<int> &list, int from, int to, int &lsum) {
    int psum = 0;
    for (int i = from; i < to; ++i) psum += list[i];

    lsum += psum;
}

int main() {
    const int N = 100000000;
    const int M = N / 8;
    vector<int> list(N);

    srand(time(0));

    for (int i = 0; i < N; ++i) {
        list[i] = (rand() % N);
    }

    // Суммирование без параллелизма
    int lsum = 0;
    cl::time_point begin = cl::now();
    for (int i = 0; i < N; ++i) lsum += list[i];
    cl::time_point end = cl::now();


    cout << "Sum is: " << lsum << endl;
    cout << "Time elapsed (seq): " << chr::duration_cast<chr::milliseconds>(end - begin).count() << endl;


    // Суммирование через разделение на потоки
    lsum = 0;
    vector<thread> ts;
    cl::time_point mt_begin = cl::now();
    for (int i = 0; i < N; i += M) {
        ts.emplace_back(part_sum, ref(list), i, i + M, ref(lsum));
    }
    for (auto &t : ts) t.join();
    cl::time_point mt_end = cl::now();

    cout << "Sum is: " << lsum << endl;
    cout << "Time elapsed (par): " << chr::duration_cast<chr::milliseconds>(mt_end - mt_begin).count() << endl;


    // Суммирование встроенной функцией reduce с параллельной политикой исполнения
    lsum = 0;
    cl::time_point reduce_begin = cl::now();
    lsum = reduce(execution::par, list.cbegin(), list.cend());
    cl::time_point reduce_end = cl::now();

    cout << "Sum is: " << lsum << endl;
    cout << "Time elapsed (reduce): " << chr::duration_cast<chr::milliseconds>(reduce_end - reduce_begin).count() << endl;


    return 0;
}
