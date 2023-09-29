#!/bin/bash

usage () {
  echo "Sintax: change_frequencies_p_states.sh min_perf_pct max_perf_pct <command_to_launch> <args>"
  echo "This scripts requires the intel_pstate driver enabled and root privileges"
  echo "See https://www.kernel.org/doc/html/v4.12/admin-guide/pm/intel_pstate.html#"
  echo "for more information"
  exit 1 
}

check_required_intel_pstate_files ()
{
  if [ ! -f /sys/devices/system/cpu/intel_pstate/min_perf_pct ] || \
   [ ! -f /sys/devices/system/cpu/intel_pstate/max_perf_pct ];
  then
    echo "Unable to find intel_pstate control files"
    usage 
  fi
 }



[ "$UID" -eq 0 ] || usage
check_required_intel_pstate_files

if [ "$#" -lt 3 ]; then
  usage
fi

# store oll perf_pct_values
old_min_perf_pct=$(cat /sys/devices/system/cpu/intel_pstate/min_perf_pct)
old_max_perf_pct=$(cat /sys/devices/system/cpu/intel_pstate/max_perf_pct)

# set the new input values
echo "$1" > /sys/devices/system/cpu/intel_pstate/min_perf_pct
echo "$2" > /sys/devices/system/cpu/intel_pstate/max_perf_pct
shift 2

# launch the command with perf
sudo perf stat -a -e power/energy-cores/ -r 2 "$@"

# restore old values
echo "${old_min_perf_pct}" > /sys/devices/system/cpu/intel_pstate/min_perf_pct
echo "${old_max_perf_pct}" > /sys/devices/system/cpu/intel_pstate/max_perf_pct
# warning if the program fails, this script is incorrect

exit 0
