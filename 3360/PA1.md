# Part 0: Before we begin

This assignment (and the guide by extension) assumes that you have a basic understanding of C++. If not, Google and AI (ChatGPT) are your friends.

This guide is not going to hold your hand and give you all the implementation to complete PA1. Any and all code snippets are for demonstration purposes only. Do not copy them and expect them to work for your implementation. These are to guide you towards the solution, and to encourage critical thinking. Asking for answers is not tolerated, and you will be removed from the server if I have reason to believe you are genuinely trying to cheat.

# Part 1: Introduction

So… What are we supposed to do?

Let’s look at the instructions: “For this assignment, you will create a multithreaded version of the incremental entropy algorithm proposed by Dr. Rincon in the paper "Entropy-based scheduling performance in real-time multiprocessor systems" (https://ieeexplore.ieee.org/abstract/document/10089704).”

This is what the algorithm in question looks like:

```
Algorithm 2: Incremental entropy per processor

Input: freq, currFreq, currH, selectedTask, extraFreq
Output: H, NFreq

NFreq = currFreq + extraFreq
if NFreq == extraFreq then
  H = 0
else
  if freq[selectedTask] == 0 then
    currentTerm = 0
  else
    currentTerm = freq[selectedTask] * logb(freq[selectedTask])
  end if
  newTerm = (freq[selectedTask] + extraFreq) * logb(freq[selectedTask] + extraFreq)
  H = logb(NFreq) - ((logb(currFreq) - currH) * (currFreq) - currentTerm + newTerm) / NFreq
end if
return H, NFreq
```

Awesome! We have the pseudocode in front of us. But, let’s understand what this algorithm is, and to do that, let’s look at the input.

## INPUT: A 2 B 4 C 3 A 7

So, we’re given an arbitrary amount of strings, and each string contains an arbitrary amount of letters and an equal amount of numbers for each letter. The letters and numbers are paired up together, with the order being: letter X1, space, number Y1, space, letter X2, space, number Y2, space… letter Xn, space, number Yn. Hmm… a pair…

```cpp
pair<char, int> pairOne('A', 2);
pair<char, int> pairTwo('B', 4);
pair<char, int> pairThree('C', 3);
pair<char, int> pairFour('A', 7);
```

Now that we’ve got that taken care of, let’s do some math!

# Part 2: The Math

Unfortunately, it’d be too easy if I just gave you this in code. What I will do though, is walk you through it step by step.

Pass in freq, currFreq, currH, selectedTask, extraFreq, and then…

Wait! I should define what each of those are and what they are used for.

Freq = Frequency Array. When we start calculating entropy, all the values are set to 0. As we loop through the strings, the Frequency Array updates to be the sum of the current value in the frequency array and the extra frequency.
currFreq = Current Frequency. This keeps track of the most recent frequency we calculated entropy for, NOT the one we are about to calculate in the loop.
currH = Current Entropy. Same as current Frequency, this is for the most recent entropy we calculated.
selectedTask = self-explanatory. The task we are about to calculate the entropy for.
extraFreq = self-explanatory. The frequency we are about to calculate the entropy for.

Ok… now that we have that defined, we can move to step 2.

NFreq = currFreq + extraFreq

What is NFreq? NFreq is the sum of the currFreq and extraFreq, of course! I’m not sure what the N in NFreq stands for, but that's not really the point of this guide to tell you.

If NFreq == extraFreq then: H = 0

H is the entropy we are calculating for the current loop, not to be confused with currH, the entropy we calculated for the loop right before our current loop. This simple conditional states that if NFreq = extraFreq, then the entropy is zero, and we can move on to the next pair. This conditional will ALWAYS be true if we are in the first pass of the loop we have (and if extraFreq is always zero, but that is probably never going to happen).

Else (if freq[selectedTask] == 0 then currentTerm = 0) (else currentTerm = freq[selectedTask * logb(freq[selectedTask])

Let’s break this down because it’s a bit more complicated than what we’ve seen so far. If the frequency array for the selected task is currently zero, then the currentTerm is zero. What’s the currentTerm? We use it to calculate the entropy, and that’s all you really need to know to do this task. If you really want to know, ask the professor.

However, what if the selected task is currently not zero? Then, we multiply the frequency of the selected task by the log sub-2 of the frequency of the selected task. (B is 2, and will be known as such as we further discuss the algorithm).

End if

Just to clarify, this means that the conditional from lines 4 - 9 in the provided picture is complete, and the remaining code executes regardless of what current Term is. The conditional in lines 2 and 3 will completely finish the loop without question and go straight to line 12.

newTerm = (freq[selectedTask] + extraFreq) * log2(freq[selectedTask] + extraFreq)

newTerm, much like currentTerm, is only used for the entropy algorithm, and so we don’t need to delve too deep into its origins. This one should be self explanatory, similarly to the formula we used to create the currentTerm, with the difference this will execute regardless of the current frequency in the array for selectedTask.

H = log2(NFreq) - ((log2(currFreq) - currH) * (currFreq) - currentTerm + newTerm) / NFreq

This one should be self explanatory as well. The entropy, assuming you made it past line 2, is calculated by this lengthy function here.

Return H, NFreq

For the purposes of this pseudocode, it will return two variables, which I will refer to as a tuple. I personally did not return NFreq, since it’s not used anywhere else in your code (at least it should not be) besides this function, and a for loop inside your entropy function (which is what I did) will eliminate the need to pass in any more than 2 variables (depending on your implementation) and return only 1 (depending on your implementation). That being said, I don’t think there’s anything wrong with returning more than 1 variable, or passing in more than 2. I just personally don’t see a need when the majority of these variables passed in are used only in this algorithm.

# Part 3: A run-through of the algorithm

Now we have an above-average understanding of this interesting formula, let’s do a runthrough with the input I provided earlier:

## INPUT: A 2 B 4 C 3 A 7

Let’s start with A and 2.

When we start, everything is initialized to 0.

Frequency Array: A = 0, B = 0, C = 0
currFreq = 0
currH = 0
selectedTask = ‘ ‘
extraFreq = 0
H = 0
NFreq = 0

Let’s pass in A and 2

Frequency Array: A = 0, B = 0, C = 0
currFreq = 0
currH = 0
selectedTask = ‘A‘
extraFreq = 2
H = 0
NFreq = 0

Hmm, not much changed. Let’s try to calculate entropy, anyways. First up, we calculate NFreq.

NFreq = currFreq + extraFreq
N = 0 + 2 = 2
NFreq = 2

Okay, so NFreq is equal to extraFreq. I wonder if that is important…

If NFreq == extraFreq then: H = 0

Well, they are equal. H = 0, we skip everything up till line 12. Let’s go look at line 12.

End if
Return H, NFreq.

Well, that was quick. Let’s try B = 4

Frequency Array: A = 2, B = 0, C = 0
currFreq = 2
currH = 0
selectedTask = ‘ ‘
extraFreq = 0
H = 0
NFreq = 2

Wow, that looks way different. What changed? Well, Frequency Array has been updated to be the sum of its current value and the extra frequency. currFreq is now two, since we currently calculated the frequency to be two. We haven’t started the next loop just yet. We reset selectedTask and extraFreq because we passed that already, and we are going to work on the next loop. NFreq, the sum of the current and extra frequencies, is two.

Let’s plug in B and 4

Frequency Array: A = 2, B = 0, C = 0
currFreq = 2
currH = 0
selectedTask = ‘B‘
extraFreq = 4
H = 0
NFreq = 2

Awesome! Let’s do some math.

NFreq = currFreq + extraFreq
NFreq = 2 + 4
NFreq = 6

NFreq is not equal to currFreq. Let’s see what changes now.

If NFreq == extraFreq == 0 then: entropy = 0

Nope. NFreq is not equal to extraFreq. Let’s keep going.

Else (if freq[selectedTask] == 0 then currentTerm = 0) (else currentTerm = freq[selecredTask] * log2(freq[SelectedTask])

Okay, so our frequency for the selectedTask is 0 right now, so currentTerm stays 0. Let’s keep going

newTerm = (freq[selectedTask] + extraFreq) * log2(freq[selectedTask] + extraFreq)
	newTerm = (0 + 4) * log2(0 + 4)
	newTerm = 4 * log2(4)

Well, I could calculate this for you, but you have calculators, right? I’ll just show you what the code in C++ would look like because I’m so nice.

```cpp
double newTerm = (freq[selectedTask] + extraFreq) * log2(freq[selectedTask] + extraFreq);
```

Good luck!

H = log2(NFreq) - ((log2(currFreq) - currH) * (currFreq) - currentTerm+newTerm)/NFreq
H = log2(6) - ((log2(2) - 0) * (2) - 0 + (4 * log2(4))/6
H = log2(6) - (log2(2) * 2 + (4 * log2(4))/6
H = .92

Same thing here, too lazy to calculate, but you would get an entropy of .9182, which rounds to .92 (all the answers must have only two digits to the right of the decimals).

double entropy = log2(NFreq) - ((log2(currFreq) - currH) * (currFreq)-currTerm + newTerm) / NFreq;

Okay, so we’ve done A and B. Let’s do C. Right now, our variables look like this:

Frequency Array: A = 2, B = 4, C = 0
currFreq = 6
currH = 0.92
selectedTask = ‘ ‘
extraFreq = 0
H = 0
NFreq = 6

Remember to update the currFreq, currH, and the frequency array. Now, let’s plug in C.

Frequency Array: A = 2, B = 4, C = 0
currFreq = 6
currH = 0.92
selectedTask = ‘C‘
extraFreq = 3
H = 0
NFreq = 6

And now, we run through the algorithm once more.

NFreq = currFreq + extraFreq
NFreq = 6 + 3
NFreq = 9

if(NFreq == extraFreq) then: H = 0

NFreq is not equal to extraFreq, so we keep moving

Else: (if freq[selectedTask] == 0) then: currentTerm = 0

If we look at the frequency array, C = 0, so that means currentTerm will be 0.

newTerm = (freq[selectedTask] + extraFreq) * log2(freq[selectedTask] + extraFreq)
newTerm = (0 + 3) * log2(0 + 3)
newTerm = 3 * log2(3)

H = log2(NFreq) - ((log2(currFreq) - currH) * (currFreq) - currentTerm+newTerm)/NFreq
H = log2(9) - ((log2(3) - 0.92) * (6) - 0 + (3 * log2(3))/9
H = 1.53

You get the gist, let’s move on to A 7. But before we do, let’s look at our variables.

Frequency Array: A = 2, B = 4, C = 3
currFreq = 9
currH = 1.53
selectedTask = ‘ ‘
extraFreq = 0
H = 0
NFreq = 9

Let’s push in A and 7.

Frequency Array: A = 2, B = 4, C = 3
currFreq = 9
currH = 1.53
selectedTask = ‘A‘
extraFreq = 7
H = 0
NFreq = 9

We know the drill, let’s do the math.

NFreq = currentFreq + extraFreq
	NFreq = 9 + 7
	NFreq = 16

If NFreq == extraFreq then: H = 0

They are not equal so we keep going.

Else (if freq[selectedTask] == 0 then currentTerm = 0) (else currentTerm = freq[selectedTask] * log2(freq[selectedTask])

For the first time, the frequency for the selectedTask in the frequency array is not 0. So we calculate currentTerm as the frequency of the selectedTask in the frequency array multiplied by the log2 of the frequency of the selectedTask in the frequency array.

currentTerm = freq[selectedTask * log2(freq[selectedTask]
currentTerm = 2 * log2(2)

The newTerm will also change now that we finally have a frequency in the frequency array for the selectedTask

newTerm = (freq[selectedTask] + extraFreq) * log2(freq[selectedTask] + extraFreq)
newTerm = (2 + 7) * log2(2 + 7)
newTerm = 9 * log2(9)

And finally, the entropy.

H = log2(NFreq) - ((log2(currFreq) - currH) * (currFreq) - currentTerm+newTerm)/NFreq
	H = log2(16) - ((log2(9) - 1.53) * (9) - (2 * log(2)) + (9 * log(9)))/16
	H = 1.42

Now, let’s update our frequency array.

Frequency Array: A = 9, B = 4, C = 3
currFreq = 16
currH = 1.42
selectedTask = ‘ ‘
extraFreq = 
H = 1.42
NFreq =16

Wait, why is A = 9? Shouldn’t it be 7? We are going to update the array by adding the extraFrequency to the array’s index.

And that’s how you go through the algorithm! Let’s look at multithreading now.

# Part 4: Multithreading

Let’s start with explaining what multithreading is. I will use the analogy of a race, because it is the one I like the most. When you code a single threaded solution, it is similar to a relay race. You have to wait for the first “task” to finish before the next “task” can begin. With multithreading, it is like a traditional race, in which all “tasks” start at the same time. Each string you get from the console as input will have its own thread, however you will not know how many strings you will get. You will then code all the threads such that they all calculate their entropy at the same time.

Here is an example of what the implementation would look like.

```cpp
#include <pthread.h>
#include <unistd.h>
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
    cout << "I am thread" << endl; //to make sure its actually multithreading
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
A for loop to create the threads
A for loop to join the threads
A struct to pass in the data
A function to give the thread their instructions

Let’s break it down even further.

A for loop to create the threads

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

A for loop to join the thread

```cpp

    for(int b = 0; b < 4; b++) //join means "stop" we are done threading
    {
        pthread_join(threadVector[b], NULL); //join all the threads
    }
```

Joining the threads basically means that you want to stop them doing their tasks.

A struct to pass in the data

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

A function to give the thread their instructions

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

# Part 5: Conclusion

Let me know if I should add anything to this:

Version 0.01 - 9/15/2023
Version 0.02 - 11/6/2023
