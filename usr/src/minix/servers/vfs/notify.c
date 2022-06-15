#include "fs.h"
#include "vnode.h"
#include "file.h"
#include <fcntl.h>
#include <stdio.h>

int do_notify(void) {
//    struct fproc *caller = fp;
    struct filp *f;
    register struct vnode *vp;

    // got that from do_utimens
    if ((f = get_filp(job_m_in.m_lc_vfs_notify.fd, VNODE_READ)) == NULL)
        return (err_code);
    vp = f->filp_vno;        /* get vnode pointer */
    // there is some not explicitly stated lock on vnode as well as flip
    // look for unlock_flip(flip)

    printf("dupa\n");
    printf("%d", job_m_in.m_lc_vfs_notify.event);

    switch (job_m_in.m_lc_vfs_notify.event) {
        case NOTIFY_OPEN:
            suspend(FP_BLOCKED_ON_LOCK);
            break;
        default:
            // throw error
            break;
    }


    return (SUSPEND);
//	return(ENOSYS);  // TODO: implementacja VFS_NOTIFY
}
