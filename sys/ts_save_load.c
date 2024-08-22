/* ts_io.c 7/3/94 Stuart Cornell */
/* The functions in the file are for saving and loading tina data structure */
/* trees generically. Also for comparing and updating id format versions */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <time.h>
#include <string.h>

static char tdi_version[25]="1.1"; /* The current tsid version  */

/* Return the current version string for the Ts_id array */
char *ts_version_get(void)
{
  return tdi_version;
}

/* Write the Tina data tree at 'data' to a FILE stream*/
int ts_fsave(void *data, FILE *fp)
{
  List *s=NULL;
  int count;
  
  if(fp)
  {
      fprintf(fp,"Tina Structure Data. Version %s\n",ts_version_get());
      s=ts_serialise_gen(s,data);	     /* produce the serial list */
      count=ts_serialise_end();		     /* get the item count */
      fwrite_ts(fp,s,count);	     /* write to file */
      return 1;
  }
  return 0;
}
/* Write the Tina data tree at 'data' to a filename constructed from  */
/* 'path' + 'name' + an appropriate extension. */
int ts_save(void *data, char *path, char *name)
{
  char fname[256];
  FILE *fp;
  List *s=NULL;

  sprintf(fname,"%s/%s.tsd",path,name);
  fp=fopen(fname,"wb");
  if(fp)
  {
      int r=ts_fsave(data,fp);
      fclose(fp);
      return r;
  }
  else format("ERROR: Could not open file %s\n",fname);
  return 0;
}

/* Read the Tina data tree into pointer 'dp' from a FILE stream */
int ts_fload(void **dp,FILE *fp )
{
  List *s=NULL;
  int count;
  char version[25];

  if(fp)
    {
      int toks=fscanf(fp,"Tina Structure Data. Version %s\n",version);
      if(toks!=1)		/* file reading error */
	{
	  *(dp)=NULL;
	  return toks;
	}
      s=fread_ts(fp,&count);	     /* Read the serial list */
      if(strcmp(version,ts_version_get()))   /* if old version */
	ts_upgrade_data(s,version);	     /* upgrade ids to current Ver */
      s=ts_deserialise_gen(s,dp);	     /* produce tree from serial list */
      return 1;
    }
  return 0;
}
/* Read the Tina data tree into pointer 'dp' from a filename constructed from  */
/* 'path' + 'name' + an appropriate extension. */
int ts_load(void **dp, char *path, char *name)
{
  char fname[256];
  FILE *fp;
  List *s=NULL;

  sprintf(fname,"%s/%s.tsd",path,name);
  fp=fopen(fname,"rb");
  if(fp)
    {
      int r=ts_fload(dp,fp);
      fclose(fp);
      return r;
    }
  else format("ERROR: Could not open file %s\n",fname);
  return 0;
}

/* Save a Tina_data_info array into a filename constructed from 'path'*/
int ts_table_save(char *path, Tina_data_info *tdi, int size)
{
  char fname[256];
  FILE *fp;
  int id;

  sprintf(fname,"%s/tstable.%s",path,ts_version_get());
  fp=fopen(fname,"wt");
  if(fp)
    {
      time_t tm=time(NULL);
      fprintf(fp,"Tina Structure Data Table. Version %s\n%s",
	      ts_version_get(),asctime(gmtime(&tm)));
      fprintf(fp,"size=%i\n",size);          /* write the header */
      for(id=0; id<size; id++)		     /* for each id in table */
	fprintf(fp,"%i\t%s\t%s\n",	     /* write out the */
		id,			     /* relative id no */
		tdi[id].name,		     /* the structure name */
		tdi[id].swap_string);	     /* and the swapstring */
      fclose(fp);
      return 1;
    }
  else format("ERROR: Could not open file %s\n",fname);
  return 0;
}

/* load in a TDI table from a filename made from path + version */
/* Return the newly ralloced table and set the size */
Tina_data_info *ts_table_load(char *path,char *version, int *size)
{
  char fname[256],version_read[25],date_read[256],lstore[256];
  FILE *fp;
  Tina_data_info *tdi;
  
  sprintf(fname,"%s/tstable.%s",path,version);
  fp=fopen(fname,"rt");
  if(fp)
    {
      int id,ids;

      fscanf(fp,"Tina Structure Data Table. Version %s\n",version_read);
      fgets(date_read,256,fp);
      fscanf(fp,"size=%i\n",&ids);
#ifdef DEBUG
      format("Reading table Version %s %s Ts ids %i\n",
	     version_read,date_read,ids);
#endif
      *size=ids;			     /*Set the table size for caller */
      tdi=(Tina_data_info*)ralloc(sizeof(Tina_data_info)*ids);
      while(ids-- && !feof(fp))		     /* for all ids + while in file */
	{
	  char *name2,*ss2;		     /* the new name and ss */
	  char *line=lstore;
	  char *delim;			     /* delimiter pointer ->'\t' */

	  fgets(line,256,fp);		     /* read a line */
	  delim=strchr(line,'\t');	     /* find the first tab */
	  *delim=0;			     /* terminate the string at it */
	  id=atoi(line);		     /* convert the string to id no */

	  line=delim+1;			     /* move to next token */
	  delim=strchr(line,'\t');	     /* find the next tab */
	  *delim++=0;			     /* terminate the string at it */
	  name2=ralloc(delim-line);	     /* alocate the string space */
	  strcpy(name2,line);		     /* copy the structure name */

	  line=delim;			     /* move to last token */
	  delim=strchr(line,'\n');	     /* find the end of line */
	  *delim++=0;			     /* terminate string at it */
	  ss2=ralloc(delim-line);	     /* copy the swap string */
	  strcpy(ss2,line);

#ifdef DEBUG
	  format("ID %i %s <%s>\n",id,name2,ss2);
#endif
	  tdi[id].name=name2;		     /* set the fields if the tdi */
	  tdi[id].swap_string=ss2;	     /* array with name and ss */
	}
      fclose(fp);
      return tdi;
    }
  else
    fprintf(stderr,"ERROR: Cannot open file %s\n",fname);
  return NULL;
}

/* Build a cross reference table to look up then new ids from the old */
/* o_size is the size of the old table and n_size the new */
/* Returns an array of Ts_id's which when indexed by old id */
/* gives the appropriate new id or -1 if non-exists */
Ts_id *tdi_xref(Tina_data_info *tdi_old, int o_size,
		Tina_data_info *tdi_new, int n_size)
{
    Ts_id *reft=((Ts_id*)ralloc(sizeof(Ts_id)*o_size));
    int co,cn,upper;
    
    upper= MAX(o_size,n_size);
    for(co=0; co<o_size; co++)
    if(co > upper) reft[co]=-1;	             /* error if outside new table */
				             /* else is the structure name diff */
    else if( strcmp( tdi_old[co].name, tdi_new[co].name ))
    {		
	mprintf("WARNING: Looking for <%s> in new tables\n",tdi_old[co].name);
	for(cn=0; cn<n_size; cn++)	     /* find name in new table */
	if(!strcmp( tdi_old[co].name, tdi_new[cn].name ))
	{
	    reft[co]=cn+ts_base_id;	     /* set xreference */
	    break;			     /* drop out of search */
	}
	if(cn==n_size)		             /* didn't find a match */
	{
	    reft[co]=0;			     /* set to flag error */
	    mprintf("ERROR: Couln't find a ts match for <%s> in current version\n",
		    tdi_old[co].name);
	}
    }
    /* else is the ss different */
    else if( strcmp( tdi_old[co].swap_string, tdi_new[co].swap_string ))
    {
	reft[co]=0;			     /* then flag error */
	mprintf("WARNING: Swap string is different for <%s> OLD<%s>!=NEW<%s>\n",
		tdi_old[co].name,tdi_old[co].swap_string, tdi_new[co].swap_string );
    }
    return reft;
}

/* Translate the data in the serial list from tdi_old type to tdi_new*/
/* o_size is the size of the old table and n_size the new */
/* Returns 0 if ok !0 if not */
int ts_version_translate(List *lg, 
			  Tina_data_info *tdi_old, int o_size,
			  Tina_data_info *tdi_new, int n_size)
{
  List *l;
  int err=0;
  Ts_id *reft;

  reft=tdi_xref(tdi_old,o_size,tdi_new,n_size);	/* make xref table */
  reft-=ts_base_id;
  for(l=lg; l; l=l->next)		     /* for serial list members */
    {					     /* pickup id and pointer */
      Ts_id id=*(Ts_id*)lg->to, *idp=(Ts_id*)lg->to;
      if(lg->type>0 && reft[id])	     /* if new pointer and no error */
        *idp=reft[id];			     /* set new id from xref table */
      else err++;			     /* else flag an error */
  }
  rfree(reft+ts_base_id);
  return err==0;
}

/* Translate the data in the serial list from version 'version' to the */
/* current Ts_id system . Return an error code !0 = error if unsuccesful*/
int ts_upgrade_data(List *l, char *version)
{
  char *dir=getenv("TS_VERSION_DIR");	     /* find the version data dir */
  int o_size;
  Tina_data_info *tdi_old;		     /* a tdi table to match data */

  format("WARNING: Upgrading data from version %s\n",version);

  if(!dir) 
  {
      format("WARNING: You have not set $TS_VERSION_DIR. \n"
	     "WARNING: Trying current directory\n");
      dir=".";			     /* no env so use current dir */
  }
  tdi_old=ts_table_load(dir,version,&o_size); /* read the old version table */
					     /* translate the ids in the  */
					     /* data to match the current */
					     /* ids in this version */
  if(tdi_old)
  return ts_version_translate(l, tdi_old, o_size, 
			      tina_data_info_array, ts_last_id-ts_base_id);
				/* and return the error flag */
  else return -1;
}
