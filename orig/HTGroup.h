

#ifndef HTGROUP_H
#define HTGROUP_H

#include "HTUtils.h"
#include "HTAAUtil.h" /* HTAAFailReason */
#include "HTList.h"
#include "HTWild.h"

#ifdef SHORT_NAMES
#define HTAApGrD HTAA_parseGroupDef
#define HTAArGrR HTAA_resolveGroupReferences
#define HTAApGrD HTAA_printGroupDef
#define HTAAGD_d GroupDef_delete
#define HTAAuIIG HTAA_userAndInetInGroup
#endif /* SHORT_NAMES */

typedef HTList GroupDefList;
typedef HTList ItemList;

typedef struct
{
    char *group_name;
    ItemList *item_list;
} GroupDef;

PUBLIC GroupDef *HTAA_parseGroupDef PARAMS((FILE * fp));

// References to groups(by their name) are resolved from PUBLIC void HTAA_resolveGroupReferences
//     PARAMS((GroupDef * group_def, GroupDefList *group_def_list));
// 
// If group file is already in cache returns a pointer to previously read group definition
//     list.PUBLIC GroupDefList *HTAA_readGroupFile PARAMS((CONST char *filename));
// 
// should only be used to free group definitions read by PUBLIC void GroupDef_delete PARAMS((GroupDef * group_def));

PUBLIC void HTAA_printGroupDef PARAMS((GroupDef * group_def));

// This function checks both the username and the internet address.
    /* PUBLIC					HTAA_userAndInetInGroup()
    **		CHECK IF USER BELONGS TO TO A GIVEN GROUP
    **		AND THAT THE CONNECTION COMES FROM AN
    **		ADDRESS THAT IS ALLOWED BY THAT GROUP
    ** ON ENTRY:
    **	group		the group definition structure.
    **	username	connecting user.
    **	ip_number	browser host IP number, optional.
    **	ip_name		browser host IP name, optional.
    **			However, one of ip_number or ip_name
    **			must be given.
    ** ON EXIT:
    **	returns		HTAA_IP_MASK, if IP address mask was
    **			reason for failing.
    **			HTAA_NOT_MEMBER, if user does not belong
    **			to the group.
    **			HTAA_OK if both IP address and user are ok.
    */
    PUBLIC HTAAFailReason HTAA_userAndInetInGroup PARAMS((GroupDef * group, char *username, char *ip_number,
                                                          char *ip_name));
PUBLIC BOOL HTIpMaskMatch PARAMS((HTPattern * pat, CONST char *ip_number, CONST char *ip_name));

#endif /* not HTGROUP_H */