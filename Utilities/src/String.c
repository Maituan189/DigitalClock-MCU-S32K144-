/**
 * @file 		String.c
 * @brief 	Custom String Handling Functions
 * @details This file includes implementations for various string handling functions, such as
 *          checking for digits, string copying, tokenizing, and validating time and date formats.
 *
 * @version 1.0
 * @date    2024-10-09
 * @author  Mai Anh Tuan
 */
 /*==================================================================================================
*                                       INLCUDE FILE
==================================================================================================*/
#include "String.h"
/*==================================================================================================
*                                       LOCAL FUNCTIONS PROTOTYPE
==================================================================================================*/
static unsigned char my_isdigit(char str);
/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
static unsigned char my_isdigit(char str){
    if (str >= '0' && str <= '9') 
		{
      return 1;  // It's a digit
    }
    return 0;      // It's not a digit
}
/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
unsigned char my_strlen(char *str)
{
	/* Initialize the length counter */
  unsigned char length=0;
	/* Loop through the string until the null terminator is found */
  while(*(str+length) != '\0')
  {
      length++;
  }
  *(str+length) = '\0';
	/* Return the length of the string */
  return length;
}


void my_strcpy(char *dest, const char *src) 
{
	/* Copy each character from src to dest until null terminator is reached */
    while (*src) 
		{
			*dest = *src; 
			dest++;
			src++;
    }
		/* Add the null terminator at the end of the destination string */
    *dest = '\0';  
}

void my_strncpy(char *dest, const char *src, int n) 
{
	/* Initialize counter */
  int i;
	/* Copy characters from src to dest, up to n characters or until null terminator */
  for (i = 0; i < n && src[i] != '\0'; i++) 
	{
		dest[i] = src[i];  
  }
	/* Add the null terminator at the end of the destination string */
  dest[i] = '\0';  
}



char *my_strchr(char *str, char c) 
{
	/* Iterate through the string until the null terminator is reached */
  while (*str != '\0') 
  {
	/* Check if the current character matches c */
    if (*str == c) 
		{
		/* Return the pointer to the first occurrence of c */
      return (char *)str;  
    }
		else 
		{
		/*do not thing*/
		}
    str++;  
   }
	/* Return NULL if the character c is not found */
  return NULL; 
}



char stringcompare(unsigned char* str1, const unsigned char* str2) 
{
  int i = 0;
	/* Iterate through both strings until the end of one is reached */
  while (str1[i] != '\0' && str2[i] != '\0') 
	{
		/* If characters do not match, return 0 (not equal) */
    if (str1[i] != str2[i]) 
		{
      return 0;
    }
		else 
		{
		/*do not thing*/
		}
    i++;
  }
	/* Check if both strings reached their null terminators simultaneously */
  if (str1[i] == '\0' && str2[i] == '\0') 
	{
    return 1; /* Strings are equal */
  } 
	else 
	{
    return 0; /* Strings are not equal */
  }
}

unsigned char Check_Format_Setting_Time(char *input) 
{
     unsigned char valid = TRUE;
	 /* Check if the input length is exactly 8 characters */
    if (my_strlen(input) != 8) 
		{
        valid = FALSE;
    }
		else 
		{
			/*do not thing*/
		}
		 /* Validate the structure of the time string */
    if (valid && !(my_isdigit(input[0]) && my_isdigit(input[1]) &&
                   input[2] == '-' &&
                   my_isdigit(input[3]) && my_isdigit(input[4]) &&
                   input[5] == '-' &&
                   my_isdigit(input[6]) && my_isdigit(input[7]))) 
		{
        valid = FALSE;
    }
		else 
		{
			/*do not thing*/
		}
		/* Validate hour range */
    if (valid) 
		{
      int hour = (input[0] - '0') * 10 + (input[1] - '0');
      if (hour < 0 || hour > 23) 
			{
        valid = FALSE;
      }
			else 
			{
				/*do not thing*/
			}
    }
		else 
		{
			/*do not thing*/
		}
		/* Validate minute range */
    if (valid) {
        int minute = (input[3] - '0') * 10 + (input[4] - '0');
        if (minute < 0 || minute > 59) 
				{
            valid = FALSE;
        }
				else 
				{
					/*do not thing*/
				}
    }
		else 
		{
			/*do not thing*/
		}
		/* Validate second range */
    if (valid) 
		{
        int second = (input[6] - '0') * 10 + (input[7] - '0');
        if (second < 0 || second > 59) 
				{
            valid = FALSE;
        }
				else 
				{
					/*do not thing*/
				}
    }
		else 
		{
			/*do not thing*/
		}
		 /* Return the validity of the time format */
    return valid;
}

unsigned char Check_Format_Setting_Date(char *input) 
{
    unsigned char valid = TRUE;
		/* Check if the input length is exactly 10 characters */
    if (my_strlen(input) != 10) 
		{
        valid = FALSE;
    }
		else 
		{
			/*do not thing*/
		}
		/* Validate the structure of the date string */
    if (valid && !(my_isdigit(input[0]) && my_isdigit(input[1]) &&
                   input[2] == '.' &&
                   my_isdigit(input[3]) && my_isdigit(input[4]) &&
                   input[5] == '.' &&
                   my_isdigit(input[6]) && my_isdigit(input[7]) &&
                   my_isdigit(input[8]) && my_isdigit(input[9]))) 
		{
        valid = FALSE;
    }
		else 
		{
			/*do not thing*/
		}
		/* Validate day range */
    if (valid) 
		{
        int day = (input[0] - '0') * 10 + (input[1] - '0');
        if (day < 1 || day > 31) 
				{
            valid = FALSE;
        }
				else 
				{
					/*do not thing*/
				}
    }
		else 
		{
			/*do not thing*/
		}
		/* Validate month range */
    if (valid) 
		{
        int month = (input[3] - '0') * 10 + (input[4] - '0');
        if (month < 1 || month > 12)
				{
            valid = FALSE;
        }
				else 
				{
					/*do not thing*/
				}
    }
		else 
		{
			/*do not thing*/
		}
		 /* Validate year range */
    if (valid) 
		{
        int year = (input[6] - '0') * 1000 + (input[7] - '0') * 100 +
                   (input[8] - '0') * 10 + (input[9] - '0');
        if (year < 1000 || year > 9999) 
				{
            valid = FALSE;
        }
				else 
				{
					/*do not thing*/
				}
    }
		else 
		{
			/*do not thing*/
		}
		/* Return the validity of the date format */
    return valid;
}

unsigned char my_atouchar (char* str)
{
  unsigned char result = 0;
	/* Iterate through the string */
  while (*str) 
  {
		/* Check if the character is not a digit */
    if (*str < '0' || *str > '9') 
    {
      return 0;
    }
		else 
		{
		/*do not thing*/
		}
    result = result * 10 + (*str - '0'); /* Update the result */
    str++;
  }
	/* Return the final result */
  return result; 
}

unsigned short my_atoushort(char *str) 
{
  unsigned short result = 0;
	/* Iterate through the string */
  while (*str) 
  {
		/* Check if the character is not a digit */
		if (*str < '0' || *str > '9') 
    {
			return 0;  
    }
	  else 
		{
		/*do not thing*/	
		}
    result = result * 10 + (*str - '0'); /* Update the result */
    str++;
  }
	/* Return the final result */
  return result; 
}

char* my_strtok(char* str, char* delim) 
{
	char* tokenStart;
	char* tokenEnd; 
  static char* nextToken = NULL;
	/* If str is not NULL, initialize nextToken with str */
  if (str != NULL) 
  {
       nextToken = str; 
  }
	else 
	{
		/*do not thing*/
	}
	/* If there are no more tokens, return NULL */
  if (nextToken == NULL) 
  {
    return NULL;
  }
	else 
	{
		/*do not thing*/
	}
	/* Skip leading delimiters */
	tokenStart = nextToken;
  while (*tokenStart && my_strchr(delim, *tokenStart)) 
  {
     tokenStart++;
  }
	/* If we reach the end of the string, return NULL */
  if (*tokenStart == '\0') 
  {
    nextToken = NULL;
    return NULL;
  }
	else 
	{
		/*do not thing*/
	}
	/* Set tokenEnd to the start of the token */
	tokenEnd	= tokenStart;
	/* Find the end of the token */
  while (*tokenEnd && !my_strchr(delim, *tokenEnd)) 
  {
    tokenEnd++;
  }
	/* If the end of the token is found, null-terminate it */
  if (*tokenEnd) 
  {
   *tokenEnd = '\0';
    nextToken = tokenEnd + 1;
  } 
  else 
  {
    nextToken = NULL; 
  }
  return tokenStart;
}


