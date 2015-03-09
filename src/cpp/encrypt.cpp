#include <iostream>

std::string encryptDecrypt(std::string toEncrypt) {
    char key[3] = {'K', 'C', 'Q'}; //Any chars will work
    std::string output = toEncrypt;
    
    for (int i = 0; i < toEncrypt.size(); i++)
        output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];
    
    return output;
}


int main()
{
    std::string toencry = "kk1234";
    std::string encry = encryptDecrypt(toencry);
    std::cout << encry << std::endl;

    std::string decry = encryptDecrypt(encry);
    std::cout << decry << std::endl;

    return 0;
}
