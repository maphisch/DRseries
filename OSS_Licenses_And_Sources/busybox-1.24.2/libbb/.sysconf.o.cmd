cmd_libbb/sysconf.o := /home/mschreiber/Project/buildroot-2016.05/output/host/usr/bin/sh4a-buildroot-linux-gnu-gcc -Wp,-MD,libbb/.sysconf.o.d   -std=gnu99 -Iinclude -Ilibbb  -include include/autoconf.h -D_GNU_SOURCE -DNDEBUG -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -D"BB_VER=KBUILD_STR(1.24.2)" -DBB_BT=AUTOCONF_TIMESTAMP  -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64  -Os  -Wall -Wshadow -Wwrite-strings -Wundef -Wstrict-prototypes -Wunused -Wunused-parameter -Wunused-function -Wunused-value -Wmissing-prototypes -Wmissing-declarations -Wno-format-security -Wdeclaration-after-statement -Wold-style-definition -fno-builtin-strlen -finline-limit=0 -fomit-frame-pointer -ffunction-sections -fdata-sections -fno-guess-branch-probability -funsigned-char -static-libgcc -falign-functions=1 -falign-jumps=1 -falign-labels=1 -falign-loops=1 -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-builtin-printf -Os     -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(sysconf)"  -D"KBUILD_MODNAME=KBUILD_STR(sysconf)" -c -o libbb/sysconf.o libbb/sysconf.c

deps_libbb/sysconf.o := \
  libbb/sysconf.c \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/stdc-predef.h \
  include/libbb.h \
    $(wildcard include/config/feature/shadowpasswds.h) \
    $(wildcard include/config/use/bb/shadow.h) \
    $(wildcard include/config/selinux.h) \
    $(wildcard include/config/feature/utmp.h) \
    $(wildcard include/config/locale/support.h) \
    $(wildcard include/config/use/bb/pwd/grp.h) \
    $(wildcard include/config/lfs.h) \
    $(wildcard include/config/feature/buffers/go/on/stack.h) \
    $(wildcard include/config/feature/buffers/go/in/bss.h) \
    $(wildcard include/config/feature/verbose.h) \
    $(wildcard include/config/feature/ipv6.h) \
    $(wildcard include/config/feature/seamless/xz.h) \
    $(wildcard include/config/feature/seamless/lzma.h) \
    $(wildcard include/config/feature/seamless/bz2.h) \
    $(wildcard include/config/feature/seamless/gz.h) \
    $(wildcard include/config/feature/seamless/z.h) \
    $(wildcard include/config/feature/check/names.h) \
    $(wildcard include/config/feature/prefer/applets.h) \
    $(wildcard include/config/long/opts.h) \
    $(wildcard include/config/feature/getopt/long.h) \
    $(wildcard include/config/feature/pidfile.h) \
    $(wildcard include/config/feature/syslog.h) \
    $(wildcard include/config/feature/individual.h) \
    $(wildcard include/config/echo.h) \
    $(wildcard include/config/printf.h) \
    $(wildcard include/config/test.h) \
    $(wildcard include/config/kill.h) \
    $(wildcard include/config/chown.h) \
    $(wildcard include/config/ls.h) \
    $(wildcard include/config/xxx.h) \
    $(wildcard include/config/route.h) \
    $(wildcard include/config/feature/hwib.h) \
    $(wildcard include/config/desktop.h) \
    $(wildcard include/config/feature/crond/d.h) \
    $(wildcard include/config/use/bb/crypt.h) \
    $(wildcard include/config/feature/adduser/to/group.h) \
    $(wildcard include/config/feature/del/user/from/group.h) \
    $(wildcard include/config/ioctl/hex2str/error.h) \
    $(wildcard include/config/feature/editing.h) \
    $(wildcard include/config/feature/editing/history.h) \
    $(wildcard include/config/feature/editing/savehistory.h) \
    $(wildcard include/config/feature/tab/completion.h) \
    $(wildcard include/config/feature/username/completion.h) \
    $(wildcard include/config/feature/editing/vi.h) \
    $(wildcard include/config/feature/editing/save/on/exit.h) \
    $(wildcard include/config/pmap.h) \
    $(wildcard include/config/feature/show/threads.h) \
    $(wildcard include/config/feature/ps/additional/columns.h) \
    $(wildcard include/config/feature/topmem.h) \
    $(wildcard include/config/feature/top/smp/process.h) \
    $(wildcard include/config/killall.h) \
    $(wildcard include/config/pgrep.h) \
    $(wildcard include/config/pkill.h) \
    $(wildcard include/config/pidof.h) \
    $(wildcard include/config/sestatus.h) \
    $(wildcard include/config/unicode/support.h) \
    $(wildcard include/config/feature/mtab/support.h) \
    $(wildcard include/config/feature/clean/up.h) \
    $(wildcard include/config/feature/devfs.h) \
  include/platform.h \
    $(wildcard include/config/werror.h) \
    $(wildcard include/config/big/endian.h) \
    $(wildcard include/config/little/endian.h) \
    $(wildcard include/config/nommu.h) \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/lib/gcc/sh4a-buildroot-linux-gnu/4.9.3/include-fixed/limits.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/lib/gcc/sh4a-buildroot-linux-gnu/4.9.3/include-fixed/syslimits.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/limits.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/features.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/sys/cdefs.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/wordsize.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/gnu/stubs.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/posix1_lim.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/local_lim.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/linux/limits.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/posix2_lim.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/xopen_lim.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/stdio_lim.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/byteswap.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/byteswap.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/types.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/typesizes.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/byteswap-16.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/endian.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/endian.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/lib/gcc/sh4a-buildroot-linux-gnu/4.9.3/include/stdint.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/stdint.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/wchar.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/lib/gcc/sh4a-buildroot-linux-gnu/4.9.3/include/stdbool.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/unistd.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/posix_opt.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/environments.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/lib/gcc/sh4a-buildroot-linux-gnu/4.9.3/include/stddef.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/confname.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/getopt.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/ctype.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/xlocale.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/dirent.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/dirent.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/errno.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/errno.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/linux/errno.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/asm/errno.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/asm-generic/errno.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/asm-generic/errno-base.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/fcntl.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/fcntl.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/fcntl-linux.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/uio.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/sys/types.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/time.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/sys/select.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/select.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/sigset.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/time.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/sys/sysmacros.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/pthreadtypes.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/stat.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/inttypes.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/netdb.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/netinet/in.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/sys/socket.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/sys/uio.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/socket.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/socket_type.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/sockaddr.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/asm/socket.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/asm-generic/socket.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/asm/sockios.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/in.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/rpc/netdb.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/siginfo.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/netdb.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/setjmp.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/setjmp.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/signal.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/signum.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/sigaction.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/sigcontext.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/asm/sigcontext.h \
    $(wildcard include/config/cpu/sh5.h) \
    $(wildcard include/config/cpu/sh4.h) \
    $(wildcard include/config/cpu/sh2a.h) \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/sigstack.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/sys/ucontext.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/sigthread.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/stdio.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/libio.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/_G_config.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/wchar.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/lib/gcc/sh4a-buildroot-linux-gnu/4.9.3/include/stdarg.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/sys_errlist.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/stdlib.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/waitflags.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/waitstatus.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/alloca.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/stdlib-float.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/string.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/libgen.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/poll.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/sys/poll.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/poll.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/sys/ioctl.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/ioctls.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/asm/ioctls.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/asm/ioctl.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/asm-generic/ioctl.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/ioctl-types.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/sys/ttydefaults.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/sys/mman.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/mman.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/mman-linux.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/sys/stat.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/sys/time.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/sys/wait.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/termios.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/termios.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/timex.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/sys/param.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/param.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/linux/param.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/asm/param.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/asm-generic/param.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/pwd.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/grp.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/shadow.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/paths.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/mntent.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/sys/statfs.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/statfs.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/selinux/selinux.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/selinux/context.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/selinux/flask.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/selinux/av_permissions.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/utmpx.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/bits/utmpx.h \
  /home/mschreiber/Project/buildroot-2016.05/output/host/usr/sh4a-buildroot-linux-gnu/sysroot/usr/include/arpa/inet.h \
  include/xatonum.h \

libbb/sysconf.o: $(deps_libbb/sysconf.o)

$(deps_libbb/sysconf.o):
