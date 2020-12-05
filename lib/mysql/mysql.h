//
// Created by quanye on 11/15/20.
//

#include <mysql/mysql.h>
#include "listbuff.h"

#ifndef TEST_C_CMYSQL_FFI_H
#define TEST_C_CMYSQL_FFI_H

#endif //TEST_C_CMYSQL_FFI_H

/* Connect to the MYSQL server*/
MYSQL *connect(char *host, char *user, char *password, char *db, unsigned port);

/* Execute no-effect sql */
char *query(MYSQL *mysql, char *sql);

/* Execute has-effected sql */
uint64_t affect_sql(MYSQL *mysql, char *sql);
