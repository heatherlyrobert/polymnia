/*============================[[ beg-of-code ]]===============================*/



/*===[[ ONE_LINERS ]]=========================================================*/
/*-------   --12345678  "123456789-123456789-123456789-123456789-123456789-123456789-"  */

#define     P_FOCUS     "DE (development environment)"
#define     P_NICHE     "ca (code anaylsis)"
#define     P_SUBJECT   "ansi-c code analysis"
#define     P_PURPOSE   "c language code-base navigation, research, and analysis"

#define     P_NAMESAKE  "polymnia-hymnos (many praises)"
#define     P_HERITAGE  "greek muse of divine hymns, poetry, dancing, geometry, grammer"
#define     P_IMAGERY   "beautiful woman wearing a veil and looking up at the heavens"
#define     P_REASON    "she is the muse of divine hymns (c is the divine language)"

#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT

#define     P_BASENAME  "polymnia"
#define     P_FULLPATH  "/usr/local/bin/polymnia"
#define     P_SUFFIX    "htags"
#define     P_CONTENT   "code navigation file"

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "small       (appoximately 1,000 slocl)"
#define     P_DEPENDS   "ySTR"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2019-01"

#define     P_VERMAJOR  "0.--, pre-production"
#define     P_VERMINOR  "0.8-, working out final issues"
#define     P_VERNUM    "0.8j"
#define     P_VERTXT    "extracted shared file read and parsing, and unit tested them"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"

/*-------   --12345678  "123456789-123456789-123456789-123456789-123456789-123456789-"  */
/*===[[ END ONE_LINERS ]]=====================================================*/



#define     P_SUMMARY   \
 "polymnia is a custom code analysis tool offering tag navigation for¦" \
 "vim-ide, detailed function complexity analysis, and code-base wide¦" \
 "reporting and research for the one-true language (c) ;)¦"

#define     P_ASSUME    \
 "-- all applications are only written in c¦" \
 "-- coding practices follow my standards (allowing deeper analysis)¦" \
 "-- program headers and key information are in standard named macros¦" \
 "-- all code stored in system, monkey, and member directories¦" \
 "-- zero configuration ;) written for me, by me, for only me¦"

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
#include    <dirent.h>
#include    <sys/stat.h>


/*---(heatherly made)--------------------*/
#include    <yURG.h>         /* CUSTOM  heatherly urgent processing           */
#include    <yLOG.h>         /* CUSTOM  heatherly program logging             */
#include    <ySTR.h>         /* CUSTOM  heatherly string handling             */



#define      LEN_HUND          100



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
typedef     struct      dirent      tDIRENT;
typedef     struct      stat        tSTAT;

typedef     struct      cMY         tMY;
typedef     struct      cPROJ       tPROJ;
typedef     struct      cFILE       tFILE;
typedef     struct      cFUNC       tFUNC;
typedef     struct      cYLIB       tYLIB;
typedef     struct      cWORK       tWORK;

typedef     struct      cBTREE      tBTREE;
typedef     struct      cEXTERN     tEXTERN;



#define     MODE_HTAGS        'h'
#define     MODE_ABOUT        'a'
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
#define     MODE_LIBUSE       'L'
#define     MODE_DUMP         'd'

#define     RPTG_TITLES       't'
#define     RPTG_NOTITLES     '-'
#define     RPTG_TREEVIEW     'T'


#define     FILTER_NONE       '-'
#define     FILTER_DEBUG      'D'
#define     FILTER_PARAMS     'p'
#define     FILTER_DATA       'd'
#define     FILTER_LINUX      'l'


#define     F_CTAGS     "polymnia.ctag"
#define     F_CFLOW     "polymnia.cflow"
#define     F_MYSTRY    "polymnia.mystry"
#define     F_VARS      "polymnia.vars"
#define     F_EXTERN    "/var/lib/polymnia/external.txt"
#define     F_EXTFUNCS  "/var/lib/polymnia/ext_funcs.txt"
#define     F_EXTMACRO  "/var/lib/polymnia/ext_macro.txt"
#define     F_EXTLABEL  "/var/lib/polymnia/ext_label.txt"
#define     F_DB        "/var/lib/polymnia/polymnia.db"



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
   char        version     [LEN_HUND];      /* version string                 */
   char        g_mode;                 /* run-time mode                       */
   char        g_titles;               /* use/hide report titles              */
   char        g_filter;               /* report filtering criteria           */
   /*---(filtering)-----------*/
   char        g_project   [LEN_RECD]; /* project name for filtering          */
   tPROJ      *g_proj;                 /* limit output to this project        */
   char        g_extern    [LEN_RECD]; /* name for focus/filtering            */
   char        g_libuse    [LEN_RECD]; /* extern library for filtering        */
   /*---(long-term files)-----*/
   char        n_db        [LEN_RECD]; /* name of database file               */
   FILE       *f_db;                   /* shared database of tags             */
   char        n_extern    [LEN_RECD]; /* name of external file               */
   FILE       *f_extern;               /* shared external function list       */
   /*---(working files)-------*/
   FILE       *f_code;                 /* current program source file         */
   FILE       *f_ctags;                /* ctags input file                    */
   FILE       *f_cflow;                /* cflow input file                    */
   FILE       *f_mystry;               /* local mystery external calls        */
   FILE       *f_vars;                 /* global/file variables               */
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
   /*---(overall)-----------*/
   char        name        [LEN_TITLE];
   char        header      [LEN_DESC];      /* flags on each header onelineer */
   /*---(master)------------*/
   char        focus       [LEN_DESC]; 
   char        niche       [LEN_DESC]; 
   char        subject     [LEN_TITLE];
   char        purpose     [LEN_HUND];
   /*---(greek)-------------*/
   char        namesake    [LEN_HUND];
   char        heritage    [LEN_HUND];
   char        imagery     [LEN_HUND];
   char        reason      [LEN_HUND];
   char        oneline     [LEN_HUND];
   /*---(location)----------*/
   char        homedir     [LEN_HUND];
   char        progname    [LEN_TITLE];
   char        fullpath    [LEN_HUND];
   char        suffix      [LEN_LABEL];
   char        content     [LEN_TITLE];
   /*---(system)------------*/
   char        systems     [LEN_HUND];
   char        language    [LEN_HUND];
   char        codesize    [LEN_DESC];
   char        depends     [LEN_HUND];
   /*---(author)------------*/
   char        author      [LEN_TITLE];
   char        created     [LEN_LABEL];
   /*---(versioning)--------*/
   char        vermajor    [LEN_HUND];
   char        verminor    [LEN_HUND];
   char        vernum      [LEN_LABEL];
   char        vertxt      [LEN_HUND];
   /*---(new stats interface)-*/
   int         funcs;
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
   char        name        [LEN_TITLE];
   char        sort        [LEN_TITLE];
   /*---(new stats interface)-*/
   int         counts      [MAX_COUNTS];    /* line counts                    */
   /*---(parent)------------*/
   tPROJ      *proj;
   /*---(files)-------------*/
   tFILE      *prev;
   tFILE      *next;
   /*---(tags)--------------*/
   tFUNC      *head;
   tFUNC      *tail;
   int         count;
   /*---(btree)-------------*/
   tBTREE     *btree;
   /*---(done)--------------*/
};


#define     MAX_STATS      50

#define     STATS_SINGLE   stats [ 0]
/*---(group one.a)--------------------*/
#define     STATS_SCOPE    stats [ 1]
#define     STATS_RTYPE    stats [ 2]
#define     STATS_PARAMS   stats [ 3]
#define     STATS_PTWO     stats [ 4]
#define     STATS_PNUM     stats [ 5]
#define     STATS_PROTO    stats [ 6]
/*---(group one.b)--------------------*/
#define     STATS_TOTAL    stats [ 7]
#define     STATS_DEBUG    stats [ 8]
#define     STATS_SLOCL    stats [ 9]
/*---(group one.c)--------------------*/
#define     STATS_LVARS    stats [10]
#define     STATS_FVARS    stats [11]
#define     STATS_GVARS    stats [12]
/*---(group one.d)--------------------*/
#define     STATS_CHOICE   stats [13]
#define     STATS_RETURN   stats [14]
#define     STATS_INDENT   stats [15]
#define     STATS_MEMORY   stats [16]
/*---(group two.a)--------------------*/
#define     STATS_ACALLS   stats [17]
#define     STATS_LCALLS   stats [18]
#define     STATS_GCALLS   stats [19]
#define     STATS_ECALLS   stats [20]
#define     STATS_RECURS   stats [21]
/*---(group two.b)--------------------*/
#define     STATS_FUNCS    stats [22]
#define     STATS_DFUNCS   stats [23]
#define     STATS_RFUNCS   stats [24]
#define     STATS_LFUNCS   stats [25]
#define     STATS_GFUNCS   stats [26]
#define     STATS_CSTD     stats [27]
#define     STATS_YLIB     stats [28]
#define     STATS_OFUNCS   stats [29]
#define     STATS_MYSTRY   stats [30]
/*---(group two.c)--------------------*/
#define     STATS_READ     stats [31]
#define     STATS_WRITE    stats [32]
#define     STATS_SYSTEM   stats [33]
/*---(group two.d)--------------------*/
#define     STATS_NCURSE   stats [34]
#define     STATS_OPENGL   stats [35]
#define     STATS_WINDOW   stats [36]
#define     STATS_MYX      stats [37]
/*---(group three.a)------------------*/
#define     STATS_DSTYLE   stats [38]
#define     STATS_DMACRO   stats [39]
#define     STATS_DMATCH   stats [40]
#define     STATS_DWARN    stats [41]
/*---(group three.b)------------------*/
#define     STATS_PUSE     stats [42]
#define     STATS_FUSE     stats [43]
#define     STATS_GUSE     stats [44]
#define     STATS_MUSE     stats [45]
#define     STATS_YUSE     stats [46]
#define     STATS_OUSE     stats [47]



struct cFUNC {
   /*---(master)-------------------------*/
   char        type;                        /* 'f' normal, '_' separator      */
   char        name        [LEN_TITLE];     /* c function name                */
   int         line;                        /* line in source file            */
   char        hint        [LEN_SHORT];     /* two-char navigation hint       */
   char        purpose     [LEN_DESC];      /* short description of purpose   */
   char        ready;
   /*---(new stats interface)------------*/
   int         counts      [MAX_COUNTS];    /* line counts                    */
   char        stats       [MAX_STATS];     /* statistics                     */
   /*---(parent)------------*/
   tFILE      *file;
   /*---(tags)--------------*/
   tFUNC      *prev;
   tFUNC      *next;
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
   char        name        [LEN_TITLE];
   int         line;
   /*---(tags)--------------*/
   tFUNC      *tag;
   tYLIB      *tprev;
   tYLIB      *tnext;
   /*---(ylib)--------------*/
   tEXTERN    *ylib;
   tYLIB      *eprev;
   tYLIB      *enext;
   /*---(done)--------------*/
};

/*---(location)-----------------------*/
#define     WORK_BEG       work->beg
#define     WORK_END       work->end
/*---(group one.b)--------------------*/
#define     WORK_PARAMS    work->temp  [ 0]
/*---(group one.c)--------------------*/
#define     WORK_LVARS     work->temp  [ 1]
#define     WORK_FVARS     work->temp  [ 2]
#define     WORK_GVARS     work->temp  [ 3]
/*---(group one.d)--------------------*/
#define     WORK_CHOICE    work->temp  [ 4]
#define     WORK_RETURN    work->temp  [ 5]
#define     WORK_INDENT    work->temp  [ 6]
#define     WORK_MEMORY    work->temp  [ 7]
/*---(group two.a)--------------------*/
#define     WORK_ACALLS    work->temp  [ 8]
#define     WORK_LCALLS    work->temp  [ 9]
#define     WORK_GCALLS    work->temp  [10]
#define     WORK_ECALLS    work->temp  [11]
#define     WORK_RECURS    work->temp  [12]
/*---(group two.b)--------------------*/
#define     WORK_FUNCS     work->temp  [13]
#define     WORK_DFUNCS    work->temp  [14]
#define     WORK_RFUNCS    work->temp  [15]
#define     WORK_LFUNCS    work->temp  [16]
#define     WORK_GFUNCS    work->temp  [17]
#define     WORK_CSTD      work->temp  [18]
#define     WORK_YLIB      work->temp  [19]
#define     WORK_OFUNCS    work->temp  [20]
#define     WORK_MYSTRY    work->temp  [21]
/*---(group two.c)--------------------*/
#define     WORK_INPUT     work->temp  [22]
#define     WORK_TREAD     work->temp  [23]
#define     WORK_BREAD     work->temp  [24]
#define     WORK_OUTPUT    work->temp  [25]
#define     WORK_TWRITE    work->temp  [26]
#define     WORK_BWRITE    work->temp  [27]
#define     WORK_PROCS     work->temp  [28]
#define     WORK_OPSYS     work->temp  [29]
#define     WORK_FILESYS   work->temp  [30]
/*---(group two.d)--------------------*/
#define     WORK_NCURSE    work->temp  [31]
#define     WORK_OPENGL    work->temp  [32]
#define     WORK_WINDOW    work->temp  [33]
#define     WORK_MYX       work->temp  [34]
/*---(group three.a)------------------*/
#define     WORK_DCOUNT    work->temp  [35]
#define     WORK_DLONG     work->temp  [36]
#define     WORK_DSHORT    work->temp  [37]
#define     WORK_DENTER    work->temp  [38]
#define     WORK_DEXIT     work->temp  [39]
#define     WORK_DFREE     work->temp  [40]
/*---(group three.b)------------------*/
#define     WORK_PUSE      work->temp  [41]
#define     WORK_FUSE      work->temp  [42]
#define     WORK_GUSE      work->temp  [43]
#define     WORK_MUSE      work->temp  [44]
#define     WORK_YUSE      work->temp  [45]
#define     WORK_OUSE      work->temp  [46]



#define     MAX_TEMPS      50
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
#define     B_FUNCS      't'
#define     B_PROTO     'p'
#define     B_EXTERN    'e'
#define     B_UNIT      'U'
#define     B_ALL       "TftpeU"



/*----------+-----------+-----------+-----------+-----------+-----------+-----*/
struct      cEXTERN {
   /*---(information)-------*/
   char        lib         [LEN_TITLE];
   char        name        [LEN_TITLE];
   int         line;
   char        type;
   char        cat;
   char        sub;
   int         uses;
   /*---(ylib)--------------*/
   tYLIB      *head;
   tYLIB      *tail;
   int         count;
   /*---(btree)-------------*/
   tBTREE     *btree;
   /*---(done)--------------*/
};

extern int   g_depth;
extern char  g_path    [LEN_HUND];



extern char      unit_answer [LEN_RECD];



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        poly_files_init         (void);
char        poly_files_wrap         (void);
tFILE*      poly_file_new           (void);
char        poly_file_add           (tPROJ *a_proj, char *a_name, char a_type, tFILE **a_file);
char        poly_files_del          (tFILE **a_file);
char        poly_files_purge_proj   (tPROJ *a_proj);
char        poly_files_review       (tPROJ *a_proj);
char        poly_files_list         (void);
tFILE*      poly_files_search       (char *a_name);
char        poly_file_line          (tFILE *a_file, char a_style, int a, int b, char a_print);
/*---(tags)-----------------*/
/*---(unittest)-------------*/
char*       poly_file__unit         (char *a_question, int n);

char        poly_tags_inventory     (tFILE *a_file);
char        poly_tags_addylib       (tFUNC *a_tag, tYLIB *a_ylib);
char*       poly_tags__unit         (char *a_question, int n);

char        poly_cats_counts_clear  (int  a_counts [MAX_COUNTS]);
char        poly_cats_stats_clear   (char a_stats  [MAX_STATS]);
char        poly_cats_flag          (char *a_label, int a_src, char *a_dst, char a_zero);
char        poly_cats_exists        (char *a_label, int a_src, char *a_dst, char a_zero);
char        poly_cats_exact         (char *a_label, int a_src, char *a_dst, char a_zero);
char        poly_cats_scaled        (char *a_label, int a_src, char *a_dst, char a_zero);
char        poly_cats_logic         (tFUNC *a_tag, char a_type);
char        poly_cats__group_1a     (tFUNC *a_func);
char        poly_cats__group_1b     (tFUNC *a_func);
char        poly_cats__group_1c     (tFUNC *a_func);
char        poly_cats__group_1d     (tFUNC *a_func);
char        poly_cats__complexity   (char a_style, tFUNC *a_func, char a_update, char *a_out);
char        poly_cats__group_2a     (tFUNC *a_func);
char        poly_cats__group_2b     (tFUNC *a_func);
char        poly_cats__group_2c     (tFUNC *a_func);
char        poly_cats__group_2d     (tFUNC *a_func);
char        poly_cats__integration  (char a_style, tFUNC *a_func, char a_update, char *a_out);
char        poly_cats__group_3a     (tFUNC *a_func);
char        poly_cats__watchpoints  (char a_style, tFUNC *a_func, char a_update, char *a_out);
char        poly_cats_function      (tFUNC *a_func);
char*       poly_cats_header        (int n, char *a_title, int a_curr, int a_total);
char*       poly_cats_database      (tFUNC *a_func);
char*       poly_cats_comment       (tFUNC *a_func);
char*       poly_cats_full          (tFUNC *a_func, char *a_out);
char*       poly_cats__unit         (char *a_question, int n);

char        PROG_prepare            (void);
char        PROG_summarize          (tPROJ *x_proj);
char        PROG__unit_quiet        (void);
char        PROG__unit_loud         (void);
char        PROG__unit_end          (void);

char        poly_extern_init        (void);
char        poly_extern_wrap        (void);
char        poly_extern__add        (char *a_lib, char *a_name, int a_line, char a_type);
char        poly_extern__load_read  (int *a_line, char *a_recd);
char        poly_extern__load_parse (char *a_recd, char *a_lib, char *a_name, int *a_pos, char *a_type);
char        poly_extern_load        (void);
char        poly_extern__read       (char *a_curr);
char        poly_extern__parse      (char *a_curr, char *a_func, char *a_file, int *a_line);
char        poly_extern__pointers   (char *a_func, char *a_file, int a_line, tFUNC **a_src, tFUNC **a_dst, tEXTERN **a_ext);
char        poly_extern__tally      (tFUNC *a_src, tFUNC *a_dst, tEXTERN *a_ext, int a_line);
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
char        poly_proj_del           (tPROJ **a_proj);
char        poly_proj_purge         (void);
char        poly_proj_here          (tPROJ **a_proj);
/*---(files)----------------*/
int         poly_proj_file_count    (tPROJ *a_proj);
char        poly_proj_file_hook     (tPROJ *a_proj, tFILE *a_file);
char        poly_proj_file_unhook   (tFILE *a_file);
char        poly_proj_nextfile      (tPROJ *a_proj, tFILE **a_file);
char        poly_proj_prepare       (void);
char        poly_proj_system        (char *a_path);
char        poly_proj__headerline   (char *a_header, char n, char a_abbr, char *a_text, char a_min, char a_low, char a_high, char a_max);
char        poly_proj_header        (tPROJ *a_proj);
char        poly_proj_line          (tPROJ *a_proj, char a_style, int c, char a_print);

char        poly_db_write           (void);
char        poly_db_read            (void);

char        poly_rptg_projects      (void);
char        poly_rptg_htags         (tPROJ *x_proj);
char        poly_rptg_dump          (void);
char        poly_rptg_extern        (tEXTERN *a_extern);

char        poly_action_generate    (void);
char        poly_action_search      (void);
char        poly_action_update      (void);
char        poly_action_about       (void);
char        poly_action_remove      (void);
char        poly_action_extern      (void);
char        poly_action_libuse      (void);

tYLIB*      poly_ylib_new           (void);
char        poly_ylib_add           (tFUNC *a_tag, tEXTERN *a_extern, int a_line, tYLIB **a_ylib);
char        poly_ylib_del           (tYLIB *a_ylib);
char        poly_ylib_purge_tag     (tFUNC *a_tag);

/*---(support)--------------*/
char        poly_debug__macro       (char *a_macro);
/*---(checking)-------------*/
char        poly_debug__counts      (tFILE *a_file, tFUNC *a_func, char a_type);
char        poly_debug_line         (tFILE *a_file, tFUNC *a_func, char *a_recd);
/*---(stats)----------------*/
char        poly_debug_cflow        (tFUNC *a_func, char a_type, char a_more);
char        poly_debug_function     (tFUNC *a_func);
/*---(unittest)-------------*/
char        poly_debug__fake        (tFUNC *a_func, int a_return, int a_intern, int a_ylib);
char*       poly_debug__unit        (char *a_question, int i);

/*---(support)--------------*/
char        poly_func__wipe         (tFUNC *a_dst);
char        poly_func__hint         (int n, char *a_label);
/*---(memory)---------------*/
char        poly_func_new           (tFUNC **a_func);
char        poly_func__free         (tFUNC **a_func);
/*---(hooking)--------------*/
char        poly_func_hook          (tFILE *a_file, tFUNC *a_tag);
char        poly_func__unhook       (tFUNC *a_tag);
char        poly_func_count         (tFILE *a_file);
/*---(existance)------------*/
char        poly_func_add           (tFILE *a_file, char *a_name, char a_type, int a_line, tFUNC **a_func);
char        poly_func_del           (tFUNC **a_tag);
/*---(position)-------------*/
char        poly_func_enter         (tFUNC *a_func, int a_line);
char        poly_func_exit          (tFUNC *a_func, int a_line);
char        poly_func_inside        (tFUNC *a_func);
char        poly_func_search        (tFILE *a_file, int a_line, tFUNC **a_func);
/*---(program)--------------*/
char        poly_func_init          (void);
char        poly_func_purge         (tFILE *a_file);
char        poly_func_wrap          (void);
/*---(source)---------------*/
char        poly_func_purpose       (tFUNC *a_func, char *a_recd);
char        poly_func_return        (tFUNC *a_func, char *a_recd, char *a_prev);
char        poly_func_params        (tFUNC *a_func, char *a_recd);
/*---(reporting)------------*/
char*       poly_func_line          (tFUNC *a_func, char a_style, int a, int b, int c, char a_print);
/*---(unittest)-------------*/
char*       poly_func__unit         (char *a_question, int i);



char        poly_code__unquote      (char *a_dst, char *a_src, int a_max);
char        poly_code__oneliners    (tFILE *a_file, char *a_recd);
char        poly_code__reserved     (tFILE *a_file, tFUNC *a_func, char *a_recd);
char        poly_code__indent       (tFUNC *a_func, char *a_recd);
char        poly_code_function      (tFUNC *a_func, char *a_recd, char *a_prev);
char        poly_code_nextfunc      (tFILE *a_file, tFUNC **a_func);
char        poly_code__open         (tFILE *a_file);
char        poly_code__read         (int *a_line, char *a_curr, char *a_prev);
char        poly_code__close        (void);
char        poly_code__before       (tFILE *a_file, tFUNC **a_func);
char        poly_code__current      (tFILE *a_file, int a_line, tFUNC *a_func, char *a_curr, char *a_prev);
char        poly_code__after        (tFILE *a_file, int a_line, tFUNC *a_func, char *a_curr);
char        poly_code_review        (tFILE *a_file);


char        poly_tags__create       (tFILE *a_file);
char        poly_tags__cleanup      (void);
char        poly_tags__handler      (tFILE *a_file, char *a_recd);
char        poly_tags_inventory     (tFILE *a_file);


char        poly_shared_open        (char a_type, char *a_focus);
char        poly_shared_close       (char a_type);
char        poly_shared_read        (char a_type, int *a_line, char *a_curr, char *a_prev);
char        poly_shared_parse_tags  (char *a_curr, char *a_name, char *a_type, int *a_line, char *a_file);
char        poly_shared_parse_flow  (char *a_curr, char *a_name, char *a_defn, int *a_line, char *a_file);
char*       poly_shared__unit       (char *a_question);


char        poly_vars_init          (void);
char        poly_vars__push         (tFILE *a_file, char *a_name, char a_type);
char        poly_vars__pop_file     (void);
char        poly_vars_reset         (tFUNC *a_func);
char        poly_vars__extern_find  (tFUNC *a_func, int a_line, char *a_recd, char a_act);
char        poly_vars_find          (tFUNC *a_func, int a_line, char *a_recd, char a_act);
char        poly_vars_inventory     (tFILE *a_file);
char*       poly_vars__unit         (char *a_question, int i);


