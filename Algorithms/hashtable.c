/* Author J. Zobel, April 2001.
   Permission to use this code is freely granted, provided that this
   statement is retained. */

#define TSIZE	1048576
#define SEED	1159241
#define HASHFN  bitwisehash


typedef struct hashrec
{
    char	*word;
    struct hashrec *next;
} HASHREC;


/* Create hash table, initialise ptrs to NULL */
HASHREC **
inithashtable()
{
    int		i;
    HASHREC     **ht;

    ht = (HASHREC **) malloc( sizeof(HASHREC *) * TSIZE );

    for( i=0 ; i<TSIZE ; i++ )
	ht[i] = (HASHREC *) NULL;

    return(ht);
}


/* Search hash table for given string, return record if found, else NULL */
HASHREC *
hashsearch(HASHREC **ht, char *w)
{
    HASHREC	*htmp, *hprv;
    unsigned int hval = HASHFN(w, TSIZE, SEED);

    for( hprv = NULL, htmp=ht[hval]
	    ; htmp != NULL && scmp(htmp->word, w) != 0
	    ; hprv = htmp, htmp = htmp->next )
    {
	;
    }

    if( hprv!=NULL ) /* move to front on access */
    {
	hprv->next = htmp->next;
	htmp->next = ht[hval];
	ht[hval] = htmp;
    }

    return(htmp);
}


/* Search hash table for given string, insert if not found */
void
hashinsert(HASHREC **ht, char *w)
{
    HASHREC	*htmp, *hprv;
    unsigned int hval = HASHFN(w, TSIZE, SEED);

    for( hprv = NULL, htmp=ht[hval]
	    ; htmp != NULL && scmp(htmp->word, w) != 0
	    ; hprv = htmp, htmp = htmp->next )
    {
	;
    }

    if( htmp==NULL )
    {
	htmp = (HASHREC *) malloc( sizeof(HASHREC) );
	htmp->word = (char *) malloc( strlen(w) + 1 );
	strcpy(htmp->word, w);
	htmp->next = NULL;
	if( hprv==NULL )
	    ht[hval] = htmp;
	else
	    hprv->next = htmp;

	/* new records are not moved to front */
    }
    else
    {
	if( hprv!=NULL ) /* move to front on access */
	{
	    hprv->next = htmp->next;
	    htmp->next = ht[hval];
	    ht[hval] = htmp;
	}
    }

    return;
}
