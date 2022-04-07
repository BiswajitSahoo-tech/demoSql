#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
typedef enum
            {
                META_COMMAND_SUCCESS,
                META_COMMAND_UNRECOGNIZED_COMMAND
            }META_COMMAND_RESULT;

typedef enum
    {
        PREPARE_SUCCESS, 
        PREPARE_UNRECOGNIZED_STATEMENT

    }STATEMENT_PREPARE_RESULT;

typedef enum
    {
        STATEMENT_INSERT, 
        STATEMENT_SELECT

    }STATEMENT_TYPE;

typedef struct{
    STATEMENT_TYPE type;
}Statement;

typedef struct{
    char* buffer;
    size_t buffer_length;
    size_t input_length;
}inputBuffer;
inputBuffer* new_buffer(){
    inputBuffer* new_buf = (inputBuffer*)malloc(sizeof(inputBuffer));
    new_buf->buffer = NULL;
    new_buf->buffer_length = 0;
    new_buf->input_length = 0;
    return new_buf;
}
void read_input(inputBuffer* obj){
    // use getline function, it allocate sufficient mem and store the input from
    //stdin then make the char* to point to that allocated mem. scanf does not
    //have this dynamic allocation.
    //prototype ---  sizet getline(char**,size_t,FILE*)
    size_t n_read = getline(&(obj->buffer),&(obj->buffer_length),stdin);
    if(n_read <=0){
        printf("Could not read data.\n");
        exit(EXIT_SUCCESS);
    }
    obj->input_length = n_read - 1;
    (obj->buffer)[n_read-1] = '\0';
}
void print_propmt(){
    printf("db >");
}
void free_buff(inputBuffer* obj){
    free(obj->buffer);
    free(obj);
    return ;
}


void print_header(){
    printf("~ sqlite3\nSQLite version 3.16.0 2016-11-04 19:09:39\nEnter \".help\" for usage hints.\n");
}
META_COMMAND_RESULT do_meta_command(inputBuffer* buf_obj){ //meta command handler
    if(strcmp(buf_obj->buffer,".exit") == 0){
        free_buff(buf_obj);
        exit(EXIT_SUCCESS);
    }
    else{
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}
STATEMENT_PREPARE_RESULT prepare_statement(inputBuffer* buff_obj,Statement* stmt){ //Compiler
    if(strncmp(buff_obj->buffer,"insert",6) == 0){
        stmt->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    else if(strncmp(buff_obj->buffer,"select",6) == 0){
        stmt->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }
    else{
        return PREPARE_UNRECOGNIZED_STATEMENT;
    }
}
void execute_stmt(Statement* stmt){ //VM
    if(stmt->type = STATEMENT_SELECT){
        printf("This is where we would do an insert.\n");

    }
    else{
        printf("This is where we would do a select.\n");

    }
}
int main(int argc,char* argv[]){
    print_header();
    inputBuffer* buf_obj = new_buffer();

    while(1){
        print_propmt();
        read_input(buf_obj);

        if(buf_obj->buffer[0] == '.'){
            switch (do_meta_command(buf_obj))
            {
            case META_COMMAND_SUCCESS:
                
                continue;
            case META_COMMAND_UNRECOGNIZED_COMMAND:
                printf("Unrecognized command '%s'\n", buf_obj->buffer);
                continue;
            default:
                break;
            }
        }

        Statement stmt;
        switch(prepare_statement(buf_obj,&stmt)){
            
            case PREPARE_SUCCESS:
                break;
            case PREPARE_UNRECOGNIZED_STATEMENT:
                printf("Unrecognized keyword at start of '%s'.\n",
                buf_obj->buffer);
                continue;
            
        }


        execute_stmt(&stmt);
        printf("Executed\n");

    }
    return 0;
}