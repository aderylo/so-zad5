#include "fs.h"
#include "sys/fcntl.h"
#include "file.h"
#include "vnode.h"
#include <stdio.h>

struct vnode *get_vnode(int fd) {
    struct filp *filp = get_filp(fd, VNODE_READ);
    if (!filp)
        return NULL;
    struct vnode *vp = filp->filp_vno;
    unlock_filp(filp);
    return vp;
}

int do_notify(void) {
    struct vnode *file_ptr = get_vnode(m_in.m_lc_vfs_notify.fd);
    struct notify_wait *np;

    if (NR_WAITING_FOR_NOTIFY >= NR_NOTIFY)
        return ENONOTIFY;
    else if (file_ptr == NULL)
        return EBADF;

    switch (m_in.m_lc_vfs_notify.event) {
        case NOTIFY_OPEN:
            break;
        case NOTIFY_TRIOPEN:
            if (file_ptr->v_ref_count >= 3)
                return OK;
            break;
        case NOTIFY_CREATE:
            if (!S_ISDIR(file_ptr->v_mode))
                return ENOTDIR;
            break;
        case NOTIFY_MOVE:
            if (!S_ISDIR(file_ptr->v_mode))
                return ENOTDIR;
            break;
        default:
            return EINVAL;
    }


    for (np = &notify_wait[0]; np < &notify_wait[NR_NOTIFY]; np++) {
        if (np->notify_event == 0) {
            np->notify_proc = fp;
            np->notify_vnode = file_ptr;
            np->notify_event = job_m_in.m_lc_vfs_notify.event;
            NR_WAITING_FOR_NOTIFY++;
            break;
        }
    }

    suspend(FP_BLOCKED_ON_NOTIFY);
    return SUSPEND;
    return OK;
}