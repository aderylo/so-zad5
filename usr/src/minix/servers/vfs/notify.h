#ifndef __VFS_NOTIFY_H__
#define __VFS_NOTIFY_H__


 struct notify_wait
{
    struct vnode* notify_vnode;
    struct fproc* notify_proc;
    int notify_event;
} notify_wait[NR_NOTIFY];

int NR_WAITING_FOR_NOTIFY;

#endif