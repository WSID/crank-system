#include <glib.h>

#include "crankdummy.h"

void  test_dummy_do (void);

gint
main (gint   argc,
      gchar *argv[])
{
  g_test_init (&argc, &argv, NULL);

  g_test_add_func ("/wsid/crank/dummy/do", test_dummy_do);

  g_test_run ();

  return 0;
}


void
test_dummy_do (void) {
  g_assert_cmpint (4, ==, crank_dummy_do (4));
}
