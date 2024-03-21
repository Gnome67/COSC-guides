# Part 0: The end (not really)

I wrote this 2 weeks before PA3 even came out. The majority of this guide was sourced from Tariq Achor Zyed and Frank Bui’s tutorial [here](https://docs.google.com/document/d/1YKy6xpAE4BArbdqLNGA5zB8ptnEHWuUwCrveh10yCH4/edit). Why not just use their guide? I don’t know. But I figured I’d write this guide.

Before we truly begin, let me mention that we don’t need anything from PA2. Find your old PA1 code and make a copy of it for PA3.

# Part 1: Approaching PA3

The first thing I want to talk about is what we need to do. What exactly do we need to do? Well, if you did PA1 the right way, your output should be outputting after the threads are all joined using the `pthread_join()` function. In PA3, we have to output BEFORE we join the threads, so remove that cout part. We are also using a single struct. Get rid of any other structs you are using, we can only allow one. However, this means all threads are using the same struct, which is the same as saying all threads are using the same memory. Threads are very selfish, and they will cause interference since they are all sharing the same memory. If you’ve tried outputting in the void* function in PA1, you’d see that it prints out of order. We are going to fix that in this guide. But how?

Simply put, we are going to make our code only perform one operation at a time. This is where this code gets trippy. You might be wondering why thread at all if we’re going to do one operation at all, but I can’t answer that for philosophical reasons. Just know that Professor Rincon has asked us to understand how mutexes and conditional variables work. What are those? Mutex is short for Mutual Exclusion, which is a lock we set on shared resources and then remove afterwards. While this shared resource is on lock, we can use a conditional variable to allow a specific process or processes to access the shared resource.

Before we move on, let’s discuss what a shared resource is and what a critical section is so we’re all on the same page. A shared resource is a resource that all the threads are sharing, duh. But seriously, a shared resource is a data structure, variable, or any piece of memory that can be accessed and modified by multiple threads concurrently in a multithreaded program. A critical section is a specific section of code within a program that accesses and manipulates shared resources. It's called "critical" because only one thread at a time is allowed to execute this section. We are going to use conditional variables to ensure that only one thread is able to access the shared resources at a time, therefore creating a critical section.

# Part 2: Code

I wouldn’t be surprised if any of you skipped Part 1, considering there’s a lot of text. If you did, go read it. This is where code gets trippy. 

## Critical Sections

### Main Thread / int main()

```cpp
struct threadArg; //CAN ONLY CREATE 1
for .. {
  pthread_lock;
  pthread_create(threadArg);
}

for .. {
  pthread_join();
}
```

### Child Thread / void* threadInstructions

```cpp
void* threadInstructions(void* arg) {
  struct arg_ptr = (threadArg*) arg;
  pthread_unlock; //WE LOCKED IN THE MAIN THREAD
  // !!!IMPORTANT!!!
  // ALGORITHM FUNCTION HERE
  // PREPARE OUTPUT
  // !!!IMPORTANT!!!

  // MOST IMPORTANT: THE WORK ABOVE HAS TO HAPPEN WHILE WORK FOR THE PREVIOUS THREAD IS HAPPENING (potentially), NOT ALWAYS ONLY AFTER
  // Using broadcast and wait to find the thread you want and sleep the other threads
  // You ensure the order is strict only after work is done
}
```

The above code shows how we would work with mutexes to create a critical section. When we call pthread_create, we lock a mutex in the same for loop that will create the first critical section. Make sure to pass in the mutex you are locking (notice how I mentioned the mutex you are locking, almost as if I’m implying there will be more than one 👀) or you will be stupid like me, and that’s not something you want to be, trust me. Anyways, notice how the first thing we do in the void* function after reverting the struct-to-void* change is unlock the mutex. Trippy, right? Well, think of it as a boolean value, with the states of either locked or unlocked. When we initialized it and passed it in, it was locked. Now we unlocked it inside the struct.

Let’s talk about wait and broadcast. Imagine you are the manager of a waiting room, and all the people in the room have a ticket, but you’re not sure who has the ticket you need. We use broadcast to say “I need ticket n”. So everyone stands up, and looks at their ticket, and the holder of the ticket n will come and do whatever you want him to do. But everyone else thinks you are about to call them, so we use wait to say “That’s all for now”. Here’s a code example of what that looks like.

```cpp
while(threadID != turn) //while its not a thread turn, tell that thread to goto sleep
{
  pthread_cond_wait(&waitTurn, &bsem) //blocks the calling thread
}
```

IMPORTANT: IF YOU ARE READING THIS AFTER EXAM 2, DO NOT MAKE “threadID”, “turn”, “waitTurn” OR “bsem” GLOBAL VARIABLES. YOU WILL GET A 0!!!

Now, let’s discuss the synchronization of threads. You should make the child threads wait in the child process. The reason why is if we make them wait in main, then it will not create the threads simultaneously, and then you will get points off for not taking full advantage of multithreading. We will be making them wait just before they print, so that they finish their threading job, but we are able to manipulate the order in which they print. Here’s an example of what properly synchronized code looks like.

# namethiscodelaterlol
```cpp
void* threadInstructions(void* arg)
{
  threadArg* arg_ptr = (arg*) arg;
  int local_thread_id = arg_ptr->child_idx;
  int some_number=fun(local_thread_id);
  pthread_mutex_unlock(arg_ptr->mutex);
  //the code im looking at didnt put anything here lol
  pthread_mutex_lock(arg_ptr->mutex);
  while((*arg_ptr->idx)!=local_thread_id) {
    pthread_cond_wait(arg_ptr->mutex_turn, arg_ptr->mutex);
  }
  pthread_mutex_unlock(arg_ptr->mutex);
  cout << "I am " << some_number << " from " << /*something*/ << endl;
  pthread_mutex_lock(arg_ptr->mutex);
  (*arg_ptr->idx)=(*arg_ptr->idx)+1;
  pthread_cond_broadcast(arg_ptr->mutex_turn);
  pthread_mutex_unlock(global_args->mutex);
  return NULL;
}

int main()
{
  int mainIndex = 1;
  pthread_tid pid[1000];
  string str = "Hello World!"
  static pthread_mutex_t mutex;
  static pthread_cond_t turn;
  threadArg thread_arg;
  //you should know how to initialize a struct by now
  //pass in mutex, mutex_turn, str, index (REMEMBER & IN FRONT)
  for .. {
    pthread_mutex_lock(&mutex);
    thread_arg.child_idx = ..+1; //counter + 1
    pthread_create(&pid[i], NULL, threadInstructions, &thread_arg);
  }
  for ..
  {
    pthread_join(pid[i], NULL);
  }
  return NULL;
}
```

The code in-between each mutex lock and unlock is a critical section. Take note of where they are in the code and what is happening in each of them. The first critical section that starts in main() and ends in the void* function creates a set of local variables that are MUTually EXclusive (roll credits), so that they will not be modified when the thread function runs to completion. The second critical section sets up the conditional variable, in which the threads you don’t want doing stuff are put to sleep if they’re not the thread you want doing stuff. Notice how this wait condition is set AFTER we finish the work but BEFORE we start printing. Finally, the third critical section prevents a deadlock. What is a deadlock? A deadlock is when all your threads are waiting for other threads to do something, so no thread does anything because they’re all waiting. After the thread we want to finish doing work is finished, we tell him to go to sleep and update the ticket to the next thread in line. We then use broadcast to wake up all the threads and look for the new n-th ticket holder.

# Part 3: The end (really)

Okay so if you’ve made it this far, you deserve a reward. I will tell you all the steps I did to convert PA1 to PA3. No code, obviously. Just steps

I initialized two mutexes, a static int “counter”, and a conditional variable
I initialized ONE STRUCT, and passed in the variables i made above + the usual from PA1
Inside the pthread_create loop, i locked one of my two mutexes, changed the values for my entropy algorithm’s input for each string, and then called pthread_create

Ok, quick break. Why did I do this? This was to create my first critical section. Since my entropy algorithm input changes based on the line, I wanted to make sure that they would not be modified prematurely.

Inside the void* function called by pthread_create(), after reversing the struct cast, I created local variables of my entropy algorithm’s input variables. I then UNLOCKED my first mutex that was locked in the pthread_create() loop.
I then processed my algorithm using the LOCAL VARIABLES, not the ones passed in, to avoid issues with thread interference.

I then used the critical section to make all the child threads except the one i wanted to goto sleep, and then outputted OUTSIDE the critical section.

### IMPORTANT NOTE: YOU MUST HAVE AT LEAST 2 MUTEXES.

# GITHUB EXCLUSIVE

```cpp
//include necessary libraries

using namespace std;

struct data
{
    string input;
    int cpu;
    int *counter;
    pthread_mutex_t *mutex;
    pthread_mutex_t *mutex2;
    pthread_cond_t *condition;
    data() {}
};

string answer(string input)
{
    return "Hello World";
}

void* threadInstruct(void* arg)
{
    data arg_ptr = *(data*) arg;
    string localInput = arg_ptr->input;
    int localCPU = arg_ptr->cpu;
    pthread_mutex_unlock(mutex);
    string answer = answer(input);
    pthread_mutex_lock(mutex2);
    while(*counter!=localCPU) { pthread_cond_wait(condition, mutex2); }
    pthread_mutex_unlock(mutex2);
    cout << answer << endl;
    pthread_mutex_lock(mutex2);
    (*counter)++;
    pthread_cond_broadcast(condition);
    pthread_mutex_unlock(mutex2);
    return NULL;
}

int main () 
{
    vector<string> input;
    string inputLine
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, nullptr);
    pthread_mutex_t mutex2;
    pthread_mutex_init(&mutex2, nullptr);
    pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
    static int counter = 0;
    while(getline(cin, inputLine))
    {
        //check if empty, otherwise push into input vector
    }
    data newThread;
    newThread.counter = &counter;
    newThread.mutex = &mutex;
    newThread.condition = &condition;
    newThread.mutex2 = &mutex2;
    for(int a = 0; a < input.size(); a++)
    {
        pthread_t myThread;
        pthread_mutex_lock(&mutex);
        newThread.input = input[a];
        newThread.cpu = a;
        if(pthread_create(...)
        {
            // error
        }
    }
    // join threads
}
```

Thank you so much for reading my guides. Big shoutout to MadDawg, bwandii, tachorzy, and many others for their combined help in the creation of my guide.

```
Version 0.01 - 10/18/2023
Version 0.02 - 11/2/2023
Version 0.03 - 11/5/2023
Version 0.04 - 03/21/2024
```
