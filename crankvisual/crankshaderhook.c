/* Copyright (C) 2015, WSID   */

/* Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#define _CRANKVISUAL_INSIDE

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"

#include "crankshaderhook.h"








//////// List of virtual functions /////////////////////////////////////////////

static void      crank_shader_hook_get_property (GObject    *object,
                                                 guint       prop_id,
                                                 GValue     *value,
                                                 GParamSpec *pspec);

static void      crank_shader_hook_set_property (GObject      *object,
                                                 guint         prop_id,
                                                 const GValue *value,
                                                 GParamSpec   *pspec);

static void      crank_shader_hook_dispose (GObject *object);

static void      crank_shader_hook_finalize (GObject *object);







//////// Private functions /////////////////////////////////////////////////////

static gchar    *crank_shader_hook_generate_parameter (GParamSpec *param);









//////// Properties ////////////////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_NAME,
  PROP_QNAME,
  PROP_NICK,
  PROP_BLURB,
  PROP_N_PARAMS,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};







//////// Type Declarations /////////////////////////////////////////////////////

struct _CrankShaderHook
{
  GObject _parnet;

  GQuark  name;
  gchar  *nick;
  gchar  *blurb;

  GPtrArray *params;
};

G_DEFINE_TYPE (CrankShaderHook,
               crank_shader_hook,
               G_TYPE_OBJECT)







//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_shader_hook_init (CrankShaderHook *self)
{
  self->params = g_ptr_array_new_with_free_func ((GDestroyNotify)g_param_spec_unref);
}


static void
crank_shader_hook_class_init (CrankShaderHookClass *self)
{
  GObjectClass *c = G_OBJECT_CLASS (c);

  c->get_property = crank_shader_hook_get_property;
  c->set_property = crank_shader_hook_set_property;
  c->dispose = crank_shader_hook_dispose;
  c->finalize = crank_shader_hook_finalize;

  pspecs[PROP_NAME] =
  g_param_spec_string ("name", "name", "Name of hook",
                       NULL,
                       G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY |
                       G_PARAM_STATIC_STRINGS );

  /**
   * CrankShaderHook:qname: (type GQuark)
   *
   * Name of hook, as a GQuark.
   */
  pspecs[PROP_QNAME] =
  g_param_spec_uint ("qname", "qname", "Name of hook as GQuark",
                     0, G_MAXUINT, 0,
                     G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY |
                     G_PARAM_STATIC_STRINGS );

  pspecs[PROP_NICK] =
  g_param_spec_string ("nick", "nick", "Nick name of hook",
                       NULL,
                       G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY |
                       G_PARAM_STATIC_STRINGS );

  pspecs[PROP_BLURB] =
  g_param_spec_string ("blurb", "blurb", "Short description of hook",
                       NULL,
                       G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY |
                       G_PARAM_STATIC_STRINGS );

  pspecs[PROP_N_PARAMS] =
  g_param_spec_uint ("n-params", "Number of params", "Number of params",
                     0, G_MAXUINT, 0,
                     G_PARAM_READABLE | G_PARAM_STATIC_STRINGS );
}







//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_shader_hook_get_property (GObject    *object,
                                guint       prop_id,
                                GValue     *value,
                                GParamSpec *pspec)
{
  CrankShaderHook *self = (CrankShaderHook*) object;
  switch (prop_id)
    {
    case PROP_NAME:
      g_value_set_string (value, g_quark_to_string (self->name));
      break;

    case PROP_QNAME:
      g_value_set_uint (value, self->name);
      break;

    case PROP_NICK:
      g_value_set_string (value, self->nick);
      break;

    case PROP_BLURB:
      g_value_set_string (value, self->blurb);
      break;

    case PROP_N_PARAMS:
      g_value_set_uint (value, self->params->len);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
crank_shader_hook_set_property (GObject      *object,
                                guint         prop_id,
                                const GValue *value,
                                GParamSpec   *pspec)
{
  CrankShaderHook *self = (CrankShaderHook*) object;
  switch (prop_id)
    {
    case PROP_NAME:
        {
          const gchar* str = g_value_get_string (value);
          if (str != NULL)
            self->name = g_quark_from_string (str);
        }
      break;

    case PROP_QNAME:
        {
          GQuark quark = g_value_get_uint (value);
          if (quark != 0)
            self->name = quark;
        }
      break;

    case PROP_NICK:
      self->nick = g_value_dup_string (value);
      break;

    case PROP_BLURB:
      self->blurb = g_value_dup_string (value);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
crank_shader_hook_dispose (GObject *object)
{
  GObjectClass *pc = crank_shader_hook_parent_class;
  CrankShaderHook *self = (CrankShaderHook*) object;

  self->name = 0;
  g_clear_pointer (& self->nick, g_free);
  g_clear_pointer (& self->blurb, g_free);

  g_ptr_array_set_size (self->params, 0);

  pc->dispose (object);
}

static void
crank_shader_hook_finalize (GObject *object)
{
  GObjectClass *pc = crank_shader_hook_parent_class;
  CrankShaderHook *self = (CrankShaderHook*) object;

  g_ptr_array_unref (self->params);

  pc->finalize(object);
}







//////// Private functions /////////////////////////////////////////////////////

static gchar*
crank_shader_hook_generate_parameter (GParamSpec *param)
{
  gboolean readable;
  gboolean writable;

  GType         type;
  const gchar*  tstr;

  readable = (param->flags & G_PARAM_READABLE) != 0;
  writable = (param->flags & G_PARAM_WRITABLE) != 0;

  type = param->value_type;

  if (type == G_TYPE_INT)
    tstr = "int";
  else if (type == G_TYPE_FLOAT)
    tstr = "float";
  else if (type == G_TYPE_BOOLEAN)
    tstr = "boolean";

  return g_strdup_printf ("%s%s %s %s",
                          (readable) ? "in" : "",
                          (writable) ? "out" : "",
                          tstr,
                          g_param_spec_get_name (param));
}







//////// Public Functions //////////////////////////////////////////////////////

//////// Properties ////////////////////////////////////////////////////////////

/**
 * crank_shader_hook_get_name:
 * @hook: A Hook.
 *
 * Gets name of hook.
 *
 * Returns: (transfer none): Name of hook.
 */
const gchar*
crank_shader_hook_get_name (CrankShaderHook *hook)
{
  return g_quark_to_string (hook->name);
}

/**
 * crank_shader_hook_get_qname:
 * @hook: A Hook.
 *
 * Gets name of hook, as a GQuark.
 *
 * Returns: Name of hook.
 */
GQuark
crank_shader_hook_get_qname (CrankShaderHook *hook)
{
  return hook->name;
}

/**
 * crank_shader_hook_get_nick:
 * @hook: A Hook.
 *
 * Gets nick name of hook.
 *
 * Returns: (transfer none): Nick of hook.
 */
const gchar*
crank_shader_hook_get_nick (CrankShaderHook *hook)
{
  return hook->nick;
}

/**
 * crank_shader_hook_get_blurb:
 * @hook: A Hook.
 *
 * Gets short description of hook.
 *
 * Returns: (transfer none): Short description of hook.
 */
const gchar*
crank_shader_hook_get_blurb (CrankShaderHook *hook)
{
  return hook->blurb;
}

/**
 * crank_shader_hook_get_n_params:
 * @hook: A Hook.
 *
 * Gets number of parameters for this hook.
 *
 * Returns: Number of parameters.
 */
guint
crank_shader_hook_get_n_params (CrankShaderHook *hook)
{
  return hook->params->len;
}








//////// Parameters ////////////////////////////////////////////////////////////

/**
 * crank_shader_hook_add_param:
 * @hook: A Hook.
 * @param: A Parameter.
 *
 * Adds a parameter.
 *
 * Returns: index of newly added parameters.
 */
guint
crank_shader_hook_add_param (CrankShaderHook *hook,
                             GParamSpec      *param)
{
  g_ptr_array_add (hook->params, param);
  return hook->params->len - 1;
}

/**
 * crank_shader_hook_remove_param:
 * @hook: A Hook.
 * @param: A Param.
 *
 * Removes a parameter from hook.
 *
 * Returns: Whether @param was removed from @hook.
 */
gboolean
crank_shader_hook_remove_param (CrankShaderHook *hook,
                                GParamSpec      *param)
{
  return g_ptr_array_remove (hook->params, param);
}

/**
 * crank_shader_hook_get_param:
 * @hook: A Hook.
 * @index: Index.
 *
 * Gets parameter at @index.
 *
 * Returns: (transfer none): A Parameter of hook.
 */
GParamSpec*
crank_shader_hook_get_param (CrankShaderHook *hook,
                             const guint      index)
{
  return hook->params->pdata[index];
}

/**
 * crank_shader_hook_index_of_param:
 * @hook: A Hook.
 * @param: A Parameter.
 *
 * Get index of paramater.
 *
 * Returns: Index of @param.
 */
gint
crank_shader_hook_index_of_param (CrankShaderHook *hook,
                                  GParamSpec      *param)
{
  guint i;
  for (i = 0; i < hook->params->len; i++)
    {
      if (hook->params->pdata[i] == param)
        return i;
    }
  return -1;
}

/**
 * crank_shader_hook_get_params:
 * @hook: A Hook.
 * @nparams: (out) (optional): Number of parameters.
 *
 * Gets parameters as array.
 *
 * Returns: (array length=nparams) (transfer container): Parameters.
 */
GParamSpec**
crank_shader_hook_get_params (CrankShaderHook *hook,
                              guint           *nparams)
{
  if (nparams != NULL)
    *nparams = hook->params->len;

  return g_memdup (hook->params->pdata,
                   sizeof (GParamSpec*) * hook->params->len);
}








//////// Generate //////////////////////////////////////////////////////////////

gchar*
crank_shader_hook_generate_signiture (CrankShaderHook *hook,
                                      const gchar     *func_name)
{
  GString*  sig = g_string_new (NULL);
  guint i;

  g_string_printf (sig, "void %s (", func_name);

  for (i = 0; i < hook->params->len; i++)
    {
      GParamSpec *param = hook->params->pdata[i];
      gchar *pstr = crank_shader_hook_generate_parameter (param);

      if (i != 0)
        g_string_append (sig, ", ");

      g_string_append (sig, pstr);
      g_free (pstr);
    }

  g_string_append_c (sig, ')');

  return g_string_free (sig, FALSE);
}
