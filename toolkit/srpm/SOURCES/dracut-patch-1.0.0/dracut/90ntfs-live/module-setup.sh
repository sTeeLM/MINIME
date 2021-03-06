#!/bin/bash
# -*- mode: shell-script; indent-tabs-mode: nil; sh-basic-offset: 4; -*-
# ex: ts=8 sw=4 sts=4 et filetype=sh

check() {
    # a live host-only image doesn't really make a lot of sense
    [[ $hostonly ]] && return 1
    return 255
}

depends() {
    # if dmsetup is not installed, then we cannot support fedora/red hat
    # style live images
    return 0
}

installkernel() {
    return 0
}

install() {
    inst_multiple ntfs-3g ntfs-3g.probe ntfs-3g.secaudit ntfs-3g.usermap lowntfs-3g ntfsmount mount.lowntfs-3g mount.ntfs-3g mount.ntfs-fuse
    inst_script "$moddir/mount.ntfs.sh" "/sbin/mount.ntfs"
}
