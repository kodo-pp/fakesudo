#!/usr/bin/env bash

g_username=root
g_argv=("$@")

function show_help_and_exit {
    echo "Usage: sudo [-u user] <command> [arguments...]" 2>&1
    echo "Run command with libfakesudo.so set up and preloaded" 2>&1
    echo "" 2>&1
    echo "Options:" 2>&1
    echo "    -u|--user <USER>          Specify faked user name (default: root)" 2>&1
    exit 1
}

function parse_options {
    while [[ "$#" -gt 0 ]]; do
        case "$1" in
            --help|-h)
                show_help_and_exit
                ;;
            -u|--user)
                if [[ -z "$2" ]]; then
                    echo "Username not provided" >&2
                    show_help_and_exit
                fi
                g_username="$2"
                shift
                shift
                ;;
            -*)
                echo "Invalid options: '$1'" >&2
                show_help_and_exit
                ;;
            *)
                g_argv=("$@")
                break
                ;;
        esac
    done
}


function get_user_id {
    if ! getent passwd "$1" >/dev/null; then
        return 1
    fi
    getent passwd "$1" | (IFS=: read username x uid remaining_args; echo "${uid}")
}


function main {
    parse_options "$@"
    local uid="$(get_user_id "${g_username}")"
    if [[ -z "${uid}" ]]; then
        echo "No such user" >&2;
        exit 1
    fi
    
    export LD_PRELOAD='libfakesudo.so'
    export LIBFAKESUDO_UID="${uid}"
    exec "${g_argv[@]}"
}

main "$@"
