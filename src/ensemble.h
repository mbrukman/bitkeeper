#ifndef _NESTED_H
#define _NESTED_H

#define	ALIASES	"BitKeeper/etc/aliases"

#define	csetChomp(path)	{			\
	char	*slash = strrchr(path, '/');	\
	assert(slash);				\
	*slash = 0;				\
	}

typedef struct {
	void	**repos;	// addlines of pointers to repo's
	char	*rootkey;	// points at repos[i]->rootkey
	char	*deltakey;	// ditto
	char	*path;		// ditto
	u32	new:1;		// ditto
	u32	present:1;	// ditto
	int	index;		// used by the iterator
} repos;

typedef	struct {
	sccs	*sc;		// product changeset file if set
	char	*rev;		// if set, we want the deltakeys as of this
	char	**revs;		// if set, limit the components to these csets 
	hash	*aliases;	// if set, limit the comps to these root keys
	u32	product:1;	// include the product in the list
	u32	product_first:1;// default is last in list
	u32	undo:1;		// undo wants the -a inferred from opts.revs
	u32	deepfirst:1;	// sort such that deeply nested comps are first
} eopts;

repos*	ensemble_list(eopts opts);
int	ensemble_find(repos *repos, char *rootkey);
char*	ensemble_dir2key(repos *repos, char *dir);
repos*	ensemble_first(repos *repos);
repos*	ensemble_next(repos *repos);
void	ensemble_free(repos *repos);

int	ensemble_toStream(repos *repos, FILE *f);
repos*	ensemble_fromStream(repos *repos, FILE *f);

int	ensemble_each(int quiet, int ac, char **av);
hash	*alias_list(char **names, sccs *cset);
int	isComponent(char *path);
void	ensemble_nestedCheck(void);
int	ensemble_emptyDir(char *dir);
int	ensemble_rmtree(char *dir);
#define	EACH_REPO(c)	for (ensemble_first(c); (c)->index; ensemble_next(c))

#endif /* _NESTED_H */