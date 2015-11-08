/*
 * Copyright (c) 2015, Federico G. Schwindt <fgsch@lodoss.net>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>

#include <utf8proc.h>

#include "cache/cache.h"

#include "vrt.h"
#include "vsa.h"

#include "vcc_if.h"

#ifndef VRT_CTX
#define VRT_CTX		const struct vrt_ctx *ctx
#endif

VCL_STRING __match_proto__(td_utf8_transform)
vmod_transform(VRT_CTX, VCL_STRING s, VCL_INT options)
{
	char *p;
	utf8proc_ssize_t len;
	unsigned u;

	CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);

	if (!s || !*s) {
		VSLb(ctx->vsl, SLT_Error, "utf8.transform: No input");
		return (NULL);
	}

	u = WS_Reserve(ctx->ws, 0);
	if (!u) {
		VSLb(ctx->vsl, SLT_Error, "utf8.transform: Out of workspace");
		return (NULL);
	}
	p = ctx->ws->f;

	/* Use composed if not specified. */
	if ((options & UTF8PROC_STRIPMARK) &&
	    (options & (UTF8PROC_COMPOSE | UTF8PROC_DECOMPOSE)) == 0)
		options |= UTF8PROC_COMPOSE;
	/* Input is NULL terminated. */
	options |= UTF8PROC_NULLTERM;

	len = utf8proc_decompose((utf8proc_uint8_t *)s, 0 /* IGNORED */,
	    (utf8proc_int32_t *)p, u, options);
	if (len < 0) {
		VSLb(ctx->vsl, SLT_Error,
		    "utf8.transform: utf8proc_decompose: %s",
		    utf8proc_errmsg(len));
		WS_Release(ctx->ws, 0);
		return (NULL);
	}

	len = utf8proc_reencode((utf8proc_int32_t *)p, len, options);
	assert(len > 0);
	assert(len < u);

	WS_Release(ctx->ws, len + 1);
	return (p);
}
