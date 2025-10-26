//ALI MUHI IBRAHIM ALOBADI $$
#include <stdio.h>
#include <string.h>

#define MAX_CANDIDATES 11
// Maximum number of candidates allowed

// Structure to store candidate information
typedef struct {
    char name[50];
    int voteCount;
    char symbol;
} Candidate;

// Global array to hold all candidates
Candidate candidates[MAX_CANDIDATES];

// Number of candidates participating
int totalCandidates = 0;

// Set of available voting symbols
char availableSymbols[10] = { '!', '@', '#', '$', '%', '^', '&', '*', '~', '+' };

// To mark which symbols have already been used
int isSymbolUsed[10];

// Function declarations
void registerCandidate(int index);
void showCandidates();
void castVote(int voterNumber);
void announceResults();

int main() {
    // Initialize symbol usage tracking
    for (int i = 0; i < 10; i++) {
        isSymbolUsed[i] = 0;
    }

    // Get number of candidates
    printf("Enter number of candidates (max 10): ");
    scanf("%d", &totalCandidates);

    if (totalCandidates > 10) {
        printf("Error: Maximum 10 candidates allowed. Program terminated.\n");
        return 0;
    }

    // Register each candidate
    for (int i = 0; i < totalCandidates; i++) {
        registerCandidate(i);
    }

    // Get number of voters
    int totalVoters;
    printf("Enter number of voters: ");
    scanf("%d", &totalVoters);

    // Voting phase
    for (int i = 0; i < totalVoters; i++) {
        castVote(i);
    }

    // Display final results
    announceResults();

    return 0;
}

// Function to input candidate details
void registerCandidate(int index) {
    printf("\nAvailable Symbols:\n");
    for (int i = 0; i < 10; i++) {
        if (!isSymbolUsed[i]) {
            printf("%d. %c\n", i + 1, availableSymbols[i]);
        }
    }

    int choice;
    printf("Choose a symbol number for candidate %d: ", index + 1);
    scanf("%d", &choice);

    if (choice <= 0 || choice > 10 || isSymbolUsed[choice - 1]) {
        printf("Invalid symbol choice! Try again.\n");
        registerCandidate(index);  // Recursive retry
        return;
    }

    isSymbolUsed[choice - 1] = 1;
    candidates[index].symbol = availableSymbols[choice - 1];
    candidates[index].voteCount = 0;

    printf("Enter candidate %d name: ", index + 1);
    scanf("%s", candidates[index].name);
}

// Function to display all candidates and their symbols
void showCandidates() {
    printf("\nCandidates List:\n");
    for (int i = 0; i < totalCandidates; i++) {
        printf("%d. %-15s Symbol: %c\n", i + 1, candidates[i].name, candidates[i].symbol);
    }
    printf("\n");
}

// Function for a single voter to cast their vote
void castVote(int voterNumber) {
    showCandidates();

    int voteChoice;
    printf("Voter %d, enter your choice (1 - %d): ", voterNumber + 1, totalCandidates);
    scanf("%d", &voteChoice);

    if (voteChoice >= 1 && voteChoice <= totalCandidates) {
        candidates[voteChoice - 1].voteCount++;
    } else {
        printf("Invalid input! Please vote again.\n");
        castVote(voterNumber);
    }
}

// Function to determine and print election results
void announceResults() {
    int highestVotes = 0;
    int winnerIndex = -1;
    int tieCount = 0;

    for (int i = 0; i < totalCandidates; i++) {
        if (candidates[i].voteCount > highestVotes) {
            highestVotes = candidates[i].voteCount;
            winnerIndex = i;
        }
    }

    // Check for tie
    for (int i = 0; i < totalCandidates; i++) {
        if (candidates[i].voteCount == highestVotes) {
            tieCount++;
        }
    }

    printf("\n========== FINAL RESULTS ==========\n");
    if (tieCount > 1) {
        printf("It's a tie! No clear winner.\n");
    } else if (winnerIndex != -1) {
        printf("Winner: %s\nSymbol: %c\nTotal Votes: %d\n",
               candidates[winnerIndex].name,
               candidates[winnerIndex].symbol,
               highestVotes);
    } else {
        printf("No votes were cast.\n");
    }
    printf("===================================\n");
}
