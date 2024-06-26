

/*
**	(c) COPYRIGHT MIT 1995.
**	Please first read the full copyright statement in the file COPYRIGH.
*/

/*
**
** AUTHORS:
**	AL	Ari Luotonen    luotonen@dxcern.cern.ch
**	MD	Mark Donszelmann    duns@vxdeop.cern.ch
**
** HISTORY:
**	11 Dec 93  AL	Written based on the old HTHandle().
**
*/

#ifndef HTREQUEST_H
#define HTREQUEST_H

#include "HTUtils.h"
#include "HTFormat.h"
#include "HTAccess.h"

/*
 * Makes a full reference to the server itself given a URL with only
 * the path portion.  I.e. will add http:, hostname and port parts.
 *
 * Returns NULL if URL is already full.
 */
PUBLIC char *HTFullSelfReference PARAMS((CONST char *url));

/*
 * Produce a redirection message document for browsers without
 * redirection support.
 */
PUBLIC char *HTRedirectionMsg PARAMS((char *url));

PUBLIC HTStream *HTScriptWrapper PARAMS((HTRequest * req, char **extra_headers, int extra_count, HTStream *sink));

PUBLIC HTRequest *HTParseRequest PARAMS((HTInputSocket * isoc));

PUBLIC int HTTranslateRequest PARAMS((HTRequest * req));

PUBLIC char *HTReplyHeaders PARAMS((HTRequest * req));

PUBLIC char *HTReplyHeadersWith PARAMS((HTRequest * req, char **extras, int extra_cnt));

PUBLIC HTList *hbuf_http_env_vars PARAMS((HTRequest * req));
PUBLIC char *hbuf_proxy_headers PARAMS((HTRequest * req));

#endif
