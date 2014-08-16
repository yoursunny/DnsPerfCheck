VERSION='0.1'
APPNAME='DnsPerfCheck'

import waflib

def options(opt):
    opt.load('compiler_cxx')

    opt.add_option('--optimize', action='store_true', default=False,
                   dest='optimize', help='optimize object code')
    opt.add_option('--gtest', action='store_true', default=False,
                   dest='gtest', help='build unit tests')
    opt.add_option('--markdown', action='store_true', default=False,
                   dest='markdown', help='build Markdown into HTML')

def configure(conf):
    conf.load('compiler_cxx')

    conf.define('_GNU_SOURCE', 1)
    flags = ['-Wall', '-Werror', '-Wpointer-arith', '-fPIC', '-fno-exceptions', '-std=c++0x', '-fno-rtti']
    conf.env.append_unique('CXXFLAGS', flags)

    if conf.options.optimize:
        conf.env.append_unique('CFLAGS', ['-O3', '-g1'])
        conf.env.append_unique('CXXFLAGS', ['-O3', '-g1'])
    else:
        conf.env.append_unique('CFLAGS', ['-O0', '-g3'])
        conf.env.append_unique('CXXFLAGS', ['-O0', '-g3'])

    if conf.options.gtest:
        conf.env.GTEST = 1

    if conf.options.markdown:
        conf.env.MARKDOWN = 1
        conf.find_program('pandoc', var='PANDOC')

def build(bld):
    source_subdirs = ['dns', 'store']
    bld.objects(target='objects',
        source=bld.path.ant_glob([subdir + '/*.cpp' for subdir in source_subdirs],
                                 excl=['**/*_test*.cpp']),
        includes='.',
        export_includes='.',
        )

    bld.program(target='dpc',
        source=['dpc.cpp'],
        includes='.',
        use='objects',
        )

    if bld.env.GTEST:
        bld.stlib(target='gtest/gtest',
            source=['gtest/gtest.cc', 'gtest/gtest_main.cc'],
            includes='. gtest',
            )
        bld.program(target='unittest',
            source=bld.path.ant_glob([subdir + '/*_test*.cpp' for subdir in source_subdirs]),
            use='objects gtest/gtest',
            install_path=None,
            )

    if bld.env.MARKDOWN:
        waflib.TaskGen.declare_chain(name='markdown2html',
            rule='${PANDOC} -f markdown -t html -o ${TGT} ${SRC}',
            shell=False,
            ext_in='.md',
            ext_out='.htm',
            reentrant=False,
            install_path=None,
            )
        bld(source=bld.path.ant_glob(['**/*.md']))

