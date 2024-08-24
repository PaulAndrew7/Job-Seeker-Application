#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct seeker {
  int ID;
  char name[50];
  int age;
  char qualifications[50][50];
  int no_Of_Qualifications;
  int experience;
  char shift[5];
  int shift_c;
  int salary[2];
};

struct employer {
  int ID;
  char name[50];
  char qualifications[50][50];
  int qualification_constraints[50];
  int no_Of_Qualifications;
  int working_hours;
  char shift[5];
  int salary;
  int experience[2];
};

char *removeSpaces(const char *str) {
  int len = strlen(str);
  char *result = (char *)malloc(len * sizeof(char));
  int i, j;

  for (i = 0, j = 0; i < len; i++) {
    if (str[i] != ' ') {
      result[j++] = str[i];
    }
  }

  result[j] = '\0';

  return result;
}

void createJobseeker(struct seeker seekers[], int numSeeker) {
  int i = 0;
  char ch, password[50];

  printf("\nEnter Name: ");
  scanf(" %[^\n]", seekers[numSeeker].name);
  char *username = removeSpaces(seekers[numSeeker].name);

  // Check if the username already exists
  FILE *fp = fopen("seekerLogins.txt", "r");
  if (fp != NULL) {
    char line[100];
    while (fgets(line, sizeof(line), fp)) {
      char storedUsername[50];
      sscanf(line, "%s", storedUsername);
      if (strcmp(username, storedUsername) == 0) {
        fclose(fp);
        printf("Username already exists. Please try again.\n");
        return;
      }
    }
    fclose(fp);
  }

  printf("Enter a password: ");
  scanf("%s", password);

  // Store the new account in the login database
  fp = fopen("seekerLogins.txt", "a");
  if (fp == NULL) {
    printf("Error opening login database.\n");
    return;
  }

  fprintf(fp, "%s %s\n", username, password);
  fclose(fp);

  seekers[numSeeker].ID = numSeeker + 1;

  // gathering details
  printf("\nEnter age: ");
  scanf("%d", &seekers[numSeeker].age);
  printf("\nExperience (in months): ");
  scanf("%d", &seekers[numSeeker].experience);
  printf("\nPreferred Shift? (day/night): ");
  scanf(" %[^\n]", seekers[numSeeker].shift);
  printf("\nOptional or Compulsory? (0/1): ");
  scanf("%d", &seekers[numSeeker].shift_c);
  printf("\nExpected salary: ");
  scanf("%d", &seekers[numSeeker].salary[0]);
  printf("\nOptional or Compulsory? (0/1): ");
  scanf("%d", &seekers[numSeeker].salary[1]);
  while (1) {
    printf("\nEnter qualification: ");
    scanf(" %[^\n]", seekers[numSeeker].qualifications[i]);
    i++;
    printf("\nAdd more? (y/n): ");
    scanf(" %c", &ch);
    if (ch == 'n') {
      break;
    }
  }
  seekers[numSeeker].no_Of_Qualifications = i;
  free(username);
}

void createEmployer(struct employer employers[], int numEmployer) {
  int i = 0;
  char ch, password[50];
  employers[numEmployer].ID = numEmployer + 1;
  printf("\nEnter Company Name: ");
  scanf(" %[^\n]", employers[numEmployer].name);
  char *username = removeSpaces(employers[numEmployer].name);

  // Check if the username already exists
  FILE *fp = fopen("employerLogins.txt", "r");
  if (fp != NULL) {
    char line[100];
    while (fgets(line, sizeof(line), fp)) {
      char storedUsername[50];
      sscanf(line, "%s", storedUsername);
      if (strcmp(username, storedUsername) == 0) {
        fclose(fp);
        printf("Username already exists. Please try again.\n");
        return;
      }
    }
    fclose(fp);
  }

  printf("Enter a password: ");
  scanf("%s", password);

  // Store the new account in the login database
  fp = fopen("employerLogins.txt", "a");
  if (fp == NULL) {
    printf("Error opening login database.\n");
    return;
  }

  fprintf(fp, "%s %s\n", username, password);
  fclose(fp);

  // gather details
  printf("\nEnter working hours: ");
  scanf("%d", &employers[numEmployer].working_hours);
  printf("\nExperience (in months): ");
  scanf("%d", &employers[numEmployer].experience[0]);
  printf("\nOptional or Compulsory? (0/1): ");
  scanf("%d", &employers[numEmployer].experience[1]);
  printf("\nWorking Shift (day/night): ");
  scanf("%s", employers[numEmployer].shift);
  printf("\nOffered salary: ");
  scanf("%d", &employers[numEmployer].salary);
  while (1) {
    printf("\nEnter required qualification: ");
    scanf(" %[^\n]", employers[numEmployer].qualifications[i]);
    printf("\nOptional or Compulsory? (0/1): ");
    scanf("%d", &employers[numEmployer].qualification_constraints[i]);
    i++;
    printf("\nAdd more? (y/n): ");
    scanf(" %c", &ch);
    if (ch == 'n') {
      break;
    }
  }
  employers[numEmployer].no_Of_Qualifications = i;
  free(username);
}

int validateSeekerLogin(char *username, char *password) {
  // Check if the username and password match a record in the database
  FILE *fp = fopen("seekerLogins.txt", "r");
  if (fp == NULL) {
    printf("Login database does not exist.\n");
    return 0;
  }

  char line[100];
  while (fgets(line, sizeof(line), fp)) {
    char storedUsername[50], storedPassword[50];
    sscanf(line, "%s %s", storedUsername, storedPassword);
    if (strcmp(username, storedUsername) == 0 &&
        strcmp(password, storedPassword) == 0) {
      fclose(fp);
      return 1; // Valid login credentials
    }
  }

  fclose(fp);
  return 0; // Invalid login credentials
}
int validateEmployerLogin(char *username, char *password) {
  // Check if the username and password match a record in the database
  FILE *fp = fopen("employerLogins.txt", "r");
  if (fp == NULL) {
    printf("Login database does not exist.\n");
    return 0;
  }

  char line[100];
  while (fgets(line, sizeof(line), fp)) {
    char storedUsername[50], storedPassword[50];
    sscanf(line, "%s %s", storedUsername, storedPassword);
    if (strcmp(username, storedUsername) == 0 &&
        strcmp(password, storedPassword) == 0) {
      fclose(fp);
      return 1; // Valid login credentials
    }
  }

  fclose(fp);
  return 0; // Invalid login credentials
}
void displaySeeker(struct seeker seekers[], int numSeeker) {
  printf("\nName: %s", seekers[numSeeker].name);
  printf("\nAge: %d", seekers[numSeeker].age);
  printf("\nExperience: %d months", seekers[numSeeker].experience);
  printf("\nShift: %s", seekers[numSeeker].shift);
  if (seekers[numSeeker].shift_c) {
    printf("  Compulsory?: Yes");
  } else {
    printf("  Compulsory?: No");
  }
  printf("\nExpected salary: %d", seekers[numSeeker].salary[0]);
  if (seekers[numSeeker].salary[1] == 1) {
    printf("  Compulsory?: Yes");
  } else {
    printf("  Compulsory?: No");
  }
  printf("\nQualifications: ");
  for (int i = 0; i < seekers[numSeeker].no_Of_Qualifications; i++) {
    printf("\n%s", seekers[numSeeker].qualifications[i]);
  }
}
void displayEmployer(struct employer employers[], int numEmployer) {
  printf("\nName: %s", employers[numEmployer].name);
  printf("\nWorking hours: %d", employers[numEmployer].working_hours);
  printf("\nExperience: %d months", employers[numEmployer].experience[0]);
  if (employers[numEmployer].experience[1] == 1) {
    printf("  Compulsory?: Yes");
  } else {
    printf("  Compulsory?: No");
  }
  printf("\nShift: %s", employers[numEmployer].shift);
  printf("\nOffered salary: %d", employers[numEmployer].salary);
  printf("\nRequired Qualifications: ");
  for (int i = 0; i < employers[numEmployer].no_Of_Qualifications; i++) {
    printf("\n%s", employers[numEmployer].qualifications[i]);
    if (employers[numEmployer].qualification_constraints[i] == 1) {
      printf("  Compulsory?: Yes");
    } else {
      printf("  Compulsory?: No");
    }
  }
}
// store the seekers into a file
void storeSeekers(const char *filename, struct seeker *seekers,
                  int numSeekers) {
  FILE *file = fopen(filename, "wb");
  if (file == NULL) {
    printf("Error opening file: %s\n", filename);
    return;
  }

  fwrite(&numSeekers, sizeof(int), 1,
         file); // Writing the number of seekers as the first record

  fwrite(seekers, sizeof(struct seeker), numSeekers, file);

  fclose(file);
}
// store the employers into a file
void storeEmployers(const char *filename, struct employer *employers,
                    int numEmployers) {
  FILE *file = fopen(filename, "wb");
  if (file == NULL) {
    printf("Error opening file: %s\n", filename);
    return;
  }

  fwrite(&numEmployers, sizeof(int), 1,
         file); // Writing the number of employers as the first record

  fwrite(employers, sizeof(struct employer), numEmployers, file);

  fclose(file);
}
// read the seekers from file
void readSeekers(const char *filename, struct seeker *seekers,
                 int *numSeekers) {
  FILE *file = fopen(filename, "rb");
  if (file == NULL) {
    printf("Error opening file: %s\n", filename);
    return;
  }

  fread(numSeekers, sizeof(int), 1,
        file); // Reading the number of seekers from the first record

  fread(seekers, sizeof(struct seeker), *numSeekers, file);

  fclose(file);
}
// read the employers from file
void readEmployers(const char *filename, struct employer *employers,
                   int *numEmployers) {
  FILE *file = fopen(filename, "rb");
  if (file == NULL) {
    printf("Error opening file: %s\n", filename);
    return;
  }

  fread(numEmployers, sizeof(int), 1,
        file); // Reading the number of employers from the first record

  fread(employers, sizeof(struct employer), *numEmployers, file);

  fclose(file);
}

// calculate match percentage
float seekerMatchPercentage(struct seeker seeker, struct employer employer) {
  float totalScore = 0.0, w1 = 0.85, w2 = 1.0, w3 = 0.25;
  // comparing shifts
  if (strcmp(employer.shift, seeker.shift) == 0) {
    if (seeker.shift_c == 1) {
      totalScore += w1;
    } else {
      totalScore += w2;
    }
  } else {
    if (seeker.shift_c == 0) {
      totalScore += w3;
    }
  }

  // comparing salary
  if (employer.salary >= seeker.salary[0]) {
    if (seeker.salary[1] == 1) {
      totalScore += w1;
    } else {
      totalScore += w2;
    }
  } else {
    if (seeker.salary[1] == 0) {
      totalScore += w3;
    }
  }

  // totalScore calculation
  totalScore /= 2.0;
  return totalScore * 100;
}

float employerMatchPercentage(struct employer employer, struct seeker seeker) {
  float totalScore = 0.0, w1 = 0.85, w2 = 1.0, w3 = 0.25;
  // compare experience
  if (seeker.experience >= employer.experience[0]) {
    if (employer.experience[1] == 1) {
      totalScore += w1;
    } else {
      totalScore += w2;
    }
  } else {
    if (employer.experience[1] == 0) {
      totalScore += w3;
    }
  }
  // compare qualifications

  for (int i = 0; i < employer.no_Of_Qualifications; i++) {
    int check = 0;
    for (int j = 0; j < seeker.no_Of_Qualifications; j++) {
      if (strcmp(seeker.qualifications[j], employer.qualifications[i]) == 0) {
        check = 1;
        break;
      }
    }
    if (check) {
      if (employer.qualification_constraints[i] == 1) {
        totalScore += w1;
      } else {
        totalScore += w2;
      }
    } else if (employer.qualification_constraints[i] == 0) {
      totalScore += w3;
    }
  }
  totalScore /= employer.no_Of_Qualifications + 1;
  return totalScore * 100;
}
// Function to swap two float values
void swap(float arr[][2], int a, int b) {
  float temp1 = arr[a][0];
  float temp2 = arr[a][1];
  arr[a][0] = arr[b][0];
  arr[a][1] = arr[b][1];
  arr[b][0] = temp1;
  arr[b][1] = temp2;
}

// Partition function for quicksort
int partition(float arr[][2], int low, int high) {
  float pivot = arr[high][1];
  int i = low - 1;

  for (int j = low; j < high; j++) {
    if (arr[j][1] >= pivot) {
      i++;
      swap(arr, i, j);
    }
  }

  swap(arr, i + 1, high);
  return (i + 1);
}

// Quicksort function to sort two-dimensional float array based on the second
// element in descending order
void quicksortDescending(float arr[][2], int low, int high) {
  if (low < high) {
    int pi = partition(arr, low, high);

    quicksortDescending(arr, low, pi - 1);
    quicksortDescending(arr, pi + 1, high);
  }
}

// Function to sort a two-dimensional float array based on the second element in
// descending order using quicksort
void sortDescending(float arr[][2], int size) {
  quicksortDescending(arr, 0, size - 1);
}

int main() {
  int numSeeker, numEmployer, choice, s;
  char username[50], password[50];
  struct seeker seekers[100];
  struct employer employers[100];
  int readNumSeekers;
  int readNumEmployers;
  readSeekers("seekers.dat", seekers, &readNumSeekers);
  readEmployers("employers.dat", employers, &readNumEmployers);
  FILE *file = fopen("numbers.txt", "r");
  fscanf(file, "%d %d", &numSeeker, &numEmployer);
  fclose(file);
  //   menu
  while (1) {
    printf("\t\t---MAIN MENU---\n");
    printf("\n1. Create New Account \n2. Login \n3. Exit\n\nEnter your "
           "choice: ");
    scanf("%d", &choice);
    if (choice == 3) {
      break;
    }
    switch (choice) {
    case 1: {
      int ch;
      do {
        printf("\n\t\t---ACCOUNT CREATION---\n");
        printf("\n1. Create New Seeker  \n2. Create New Employer \n3. Exit "
               "\nEnter your choice: ");
        scanf("%d", &ch);
        switch (ch) {
        case 1: {
          printf("\n\t\t--Job Seeker Creation--\n");
          createJobseeker(seekers, numSeeker);
          numSeeker++;
          break;
        }
        case 2: {
          printf("\n\t\t--Employer Creation--\n");
          createEmployer(employers, numEmployer);
          numEmployer++;
          break;
        }
        default: {
          printf("\n");
          break;
        }
        }
      } while (ch != 3);
      break;
    }
    case 2: {
      int ch;
      do {
        printf("\n\t\t---LOGIN---\n");
        printf("\n1. Job Seeker Login \n2. Employer Login \n3. Exit "
               "\nEnter your choice: ");
        scanf("%d", &ch);
        switch (ch) {
        case 1: {

          printf("Enter your Name without spaces: ");
          scanf(" %s", username);
          printf("Enter your password: ");
          scanf(" %s", password);

          if (validateSeekerLogin(username, password)) {
            printf("Login successful.\n");
            int pos;
            for (int i = 0; i < numSeeker + 1; i++) {
              char *tempStr = removeSpaces(seekers[i].name);
              if (strcmp(tempStr, username) == 0) {
                pos = i;
                free(tempStr);
                break;
              }
            }

            printf("\n\t\t--Your Profile--\n");
            displaySeeker(seekers, pos);
            printf("\n\n\t\tMatching Jobs suiting you:\n\n");
            float seekerPercentages[numEmployer][2];
            for (int i = 0; i < numEmployer; i++) {
              seekerPercentages[i][1] =
                  seekerMatchPercentage(seekers[pos], employers[i]);
              seekerPercentages[i][0] = employers[i].ID;
            }
            sortDescending(seekerPercentages, numEmployer);

            // top 3 results
            for (int i = 0; i < 3; i++) {
              printf("%-20s\t%3.2f\n",
                     employers[(int)seekerPercentages[i][0] - 1].name,
                     seekerPercentages[i][1]);
            }
            printf("\n\n");
          } else {
            printf("Invalid username or password.\n");
          }
          break;
        }
        case 2: {
          printf("Enter your Company Name without spaces: ");
          scanf(" %s", username);
          printf("Enter your password: ");
          scanf(" %s", password);

          if (validateEmployerLogin(username, password)) {
            printf("Login successful.\n");
            int pos;

            for (int i = 0; i < numEmployer + 1; i++) {
              char *tempStr = removeSpaces(employers[i].name);
              if (strcmp(tempStr, username) == 0) {
                pos = i;
                free(tempStr);
                break;
              }
            }
            printf("\n\t\t--Your Profile--\n");
            displayEmployer(employers, pos);
            printf("\n\nMatching Candidates suiting you:\n\n");
            float employerPercentages[numSeeker][2];
            for (int i = 0; i < numSeeker; i++) {
              employerPercentages[i][1] =
                  employerMatchPercentage(employers[pos], seekers[i]);
              employerPercentages[i][0] = seekers[i].ID;
            }
            sortDescending(employerPercentages, numSeeker + 1);

            printf("\n\n");
            // top 3 results
            for (int i = 0; i < 3; i++) {
              printf("%-20s\t%3.2f\n",
                     seekers[(int)employerPercentages[i][0] - 1].name,
                     employerPercentages[i][1]);
            }
            printf("\n");
          } else {
            printf("Invalid username or password.\n");
          }
        }
        default: {
          printf("\n");
        }
        }
      } while (ch != 3);
      break;
    }
    default:
      printf("\nInvalid choice ");
      break;
    }
  }
  storeSeekers("seekers.dat", seekers, numSeeker);
  storeEmployers("employers.dat", employers, numEmployer);
  FILE *file1 = fopen("numbers.txt", "w");
  fprintf(file1, "%d %d", numSeeker, numEmployer);
  fclose(file1);
  return 0;
}
