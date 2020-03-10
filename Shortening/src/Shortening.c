
/*
 * Conway's Game of Life
 *
 * A. Mucherino
 *
 * PPAR, TP5
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include </usr/include/mpi/mpi.h>

int N = 32;
int itMax = 20;

// allocation only
unsigned int *allocate()
{
   return (unsigned int *)calloc(N*N/2, sizeof(unsigned int));
};

// conversion cell location : 2d --> 1d
// (row by row)
int code(int x, int y, int dx, int dy)
{
   int i = (x + dx) % N;
   int j = (y + dy) % N;
   if (i < 0)
      i = N + i;
   if (j < 0)
      j = N + j;
   return i * N + j;
};

// writing into a cell location
void write_cell(int x, int y, unsigned int value, unsigned int *world)
{
   int k;
   k = code(x, y, 0, 0);
   world[k] = value;
};

// random generation
unsigned int *initialize_random()
{
   int x, y;
   unsigned int cell;
   unsigned int *world;

   world = allocate();
   for (x = 0; x < N; x++)
   {
      for (y = 0; y < N; y++)
      {
         if (rand() % 5 != 0)
         {
            cell = 0;
         }
         else if (rand() % 2 == 0)
         {
            cell = 1;
         }
         else
         {
            cell = 2;
         };
         write_cell(x, y, cell, world);
      };
   };
   return world;
};

// dummy generation
unsigned int *initialize_dummy()
{
   int x, y;
   unsigned int *world;

   world = allocate();
   for (x = 0; x < N; x++)
   {
      for (y = 0; y < N; y++)
      {
         write_cell(x, y, x % 3, world);
      };
   };
   return world;
};

// "glider" generation
unsigned int *initialize_glider()
{
   int x, y, mx, my;
   unsigned int *world;

   world = allocate();
   for (x = 0; x < N; x++)
   {
      for (y = 0; y < N; y++)
      {
         write_cell(x, y, 0, world);
      };
   };

   mx = N / 2 - 1;
   my = N / 2 - 1;
   x = mx;
   y = my + 1;
   write_cell(x, y, 1, world);
   x = mx + 1;
   y = my + 2;
   write_cell(x, y, 1, world);
   x = mx + 2;
   y = my;
   write_cell(x, y, 1, world);
   y = my + 1;
   write_cell(x, y, 1, world);
   y = my + 2;
   write_cell(x, y, 1, world);

   return world;
};

// "small exploder" generation
unsigned int *initialize_small_exploder()
{
   int x, y, mx, my;
   unsigned int *world;

   world = allocate();
   for (x = 0; x < N; x++)
   {
      for (y = 0; y < N; y++)
      {
         write_cell(x, y, 0, world);
      };
   };

   mx = N / 2 - 2;
   my = N / 2 - 2;
   x = mx;
   y = my + 1;
   write_cell(x, y, 2, world);
   x = mx + 1;
   y = my;
   write_cell(x, y, 2, world);
   y = my + 1;
   write_cell(x, y, 2, world);
   y = my + 2;
   write_cell(x, y, 2, world);
   x = mx + 2;
   y = my;
   write_cell(x, y, 2, world);
   y = my + 2;
   write_cell(x, y, 2, world);
   x = mx + 3;
   y = my + 1;
   write_cell(x, y, 2, world);

   return world;
};

// reading a cell
int read_cell(int x, int y, int dx, int dy, unsigned int *world)
{
   int k = code(x, y, dx, dy);
   return world[k];
};

// updating counters
void update(int x, int y, int dx, int dy, unsigned int *world, int *nn, int *n1, int *n2)
{
   unsigned int cell = read_cell(x, y, dx, dy, world);
   if (cell != 0)
   {
      (*nn)++;
      if (cell == 1)
      {
         (*n1)++;
      }
      else
      {
         (*n2)++;
      };
   };
};

// looking around the cell
void neighbors(int x, int y, unsigned int *world, int *nn, int *n1, int *n2)
{
   int dx, dy;

   (*nn) = 0;
   (*n1) = 0;
   (*n2) = 0;

   // same line
   dx = -1;
   dy = 0;
   update(x, y, dx, dy, world, nn, n1, n2);
   dx = +1;
   dy = 0;
   update(x, y, dx, dy, world, nn, n1, n2);

   // one line down
   dx = -1;
   dy = +1;
   update(x, y, dx, dy, world, nn, n1, n2);
   dx = 0;
   dy = +1;
   update(x, y, dx, dy, world, nn, n1, n2);
   dx = +1;
   dy = +1;
   update(x, y, dx, dy, world, nn, n1, n2);

   // one line up
   dx = -1;
   dy = -1;
   update(x, y, dx, dy, world, nn, n1, n2);
   dx = 0;
   dy = -1;
   update(x, y, dx, dy, world, nn, n1, n2);
   dx = +1;
   dy = -1;
   update(x, y, dx, dy, world, nn, n1, n2);
};

// computing a new generation
short newgeneration(unsigned int *world1, unsigned int *world2, int xstart, int xend)
{
   int x, y;
   int nn, n1, n2;
   unsigned int cell;
   short change = 0;

   // cleaning destination world
   for (x = 0; x < N; x++)
   {
      for (y = 0; y < N; y++)
      {
         write_cell(x, y, 0, world2);
      };
   };

   // generating the new world
   for (x = xstart; x < xend; x++)
   {
      for (y = 0; y < N; y++)
      {
         //
         // to be completed
         //
         neighbors(x, y, world1, &nn, &n1, &n2);
         cell = read_cell(x, y, 0, 0, world1);
         if (cell != 0)
         {
            if (nn == 2 || nn == 3)
            {

               write_cell(x, y, cell, world2);
            }
         }
         else
         {
            if (nn == 3)
            {
               if (n1 > n2)
               {
                  write_cell(x, y, 1, world2);
               }

               else
               {
                  write_cell(x, y, 2, world2);
               }
               change = 1;
            }
         }
      };
   };
   return change;
};

// cleaning the screen
void cls()
{
   int i;
   for (i = 0; i < 10; i++)
   {
      // fprintf(stdout, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
   }
}

// diplaying the world
void print(unsigned int *world)
{
   int i;
   cls();
   for (i = 0; i < N; i++)
      fprintf(stdout, "-");

   for (i = 0; i < N * N; i++)
   {
      if (i % N == 0)
         fprintf(stdout, "\n");
      if (world[i] == 0)
         fprintf(stdout, " ");
      if (world[i] == 1)
         fprintf(stdout, "o");
      if (world[i] == 2)
         fprintf(stdout, "x");
   };
   fprintf(stdout, "\n");

   for (i = 0; i < N; i++)
      fprintf(stdout, "-");
   fprintf(stdout, "\n");
   sleep(1);
};

// main
int main(int argc, char *argv[])
{
   int it, change, my_rank, comm_size, startIndex, endIndex, loc;
   //int  changeGlob;
   unsigned int *world1, *world2;
   unsigned int *worldaux;
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
   MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
   //Verify if The world is divisible by the number of Processors
   if (N % comm_size != 0)
   {
      if (my_rank == 0)
      {
         printf("The World Size is NOT divisible by the number of processor\n");
      }
      exit(1);
   }

   // getting started
   if (my_rank == 0)
   {
      //world1 = initialize_dummy();
      //world1 = initialize_random();
      //world1 = initialize_glider();
      world1 = initialize_small_exploder();
   }
   else
   {
      world1 = allocate();
   }

   //Proc 0 send to everyone its world1
   MPI_Bcast(world1, N * N, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
   MPI_Barrier(MPI_COMM_WORLD);

   world2 = allocate();

   //Proc 0 print its initial world1
   if (my_rank == 0)
   {
      print(world1);
   }

   loc = N / comm_size;
   startIndex = my_rank * loc;
   endIndex = (my_rank + 1) * loc;
   it = 0;
   change = 1;
   while (/*change &&*/ it < itMax)
   {

      change = newgeneration(world1, world2, startIndex, endIndex);

      /*MPI_Barrier(MPI_COMM_WORLD);
      MPI_Reduce(&change,&changeGlob,1,MPI_UNSIGNED,MPI_LOR,0,MPI_COMM_WORLD);
      MPI_Barrier(MPI_COMM_WORLD);

      if(my_rank==0){
         for(int i=1; i< comm_size;i++){
            MPI_Send(&changeGlob,1,MPI_UNSIGNED,i,0,MPI_COMM_WORLD);
         }
      }else{
         MPI_Status status;
         MPI_Recv(&change,1,MPI_UNSIGNED,0,0,MPI_COMM_WORLD,&status);
      }*/

      MPI_Barrier(MPI_COMM_WORLD);
      worldaux = world1;
      world1 = world2;
      world2 = worldaux;
      MPI_Barrier(MPI_COMM_WORLD);

      //Each proc sends its first and last row to their neighboors
      MPI_Send(&(world1[code(startIndex, 0, 0, 0)]), N, MPI_UNSIGNED, (my_rank + (comm_size - 1)) % comm_size, 0, MPI_COMM_WORLD);
      MPI_Send(&(world1[code(endIndex - 1, 0, 0, 0)]), N, MPI_UNSIGNED, (my_rank + 1) % comm_size, 1, MPI_COMM_WORLD);
      MPI_Barrier(MPI_COMM_WORLD);

      //Each processor recv their neighboors rows
      MPI_Status status;
      MPI_Recv(&(world1[code(startIndex - 1, 0, 0, 0)]), N, MPI_UNSIGNED, (my_rank + (comm_size - 1)) % comm_size, 1, MPI_COMM_WORLD, &status);
      MPI_Recv(&(world1[code(endIndex, 0, 0, 0)]), N, MPI_UNSIGNED, (my_rank + 1) % comm_size, 0, MPI_COMM_WORLD, &status);
      MPI_Barrier(MPI_COMM_WORLD);

      it++;
   };


   //Proc 0 gather all the world1 sections of each procs to be able to print the entire final world
   MPI_Barrier(MPI_COMM_WORLD);
   MPI_Gather(&(world1[code(my_rank * loc, 0, 0, 0)]), N * loc, MPI_UNSIGNED, world2, N * loc, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
   MPI_Barrier(MPI_COMM_WORLD);
   if (my_rank == 0)
   {
      print(world2);
   }

   // ending
   free(world1);
   free(world2);
   MPI_Finalize();

   return 0;
};
