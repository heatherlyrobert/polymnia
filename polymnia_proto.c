/*============================----beg-of-source---============================*/
#include  "polymnia.h"


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
#define     MAX_PROTO   500
typedef     struct      cPROTO      tPROTO;
struct      cPROTO {
   char        name        [LEN_NAME];
   int         len;
   int         file;
   int         line;
   char        type;
};
tPROTO      s_protos    [MAX_PROTO];
int         s_nproto    =    0;



/*====================------------------------------------====================*/
/*===----                     elemental manipulation                   ----===*/
/*====================------------------------------------====================*/
static void  o___ELEMENTAL_______o () { return; }

char
poly_proto__wipe   (tPROTO *a_dst)
{
   /*> if (a_dst == NULL)  return -1;                                                 <* 
    *> strlcpy (a_dst->name, "", LEN_NAME);                                           <* 
    *> a_dst->len      = 0;                                                           <* 
    *> a_dst->file     = 0;                                                           <* 
    *> a_dst->line     = 0;                                                           <* 
    *> a_dst->type     = '-';                                                         <* 
    *> return 0;                                                                      <*/
}

char
poly_proto__copy  (tPROTO *a_dst, tPROTO *a_src)
{
   /*> strlcpy (a_dst->name, a_src->name, LEN_NAME);                                  <* 
    *> a_dst->len    = a_src->len;                                                    <* 
    *> a_dst->file   = a_src->file;                                                   <* 
    *> a_dst->line   = a_src->line;                                                   <* 
    *> a_dst->type   = a_src->type;                                                   <* 
    *> return 0;                                                                      <*/
}



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
poly_proto_init         (void)
{
   /*> /+---(locals)-----------+-----+-----+-+/                                        <* 
    *> int         i           =    0;          /+ generic return code            +/   <* 
    *> /+---(header)-------------------------+/                                        <* 
    *> DEBUG_PROG   yLOG_enter   (__FUNCTION__);                                       <* 
    *> for (i = 0; i < MAX_PROTO; ++i)   poly_proto__wipe (&s_protos [i]);             <* 
    *> s_nproto = 0;                                                                   <* 
    *> DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                       <* 
    *> return 0;                                                                       <*/
}

char
poly_proto_add          (int a_file, char *a_name, char a_type, int a_line)
{
   /*> /+---(locals)-----------+-----------+-+/                                        <* 
    *> char        rce         = -10;           /+ return code for errors         +/   <* 
    *> /+---(header)-------------------------+/                                        <* 
    *> DEBUG_INPT   yLOG_senter  (__FUNCTION__);                                       <* 
    *> DEBUG_INPT   yLOG_sint    (s_nproto);                                           <* 
    *> /+---(file)---------------------------+/                                        <* 
    *> DEBUG_INPT   yLOG_sint    (a_file);                                             <* 
    *> --rce;  if (a_file <  0) {                                                      <* 
    *>    DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);                               <* 
    *>    return  rce;                                                                 <* 
    *> }                                                                               <* 
    *> --rce;  if (a_file >= s_nfile) {                                                <* 
    *>    DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);                               <* 
    *>    return  rce;                                                                 <* 
    *> }                                                                               <* 
    *> s_protos [s_nproto].file = a_file;                                              <* 
    *> /+---(name)---------------------------+/                                        <* 
    *> DEBUG_INPT   yLOG_spoint  (a_name);                                             <* 
    *> --rce;  if (a_name == NULL) {                                                   <* 
    *>    htags_tags_wipe (&s_protos [s_nproto]);                                      <* 
    *>    DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);                               <* 
    *>    return  rce;                                                                 <* 
    *> }                                                                               <* 
    *> strlcpy (s_protos [s_nproto].name  , a_name  , LEN_NAME);                       <* 
    *> /+---(type)---------------------------+/                                        <* 
    *> DEBUG_INPT   yLOG_spoint  (a_type);                                             <* 
    *> --rce;  if (a_type == NULL) {                                                   <* 
    *>    htags_tags_wipe (&s_protos [s_nproto]);                                      <* 
    *>    DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);                               <* 
    *>    return  rce;                                                                 <* 
    *> }                                                                               <* 
    *> strlcpy (s_protos [s_nproto].type  , a_type  , LEN_RECD);                       <* 
    *> /+---(line)---------------------------+/                                        <* 
    *> DEBUG_INPT   yLOG_sint    (a_line);                                             <* 
    *> --rce;  if (a_line <= 0) {                                                      <* 
    *>    htags_tags_wipe (&s_protos [s_nproto]);                                      <* 
    *>    DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);                               <* 
    *>    return  rce;                                                                 <* 
    *> }                                                                               <* 
    *> s_protos [s_nproto].line  = a_line;                                             <* 
    *> /+---(update)-------------------------+/                                        <* 
    *> ++s_nproto;                                                                     <* 
    *> /+---(complete)-----------------------+/                                        <* 
    *> DEBUG_INPT   yLOG_sexit   (__FUNCTION__);                                       <* 
    *> return 0;                                                                       <*/
}

char
poly_proto_find    (char *a_name)
{
}
