/*============================[[ beg-of-code ]]===============================*/
#ifndef POLYMNIA
#define POLYMNIA yes



/*===[[ ONE_LINERS ]]=========================================================*/
/*-------   --12345678  "123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-"  */

#define     P_FOCUS     "DE (development environment)"
#define     P_NICHE     "ca (code anaylsis)"
#define     P_SUBJECT   "ansi-c analysis and research"
#define     P_PURPOSE   "pervasive and detailed ansi-c code analysis, research, and navigation"

#define     P_NAMESAKE  "polymnia-hymnos (many praises)"
#define     P_PRONOUNCE "poh·lee·mih·nee·uh hihm·nohs"
#define     P_HERITAGE  "greek muse of divine hymns, poetry, dancing, geometry, grammer"
#define     P_BRIEFLY   "hymns, dancing, and geometry"
#define     P_IMAGERY   "beautiful woman wearing a veil and looking up at the heavens"
#define     P_REASON    "she is the muse of divine hymns (c is the divine language)"

#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT

#define     P_HOMEDIR   "/home/system/polymnia.muse_of_coding_structure"
#define     P_BASENAME  "polymnia"
#define     P_FULLPATH  "/usr/local/bin/polymnia"
#define     P_SUFFIX    "htags"
#define     P_CONTENT   "code navigation file"

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_COMPILER  "gcc 5.3.0"
#define     P_CODESIZE  "moderate    (appoximately 2,000 to 10,000 slocl)"
#define     P_DEPENDS   "ySTR,yJOBS,ySORT,yREGEX"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2019-01"

#define     P_VERMAJOR  "1.--, working excellent, keep improving"
#define     P_VERMINOR  "1.0-, move further to yJOBS"
#define     P_VERNUM    "1.0c"
#define     P_VERTXT    "added unit test SCRP format with terse labels handling for tags"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"

/*-------   --12345678  "123456789-123456789-123456789-123456789-123456789-123456789-"  */
/*===[[ END ONE_LINERS ]]=====================================================*/

/*3456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789- */
#define     P_ITCH      "itch¦" \
   "i am growing and have a large, evolving code-base.  the results can be¦" \
   "chaotic.  i need to make sense of it all, identify potential troubles,¦" \
   "track inter-dependencies, and help isolate troubles very quickly.¦"

/*3456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789- */
#define     P_EXISTS    "exists¦" \
   "there are fantastic tools, but they change, devolve, and overbuild.¦" \
   "i need a targeted tool that finds my personal weaknesses and does¦" \
   "not include a kitchen sink, no say in development, and weird licensing.¦"

/*3456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789- */
#define     P_AVOID     "avoid¦" \
   "polymnia will not replace or compete with lint, valgrind, and other¦" \
   "detailed code analyis.  it is meant to supplement and help with larger¦" \
   "troubles and larger context.  i am sure many ide's do this well.¦"

/*3456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789- */
#define     P_SCRATCH   "scratch¦" \
   "code navigation and analysis can mean many things, but i am specifically¦" \
   "targeting predictive statistics for complexity, integration points, and¦" \
   "personal blind-spots to help me manage a large code-base by myself.¦"

/*3456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789- */
#define     P_SUMMARY   "summary¦"\
  "polymnia is a custom code analysis tool offering tag navigation for¦" \
  "vim-ide, detailed function complexity analysis, and code-base wide¦" \
  "reporting and research for the one-true language (c) ;)¦"

/*3456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789- */
#define     P_ASSUME    "assume¦" \
   "-- all applications are only written in c (nearly ansi-c)¦" \
   "-- file naming follows my standards (headers, source, and units)¦" \
   "-- coding practices follow my standards (allowing deeper analysis)¦" \
   "-- program headers and key information are in standard named macros¦" \
   "-- zero configuration ;) written for me, by me, for only me¦"

/*3456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789- */
#define     P_GREEK     "greek heritage¦" \
  "polymnia-hymnos (many praises) is the muse and protector of divine hymns¦" \
  "and lyric poetry, inventor of the lyre, patron of dancing, geometry, and¦" \
  "grammar.  the muses (mousai) are nine daughters of zeus and mnemosyne¦" \
  "(titan of memory) and are the goddesses of art, literature, and science.¦" \
  "they inspire creation, enthusiasm, and the creative impulses.  polymnia¦" \
  "is usually depicted wearing a veil and looking up to the heavens.¦"

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
#include    <yJOBS.h>             /* heatherly job execution and control      */
#include    <ySORT.h>             /* heatherly sorting and searching          */
#include    <yREGEX.h>       /* CUSTOM  heatherly regular expressions         */
#include    <yDLST_solo.h>   /* CUSTOM  heatherly regular expressions         */



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
typedef     struct      dirent      tDIRENT;
typedef     struct      stat        tSTAT;

typedef     struct      cMY         tMY;
typedef     struct      cAUDIT      tAUDIT;
typedef     struct      cPROJ       tPROJ;
typedef     struct      cFILE       tFILE;
typedef     struct      cFUNC       tFUNC;
typedef     struct      cYLIB       tYLIB;
typedef     struct      cWORK       tWORK;

typedef     struct      cBTREE      tBTREE;
typedef     struct      cELIB       tELIB;
typedef     struct      cEXTERN     tEXTERN;


/*---(modes)----------------*/
#define     POLY_NONE           '-'
#define     POLY_DATA           'd'
#define     POLY_RPTG           'r'
#define     POLY_BOTH           'B'
/*---(scopes)---------------*/
#define     POLY_FULL           '*'
#define     POLY_PROJ           'P'
#define     POLY_FILE           'I'
#define     POLY_FUNC           'F'
#define     POLY_EXTS           'E'
#define     POLY_VARS           'V'
#define     POLY_YLIB           'Y'
/*---(projects)-------------*/
#define     POLY_PROJS          'p'
#define     POLY_GREEK          'g'
#define     POLY_ONELINE        'o'

/*
 *  incomming-------------------------------
 *  
 *  v = verify
 *  b = register  = verify and register
 *  i = install   = verify, install, register
 *  u = update    = verify and install (no register)
 *
 *  central---------------------------------
 *
 *  l = count/list
 *  ? = report
 *  c = check
 *  a = audit
 *  f = fix
 *  h = reload (system)
 *
 *  behind----------------------------------
 *
 *  ? = upload   (from central to elsewhere)
 *  ? = download (to central from elsewhere)
 *
 *  outgoing--------------------------------
 *
 *  q = withdraw  = unregister
 *  x = clear (quick single prune)
 *  r = remove (and unregister)
 *  e = extract (copy/one time)
 *
 *  execution--------------------------------
 *
 *  d = daemon
 *  p = prickly
 *  n = normal
 *  s = strict
 *
 *
 *
 */




#define     POLY_DATA_VALIDS    "-hwurLSRU"
#define     POLY_DATA_NONE      '-'
#define     POLY_DATA_HTAGS     'h'
#define     POLY_DATA_NEW       'w'
#define     POLY_DATA_UPDATE    'u'
#define     POLY_DATA_REMOVE    'r'
#define     POLY_DATA_LIBS      'L'
#define     POLY_DATA_SYSTEM    'S'
#define     POLY_DATA_REG       'R'
#define     POLY_DATA_UNREG     'U'

#define     POLY_RPTG_FILES     'I'
#define     POLY_RPTG_FUNCS     'F'

#define     POLY_RPTG_VALIDS    "-adefhopvyF"
#define     POLY_RPTG_NONE      '-'
#define     POLY_RPTG_ABOUT     'a'
#define     POLY_RPTG_DUMP      'd'
#define     POLY_RPTG_EXTERN    'e'
#define     POLY_RPTG_FUNC      'f'
#define     POLY_RPTG_HTAGS     'h'
#define     POLY_RPTG_ONELINE   'o'
#define     POLY_RPTG_PROJS     'p'
#define     POLY_RPTG_FILES     'F'
#define     POLY_RPTG_VARS      'v'
#define     POLY_RPTG_YLIB      'y'

#define     MODE_SEARCH       's'
#define     MODE_FILE         'F'
#define     MODE_PROTO        'p'

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
#define     F_UNITS     "polymnia.units"
#define     F_EXTERN    "/var/lib/polymnia/external.txt"
#define     F_EXTFUNCS  "/var/lib/polymnia/ext_funcs.txt"
#define     F_EXTMACRO  "/var/lib/polymnia/ext_macro.txt"
#define     F_EXTLABEL  "/var/lib/polymnia/ext_label.txt"
#define     F_DB        "/var/lib/polymnia/polymnia.db"
#define     F_WORLD     "/var/lib/polymnia/world.txt"



#define     MAX_COUNTS     15
#define     COUNT_PROJS    counts [ 0]
#define     COUNT_FILES    counts [ 1]
#define     COUNT_FUNCS    counts [ 2]
#define     COUNT_YLIBS    counts [ 3]
#define     COUNT_LINES    counts [ 4]
#define     COUNT_EMPTY    counts [ 5]
#define     COUNT_DOCS     counts [ 6]
#define     COUNT_DEBUG    counts [ 7]
#define     COUNT_CODE     counts [ 8]
#define     COUNT_SLOCL    counts [ 9]
#define     COUNT_TEXT     counts [10]
#define     COUNT_DATA     counts [11]
#define     COUNT_BSS      counts [12]



struct cAUDIT {
   char        name        [LEN_LABEL];
   char        vernum      [LEN_SHORT];
   int         counts      [MAX_COUNTS];    /* line counts                    */
};
extern      tAUDIT      g_audit;


struct cMY {
   /*---(yJOBS)----------------*/
   char        run_as;                      /* khronos, eos, heracles, ...    */
   char        run_mode;                    /* verify, install, audit, ...    */
   char        run_file    [LEN_PATH];      /* file to act on                 */
   int         run_uid;                     /* uid of person who launched     */
   long        runtime;
   /*---(runtime config)------*/
   char        version     [LEN_HUND];      /* version string                 */
   char        g_mode;                 /* switch for data/reporting           */
   char        g_scope;                /* scope for action (proj, file, ...)  */
   char        g_data;                 /* data handling mode                  */
   char        g_unit;                 /* include unit test metrics (slower)  */
   char        g_rptg;                 /* reporting mode                      */
   char        g_titles;               /* use/hide report titles              */
   char        g_filter;               /* report filtering criteria           */
   /*---(filtering)-----------*/
   int         g_projno;
   char        g_projname  [LEN_LABEL];/* project name for filtering          */
   tPROJ      *g_proj;                 /* limit output to this project        */
   int         g_fileno;
   char        g_filename  [LEN_LABEL];/* file name for filtering             */
   tFILE      *g_file;                 /* limit output to this file           */
   char        g_extern    [LEN_RECD]; /* name for focus/filtering            */
   char        g_libuse    [LEN_RECD]; /* extern library for filtering        */
   char        g_funcname  [LEN_DESC]; /* file name for filtering             */
   char        g_hint      [LEN_TERSE];/* function hint for filtering         */
   /*---(long-term files)-----*/
   FILE       *f_error;                /* stderr output                       */
   char        n_db        [LEN_RECD]; /* name of database file               */
   FILE       *f_db;                   /* shared database of tags             */
   char        n_extern    [LEN_RECD]; /* name of external file               */
   FILE       *f_extern;               /* shared external function list       */
   char        n_world     [LEN_RECD]; /* name of world project inventory     */
   FILE       *f_world;                /* world project inventory             */
   /*---(working files)-------*/
   FILE       *f_code;                 /* current program source file         */
   FILE       *f_ctags;                /* ctags input file                    */
   FILE       *f_cflow;                /* cflow input file                    */
   FILE       *f_mystry;               /* local mystery external calls        */
   FILE       *f_vars;                 /* global/file variables               */
   FILE       *f_units;                /* function calls from unit tests      */
   FILE       *f_scrps;                /* reading unit tests                  */
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
   char        header      [LEN_DESC];      /* flags on each header oneliner  */
   long        written;
   /*---(master)------------*/
   char        focus       [LEN_DESC]; 
   char        niche       [LEN_DESC]; 
   char        subject     [LEN_DESC];
   char        purpose     [LEN_HUND];
   /*---(greek)-------------*/
   char        namesake    [LEN_HUND];
   char        pronounce   [LEN_TITLE];
   char        heritage    [LEN_HUND];
   char        briefly     [LEN_TITLE];
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
   char        compiler    [LEN_LABEL];
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
   /*---(other)-------------*/
   char        manual      [LEN_LABEL];
   char        git;
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


#define     MAX_STATS      60
#define     MAX_CATS       70

/*---(overall)------------------------*/
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
/* duplicate of STATS_DEBUG */
#define     STATS_DWARN    stats [42]
/*---(group three.b)------------------*/
#define     STATS_PUSE     stats [43]
#define     STATS_FUSE     stats [44]
#define     STATS_GUSE     stats [45]
#define     STATS_MUSE     stats [46]
#define     STATS_YUSE     stats [47]
#define     STATS_OUSE     stats [48]
/*---(group three.c)------------------*/
#define     STATS_VMASK    stats [49]
#define     STATS_MMASK    stats [50]
#define     STATS_FMASK    stats [51]
#define     STATS_LSTATIC  stats [52]
/*---(group three.d)------------------*/
#define     STATS_TUNIT    stats [53]
#define     STATS_SUNIT    stats [54]
#define     STATS_NUNIT    stats [55]
/*---(new)----------------------------*/
#define     STATS_RCE      stats [56]
#define     STATS_LOOP     stats [57]



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
typedef     struct      cCTRL       tCTRL;
struct cCTRL    {
   int         count;
   void       *head;
   void       *tail;
};



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
typedef     struct      cSIBS       tSIBS;
struct cSIBS {
   void       *parent;
   void       *prev;
   void       *next;
};



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
struct      cFUNC {
   /*---(master)-------------------------*/
   char        type;                        /* 'f' normal, '_' separator      */
   char        name        [LEN_TITLE];     /* c function name                */
   char        hint        [LEN_SHORT];     /* two-char navigation hint       */
   char        purpose     [LEN_DESC];      /* short description of purpose   */
   int         line;                        /* function header                */
   int         beg;                         /* first code line                */
   int         end;                         /* last code line                 */
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
   int         y_count;
   tYLIB      *y_head;
   tYLIB      *y_tail;
   /*---(btree)-------------*/
   tBTREE     *btree;
   /*---(done)--------------*/
};

struct cYLIB {
   /*---(main)--------------*/
   uchar       name       [LEN_TITLE];
   int         line;
   /*---(function)----------*/
   tFUNC      *func;
   tYLIB      *f_prev;
   tYLIB      *f_next;
   /*---(extern)------------*/
   tEXTERN    *ylib;
   tYLIB      *e_prev;
   tYLIB      *e_next;
   /*---(done)--------------*/
};
extern   int g_nylib;


typedef struct cWORLD tWORLD;
struct cWORLD {
   char        name        [LEN_LABEL];
   char        home        [LEN_RECD];
   tBTREE     *btree;
};




#define     MAX_TEMPS      60

/*---(location)-----------------------*/
#define     WORK_BEG       work->beg
#define     WORK_END       work->end
#define     WORK_LOCALS    work->locals
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
/*---(group three.c)------------------*/
#define     WORK_VMASK     work->temp  [47]
#define     WORK_MMASK     work->temp  [48]
#define     WORK_FMASK     work->temp  [49]
#define     WORK_LSTATIC   work->temp  [50]
/*---(group three.d)------------------*/
#define     WORK_TSAVE     work->temp  [51]
#define     WORK_TUNIT     work->temp  [52]
#define     WORK_SSAVE     work->temp  [53]
#define     WORK_SUNIT     work->temp  [54]
#define     WORK_NUNIT     work->temp  [55]
/*---(new)----------------------------*/
#define     WORK_RCE       work->temp  [56]
#define     WORK_LOOP      work->temp  [57]



struct cWORK {
   /*---(positioning)--------------------*/
   int         beg;
   int         end;
   int         temp        [MAX_TEMPS];
   char        locals      [LEN_RECD];
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
#define     B_FUNCS     't'
#define     B_PROTO     'p'
#define     B_EXTERN    'e'
#define     B_WORLD     'w'
#define     B_ELIB      'l'
#define     B_UNIT      'U'
#define     B_ALL       "TftpewlU"

struct      cELIB {
   /*---(info)--------------*/
   char        name        [LEN_LABEL];
   int         wuse;
   /*---(extern)------------*/
   int         count;
   tEXTERN    *head;
   tEXTERN    *tail;
   /*---(btree)-------------*/
   tBTREE     *btree;
   /*---(done)--------------*/
};


/*----------+-----------+-----------+-----------+-----------+-----------+-----*/
struct      cEXTERN {
   /*---(information)-------*/
   tELIB      *elib;
   char        name        [LEN_TITLE];
   int         line;
   char        type;
   char        cat;
   char        sub;
   int         count;
   /*---(working)-----------*/
   int         wuse;
   /*---(elib)--------------*/
   tEXTERN    *l_next;
   tEXTERN    *l_prev;
   /*---(ylib)--------------*/
   int         y_count;
   tYLIB      *y_head;
   tYLIB      *y_tail;
   /*---(btree)-------------*/
   tBTREE     *btree;
   /*---(done)--------------*/
};

extern int   g_depth;
extern char  g_path    [LEN_HUND];



extern char      unit_answer [LEN_RECD];

#define     CODE_NORMAL      '-'
#define     CODE_VAR_I       'i'
#define     CODE_VAR_M       'm'
#define     CODE_VAR_V       'v'
#define     CODE_VAR_O       'o'
#define     CODE_VAR_F       'f'


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        poly_file_init          (void);
char        poly_file_wrap          (void);
/*---(memory)---------------*/
char        poly_file__new          (tFILE **a_new);
char        poly_file_force         (tFILE **a_new);
char        poly_file__free         (tFILE **a_old);
char        poly_file__wipe         (tFILE *a_dst);
char*       poly_file__unit_memory  (tFILE *a_file);
/*---(hooking)--------------*/
char        poly_file_hook          (tPROJ *a_proj, tFILE *a_file);
char        poly_file_unhook        (tFILE *a_file);
/*---(existance)------------*/
char        poly_file_add           (tPROJ *a_proj, char *a_name, char a_type, tFILE **a_file);
char        poly_file_remove        (tFILE **a_old);
char        poly_file_purge         (tPROJ *a_proj, char a_update);
char        poly_file_review        (tPROJ *a_proj);
char        poly_file_by_name       (uchar *a_name, tFILE **a_file);
char        poly_file_by_index      (int n, tFILE **a_file);
char        poly_file_by_proj_index (tPROJ *a_proj, int n, tFILE **a_file);
char        poly_file_by_cursor     (char a_dir, tFILE **a_file);
char        poly_file_line          (tFILE *a_file, char a_style, char a_use, char a_pre, int a, int b, char a_print);
/*---(footprint)------------*/
char        poly_file_footprint    (tFILE *a_file);
/*---(unittest)-------------*/
char*       poly_file__unit         (char *a_question, int n);

char        poly_tags_inventory     (tFILE *a_file);
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
char        poly_cats_func          (tFUNC *a_func);
char        poly_cats_by_index      (tFUNC *a_func, char n, char *a_grp, char *a_sub, char *a_name, char *a_desc, char *a_set);
char*       poly_cats__unit         (char *a_question, int n);



/*---(support)--------------*/
char        PROG_reset_yjobs        (void);
/*---(urgents)--------------*/
char        PROG_urgents            (int a_argc, char *a_argv[]);
/*---(startup)--------------*/
char        PROG__init              (int a_argc, char *a_argv[]);
char        PROG__args              (int a_argc, char *a_argv[]);
char        PROG__begin             (void);
char        PROG_startup            (int a_argc, char *a_argv[]);
/*---(main)-----------------*/
char        PROG_summarize          (tPROJ *x_proj);
/*---(shutdown)-------------*/
char        PROG__end               (void);
char        PROG_shutdown           (void);
/*---(unittest)-------------*/
char        PROG__unit_quiet        (void);
char        PROG__unit_loud         (void);
char        PROG__unit_end          (void);
char*       prog__unit              (char *a_question, int i);
/*---(done)-----------------*/



/*---(memory)---------------*/
char        poly_extern__new        (tEXTERN **a_new);
char        poly_extern_force       (tEXTERN **a_new);
char        poly_extern__free       (tEXTERN **a_old);
char        poly_extern__wipe       (tEXTERN *a_ext);
char*       poly_extern__memory     (tEXTERN *a_ext);
/*---(program)--------------*/
char        poly_extern_init        (void);
char        poly_extern_clear_uses  (void);
char        poly_extern_wrap        (void);
/*---(existance)------------*/
char        poly_extern_add         (char *a_lib, char *a_name, int a_line, char a_type);
char        poly_extern_load        (void);
char        poly_extern__pointers   (char *a_func, char *a_file, int a_line, tFUNC **a_src, tFUNC **a_dst, tEXTERN **a_ext);
char        poly_extern__tally      (tFUNC *a_src, tFUNC *a_dst, tEXTERN *a_ext, int a_line);
char        poly_extern_review      (void);
char        poly_extern_list        (void);
int         poly_extern_count       (void);
/*---(search)---------------*/
char        poly_extern_by_name     (uchar *a_name, tEXTERN **a_func);
char        poly_extern_by_index    (int n, tEXTERN **a_ext);
char        poly_extern_by_cursor   (char a_dir, tEXTERN **a_ext);
/*---(unittest)-------------*/
char*       poly_extern__unit       (char *a_question, int n);
/*---(done)-----------------*/



char        poly_proto__purge       (void);
char        poly_proto_init         (void);
char        poly_proto_push         (tFILE *a_file, int a_line, char *a_name);
char        poly_proto_hook         (tFILE *a_file, tFUNC *a_func, char *a_name);
char        poly_proto_list         (void);
char*       poly_proto__unit        (char *a_question, int i);



/*> char        poly_btree_init         (char a_btree);                               <*/
/*> char        poly_btree_hook         (char a_btree, void *a_data, char *a_sort, tBTREE **a_link);   <*/
/*> char        poly_btree_unhook       (tBTREE **a_link);                            <*/
/*> char        poly_btree_purge        (char a_btree);                               <*/
/*> int         poly_btree__depth       (int a_size);                                 <*/
/*> int         poly_btree__span        (int a_levels);                               <*/
/*> char        poly_btree_dgnome       (char a_btree);                               <*/
/*> char        poly_btree_build        (char a_btree);                               <*/
/*> char        poly_btree_prepare      (char a_btree);                               <*/
char        poly_btree_prepare_all  (void);
/*> char        poly_btree_purge_all    (void);                                       <*/
/*> char        poly_btree_list         (char a_btree);                               <*/
/*---(search)---------------*/
/*> char        poly_btree_by_cursor    (char a_btree, char a_dir, void **r_data);    <*/
/*> char        poly_btree_by_index     (char a_btree, int i, void **r_data);         <*/
/*> char        poly_btree_by_name      (char a_btree, char *a_name, void **r_data);   <*/
/*> int         poly_btree_count        (char a_btree);                               <*/
char*       poly_btree__unit        (char a_btree, char *a_question, int i);



char        poly_proj_cli           (char *a_name, char a_loud);
/*---(memory)---------------*/
char        poly_proj__new          (tPROJ **a_new);
char        poly_proj_force         (tPROJ **a_new);
char        poly_proj__free         (tPROJ **a_old);
char        poly_proj__wipe         (tPROJ *a_dst);
char*       poly_proj__memory       (tPROJ *a_proj);
/*---(hooking)--------------*/
char        poly_proj__hook         (tPROJ *a_proj);
char        poly_proj__unhook       (tPROJ *a_proj);
/*---(existance)------------*/
char        poly_proj__adder        (char *a_name, char *a_home, tPROJ **a_proj, char a_force);
char        poly_proj_add           (char *a_name, char *a_home, tPROJ **a_proj);
char        poly_proj_replace       (char *a_name, char *a_home, tPROJ **a_proj);
char        poly_proj_remove        (tPROJ **a_proj);
/*---(special)--------------*/
char        poly_proj__get_home     (char *a_home);
char        poly_proj__get_name     (cchar *a_home, char *a_name);
char        poly_proj_identify      (char *a_name, char *a_home);
char        poly_proj_here          (tPROJ **a_proj);
/*---(search)---------------*/
int         poly_proj_count         (void);
char        poly_proj_by_name       (uchar *a_name, tPROJ **a_proj);
char        poly_proj_by_index      (int n, tPROJ **a_proj);
char        poly_proj_by_cursor     (char a_dir, tPROJ **a_proj);
/*---(program)--------------*/
char        poly_proj_init          (void);
char        poly_proj_purge         (void);
char        poly_proj_wrap          (void);
/*---(system)---------------*/
/*> char        poly_proj_system        (char *a_path);                               <*/
char        poly_proj_git           (tPROJ *a_proj);
char        poly_proj_footprint     (tPROJ *a_proj);
/*---(reporting)------------*/
char        poly_proj__headerline   (char *a_header, char n, char a_abbr, char *a_text, char a_min, char a_low, char a_high, char a_max);
char        poly_proj_header        (tPROJ *a_proj);
char        poly_proj_line          (tPROJ *a_proj, char a_style, char a_use, char a_pre, int a, char a_print);
/*---(unittest)-------------*/
char*       poly_proj__unit         (char *a_question, int i);



char        poly_db_cli             (char *a_name, char a_loud);
char        poly_db_init            (void);
char        poly_db__open           (char a_mode, int *a_nproj, int *a_nfile, int *a_nfunc, int *a_nylib);
char        poly_db__close          (void);
char        poly_db_write           (void);
char        poly_db_read            (void);
char*       poly_db__unit           (char *a_question);

char        poly_rptg_lookup        (char *a_option);
char        poly_rptg_projects      (void);
char        poly_rptg_files         (void);
char        poly_rptg_htags         (tPROJ *x_proj);
char        poly_rptg_dump          (void);
char        poly_rptg_extern        (tEXTERN *a_extern);
char        poly_rptg_dispatch      (void);

/*> char        poly_action_whoami      (void);                                       <*/
/*> char        poly_action_htags       (void);                                       <*/
char        poly_action_generate    (void);
char        poly_action_search      (void);
/*> char        poly_action_update      (void);                                       <*/
/*> char        poly_action_audit       (void);                                       <*/
/*> char        poly_action_about       (void);                                       <*/
/*> char        poly_action_remove      (void);                                       <*/
char        poly_action_extern      (void);
char        poly_action_libuse      (void);
char        poly_action_vars        (void);
char        poly_action_detail      (void);

/*---(memory)---------------*/
char        poly_ylib__new          (tYLIB **a_new);
char        poly_ylib_force         (tYLIB **a_new);
char        poly_ylib__free         (tYLIB **a_old);
char        poly_ylib__wipe         (tYLIB *a_ylib);
char*       poly_ylib__memory       (tYLIB *a_ylib);
/*---(hooking)--------------*/
char        poly_ylib__fhook        (tFUNC *a_func, tYLIB *a_ylib);
char        poly_ylib__funhook      (tYLIB *a_ylib);
char        poly_ylib__ehook        (tEXTERN *a_ext, tYLIB *a_ylib);
char        poly_ylib__eunhook      (tYLIB *a_ylib);
/*---(existance)------------*/
char        poly_ylib_add           (tFUNC *a_tag, tEXTERN *a_extern, int a_line, tYLIB **a_ylib);
char        poly_ylib_remove        (tYLIB **a_ylib);
/*---(program)--------------*/
char        poly_ylib_purge         (tFUNC *a_func, char a_update);
/*---(search)---------------*/
int         poly_ylib_count         (void);
char        poly_ylib_by_name       (uchar *a_name, tYLIB **a_ylib);
char        poly_ylib_by_index      (int n, tYLIB **a_ylib);
char        poly_ylib_by_cursor     (char a_dir, tYLIB **a_ylib);
char        poly_ylib_by_func_index (tFUNC *a_func, int n, tYLIB **r_ylib);
char        poly_ylib_use_by_index  (char *a_name, int n, tYLIB **r_ylib);
/*---(unittest)-------------*/
char*       poly_ylib__unit         (char *a_question, char *a_name);
/*---(done)-----------------*/



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
char        poly_func__wipe         (tFUNC *a_func);
char*       poly_func__memory       (tFUNC *a_func);
char        poly_work__wipe         (tWORK *a_work);
char*       poly_work__memory       (tWORK *a_work);
char        poly_func_cli           (char *a_hint, char a_loud);
char        poly_func_cli_name      (char *a_name, char a_loud);
/*---(memory)---------------*/
char        poly_func__new          (tFUNC **a_func);
char        poly_func_force         (tFUNC **a_func);
char        poly_func__free         (tFUNC **a_func);
char        poly_work__new          (tWORK **a_work);
char        poly_work_force         (tWORK **a_work);
char        poly_work__free         (tWORK **a_work);
/*---(hooking)--------------*/
char        poly_func_hook          (tFILE *a_file, tFUNC *a_tag);
char        poly_func_unhook        (tFUNC *a_tag);
char        poly_func_in_file       (tFILE *a_file);
/*---(existance)------------*/
char        poly_func_add           (tFILE *a_file, char *a_name, char a_type, int a_line, tFUNC **a_func);
char        poly_func_remove        (tFUNC **a_tag);
/*---(position)-------------*/
char        poly_func_enter         (tFUNC *a_func, int a_line);
char        poly_func_exit          (tFUNC *a_func, int a_line);
char        poly_func_inside        (tFUNC *a_func);
/*---(search)---------------*/
int         poly_func_count         (void);
char        poly_func_by_name       (uchar *a_name, tFUNC **a_func);
char        poly_func_by_index      (int n, tFUNC **a_func);
char        poly_func_cursor        (char a_dir, tFUNC **a_func);
char        poly_func_by_line       (tFILE *a_file, int a_line, tFUNC **a_func);
char        poly_func_by_hint       (tPROJ *a_proj, uchar *a_hint, tFUNC **a_func);
char        poly_func_by_cursor     (tPROJ *a_proj, uchar a_mode, tFUNC **a_func);
char        poly_func_by_regex      (uchar *a_regex, tFUNC **a_func);
/*---(program)--------------*/
char        poly_func_init          (void);
char        poly_func_purge         (tFILE *a_file, char a_update);
char        poly_func_wrap          (void);
/*---(source)---------------*/
char        poly_func_purpose       (tFUNC *a_func, char *a_recd);
char        poly_func_return        (tFUNC *a_func, char *a_recd, char *a_prev);
char        poly_func_params        (tFUNC *a_func, char *a_recd);
/*---(reporting)------------*/
char*       poly_func__prefix       (tFUNC *a_func, char a_spec, int a, int b, int c);
char*       poly_func__core         (tFUNC *a_func, char a_spec, int c);
char*       poly_func__suffix       (tFUNC *a_func, char a_spec);
char*       poly_func_line          (tFUNC *a_func, char a_style, int a, int b, int c, char a_print);
/*---(unittest)-------------*/
char*       poly_func__unit         (char *a_question, int i);



char        poly_code__unquote      (char *a_dst, char *a_src, int a_max);
char        poly_code__oneliners    (tFILE *a_file, char *a_recd);
char        poly_code__reserved     (tFILE *a_file, tFUNC *a_func, char *a_recd);
char        poly_code__indent       (tFUNC *a_func, char *a_recd);
char        poly_code_function      (tFUNC *a_func, char *a_recd, char *a_prev);
char        poly_code_nextfunc      (tFILE *a_file, tFUNC **a_func);
char        poly_code__before       (tFILE *a_file, int a_line, tFUNC **a_func, char *a_curr, char *a_prev);
char        poly_code__current      (tFILE *a_file, int a_line, tFUNC *a_func, char *a_curr, char *a_prev);
char        poly_code__after        (tFILE *a_file, int a_line, tFUNC *a_func, char *a_curr);
char        poly_code_driver        (tFILE *a_file, int a_beg, int a_end, char a_act);
char        poly_code_review        (tFILE *a_file);


char        poly_tags__create       (tFILE *a_file);
char        poly_tags__cleanup      (void);
char        poly_tags__handler      (tFILE *a_file, char *a_recd);


/*---(memory)---------------*/
char        poly_shared_new         (char *a_terse, int a_size, void **a_new, int *a_count, char a_force, char *a_wiper (void *));
char        poly_shared_free        (char *a_terse, void **a_old, int *a_count);
char        poly_shared__unit_wiper (void *a_void);
char        poly_shared__check_char (char *a_out, char a_char);
char        poly_shared__check_str  (char *a_out, char *a_str);
char        poly_shared__check_ptr  (char *a_out, void *a_ptr);
char        poly_shared__check_num  (char *a_out, int a_num);
char        poly_shared__spacer     (char *a_out);
/*---(hooking)--------------*/
/*> char        poly_shared_hook        (char *a_terse, char *a_name, void *a_here, void *a_parent, void *a_owner, void *a_head, void *a_tail, void *a_prev, void *a_tnext, int *a_count, int *a_counta, int *a_countb, int *a_countc);   <*/
/*> char        poly_shared_unhook      (char *a_terse, char *a_name, void *a_here, void *a_owner, void *a_head, void *a_tail, void *a_prev, void *a_pnext, void *a_next, void *a_nprev, int *a_count, int *a_counta, int *a_countb, int *a_countc);   <*/
/*---(other)----------------*/
char        poly_shared_verify      (uchar *a_name);
char        poly_shared_open        (char a_type, char *a_focus);
char        poly_shared_close       (char a_type);
char        poly_shared_read        (char a_type, int *a_line, char *a_curr, char *a_prev);
char        poly_shared_parse_tags  (char *a_curr, char *a_name, char *a_type, int *a_line, char *a_file);
char        poly_shared_parse_flow  (char *a_curr, char *a_name, char *a_defn, int *a_line, char *a_file);
char        poly_shared_parse_unit  (char *a_curr, char *a_verb, char *a_name);
char*       poly_shared__unit       (char *a_question);


char        poly_vars_init          (void);
char        poly_vars__push         (tFILE *a_file, int a_line, char *a_name, char a_type);
char        poly_vars__pop_file     (void);
char        poly_vars_reset         (tFUNC *a_func);
char        poly_vars__extern_find  (tFUNC *a_func, int a_line, char *a_recd, char a_act);
char        poly_vars__intern_find  (tFUNC *a_func, int a_line, char *a_recd, char a_act);
char        poly_vars_header        (char a_act);
char        poly_vars__hiding       (tFUNC *a_func);
char        poly_vars_summary       (tFUNC *a_func, char a_act);
char        poly_vars_find          (tFUNC *a_func, int a_line, char *a_recd, char a_act);
char        poly_vars_inventory     (tFILE *a_file);
char        poly_vars_list          (void);
char        poly_vars__unit_set     (tFUNC *a_func, char *a_extern, char *a_intern, char *a_macros, char *a_locals);
char*       poly_vars__unit         (char *a_question, int i);



/*---(cli)------------------*/
/*> char        poly_world_cli          (char *a_name, char a_loud);                  <*/
/*---(cleansing)------------*/
/*> char        poly_world__wipe        (tWORLD *a_world);                            <*/
/*> char*       poly_world__memory      (tWORLD *a_world);                            <*/
/*---(memory)---------------*/
/*> char        poly_world__new         (tWORLD **a_new);                             <*/
/*> char        poly_world__free        (tWORLD **a_old);                             <*/
/*---(existance)------------*/
/*> char        poly_world__add         (char *a_name, char *a_home);                 <*/
/*> char        poly_world__remove      (char *a_name);                               <*/
/*---(searching)------------*/
/*> int         poly_world__count       (void);                                       <*/
/*> char        poly_world__by_name     (uchar *a_name, tWORLD **a_world);            <*/
/*> char        poly_world__by_index    (int n, tWORLD **a_world);                    <*/
/*> char        poly_world__by_cursor   (char a_dir, tWORLD **a_world);               <*/
/*---(exim)-----------------*/
/*> char        poly_world__export      (void);                                       <*/
/*> char        poly_world__import      (void);                                       <*/
/*---(register)-------------*/
/*> char        poly_world__register    (void);                                       <*/
/*> char        poly_world__unregister  (void);                                       <*/
/*---(actions)--------------*/
/*> char        poly_world_register     (void);                                       <*/
/*> char        poly_world_unregister   (void);                                       <*/
/*> char        poly_world_system       (void);                                       <*/
/*---(program)--------------*/
/*> char        poly_world_init         (void);                                       <*/
/*> char        poly_world__purge       (void);                                       <*/
/*> char        poly_world_wrap         (void);                                       <*/


char        poly_units_by_func      (void);
char        poly_units__scripts     (tFILE *a_file, int x_line, char *a_recd, tFUNC **a_func);
char        poly_units__classify    (tFILE *a_file, tFUNC *a_func, int a_line, char *a_recd);
char        poly_units_inventory    (tFILE *a_file);


char        PROG_dispatch           (void);
char        poly_yjobs_callback     (cchar a_req, cchar *a_data);

#endif
