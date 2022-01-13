#include "givenA3.h"


typedef struct //Struct of total country medals and their corresponding indices
{
    int countryIndex;
    int countryMedalCount;
}TotalMedals;

typedef struct //Struct of number of gold won by country and the corresponding index
{
    int numGold;
    int countryIndex;
}CountryGold;



/*Function readFromFile reads country name and medals won in each category from a textfile and stores the info into arrays and variables
 In: char fName [30], int country [COUNTRIES][MEDALCAT], char countryNames [COUNTRIES][MAX_LENGTH_CNAME]
 Out: None (Void)
 Post: Stores information into arrays
*******/
void readFromFile (char fName [30], int country [COUNTRIES][MEDALCAT], char countryNames [COUNTRIES][MAX_LENGTH_CNAME])
{
    FILE* inputFile = NULL; //Initializing file pointer
    
    inputFile = fopen(fName, "r"); //Opening the file passed in the filename parameter
    
    if (inputFile == NULL) //Checking for error in opening the file
    {
        printf("Could not open file %s\n", fName); //if cannot open file, print error msg
    }
    
    int i = 0; //initializing i to 0 to increment index # in country array
    
    while (!feof(inputFile)) // Looping through the file until reaching the end
    {
        //Stores the country name at the i'th index of countryNames and each respective medal category in country array
        fscanf(inputFile, "%s %d %d %d" , countryNames[i], &country[i][MEDALCAT - 3], &country[i][MEDALCAT - 2], &country[i][MEDALCAT - 1]);
        i++;
    }
    
}

/*Function findTotalPerCountry finds the total number of medals won by each country
 In: int country [COUNTRIES] [MEDALCAT], int totalAllCountries [COUNTRIES]
 Out: None (Void)
 Post: Stores information into arrays
*******/
void findTotalPerCountry (int country [COUNTRIES] [MEDALCAT], int totalAllCountries [COUNTRIES])
{
    int i; //Declaring variable for the for loop.
    
    for (i = 0; i < COUNTRIES; i++) //Iterating through each country in country array
    {
        totalAllCountries[i] = country[i][MEDALCAT - 3] + country[i][MEDALCAT - 2] + country[i][MEDALCAT - 1]; //Summing the number of medals in each category for the i'th country (each country)
    }
}

/*Function findTotalPerMedal finds the total number of medals won in general
 In: int country [COUNTRIES][MEDALCAT], int totalAllMedals [MEDALCAT], int * whichMedal
 Out: Returns maximum number of medals in X category
 Post: Stores information into arrays and passes on the index of the category with max medals
*******/
int findTotalPerMedal (int country [COUNTRIES][MEDALCAT], int totalAllMedals [MEDALCAT], int * whichMedal)
{
    int i; //Declaring variable for the for loop
    
    totalAllMedals[0] = 0;
    totalAllMedals[1] = 0; //Initializing the total medals to 0 to begin with.
    totalAllMedals[2] = 0;
    
    //Totaling the number of Gold medals
    
    for (i = 0; i < COUNTRIES; i++)
    {
        totalAllMedals[MEDALCAT - 3] = totalAllMedals[MEDALCAT - 3] + country [i][MEDALCAT - 3];
    }
    
    //Totaling the number of Silver medals
    
    for (i = 0; i < COUNTRIES; i++)
    {
        totalAllMedals[MEDALCAT - 2] = totalAllMedals[MEDALCAT - 2] + country [i][MEDALCAT - 2];
    }
    //Totaling the number of Bronze medals
    
    for (i = 0; i < COUNTRIES; i++)
    {
        totalAllMedals[MEDALCAT - 1] = totalAllMedals[MEDALCAT - 1] + country [i][MEDALCAT - 1];
    }
    
    //Finding Max Number
    int max = totalAllMedals[0]; //Initialize first number to max to begin with
    *whichMedal  = 0; //Initialize the index number to 0 to begin with as well
    
    for (i = 0; i < MEDALCAT; i++) //Iterating through total of all medal categories array
    {
        if (totalAllMedals[i] > max) //if the i'th category is larger than the current max
        {
            max = totalAllMedals[i]; //Set new max
            *whichMedal = i; //Set new index
        }
    }
    
    return max;
}

/*Function hHistogram prints horizontal histogram of countries and total medals won
 In: char countryNames [COUNTRIES][MAX_LENGTH_CNAME], int totalMedals[COUNTRIES]
 Out: None (void)
 Post: Prints horizontal histogram
*******/
void hHistogram (char countryNames [COUNTRIES][MAX_LENGTH_CNAME], int totalMedals[COUNTRIES])
{
    int i; //Declaring integer variable for the for loop
     
    for (i = 0; i  < COUNTRIES; i++) //Using for loop to iterate through the array of countries
    {
        printf("%s", countryNames[i]); //Printing country name
        int temp = 11.0 - strlen((countryNames[i])); //Calculating the number of spaces needed to print. (total spaces = 25, 25 - strlen(string) = # of spaces)
        printf("%*c", temp, ':'); //Printing ':' at the location calculated, allows histogram to look uniform
        printf(" "); //Printing a space before the stars
        printf("%.*s", totalMedals[i], "******************************************************************************************"); //Prints the # of medals won of the i'th country in stars
        printf(" (%d)\n", totalMedals[i]); //Displays the integer value of the #of medals won
    }
    
        
}

/*Function searchCountry searches user input in the list of countries and returns the total number of medals if country found
 In: char countryName [MAX_LENGTH_CNAME], char countryNames [COUNTRIES][MAX_LENGTH_CNAME], int totalAllCountries [COUNTRIES]
 Out: returns -1 if invalid input, else returns total number of countries won by country selected
 Post: Prints out total medals if input is valid, else prints "invalid input"
*******/
int searchCountry (char countryName [MAX_LENGTH_CNAME], char countryNames [COUNTRIES][MAX_LENGTH_CNAME], int totalAllCountries [COUNTRIES])
{
    int i; //Declaring variable for for loop
    
    for (i = 0; i < COUNTRIES; i++) //Iterating through array of valid country names
    {
        if (strcmp(countryName, countryNames[i]) == 0) // Comparing user input to each country in array
        {
            return totalAllCountries[i]; //If valid country input, returns total medals that country has won
        }
    }
    
    return -1; //Return -1 if not valid input
}

/*Function rankTopThreeByTotal finds the countries with top 3 number of total medals and prints them
 In: int totalMedals[COUNTRIES], char countryNames [COUNTRIES][MAX_LENGTH_CNAME]
 Out: None (void)
 Post: Prints out top three countries based on total medals won and their medal counts
*******/
void rankTopThreeByTotal (int totalMedals[COUNTRIES], char countryNames [COUNTRIES][MAX_LENGTH_CNAME])
{
    TotalMedals allCountries[COUNTRIES] = {0}; //Declaring a struct variable for all countries, giving each a index  # and medal count
    
    
    int i, j; //Declaring variables for the for loop
    
    for (i = 0; i < COUNTRIES; i++) //Populating Allcountries, assigning each a index num and medal count
    {
        allCountries[i].countryMedalCount = totalMedals[i];
        allCountries[i].countryIndex = i;
    }
    
    int temp = 0; //temp variable to keep track of the first element when sorting array
    
    for (i = 0; i < COUNTRIES; i++) //Sorting allCountries by medal count highest to lowest
    {
        for (j = i + 1; j < COUNTRIES; j++) //Counter for next element
        {
            if (allCountries[i].countryMedalCount < allCountries[j].countryMedalCount)// If the j'th element is greater than the i'th they switch spots
            {
                //Switching medal counts
                temp = allCountries[i].countryMedalCount;
                allCountries[i].countryMedalCount = allCountries[j].countryMedalCount;
                allCountries[j].countryMedalCount = temp;
                
                //Switching indices
                temp = allCountries[i].countryIndex;
                allCountries[i].countryIndex = allCountries[j].countryIndex;
                allCountries[j].countryIndex = temp;
            }
        }
    }
    
    printf("%s (%d)\n", countryNames[allCountries[0].countryIndex], allCountries[0].countryMedalCount);
    printf("%s (%d)\n", countryNames[allCountries[1].countryIndex], allCountries[1].countryMedalCount); //Printing Results
    printf("%s (%d)\n", countryNames[allCountries[2].countryIndex], allCountries[2].countryMedalCount);
    
}
/*Function rankTopThreeByMedal finds the countries with top 3 number of gold medals and prints them
 In: int country [COUNTRIES] [MEDALCAT], char countryNames [COUNTRIES][MAX_LENGTH_CNAME]
 Out: None (void)
 Post: Prints out top three countries based on total gold medals won and their gold medal counts
*******/
void rankTopThreeByMedal (int country [COUNTRIES] [MEDALCAT], char countryNames [COUNTRIES][MAX_LENGTH_CNAME])
{
    int i, j; //Declaring variables for the for loop
    
    CountryGold allCountries[COUNTRIES]; //Declaring struct variable to keep track of index num and num of gold won
    
    for (i = 0; i < COUNTRIES; i++) //for loop to populate allCountries array
    {
        allCountries[i].countryIndex = i;
        allCountries[i].numGold = country[i][0];
    }
    
    int temp = -1; // temp value to temporarily store a value while its being swapped
    
    //Sorting Algorithm, sorting by number of gold won in descending order
    
    for (i = 0; i < COUNTRIES; i++) //Incrementing through countries
    {
        for (j = i + 1; j < COUNTRIES; j++) //Checking next element after the i'th
        {
            if (allCountries[i].numGold < allCountries[j].numGold) //if the i'th country has less gold than the j'th, they swap
            {
                //Swapping number of gold
                allCountries[i].numGold = temp;
                allCountries[i].numGold = allCountries[j].numGold;
                allCountries[j].numGold = temp;
                
                //Swapping index nums
                temp = allCountries[i].countryIndex;
                allCountries[i].countryIndex = allCountries[j].countryIndex;
                allCountries[j].countryIndex = temp;
            }
        }
    }
    
    printf("%s (%d)\n", countryNames[allCountries[0].countryIndex], allCountries[0].numGold);
    printf("%s (%d)\n", countryNames[allCountries[1].countryIndex], allCountries[1].numGold); //Printing results
    printf("%s (%d)\n", countryNames[allCountries[2].countryIndex], allCountries[2].numGold);
}

/*Function findAllWithNoXMedals finds the countries with no medals in X category
 In: int country [COUNTRIES] [MEDALCAT], int indexMedal, int indexOfCountries [COUNTRIES]
 Out: total number of countries with no X type of medal
 Post: Prints out countries with no medals in the category the user inputs
*******/
int findAllWithNoXMedals (int country [COUNTRIES] [MEDALCAT], int indexMedal, int indexOfCountries [COUNTRIES])
{
    int i; //Declaring variable for the for loop
    int totalZero = 0; //Declaring and initializing variable to 0 to count number of countries with no medals won in given category
    int indexCount = -1; //initializing the index count to -1 to begin with
    
    for (i = 0; i < COUNTRIES; i++) //Incrementing through array of countries
    {
        if (country [i][indexMedal - 1] == 0) //if medal count of the specific category passed on is 0
        {
            totalZero++; //increment total zero count
            indexCount++; //increment the index count
            indexOfCountries [indexCount] = i; //record index num which is equal to in the index of countries array
        }
    }
    
    return totalZero; //return total number of countries with zero medals in the specified category
}

/*Function findAllWithOnlyXMedals finds the countries with only medals in X category
 In: int country [COUNTRIES][MEDALCAT], int indexMedal, int indexOfCountries [COUNTRIES]
 Out: Num of countries with medals in only X category
 Post: Prints out countries with medals in only X category
*******/
int findAllWithOnlyXMedals (int country [COUNTRIES][MEDALCAT], int indexMedal, int indexOfCountries [COUNTRIES])
{
    int i; //Declaring variable for the for loop
    int indexCount = -1; //Initializing the index count to -1, when incremented = 0 which is first index
    int countryCount = 0; //Initializing # of countries with only X medals to 0
    
    if (indexMedal == 1) //If user chooses Gold
    {
        for (i = 0; i < COUNTRIES; i++) //iterates through the countries
        {
            if ( (country[i][1 - 1] > 0) && (country[i][2 - 1] == 0) && (country[i][3 - 1] == 0) ) //If the medal cat of interest is > 0 and the rest of the cats = 0
            {
                countryCount++; //Increment country count
                indexCount++; //Increment index num
                indexOfCountries[indexCount] = i; //Set the current index to the i which is the index of the country of interest
            }
        }
    }
    else if (indexMedal == 2) //If user chooses Silver
    {
        for (i = 0; i < COUNTRIES; i++) //iterates through the countries
        {
            if ( (country[i][1 - 1] == 0) && (country[i][2 - 1] > 0) && (country[i][3 - 1] == 0) ) //If the medal cat of interest is > 0 and the rest of the cats = 0
            {
                countryCount++; //Increment country count
                indexCount++; //Increment index num
                indexOfCountries[indexCount] = i; //Set the current index to the i which is the index of the country of interest
            }
        }
    }
    else if (indexMedal == 3) //If user chooses Bronze
    {
        for ( i = 0; i < COUNTRIES; i++) //iterates through the countries
        {
            if ( (country[i][1 - 1] == 0) && (country[i][2 - 1] == 0) && (country[i][3 - 1] > 0) ) //If the medal cat of interest is > 0 and the rest of the cats = 0
            {
                countryCount++; //Increment country count
                indexCount++; //Increment index num
                indexOfCountries[indexCount] = i; //Set the current index to the i which is the index of the country of interest
            }
        }
    }
    
    return countryCount; //Return total countries with only X medals
}

/*Function findCountryIndexWithMinOrMaxLength finds the countries with min or max length ( user specified )
 In: int minOrMax, char countryNames [COUNTRIES][MAX_LENGTH_CNAME]
 Out: index number of country with max length
 Post: Prints out country with max or min length
*******/
int findCountryIndexWithMinOrMaxLength (int minOrMax, char countryNames [COUNTRIES][MAX_LENGTH_CNAME])
{
    int i; //Declaring variable for the for loop
    int indexNum = 0; //initiazliing the indexNum to first index (0) to begin with
    
    if (minOrMax == 1) //If user asks for minimum length country
    {
        int min = strlen(countryNames[0]) + 0.0; //set min to the length of the first country
        
        for (i = 0; i < COUNTRIES; i++) //iterate through all countries
        {
            if (strlen(countryNames[i]) < min) //if the i'th country is less than min
            {
                min = strlen(countryNames[i]) + 0.0; //the i'th country is the new min
                indexNum = i; //index num is set to i for the i'th country
            }
        }
        return indexNum; //return the index num of min country length
    }
             
    else if (minOrMax == 2) //If user asks for max lenght country
    {
        int max = strlen(countryNames[0]) + 0.0; //Set max to the length of the first country
        
        for (i = 0; i < COUNTRIES; i++) //Iterate through countryNames
        {
            if (strlen(countryNames[i]) > max) //if the i'th country is longer than the current max
            {
                max = strlen(countryNames[i]) + 0.0; //new max is the i'th country
                indexNum = i; //Store index num
            }
        }
        return indexNum; //return index num of max length country
    }
    
    return -1; //if something goes wrong return -1
}

/*Function vHistogram prints a vertical histogram of countries and total medals won
 In: char countryNames [COUNTRIES][MAX_LENGTH_CNAME], int totalMedals[COUNTRIES]
 Out: None (void)
 Post: Prints vertical histogram of countries and num of medals won
*******/
void vHistogram (char countryNames [COUNTRIES][MAX_LENGTH_CNAME], int totalMedals[COUNTRIES])
{
    //Step 1: Finding country with max # of medals
    int i ,j; //Declaring variables for the for loops
    int max = totalMedals[0]; //Initializing max to the first index to begin the comparison with
    
    for (i = 0; i < COUNTRIES; i++) //Iterate through totalMedals array
    {
        if (max < totalMedals[i]) //if the i'th element is greather than max
        {
            max = totalMedals[i]; //Set new max
        }
    }
    
    //Print total medals for each country on the first line
    for (i = 0; i < COUNTRIES; i++) //iterating through totalMedals
    {
        printf("%-12d", totalMedals[i]); //Printing total medals for each country
    }
    printf("\n"); //end with new line
    
    //Print the stars
    for(i = max; i > -1; i--) //Setting i to max to comapre each countries total medals to the max and incrementing down
    {
        for (j = 0; j < COUNTRIES; j++) //iterating through total medals in all countries
        {
            
            if (totalMedals[j] > i) //if current index country is greater than i
            {
                printf("%-12s", "*"); //print a star if true
                
            }
            else
            {
                printf("%-12s" , " "); //print blank space if condition not met
            }
        }
        printf("\n"); //end on new line
    }
    
    //Finally print the country names along the X axis
    
    for (i = 0; i < COUNTRIES; i++) //iterate through all country names
    {
        printf("%-12s", countryNames[i]); //print each country

    }
    printf("\n"); //end on new line
}
