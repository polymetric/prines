#!/usr/bin/python2

import os

####################

dry_run = True
print_cmds = False
app_name = 'prines'
template_in = 'templates/prines_in'
template_out = 'templates/prines_out'
run = 7
n_workunits = 20000
workunit_size = 10**7
initial_wu = 80000
final_wu = None

####################

range_start = initial_wu
range_end = initial_wu + n_workunits

for wu_base in range(range_start, range_end):
    start = wu_base * workunit_size
    end = (wu_base + 1) * workunit_size
    command = """
        ./bin/create_work \
            --appname {} \
            --wu_template {} \
            --result_template {} \
            --command_line '{}' \
            --wu_name '{}'\
        """.format(
            app_name,
            template_in,
            template_out,
            '--start {} --end {}'.format(start, end),
            '{}_r{}_b{}_s{}_e{}'.format(app_name, run, wu_base, start, end),
        )
    # the slash here in front of the brackets is so that the shell
    # doesn't interpret the newline as the start of a new command
    if print_cmds: os.system("echo \{}".format(command))
    if not dry_run: os.system(command)
    print("created workunit with base {}, start {} and end {}".format(wu_base, start, end))
    final_wu = wu_base

print("start of next run: {}".format(final_wu + 1))
