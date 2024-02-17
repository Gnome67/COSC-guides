# Part 0: Before we begin

This assignment (and the guide by extension) assumes that you have a basic understanding of C++. If not, Google and AI (ChatGPT) are your friends. Please note that that does not mean you should rely on AI to code for you. You are on your own if you do this.

This guide is not going to hold your hand and give you all the implementation to complete PA1. Any and all code snippets are for demonstration purposes only. Do not copy them and expect them to work for your implementation. These are to guide you towards the solution, and to encourage critical thinking. Asking for answers is not tolerated, and you will be removed if I have reason to believe you are genuinely trying to cheat.

# Part 1: Introduction

Let’s start with explaining what multithreading is. I will use the analogy of a race, because it is the one I like the most. When you code a single threaded solution, it is similar to a relay race. You have to wait for the first “task” to finish before the next “task” can begin. With multithreading, it is like a traditional race, in which all “tasks” start at the same time. Each string you get from the console as input will have its own thread, however you will not know how many strings you will get. You will then code all the threads such that they all perform their tasks at the same time.

Here is an example of what the implementation would look like.

```cpp
#include <pthread.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

struct thread //this is how you pass in info
{
    int count; //example of how to pass in data to a struct
    string s = ""; //this is an example of accessing data
    thread(int c) //struct constructor (for int main())
    {
        count = c;
    }
};

void* threadInstructions(void* arg)
{
    thread* threadArg = (thread*) arg; //convert back to struct (from void*)
    cout << "I am thread " << threadArg->count << endl; //to make sure its actually multithreading
    threadArg->s = "SUCCESS"; //accessing data once its finished threading
    return NULL; //always returns NULL
}

int main()
{
    vector<pthread_t> threadVector; //for a potentially-unlimited amount of threads, a vector is useful in keeping track of all your threads
    vector<thread*> pointerVector; //this is a vector of structs to pass in and pass out the data for the thread, and for accessing said data whenever
    for(int a = 0; a < 4; a++) //for 4 threads
    {
        thread* newThread = new thread(a); //we create a struct, with parameter a (the for loop counter)
        pthread_t myThread; //we create a thread
        if(pthread_create(&myThread, NULL, threadInstructions, static_cast<void*> (newThread)))
        //when you create a pthread, it will always return 0, which is false
        // This conditional says if it returns a non-zero value > 0, (true), an error occurred
        {
            cout << "ERROR";
            return -1;
        }
        pointerVector.push_back(newThread); //push your new struct (thread)* to its respective vector
        threadVector.push_back(myThread); //push your new thread to its respective vector
    }
    for(int b = 0; b < 4; b++) //join means "stop" we are done threading
    {
        pthread_join(threadVector[b], NULL); //join all the threads
    }
    for(int c = 0; c < 4; c++) //this is how we access the data from the struct
    {
        cout << pointerVector[c]->s << endl;
        //the data that the threads accessed remains afterwards
        //so we can output that information to console for demonstration purposes
    }
}
```

Wow, that’s a lot of code. Let’s break it down.

Multithreading is four important things.
1. A for loop to create the threads
2. A for loop to join the threads
3. A struct to pass in the data
4. A function to give the thread their instructions

Let’s break it down even further.

1. A for loop to create the threads

We are going to be making a thread for each string. However, we will not know how many threads we need to make. That’s why in the example provided, I use a vector. Now if we look at the code, we see:

```cpp
 if(pthread_create(&myThread, NULL, threadInstructions, static_cast<void*> (newThread)))
        //when you create a pthread, it will always return 0, which is false
        // This conditional says if it returns a non-zero value > 0, (true), an error occurred
        {
            cout << "ERROR";
            return -1;
        }
```

2. A for loop to join the threads

```cpp

    for(int b = 0; b < 4; b++) //join means "stop" we are done threading
    {
        pthread_join(threadVector[b], NULL); //join all the threads
    }
```

Joining the threads basically means that you want to stop them doing their tasks.

3. A struct to pass in the data

```cpp
struct thread //this is how you pass in info
{
    int count; //example of how to pass in data to a struct
    string s = ""; //this is an example of accessing data
    thread(int c) //struct constructor (for int main())
    {
        count = c;
    }
};
```

Threads can only pass in one argument in their creation. A struct is the best way to package multiple data types into one.

4. A function to give the thread their instructions

```cpp
void* threadInstructions(void* arg)
{
    thread* threadArg = (thread*) arg; //convert back to struct (from void*)
    cout << "I am thread" << endl; //to make sure its actually multithreading
    threadArg->s = "SUCCESS"; //accessing data once its finished threading
    return NULL; //always returns NULL
}
```

When you are initializing the threads, you must pass in instructions for the threads to follow. This function (named threadInstructions) provides the instructions for each thread.

# Part 2: Conclusion

Let me know if I should add anything to this:

```
Assistant Professor tzkal
Department of Scuffed Sciences
Office: PGH 533
Phone Number: no
E-mail: no

Version 0.01 - 9/15/2023
Version 0.02 - 11/6/2023
Version 0.03 - 02/17/2024
```
