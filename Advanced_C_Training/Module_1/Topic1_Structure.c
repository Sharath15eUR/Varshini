#include <stdio.h>
#include <string.h>

#define MAX_DAYS 7
#define MAX_TASKS 3
#define MAX_TASK_LENGTH 100

// Structure to represent a day with dayName and tasks
typedef struct {
    char dayName[10];
    char tasks[MAX_TASKS][MAX_TASK_LENGTH];
    int taskCount;
} Day;

int main() {
    // Array of type Day(structure) for 7 days in the week.
    // This is used to hold the values of tasks for each day separetely with task count.
    Day week[MAX_DAYS] = {
        {"Monday", {}, 0},
        {"Tuesday", {}, 0},
        {"Wednesday", {}, 0},
        {"Thursday", {}, 0},
        {"Friday", {}, 0},
        {"Saturday", {}, 0},
        {"Sunday", {}, 0}
    };


    // Getting input from the user to perform the operation
    int choice;
    do {
        printf("\n===== Weekly Task Manager =====\n");
        printf("1. Add tasks to a day\n");
        printf("2. Display all tasks\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

// Selecting the option
        // Adding the tasks if choice 1 is selected.
	// Inserting the tasks in the Weekly Task Manager.
        if (choice == 1) {
            int dayIndex;
            printf("Select a day (0=Mon, 1=Tue, ..., 6=Sun): ");
            scanf("%d", &dayIndex);
            getchar(); 

	    // Checking if dayIndex is in the limit if not alerting the user.
            if (dayIndex < 0 || dayIndex >= MAX_DAYS) {
                printf("Invalid day index!\n");
                continue;
            }

            Day *d = &week[dayIndex];
            printf("You selected %s. You can add up to %d tasks.\n", d->dayName, MAX_TASKS - d->taskCount);

	    // Getting tasks from the user.
            while (d->taskCount < MAX_TASKS) {
                printf("Enter task %d (or type 'done' to stop): ", d->taskCount + 1);
                char input[MAX_TASK_LENGTH];
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0; // remove newline

                if (strcmp(input, "done") == 0)
                    break;

                strcpy(d->tasks[d->taskCount], input);
                d->taskCount++;
            }

        // Displaying the tasks
        } else if (choice == 2) {
            printf("\n===== Weekly Tasks =====\n");
            for (int i = 0; i < MAX_DAYS; i++) {
                printf("%s:\n", week[i].dayName);
                if (week[i].taskCount == 0) {
                    printf("  No tasks\n");
                } else {
                    for (int j = 0; j < week[i].taskCount; j++) {
                        printf("  - %s\n", week[i].tasks[j]);
                    }
                }
            }
        }

    // Exit
    } while (choice != 3);

    printf("Exit!\n");
    return 0;
}
