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

    conf.check_cxx(lib='rt', header_name='time.h', uselib_store='RT')
    conf.check_cxx(lib='ldns', header_name='ldns/ldns.h', uselib_store='LDNS')
    conf.check_cxx(lib='mysqlclient', header_name='mysql_version.h',
                   includes='/usr/include/mysql', export_includes='/usr/include/mysql',
                   paths=['/usr/lib', '/usr/lib/i386-linux-gnu', '/usr/lib/x86_64-linux-gnu'],
                   uselib_store='MYSQL')
    conf.check_cxx(lib='mysqlpp', header_name='mysql++/mysql++.h',
                   use='MYSQL', uselib_store='MYSQLPP')

    conf.define('_GNU_SOURCE', 1)
    flags = ['-Wall', '-Werror', '-Wpointer-arith', '-fPIC', '-std=c++0x']
    conf.env.append_unique('CXXFLAGS', flags)

    if conf.options.optimize:
        conf.env.append_unique('CFLAGS', ['-O3', '-g1'])
        conf.env.append_unique('CXXFLAGS', ['-O3', '-g1'])
    else:
        conf.env.append_unique('CFLAGS', ['-O0', '-g3'])
        conf.env.append_unique('CXXFLAGS', ['-O0', '-g3'])

    if conf.options.gtest:
        conf.env.GTEST = 1
        conf.env.append_unique('CXXFLAGS', ['-DGTEST_HAS_PTHREAD=0'])

    if conf.options.markdown:
        conf.env.MARKDOWN = 1
        conf.find_program('pandoc', var='PANDOC')

def build(bld):
    source_subdirs = ['core', 'dns', 'db']
    bld.objects(target='objects',
        source=bld.path.ant_glob([subdir + '/*.cpp' for subdir in source_subdirs],
                                 excl=['**/*_test*.cpp']),
        includes='.',
        export_includes='.',
        use='RT LDNS MYSQL MYSQLPP',
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

