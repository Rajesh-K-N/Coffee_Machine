#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h> // Replace unistd.h with windows.h for Windows compatibility

// Coffee machine states
typedef enum {
    IDLE,
    HEATING,
    BREWING,
    DISPENSING,
    CLEANING,
    MAINTENANCE
} MachineState;

// Coffee types
typedef enum {
    ESPRESSO,
    AMERICANO,
    LATTE,
    CAPPUCCINO,
    MOCHA
} CoffeeType;

// Coffee machine structure
typedef struct {
    MachineState state;
    int waterLevel;
    int beanLevel;
    int milkLevel;
    bool powered;
    int temperature;
    int coffeesMade;
    int maxWater;
    int maxBeans;
    int maxMilk;
} CoffeeMachine;

// Function prototypes
void initializeMachine(CoffeeMachine *machine);
void displayStatus(CoffeeMachine *machine);
void powerToggle(CoffeeMachine *machine);
void fillWater(CoffeeMachine *machine);
void fillBeans(CoffeeMachine *machine);
void fillMilk(CoffeeMachine *machine);
void brewCoffee(CoffeeMachine *machine, CoffeeType type);
void cleanMachine(CoffeeMachine *machine);
void runMaintenance(CoffeeMachine *machine);
const char* getStateName(MachineState state);
const char* getCoffeeName(CoffeeType type);
void displayMenu();

int main() {
    CoffeeMachine machine;
    initializeMachine(&machine);
    
    int choice;
    int coffeeChoice;
    
    printf("Digital Coffee Machine Simulation\n");
    printf("=================================\n");
    
    while (true) {
        displayStatus(&machine);
        displayMenu();
        
        printf("Enter your choice (0-8): ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 0:
                printf("Thank you for using the Digital Coffee Machine!\n");
                return 0;
            case 1:
                powerToggle(&machine);
                break;
            case 2:
                fillWater(&machine);
                break;
            case 3:
                fillBeans(&machine);
                break;
            case 4:
                fillMilk(&machine);
                break;
            case 5:
                if (!machine.powered) {
                    printf("Please turn on the machine first.\n");
                    break;
                }
                printf("Select coffee type:\n");
                printf("1. Espresso\n");
                printf("2. Americano\n");
                printf("3. Latte\n");
                printf("4. Cappuccino\n");
                printf("5. Mocha\n");
                printf("Enter your choice (1-5): ");
                scanf("%d", &coffeeChoice);
                
                if (coffeeChoice >= 1 && coffeeChoice <= 5) {
                    brewCoffee(&machine, coffeeChoice - 1);
                } else {
                    printf("Invalid coffee selection.\n");
                }
                break;
            case 6:
                cleanMachine(&machine);
                break;
            case 7:
                runMaintenance(&machine);
                break;
            case 8:
                printf("Coffee Machine Manual:\n");
                printf("- Turn on the machine before brewing\n");
                printf("- Ensure water, beans, and milk are filled as needed\n");
                printf("- Clean the machine after every 5 coffees\n");
                printf("- Run maintenance when indicated\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        
        // Small delay to make the simulation feel more realistic
        Sleep(1000); // Windows uses Sleep() with milliseconds instead of sleep()
    }
    
    return 0;
}

void initializeMachine(CoffeeMachine *machine) {
    machine->state = IDLE;
    machine->waterLevel = 0;
    machine->beanLevel = 0;
    machine->milkLevel = 0;
    machine->powered = false;
    machine->temperature = 20; // Room temperature
    machine->coffeesMade = 0;
    machine->maxWater = 1000; // ml
    machine->maxBeans = 500;  // g
    machine->maxMilk = 500;   // ml
}

void displayStatus(CoffeeMachine *machine) {
    printf("\n--- Coffee Machine Status ---\n");
    printf("Power: %s\n", machine->powered ? "ON" : "OFF");
    printf("State: %s\n", getStateName(machine->state));
    printf("Water Level: %d/%d ml\n", machine->waterLevel, machine->maxWater);
    printf("Bean Level: %d/%d g\n", machine->beanLevel, machine->maxBeans);
    printf("Milk Level: %d/%d ml\n", machine->milkLevel, machine->maxMilk);
    printf("Temperature: %d°C\n", machine->temperature);
    printf("Coffees Made Since Last Cleaning: %d\n", machine->coffeesMade);
    printf("----------------------------\n\n");
}

void powerToggle(CoffeeMachine *machine) {
    if (machine->powered) {
        machine->powered = false;
        machine->state = IDLE;
        machine->temperature = 20; // Return to room temperature
        printf("Powering down...\n");
    } else {
        machine->powered = true;
        machine->state = HEATING;
        printf("Powering up...\n");
        
        // Simulate heating
        printf("Heating up");
        for (int i = 0; i < 3; i++) {
            printf(".");
            fflush(stdout);
            Sleep(1000); // Windows uses Sleep() with milliseconds
            machine->temperature += 20;
        }
        printf("\n");
        
        machine->temperature = 90; // Operating temperature
        machine->state = IDLE;
        printf("Coffee machine ready!\n");
    }
}

void fillWater(CoffeeMachine *machine) {
    if (machine->waterLevel == machine->maxWater) {
        printf("Water tank is already full!\n");
        return;
    }
    
    machine->waterLevel = machine->maxWater;
    printf("Water tank filled to maximum capacity (%d ml).\n", machine->maxWater);
}

void fillBeans(CoffeeMachine *machine) {
    if (machine->beanLevel == machine->maxBeans) {
        printf("Bean container is already full!\n");
        return;
    }
    
    machine->beanLevel = machine->maxBeans;
    printf("Bean container filled to maximum capacity (%d g).\n", machine->maxBeans);
}

void fillMilk(CoffeeMachine *machine) {
    if (machine->milkLevel == machine->maxMilk) {
        printf("Milk container is already full!\n");
        return;
    }
    
    machine->milkLevel = machine->maxMilk;
    printf("Milk container filled to maximum capacity (%d ml).\n", machine->maxMilk);
}

void brewCoffee(CoffeeMachine *machine, CoffeeType type) {
    if (machine->state != IDLE) {
        printf("Machine is busy. Current state: %s\n", getStateName(machine->state));
        return;
    }
    
    int waterNeeded = 0;
    int beansNeeded = 0;
    int milkNeeded = 0;
    
    // Set requirements based on coffee type
    switch (type) {
        case ESPRESSO:
            waterNeeded = 30;
            beansNeeded = 9;
            milkNeeded = 0;
            break;
        case AMERICANO:
            waterNeeded = 120;
            beansNeeded = 9;
            milkNeeded = 0;
            break;
        case LATTE:
            waterNeeded = 30;
            beansNeeded = 9;
            milkNeeded = 150;
            break;
        case CAPPUCCINO:
            waterNeeded = 30;
            beansNeeded = 9;
            milkNeeded = 120;
            break;
        case MOCHA:
            waterNeeded = 30;
            beansNeeded = 11;
            milkNeeded = 100;
            break;
    }
    
    // Check resources
    if (machine->waterLevel < waterNeeded) {
        printf("Not enough water! Please refill.\n");
        return;
    }
    
    if (machine->beanLevel < beansNeeded) {
        printf("Not enough coffee beans! Please refill.\n");
        return;
    }
    
    if (machine->milkLevel < milkNeeded) {
        printf("Not enough milk! Please refill.\n");
        return;
    }
    
    // Brewing process
    printf("Brewing %s...\n", getCoffeeName(type));
    
    machine->state = BREWING;
    printf("Grinding beans");
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        Sleep(1000); // Windows uses Sleep() with milliseconds
    }
    printf("\n");
    
    machine->state = DISPENSING;
    printf("Dispensing coffee");
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        Sleep(1000); // Windows uses Sleep() with milliseconds
    }
    printf("\n");
    
    if (milkNeeded > 0) {
        printf("Adding milk");
        for (int i = 0; i < 2; i++) {
            printf(".");
            fflush(stdout);
            Sleep(1000); // Windows uses Sleep() with milliseconds
        }
        printf("\n");
    }
    
    // Consume resources
    machine->waterLevel -= waterNeeded;
    machine->beanLevel -= beansNeeded;
    machine->milkLevel -= milkNeeded;
    machine->coffeesMade++;
    
    machine->state = IDLE;
    printf("Your %s is ready! Enjoy!\n", getCoffeeName(type));
    
    // Suggest cleaning if needed
    if (machine->coffeesMade >= 5) {
        printf("NOTICE: Machine should be cleaned after %d coffees.\n", machine->coffeesMade);
    }
}

void cleanMachine(CoffeeMachine *machine) {
    if (!machine->powered) {
        printf("Please turn on the machine before cleaning.\n");
        return;
    }
    
    if (machine->state != IDLE) {
        printf("Cannot clean while machine is %s.\n", getStateName(machine->state));
        return;
    }
    
    machine->state = CLEANING;
    printf("Cleaning cycle started");
    for (int i = 0; i < 5; i++) {
        printf(".");
        fflush(stdout);
        Sleep(1000); // Windows uses Sleep() with milliseconds
    }
    printf("\n");
    
    machine->coffeesMade = 0;
    machine->state = IDLE;
    printf("Cleaning complete!\n");
}

void runMaintenance(CoffeeMachine *machine) {
    if (machine->powered) {
        printf("Please turn off the machine before maintenance.\n");
        return;
    }
    
    machine->state = MAINTENANCE;
    printf("Running maintenance checks");
    for (int i = 0; i < 4; i++) {
        printf(".");
        fflush(stdout);
        Sleep(1000); // Windows uses Sleep() with milliseconds
    }
    printf("\n");
    
    // Simulate descaling and part checking
    printf("Descaling system... OK\n");
    Sleep(1000); // Windows uses Sleep() with milliseconds
    printf("Checking heating element... OK\n");
    Sleep(1000); // Windows uses Sleep() with milliseconds
    printf("Checking grinder... OK\n");
    Sleep(1000); // Windows uses Sleep() with milliseconds
    printf("Checking pump pressure... OK\n");
    
    machine->state = IDLE;
    printf("Maintenance complete! The machine is ready for use.\n");
}

const char* getStateName(MachineState state) {
    switch (state) {
        case IDLE: return "IDLE";
        case HEATING: return "HEATING";
        case BREWING: return "BREWING";
        case DISPENSING: return "DISPENSING";
        case CLEANING: return "CLEANING";
        case MAINTENANCE: return "MAINTENANCE";
        default: return "UNKNOWN";
    }
}

const char* getCoffeeName(CoffeeType type) {
    switch (type) {
        case ESPRESSO: return "Espresso";
        case AMERICANO: return "Americano";
        case LATTE: return "Latte";
        case CAPPUCCINO: return "Cappuccino";
        case MOCHA: return "Mocha";
        default: return "Unknown Coffee";
    }
}

void displayMenu() {
    printf("--- Menu ---\n");
    printf("1. Power On/Off\n");
    printf("2. Fill Water\n");
    printf("3. Fill Beans\n");
    printf("4. Fill Milk\n");
    printf("5. Brew Coffee\n");
    printf("6. Clean Machine\n");
    printf("7. Run Maintenance\n");
    printf("8. Show Manual\n");
    printf("0. Exit\n");
}