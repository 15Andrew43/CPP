#include <iostream>
using namespace std;

void ConvertToBinary(char* array, int start, int end)
{
    if(array[start] == array[end] && array[start] == '0')
    {
        cout<<'0';
        return;
    }

    char binaryInt[1000];
    int length = 0;

    while(start != end || array[start] != '0')
    {
        int carry = 0;
        for(int i = start; i <= end; ++i)
        {
            int currentInt = array[i] - '0';
            array[i] = currentInt/2 + carry*5 + '0';
            carry = currentInt%2;
        }
        if(array[start] == '0' && start != end) start++;
        binaryInt[length] = carry + '0';
        length++;
    }

    for(int i = length - 1; i >= 0; --i)
    {
        cout<<binaryInt[i];
    }
}

void ReplaceWithBinary(char* array)
{
    int startOfInt = -1, endOfInt = -1;
    for(int i = 0; array[i] != '\0'; ++i)
    {
        if(array[i] >= '0' && array[i] <= '9')
        {
            if(startOfInt == -1)
            {
                startOfInt = endOfInt = i;
            }
            else endOfInt++;
        }
        else
        {
            if(startOfInt != -1)
            {
                ConvertToBinary(array, startOfInt, endOfInt); //
                startOfInt = -1;
                endOfInt = -1;
            }
            cout<<array[i];
        }
    }
    if(startOfInt != -1) ConvertToBinary(array, startOfInt, endOfInt);
}

int main()
{
    char array[256];
    cin.getline(array, 256);
    ReplaceWithBinary(array);
}