/**
 * Generic errors structure that contains some information about an error,
 * like error code and message.
 */
typedef struct error {
	int err_code;
	char err_msg[100];
} t_error;

/**
 * Definition of the wrong number of nodes error code,
 * the choice of the message is free.
 */
#define WRONG_NUM_OF_NODES_ERR 1

/**
 * Definition of the wrong number of blocks error code,
 * the choice of the message is free.
 */
#define WRONG_BLOCK_SIZE_ERR 2
