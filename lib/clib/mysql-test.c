//
// Created by quanye on 11/7/20.
//

#include <stdio.h>
#include "mysql.h"

int main(void) {
    MYSQL *mysql = connect("localhost", "root", "Quanyec-123", "test", 3306);
    printf("= mysql connect success =\n");

    affect_sql(mysql, "START TRANSACTION");

    // delete test
//    affect_sql(mysql, "DELETE FROM user WHERE name = 'DavidChen'");

    // insert test
//    affect_sql(mysql, "INSERT INTO user (name, age) VALUE ('DavidChen', 12)");

    // query test
    char *rs = query(mysql, "SELECT * FROM user ORDER BY id DESC LIMIT 100");

    affect_sql(mysql, "COMMIT");

    printf("%s\n", rs);
    free(rs);

    mysql_close(mysql);

    return 0;
}