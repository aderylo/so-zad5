#include "fs.h"
#include "sys/fcntl.h"
#include "file.h"
#include "vnode.h"
#include <stdio.h>

struct vnode *get_vnode(int fd) {
    struct filp *filp = get_filp(fd, VNODE_READ);
    struct vnode *vp = filp->filp_vno;
    unlock_filp(filp);
    return vp;
}

int do_notify(void) {
    struct vnode *file_ptr = get_vnode(m_in.m_lc_vfs_notify.fd);
    struct notify_wait *np;

    if (file_ptr == NULL) {
        printf("nie da sie uzyskac wskaznika do tego pliku\n");
        return EBADF;
    }
    if (m_in.m_lc_vfs_notify.event != NOTIFY_OPEN) {
        // na razie tylko open obsługujemy
        printf("zly deskryptor eventu\n");
        return EINVAL;
    }
    // na razie olejemy ENOTDIR
    if (NR_WAITING_FOR_NOTIFY >= NR_NOTIFY) {
        printf("za duzo procesow czeka\n");
        return ENONOTIFY;
    }

    printf("%d\n", ENONOTIFY);

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