#ifndef _COMMANDS_H_
#define _COMMANDS_H_

// Registration commands
const char* PASS_CMD = "PASS";
const char* NICK_CMD = "NICK";
const char* USER_CMD = "USER";
const char* QUIT_CMD = "QUIT";

// Error commands
const char* NICK_IN_USE = "433";
const char* NICK_INVALID = "432";
const char* NICK_NULL = "431";
const char* PARAMETERS_MISSING = "461";


// Misc
const char* PRINT_CMD = "PRINT";



// //Commands from client
// const char* CONNECT_CMD = "+CONNECT"; 
// const char* QUIT_CMD = "+QUIT"; 
// const char* MSG_CMD = "+MSG"; 
// const char* LIST_CMD = "+LIST"; //list names of ppl in channel
// const char* LIST_ALL_CMD = "+LIST_ALL"; //list names of all ppl on server
// const char* ROOMS_CMD = "+ROOMS";
// const char* HELP_CMD = "+HELP"; 
// const char* JOIN_CMD = "+JOIN"; 

// //Commands to client
// const char* PRINT_CMD = "+PRINT"; 
// const char* SET_PROMPT_CMD = "+PROMPT"; 
// const char* FAIL_CMD = "+FAIL"; 
// const char* JOIN_SUCCESS_CMD = "+JOIN_SUCCESS"; 

#endif
