#ifndef _COMMANDS_H_
#define _COMMANDS_H_

// Registration commands
const char* PASS_CMD;
const char* NICK_CMD;
const char* USER_CMD;
const char* REG_QUIT_CMD;

// Error commands
const char* NICK_IN_USE;
const char* NICK_INVALID;
const char* NICK_NULL;
const char* PARAMETERS_MISSING;


// //Commands from client
const char* CONNECT_CMD;
const char* QUIT_CMD;
const char* PRIVMSG_CMD;
const char* NOTICE_CMD;
const char* LIST_CMD;
const char* LIST_ALL_CMD;
const char* ROOMS_CMD;
const char* HELP_CMD;
const char* JOIN_CMD;

// //Commands to client
const char* PRINT_CMD;
const char* PROMPT_CMD;
const char* FAIL_CMD;
const char* JOIN_SUCCESS_CMD;

#endif
