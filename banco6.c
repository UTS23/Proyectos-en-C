#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 10

struct BankAccount {
    char name[50];
    double balance;
};

void deposit(struct BankAccount *account, double amount) {
    account->balance += amount;
    printf("Depósito exitoso. Saldo actual: %.2f\n", account->balance);
}

void withdraw(struct BankAccount *account, double amount) {
    if (amount > account->balance) {
        printf("Fondos insuficientes\n");
    } else {
        account->balance -= amount;
        printf("Retiro exitoso. Saldo actual: %.2f\n", account->balance);
    }
}

void checkBalance(struct BankAccount *account) {
    printf("Saldo actual: %.2f\n", account->balance);
}

void saveTransaction(struct BankAccount *account, const char *transactionType, double amount) {
    FILE *file = fopen("accounts.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %.2f %s\n", account->name, amount, transactionType);
        fclose(file);
    } else {
        printf("Error al guardar la transacción\n");
    }
}

void loadAccount(struct BankAccount *accounts, int *numAccounts) {
    FILE *file = fopen("accounts.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%s %lf", accounts[*numAccounts].name, &accounts[*numAccounts].balance) != EOF) {
            (*numAccounts)++;
            if (*numAccounts >= MAX_ACCOUNTS) {
                break;
            }
        }
        fclose(file);
    }
}

void printReceipt(const char *name, double amount, const char *transactionType) {
    printf("\nRecibo:\n");
    printf("Nombre: %s\n", name);
    printf("Tipo de transacción: %s\n", transactionType);
    printf("Monto: %.2f\n", amount);
}

int main() {
    struct BankAccount accounts[MAX_ACCOUNTS];
    int numAccounts = 0;

    // Cargar cuentas existentes
    loadAccount(accounts, &numAccounts);

    int choice;
    double amount;
    char currentAccount[50];

    do {
        printf("\n1. Seleccionar cuenta\n2. Consultar saldo\n3. Depositar\n4. Retirar\n5. Imprimir recibo\n6. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Ingrese su nombre de cuenta: ");
                scanf("%s", currentAccount);
                // Buscar la cuenta seleccionada
                int accountIndex;
                for (accountIndex = 0; accountIndex < numAccounts; accountIndex++) {
                    if (strcmp(accounts[accountIndex].name, currentAccount) == 0) {
                        break;
                    }
                }
                // Si la cuenta no existe, crear una nueva
                if (accountIndex == numAccounts && numAccounts < MAX_ACCOUNTS) {
                    strcpy(accounts[numAccounts].name, currentAccount);
                    accounts[numAccounts].balance = 0.0;
                    numAccounts++;
                }
                break;
            case 2:
                checkBalance(&accounts[accountIndex]);
                break;
            case 3:
                printf("Ingrese la cantidad a depositar: ");
                scanf("%lf", &amount);
                deposit(&accounts[accountIndex], amount);
                saveTransaction(&accounts[accountIndex], "Depósito", amount);
                printReceipt(accounts[accountIndex].name, amount, "Depósito");
                break;
            case 4:
                printf("Ingrese la cantidad a retirar: ");
                scanf("%lf", &amount);
                withdraw(&accounts[accountIndex], amount);
                saveTransaction(&accounts[accountIndex], "Retiro", amount);
                printReceipt(accounts[accountIndex].name, amount, "Retiro");
                break;
            case 5:
                printf("Imprimiendo recibo...\n");
                // Puedes implementar esta función según tus necesidades
                break;
            case 6:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no válida\n");
        }
    } while (choice != 6);

    return 0;
}

