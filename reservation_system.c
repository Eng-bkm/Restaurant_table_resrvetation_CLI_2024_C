#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TABLE_2_CAPACITY 2
#define TABLE_4_CAPACITY 4
#define TABLE_6_CAPACITY 6
#define TABLE_8_CAPACITY 8

#define TABLE_AVAILABLE 0
#define TABLE_BOOKED 1

struct BigMapEntry {
    int capacity;
    int index;
};

struct BigMapEntry bigMap[] = {
    {2, 4},   // 2 -> aBig
    {4, 10},  // 4 -> bBig
    {6, 6},   // 6 -> cBig
    {8, 4}    // 8 -> dBig
};

struct Reservation {
    char customerName[50];
    char phoneNumber[15];
    int numberOfPeople;
    int dateDifference;
    int hour;
    char allergies[100];  //  field for allergies
    char dietaryRequirements[100];  //  field for dietary requirements
};

struct TableNode {
    int tableNumber;
    struct TableNode *next;
};

struct Table {
    int tableNumber;
    int capacity;
    int ***availabilityMatrix;  // Change int** to int***
};

//  this is declared globally
struct Table bigArray[4][10];

void initializeTables(struct Table *tables);
void makeReservation(struct Table *tables, struct Reservation reservation);
void printTables(struct Table *tables);
void saveMatrixToFile(struct Table *tables);
void loadMatrixFromFile(struct Table *tables);
void printTablesAtThisDate(struct Table *tables);
void bookedDatesOfTable(struct Table *tables, int tableNumber);
void unreserveLastBooking(struct Table *tables);
void printBookings();

int main() {
    struct Table tables[24];
    initializeTables(tables);
    loadMatrixFromFile(tables);

    int command;
    struct Reservation reservation;
    struct Reservation reservation9;
    int date1,hour1;
    int tableNumber23;

    while (1) {
        // Display menu
        printf("Hotel reservation:\n");
        printf("1. Make Reservation\n");
        printf("2. Print booking information\n");
        printf("3. Change previous Reservation\n");
        printf("4. Save Reservations\n");
        printf("5. Exit\n");

        // Get user command
        printf("Enter command (1-5): ");
        scanf("%d", &command);

        switch (command) {
            case 1:
                // Get reservation details from the user
                printf("Enter customer name: ");
                getchar();  // consume newline left by previous scanf
                fgets(reservation.customerName, sizeof(reservation.customerName), stdin);
                reservation.customerName[strcspn(reservation.customerName, "\n")] = '\0';

                printf("Enter phone number: ");
                fgets(reservation.phoneNumber, sizeof(reservation.phoneNumber), stdin);
                reservation.phoneNumber[strcspn(reservation.phoneNumber, "\n")] = '\0';

                printf("Enter number of people: ");
                scanf("%d", &reservation.numberOfPeople);

                printf("Enter date difference: ");
                scanf("%d", &reservation.dateDifference);

                printf("Enter hour: ");
                scanf("%d", &reservation.hour);

                // Get allergies and dietary requirements
                printf("Enter allergies: ");
                getchar();  // consume newline left by previous scanf
                fgets(reservation.allergies, sizeof(reservation.allergies), stdin);
                reservation.allergies[strcspn(reservation.allergies, "\n")] = '\0';

                printf("Enter dietary requirements: ");
                fgets(reservation.dietaryRequirements, sizeof(reservation.dietaryRequirements), stdin);
                reservation.dietaryRequirements[strcspn(reservation.dietaryRequirements, "\n")] = '\0';

                makeReservation(tables, reservation);
                saveMatrixToFile(tables);
                break;

            case 2:
                // Sub-menu for printing tables
                printf("Sub-Menu for Printing Tables:\n");
                printf("1. Print all bookings made\n");
                printf("2. Print Tables at Specific Date and Hour\n");
                printf("3. Print Booked Dates for a Specific Table\n");
                printf("4. Print dates for all tables\n");


                printf("Enter sub-command (1-4): ");

                int subCommand;
                scanf("%d", &subCommand);

                switch (subCommand) {
                    case 1:
                        // Get date and hour from the user
                          // Declare variables here


                        printBookings();
                        break;


                    case 2:
                        // Get date and hour from the user
                          // Declare variables here


                        printTablesAtThisDate(tables);
                        break;

                    case 3:
                        // Get table number from the user

                        printf("Enter table number (0-23): ");
                        scanf("%d", &tableNumber23);

                        // Check if the table number is within the valid range
                        if (tableNumber23 >= 1 && tableNumber23 <= 24) {
                            bookedDatesOfTable(tables, tableNumber23);
                        } else {
                            printf("Invalid table number. Please enter a number between 1 and 24.\n");
                        }
                        break;
                    case 4:
                        printTables(tables);
                        break;


                    default:
                        printf("Invalid sub-command. Please enter a number between 1 and 3.\n");
                        break;
                }
                break;

            case 3:
            // Sub-menu for changing previous reservations
            printf("Sub-Menu for Changing Previous Reservations:\n");
            printf("1. Delete previous Reservation\n");
            printf("2. Change previous Reservation\n");

            printf("Enter sub-command (1-2): ");
            int subCommandChange;
            scanf("%d", &subCommandChange);

            switch (subCommandChange) {
                case 1:
                    // Get reservation details to delete
                    // Call the deleteReservation function
                    unreserveLastBooking(tables);
                    deleteLastLine("booking.txt");
                    saveMatrixToFile(tables);

                    break;

                case 2:
                    // Get reservation details to delete
                    // Call the deleteReservation function
                   unreserveLastBooking(tables);
                    deleteLastLine("booking.txt");
                    saveMatrixToFile(tables);



                    printf("Enter customer name: ");
                getchar();  // consume newline left by previous scanf
                fgets(reservation9.customerName, sizeof(reservation9.customerName), stdin);
                reservation9.customerName[strcspn(reservation9.customerName, "\n")] = '\0';

                printf("Enter phone number: ");
                fgets(reservation9.phoneNumber, sizeof(reservation9.phoneNumber), stdin);
                reservation9.phoneNumber[strcspn(reservation9.phoneNumber, "\n")] = '\0';

                printf("Enter number of people: ");
                scanf("%d", &reservation9.numberOfPeople);

                printf("Enter date difference: ");
                scanf("%d", &reservation9.dateDifference);

                printf("Enter hour: ");
                scanf("%d", &reservation9.hour);

                // Get allergies and dietary requirements
                printf("Enter allergies: ");
                getchar();  // consume newline left by previous scanf
                fgets(reservation9.allergies, sizeof(reservation9.allergies), stdin);
                reservation9.allergies[strcspn(reservation9.allergies, "\n")] = '\0';

                printf("Enter dietary requirements: ");
                fgets(reservation9.dietaryRequirements, sizeof(reservation9.dietaryRequirements), stdin);
                reservation9.dietaryRequirements[strcspn(reservation9.dietaryRequirements, "\n")] = '\0';

                makeReservation(tables, reservation9);
                saveMatrixToFile(tables);

                    // Get new reservation details

                    break;

                default:
                    printf("Invalid sub-command. Please enter a number between 1 and 2.\n");
                    break;
            }
            break;


            case 4:
                // Implement Save Reservations logic
                saveMatrixToFile(tables);
                break;


            case 5:
                // Save availability matrix to file before exiting
                saveMatrixToFile(tables);
                return 0;

            default:
                printf("Invalid command. Please enter a number between 1 and 5.\n");
                break;
        }
    }
}


void initializeTables(struct Table *tables) {
    int a = 0, b = 0, c = 0, d = 0, e = 0;
    for (int i = 0; i < 24; i++) {
        tables[i].tableNumber = i;
        if (i < 4) {
            tables[i].capacity = TABLE_2_CAPACITY;
            bigArray[0][a] = tables[i];
            a++;

        } else if (i >= 4 && i < 14) {
            tables[i].capacity = TABLE_4_CAPACITY;
            bigArray[1][b] = tables[i];
            b++;

        } else if (i >= 14 && i < 20) {
            tables[i].capacity = TABLE_6_CAPACITY;
            bigArray[2][c] = tables[i];
            c++;

        } else if (i >= 20 && i < 24) {
            tables[i].capacity = TABLE_8_CAPACITY;
            bigArray[3][d] = tables[i];
            d++;

        } else {
            printf("Error: Invalid table index\n");
        }

        tables[i].availabilityMatrix = (int ***)malloc(732 * sizeof(int **));
        if (tables[i].availabilityMatrix == NULL) {
            fprintf(stderr, "Memory allocation failed for availabilityMatrix.\n");
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < 732; j++) {
            tables[i].availabilityMatrix[j] = (int **)malloc(24 * sizeof(int *));
            if (tables[i].availabilityMatrix[j] == NULL) {
                fprintf(stderr, "Memory allocation failed for availabilityMatrix row.\n");
                exit(EXIT_FAILURE);
            }

            for (int k = 0; k < 24; k++) {
                tables[i].availabilityMatrix[j][k] = (int *)malloc(sizeof(int));
                if (tables[i].availabilityMatrix[j][k] == NULL) {
                    fprintf(stderr, "Memory allocation failed for availabilityMatrix column.\n");
                    exit(EXIT_FAILURE);
                }

                // Initialize availabilityMatrix with TABLE_AVAILABLE
                tables[i].availabilityMatrix[j][k] = TABLE_AVAILABLE;



            }
        }

    }

}


// Function to make a reservation based on the provided reservation details
void makeReservation(struct Table tables[], struct Reservation reservation) {
    printf("Started reservation\n");

    // Initialization
    struct TableNode *tablesFoundList = NULL;
    int originalNo = (int)reservation.numberOfPeople;
    int noLeft = 0;
    int ecap, ecapDown, ecapUp, ecapOriginal;

    if (originalNo % 2 == 0) {
            ecap = originalNo;
        } else {
            ecap = (int)(originalNo / 2) + 2;
        }
    if (originalNo % 2 == 0) {
            noLeft = originalNo;
        } else {
            noLeft = (int)(originalNo / 2) + 2;
        }
    ecapDown = ecap;
    ecapUp = ecap;
    int ecapDown2 = 8;

    int reservedTables = 0;
    int tablesChecked = 0;



    if (originalNo <= 8) {
        if (originalNo % 2 == 0) {
            ecap = originalNo;
        } else {
            ecap = (int)(originalNo / 2) + 2;
        }
    if (originalNo % 2 == 0) {
            noLeft = originalNo;
        } else {
            noLeft = (int)(originalNo / 2) + 2;
        }
while(noLeft > 0 && ecapUp <=8){




        // Loop to find available tables



            while(ecapDown > 0 && noLeft > 0 ){
            int counter = (ecapDown - 2) / 2;
            // Loop through available tables in the specified category
            for (int i = 0; i < bigMap[counter].index && noLeft >0; i++) {
                if (tables[bigArray[counter][i].tableNumber].availabilityMatrix[reservation.dateDifference][reservation.hour] == TABLE_AVAILABLE) {
                    // Update table as reserved
                    tables[bigArray[counter][i].tableNumber].availabilityMatrix[reservation.dateDifference][reservation.hour] = TABLE_BOOKED;

                    // Add table number to the tablesFoundList
                    struct TableNode *newNode = (struct TableNode *)malloc(sizeof(struct TableNode));
                    newNode->tableNumber = bigArray[counter][i].tableNumber;
                    newNode->next = tablesFoundList;
                    tablesFoundList = newNode;

                    noLeft = noLeft - ecapDown;
                    reservedTables++;
                }

            }

            ecapDown = ecapDown - 2;  // Reservation successful, exit loop
        }

            while( ecapUp <= 8 && noLeft > 0 ){
                printf("going up\n");

            int ecapU1 = ecapUp + 2;

            int counter = (ecapU1 - 2) / 2;

            // Loop through available tables in the specified category
            for (int i = 0; (i < bigMap[counter].index) && noLeft > 0; i++) {
                if (tables[bigArray[counter][i].tableNumber].availabilityMatrix[reservation.dateDifference][reservation.hour] == TABLE_AVAILABLE) {
                    // Update table as reserved
                    tables[bigArray[counter][i].tableNumber].availabilityMatrix[reservation.dateDifference][reservation.hour] = TABLE_BOOKED;

                    // Add table number to the tablesFoundList
                    struct TableNode *newNode = (struct TableNode *)malloc(sizeof(struct TableNode));
                    newNode->tableNumber = bigArray[counter][i].tableNumber;
                    newNode->next = tablesFoundList;
                    tablesFoundList = newNode;

                    noLeft -= ecapU1;
                    reservedTables++;
                }


            ecapUp = ecapUp + 2;
                        }

    }
                }//end of if less }than 8


    }//strat of if greater than 8
    else{
            if (originalNo % 2 == 0) {
            ecap = originalNo;
        } else {
            ecap = (2 * (int)(originalNo / 2)) + 2;
        }
    if (originalNo % 2 == 0) {
            noLeft = originalNo;
        } else {
            noLeft = ( 2 * (int)(originalNo / 2)) + 2;
        }
        while(ecapDown2 > 0 && noLeft > 0){
            int counter = (ecapDown2 - 2) / 2;
            // Loop through available tables in the specified category
            for (int i = 0; i < bigMap[counter].index && noLeft > 0; i++) {
                if (tables[bigArray[counter][i].tableNumber].availabilityMatrix[reservation.dateDifference][reservation.hour] == TABLE_AVAILABLE) {
                    // Update table as reserved
                    tables[bigArray[counter][i].tableNumber].availabilityMatrix[reservation.dateDifference][reservation.hour] = TABLE_BOOKED;

                    // Add table number to the tablesFoundList
                    struct TableNode *newNode = (struct TableNode *)malloc(sizeof(struct TableNode));
                    newNode->tableNumber = bigArray[counter][i].tableNumber;
                    newNode->next = tablesFoundList;
                    tablesFoundList = newNode;

                    noLeft -= ecapDown2;
                    reservedTables++;
                }

            }

            ecapDown2 = ecapDown2 - 2;  // Reservation successful, exit loop
        }
    }//end of greater than 8
    //end of tables checker
    if (noLeft <= 0) {
        // Print saying reservation made
        printf("Reservation made successfully.\n");

        // Put details of the reservation in the booking text
        FILE *bookingFile = fopen("booking.txt", "a");
        if (bookingFile != NULL) {
            fprintf(bookingFile, "%s;%s;%d;%d;%d;%s;%s;", reservation.customerName, reservation.phoneNumber, reservation.numberOfPeople,
                    reservation.dateDifference, reservation.hour, reservation.allergies, reservation.dietaryRequirements);

            // Print reserved table numbers
            struct TableNode *currentNode = tablesFoundList;
            while (currentNode != NULL) {
                fprintf(bookingFile, ",%d", currentNode->tableNumber);
                struct TableNode *tempNode = currentNode;
                currentNode = currentNode->next;
                free(tempNode);
            }

            fprintf(bookingFile, "\n");
            fclose(bookingFile);
        }
    } else {
        // Print reservation not made, no available slot
        printf("Reservation not made. No available slot.\n");

        // Unreserve all the reservations made on the tables in the tablesFoundList
        struct TableNode *currentNode = tablesFoundList;
        while (currentNode != NULL) {
            // Assuming availabilityMatrix is a 2D array
            tables[currentNode->tableNumber].availabilityMatrix[reservation.dateDifference][reservation.hour] = TABLE_AVAILABLE;
            struct TableNode *tempNode = currentNode;
            currentNode = currentNode->next;
            free(tempNode);
        }
    }


}
void deleteLastLine(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Create a temporary file
    FILE *tempFile = fopen("temp_booking.txt", "w");
    if (tempFile == NULL) {
        perror("Error creating temporary file");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Copy content from the original file to the temporary file, excluding the last line
    char line[256];
    char lastLine[256];
    lastLine[0] = '\0';  // Initialize lastLine to an empty string

    while (fgets(line, sizeof(line), file) != NULL) {
        // Save the current line to lastLine before overwriting it
        strcpy(lastLine, line);
    }

    // Return to the beginning of the file
    fseek(file, 0, SEEK_SET);

    // Copy all lines to the temporary file except the last line
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strcmp(line, lastLine) != 0) {
            fputs(line, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Delete the original file and rename the temporary file
    remove(filename);
    rename("temp_booking.txt", filename);
}

void printTablesAtThisDate(struct Table *tables) {
    int date,hour;
    printf("Enter date: ");
                        scanf("%d", &date);
                        printf("Enter hour: ");
                        scanf("%d", &hour);



    int myArray[24] = {0};  // Array to store available tables
    int numAvailableTables = 0;

    for (int i = 0; i < 24; i++) {
        if (tables[i].availabilityMatrix[date][hour] == TABLE_AVAILABLE) {
            // Insert the available table into the array using insertion sort
            int j = numAvailableTables - 1;
            while (j >= 0 && tables[i].tableNumber < myArray[j]) {
                myArray[j + 1] = myArray[j];
                j--;
            }
            myArray[j + 1] = tables[i].tableNumber;
            numAvailableTables++;
        }
    }
    if(numAvailableTables == 0)
        {printf("not tables at date %d and hour %d'n", date, hour);
        }
    else{printf("tables Avialable at date %d and hour %d are\n", date, hour);}

    // Print all available tables in the array with their table number and capacity
    for (int i = 0; i < numAvailableTables; i++) {
        printf("Table %d \n", myArray[i]);
    }
}

void bookedDatesOfTable(struct Table *tables, int tableNumber) {

    printf("Booked Dates for Table %d:\n", tableNumber);



    for (int date = 0; date < 732; date++) {
        for (int hour = 0; hour < 24; hour++) {
            if (tables[tableNumber].availabilityMatrix[date][hour] == TABLE_BOOKED) {

                printf("Table %d is booked at Date %d, Hour %d\n", tableNumber, date, hour);

            }
        }


    }
}

void printTables(struct Table *tables) {
    for(int i = 0; i <24; i++){

        printf("\ntable number %d with capacity %d: \n",tables[i].tableNumber, tables[i].capacity);
        for (int date = 0; date < 732; date++) {
        for (int hour = 0; hour < 24; hour++) {
            if (tables[i].availabilityMatrix[date][hour] == TABLE_BOOKED) {

                printf("\tDate \t%d, \ttHour \t%d\n", i, date, hour);

            }
            else
            {;
            }
            }
        }


    }



}

void saveMatrixToFile(struct Table *tables) {
    FILE *file = fopen("2darray.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 732; j++) {
            for (int k = 0; k < 24; k++) {
                fprintf(file, "%d ", tables[i].availabilityMatrix[j][k]);
            }
            fprintf(file, "\n");
        }
    }

    fclose(file);
}

void loadMatrixFromFile(struct Table *tables) {
    FILE *file = fopen("2darray.txt", "r");
    if (file == NULL) {
        printf("File '2darray.txt' does not exist. Creating a new file.\n");
        return;
    }

    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 732; j++) {
            for (int k = 0; k < 24; k++) {
                fscanf(file, "%d", &tables[i].availabilityMatrix[j][k]);
            }
        }
    }

    fclose(file);
}
void unreserveLastBooking(struct Table *tables) {
    FILE *bookingFile = fopen("booking.txt", "r");
    if (bookingFile == NULL) {
        perror("Error opening booking.txt for reading");
        return;
    }

    // Find the last line in the file
    char lastLine[256];
    while (fgets(lastLine, sizeof(lastLine), bookingFile) != NULL) {
        // Read until the last line
    }

    fclose(bookingFile);
    int integerDate, integerHour;
    int integerArray[24];
    int numTables = 0;
    int is;


    char *token = strtok(lastLine, ";");
    int tokenIndex = 0;
    while (token != NULL) {
        switch (tokenIndex) {
            case 0:
                is++;// Process string1
                break;
            case 1:
                is++;// Process string2
                break;
            case 2:
                is++;// Process string3
                break;
            case 3:
                integerDate = atoi(token);
                break;
            case 4:
                integerHour = atoi(token);
                break;
            case 5:
                is++;// Process string4
                break;
            case 6:
                is++;// Process string5
                break;
            default:

                if (strchr(token, ',') != NULL) {
                        char *numberToken = strtok(token, ",");
                        while (numberToken != NULL && numTables < 24) {
                            integerArray[numTables++] = atoi(numberToken);
                            numberToken = strtok(NULL, ",");
                        }
                    }
                    break;
        }

        token = strtok(NULL, ";");
        tokenIndex++;
    }
    for (int i = 0; i < numTables; i++) {
            printf("%d ",integerArray[i]);
            tables[integerArray[i]].availabilityMatrix[integerDate][integerHour] = TABLE_AVAILABLE;

        }



}
void printBookings() {
    FILE *file = fopen("booking.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char line[256];

    // Read each line from the file
    while (fgets(line, sizeof(line), file) != NULL) {
        char string1[256], string2[256], string3[256], string4[256], string5[256];
        int integerDate, integerHour;
        int integerArray[24];
        int numTables = 0;

        // Tokenize the line using semicolon as a delimiter
        char *token = strtok(line, ";");
        int tokenIndex = 0;

        while (token != NULL) {
            switch (tokenIndex) {
                case 0:
                    strcpy(string1, token);
                    break;
                case 1:
                    strcpy(string2, token);
                    break;
                case 2:
                    strcpy(string3, token);
                    break;
                case 3:
                    integerDate = atoi(token);
                    break;
                case 4:
                    integerHour = atoi(token);
                    break;
                case 5:
                    strcpy(string4, token);
                    break;
                case 6:
                    strcpy(string5, token);
                    break;
                default:

                    if (strchr(token, ',') != NULL) {
                        char *numberToken = strtok(token, ",");
                        while (numberToken != NULL && numTables < 24) {
                            integerArray[numTables++] = atoi(numberToken);
                            numberToken = strtok(NULL, ",");
                        }
                    }
                    break;
            }

            token = strtok(NULL, ";");
            tokenIndex++;
        }

        // Print the retrieved values
        printf("\n\nName: %s\n", string1);
        printf("Phone Number: %s\n", string2);
        printf("Number of People: %s\n", string3);
        printf("Date of Reservation: %d\n", integerDate);
        printf("Hour of Reservation: %d\n", integerHour);
        printf("Allergies: %s\n", string4);
        printf("Dietary Requirements: %s\n", string5);
        printf("tables assigned: ");
        for (int i = 0; i < numTables; i++) {
            printf("%d ",integerArray[i]);
        }
        printf("\n");
    }

    fclose(file);
    return 0;
}

