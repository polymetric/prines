#!/bin/bash

run=6
for i in {20000..80000}; do
    start=$((i-1))0000000
        end=$((i))0000000
    printf "%b %b\n" $start $end
    ./bin/create_work \
        --appname prines \
        --wu_template templates/prines_in \
        --result_template templates/prines_out \
        --command_line "--start ${start} --end ${end}" \
        --wu_name "prines_s${start}_e${end}_r${run}"
done
