from distutils.core import setup, Extension

module1 = Extension('pyGTMx',
                    define_macros = [('MAJOR_VERSION', '0'),
                                     ('MINOR_VERSION', '1')],
                    include_dirs = ['/usr/include/python2.6',
                                    '/opt/gtm/V53003'],
                    libraries = ['gtmshr','python2.6'],
                    library_dirs = ['/opt/gtm/V53003'],
                    sources = ['pyGTMx.c'])

setup (name = 'pyGTMx',
       version = '0.1',
       description = 'pyGTMx package',
       author = 'stuffduff',
       author_email = 'stuffduff@cox.net',
       url = 'http://www.python.org/doc/current/ext/building.html',
       long_description = '''
pyGTMx (Experimental) Python-GT.M interface package.  Provides GT.M call-in functionality from the Python programming language via module pyGTMx.
''',
       ext_modules = [module1])
