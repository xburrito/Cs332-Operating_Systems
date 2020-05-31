#include <iostream>
#include <unistd.h> // usleep()
#include <math.h> // pow(x,y)
#include <cstdlib>
#include <ctime>
#include <thread>
#include <mutex>
using namespace std;

int north, south;
// Generates a random number between 1 and 3
int randNum = (rand() % 3) + 1;
mutex mutex1, mutex2;

void thread_north(){
  mutex1.lock();
  north++;
  cout << "North Tunbridge #" << north << " farmer can cross the bridge \n";
  cout << "North Tunbridge #" << north << " is travelling on the bridge... \n";
  usleep(randNum * pow(10,6)); // Sleeps for a random time between 1 to 3 seconds
  cout << "North Tunbridge #" << north << " farmer has left the bridge\n\n";
  // Mutex 2 is locked from acting until mutex 1 has been unlocked
  mutex2.lock();
  mutex2.unlock();
  mutex1.unlock();
}

void thread_south(){
  mutex1.lock();
  south++;
  cout << "South Tunbridge #" << south << " farmer can cross the bridge \n";
  cout << "South Tunbridge #" << south << " is travelling on the bridge... \n";
  usleep(randNum * pow(10,6)); // Sleeps for a random time between 1 to 3 seconds
  cout << "South Tunbridge #" << south << " farmer has left the bridge \n\n";
  // Mutex 2 is locked from acting until mutex 1 has been unlocked
  mutex2.lock();
  mutex1.unlock();
  mutex2.unlock();
}

// Driver Code
int main(){
  while(true){

    thread t1(thread_north);
    thread t2(thread_south);

    t1.join();
    t2.join();
  }

  return 0;
}
