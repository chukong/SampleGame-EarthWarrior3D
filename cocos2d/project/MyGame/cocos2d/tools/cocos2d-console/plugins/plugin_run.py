#!/usr/bin/python
# ----------------------------------------------------------------------------
# cocos2d "install" plugin
#
# Authr: Luis Parravicini
#
# License: MIT
# ----------------------------------------------------------------------------
'''
"run" plugin for cocos2d command line tool
'''

__docformat__ = 'restructuredtext'

import sys
import os
import cocos2d

class CCPluginRun(cocos2d.CCPlugin):
    """
    Compiles a project and install it on a device
    """

    @staticmethod
    def depends_on():
        return ('compile', 'install')

    @staticmethod
    def plugin_name():
      return "run"

    @staticmethod
    def brief_description():
        return "compiles a project and install the files on a device"

    def run(self, argv, dependencies):
        cocos2d.Logging.info("starting application")
        self.parse_args(argv)
        install_dep = dependencies['install']
        self._run_cmd("adb shell am start -n %s/%s" %
            (install_dep.package, install_dep.activity))
