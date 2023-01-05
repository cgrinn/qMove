#include <string>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

bool matchDirectory(std::string* toMatch, int curLevel, int maxDepth, fs::path curPath, std::string* finalPath);

int main(int argc, char* argv[])
{
    if(argv[1] == NULL)
    {
        return EXIT_FAILURE;
    }
    std::string curPath = fs::current_path();
    std::string argString(argv[1]);


    int depth = 6;
    if(argv[2] != NULL)
    {
        depth = atoi(argv[2]);
        if(depth  < 0)
        {
            std::cerr << "Search depth must be be positive." << std::endl;
            return EXIT_FAILURE;
        }
    }

    std::string resString;
    if(!matchDirectory(&argString, 0, depth, fs::current_path(), &resString))
    {
        std::cerr << "Couldn't find that directory." << std::endl;
        return EXIT_FAILURE;
    }

    //Cout result for use in shell
    std::cout << resString;

    return EXIT_SUCCESS;
}

//Tries to find a directory matching toMatch, sstating in the current directory and searching to maxDepth 
//Returns true on success and stores the path in finalPath
bool matchDirectory(std::string* toMatch, int curLevel, int maxDepth, fs::path curPath, std::string* finalPath)
{
    //ignore directory if error with access
 
    //iterate through all directories in the current directory seeking a matching file name
     for(auto entry: fs::directory_iterator(curPath))
     {
        try
        {
            if(fs::is_directory(entry.status()))
            {
                if(*toMatch == entry.path().filename().string())
                {
                    *finalPath = std::string(entry.path());
                    return true;
                }
            }
        }
        catch(std::exception e)
        {
            //ignore and continue
            //file permission errors flood to much to give usefull information
        }
     }

    //if the currentLevel is to high, exit before call self again
    if(curLevel >= maxDepth)
    {
        return false;
    }
    //ignore directory if error with access

    //iterate through all directories in current directory and call this function on them
    for(auto entry: fs::directory_iterator(curPath))
    {
        try
        {
            if(fs::is_directory(entry.status()))
            {
                if(matchDirectory(toMatch, curLevel+1, maxDepth, entry, finalPath))
                {
                    return true;
                }
            }
        }
        catch(std::exception e)
        {
            //Same error as above
        }
    }

    return false;
}