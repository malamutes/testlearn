#include "wrappers.hpp"
#include <chrono>
#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <thread>

std::map<std::string, std::string> g_pages;
std::mutex g_pages_mutex;

void save_page(const std::string &url, int threadNum) {
  // simulate a long page fetch
  std::lock_guard<std::mutex> guard(g_pages_mutex);
  MyWrappers::printWithArg("STARTING THREAD PROCESS FOR", threadNum);
  std::this_thread::sleep_for(std::chrono::seconds(5));
  std::string result = "fake content";

  MyWrappers::printWithArg("ABOUT TO EDIT CRITICAL SECTION", threadNum);
  g_pages[url] = result;

  MyWrappers::printWithArg("MODIFIED CRITICAL SECTION", threadNum);
}

int main() {
  std::thread t1(save_page, "http://foo", 1);
  std::thread t2(save_page, "http://bar", 2);
  t1.join();
  t2.join();

  // safe to access g_pages without lock now, as the threads are joined
  for (const auto &[url, page] : g_pages)
    std::cout << url << " => " << page << '\n';
}