#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <crypt.h>
int main(int argc, char *agrv[])
{
	const char *const pass = "$1$Og9RbNrT$/gNprNaDgv.hNS01Ue2gi1";
    char *result;
    int ok;
    result = crypt(getpass("Password:"), pass);
    ok = strcmp (result, pass);
    if ( ok == 0 )
	{
        puts("Access granted\n");
		return 0;
	} else {
	    puts ("Access denied\n");
		return 1;
	}
}
