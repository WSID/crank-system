#include <glib.h>
#include <locale.h>
#include <glib/gi18n.h>

#include "crankdummy.h"

gint
main  (gint    argc,
       gchar **argv)
{
  setlocale (LC_ALL, "");
  bindtextdomain (GETTEXT_PACKAGE, LOCALEDIR);
  textdomain (GETTEXT_PACKAGE);

  crank_dummy_init ();
  crank_dummy_do (7);
  return 0;
}
