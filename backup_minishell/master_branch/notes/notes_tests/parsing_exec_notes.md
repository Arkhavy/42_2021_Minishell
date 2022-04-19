- récupération des variables d'environnement -> linked list
- récupération de pwd -> getcwd
- récupération des fd STDIN STDOUT STDERR -> dup
- lecture de ligne -> readline
- ajout de la ligne dans l'historique -> add_history
- gestion des flèches pour l'historique ? -> rl_replace_line / rl_on_new_line

# parsing de la ligne lue
	vérification du contenu : double quotes, simple quotes, dollars, pipe, commandes, chevrons, redirections
	split de ce même contenu
		séparation des commandes avec leurs flags et leurs arguments
		if chevron < le récupérer avec son argument dans un split
		if chevron << here_doc avec son limiteur dans un split
		if chevron > récupérer avec son argument dans un split
		Avoir un identifiant pour chaque maillon pour savoir à quoi on a affaire ? (1 cmd, 2 stdin, 3 here_doc, 4 redirect)

# linked list t_line
{
	char	*value; //raw part until what ? Pipe ? Redirection ?
	char	**split; //cmd + flags + args of value
	int		id; //1 for cmd, 2 for <, 3 for <<, 4 for >, 5 for >>, 6 for |
	int		pipe_in; // boolean
	int		pipe_out; // boolean
	list	*next;
}

Gestion de la ligne en linked list de split
Les tokens peuvent être utiles, mais sont-ils nécessaires ? STRTOK ?

Exec -> linked list env into split
il faut une fonction spéciale conversion linked list -> split

Export ajoute quelque chose à la liste
Unset retire quelque chose à la liste (Pas totalement sûr de ça)
Env affiche la liste
Pwd affiche getcwd
Echo sera géré comme une commande classique
Exit est à recoder
Cd a besoin de getcwd ou de la variable env pwd


| Les pipes : Donnent la sortie de la commande précédente en tant qu'argument à la suivante
Comment les gérer avec la liste ? Si on a un pipe, on doit récupérer la sortie de la cmd précédente


# Split with space
if split[x] = cmd
then if split[x + 1] = pipe
		linkcmd->pipe_out = 1;
	if split[x - 1] = pipe
		linkcmd->pipe_in = 1;
deal cmd with those infos
Attention aux quotes si on split de cette façon (le split expliqué plus bas serait une solution)
Est-ce qu'un fonctionnement en token aiderait à faire ce genre de chose ?

# cmd exec will then have 4 different functions
	1 : no pipe
	2 : pipe_in only
	3 : pipe_out only
	4 : pipe both
	each will have a different way of working, duping and executing commands
	handle fd before and after the execution depending on those values might be the solution

# Création de la linked list
	Lecture de la ligne
		Split en fonction des espaces selon des conditions précises : 
			cmd <flags> <args>
			cmd <flags>
			cmd <args>
			cmd
			end of double quotes unless if nested
			end of simple quotes unless if nested
			end of $ENV_VAR unless if nested
			pipe needs to be isolated and need to update booleans of what is around
			<< <arg>
			< <arg>
			> <arg> ou X> <arg>
			>> <arg> ou X>> <arg>
		if double quote -> chercher la seconde
		if simple quote -> chercher la seconde
		les doubles ou simples quotes peuvent entourer les <args> et $ENV_VAR

Tout ce qui est entre double ou simple quote est considéré comme un seul paquet (if nested, don't split or handle)

### Quelles sont les conditions de split ?
	Fin de nesting ? (end of double or simple quotes)
	Pipe hors nesting
	Fin d'argument de commande hors nesting
	Fin de flag de commande si pas d'argument hors nesting
	Fin de commande si pas de flag ni d'argument hors nesting
	Fin de variable environnement hors nesting
	Début de redirection hors nesting
	Fin d'argument de redirection (nesting compris)