#pragma once
class Utils{

    public:
        char *read_line();
        char **split_line(char* line);
        int execute(char** args);
};
