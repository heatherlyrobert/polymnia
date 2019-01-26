/*===============================[[ beg-code ]]===============================*/

/*===[[ HEADER ]]=============================================================*/
/*
 *   focus         : c-ide
 *   niche         : code analysis
 *   heritage      : polymnia-hymnos (muse of divine hymns, geometry, and grammar)
 *   purpose       : research and analysis of c programs and my full code-base
 *
 *   base_system   : gnu/linux   (powerful, ubiquitous, technical, and hackable)
 *   lang_name     : ansi-c      (wicked, limitless, universal, and everlasting)
 *   dependencies  : none
 *   size          : small       (approximately 2,000 slocL)
 * 
 *   author        : rsheatherly
 *   created       : 2019-01
 *   priorities    : direct, simple, brief, vigorous, and lucid (h.w. fowler)
 *   end goal      : loosely coupled, strict interface, maintainable, traceable
 */

/*===[[ GREEK HERITAGE ]]=====================================================*/
/*
 *
 *   polymnia-hymnos (many praises) is the muse and protector of divine hymns
 *   and lyric poetry, inventor of the lyre, patron of dancing, geometry, and
 *   grammar.  the muses (mousai) are nine daughters of zeus and mnemosyne
 *   (titan of memory) and are the goddesses of art, literature, and science.
 *   they inspire creation, enthusiasm, and the creative impulses.  polymnia
 *   is usually depicted wearing a veil and looking up to the heavens
 *
 */

/*===[[ VERSION ]]========================================*/
/* rapidly evolving version number to aid with visual change confirmation     */
#define   VER_NUM       "0.7b"
#define   VER_TXT       "bringing back and enhancing unit testing"



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
 *  5) interaction (15 chars long)                 [ab.cdefg.hijk]
 *     ----
 *     b global (global references count)
 *     a local  (local/file references count)
 *     ----
 *     c funcs  (function call count)
 *     d intern (calls to internal functions)
 *     e cstd   (function call count, just c-std)
 *     f ylib   (function call count, just my-libs)
 *     g mystry (who knows the destination)
 *     ----
 *     h input  (std library input)            R/-
 *     i output (std library output)           W/-
 *     j process/system                        P/S/B
 *     k recursion                             y/-
 *     ----
 *  6) warnings                                    [abc.defg.hijk]
 *     a dstyle (multi, single, mix, none)    - l s b L S B f #
 *     b dmacro (single, multi)
 *     c dmatch (verify matching enter/exits)
 *     ----
 *     d ncurse (calls to ncurses)             
 *     e opengl (calls to opengl)             
 *     f window (calls to X11, etc)
 *     g myx    (calls to yX11, yFONT, yCOLOR)
 *     ----
 *     h proto  (global, private, local)              
 *     i extern (extern references count)
 *     j -
 *     k unit   (calls in unit tests)
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
#define      LEN_FULL          100
#define      LEN_NAME           30
#define      LEN_LABEL          20



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
typedef     struct      dirent      tDIRENT;

typedef     struct      cMY         tMY;
typedef     struct      cPROJ       tPROJ;
typedef     struct      cFILE       tFILE;
typedef     struct      cTAG        tTAG;
typedef     struct      cYLIB       tYLIB;
typedef     struct      cWORK       tWORK;

typedef     struct      cBTREE      tBTREE;
typedef     struct      cEXTERN     tEXTERN;



#define     MODE_HTAGS        'h'
#define     MODE_SEARCH       's'
#define     MODE_WRITE        'w'
#define     MODE_REMOVE       'r'
#define     MODE_UPDATE       'u'
#define     MODE_SYSTEM       'S'
#define     MODE_PROJ         'P'
#define     MODE_FILE         'F'
#define     MODE_TAGS         'T'
#define     MODE_EXTERN       'E'
#define     MODE_DUMP         'd'

#define     RPTG_TITLES       't'
#define     RPTG_NOTITLES     '-'
#define     RPTG_TREEVIEW     'T'


#define     FILTER_NONE       '-'
#define     FILTER_DEBUG      'd'


#define     F_DB        "/var/lib/polymnia/polymnia.db"
#define     F_CTAGS     "polymnia.ctag"
#define     F_CFLOW     "polymnia.cflow"
#define     F_EXTERN    "/var/lib/polymnia/external.txt"
#define     F_MYSTRY    "polymnia.mystry"


struct cMY {
   /*---(runtime config)------*/
   char        g_mode;                 /* run-time mode                       */
   char        g_titles;               /* use/hide report titles              */
   char        g_filter;               /* report filtering criteria           */
   /*---(filtering)-----------*/
   char        g_project   [LEN_RECD]; /* project name for filtering          */
   tPROJ      *g_proj;                 /* limit output to this project        */
   char        g_extern    [LEN_RECD]; /* name for focus/filtering            */
   /*---(files)---------------*/
   FILE       *f_db;                   /* shared database                     */
   FILE       *f_prog;                 /* current program source file         */
   FILE       *f_tags;                 /* ctags input file                    */
   FILE       *f_flow;                 /* cflow input file                    */
   FILE       *f_extern;               /* shared external function list       */
   FILE       *f_mystry;               /* local mystery external calls        */
   /*---(counts)--------------*/
   int         s_files;                /* global file count                   */
   int         s_funcs;                /* global function count               */
   int         s_lines;                /* global line count (all)             */
   int         s_empty;                /* global empty line count             */
   int         s_docs;                 /* global doc/commnent line count      */
   int         s_debug;                /* global debug line count             */
   int         s_code;                 /* global source code line count       */
   int         s_slocl;                /* global truer code line count        */
   /*---(content)-------------*/
   char        s_curr      [LEN_RECD]; /* current source line                 */
   char        s_prev      [LEN_RECD]; /* previous source line                */
   char        s_pprev     [LEN_RECD]; /* prev-previous source line           */
   /*---(done)----------------*/
};
extern      tMY         my;






/*----------+-----------+-----------+-----------+-----------+-----------+-----*/
struct cPROJ {
   /*---(master)------------*/
   char        focus       [LEN_NAME];
   char        niche       [LEN_NAME];
   char        name        [LEN_NAME];
   char        heritage    [LEN_FULL];
   char        purpose     [LEN_FULL];
   char        created     [LEN_LABEL];
   char        codesize    [LEN_NAME];
   char        home        [LEN_FULL];
   char        vernum      [LEN_LABEL];
   char        vertxt      [LEN_FULL];
   /*---(stats)-------------*/
   int         ntags;
   int         lines;
   int         empty;
   int         docs;
   int         debug;
   int         code;
   int         slocl;
   /*---(files)-------------*/
   tFILE      *head;
   tFILE      *tail;
   int         count;
   /*---(btree)-------------*/
   tBTREE     *btree;
   /*---(done)--------------*/
};



struct cFILE {
   /*---(master)------------*/
   char        type;
   char        name        [LEN_NAME];
   char        sort        [LEN_NAME];
   /*---(stats)-------------*/
   int         lines;
   int         empty;
   int         docs;
   int         debug;
   int         code;
   int         slocl;
   /*---(parent)------------*/
   tPROJ      *proj;
   /*---(files)-------------*/
   tFILE      *prev;
   tFILE      *next;
   /*---(tags)--------------*/
   tTAG       *head;
   tTAG       *tail;
   int         count;
   /*---(btree)-------------*/
   tBTREE     *btree;
   /*---(done)--------------*/
};



struct cTAG {
   /*---(master)-------------------------*/
   char        type;
   char        name        [LEN_NAME];
   int         line;
   char        hint        [3];
   char        image       [10];
   char        desc        [40];
   char        ready;
   /*---(positioning)--------------------*/
   char        oneline;                 /* return type and name on same line  */
   /*---(line counts)--------------------*/
   int         lines;
   int         empty;
   int         docs;
   int         debug;
   int         code;
   int         slocl;
   /*---(group one outputs)--------------*/
   char        scope;      /* 1st sub */
   char        rtype;
   char        psize;
   char        tsize;      /* 2nd sub */
   char        dsize;
   char        ssize;
   char        lsize;      /* 3rd sub */
   char        csize;
   char        rsize;
   int         isize;
   char        msize;
   /*---(group two outputs)-----------*/
   char        Lsize;      /* 1st sub */
   char        Gsize;
   char        Fsize;      /* 2nd sub */
   char        Isize;
   char        Csize;
   char        Ysize;
   char        Msize;
   char        Rflag;      /* 3rd sub */
   char        Wflag;
   char        Lflag;
   char        Sflag;
   /*---(group three outputs)---------*/
   char        Dstyle;     /* 1st sub */
   char        Dmacro;
   char        Dmatch;
   char        Nsize;      /* 2nd sub */
   char        Osize;
   char        Wsize;
   char        Zsize;
   char        Pstyle;     /* 3rd sub */
   char        Esize;
   char        Xsize;
   /*---(parent)------------*/
   tFILE      *file;
   /*---(tags)--------------*/
   tTAG       *prev;
   tTAG       *next;
   tWORK      *work;
   /*---(extern)------------*/
   tYLIB      *head;
   tYLIB      *tail;
   int         count;
   /*---(btree)-------------*/
   tBTREE     *btree;
   /*---(done)--------------*/
};

struct cYLIB {
   /*---(master)-------------------------*/
   char        name        [LEN_NAME];
   int         line;
   /*---(tags)--------------*/
   tTAG       *tag;
   tYLIB      *tprev;
   tYLIB      *tnext;
   /*---(ylib)--------------*/
   tEXTERN    *ylib;
   tYLIB      *eprev;
   tYLIB      *enext;
   /*---(done)--------------*/
};

struct cWORK {
   /*---(positioning)--------------------*/
   int         beg;
   int         end;
   /*---(group one working)--------------*/
   char        nparam;
   int         lvars;
   int         choices;
   int         returns;
   int         indent;
   int         memories;
   /*---(group two working)-----------*/
   int         lcalls;
   int         gcalls;
   int         ecalls;
   int         depth;
   int         funcs;
   int         intern;
   int         mystry;
   int         cstd;
   int         ylibs;
   int         xfuncs;
   int         reads;
   int         writes;
   int         opengl;
   int         ncurses;
   int         process;
   int         scalls;
   int         recurse;
   /*---(group three working)---------*/
   int         dcount;                    /* uses of DEBUG_ in function       */
   int         dlong;                     /* long style yLOG_                 */
   int         dshort;                    /* short style yLOG_                */
   int         denterc;                   /* enter count - externals          */
   int         dexitc;                    /* exit  count - externals          */
   int         dfree;                     /* yLOG_ without DEBUG_ protection  */
   int         window;                    /* window manager/x11 calls         */
   int         myx;
   /*---(done)------------------------*/
};





/*----------+-----------+-----------+-----------+-----------+-----------+-----*/
struct      cBTREE {
   /*---(information)-------*/
   char        n;
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
#define     B_PROJ      'T'
#define     B_FILES     'f'
#define     B_TAGS      't'
#define     B_PROTO     'p'
#define     B_EXTERN    'e'
#define     B_UNIT      'U'
#define     B_ALL       "TftpeU"



/*----------+-----------+-----------+-----------+-----------+-----------+-----*/
struct      cEXTERN {
   /*---(information)-------*/
   char        type;
   char        name        [LEN_NAME];
   int         uses;
   char        more;
   /*---(ylib)--------------*/
   tYLIB      *head;
   tYLIB      *tail;
   int         count;
   /*---(btree)-------------*/
   tBTREE     *btree;
   /*---(done)--------------*/
};

extern int   g_depth;
extern char  g_path    [LEN_LABEL];



extern char      unit_answer [LEN_RECD];


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        poly_cats_tagsumm       (tTAG *a_tag);

char        poly_files_init         (void);
char        poly_files_wrap         (void);
tFILE*      poly_files_new          (void);
char        poly_files_add          (tPROJ *a_proj, char *a_name, char a_type, tFILE **a_file);
char        poly_files_purge_proj   (tPROJ *a_proj);
char        poly_files_review       (tPROJ *a_proj);
char        poly_files_list         (void);
tFILE*      poly_files_search       (char *a_name);
char        poly_files_addtag       (tFILE *a_file, tTAG *a_tag);
char        poly_files_nexttag      (tFILE *a_file, tTAG **a_tag);
char*       poly_files__unit        (char *a_question, int n);

char        poly_tags_macro         (char *a_macro);
tTAG*       poly_tags_byline        (tFILE *a_file, int a_line);
char        poly_tags_init          (void);
char        poly_tags_purge_file    (tFILE *a_file);
char        poly_tags_wrap          (void);
char        poly_tags__hint         (int n, char *a_label);
char        poly_tags__wipe         (tTAG *a_dst);
tTAG*       poly_tags_new           (void);
char        poly_tags_add           (tFILE *a_file, char *a_name, char a_type, int a_line, tTAG **a_tag);
char        poly_tags_inventory     (tFILE *a_file);
char        poly_tags_readline      (tFILE *a_file, int *a_line, tTAG **a_tag);
char        poly_tags_review        (tFILE *a_file);
char        poly_tags_addylib       (tTAG *a_tag, tYLIB *a_ylib);
char*       poly_tags__unit         (char *a_question, int n);

char        poly_cats_flag          (char *a_label, int a_src, char *a_dst, char a_zero);
char        poly_cats_exists        (char *a_label, int a_src, char *a_dst, char a_zero);
char        poly_cats_exact         (char *a_label, int a_src, char *a_dst, char a_zero);
char        poly_cats_scaled        (char *a_label, int a_src, char *a_dst, char a_zero);
char        poly_cats_logic         (tTAG *a_tag, char a_type);
char        poly_cats_lines         (tFILE *a_file, tTAG *a_tag, char a_type);
char*       poly_cats__unit         (char *a_question, int n);

char        PROG_prepare            (void);
char        PROG_summarize          (tPROJ *x_proj);
char        PROG_report             (tPROJ *x_proj);
char        PROG__unit_quiet        (void);
char        PROG__unit_loud         (void);
char        PROG__unit_end          (void);

char        poly_extern_init        (void);
char        poly_extern_wrap        (void);
char        poly_extern__add        (char *a_name, char a_type, char a_more);
char        poly_extern_load        (void);
char        poly_extern_check       (char *a_name);
char        poly_extern_review      (void);
char        poly_extern_list        (void);
tEXTERN*    poly_extern_search      (char *a_name);
char        poly_extern_addylib     (tEXTERN *a_extern, tYLIB *a_ylib);
char*       poly_extern__unit       (char *a_question, int n);

char        poly_proto_init         (void);
char        poly_proto_add          (int a_file, char *a_name, char a_type, int a_line);


char        poly_btree_init         (char a_btree);
char        poly_btree_hook         (char a_btree, void *a_data, char *a_sort, tBTREE **a_link);
char        poly_btree_unhook       (tBTREE **a_link);
char        poly_btree_purge        (char a_btree);
int         poly_btree__depth       (int a_size);
int         poly_btree__span        (int a_levels);
char        poly_btree_dgnome       (char a_btree);
void*       poly_btree_first        (char a_btree);
void*       poly_btree_next         (char a_btree);
void*       poly_btree_entry        (char a_btree, int i);
int         poly_btree_count        (char a_btree);
char        poly_btree_build        (char a_btree);
char        poly_btree_prepare_all  (void);
char        poly_btree_purge_all    (void);
char        poly_btree_list         (char a_btree);
void*       poly_btree_search       (char a_btree, char *a_name);
char*       poly_btree__unit        (char a_btree, char *a_question, int i);

char        poly_proj_init          (void);
char        poly_proj_wrap          (void);
tPROJ*      poly_proj_new           (void);
char        poly_proj_add           (char *a_name, char *a_home, tPROJ **a_proj);
char        poly_proj_del           (tPROJ *a_proj);
char        poly_proj_here          (tPROJ **a_proj);
char        poly_proj_nextfile      (tPROJ *a_proj, tFILE **a_file);
char        poly_proj_prepare       (void);
char        poly_proj_system        (char *a_path);

char        poly_db_write           (void);
char        poly_db_read            (void);

char        poly_rptg_dump          (void);
char        poly_rptg_extern        (tEXTERN *a_extern);

char        poly_action_generate    (void);
char        poly_action_search      (void);
char        poly_action_update      (void);
char        poly_action_remove      (void);
char        poly_action_extern      (void);

tYLIB*      poly_ylib_new           (void);
char        poly_ylib_add           (tTAG *a_tag, tEXTERN *a_extern, int a_line, tYLIB **a_ylib);
char        poly_ylib_del           (tYLIB *a_ylib);
char        poly_ylib_purge_tag     (tTAG *a_tag);

