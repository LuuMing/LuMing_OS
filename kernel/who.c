#include<asm/segment.h>
#include<errno.h>
extern int errno;
char myname[23];
int sys_whoami(char * name, unsigned int size)
{
	unsigned int i = 0;
	for( i = 0; myname[i] != 0; i++)
		put_fs_byte(myname[i],&name[i]);
	put_fs_byte(0,&name[i]);
	if( i > size)
	{
		errno = EINVAL;
		return -1;
	}
	else
		return i;
}
int sys_iam(const char * name)
{
	int i = 0;
	for( i = 0; i < 23; i++)
	{
		myname[i] = get_fs_byte(&name[i]);
		if(myname[i] == 0)
			break;
	}
	printk("%s\n",myname);
}
