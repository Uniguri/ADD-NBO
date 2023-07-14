#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <netinet/in.h>

uint32_t ReadFileAndGetValue(const char* file_name)
{
    FILE* fp = fopen(file_name, "r");
    if(!fp)
    {
        printf("%s : does not exist.\n", file_name);
        exit(-1);
    }
    uint32_t val = 0;
    fread(reinterpret_cast<void*>(&val), 4, 1, fp);
    fclose(fp);

    return ntohl(val); 
}

void PrintDecAndHex(uint32_t val) 
{
    printf("%d(%p)", val, reinterpret_cast<void*>(val));
}

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("syntax : add-nbo <file1> <file2>\n");
        printf("sample : add-nbo a.bin b.bin\n");
        exit(0);
    }

    uint32_t val1 = ReadFileAndGetValue(argv[1]),
             val2 = ReadFileAndGetValue(argv[2]);
    PrintDecAndHex(val1);
    printf(" + ");
    PrintDecAndHex(val2);
    printf(" = ");
    PrintDecAndHex(val1+val2);
    printf("\n");
    return 0;
}
