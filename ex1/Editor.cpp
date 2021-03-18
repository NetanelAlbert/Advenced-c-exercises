#include <iostream>
#include "Editor.h"
#include <regex>

using namespace std;

void Editor::loop(){
    while (true){
        string command;
        getline(cin, command);
        regex numReg("([0-9]+)");
        regex addReg("([+-][0-9]+)");
        regex replaceReg("(s/.*/.*/)");
        regex findReg("/.*/");
        
        if(regex_match(command, addReg)){
            // +n
        } else if (regex_match(command, numReg)){
            // jump to
        } else if (command == "$"){

        } else if (command == "a"){

        } else if (command == "i"){
          
        } else if (command == "c"){

        } else if (command == "d"){
            
        } else if (command == "j"){
            
        } else if (command == "q"){
            
        } else if (regex_match(command, replaceReg)){
            smatch match;
            regex_search(command.begin(), command.end(), match, replaceReg);
            //??^
        } else if (command == ){
            
        } else if (command == ){
            
        }
    }
    
}