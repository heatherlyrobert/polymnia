/*============================----beg-of-source---============================*/
#include   "polymnia.h"


/*> struct {                                                                          <* 
 *>    char        match       [LEN_LABEL];                                           <* 
 *>    char        desc        [LEN_TERSE];                                           <* 
 *> } s_matches [LEN_DESC] = {                                                        <* 
 *>    /+---(ends)---------------------------+/                                       <* 
 *>    { "c ·· ·· ··· ·",  "leaf"       },                                            <* 
 *>    { "c ·´ ·· ··· ·",  "leaf+"      },                                            <* 
 *>    { "c ·· ·· ··· ´",  "seed"       },                                            <* 
 *>    { "c ·´ ·· ··· ´",  "seed+"      },                                            <* 
 *>    { "c ·· ·· ´·· ´",  "root"       },                                            <* 
 *>    { "c ·· ·· ·´· ´",  "tendril"    },                                            <* 
 *>    { "c ·· ·· ··´ ´",  "flower"     },                                            <* 
 *>    /+---(connections)--------------------+/                                       <* 
 *>    { "c ·´ ·· ··· ·",  "node"       },                                            <* 
 *>    { "c ·· ·´ ··· ·",  "node"       },                                            <* 
 *>    { "c ·´ ·´ ··· ·",  "node+"      },                                            <* 
 *>    { "s ·´ ·· ··· ·",  "access"     },                                            <* 
 *>    { "s ·· ·´ ··· ·",  "access"     },                                            <* 
 *>    { "s ·´ ·´ ··· ·",  "access+"    },                                            <* 
 *>    /+---(done)---------------------------+/                                       <* 
 *>    { "---"          ,  "END-LIST"   },                                            <* 
 *> };                                                                                <*/

/*> char         /+-> classify function by statistics -------------[ leaf       ]-+/ /+-åfc#´·8á71·á···´4·A´1··´2·A1·á·æ¬å1á1···´8·8á······´···´····æ¬å·····´······´····´····æ-+/                                                             <* 
 *> poly_cats__anatomy      (char a_name [LEN_TITLE], char a_rtype, char a_fvars, char a_gvars, char a_fcalls, char a_gcalls, char a_graph, char a_read, char a_write, char a_memory, char r_anatomy [LEN_TERSE], char r_match [LEN_LABEL])   <* 
 *> {                                                                                                                                                                                                                                         <* 
 *>    int         i           =    0;                                                                                                                                                                                                        <* 
 *>    char        x_match     [LEN_LABEL] = "· ·· ·· ··· ·";                                                                                                                                                                                 <* 
 *>    char        x_anatomy   [LEN_TERSE] = "´";                                                                                                                                                                                             <* 
 *>    /+---(quick-out)----------------------+/                                                                                                                                                                                               <* 
 *>    if (strncmp (a_name, "o___", 4) == 0) {                                                                                                                                                                                                <* 
 *>       if (r_anatomy != NULL)  ystrlcpy (r_anatomy, "·········", LEN_TERSE);                                                                                                                                                               <* 
 *>       if (r_match   != NULL)  ystrlcpy (r_match  , ""         , LEN_LABEL);                                                                                                                                                               <* 
 *>       return 0;                                                                                                                                                                                                                           <* 
 *>    }                                                                                                                                                                                                                                      <* 
 *>    /+---(build match)--------------------+/                                                                                                                                                                                               <* 
 *>    if (a_rtype  == 'c')  x_match [ 0]  = 'c';                                                                                                                                                                                             <* 
 *>    if (a_rtype  == 's')  x_match [ 0]  = 's';                                                                                                                                                                                             <* 
 *>    if (a_gvars  >   0 )  x_match [ 2]  = '´';                                                                                                                                                                                             <* 
 *>    if (a_fvars  >   0 )  x_match [ 3]  = '´';                                                                                                                                                                                             <* 
 *>    if (a_gcalls >   0 )  x_match [ 5]  = '´';                                                                                                                                                                                             <* 
 *>    if (a_fcalls >   0 )  x_match [ 6]  = '´';                                                                                                                                                                                             <* 
 *>    if (a_read   >   0 )  x_match [ 8]  = '´';                                                                                                                                                                                             <* 
 *>    if (a_write  >   0 )  x_match [ 9]  = '´';                                                                                                                                                                                             <* 
 *>    if (a_graph  >   0 )  x_match [10]  = '´';                                                                                                                                                                                             <* 
 *>    if (a_memory >   0 )  x_match [12]  = '´';                                                                                                                                                                                             <* 
 *>    /+---(test match)---------------------+/                                                                                                                                                                                               <* 
 *>    ystrlcpy (x_anatomy, "´"        , LEN_TERSE);                                                                                                                                                                                          <* 
 *>    for (i = 0; i < LEN_DESC; ++i) {                                                                                                                                                                                                       <* 
 *>       if (strcmp ("---"  , s_matches [i].match) == 0)   break;                                                                                                                                                                            <* 
 *>       if (strcmp (x_match, s_matches [i].match) != 0)   continue;                                                                                                                                                                         <* 
 *>       ystrlcpy (x_anatomy, s_matches [i].desc, LEN_TERSE);                                                                                                                                                                                <* 
 *>       break;                                                                                                                                                                                                                              <* 
 *>    }                                                                                                                                                                                                                                      <* 
 *>    if (r_anatomy != NULL)  ystrlcpy (r_anatomy, x_anatomy, LEN_TERSE);                                                                                                                                                                    <* 
 *>    if (r_match   != NULL)  ystrlcpy (r_match  , x_match  , LEN_LABEL);                                                                                                                                                                    <* 
 *>    return 0;                                                                                                                                                                                                                              <* 
 *> }                                                                                                                                                                                                                                         <*/



/*
 * anatomy
 *    return type
 *
 *    global vars used          · f G °
 *    file/static vars used
 *
 *    global calls              · f G °
 *    file/static calls
 *
 *    input   user (scanf, ...)
 *    read    file/stream
 *
 *    output  user (printf, ...)
 *    write   file/stream
 *
 *    input
 *    output
 *
 *    graphics
 *    memory alloc/free
 *
 *    any non-local variables
 *    any non-lib, non-std function calls
 *
 */


/*    -  f  g  °
/* HAIR INDICATOR (2 fields)                                            */
/*   ƒ€€€€€€ uses local (-), file (*) ,or global (°) variables          */
/*    ƒ€€€€ calls to none (-), file (*), or global (°) functions       */
/* [·-·-·]¬[fcC##g·L44·27-·E-2D1-]¬[-----·--·-------·---·----]¬[?#p-#·4-2--2·----·----]  */
/* [·*·*·]¬[fcC##g·L44·27-·E-2D1-]¬[-----·--·-------·---·----]¬[?#p-#·4-2--2·----·----]  */
/* [·°·°·]¬[fcC##g·L44·27-·E-2D1-]¬[-----·--·-------·---·----]¬[?#p-#·4-2--2·----·----]  */

/*   leaf      uses only local data and calls only cstd functions   */
/*   tindril                                                        */
/*   creeper                                                        */
/*   vine                                                           */
/*   pod                                                            */
/*   flower                                                         */
/*   burl                                                           */
/*   branch                                                         */
/*   trunk                                                          */
/*   root                                                           */
/*   bark      uses only local data and calls only cstd functions   */


/*> #define     WORK_BEG       work->beg                                              <* 
 *> #define     WORK_END       work->end                                              <* 
 *> #define     WORK_LOCALS    work->locals                                           <*/

static const tySCORE_TB  s_polymnia_table [LEN_FULL] = {
   /*===[[ HAIR ]]=========== print======= description========================= style check valid============== legend====== ============ ============ ============ ============ ============ ============   */
   { "HRá "     , '>' ,  0  , "HAIR"                       , ""               , ' ' , ' ' , ""                , ""                                                                                            },
   /*--label----- def-- samp- print------- description------------------------- style check valid-------------- legend------ ------------ ------------ ------------ ------------ ------------ ------------   */
   { "HCALL"    , '·' , 'f' , "hcall"    , "widest²scope²call²to²function"    , ' ' , ' ' , "-fg°"            , "-) none     f) file      g) global    °) extern"                                            },
   { "HFUNC"    , '·' , '-' , "hfunc"    , "widest²scope²function²used"       , ' ' , ' ' , "-fg°"            , "-) none     f) file      g) global    °) extern"                                            },
   { "HVAR"     , '·' , 'g' , "hvar"     , "widest²scope²variable²used"       , ' ' , ' ' , "-fmg°"           , "-) none     f) file      m) access    g) global    °) extern"                               },
   { "   "      , ' ' ,  3  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },

   /*===[[ COMPLEXITY ]]===== print======= description========================= style check valid============== legend====== ============ ============ ============ ============ ============ ============   */
   { "COá "     , '>' ,  0  , "COMPLEXITY"                 , ""               , ' ' , ' ' , ""                , ""                                                                                            },
   /*--label----- def-- samp- print------- description------------------------- style check valid-------------- legend------ ------------ ------------ ------------ ------------ ------------ ------------   */
   { "SINGLE"   , '·' , '-' , "single"   , "single²line²function"             , ' ' , ' ' , "-y"              , "y) single    -) multi"                                                                       },
   { "SCOPE"    , '·' , 'g' , "scope"    , "function²scope"                   , ' ' , ' ' , "xgfsu"           , "x) extern    g) global    f) file      s) static    u) unit"                                 },
   { "RTYPE"    , '·' , 'c' , "rtype"    , "function²return²type"             , ' ' , ' ' , "nbu"             , "c) char      s) string    n) number    p) point     v) void      o) other"                   },
   { "PROTO"    , '·' , 'g' , "proto"    , "function²prototype²location"      , ' ' , ' ' , "nbu"             , "g) global    f) file      -) none"                                                           },
   { " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*--label----- def-- samp- print------- description------------------------- style check valid-------------- legend------ ------------ ------------ ------------ ------------ ------------ ------------   */
   { "PAUDIT"   , '·' , '-' , "paudit"   , "audit²of²parameters"              , ' ' , ' ' , "-"               , "-) tbd"                                                                                      },
   { "PARAMS"   , '·' , 'A' , "params"   , "number²of²parameters"             , ' ' , ' ' , "?0-9#"           , "?) WTF       0) void      1-3) low     4-6) mid     7-9) high    #) huge"                    },
   { " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*--label----- def-- samp- print------- description------------------------- style check valid-------------- legend------ ------------ ------------ ------------ ------------ ------------ ------------   */
   { "PIN"      , '·' , '4' , "pin"      , "incomming²parameters²²²(a)"       , ' ' , ' ' , "?0-9#"           , "?) WTF       0) none      1-3) low     4-6) mid     7-9) high    #) huge"                    },
   { "POUT"     , '·' , '3' , "pout"     , "outgoing²parameters²²²²(r)"       , ' ' , ' ' , "?0-9#"           , "?) WTF       0) none      1-3) low     4-6) mid     7-9) high    #) huge"                    },
   { "PBOTH"    , '·' , '2' , "pboth"    , "both²in/out²parameters²(b)"       , ' ' , ' ' , "?0-9#"           , "?) WTF       0) none      1-3) low     4-6) mid     7-9) high    #) huge"                    },
   { "PCONF"    , '·' , '1' , "pconf"    , "run-time²conf²params²²²(c)"       , ' ' , ' ' , "?0-9#"           , "?) WTF       0) none      1-3) ok      4+) high"                                             },
   { " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*--label----- def-- samp- print------- description------------------------- style check valid-------------- legend------ ------------ ------------ ------------ ------------ ------------ ------------   */
   { "PNUM"     , '·' , '1' , "pnum"     , "params²as²numeric²pointers"       , ' ' , ' ' , "?0-9#"           , "?) WTF       0) none      1-3) low     4-6) mid     7-9) high    #) huge"                    },
   { "PMULTI"   , '·' , '2' , "pmulti"   , "params²as²multiple²pointers"      , ' ' , ' ' , "?0-9#"           , "?) WTF       0) none      1-3) low     4-6) mid     7-9) high    #) huge"                    },
   { "PFUNC"    , '·' , '3' , "pfunc"    , "function²parameters²²²²(f)"       , ' ' , ' ' , "?0-9#"           , "?) WTF       0) none      1-3) low     4-6) mid     7-9) high    #) huge"                    },
   { "PSTRUC"   , '·' , '4' , "pstruc"   , "params²as²struct²pointers"        , ' ' , ' ' , "?0-9#"           , "?) WTF       0) none      1-3) low     4-6) mid     7-9) high    #) huge"                    },
   { "PVOID"    , '·' , '1' , "pvoid"    , "params²as²void²points²²(v)"       , ' ' , ' ' , "?0-9#"           , "?) WTF       0) none      1-3) low     4-6) mid     7-9) high    #) huge"                    },
   { " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*--label----- def-- samp- print------- description------------------------- style check valid-------------- legend------ ------------ ------------ ------------ ------------ ------------ ------------   */
   { "TOTAL"    , '·' , 'B' , "total"    , "total²lines²(div²5)"              , ' ' , ' ' , "0-9A-Z#"         , "1-4) small   5-9) mod     A-D) full    E-H) large   I-N) huge    O-Z) SCARY   #)JESUS"       },
   { "DEBUG"    , '·' , '3' , "debug"    , "percent²debugging²lines"          , ' ' , ' ' , "0-9#"            , "0-1) tiny    2-4) avg     5-7) high    #) warning"                                           },
   { "CODE"     , '·' , '6' , "code"     , "percent²code²lines"               , ' ' , ' ' , "0-9#"            , "0-3) low     4-7) avg     8-9) high    #) warning"                                           },
   { " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*--label----- def-- samp- print------- description------------------------- style check valid-------------- legend------ ------------ ------------ ------------ ------------ ------------ ------------   */
   { "LVARS"    , '·' , '4' , "lvars"    , "number²of²local²vars²used"        , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) few     4-6) avg     7-9) heavy   A-Z) SCARY   #) JESUS"                   },
   { "LSTAT"    , '·' , '1' , "lstat"    , "number²of²locals²also²static"     , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) few     4-6) avg     7-9) heavy   A-Z) SCARY   #) JESUS"                   },
   { "FVARS"    , '·' , '2' , "fvars"    , "number²of²file/static²vars²used"  , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) few     4-6) avg     7-9) heavy   A-Z) SCARY   #) JESUS"                   },
   { "GVARS"    , '·' , '3' , "gvars"    , "number²of²global²vars²used"       , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) few     4-6) avg     7-9) heavy   A-Z) SCARY   #) JESUS"                   },
   { "AVARS"    , '·' , '1' , "avars"    , "number²of²accessor²vars²used"     , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) few     4-6) avg     7-9) heavy   A-Z) SCARY   #) JESUS"                   },
   { " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*--label----- def-- samp- print------- description------------------------- style check valid-------------- legend------ ------------ ------------ ------------ ------------ ------------ ------------   */
   { "INDENT"   , '·' , '2' , "indent"   , "depth²of²indentation"             , ' ' , ' ' , "0-9#"            , "0) none      1-3) avg     4-6) lots    7+) SCARY"                                            },
   { "LOOP"     , '·' , '1' , "loop"     , "number²of²looping²statements"     , ' ' , ' ' , "0-9#"            , "0) none      1-2) avg     3-4) lots    5+) SCARY"                                            },
   { "CHOICE"   , '·' , '3' , "choice"   , "number²of²choices/decisions"      , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) avg     4-9) lots    A+) SCARY"                                            },
   { "RETURN"   , '·' , '1' , "return"   , "number²of²normal²returns"         , ' ' , ' ' , "0-9A-Z#"         , "0) WTF       1) perfect   2-5) avg     A-Z) SCARY"                                           },
   { "RCE"      , '·' , '5' , "rce"      , "number²of²error²returns"          , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) avg     4-6) lots    9+) major"                                            },
   { " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*--label----- def-- samp- print------- description------------------------- style check valid-------------- legend------ ------------ ------------ ------------ ------------ ------------ ------------   */
   { "MEMORY"   , '·' , '-' , "memory"   , "memory²management²(malloc/free)"  , ' ' , ' ' , "-y"              , "y) in-use    -) none"                                                                        },
   { "   "      , ' ' ,  3  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },

   /*===[[ INTEGRATION ]]==== print======= description========================= style check valid============== legend====== ============ ============ ============ ============ ============ ============   */
   { "INá "     , '>' ,  0  , "INTEGRATION"                , ""               , ' ' , ' ' , ""                , ""                                                                                            },
   /*--label----- def-- samp- print------- description------------------------- style check valid-------------- legend------ ------------ ------------ ------------ ------------ ------------ ------------   */
   { "CALLED"   , '·' , '9' , "called"   , "called²by²anything²else"          , ' ' , ' ' , "-y"              , "y) yes       -) no"                                                                          },
   { "FCALL"    , '·' , '1' , "fcall"    , "called²by²local²functions"        , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { "GCALL"    , '·' , '2' , "gcall"    , "called²by²global²functions"       , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { "XCALL"    , '·' , '6' , "xcall"    , "called²by²external²functions"     , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { "RECURS"   , '·' , '-' , "recurs"   , "called²recursively"               , ' ' , ' ' , "-y"              , "y) yes       -) no"                                                                          },
   { " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*--label----- def-- samp- print------- description------------------------- style check valid-------------- legend------ ------------ ------------ ------------ ------------ ------------ ------------   */
   { "CALLTO"   , '·' , 'C' , "callto"   , "call²to²anything²else"            , ' ' , ' ' , "-y"              , "y) yes       -) no"                                                                          },
   { "DFUNC"    , '·' , '2' , "dfunc"    , "call²to²debugging²functions"      , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { "RFUNC"    , '·' , 'A' , "rfunc"    , "call²to²real²functions"           , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*--label----- def-- samp- print------- description------------------------- style check valid-------------- legend------ ------------ ------------ ------------ ------------ ------------ ------------   */
   { "FFUNC"    , '·' , '2' , "ffunc"    , "call²to²local²functions"          , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { "GFUNC"    , '·' , '1' , "gfunc"    , "call²to²global²functions"         , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { "CSTD"     , '·' , '5' , "cstd"     , "call²to²c-std²functions"          , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { "YLIB"     , '·' , '2' , "ylib"     , "call²to²ylib²functions"           , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { "VIKEYS"   , '·' , '-' , "vikeys"   , "call²to²vi-keys²functions"        , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { "OFUNC"    , '·' , '-' , "ofunc"    , "call²to²other²functions"          , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { "MYSTRY"   , '·' , '-' , "mystry"   , "call²to²mystery²functions"        , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*--label----- def-- samp- print------- description------------------------- style check valid-------------- legend------ ------------ ------------ ------------ ------------ ------------ ------------   */
   { "INPUT"    , '·' , '4' , "input"    , "use²stdin²and²file²input"         , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { "INTXT"    , '·' , '3' , "intxt"    , "use²text²input"                   , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { "INBIN"    , '·' , '1' , "inbin"    , "use²binary²input"                 , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { "IPARSE"   , '·' , '-' , "iparse"   , "use²yparse²library²input"         , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*--label----- def-- samp- print------- description------------------------- style check valid-------------- legend------ ------------ ------------ ------------ ------------ ------------ ------------   */
   { "OUTPUT"   , '·' , '5' , "output"   , "use²stdout²and²file²output"       , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { "OUTTXT"   , '·' , '2' , "outtxt"   , "use²text²output"                  , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { "OUTBIN"   , '·' , '3' , "outbin"   , "use²binary²output"                , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { "OPARSE"   , '·' , '-' , "oparse"   , "use²yparse²library²output"        , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*--label----- def-- samp- print------- description------------------------- style check valid-------------- legend------ ------------ ------------ ------------ ------------ ------------ ------------   */
   { "SYSTEM"   , '·' , '4' , "system"   , "unix²process²and²system²calls"    , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { "PROCS"    , '·' , '1' , "procs"    , "process²control²calls"            , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { "OPSYS"    , '·' , '2' , "opsys"    , "operating²system²calls"           , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { "FILSYS"   , '·' , '1' , "filsys"   , "file²system²control²calls"        , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { "YENV"     , '·' , '-' , "yenv"     , "yenv²library²calls"               , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*--label----- def-- samp- print------- description------------------------- style check valid-------------- legend------ ------------ ------------ ------------ ------------ ------------ ------------   */
   { "NCURSE"   , '·' , '-' , "ncurse"   , "ncurses²library²calls"            , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { "WINDOW"   , '·' , '-' , "window"   , "x11²and²window²library²calls"     , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { "OPENGL"   , '·' , '-' , "opengl"   , "opengl²library²calls"             , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { "YGRAPH"   , '·' , '-' , "ygraph"   , "my²x11²and²opengl²library²calls"  , ' ' , ' ' , "0-9A-Z#"         , "0) none      1-3) low     4-6) mid     7-9) high    A-Z) tons    #) JESUS"                   },
   { "   "      , ' ' ,  3  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },

   /*===[[ WATCH-POINTS ]]=== print======= description========================= style check valid============== legend====== ============ ============ ============ ============ ============ ============   */
   { "WPá "     , '>' ,  0  , "WATCH-POINTS"               , ""               , ' ' , ' ' , ""                , ""                                                                                            },
   /*--label----- def-- samp- print------- description------------------------- style check valid-------------- legend------ ------------ ------------ ------------ ------------ ------------ ------------   */
   { "DACTIV"   , '·' , 'y' , "dactiv"   , "debugging²in·use"                 , ' ' , ' ' , "·y-"             , "y) yes       -) no"                                                                          },
   { "DSTYLE"   , '·' , 'l' , "dstyle"   , "debugging²style²(long/short)"     , ' ' , ' ' , "·-ls°"           , "-) none      l) long      s) short    °) mixed"                                              },
   { "DLONG"    , '·' , '5' , "dlong"    , "count²of²debugging²long²calls"    , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { "DSHORT"   , '·' , '-' , "dshort"   , "count²of²debugging²short²calls"   , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { "DMACRO"   , '·' , 'a' , "dmacro"   , "specific²debugging²macro²used"    , ' ' , 'X' , ""                , "identifier assigned by yURG"                                                                 },
   { " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*--label----- def-- samp- print------- description------------------------- style check valid-------------- legend------ ------------ ------------ ------------ ------------ ------------ ------------   */
   { "DMATCH"   , '·' , 'm' , "dmatch"   , "debugging²enter/exits²match"      , ' ' , ' ' , "y°"              , "m) matched   °) unmatched"                                                                   },
   { "DENTER"   , '·' , '1' , "denter"   , "count²of²debugging²enter²calls"   , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { "DEXIT"    , '·' , '2' , "dexit"    , "count²of²debugging²exit²calls"    , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { "DEXITR"   , '·' , '5' , "dexitr"   , "count²of²debugging²exitr²calls"   , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { "DFREE"    , '·' , '-' , "dfree"    , "debugging²calls²without²macro"    , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { "DWARN"    , '·' , '-' , "dwarn"    , "specific²debugging²usage²warning" , ' ' , ' ' , "-°"              , "-) good      °) warning"                                                                     },
   { " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*--label----- def-- samp- print------- description------------------------- style check valid-------------- legend------ ------------ ------------ ------------ ------------ ------------ ------------   */
   { "MACROS"   , '·' , 'y' , "macros"   , "total·potential²#define²uses"     , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { "MFILE"    , '·' , '1' , "mfile"    , "count·of·local/file²macros²used"  , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { "MGLOBL"   , '·' , '3' , "mglobl"   , "count·of·global²macros²used"      , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { "MCSTD"    , '·' , '1' , "mcstd"    , "count·of·c-standard²macros²used"  , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { "MYLIB"    , '·' , '2' , "mylib"    , "count·of·ylib²macros²used"        , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { "MVIKEY"   , '·' , '-' , "mvikey"   , "count·of·vi-keys²macros²used"     , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { "MOTHER"   , '·' , '-' , "mother"   , "count·of·other²macros²used"       , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { "MMYST"    , '·' , '-' , "mmyst"    , "count·of·mystery²macros²used"     , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*--label----- def-- samp- print------- description------------------------- style check valid-------------- legend------ ------------ ------------ ------------ ------------ ------------ ------------   */
   { "VMASK"    , '·' , '-' , "vmask"    , "variables²masking²higher²ones"    , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { "MMASK"    , '·' , '-' , "mmask"    , "macros²masking²earlier²ones"      , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { "FMASK"    , '·' , '-' , "fmask"    , "functions²masking²other²ones"     , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { " "        , '´' ,  1  , ""         , ""                                 , ' ' , ' ' , ""                , ""                                                                                            },
   /*--label----- def-- samp- print------- description------------------------- style check valid-------------- legend------ ------------ ------------ ------------ ------------ ------------ ------------   */
   { "UNITS"    , '·' , '1' , "units"    , "count²of²unit²tests²calling"      , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { "SCRPS"    , '·' , '3' , "scrps"    , "count²of²test²scripts²calling"    , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { "STEPS"    , '·' , 'B' , "steps"    , "count²of²calls·in·unit·tests"     , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },
   { "STRING"   , '·' , '-' , "string"   , "count²of²calls·in·string·tests"   , ' ' , ' ' , "0-9A-Z#"         , ""                                                                                            },

   /*===[[ END-OF-LIST ]]==== print======= description========================= style check valid============== legend====== ============ ============ ============ ============ ============ ============   */
   { "end-list" , '·' , '·' , ""         , "end-of-entries"                   , ' ' , ' ' , ""                , ""                                                                                            },
};

char         /*-> test function to understand look-and-feel-----------------å···æ¬å····á··á····á····á···á····á·····á·æ¬å·····á···á·······á···á···á····á····æ¬å·····á······á········á····á····æ */
poly_test_function          (void)
{
}

char poly_yscore_init       (void) { return ySCORE_init  (s_polymnia_table, 'y', &(my.s_yscore)); }

char poly_yscore_wrap       (void) { return ySCORE_wrap  (&(my.s_yscore)); }

