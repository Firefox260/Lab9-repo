#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
};

// Fill out this structure
struct HashType
{
    struct RecordType data;
    struct HashType* next;
};

int hash(int x)
{
    return (x % 23);
}

// Parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType* pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*)malloc(sizeof(struct RecordType) * dataSz);
        // Implement parse data block
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }

        fclose(inFile);
    }

    return dataSz;
}

// Initializes the hash table
void initializeHash(struct HashType* pHashArray[], int hashSz)
{
    for (int i = 0; i < hashSz; ++i)
    {
        pHashArray[i] = NULL;
    }
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// Inserts a record into the hash table
void insertRecord(struct HashType* pHashArray[], int hashSz, struct RecordType record)
{
    int index = hash(record.id);
    struct HashType* newNode = (struct HashType*)malloc(sizeof(struct HashType));
    if (newNode == NULL)
    {
        printf("Cannot allocate memory for hash node\n");
        exit(-1);
    }
    newNode->data = record;
    newNode->next = pHashArray[index];
    pHashArray[index] = newNode;
}

// Displays records stored in the hash table
void displayRecordsInHash(struct HashType* pHashArray[], int hashSz)
{
    for (int i = 0; i < hashSz; ++i)
    {
        struct HashType* curr = pHashArray[i];
        printf("Index %d -> ", i);
        while (curr != NULL)
        {
            printf("%d %c %d -> ", curr->data.id, curr->data.name, curr->data.order);
            curr = curr->next;
        }
        printf("\n");
    }
}

int main(void)
{
    struct RecordType* pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);
    // Initialize the hash table
    int hashSz = 23; // Adjust the size as needed
    struct HashType* pHashArray[hashSz];
    initializeHash(pHashArray, hashSz);

    // Insert records into the hash table
    for (int i = 0; i < 23; ++i)
    {

        insertRecord(pHashArray, hashSz, pRecords[i]);

    }

    // Display records stored in the hash table
    displayRecordsInHash(pHashArray, hashSz);

    // // Free allocated memory
    // for (int i = 0; i < recordSz; ++i)
    // {
    //     free(pRecords[i]);
    // }
    // free(pRecords);

    return 0;
}
