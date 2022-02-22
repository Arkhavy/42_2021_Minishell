//LIBFT Autorisée
//Une variable globale autorisée

/*Fonctions*/
#include <stdio.h>
Printf		:	int		printf(const char * restrict format, ...);
Perror		:	void	perror(const char *s);
/**Perror
 * Affiche le message donné en paramètre
 * Cherche la valeur actuelle de la variable globale errno et affiche le message assigné à cette valeur
*/

#include <stdlib.h>
Malloc		:	void	*malloc(size_t size);
Free		:	void	free(void *ptr);
Exit		:	void 	exit(int status);
/**
 * Termine un processus -> flush et close tout les streams ouverts et unlink tous les fichiers
 * le paramètre est un int retourné à la fin du programme (pareil que le return 0 du main)
*/
Getenv		:	char	*getenv(const char *name);
/**
 * param = env variable
 * returns = valeur de la variable environnement
 * optionnel ?
*/

#include <unistd.h>
Write		:	ssize_t	write(int fd, const void *buf, size_t len);
Read		:	ssize_t	read(int fd, void *buf, size_t len);
Close		:	int		close(int fd);
Access		:	int		access(const char *path, int mode);
/**
 * Vérifie les permission du path donné en premier argument
 * mode = F_OK pour check l'existence, R_OK, W_OK, X_OK pour vérifier read, write et exec
 * Si la vérification est OK, retourne 0, sinon -1 et errno est mis à jour
*/

Fork		:	pid_t	fork(void);
/**
 * duplique le processus appelant
 * le processus créé aura 0 sur la valeur retournée (child)
 * le processus appelant aura un PID donné selon le programme source (parent)
 * retourne -1 si il y a eu un problème et errno est mis à jour
*/

Unlink		:	int		unlink(const char *path);
/**
 * supprime le lien entre le param 1 et le dossier et décrémente le nombre de lien du fichier.
 * Si le nombre de lien est de 0 et qu'aucun process n'a le fichier ouvert, 
 * toutes les ressources allouées à ce fichier sont libérées
 * retourne 0 si OK, -1 si erreur et errno est mis à jour
*/

Execve		:	int		execve(const char *path, const char **av, const char **env);
/**
 * Transforme le processus appelant en un nouveau processus exécutant le fichier donné par param 1
 * param 1 = path du fichier à exécuter
 * param 2 = nom de la commande et ses éventuels flags
 * param 3 = variable environnement donnée par le main, car certaines commandes en ont besoin
 * retourne -1 en cas d'erreur, ne transforme pas le processus et met à jour errno
 * ne retourne rien en cas de réussite, le processus appelant sera exit et le nouveau sera lancé
 * À utiliser uniquement dans un child pour éviter de terminer le programme principal
*/
Dup			:	int		dup(int fd);
/**
 * duplique le fd donné en paramètre et retourne le nouveau fd
 * Si on écrit sur un des deux fd, il apparaît sur l'autre
 * Retourne -1 en cas d'erreur et errno est mis à jour
 * Sinon retourne le nouveau fd
*/
Dup2		:	int		dup2(int fd, int fd2);
/**
 * duplique le fd en param 1 sur le fd voulu en param 2
 * si fd2 est déjà ouvert, le close pour réouvrir avec la duplication
 * Retourne -1 en cas d'erreur et errno est mis à jour
 * Sinon retourne le nouveau fd, qui doit normalement être fd2
*/
Pipe		:	int		pipe(int fd[2]);
/**
 * Ouvre une paire de fd liés
 * retourne -1 en cas d'erreur et met à jour errno, sinon retourne 0
 * fd[0] est R_ONLY
 * fd[1] est W_ONLY
 * Si on écrit sur fd[1], cela s'affiche sur fd[0]
 * Si aucun des deux fd est close, le pipe reste en buffer
 * Le fait de close un des deux fd permet de créer un EOF pour celui lisant fd[0]
*/
Getcwd		:	char	*getcwd(char *buf, size_t size);
/**
 * Get Current Working Directory
 * Retourne un pointeur buf si fonctionne correctement, sinon retourne NULL et errno est mis à jour
 * Alloue un espace mémoire pour le char* qui contiendra la valeur de retour qu'il faut free
*/
Chdir		:	int		chdir(const char *path);
Ttyname		:	char	*ttyname(int fd);
Isatty		:	int		isatty(int fd);
Ttyslot		:	int		ttyslot(void);

#include <fcntl.h>
Open		:	int		open(const char *path, int oflag, ...);

#include <sys/wait.h>
Wait		:	pid_t	wait(int *stat_loc);
Waitpid		:	pid_t	waitpid(pid_t pid, int *stat_loc, int options);
Wait3		:	pid_t	wait3(int *stat_loc, int options, struct rusage *rusage);
Wait4		:	pid_t	wait4(pid_t pid, int *stat_loc, int options, struct rusage *rusage);

#include <string.h>
Strerror	:	char	*strerror(int errnum);

#include <signal.h>
struct sigaction
{
	union __sigaction_u __sigaction_u;	/* signal handler */
	sigset_t 			sa_mask;	/* signal mask to apply */
	int					sa_flags;	/* see signal options below */
};
// ^ structures issue du man ^

Signal		:	sig_t	signal(int sig, sig_t func);
Sigaction	:	int		sigaction(int sig, const struct sigaction act, struct sigaction oact);
Sigemptyset	:	int		sigemptyset(sigset_t *set);
Sigaddset	:	int		sigaddset(sigset_t *set, int signo);
Kill		:	int		kill(pid_t pid, int sig);

#include <sys/stat.h>
stat		:	int		stat(const char *path, struct stat *buf);
lstat		:	int		lstat(const char *path, struct stat *buf);
fstat		:	int		fstat(int fd, struct stat *buf);

#include <dirent.h>
opendir		:	DIR		*opendir(const char *filename);
readdir		:	struct dirent	*readdir(DIR *dirp);
closedir	:	int		closedir(DIR *dirp);

#include <sys/ioctl.h>
ioctl		:	int		ioctl(int fd, unsigned long request, ...);

#include <termios.h>
Tcsetattr	:	int		tcsetattr(int fd, int opt_actions, const struct termios *termios_p);
Tcgetattr	:	int		tcgetattr(int fd, const struct termios *termios_p);

#include <curses.h>
#include <term.h>
Tgetent		:	int		tgetent(char *bp, const char *name);
Tgetflag	:	int		tgetflag(char *id);
Tgetnum		:	int		tgetnum(char *id);
Tgetstr		:	char	*tgetstr(char *id, char **area);
Tgoto		:	char	*tgoto(const char *cap, int col, int row);
Tputs		:	int		tputs(const char *str, int affcnt, int (*putc)(int));

#include <readline/readline.h>
#include <readline/history.h>

"https://eli.thegreenplace.net/2016/basics-of-using-the-readline-library/"
"https://tiswww.case.edu/php/chet/readline/rltop.html"
Readline	:	char	*readline(const char *prompt); "https://man7.org/linux/man-pages/man3/readline.3.html"
//param = affichage du prompt (ex z4r10p5%, bash-3.2$, ...)
//retourne la ligne dans un char* malloc.
//Askip sujet à énormément de leaks ?
Add_history //probablement utilisé en couple avec Readline ?
Rl_clear_history //probablement utilisé à la fin du programme

Rl_replace_line
Rl_on_new_line
Rl_redisplay
//Ces trois là vont probablement récupérer les lignes venant de l'historique ou un truc dans le genre
//Utilisation de signaux peut être ?
//Y a pas de doc oskour

variable globale pour la sortie standard et la sortie erreur du prompt readline ?


// Liste des includes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <curses.h>
#include <term.h>
#include <readline/readline.h>
#include <readline/history.h>

//Besoin de préciser chaque param, return et fonctionnement de chaque fonction listée
//Need approfondissement concernant readline et sa doc -> brew serait une piste ?
//As-t'on réellement besoin de readline ?
//La séparation parsing / exécution peut se faire
//Les signaux seront très importants
//Pipex doit être remanié pour son here_doc, les pipes et sa gestion d'arguments
//Besoin d'explication sur les signaux et leur fonctionnement
//Les fonctions additionnelles de readline seront probablement nécessaire pour le bon fonctionnement de minishell

/* OUAF */