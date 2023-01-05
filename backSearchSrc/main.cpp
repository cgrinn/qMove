#include <string>
#include <filesystem>
#include <iostream>

//To be called from terminal
//Used for more easily moving backward through the file system
//Takes an argument and looks for it as part of the current path. If it finds it, couts the path up 
//Else returns an error

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
    if(argv[1] == NULL)
    {
        return EXIT_FAILURE;
    }
    std::string toDirStr(argv[1]);

    fs::path curPath = fs::current_path();
    
    int count = 0;
    bool sel = false;
    std::string retStr;
    //loops through the complete path, building retStr as it goes, breaks if a part of the path matches the argument
    for(const auto& part: curPath)
    {
        retStr += part;
        if(count !=0)
        {
            retStr += "/";
        }
        if(part == toDirStr){
            sel = true;
            break;
        }
        count++;

    }
    //if there's been no match, error and exit
    if(!sel)
    {
        std::cerr << "Couldn't find that directory" << std::endl;
        return EXIT_FAILURE;
    }
    //cout the path to change to
    std::cout << retStr;

    return EXIT_SUCCESS;
}