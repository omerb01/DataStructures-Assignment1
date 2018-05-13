/***************************************************************************/
/*                                                                         */
/* 234218 Data DSs 1, Spring 2018                                     */
/* Homework : Wet 1                                                        */
/*                                                                         */
/***************************************************************************/

/***************************************************************************/
/*                                                                         */
/* File Name : main1.cpp                                                   */
/*                                                                         */
/* Holds the "int main()" function and the parser of the shell's           */
/* command line.                                                           */
/***************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library1.h"
#include <iostream>
using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

/* The command's strings */
typedef enum {
	NONE_CMD = -2,
	COMMENT_CMD = -1,
	INIT_CMD = 0,
	ADDPLAYER_CMD = 1,
	ADDCLAN_CMD = 2,
	JOINCLAN_CMD = 3,
	GETBESTPLAYER_CMD = 4,
	COMPLETECHALLANGE_CMD = 5,
	GETSCOREBOARD_CMD = 6,
	UNITECLANS_CMD = 7,
	QUIT_CMD = 8
} commandType;

static const int numActions = 9;
static const char *commandStr[] = {
		"init",
		"addPlayer",
		"addClan",
		"joinClan",
		"getBestPlayer",
		"completeChallange",
		"getScoreboard",
		"uniteClans",
		"Quit" };

static const char* ReturnValToStr(int val) {
	switch (val) {
	case SUCCESS:
		return "SUCCESS";
	case ALLOCATION_ERROR:
		return "ALLOCATION_ERROR";
	case FAILURE:
		return "FAILURE";
	case INVALID_INPUT:
		return "INVALID_INPUT";
	default:
		return "";
	}
}

/* we assume maximum string size is not longer than 256  */
#define MAX_STRING_INPUT_SIZE (255)
#define MAX_BUFFER_SIZE       (255)

#define StrCmp(Src1,Src2) ( strncmp((Src1),(Src2),strlen(Src1)) == 0 )

typedef enum {
	error_free, error
} errorType;
static errorType parser(const char* const command);

#define ValidateRead(read_parameters,required_parameters,ErrorString,ErrorParams) \
if ( (read_parameters)!=(required_parameters) ) { printf(ErrorString, ErrorParams); return error; }

static bool isInit = false;

/***************************************************************************/
/* main                                                                    */
/***************************************************************************/

int main(int argc, const char**argv) {
	char buffer[MAX_STRING_INPUT_SIZE];
	FILE* fp;
	fp = fopen("C:\\Users\\Ilya\\Desktop\\MATAM\\ASSIGN4\\DataStructures-Assignment1\\input.txt", "r");
	// Reading commands
	while (fgets(buffer, MAX_STRING_INPUT_SIZE, fp) != NULL) {
		fflush(stdout);
		if (parser(buffer) == error)
			break;
	};
	return 0;
}

/***************************************************************************/
/* Command Checker                                                         */
/***************************************************************************/

static commandType CheckCommand(const char* const command,
		const char** const command_arg) {
	if (command == NULL || strlen(command) == 0 || StrCmp("\n", command))
		return (NONE_CMD);
	if (StrCmp("#", command)) {
		if (strlen(command) > 1)
			printf("%s", command);
		return (COMMENT_CMD);
	};
	for (int index = 0; index < numActions; index++) {
		if (StrCmp(commandStr[index], command)) {
			*command_arg = command + strlen(commandStr[index]) + 1;
			return ((commandType) index);
		};
	};
	return (NONE_CMD);
}

/***************************************************************************/
/* Commands Functions                                                      */
/***************************************************************************/

static errorType OnInit(void** DS, const char* const command);
static errorType OnAddPlayer(void* DS, const char* const command);
static errorType OnAddClan(void* DS, const char* const command);
static errorType OnJoinClan(void* DS, const char* const command);
static errorType OnCompleteChallange(void* DS, const char* const command);
static errorType OnUniteClans(void* DS, const char* const command);
static errorType OnGetBestPlayer(void* DS, const char* const command);
static errorType OnGetScoreboard(void* DS, const char* const command);
static errorType OnQuit(void** DS, const char* const command);

/***************************************************************************/
/* Parser                                                                  */
/***************************************************************************/

static errorType parser(const char* const command) {
	static void *DS = NULL; /* The general data structure */
	const char* command_args = NULL;
	errorType rtn_val = error;

	commandType command_val = CheckCommand(command, &command_args);

	switch (command_val) {

	case (INIT_CMD):
		rtn_val = OnInit(&DS, command_args);
		break;
	case (ADDPLAYER_CMD):
		rtn_val = OnAddPlayer(DS, command_args);
		break;
	case (ADDCLAN_CMD):
		rtn_val = OnAddClan(DS, command_args);
		break;
	case (JOINCLAN_CMD):
		rtn_val = OnJoinClan(DS, command_args);
		break;
	case (COMPLETECHALLANGE_CMD):
		rtn_val = OnCompleteChallange(DS, command_args);
		break;
	case (UNITECLANS_CMD):
		rtn_val = OnUniteClans(DS, command_args);
		break;
	case (GETBESTPLAYER_CMD):
		rtn_val = OnGetBestPlayer(DS, command_args);
		break;
	case (GETSCOREBOARD_CMD):
		rtn_val = OnGetScoreboard(DS, command_args);
		break;
	case (QUIT_CMD):
		rtn_val = OnQuit(&DS, command_args);
		break;

	case (COMMENT_CMD):
		rtn_val = error_free;
		break;
	case (NONE_CMD):
		rtn_val = error;
		break;
	default:
		assert(false);
		break;
	};
	return (rtn_val);
}

/***************************************************************************/
/* OnInit                                                                  */
/***************************************************************************/
static errorType OnInit(void** DS, const char* const command) {
	if (isInit) {
		printf("init was already called.\n");
		return (error_free);
	};
	isInit = true;

	*DS = init();
	if (*DS == NULL) {
		printf("init failed.\n");
		return error;
	};
	printf("init done.\n");

	return error_free;
}


/***************************************************************************/
/* OnAddPlayer                                                             */
/***************************************************************************/
static errorType OnAddPlayer(void* DS, const char* const command) {
	int playerID;
	int coins;
	ValidateRead(
			sscanf(command, "%d %d", &playerID, &coins),
			2, "%s failed.\n", commandStr[ADDPLAYER_CMD]);
	StatusType res = addPlayer(DS, playerID, coins);

	if (res != SUCCESS) {
		printf("%s: %s\n", commandStr[ADDPLAYER_CMD], ReturnValToStr(res));
		return error_free;
	}

	printf("%s: %s\n", commandStr[ADDPLAYER_CMD], ReturnValToStr(res));
	return error_free;
}

/***************************************************************************/
/* OnAddClan                                                               */
/***************************************************************************/
static errorType OnAddClan(void* DS, const char* const command) {
	int clanID;
	ValidateRead(sscanf(command, "%d", &clanID), 1, "%s failed.\n", commandStr[ADDCLAN_CMD]);
	StatusType res = addClan(DS, clanID);

	if (res != SUCCESS) {
		printf("%s: %s\n", commandStr[ADDCLAN_CMD], ReturnValToStr(res));
		return error_free;
	} else {
		printf("%s: %s\n", commandStr[ADDCLAN_CMD], ReturnValToStr(res));
	}

	return error_free;
}


/***************************************************************************/
/* OnJoinClan                                                              */
/***************************************************************************/
static errorType OnJoinClan(void* DS, const char* const command) {
	int playerID, teamID;
	ValidateRead(sscanf(command, "%d %d", &playerID, &teamID), 2,
			"%s failed.\n", commandStr[JOINCLAN_CMD]);
	StatusType res = joinClan(DS, playerID, teamID);
	if (res != SUCCESS) {
		printf("%s: %s\n", commandStr[JOINCLAN_CMD], ReturnValToStr(res));
		return error_free;
	}

	printf("%s: %s\n", commandStr[JOINCLAN_CMD], ReturnValToStr(res));
	return error_free;
}

/***************************************************************************/
/* OnCompleteChallange                                                     */
/***************************************************************************/
static errorType OnCompleteChallange(void* DS, const char* const command) {
	int playerID;
	int coins;
	ValidateRead(sscanf(command, "%d %d", &playerID, &coins), 2,
			"%s failed.\n", commandStr[COMPLETECHALLANGE_CMD]);
	StatusType res = completeChallange(DS, playerID, coins);

	if (res != SUCCESS) {
		printf("%s: %s\n", commandStr[COMPLETECHALLANGE_CMD], ReturnValToStr(res));
		return error_free;
	}

	printf("%s: %s\n", commandStr[COMPLETECHALLANGE_CMD], ReturnValToStr(res));
	return error_free;
}

/***************************************************************************/
/* OnUniteClans                                                            */
/***************************************************************************/
static errorType OnUniteClans(void* DS, const char* const command) {
	int clan1;
	int clan2;
	ValidateRead(sscanf(command, "%d %d", &clan1, &clan2), 2,
			"%s failed.\n", commandStr[UNITECLANS_CMD]);
	StatusType res = uniteClans(DS, clan1, clan2);

	if (res != SUCCESS) {
		printf("%s: %s\n", commandStr[UNITECLANS_CMD], ReturnValToStr(res));
		return error_free;
	}

	printf("%s: %s\n", commandStr[UNITECLANS_CMD], ReturnValToStr(res));
	return error_free;
}


/***************************************************************************/
/* OnGetBestPlayer                                                         */
/***************************************************************************/
static errorType OnGetBestPlayer(void* DS, const char* const command) {
	int clanID;
	ValidateRead(sscanf(command, "%d", &clanID), 1, "%s failed.\n", commandStr[GETBESTPLAYER_CMD]);
	int playerID;
	StatusType res = getBestPlayer(DS, clanID, &playerID);

	if (res != SUCCESS) {
		printf("%s: %s\n", commandStr[GETBESTPLAYER_CMD], ReturnValToStr(res));
		return error_free;
	}

	cout << "Most successful player is: " << playerID << endl;
	return error_free;
}

/***************************************************************************/
/* PrintAll                                                                */
/***************************************************************************/

void PrintAll(int *playerIDs, int numOfPlayers) {
	if (numOfPlayers > 0) {
		cout << "Rank\t||\tPlayer" << endl;
	}

	for (int i = 0; i < numOfPlayers; i++) {
		cout << i + 1 << "\t\t||\t" << playerIDs[i] << endl;
	}
	cout << "and there are no more players!" << endl;

	free (playerIDs);
}

static errorType OnGetScoreboard(void* DS, const char* const command) {
	int teamID;
	ValidateRead(sscanf(command, "%d", &teamID), 1,
			"%s failed.\n", commandStr[GETSCOREBOARD_CMD]);
	int* playerIDs;
	int numOfPlayers;
	StatusType res = getScoreboard(DS, teamID, &playerIDs, &numOfPlayers);

	if (res != SUCCESS) {
		printf("%s: %s\n", commandStr[GETSCOREBOARD_CMD], ReturnValToStr(res));
		return error_free;
	}

	PrintAll(playerIDs, numOfPlayers);
	return error_free;
}

/***************************************************************************/
/* OnQuit                                                                  */
/***************************************************************************/
static errorType OnQuit(void** DS, const char* const command) {
	quit(DS);
	if (*DS != NULL) {
		printf("Quit failed.\n");
		return error;
	};

	isInit = false;
	printf("Quit done.\n");

	return error_free;
}

#ifdef __cplusplus
}
#endif