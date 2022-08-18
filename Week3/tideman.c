#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void checkCycle(int og_target, int temp_target); // as a sub function in lock pairs
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
            preferences[i][j] = 0;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] where i is the voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Finds whether candidate exists and updates the ranks array
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            // For each rank is the ith candidate
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // For each candidate (int) in ranks array:
    for (int i = 0; i < candidate_count - 1; i++)
    {
        int cand_num = ranks[i];
        // For each less preferred candidate (int) after current candidate:
        for (int j = i + 1; j < candidate_count; j++)
        {
            int inferior_cand_num = ranks[j];
            preferences[cand_num][inferior_cand_num]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // For each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // For each of the next candidates
        for (int j = 0; j < candidate_count; j++)
        {
            if (i == j)
            {
                continue;
            }
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory using Bubble sort
void sort_pairs(void)
{
    bool complete;
    do
    {
        // If goes through entire array yet nothing needed to swap, complete will remain true and so the loop stops
        complete = true;
        // For pair in pairs
        for (int i = 0; i < pair_count - 1; i++)
        {
            pair current_pair = pairs[i];
            pair next_pair = pairs[i + 1];
            // If current pair strength < that of next pair, swap them --> so complete set to false and loop continues
            if (preferences[current_pair.winner][current_pair.loser] < preferences[next_pair.winner][next_pair.loser])
            {
                complete = false;
                pairs[i] = next_pair;
                pairs[i + 1] = current_pair;
            }
        }
    }
    while (!complete);
    return;
}

// Recursion
bool check_cycle(int og_target, int temp_target)
{
    // For every other candidate
    for (int other = 0; other < candidate_count; other++)
    {
        // Skips if both are the same person
        if (temp_target == other)
        {
            continue;
        }
        // If the temp_target is loser to other candidate
        if (locked[other][temp_target])
        {
            // If the other target turns out to be the original target we started with, then we know that there is a cycle
            if (other == og_target)
            {
                // So we return true and: set the locked back to false and skip this pair
                return true;
            }
            // Otherwise, we set the temp_target to the winner of this pair (other) and checkCycle again to check if it is loser to anything
            // This goes on until either a Cycle is found or the top of the hierarchy is found without any cycles
            if (check_cycle(og_target, other))
            {
                return true;
            }
        }
    }
    // If there is no cycle after checking (ie. There is a top of the hierarchy of candidates)
    // Return false meaning there is no cycle
    return false;
}

// Recursion again
int find_winner(int temp_winner)
{
    // For every other candidate
    for (int other = 0; other < candidate_count; other++)
    {
        // Skips if both are the same person
        if (temp_winner == other)
        {
            continue;
        }
        // If the temp_winner is loser to other candidate
        if (locked[other][temp_winner])
        {
            // Set the temp_winner to the winner of this pair (other) and find_winner again to check if it is loser to anything
            temp_winner = other;
            temp_winner = find_winner(temp_winner);
        }

    }
    // After finding the top of the hierarchy, return the final winner
    return temp_winner;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int locked_pairs = 0;
    // For each pair in pairs
    for (int i = 0; i < pair_count; i++)
    {
        // Locks in the pair
        pair current_pair = pairs[i];
        locked[current_pair.winner][current_pair.loser] = true;
        locked_pairs++;

        // Checking if cycle exists
        bool is_Cycle = check_cycle(current_pair.winner, current_pair.winner);
        if (is_Cycle)
        {
            // Remove the current locked in pair and skips to the next pair if cycle exists
            locked[current_pair.winner][current_pair.loser] = false;
            locked_pairs--;
        }
        continue;
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // Finds the candidate at the top of the hierarchy
    int winner = find_winner(1);
    printf("%s\n", candidates[winner]);
    return;
}