#ifndef CLI_CMD_CONFIG_H
#define CLI_CMD_CONFIG_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "config/config.h"

#include "cli_intf.h"

typedef CLI_CMD_CODE_t(*fptr_CLI_CMD_handler)(char *cmds[], uint16_t cmdLen);

struct CLI_CMD_CONFIG_s {
    const char *cmd;
    const char *title;
    const char *description;
    fptr_CLI_CMD_handler handler;
};

typedef struct CLI_CMD_CONFIG_s CLI_CMD_CONFIG_t;

#define CLI_CMD_getCmd(cmds) (cmds)[0]
#define CLI_CMD_getCmdParam(cmds, index) (cmds)[(index) > 0 ? (index)-1U : 0]

//////////////////////////////////////////////////////////////////////////
// Command handler functions prototypes
//////////////////////////////////////////////////////////////////////////
extern const CLI_CMD_CONFIG_t CLI_CMD_cShowMenu;

#define CLI_CMD_CONFIG_ENTRY(cfg) &(cfg),

#define CLI_CMD_CONFIG_SHOWMENU CLI_CMD_CONFIG_ENTRY(CLI_CMD_cShowMenu)




#define CLI_CMD_CONFIG_ENTRIES \
    CLI_CMD_CONFIG_SHOWMENU       \
    /* Add entries above this line*/

#endif /* CLI_CMD_CONFIG_H */
