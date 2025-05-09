/**
 * @file    
 * @brief   
 * @details 
 *          
 *
 * @version 1.0
 * @date    2024-10-09
 * @author  Mai Anh Tuan
 */
/*==================================================================================================
==================================================================================================*/
#ifndef STRING_H
#define STRING_H
/*==================================================================================================
*                                       MACRO DEFINITIONS
==================================================================================================*/
#define NULL ((void*)0)
#define MAX_LENGTH 20
#define TRUE 1
#define FALSE 0
/*==================================================================================================
*                                       GLOBAL FUNCTION PROTOTYPE
==================================================================================================*/
unsigned char my_atouchar (char* str);
unsigned short my_atoushort(char *str);
void my_strcpy(char *dest, const char *src);
void my_strncpy(char *dest, const char *src, int n);
char *my_strchr(char *str, char c);
char *my_strtok(char* str, char* delim);
unsigned char my_strlen(char *str);
char stringcompare(unsigned char* str1, const unsigned char* str2);
unsigned char Check_Format_Setting_Date(char *str);
unsigned char Check_Format_Setting_Time(char *str);

#endif

