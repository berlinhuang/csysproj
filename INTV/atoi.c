//
// Created by root on 17-11-19.
//
#include "INTV.h"
#include <stdio.h>

int main(void )
{
    char *s1="333640";
    char *s2="-12345";
    char *s3="123.3113";
    char *s4="-8362865623872387698";
    char *s5="+246653278";

    printf("integer1=%d\n",my_atoi(s1));
    printf("integer2=%d\n",my_atoi(s2));
    printf("integer3=%d\n",my_atoi(s3));
    printf("integer4=%d\n",my_atoi(s4));
    printf("integer5=%d\n",my_atoi(s5));
    return 0;
}