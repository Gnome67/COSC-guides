#include <unistd.h>
#include <iostream>
#include <sys/wait.h>



void fireman(int)
{
   while (waitpid(-1, NULL, WNOHANG) > 0)
      ;
}

int main()
{

   signal(SIGCHLD, fireman);   
   int nChild = 0;        
   while (true)
   {
      
      if (fork() == 0)
      {
         std::cout << "A child process started" << std::endl;
         sleep(5);
         _exit(0);
      }
      std::cin.get();
   /*   nChild ++;
      if (nChild == 10)
      {
         break;
      }*/
   }
   
   std::cout << "Parent process ended" << std::endl;
   return 0;
}
