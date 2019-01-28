/*===============================[[ beg-code ]]===============================*/

/*===[[ HEADER ]]=============================================================*/
/*
 *   focus         : c-ide
 *   niche         : code analysis
 *   heritage      : polymnia-hymnos (muse of divine hymns, dance, and geometry)
 *   purpose       : c language code-base navigation, research, and analysis
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
#define   VER_NUM       "0.7d"
#define   VER_TXT       "fixed extern vs library symbol conflict in analysis"



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
 *     b gcalls (global references count)
 *     a lcalls (local/file references count)
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
 *     j ptwo   (parameter with double pointer)
 *     k pnum   (parameter is pointer to number)
 *
 *
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
#define     MODE_RPTG         'r'
#define     MODE_SEARCH       's'
#define     MODE_WRITE        'w'
#define     MODE_REMOVE       'R'
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
#define     FILTER_DEBUG      'D'
#define     FILTER_PARAMS     'p'
#define     FILTER_DATA       'd'
#define     FILTER_LINUX      'l'


#define     F_DB        "/var/lib/polymnia/polymnia.db"
#define     F_CTAGS     "polymnia.ctag"
#define     F_CFLOW     "polymnia.cflow"
#define     F_EXTERN    "/var/lib/polymnia/external.txt"
#define     F_MYSTRY    "polymnia.mystry"



#define     MAX_COUNTS     10
#define     COUNT_PROJS    counts [0]
#define     COUNT_FILES    counts [1]
#define     COUNT_FUNCS    counts [2]
#define     COUNT_LINES    counts [3]
#define     COUNT_EMPTY    counts [4]
#define     COUNT_DOCS     counts [5]
#define     COUNT_DEBUG    counts [6]
#define     COUNT_CODE     counts [7]
#define     COUNT_SLOCL    counts [8]



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
   /*---(new stats interface)-*/
   int         counts      [MAX_COUNTS];    /* line counts                    */
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
   /*---(new stats interface)-*/
   int         ntags;
   int         counts      [MAX_COUNTS];    /* line counts                    */
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
   /*---(new stats interface)-*/
   int         counts      [MAX_COUNTS];    /* line counts                    */
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


#define     MAX_STATS      50

#define     STATS_SINGLE   stats [0]

#define     STATS_SCOPE    stats [1]
#define     STATS_RTYPE    stats [2]
#define     STATS_PARAMS   stats [3]
#define     STATS_TOTAL    stats [4]
#define     STATS_DEBUG    stats [5]
#define     STATS_SLOCL    stats [6]
#define     STATS_LOCALS   stats [7]
#define     STATS_CHOICE   stats [8]
#define     STATS_RETURN   stats [9]
#define     STATS_INDENT   stats [10]
#define     STATS_MEMORY   stats [11]

#define     STATS_GCALLS   stats [12]
#define     STATS_LCALLS   stats [13]
#define     STATS_FUNCS    stats [14]
#define     STATS_INTERN   stats [15]
#define     STATS_CSTD     stats [16]
#define     STATS_YLIB     stats [17]
#define     STATS_MSTRY    stats [18]
#define     STATS_READ     stats [19]
#define     STATS_WRITE    stats [20]
#define     STATS_SYSTEM   stats [21]
#define     STATS_RECURS   stats [22]

#define     STATS_DSTYLE   stats [23]
#define     STATS_DMACRO   stats [24]
#define     STATS_DMATCH   stats [25]
#define     STATS_NCURSE   stats [26]
#define     STATS_OPENGL   stats [27]
#define     STATS_WINDOW   stats [28]
#define     STATS_MYX      stats [29]
#define     STATS_PROTO    stats [30]
#define     STATS_ECALLS   stats [31]
#define     STATS_PTWO     stats [32]
#define     STATS_PNUM     stats [33]



struct cTAG {
   /*---(master)-------------------------*/
   char        type;
   char        name        [LEN_NAME];
   int         line;
   char        hint        [3];
   char        image       [10];
   char        desc        [40];
   char        ready;
   /*---(new stats interface)------------*/
   int         counts      [MAX_COUNTS];    /* line counts                    */
   char        stats       [MAX_STATS];     /* statistics                     */
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

#define     WORK_BEG       work->beg
#define     WORK_END       work->end

#define     WORK_PARAMS    work->temp  [0]
#define     WORK_LOCALS    work->temp  [1]
#define     WORK_CHOICE    work->temp  [2]
#define     WORK_RETURN    work->temp  [3]
#define     WORK_INDENT    work->temp  [4]
#define     WORK_MEMORY    work->temp  [5]

#define     WORK_GCALLS    work->temp  [6]
#define     WORK_LCALLS    work->temp  [7]
#define     WORK_FUNCS     work->temp  [8]
#define     WORK_INTERN    work->temp  [9]
#define     WORK_CSTD      work->temp  [10]
#define     WORK_YLIB      work->temp  [11]
#define     WORK_MYSTRY    work->temp  [12]
#define     WORK_INPUT     work->temp  [13]
#define     WORK_READ      work->temp  [14]
#define     WORK_BREAD     work->temp  [15]
#define     WORK_OUTPUT    work->temp  [16]
#define     WORK_WRITE     work->temp  [17]
#define     WORK_BWRITE    work->temp  [18]
#define     WORK_PROCS     work->temp  [19]
#define     WORK_SYSTEM    work->temp  [20]
#define     WORK_FILESYS   work->temp  [21]
#define     WORK_RECURS    work->temp  [22]

#define     WORK_DCOUNT    work->temp  [23]
#define     WORK_DLONG     work->temp  [24]
#define     WORK_DSHORT    work->temp  [25]
#define     WORK_DENTER    work->temp  [26]
#define     WORK_DEXIT     work->temp  [27]
#define     WORK_DFREE     work->temp  [28]
#define     WORK_NCURSE    work->temp  [29]
#define     WORK_OPENGL    work->temp  [30]
#define     WORK_MYX       work->temp  [31]
#define     WORK_WINDOW    work->temp  [32]
#define     WORK_ECALLS    work->temp  [33]




#define     MAX_TEMPS      35
struct cWORK {
   /*---(positioning)--------------------*/
   int         beg;
   int         end;
   int         temp        [MAX_TEMPS];
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
extern char  g_path    [LEN_FULL];



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

char        poly_cats_counts_clear  (int  a_counts [MAX_COUNTS]);
char        poly_cats_stats_clear   (char a_stats  [MAX_STATS]);
char        poly_cats_flag          (char *a_label, int a_src, char *a_dst, char a_zero);
char        poly_cats_exists        (char *a_label, int a_src, char *a_dst, char a_zero);
char        poly_cats_exact         (char *a_label, int a_src, char *a_dst, char a_zero);
char        poly_cats_scaled        (char *a_label, int a_src, char *a_dst, char a_zero);
char        poly_cats_logic         (tTAG *a_tag, char a_type);
char        poly_cats_lines         (tFILE *a_file, tTAG *a_tag, char a_type);
char*       poly_cats__unit         (char *a_question, int n);

char        PROG_prepare            (void);
char        PROG_summarize          (tPROJ *x_proj);
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
char        poly_proj_purge         (void);
char        poly_proj_here          (tPROJ **a_proj);
char        poly_proj_nextfile      (tPROJ *a_proj, tFILE **a_file);
char        poly_proj_prepare       (void);
char        poly_proj_system        (char *a_path);

char        poly_db_write           (void);
char        poly_db_read            (void);

char        poly_rptg_htags         (tPROJ *x_proj);
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

