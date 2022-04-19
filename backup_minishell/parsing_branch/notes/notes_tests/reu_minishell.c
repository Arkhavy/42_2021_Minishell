//non built-in
< 
<infile> -> open = fd_in
<&fd> = fd_in
t_envdata	*envdata;
char		*rawcmd; -> <cmd> <option> <arg>
int			fd_in;
int			fd_out;
close (fd_in);
return (fd_out);
|
t_envdata	*envdata;
char		*rawcmd; -> <cmd> <option> <arg>
int			fd_in; <- fd_out
int			fd_out; -> fd_in
close (fd_in);
return (fd_out);
|
t_envdata	*envdata;
char		*rawcmd; -> <cmd> <option> <arg>
int			fd_in; <- fd_out
int			fd_out;
close (fd_in);
return (fd_out);
>
fd_out = -> open <outfile>
fd_out = <&fd>

>
while
	read(fd_in, buffer, 1);
	write(fd_out, &buffer, 1);

if > -> vérifier sortie
	if fichier, transformer fichier en fd
	if fd -> get fd

int	token_id; = chevron
int	fd_in;
int	fd_out;
