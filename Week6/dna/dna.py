import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    # TODO: Read database file into a variable
    try:
        file = open(sys.argv[1], "r")
        reader = csv.DictReader(file)
    except:
        print(f"Couldn't open {sys.argv[1]} file")
        exit(1)
    dna_dict = {}
    suitable_targets = []
    for subsequence in reader.fieldnames[1:]:
        dna_dict[subsequence] = {}
    for person in reader:
        suitable_targets.append(person["name"])
        for subsequence in reader.fieldnames[1:]:
            dna_dict[subsequence][person["name"]] = person[subsequence]

    # TODO: Read DNA sequence file into a variable
    try:
        dnaFile = open(sys.argv[2], "r")
    except:
        print(f"Couldn't open {sys.argv[2]} file")
        exit(1)
    dna = dnaFile.readline()

    # TODO: Find longest match of each STR in DNA sequence
    str_dict = {}
    for str in dna_dict:
        str_dict[str] = longest_match(dna, str)

    # TODO: Check database for matching profiles
    # Dor each target dna subsequence and its number of matches
    for subsequence, matches in str_dict.items():
        # For every person
        for person in dna_dict[subsequence]:
            # If the person's subsequence count is not the same as the target count
            if int(dna_dict[subsequence][person]) != matches:
                # Remove previous target as i
                if person in suitable_targets:
                    suitable_targets.remove(person)
    # Print final target
    if len(suitable_targets) == 0:
        print("No match")
    else:
        print(suitable_targets[0])

    # Close files
    file.close()
    dnaFile.close()
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
