

/*
**	(c) COPYRIGHT MIT 1995.
**	Please first read the full copyright statement in the file COPYRIGH.
*/

/*
 */

#ifndef HTCONFIG_H
#define HTCONFIG_H

#include "HTUtils.h"
#include "HTList.h"
#include "HTAccess.h"
#include "HTWild.h"
#include "HTRules.h"
#include "HTAAProt.h"

#define DEFAULT_INPUT_TIMEOUT 120        /*  2 mins */
#define DEFAULT_OUTPUT_TIMEOUT 1200      /* 20 mins */
#define DEFAULT_SCRIPT_TIMEOUT 300       /*  5 mins */
#define DEFAULT_CLEANUP_TIMEOUT 15       /* 15 secs to write to log file */
#define DEFAULT_CACHE_LM_FACTOR 0.1      /* 10% of the time last-modified */
#define DEFAULT_REFRESH_INTERVAL 1200000 /* About 2 weeks */

typedef struct _HTRule
{
    struct _HTRule *next;
    HTRuleOp op;
    HTPattern *pat;
    HTPattern *eqv;
    HTUidGid *ids;
    char *prot_file;
    HTAAProt *prot_setup;
} HTRule;

typedef enum
{
    SERVER_TYPE_UNINITIALIZED = 0,
    SERVER_TYPE_STANDALONE,
    SERVER_TYPE_INETD
} HTServType;

typedef struct _HTServerConfig
{
    char *hostname;                 /* Used for CGI scripts		*/
    HTServType server_type;         /* Standalone or inetd		*/
    int port;                       /* Default port number string	*/
    BOOL no_bg;                     /* Don't auto-go background	*/
    BOOL standalone;                /* Am I standalone?		*/
    char *server_root;              /* Server's "home directory"	*/
    int security_level;             /* 0 = normal, 1 = high		*/
    char *errormsg_path;            /* URL for error messages	*/
    char *icon_path;                /* URL for Standard icons	*/
    BOOL icons_inited;              /* If not we'll use defaults	*/
    int input_timeout;              /* Timeout for reading request	*/
    int output_timeout;             /* Timeout for sending response	*/
    int script_timeout;             /* Timeout for scripts		*/
    char *pid_file;                 /* File to write the pid number	*/
    BOOL do_accept_hack;            /* Send even if not Accept'ed	*/
    BOOL disabled[MAX_METHODS + 1]; /* Disabled methods		*/
    BOOL do_setuid;                 /* Do setuid() to auth'd uid	*/
    int max_content_len_buf;        /* How much to buffer for c-l	*/
    HTList *no_log;                 /* Hosts for which no logging	*/
    BOOL new_logfile_format;        /* Use new common logfile format*/
    BOOL use_gmt;                   /* Use GMT instead of localtime	*/
    char *user_dir;                 /* User supported directory name*/
    char *user_id;                  /* Default user id		*/
    char *group_id;                 /* Default group id		*/
    char *parent_uid;               /* User id for parent process	*/
    char *parent_gid;               /* Group id for parent process	*/
    BOOL do_rfc931;                 /* Should we check remote ident	*/
    BOOL do_dns_lookup;             /* Get the DNS name for client	*/
    BOOL do_linger;                 /* Is lingering really necessary*/
    char *meta_dir;                 /* Directory for metafiles	*/
    char *meta_suffix;              /* Suffix for metafiles		*/
    BOOL always_welcome;            /* Redirect directory names to	*/
                                    /* welcome page on that dir.	*/
    char *access_log_name;          /* Access log file name		*/
    char *proxy_log_name;           /* Proxy access log file name	*/
    char *cache_log_name;           /* Cache access log file name	*/
    char *error_log_name;           /* Error log file name		*/
    char *log_file_date_ext;        /* Log file Date Extension	*/
    BOOL reloading;                 /* Are we now reloding rules	*/
    HTList *rule_files;             /* All loaded files by name	*/
} HTServerConfig;

typedef struct _HTResourceConfig
{
    HTRule *rule_head;   /* Rules (first rule)		*/
    HTRule *rule_tail;   /* Last rule			*/
    HTList *named_prots; /* Named protections setups	*/
    char *search_script; /* Search script name.		*/
    char *put_script;    /* Script to handle PUT		*/
    char *post_script;   /* Script to handle POST	*/
    char *delete_script; /* Script to handle DELETE	*/
} HTResourceConfig;

typedef struct _HTPatTime
{
    HTPattern *pat;
    time_t time;
    struct _HTPatTime *next;
    struct _HTPatTime *last; /* Only set for the first node in list	*/
} HTPatTime;

typedef struct _HTPatFact
{
    HTPattern *pat;
    float factor;
    struct _HTPatFact *next;
    struct _HTPatFact *last; /* Only set for the first node in list	*/
} HTPatFact;

typedef struct _HTCacheConfig
{
    BOOL caching_explicitly_off;       /* Is caching disabled		*/
    char *cache_root;                  /* Cache directory for gateway	*/
    HTList *no_caching;                /* No caching if matching these	*/
    HTList *cache_only;                /* Cache only if matching these	*/
    HTPatTime *cache_clean;            /* Remove always after this time*/
    time_t cache_clean_def;            /* (by template and a default).	*/
    HTPatTime *cache_unused;           /* Remove after unused this long*/
    time_t cache_unused_def;           /* (by template and a default).	*/
    HTPatTime *cache_exp;              /* Default expiry when not given*/
    time_t cache_exp_def;              /* (by template and a default).	*/
    HTPatTime *cache_refresh_interval; /* Force cache refresh		*/
    HTPatFact *cache_lm_factors;       /* For approximating Expires:	*/
    long cache_max_k;                  /* Default size in K (5MB small)*/
    int cache_max_f;                   /* At most this many cache files*/
    int cache_limit_1;                 /* Size no problem until 200K	*/
    int cache_limit_2;                 /* No caching after 4MB		*/
    time_t cache_time_margin;          /* Time accuracy (in seconds)	*/
    time_t cache_lock_timeout;         /* Break hanging locks		*/
    BOOL keep_expired;                 /* Use the max cache capasity	*/
    BOOL do_exp_check;                 /* Do expiry check		*/
    BOOL cache_no_connect;             /* Use only local cache		*/
    BOOL gc_disabled;                  /* Never do garbage collection	*/
    time_t gc_daily_gc;                /* gc daily at 3:00am		*/
    int gc_mem_usage_control;          /* How radical mem usage	*/
} HTCacheConfig;

/*
 *	Global variables for server, resource and cache configuration
 */
extern HTServerConfig sc;   /* Server configuration		*/
extern HTResourceConfig rc; /* Resource configuration	*/
extern HTCacheConfig cc;    /* Cache & proxy configuration	*/

/*
 *	HTDefaultConfig() should be called in as the first thing when
 *	the server starts to initialize the default configuration.
 */
PUBLIC void HTDefaultConfig NOPARAMS;

/*
 *	Add rule to current resource configuration;
 *	this is NOT for Protect and DefProt rules,
 *	ONLY for Map, Pass, Fail, Exec, and Redirect
 */
PUBLIC HTRule *HTAppendRule PARAMS((HTRuleOp op, CONST char *pattern, CONST char *equiv));

/*
 *	HTLoadConfig(filename) opens the configuration file, reads
 *	and parses it, and memorizes the filename so that server
 *	restart can reload the same file.
 */
PUBLIC BOOL HTLoadConfig PARAMS((char *filename));

/*
 *	HTServerInit() does final server configuration initialization;
 *	it initializes standard icons and open log files.
 *
 *	After the first time functions as the server restart function,
 *	i.e. also reloads the configuration files, and re-opens all
 *	the log files.
 */
PUBLIC BOOL HTServerInit NOPARAMS;

/*
 *	Translate request through the rule system
 */
PUBLIC BOOL HTTranslateReq PARAMS((HTRequest * req));

/*
 *	Utility functions for cache module
 */
PUBLIC time_t get_default_expiry PARAMS((char *url));
PUBLIC time_t get_unused PARAMS((char *url));
PUBLIC time_t get_clean PARAMS((char *url));
PUBLIC time_t get_refresh_interval PARAMS((char *url));
PUBLIC float get_lm_factor PARAMS((char *url));

#endif /* HTCONFIG_H */
