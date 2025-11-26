
static char   s_unit_home  [LEN_PATH]  = "";


char         /*-> set up programgents/debugging ------[ light  [uz.320.011.05]*/ /*-[00.0000.00#.#]-*/ /*-[--.---.---.--]-*/
PROG__unit_quiet   (void)
{
   char        x_argc      = 1;
   char       *x_args [1]  = { "polymnia" };
   getcwd (s_unit_home, LEN_PATH);
   PROG_debugging (x_argc, x_args);
   PROG_startup   (x_argc, x_args);
   return 0;
}

char         /*-> set up programgents/debugging ------[ light  [uz.320.011.05]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
PROG__unit_loud      (void)
{
   char        x_argc      = 3;
   char       *x_args [3]  = { "polymnia_unit", "@@kitchen", "@@nosort" };
   getcwd (s_unit_home, LEN_PATH);
   PROG_debugging (x_argc, x_args);
   yURG_by_name   ("kitchen"      , YURG_ON);
   yURG_by_name   ("yexec"        , YURG_ON);
   yURG_by_name   ("YSORT"        , YURG_ON);
   PROG_startup   (x_argc, x_args);
   return 0;
}

char         /*-> set up program urgents/debugging ---[ light  [uz.210.001.01]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
PROG__unit_end       (void)
{
   chdir (s_unit_home);
   PROG_shutdown  ();
   return 0;
}
