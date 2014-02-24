#!/usr/bin/python
# ----------------------------------------------------------------------------
# cocos2d "compile" plugin
#
# Copyright 2013 (C) Luis Parravicini
#
# License: MIT
# ----------------------------------------------------------------------------
'''
"compile" plugin for cocos command line tool
'''

__docformat__ = 'restructuredtext'

import cocos

class CCPluginCompile(cocos.CCPlugin):
    """
    compiles a project
    """
    @staticmethod
    def plugin_category():
      return "project"

    @staticmethod
    def plugin_name():
      return "compile"

    @staticmethod
    def brief_description():
        return "compiles the current project to binary"

    def _add_custom_options(self, parser):
        from optparse import OptionGroup
        parser.add_option("-m", "--mode", dest="mode", type="string", default='debug',
                          help="Set the compile mode, should be debug|release, default is debug.")
        parser.add_option("-j", "--jobs", dest="jobs", type='int', default=1,
                          help="Allow N jobs at once.")

        group = OptionGroup(parser, "Android Options")
        group.add_option("--ap", dest="android_platform", help='parameter for android-update.Without the parameter,the script just build dynamic library for project. Valid android-platform are:[10|11|12|13|14|15|16|17|18|19]')  
        parser.add_option_group(group)

        category = self.plugin_category()
        name = self.plugin_name()
        usage = "\n\t%%prog %s %s -p <platform> [-s src_dir][-m <debug|release>]" \
                "\nSample:" \
                "\n\t%%prog %s %s -p android" % (category, name, category, name)

        parser.set_usage(usage)

        pass

    def _check_custom_options(self, options):
        self._mode = 'debug'
        if options.mode:
            if options.mode == 'debug':
                self._mode = 'debug'
            elif options.mode == 'release':
                self._mode = 'release'

        cocos.Logging.info('Building mode: %s' % self._mode)

        android_platform = options.android_platform
        if not android_platform:
            cocos.Logging.info('Android platform not specified, searching a default one...')
            android_platform = cocos.select_default_android_platform()
            if android_platform is None:
                 cocos.Logging.warning('No valid android platform found, will not generate apk.')

        self._ap = android_platform

        self._jobs = 1
        if options.jobs:
            self._jobs = options.jobs
    pass


############### functions for android platform ##############

    def build_android(self):
        if not self._platforms.is_android_active():
            return
        project_dir = self._platforms.project_path()

        # for debug reason, depart 2 step here:
        # 1. build native 2. build apk
        # only build native code if -p not specified, otherwise build apk also.
        cocos.Logging.info("building native")
        with cocos.pushd(project_dir):
            self._run_cmd("python build_native.py -b %s -n \"-j %s\"" % (self._mode, self._jobs))

        cocos.Logging.info("building apk")
        with cocos.pushd(project_dir):
            self._run_cmd("python build_native.py -b %s -p %s -n \"-j %s\"" % (self._mode, self._ap, self._jobs))

    def build_ios(self):
        if not self._platforms.is_ios_active():
            return
        project_dir = self._platforms.project_path()
        cocos.Logging.info("building")
        self._run_cmd("cd \"%s\" && xcodebuild build" % project_dir)

    def run(self, argv, dependencies):
        self.parse_args(argv)
        self.build_android()
        self.build_ios()
