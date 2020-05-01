project(
    'okra-packed',
    'c',
    'cpp',
    version: '0.0.0',
    default_options:  [ 'c_std=c11', 'cpp_std=gnu++11' ]
)

# Import binary helpers
python       = find_program('python3', required: false)
objcopy      = '@0@'.format(find_program('objcopy').path())
size         = '@0@'.format(find_program('size').path())

# Startup and system files
c_args = [ '-Og' ]
# link_args = '-Wl,-T,@0@/@1@'.format(meson.current_source_dir(), 'linker.ld')

# Add src dependancies
subdir('lib')
packed_inc   = get_variable('packed_inc')
packed_src = get_variable('packed_src')
subdir('example')
example_inc   = get_variable('example_inc')
example_src = get_variable('example_src')

# Generate elf file for MCU
main = executable(
    'main',
    [ packed_src, example_src ],
    include_directories : [ packed_inc, example_inc ],
    cpp_args            : [ c_args ],
    c_args              : [ c_args ],
)

# Add CppUTest dependancy
cpputest     = subproject('cpputest')
cpputest_dep = cpputest.get_variable('cpputest_dep')

# Build native test executable
subdir('test')
test_src = get_variable('test_src')
main_test = executable(
    'tests',
    [ packed_src, test_src ],
    include_directories : [ packed_inc ],
    dependencies        : [ cpputest_dep ],
    native              : true,
    build_by_default    : false
)

test('packed test', main_test)
# Custom run commands
run_target('lint',              command: [ python, '.clang-format.py', '-r',       '-e', 'lib', 'lib' ])
run_target('fix',               command: [ python, '.clang-format.py', '-r', '-s', '-e', 'lib', 'lib' ])
run_target('run',               command: [ main ])
