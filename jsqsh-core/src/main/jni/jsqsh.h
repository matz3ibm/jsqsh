/*
 * jsqsh.h - Public interface for POSIX API calls
 *
 * Copyright 2007-2012 Scott C. Gray
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef jsqsh_h_included
#define jsqsh_h_included

#include "config.h"
#include <jni.h>

#if defined(_MSC_VER) && _MSC_VER > 850
#define MS_WIN32
#endif

/*
 * This macro lets me easily re-package the JNI interface if
 * at all necessary.
 */
#define JSQSH_PKG(f) Java_org_sqsh_jni_ShellManager_##f

/*
 * These macros provide basic C assertions except that the results
 * of the assertions can be handled in the java code.
 */
#define DEBUG 1
#if defined(DEBUG)
#define ASSERT(e) \
        (void)((e) ? 0 : jsqsh_assert_fail(#e, __FILE__, __LINE__))
#define ASSERT_JNI(env, e) \
        (void)((e) ? 0 : jsqsh_assert_jni_fail(env, #e, __FILE__, __LINE__))
#else
#define ASSERT(e)
#define ASSERT_JNI(env, e)
#endif

/*
 * Internal utilities (jsqsh_util.c)
 */
void    jsqsh_assert_fail     (char *expr, char *file, int line);
void    jsqsh_assert_jni_fail (JNIEnv *env, char *expr, char *file, int line);
void    jsqsh_debug           (char *message, ...);
void    jsqsh_info            (char *message, ...);
void    jsqsh_warn            (char *message, ...);
void    jsqsh_error           (char *message, ...);
void    jsqsh_fatal           (char *message, ...);
void    jsqsh_throw           (JNIEnv *env, int errnum, char *subclass);
JNIEnv* jsqsh_getenv       ();

/*
 * Platform specific functions
 */
int  jsqsh_popen (JNIEnv *env, char **args, jlong *pid, jlong *fd);
int  jsqsh_exec  (JNIEnv *env, char **args, jlong *pid);
void jsqsh_close (JNIEnv *env, jlong jfd);
int  jsqsh_wait  (JNIEnv *env, jlong pid);
void jsqsh_write (JNIEnv *env, jlong fd, void *buf, int len);
int  jsqsh_width (JNIEnv *env);

extern JavaVM *g_jvm;

#endif /* jsqsh_h_included */
