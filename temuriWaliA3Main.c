/******************************temuriWaliA3.c*******************************************

Student Name: Wali Temuri  Email Id: wtemuri@uoguelph.ca

Due Date: November 25th  Course Name: CIS 1300

I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
1) I have read and understood the University policy on academic integrity.
2) I have completed the Computing with Integrity Tutorial on Moodle; and
3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all
material that I have used, whether directly quoted or paraphrased. Furthermore,
I certify that this assignment was prepared by me specifically for this course.
    
*****************************************************************************************/
/*****************************************************
Compiling the program
The program should be compiled using the following flags: -std=c99 -Wall

compiling:
gcc -std=c99 -Wall temuriWaliA3Main.c temuriWaliA3.c

Running: ./a.out tokyoOlympics.txt
**********************************************************/
#include "givenA3.h"

int main (int argc, char * argv[]) {
    
    if (argc < 2)
    {
        printf("Usage: ./a.out fileName.txt"); //Checks for valid user input
    }

   //declare all variables here
    int choice; //Declaring variable for user choice (Which function they want to use)
    int i; //Decalring variable for the for loop
    char file[50]; //Variable to store the file name
    strcpy(file, argv[1]); //Setting second cmnd line argument to be the file name
    int countryMedalCount [COUNTRIES][MEDALCAT]; //Variable for country medal counts for each category
    char countryNames [COUNTRIES][MAX_LENGTH_CNAME]; //Variable for storing country names
    int totalMedalsAllCountries [COUNTRIES]; //Total medals of all countries
    int totalMedalCat[MEDALCAT]; //Total medals per category
    int maxMedalIndex; //Variable for the Category of the highest number of medals
    char medalCatName[100][100] = {"Gold", "Bronze", "Silver"}; //Variable storing the category of medals
    char countryInput[100]; //User country input for search country function
    int searchMedalIndex; //User Input variable for function 8 to search country,
    int indexOfCountries[COUNTRIES]; //Array with index of variables output from functions 8 and 9
    int maxMedal; //Maximum medal count for function 3
    int onlyMedalInput; //Num of Countries that only won X medals input, function 9
    int countryOnlyXMedal; //Num of countries with only X medals in function 9
    
    // call function readFromFile to populate your arrays
    readFromFile(file, countryMedalCount, countryNames);
    do {
        //Prompting user for input
        printf ("\nHere is the menu \n\n");
        printf ("1. Display all country names read from file and the total number of medals won by each\n");
        printf ("2.    Function 2 - Find total number of medals won by each country\n");
        printf ("3.    Function 3 - Finds total number of medals in each category (Gold, Silver, Bronze)\n");
        printf ("4.    Function 4 – Display horizontal histogram\n");
        printf ("5.    Function 5 – Search for a country and return the total number of medals won by it\n");
        printf ("6.    Function 6 – Rank and display top three countries in order of total medals won\n");
        printf ("7.    Function 7 – Rank and display top three countries in order of total gold medals won\n");
        printf ("8.    Function 8 – Find and display all countries that won no X medals, given X as either Gold, Silver or Bronze\n");
        printf ("9.    Function 9 – Find and display all countries that won ONLY X medals, given X as either Gold, Silver or Bronze\n");
        printf ("10.   Function 10 – Find and display name of the country that has minimum or maximum length among all countries read in option 1\n");
        
        
        printf ("11.   Function 11 – Display vertical histogram\n");
         
       
        printf ("12.    Exit\n");
        
        printf ("Enter your choice: ");
        scanf ("%d", &choice);
        
        switch (choice) {
            case 1:
                //Incrementing through countryNames array to display
                for (i = 0; i < COUNTRIES; i++)
                {
                    printf("Country: %s, Gold = %d, Silver = %d, Bronze = %d\n", countryNames[i], countryMedalCount[i][0], countryMedalCount[i][1], countryMedalCount[i][2]); //Print the i'th countries medals in each category
                }
                break;
            case 2:
                findTotalPerCountry(countryMedalCount, totalMedalsAllCountries); //Calling function 2 to find total medals
                
                for (i = 0; i < COUNTRIES; i++) //Incrementing through country names and total countries
                {
                    printf("%s (%d)\n", countryNames[i], totalMedalsAllCountries[i]); //Printing i'th country and displays corresponding total medals
                }
                break;
            case 3:
                maxMedal = findTotalPerMedal(countryMedalCount,totalMedalCat , &maxMedalIndex); //Initializing variable max to the number of medals in the maximum category
                
                for (i = 0; i < MEDALCAT; i++) //Incrementing through medal categories and total medals in that category
                {
                    printf("Medal = %s, Total = %d\n", medalCatName[i], totalMedalCat[i]); //Print total num of medals in each category
                }
                printf("Maximum number of medals = %d, Category (%s)\n" , maxMedal, medalCatName[maxMedalIndex]);
                break;
            case 4:
                findTotalPerCountry(countryMedalCount, totalMedalsAllCountries); //Calling findTotalPreCountry func. to populate the array totalMedalsAllCountries
                hHistogram(countryNames, totalMedalsAllCountries); //Calling function 4 to print the histogram
                break;
            case 5:
                printf("Which country are you looking for? \n"); //Prompting user to input country of interest
                scanf("%s", countryInput); //Storing user input coutry in countryInput
                
                findTotalPerCountry(countryMedalCount, totalMedalsAllCountries); //Calling to populate totalMedals array
                int countryResult = searchCountry(countryInput, countryNames, totalMedalsAllCountries); //Initiazlizing countryResult to output of fun. (returns -1 for invalid input)
                
                if (countryResult == -1) //if invalid input
                {
                    printf("No country found.\n");
                }
                else //valid input
                {
                    printf("In searchCountry\n");
                    printf("Found it - %s has a total of %d medals\n", countryInput, countryResult);
                }
                break;
            case 6:
                findTotalPerCountry(countryMedalCount, totalMedalsAllCountries); //Calling function to populate array totalMedalsAllCountries
                rankTopThreeByTotal(totalMedalsAllCountries, countryNames); //Calling function 6 to output top three countries in terms of total medals
                break;
            case 7:
                findTotalPerCountry(countryMedalCount, totalMedalsAllCountries); //Calling function to populate array countryMedalCount
                rankTopThreeByMedal(countryMedalCount, countryNames); //Displays top 3 by number of gold medals won
                break;
            case 8:
                printf("Which medal do you want to look for - Type 1 for Gold, 2 for Silver and 3 for Bronze? "); //Prompt user for input
                scanf("%d", &searchMedalIndex); //Scanning and storing input
                
                findTotalPerCountry(countryMedalCount, totalMedalsAllCountries); //Calling function to populate array totalMedalsAllCountries
                int countryNoX = findAllWithNoXMedals(countryMedalCount, searchMedalIndex, indexOfCountries); //Initializing countryNoX to the number of countries with no medals in a specific category
                
                if (searchMedalIndex == 1) //If user inputs Gold
                {
                    printf("The number of countries with no Gold medals = %d\n", countryNoX); //Printing no. of countries with no gold medals
                    
                    for (i = 0; i < countryNoX; i++)
                    {
                        printf("%s\n", countryNames[indexOfCountries[i]]); //Printing each country name that doesn't have gold medals
                    }
                }
                else if (searchMedalIndex == 2) //If user inputs Silver
                {
                    printf("The number of countries with no Silver medals = %d\n", countryNoX); //Printing no. of countries with no silver medals

                    
                    for (i = 0; i < countryNoX; i++)
                    {
                        printf("%s\n", countryNames[indexOfCountries[i]]); //Printing each country name that doesn't have silver medals
                    }
                }
                else if (searchMedalIndex == 3) //if user inputs Bronze
                {
                    printf("The number of countries with no Bronze medal = %d\n", countryNoX);//Printing no. of countries with no bronze medals
                    
                    for (i = 0; i < countryNoX; i++)
                    {
                        printf("%s\n", countryNames[indexOfCountries[i]]); //Printing each country name that doesn't have bronze medals
                    }
                }
                else //invalid input
                {
                    printf("Invalid Input.\n");
                }
                break;
            case 9:
                printf("Which medal do you want to look for - Type 1 for Gold, 2 for Silver and 3 for Bronze? \n"); //Prompting user for input
                scanf("%d", &onlyMedalInput); //Scanning user input
                
                findTotalPerCountry(countryMedalCount, totalMedalsAllCountries); //Calling functino to populate array totalMedalsAllCountries
                countryOnlyXMedal = findAllWithOnlyXMedals(countryMedalCount, onlyMedalInput, indexOfCountries); //Calling func 9 , setting variable to no of countries with only X category of medals
                
                if (onlyMedalInput == 1) //if gold
                {
                    printf("The number of countries with only Gold medals = %d\n", countryOnlyXMedal); //print num of countries with only gold
                    
                    for (i = 0; i < countryOnlyXMedal; i++)
                    {
                        printf("%s\n", countryNames[indexOfCountries[i]]); //print country names with only gold
                    }
                }
                else if (onlyMedalInput == 2) //if silver
                {
                    printf("The number of countries with only Silver medals = %d\n", countryOnlyXMedal); //print num of countries with only silver
                    
                    for (i = 0; i < countryOnlyXMedal; i++)
                    {
                        printf("%s\n", countryNames[indexOfCountries[i]]); //print country names with only silver
                    }
                }
                else if (onlyMedalInput == 3) //if bronze
                {
                    printf("The number of countries with only Bronze medal = %d\n", countryOnlyXMedal); //print num of countries with only bronze
                    
                    for (i = 0; i < countryOnlyXMedal; i++) //print country names with only bronze
                    {
                        printf("%s\n", countryNames[indexOfCountries[i]]); //print num of countries with only bronze
                    }
                }
                else //invalid input
                {
                    printf("Invalid Input.\n");
                }
                break;
            case 10:
                printf("Do you want min (enter 1) or max (enter 2)?\n"); //Prompt user for input
                int minOrMaxInput; //UserInput variable
                int minOrMaxIndex; //index of country with min or max
                scanf("%d", &minOrMaxInput); //scanning user input
                minOrMaxIndex = findCountryIndexWithMinOrMaxLength(minOrMaxInput, countryNames); //setting variable to index of min or max
                
                switch (minOrMaxInput)
                {
                    case 1: //User wants min
                        printf("The country name with the minimum length = %s\n", countryNames[minOrMaxIndex]); //print min
                        break;
                    case 2: //User wants max
                        printf("The country name with the maximum length = %s\n", countryNames[minOrMaxIndex]); //print max
                        break;
                    default:
                        break;
                }
                break;
            case 11:
                findTotalPerCountry(countryMedalCount, totalMedalsAllCountries); //Call function to populate totalMedalsAllCountries Array
                vHistogram(countryNames, totalMedalsAllCountries); //Print vertical histogram by calling function 11
                break;
            case 12:
                break;
            default:
                printf ("That is an invalid choice\n");
                break;
                
        }
        
    } while (choice != 12);
    
    
   return 0;
}

