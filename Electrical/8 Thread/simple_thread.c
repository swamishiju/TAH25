#include <inttypes.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define NUMBER_OF_TRANSACTIONS 20000
int balance = 100000; // Global account balance

// Utility function for comparing
void utility(int in);

void *transaction_func() {
  int64_t id = (int64_t)pthread_self(); // Thread id
  printf("Thread %lld ready\n", id);

  int transaction = 0;

  int acc = 0;
  for (int i = 0; i < NUMBER_OF_TRANSACTIONS; i++) {
    // Random transaction amount [-5000,5000]
    transaction = (rand() % 10001) - 5000;
    balance += transaction;

    // Update balance change due to thread
    acc += transaction;

    // Random pause
    usleep(rand() % 100);
  }

  // Print balance change
  printf("%lld: %d\n", id, acc);
  utility(acc);
  return NULL;
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  pthread_t MrRichie, MrsRichie; // Transaction threads
  int status_1, status_2;

  printf("Creating threads\n");
  printf("Balance: %d\n\n", balance); // Initial

  utility(balance);

  status_1 = pthread_create(&MrRichie, NULL, transaction_func, NULL);
  status_2 = pthread_create(&MrsRichie, NULL, transaction_func, NULL);

  if (status_1 || status_2) {
    printf("pthread_create returned error code %d %d\n", status_1, status_2);
    exit(-1);
  }

  // Wait till threads finish
  pthread_join(MrRichie, NULL);
  pthread_join(MrsRichie, NULL);

  // Final balance
  printf("Balance: %d\n\n", balance);
  utility(balance);
  return 0;
}

// UTILITY
void utility(int in) {
  static int call_n = 0;
  static int change = 0;
  static int initial = 0;
  call_n++;

  if (call_n == 4) {
    if (initial + change == in)
      printf("Transactions successful\n");
    else
      printf("Transactions failed [Expected %d]\n", initial + change);
  } else if (call_n == 1)
    initial = in;
  else
    change += in;
}
