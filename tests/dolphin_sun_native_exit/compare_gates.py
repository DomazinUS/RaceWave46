"""Separate fresh processes prove normal defaults reproduce explicit enablement."""
import os
import subprocess
import sys

kind, executable = sys.argv[1:]
environment = dict(os.environ)
for name in ('WR64_DOLPHIN_SUN_NATIVE_EXIT', 'WR64_DOLPHIN_SUN_VISIBLE_EFFECTS', 'WR64_DOLPHIN_SUN_NATIVE_TRACE'):
    environment.pop(name, None)
default_args = [] if kind == 'native' else ['default']
default = subprocess.check_output([executable, *default_args], env=environment, text=True)
environment['WR64_DOLPHIN_SUN_NATIVE_EXIT'] = '1'
environment['WR64_DOLPHIN_SUN_VISIBLE_EFFECTS'] = '1'
enabled_args = ['1'] if kind == 'native' else ['enabled']
enabled = subprocess.check_output([executable, *enabled_args], env=environment, text=True)
assert 'output digest' in default and default == enabled, (default, enabled)
print('PASS normal launch matches explicit enablement, including native output digest.')
print(default.strip())
