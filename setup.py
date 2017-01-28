from distutils.core import setup, Extension

spam_module = Extension('spammodule', sources=['spammodule.c'])

setup(name='spam',
      version='1.0',
      description='Practice module for writing C extensions',
      ext_modules=[spam_module])
