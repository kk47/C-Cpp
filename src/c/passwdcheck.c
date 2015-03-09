/* Usage: echo password | check_password username */
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <shadow.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
    char password[100];
    struct spwd* shadow_entry;
    char *p, *correct, *supplied, *salt;
    if (argc < 2) return 2;
    /* Read the password from stdin */
    p = fgets(password, sizeof(password), stdin);
    if (p == NULL) return 2;
    *p = 0;
    /* Read the correct hash from the shadow entry */
    char username[] = "shareuser";
    shadow_entry = getspnam(username);
    if (shadow_entry == NULL) return 1;
    correct = shadow_entry->sp_pwdp;
    /* Extract the salt */
    salt = strdup(correct);
    //printf("salt:%s", salt + 1);
    if (salt == NULL) return 2;
    p = strchr(salt + 1, '$');
    if (p == NULL) return 2;
    p = strchr(salt + 1, '$');
    if (p == NULL) return 2;
    //printf("salt:%s", p);
    p[1] = 0;
    printf("salt:%s", salt);
    /*Encrypt the supplied password with the salt and compare the results*/
    supplied = crypt(password, salt);
    if (supplied == NULL) return 2;
    return !!strcmp(supplied, correct);
}
