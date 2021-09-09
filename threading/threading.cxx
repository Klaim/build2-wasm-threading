#include <mutex>
#include <atomic>
#include <thread>
#include <iostream>

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


  thread t1 (f, 4000), t2 (f, 3000), t3 (f, 2000), t4 (f, 1000);

  t1.join ();
  t2.join ();
  t3.join ();
  t4.join ();

  if(verbose) cout << '\n';
  cout << n << endl;
  cerr << a.load () << endl;
}
