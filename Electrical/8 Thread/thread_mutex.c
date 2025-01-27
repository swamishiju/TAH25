#include <inttypes.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define NUMBER_OF_TRANSACTIONS 2000

// Utility function for comparing
void utility(int in);

// Locked balance struct
typedef struct Balance {
  int balance;
  pthread_mutex_t lock;
} Balance;

Balance balance = {100000, false}; // Global account balance

void *transaction_func() {
  int64_t id = (int64_t)pthread_self(); // Thread id
  printf("Thread %lld ready\n", id);

  int transaction = 0;

  int acc = 0;
  for (int i = 0; i < NUMBER_OF_TRANSACTIONS; i++) {

    // Lock to make sure other thread doesn't interfear
    pthread_mutex_lock(&balance.lock);

    // Random transaction amount [-5000,5000]
    transaction = (rand() % 10001) - 5000;
    balance.balance += transaction;

    // Update balance change due to thread
    acc += transaction;

    // Unlock mutex
    pthread_mutex_unlock(&balance.lock);

    // Random pause
    usleep(10 * (rand() % 10));
  }

  // Print balance change
  printf("%lld: %d\n", id, acc);
  utility(acc);
  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t MrRichie, MrsRichie; // Transaction threads
  int status_1, status_2;
  utility(balance.balance);

  printf("Creating threads\n");
  printf("Balance: %d\n\n", balance.balance); // Initial

  status_1 = pthread_create(&MrRichie, NULL, transaction_func, NULL);
  status_2 = pthread_create(&MrsRichie, NULL, transaction_func, NULL);
  pthread_mutex_init(&balance.lock, NULL);

  if (status_1 || status_2) {
    printf("pthread_create returned error code %d %d\n", status_1, status_2);
    exit(-1);
  }

  // Wait till threads finish
  pthread_join(MrRichie, NULL);
  pthread_join(MrsRichie, NULL);

  // Final balance
  printf("Balance: %d\n\n", balance.balance);
  utility(balance.balance);
  pthread_mutex_destroy(&balance.lock);
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
