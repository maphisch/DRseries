#!/bin/sh
#
# "$Id: cups.sh.in 6649 2007-07-11 21:46:42Z mike $"
#
#   Startup/shutdown script for the Common UNIX Printing System (CUPS).
#
#   Copyright 2007 by Apple Inc.
#   Copyright 1997-2007 by Easy Software Products, all rights reserved.
#
#   These coded instructions, statements, and computer programs are the
#   property of Apple Inc. and are protected by Federal copyright
#   law.  Distribution and use rights are outlined in the file "LICENSE.txt"
#   which should have been included with this file.  If this file is
#   file is missing or damaged, see the license at "http://www.cups.org/".
#

#### OS-Dependent Information

#
#   Linux chkconfig stuff:
#
#   chkconfig: 235 99 00
#   description: Startup/shutdown script for the Common UNIX \
#                Printing System (CUPS).
#

#
#   NetBSD 1.5+ rcorder script lines.  The format of the following two
#   lines is very strict -- please don't add additional spaces!
#
# PROVIDE: cups
# REQUIRE: DAEMON
#


#### OS-Dependent Configuration

case "`uname`" in
	IRIX*)
		IS_ON=/sbin/chkconfig

		if $IS_ON verbose; then
			ECHO=echo
		else
			ECHO=:
		fi
		ECHO_OK=:
		ECHO_ERROR=:
		;;

	*BSD*)
        	IS_ON=:
		ECHO=echo
		ECHO_OK=:
		ECHO_ERROR=:
		;;

	Darwin*)
		. /etc/rc.common

		if test "${CUPS:=-YES-}" = "-NO-"; then
			exit 0
		fi

        	IS_ON=:
		ECHO=ConsoleMessage
		ECHO_OK=:
		ECHO_ERROR=:
		;;

	Linux*)
		IS_ON=/bin/true
		if test -f /etc/init.d/functions; then
			. /etc/init.d/functions
			ECHO=echo
			ECHO_OK="echo_success"
			ECHO_ERROR="echo_failure"
		else
			ECHO=echo
			ECHO_OK=:
			ECHO_ERROR=:
		fi
		;;

	*)
		IS_ON=/bin/true
		ECHO=echo
		ECHO_OK=:
		ECHO_ERROR=:
		;;
esac

#### OS-Independent Stuff

#
# Set the timezone, if possible...  This allows the scheduler and
# all child processes to know the local timezone when reporting
# dates and times to the user.  If no timezone information is
# found, then Greenwich Mean Time (GMT) will probably be used.
#

for file in /etc/TIMEZONE /etc/rc.config /etc/sysconfig/clock; do
	if test -f $file; then
	        . $file
	fi
done

if test "x$ZONE" != x; then
	TZ="$ZONE"
fi

if test "x$TIMEZONE" != x; then
	TZ="$TIMEZONE"
fi

if test "x$TZ" != x; then
	export TZ
fi

#
# Don't use TMPDIR environment variable from init script, as that can
# cause cupsd to set TempDir to a user's temporary directory instead
# of the default...
#

unset TMPDIR


#
# Make sure we have the standard program directories in the path
# since some operating systems (this means YOU HP-UX!) don't
# provide a standard path on boot-up...
#

if test "x$PATH" = x; then
	PATH="/bin:/usr/bin:/sbin:/usr/sbin"
else
	PATH="/bin:/usr/bin:/sbin:/usr/sbin:$PATH"
fi

export PATH

#
# See if the CUPS server (cupsd) is running...
#

case "`uname`" in
	HP-UX* | AIX* | SINIX*)
		pid=`ps -e | awk '{if (match($4, ".*/cupsd$") || $4 == "cupsd") print $1}'`
		;;
	IRIX* | SunOS*)
		pid=`ps -e | nawk '{if (match($4, ".*/cupsd$") || $4 == "cupsd") print $1}'`
		;;
	UnixWare*)
		pid=`ps -e | awk '{if (match($6, ".*/cupsd$") || $6 == "cupsd") print $1}'`
		. /etc/TIMEZONE
		;;
	OSF1*)
		pid=`ps -e | awk '{if (match($5, ".*/cupsd$") || $5 == "cupsd") print $1}'`
		;;
	Linux* | *BSD* | Darwin*)
		pid=`ps ax | awk '{if (match($5, ".*/cupsd$") || $5 == "cupsd") print $1}'`
		;;
	*)
		pid=""
		;;
esac

#
# Start or stop the CUPS server based upon the first argument to the script.
#

case $1 in
	start | restart | reload)
		if $IS_ON cups; then
			if test "$pid" != ""; then
				kill -HUP $pid
			else
				prefix=/nfsroot/hico7723/rootfs
				exec_prefix=/nfsroot/hico7723/rootfs
				/nfsroot/hico7723/rootfs/sbin/cupsd
				if test $? != 0; then
					$ECHO_FAIL
					$ECHO "cups: unable to $1 scheduler."
					exit 1
				fi
			fi
			$ECHO_OK
			$ECHO "cups: ${1}ed scheduler."
		fi
		;;

	stop)
		if test "$pid" != ""; then
			kill $pid
			$ECHO_OK
			$ECHO "cups: stopped scheduler."
		fi
		;;

	status)
		if test "$pid" != ""; then
			echo "cups: scheduler is running."
		else
			echo "cups: scheduler is not running."
		fi
		;;

	start_msg)
		# HP-UX non-standard...
		echo "Starting CUPS Server"
		;;

	stop_msg)
		# HP-UX non-standard...
		echo "Starting CUPS Server"
		;;

	*)
		echo "Usage: cups {reload|restart|start|status|stop}"
		exit 1
		;;
esac

#
# Exit with no errors.
#

exit 0


#
# End of "$Id: cups.sh.in 6649 2007-07-11 21:46:42Z mike $".
#
