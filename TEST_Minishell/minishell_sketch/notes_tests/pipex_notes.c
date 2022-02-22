◦	"link		:	<unistd.h>		:" int	link(const char *path1, const char *path2); // NON AUTHORIZED
//crée le dossier noté dans path2 avec les attributs de l'objet pointé par path1, lien fonctionnel = +1
◦	"unlink		:	<unistd.h>		:" int	unlink(const char *path);
//supprime le lien path(path2 link) du fichier et décrémente le compteur de lien référencé par link.
//si l'int devient 0 et qu'aucun process n'a le fichier d'ouvert, toutes les ressources allouée au fichier sont récupérées
//si un process a le fichier ouvert, quand le dernier lien est retiré, 
//mais la commande attend que tout soit fermé pour s'exécuter

◦	"open		:	<fcntl.h>		:" int	open(const char *path, int oflag, ...);
//ouvre un fichier, renvoie un int que read et close peuvent utiliser


◦	"read		:	<unistd.h>		:" ssize_t	read(int fd, void *buffer, size_t bufsize);
//lis un fichier selon l int envoyé par open

◦	"close		:	<unistd.h>		:" int	close(int fd);
//ferme un fichier selon l int envoyé par open

◦	"write		:	<unistd.h>		:" ssize_t	write(int fd, const void *buffer, size_t bufsize);
//écris sur l int choisi, peut être un file descriptor


◦	"wait		:	<sys/wait.h>	:" pid_t	wait(int *stat_loc);
//supend l'exécution du processus qui l'appelle jusqu'à ce que l'int soit disponible ou qu'un signal est reçu
◦	"waitpid	:	<sys/wait.h>	:" pid_t	waitpid(pid_t pid, int *stat_loc, int options);
//pid = process ID, if -1, waits for any child process, if > 0, waits for that particular process.
//if < -1, same as > 0 with absolute value
//stat_loc = 
//options = contient bitwise ou WNOHANG, WUNTRACED, SIGTTIN, SIGTTOU, SIGTSTP, SIGSTOP

◦	"malloc		:	<stdlib.h>	:" void	*malloc(size_t size);
//alloue de la mémoire sous forme de pointeur

◦	"free		:	<stdlib.h>	:" void	free(void *ptr);
//libère la mémoire allouée

◦	"pipe		:	<unistd.h>	:" int	pipe(int fd[2]);
//alloue une paire de fd, le premier étant le read, le second étant le write, faisant le lien entre sortie et entrée
//ce qui est écrit sur fd[1] apparaît sur fd[0], ce qui permet d'enchaîner les pipe !
//il faut probablement open et close au fur et à mesure pour mettre à jour les int de fd

◦	"dup		:	<unistd.h>	:" int	dup(int fd);
//duplique un file descriptor et retourne sa valeur (ouvre une seconde fois quelque chose de déjà ouvert)
//le nouveau fd est le plus petit disponible
◦	"dup2		:	<unistd.h>	:" int	dup2(int fd, int fd2);
//pareil que dup, sauf que l'on défini la valeur du prochain fd avec fd2
//si fd2 est déjà utilisé, agira comme un close(fd2) avant d'open fd2 de nouveau avec la duplication

◦	"access		:	<unistd.h>	:" int	access(const char *path, int mode);
//vérifie l accessibilité d un fichier via son path, R_OK, W_OK, X_OK pour les permissions et F_OK pour son existence
// 0 if OK, -1 if KO

◦	"execve		:	<unistd.h>	:" int	execve(const char *path, char **av, char **env);
//exécute un fichier en créant un nouveau processus construit par le fichier du path donné
//le path peut mener à un exécutable comme un simple fichier de donnée à lire
//will probably need more informations

◦	"fork		:	<unistd.h>	:" pid_t	fork(void);
//permet de créer un nouveau processus enfant qui est une copie exacte de celui qui appelle cette fonction
//le child process possède son propre pid
//le child process possède le pid du processus appelant en tant que parent pid
//le child process possède les même fd, si un child modifie quelque chose, le parent aura le changement

◦	"perror		:	<stdio.h>	:" void	perror(const char *str);
//retourne le message donné en paramètre avec un retour à la ligne dans la sortie d'erreur

◦	"strerror	:	<stdio.h>	:" char	*strerror(int errnum);
//retourne un message d'erreur selon l'int donné

◦	"exit		:	built-in	:" void	exit(fd);
//termine le processus correspond au fd
//will probably need more informations

◦	"Here_doc	:	built-in	:" Here_doc LIMITER cmd1 cmd2 file2 == cmd1 << LIMITER | cmd2 >> file2
//Correspond à l'entrée terminal, le limiter étant la condition d'arrêt du terminal.