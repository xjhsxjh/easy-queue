
#include "easy_queue.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

char printable( uint8_t x )
{
    return (x < 32) ? '.' : x;
}

void print_queue(const EasyQueue_st *which)
{
    printf("head, tail: %d, %d\n[", which->head, which->tail );
    for (int i=0; i<(QUEUE_SIZE-1); i++)
    {
        printf(" ");
        if (i == which->head)
            printf("^");
        if (i == which->tail)
            printf("$");
        printf("%c", printable(which->buffer[i]) );
        printf(",");
    }

    printf(" ");
    if (QUEUE_SIZE-1 == which->head)
        printf("^");
    if (QUEUE_SIZE-1 == which->tail)
        printf("$");
    printf("%c", printable(which->buffer[QUEUE_SIZE-1]) );

    printf("]\n");
}

int main(int argc, char const *argv[])
{
    EasyQueue_st first_q;
    EasyQueue_st secont_q;
    int failed_test_count = 0;

    printf("Init tests:\n");
    init_easy_queue( &first_q );
    failed_test_count += did_queue_failed() ? 1 : 0;
    init_easy_queue( &secont_q );
    failed_test_count += did_queue_failed() ? 1 : 0;
    printf("Errors count: %d\n", failed_test_count);

    printf("Is empty tests:\n");
    failed_test_count += is_queue_empty( &first_q ) ? 0 : 1;
    failed_test_count += did_queue_failed() ? 1 : 0;
    failed_test_count += is_queue_empty( &secont_q ) ? 0 : 1;
    failed_test_count += did_queue_failed() ? 1 : 0;
    printf("Errors count: %d\n", failed_test_count);

    printf("Enqueue tests:\n");
    // no overflow
    char sample[] = "ten bytes.";
    print_queue( &first_q );

    enqueue( &first_q, (uint8_t *)sample, strlen(sample) );
    failed_test_count += did_queue_failed() ? 1 : 0;
    print_queue( &first_q );

    char buffer[6] = "      ";
    dequeue( (uint8_t *)buffer, &first_q, 5);
    failed_test_count += did_queue_failed() ? 1 : 0;
    buffer[5]='\0';
    printf("first chunk: %s\n", buffer );

    dequeue( (uint8_t *)buffer, &first_q, 5);
    failed_test_count += did_queue_failed() ? 1 : 0;
    buffer[5]='\0';
    printf("second chunk: %s\n", buffer );

    print_queue( &first_q );

    // ring overflow
    enqueue( &first_q, (uint8_t *)sample, strlen(sample) );
    failed_test_count += did_queue_failed() ? 1 : 0;
    print_queue( &first_q );

    dequeue( (uint8_t *)buffer, &first_q, 5);
    failed_test_count += did_queue_failed() ? 1 : 0;
    buffer[5]='\0';
    printf("first chunk: %s\n", buffer );

    dequeue( (uint8_t *)buffer, &first_q, 5);
    failed_test_count += did_queue_failed() ? 1 : 0;
    buffer[5]='\0';
    printf("second chunk: %s\n", buffer );

    print_queue( &first_q );
    printf("Errors count: %d\n", failed_test_count);

    return failed_test_count;
}
