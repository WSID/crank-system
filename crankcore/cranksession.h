#ifndef CRANKSESSION_H
#define CRANKSESSION_H

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

#ifndef CRANKCORE_INSIDE
#error cranksession.h cannot be included directly: include crankcore.h
#endif


#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"

G_BEGIN_DECLS


//////// Type Declaration //////////////////////////////////////////////////////


#define CRANK_TYPE_SESSION (crank_session_get_type())
G_DECLARE_DERIVABLE_TYPE (CrankSession,
                          crank_session,
                          CRANK, SESSION,
                          CrankComposite)

/**
 * CrankSession:
 *
 * Instance structure.
 */

/**
 * CrankSessionClass:
 * @resume: Slot for signal CrankSession::resume
 * @pause: Slot for signal CrankSession::pause
 *
 * Virtual function table for #CrankSession
 */
struct _CrankSessionClass
{
  /*< private >*/
  CrankCompositeClass parent;

  /*< public >*/
  // Signals

  void (*resume)    (CrankSession *session);
  void (*pause)     (CrankSession *session);
};


//////// Constructors //////////////////////////////////////////////////////////

CrankSession   *crank_session_new (void);


//////// Properties ////////////////////////////////////////////////////////////

gboolean        crank_session_is_running (CrankSession *session);

void            crank_session_set_running (CrankSession   *session,
                                           const gboolean  running);


gfloat          crank_session_get_uptime (CrankSession *session);

void            crank_session_set_uptime (CrankSession *session,
                                          const gfloat  uptime);


//////// Running state /////////////////////////////////////////////////////////

void            crank_session_resume (CrankSession *session);

void            crank_session_pause (CrankSession *session);

G_END_DECLS

#endif /* CRANK_SESSION_H */
