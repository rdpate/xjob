Optionally Parallel
====

If jobserver is on $PATH, then use it, starting if needed.  Otherwise run background jobs synchronously:

    if which jobserver >/dev/null 2>&1; then
        jobserver started || exec jobserver init "$0" "$@"
        bg_job() {
            (trap 'jobserver release' exit; command "$@" </dev/null) &
            jobserver acquire
            }
    else
        # synchronous
        bg_job() { "$@" </dev/null; }
        # redirect stdin to avoid unintentional differences
        fi

Note: this will "exec $0", which could change behavior compared to "sh -flags file".