#ifndef _COMMANDS_H_
#define _COMMANDS_H_

// Registration commands
const char* PASS_CMD;
const char* NICK_CMD;
const char* USER_CMD;
const char* QUIT_CMD;

// Error commands
const char* NICK_IN_USE;
const char* NICK_INVALID;
const char* NICK_NULL;
const char* PARAMETERS_MISSING;


// Misc
const char* PRINT_CMD;



// //Commands from client
// const char* CONNECT_CMD = "+CONNECT";
// const char* QUIT_CMD = "+QUIT";
const char* PRIVMSG_CMD;
const char* NOTICE_CMD;
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
