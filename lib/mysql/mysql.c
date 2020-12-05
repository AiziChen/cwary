//
// Created by quanye on 11/7/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "listbuff.h"

#define SOBJ_PREFIX "(*obj"
#define LIST_PREFIX "(*list"

/* SObj append */
void s_append(lb_buff_t *buff, char *key, char *value) {
    lb_append(buff, '(');
    lb_append_array(buff, key, strlen(key));
    lb_append(buff, ' ');
    lb_append_array(buff, value, strlen(value));
    lb_append(buff, ')');
}

/* SObj string append */
void s_appends(lb_buff_t *buff, char *key, char *value) {
    lb_append(buff, '(');
    lb_append_array(buff, key, strlen(key));
    lb_append(buff, '\"');
    lb_append_array(buff, value, strlen(value));
    lb_append_array(buff, "\")", 2);
}

/**
 * Init MYSQL then handle connect
 * @param host
 * @param user
 * @param password
 * @param db
 * @param port
 * @return
 */
MYSQL *connect(char *host, char *user, char *password, char *db, unsigned port) {
    MYSQL *mysql = mysql_init(NULL);
    if (mysql == NULL) {
        fprintf(stderr, "MYSQL INIT: failed\n");
        return NULL;
    }
    mysql = mysql_real_connect(mysql, host, user, password, db, port, NULL, 0);
    if (mysql == NULL) {
        fprintf(stderr, "MYSQL REAL CONNECT: failed\n");
        return NULL;
    }

    return mysql;
}

uint64_t affect_sql(MYSQL *mysql, char *sql) {
    int res = mysql_query(mysql, sql);
    if (res != 0) {
        fprintf(stderr, "MYSQL_QUERY: %s\n", mysql_error(mysql));
        exit(-1);
    }
    return mysql_affected_rows(mysql);
}


MYSQL_RES *check_and_get_mysql_res(MYSQL *mysql, char *sql) {
    int res = mysql_query(mysql, sql);
    if (res != 0) {
        fprintf(stderr, "MYSQL_QUERY: %s\n", mysql_error(mysql));
        return NULL;
    }
    MYSQL_RES *m_res = mysql_store_result(mysql);
    if (m_res == NULL) {
        fprintf(stderr, "MYSQL_STORE_RESULT: %s\n", mysql_error(mysql));
        return NULL;
    }
    return m_res;
}

char *query(MYSQL *mysql, char *sql) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    MYSQL_FIELD *field;

    lb_buff_t lb_buff;
    lb_buff_t *buff = &lb_buff;
    lb_init(buff);
    lb_append_array(buff, LIST_PREFIX, strlen(LIST_PREFIX));

    res = check_and_get_mysql_res(mysql, sql);
    if (res == NULL) {
        return NULL;
    }

    unsigned n_field = mysql_num_fields(res);
    field = mysql_fetch_field(res);

    while ((row = mysql_fetch_row(res)) > 0) {
        if (mysql_errno(mysql) != 0) {
            fprintf(stderr, "retrieve row failed: %s\n", mysql_error(mysql));
            return NULL;
        }
        lb_append_array(buff, SOBJ_PREFIX, strlen(SOBJ_PREFIX));
        int i;
        for (i = 0; i < n_field; ++i) {
            if (row[i] == NULL) {
                s_append(buff, (field + i)->name, "()");
                continue;
            }
            switch ((field + i)->type) {
                case MYSQL_TYPE_DECIMAL:
                case MYSQL_TYPE_TINY:
                case MYSQL_TYPE_SHORT:
                case MYSQL_TYPE_LONG:
                case MYSQL_TYPE_FLOAT:
                case MYSQL_TYPE_DOUBLE:
                case MYSQL_TYPE_INT24:
                case MYSQL_TYPE_LONGLONG:
                    s_append(buff, (field + i)->name, row[i]);
                    break;
                case MYSQL_TYPE_NULL:
                case MYSQL_TYPE_TIMESTAMP:
                case MYSQL_TYPE_DATE:
                case MYSQL_TYPE_TIME:
                case MYSQL_TYPE_DATETIME:
                case MYSQL_TYPE_YEAR:
                case MYSQL_TYPE_NEWDATE:
                case MYSQL_TYPE_VARCHAR:
                case MYSQL_TYPE_BIT:
                case MYSQL_TYPE_TIMESTAMP2:
                case MYSQL_TYPE_DATETIME2:
                case MYSQL_TYPE_TIME2:
                case MYSQL_TYPE_TYPED_ARRAY:
                case MYSQL_TYPE_INVALID:
                case MYSQL_TYPE_BOOL:
                case MYSQL_TYPE_JSON:
                case MYSQL_TYPE_NEWDECIMAL:
                case MYSQL_TYPE_ENUM:
                case MYSQL_TYPE_SET:
                case MYSQL_TYPE_TINY_BLOB:
                case MYSQL_TYPE_MEDIUM_BLOB:
                case MYSQL_TYPE_LONG_BLOB:
                case MYSQL_TYPE_BLOB:
                case MYSQL_TYPE_VAR_STRING:
                case MYSQL_TYPE_GEOMETRY:
                case MYSQL_TYPE_STRING:
                    s_appends(buff, (field + i)->name, row[i]);
                    break;
            }
        }
        lb_append(buff, ')');
    }
    lb_append(buff, ')');
    lb_append(buff, '\0');

    return buff->data;
}
