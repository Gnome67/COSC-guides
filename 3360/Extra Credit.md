# Exam 1
```cpp
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main()
{
  cout << "I am the parent process" << endl; //the beginning process
  for(int i=0; i<3; i++) { //for 3 children, make 3 children processes
    if(fork() == 0) { //if the clone doesnt return an error,
      cout << "I am the child process " << i << endl; //you made a child process congrats
      if(i == 1) { //for the second child
        if(fork() == 0) { //if the clone doesnt return an error,
          cout << "I am grandchild process " << i << endl; //you have a grandchild process congrats
          _exit(0); //kill the grandchild
        }
        wait(nullptr); //guarantees it will happen in certain order
      }
      _exit(0); //kills the chid
    }
    wait(nullptr); // guarantees it will happen in certain order
  }
  return 0;
}
```

# Exam 2

Banker's Algorithm:

Deadlock Detection Algorithm:

# Exam 3

First in First Out

Least Recently Used

Optimal Policy

Clock Policy :skull:
