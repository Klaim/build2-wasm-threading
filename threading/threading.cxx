#include <mutex>
#include <atomic>
#include <thread>
#include <iostream>
#include <vector>

using namespace std;

int n = 0;
mutex m;
atomic<unsigned long long> a{0};
bool verbose = false;

static void
f (int c)
{
  for (int i = 0; i != c; )
  {
    if (m.try_lock ())
    {
      i++;
      n++;
      if(verbose) std::cout << "+";
      m.unlock ();
    }
    else
    {
      a.fetch_add (1, memory_order_relaxed);
      if(verbose) std::cout << "#";
    }
  }
}

int
main (int argc, char* argv[])
{
  if(argc == 2 && std::string(argv[1]) == "-v")
    verbose = true;

  vector<thread> threads;

  for(int tidx = 0; tidx < 57; ++tidx)
  {
    threads.push_back(thread(f, 4000));
    threads.push_back(thread(f, 3000));
    threads.push_back(thread(f, 2000));
    threads.push_back(thread(f, 1000));
  }

  for(auto& t : threads) t.join();

  if(verbose) cout << '\n';
  cout << n << endl;
  cerr << a.load () << endl;
}
