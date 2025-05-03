project('bc', 'cpp',
    version : '0.1',
    default_options : ['warning_level=3', 'cpp_std=c++17']
)

fmt = subproject('fmt')
fmt_dep = fmt.get_variable('fmt_dep')

subdir('src')