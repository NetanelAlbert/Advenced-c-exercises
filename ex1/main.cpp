#include "Editor.h"

int main(int argc, char* argv[]){
    Editor* editor;
    switch (argc)
    {
    case 1:
        editor = new Editor;
        break;
    
    case 2:
        editor = new Editor(argv[1]);
        break;
    
    default:
        cerr << "Too many arguments" << endl;
        exit(1);
    }

    try{
        editor->loop();
    }
    catch(char const* s){
        cerr << "error: " << s << '\n';
        exit(1);
    }
    
    return 0;
}