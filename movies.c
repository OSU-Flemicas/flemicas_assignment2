#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//CS 374 Assignment 2
//Flemicas@oregonstate.edu
//10.25.2026

//define the linked list movie struct

typedef struct movieObj movieObj_t;

typedef struct movieObj{
    char *title;
    int year;
    char *languages;
    float rating;
    movieObj_t *nextMovie;
} movieObj_t;


//user menu functions
void movies_by_year(movieObj_t *movies, int year){
  /* this function accepts a movie linked list and a year*/
  /* iterates over the linked list and prints movies that match the year */
  /* if no movies are found, prints a relate message*/
  int count = 0;
  while(movies != NULL){
    if((movies)->year == year){
      count++;
      printf("%s\n",(movies)->title);
    }
    movies = movies->nextMovie;
  }
  if (count == 0){
    printf("No data about movies released in the year %d", year);
  }
  return;
}

void top_rated_each_year(movieObj_t *movies){
  /* this function accepts a movie linked list*/
  /* this function has its own specific linked list struct called year which manages the ratings*/
  /* iterates over the movie linked list and updates the year linked list if its rating is higher*/
  /* if the movie year in that iteration is not found in the year linked list it is added*/
  typedef struct yearObj year;

  typedef struct yearObj{
    int year;
    float rating;
    char *title;
    year *next;
  } year;

  int yearFound = 0;

  year *head = NULL;
  year *head_ptr;
  year *tail = NULL;

  year *newYear = NULL;

  while(movies != NULL){
    newYear = malloc(sizeof(year));
    
    if (head == NULL){
      newYear->year = movies->year;
      newYear->rating = movies->rating;
      newYear->title = strdup(movies->title);
      newYear->next = NULL;
      head = newYear;
      tail = newYear;
      head_ptr = head;
    }
    else{
      while(head_ptr != NULL){
        if(head_ptr->year == movies->year){
          yearFound = 1;
          if(movies->rating > head_ptr->rating){            
            head_ptr->rating = movies->rating;
            head_ptr->title = movies->title;
          }
        }
        head_ptr = head_ptr->next;           
      }
      if(yearFound == 0){
        newYear->year = movies->year;
        newYear->rating = movies->rating;
        newYear->title = strdup(movies->title);
        tail->next = newYear;
        tail = newYear;
      }
      yearFound = 0; 
      head_ptr = head;  
    }
    movies = movies->nextMovie;     
  }
  while(head_ptr != NULL){
    printf("%d %0.1f %s\n", head_ptr->year, head_ptr->rating, head_ptr->title);
    head_ptr = head_ptr->next;
  }
  free(newYear);

  return;
}

void movies_by_lang(movieObj_t *movies, char *lang){
  /* this function accepts a movie linked list and a language*/
  /* iterates over the linked list and prints movies that match the language*/
  /* if no movies are found, prints a relate message*/
  int count = 0;
  while(movies != NULL){
    if(strstr(movies->languages, lang) != NULL){
      count++;
      printf("%d %s\n", movies->year, movies->title);
    }
    movies = movies->nextMovie;
  }
  if (count == 0){
    printf("No data about movies released in %s", lang);
  }
  return;
}

void menu(movieObj_t *movies){
  /* this function is the core user loop*/
  /* it provides 4 user options and processes the correct function/action based on that response*/
  /* if the user enters an incorrect value, the user is informed and prompted again*/
  int input = 0;
  do{
    printf("\n");
    printf("1. Show movies released in the specified year\n");
    printf("2. Show highest rated movie for each year\n");
    printf("3. Show the title and year of release of all movies in a specific language\n");
    printf("4. Exit from the program\n");
    printf("\n");
    printf("Enter a choice from 1 to 4: ");
    scanf("%d", &input);
    switch(input){
      case 1:
        int year;
        printf("Enter the year for which you want to see movies: ");
        scanf("%d", &year);
        movies_by_year(movies, year);
        break;
      case 2:
        top_rated_each_year(movies);
        break;
      case 3:
        char lang[50];
        printf("Enter the language for which you want to see movies: ");
        scanf("%s", lang);
        movies_by_lang(movies, lang);
        break;
      case 4:
        break;
      default:
        printf("You entered an incorrect choice. Try again.\n");
        break;
    }
  } while (input != 4);    
}

void processMovieFile(movieObj_t **head, movieObj_t **tail, char* filePath){
  // This function is borrowed from the course material and has since been adapted to match the assignment reqs
  // Citation: OSU CS 374 - https://canvas.oregonstate.edu/courses/2061291/assignments/10618930  - (C)2026
  // Accessed on 10.24.26
  
  char *currLine = NULL;
  size_t len = 0;
  // Open the specified file for reading only
  FILE *movieFile = fopen(filePath, "r");
  //Read the file line by line
  char *segment;
  movieObj_t *newMovie;
  int count = 0;

  while(getline(&currLine, &len, movieFile) != -1)
  {
    count++;
    newMovie = malloc(sizeof(movieObj_t));
    //get the movie title
    segment = strtok(currLine,",");
    newMovie->title = strdup(segment);

    //get the movie year
    segment = strtok(NULL, ",");
    newMovie->year = atoi(segment);

    //get the movie languages
    segment = strtok(NULL, ",");
    newMovie->languages = strdup(segment);

    //get the movie rating
    segment = strtok(NULL, ",");
    newMovie->rating = atof(segment);

    newMovie->nextMovie = NULL;
    //printf("%s %d %s %f\n", newMovie->title, newMovie->year, newMovie->languages, newMovie->rating);

    if(strcmp(newMovie->title, "Title") != 0){
      //generate a new movie struct object
      if (*head == NULL){
        *head = newMovie;
        *tail = newMovie;
      }else{
          (*tail)->nextMovie = newMovie;
          *tail = newMovie;
      }    
    }
        
  }


  // Free the memory allocated by getline for currLine
  free(currLine);
  // Close the file
  fclose(movieFile);
  printf("Processed file %s and parsed data for %d movies", filePath, count-1);
}

int main(int argc, char * argv[]) {
  //movie struct linked list is initialized in main and passed to the processMovieFile function - I learned the concept of double pointers for this
  //the processMovieFile function processes the data file and creates the linked list
  //the linked list is then passed into the menu function as a reference for read only iteration

  movieObj_t *head = NULL;
  movieObj_t *tail = NULL;

  processMovieFile(&head, &tail, argv[1]);

  menu(head);
  
  return 0;
}
