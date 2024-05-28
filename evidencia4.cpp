#include <iostream>
#include <vector>
#include <map>
#include <thread>
#include <mutex>
#include <algorithm>

std::mutex aux_mutex;
std::map<int, int> aux;

void process_input(int n) {
    int x, y;
    for (int i = 0; i < n; ++i) {
        std::cin >> x >> y;
        std::lock_guard<std::mutex> lock(aux_mutex);
        aux[x] += 1;
        aux[y] -= 1;
    }
}

void find_max_time_and_people(int& _max, int& people) {
    int curr = 0;
    for (const auto& pair : aux) {
        curr += pair.second;
        if (curr > people) {
            people = curr;
            _max = pair.first;
        }
    }
}

int main() {
    int n;
    std::cin >> n;

    // Create a thread to process input
    std::thread input_thread(process_input, n);
    input_thread.join();

    // Variables to store the results
    int _max = 0;
    int people = 0;

    // Find the time and maximum number of people concurrently
    std::thread processing_thread(find_max_time_and_people, std::ref(_max), std::ref(people));
    processing_thread.join();

    // Output the result
    std::cout << _max << " " << people << std::endl;

    return 0;
}

