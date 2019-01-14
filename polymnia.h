
/*===[[ GREEK HERITAGE ]]=====================================================*/
/*
 *
 *   polymnia-hymnos (many praises) is the muse and protector of divine hymns
 *   and lyric poetry, inventor of the lyre, patron of dancing, geometry, and
 *   gammar.  the muses (mousai) are nine daughters of zeus and mnemosyne
 *   (titan of memory) and are the goddesses of art, literature, and science.
 *   they inspire creation, enthusiasm, and the creative impulses.  polymnia
 *   is usually depicted wearing a veil and looking up to the heavens
 *
 */

/*===[[ VERSION ]]========================================*/
/* rapidly evolving version number to aid with visual change confirmation     */
#define   VER_NUM       "0.5e"
#define   VER_TXT       "files uses btree now, and unit testing is updated"



/*type*/     /*-> tbd --------------------------------[ leaf   [gn.530.341.50]*/ /*-[02.0000.000.!]-*/ /*-[--.---.---.--]-*/
/*
 *  the headers have five parts
 *  1) the return type on the left        (00-13)  int  
 *  2) function description 35 chars      (14-54)  *-> tbd --------...[
 *  3) function use classifier word       (        [ leaf   [
 *  4) complexity (15 chars long)                  [abc.def.ghijk]
 *     ----
 *     a scope  (file, global, static, unit testing, external)
 *     b rtype  (string, char, void, pointer, number)
 *     c params (parameter count)              exact
 *     ----
 *     d total  (total lines)                  scaled
 *     e debug  (debug lines)                  scaled
 *     f slocl  (slocl lines)                  scaled
 *     ----
 *     g locals (local var count)              exact
 *     h choice (decision statement count)     exact
 *     i return (return statement count)       exact
 *     j indent (maximum indentation)          in threes
 *     k memory (memory management)            y/-
 *     ----
 *  5) interaction (15 chars long)                 [abc.def.ghijk]
 *     ----
 *     a local  (local/file references count)
 *     b global (global references count)
 *     c extern (extern references count)
 *     ----
 *     d funcs  (function call count)
 *     e cstd   (function call count, just c-std)
 *     f ylib   (function call count, just my-libs)
 *     ----
 *     g input  (std library input function count)
 *     h output (std library output function count)
 *     i ncures/opengl/both (ncurses function count)
 *     j process
 *     k system
 *     ----
 *  6) group three                                 [ab.cdefg.hijk]
 *     a gproto (global protopyte)                    
 *     b lproto (local protytype)                   
 *     ----
 *     c unit   (calls in unit tests)
 *
 *
 *
 */


/*===[[ HEADERS ]]========================================*/
/*---(ansi-c standard)-------------------*/
#include    <stdio.h>        /* CLIBC   standard input/output                 */
#include    <stdlib.h>       /* CLIBC   standard general purpose              */
#include    <string.h>       /* CLIBC   standard string handling              */
#include    <unistd.h>       /* CLIBC   standard unix system handling         */
#include    <math.h>         /* CLIBC   standard expanded mathematics         */

#include  <dirent.h>


/*---(heatherly made)--------------------*/
#include    <yURG.h>         /* CUSTOM  heatherly urgent processing           */
#include    <yLOG.h>         /* CUSTOM  heatherly program logging             */
#include    <ySTR.h>         /* CUSTOM  heatherly string handling             */



#define      LEN_RECD         2000
#define      LEN_NAME           50
#define      LEN_LABEL          20


#define      FILE_EXTERN     "/var/lib/polymnia/external.txt"

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
typedef     struct      dirent      tDIRENT;
typedef     struct      cFILE       tFILE;
typedef     struct      cTAG        tTAG;
typedef     struct      cBTREE      tBTREE;
typedef     struct      cEXTERN     tEXTERN;


extern FILE *f;
extern FILE *c;

#define       MAX_FILE     200
struct cFILE {
   /*---(master)------------*/
   char        type;
   char       *name;
   /*---(stats)-------------*/
   int         lines;
   int         empty;
   int         docs;
   int         debug;
   int         code;
   int         slocl;
   /*---(tags)--------------*/
   int         btag;
   int         etag;
   tTAG       *thead;
   tTAG       *ttail;
   int         ntag;
   /*---(done)--------------*/
};
extern   tFILE    s_files [MAX_FILE];
extern   int      s_nfile;
extern   tFILE    s_totals;



#define       MAX_TAG     5000
struct cTAG {
   /*---(master)-------------------------*/
   char        name        [LEN_NAME];
   int         file;
   char        type        [LEN_NAME];
   int         line;
   char        source      [LEN_RECD];
   char        hint        [5];
   /*---(positioning)--------------------*/
   char        oneline;                 /* return type and name on same line  */
   int         beg;
   int         end;
   /*---(line counts)--------------------*/
   int         lines;
   int         empty;
   int         docs;
   int         debug;
   int         code;
   int         slocl;
   /*---(group one outputs)--------------*/
   char        scope;
   char        rtype;
   char        psize;
   char        tsize;
   char        dsize;
   char        ssize;
   char        lsize;
   char        csize;
   char        rsize;
   int         isize;
   char        msize;
   /*---(group one working)--------------*/
   char        rname       [LEN_RECD];
   char        params      [LEN_RECD];
   char        nparam;
   int         lvars;
   int         choices;
   int         returns;
   int         indent;
   int         memories;
   /*---(group two outputs)-----------*/
   char        Lsize;
   char        Gsize;
   char        Esize;
   char        Dsize;
   char        Fsize;
   char        Csize;
   char        Ysize;
   char        Xsize;
   char        Rsize;
   char        Wsize;
   char        Vsize;
   char        Psize;
   char        Ssize;
   /*---(group two working)-----------*/
   int         lcalls;
   int         gcalls;
   int         ecalls;
   int         depth;
   int         funcs;
   int         cstd;
   int         ylibs;
   int         xfuncs;
   int         reads;
   int         writes;
   int         opengl;
   int         ncurses;
   int         process;
   int         scalls;
   /*---(done)--------------*/
};
extern   tTAG     s_tags [MAX_TAG];
extern   int      s_ntag;


extern char      s_pprev     [LEN_RECD];
extern char      s_prev      [LEN_RECD];
extern char      s_curr      [LEN_RECD];

extern int       s_lines;
extern int       s_empty;
extern int       s_docs;
extern int       s_debug;
extern int       s_code;
extern int       s_slocl;



/*----------+-----------+-----------+-----------+-----------+-----------+-----*/
struct      cBTREE {
   /*---(information)-------*/
   char       *sort;
   /*---(linked list)-------*/
   tBTREE     *prev;
   tBTREE     *next;
   /*---(searching)---------*/
   tBTREE     *left;
   tBTREE     *right;
   /*---(data)--------------*/
   void       *data;
   /*---(done)--------------*/
};
#define     B_FILES     'f'
#define     B_TAGS      't'
#define     B_PROTO     'p'
#define     B_EXTERN    'e'
#define     B_UNIT      'U'
#define     B_ALL       "ftpeU"



/*----------+-----------+-----------+-----------+-----------+-----------+-----*/
struct      cEXTERN {
   /*---(information)-------*/
   char       *name;
   int         len;
   char        type;
   int         count;
   /*---(linked list)-------*/
   tEXTERN    *prev;
   tEXTERN    *next;
   /*---(searching)---------*/
   tEXTERN    *left;
   tEXTERN    *right;
   /*---(done)--------------*/
};

extern int   g_depth;
extern char  g_path    [LEN_LABEL];



extern char      unit_answer [LEN_RECD];


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        htags_readline          (int a_file, int *l, int *n);
char        htags_scope             (int n, int l);
char        poly_cats_tagsumm       (int n);
char        htags_calls             (char *a_file, int  n, int *a_dst);

char        poly_files_init         (void);
char        poly_files_wrap         (void);
char        poly_files__add         (char *a_name, char a_type);
char        poly_files_review       (void);
char        poly_files_list         (void);
tFILE*      poly_files_search       (char *a_name);
char*       poly_files__unit        (char *a_question, int n);

char        htags_tags_wipe         (tTAG *a_dst);
char        htags_tags_init         (void);
char        htags_tags_hint         (int n, char *a_label);
char        htags_tags_add          (int a_file, char *a_name, char *a_type, int a_line, char *a_source);
char        htags_tags_inventory    (int n);
char        htags_tags_review       (int a_file);
char*       htags_tags__unit        (char *a_question, int n);

char        poly_cats_flag          (char *a_label, int a_src, char *a_dst, char a_zero);
char        poly_cats_exists        (char *a_label, int a_src, char *a_dst, char a_zero);
char        poly_cats_exact         (char *a_label, int a_src, char *a_dst, char a_zero);
char        poly_cats_scaled        (char *a_label, int a_src, char *a_dst, char a_zero);
char        poly_cats_logic         (int a_tag, char a_type);
char        poly_cats_lines         (int a_file, int a_tag, char a_type);
char        poly_cats_depth         (int n);
char*       htags_cats__unit        (char *a_question, int n);

char        PROG__unit_quiet        (void);
char        PROG__unit_loud         (void);
char        PROG__unit_end          (void);

char        poly_extern_init        (void);
char        poly_extern_wrap        (void);
char        poly_extern__add        (char *a_name, char a_type);
char        poly_extern_load        (void);
char        poly_extern_check       (char *a_name);
char        poly_extern_review      (int n);
char        poly_extern_list        (void);
tEXTERN*    poly_extern_search      (char *a_name);
char*       poly_extern__unit       (char *a_question, int n);

char        poly_proto_init         (void);
char        poly_proto_add          (int a_file, char *a_name, char a_type, int a_line);


char        poly_btree_init         (char a_btree);
char        poly_btree_create       (char a_btree, void *a_data, char *a_sort);
char        poly_btree_purge        (char a_btree);
int         poly_btree__depth       (int a_size);
int         poly_btree__span        (int a_levels);
char        poly_btree_dgnome       (char a_btree);
void*       poly_btree_first        (char a_btree);
void*       poly_btree_next         (void);
void*       poly_btree_entry        (char a_btree, int i);
int         poly_btree_count        (char a_btree);
char        poly_btree_build        (char a_btree);
char        poly_btree_list         (char a_btree);
void*       poly_btree_search       (char a_btree, char *a_name);
char*       poly_btree__unit        (char a_btree, char *a_question, int i);



