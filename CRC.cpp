
#include<iostream>
#include<string>
using namespace std;

// Function to perform XOR Division
string xordiv(string data, string generator)
{
    string temp = data;

    for(int i = 0; i <= (int)data.size() - (int)generator.size(); i++)
    {
        if(temp[i] == '1')
        {
            for(int j = 0; j < (int)generator.size(); j++)
            {
                if(temp[i+j] == generator[j])
                    temp[i+j] = '0';
                else
                    temp[i+j] = '1';
            }
        }
    }

    return temp.substr(data.size() - generator.size() + 1);
}

// Function to Convert Word into Binary
string wordtobinary(string data)
{
    string res = "";

    for(int i = 0; i < (int)data.size(); i++)
    {
        unsigned char c = data[i];

        for(int j = 7; j >= 0; j--)
        {
            res += (c & (1 << j)) ? '1' : '0';
        }
    }

    return res;
}

// Main Function
int main()
{
    string data, crc, generator;

    cout << "Enter data: ";
    cin >> data;

    cout << "Enter CRC type (BASIC / CCITT / 12 / 16): ";
    cin >> crc;

    if(crc == "BASIC")
        generator = "10011";
    else if(crc == "CCITT")
        generator = "10001000000100001";
    else if(crc == "12")
        generator = "1100000001111";
    else if(crc == "16")
        generator = "11000000000000101";
    else
    {
        cout << "Invalid CRC type!" << endl;
        return 0;
    }

    string binary = wordtobinary(data);

    cout << "Binary Data: " << binary << endl;

    string padded = binary + string(generator.size() - 1, '0');

    string remainder = xordiv(padded, generator);

    cout << "CRC Remainder: " << remainder << endl;

    cout << "Transmitted Data: " << binary + remainder << endl;

    return 0;
}

