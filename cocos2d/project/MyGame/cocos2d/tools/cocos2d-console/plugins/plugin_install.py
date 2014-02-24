#!/usr/bin/python
# ----------------------------------------------------------------------------
# cocos2d "install" plugin
#
# Copyright 2013 (C) Luis Parravicini
#
# License: MIT
# ----------------------------------------------------------------------------
'''
"install" plugin for cocos2d command line tool
'''

__docformat__ = 'restructuredtext'

import sys
import os
import json
import inspect
from xml.dom import minidom

import cocos2d

class CCPluginInstall(cocos2d.CCPlugin):
    """
    Install a project
    """

    @staticmethod
    def plugin_name():
      return "install"

    @staticmethod
    def brief_description():
        return "install a project in a device"

    def _xml_attr(self, dir, file_name, node_name, attr):
        doc = minidom.parse(os.path.join(dir, file_name))
        return doc.getElementsByTagName(node_name)[0].getAttribute(attr)

    def install_android(self):
        if not self._platforms.is_android_active():
            return
        project_dir = self._platforms.project_path()

        cocos2d.Logging.info("installing on device")
        self.package = self._xml_attr(project_dir, 'AndroidManifest.xml', 'manifest', 'package')
        activity_name = self._xml_attr(project_dir, 'AndroidManifest.xml', 'activity', 'android:name')
        if activity_name.startswith('.'):
            self.activity = self.package + activity_name
        else:
            self.activity = activity_name

        project_name = self._xml_attr(project_dir, 'build.xml', 'project', 'name')
        #TODO 'bin' is hardcoded, take the value from the Ant file
        apk_path = os.path.join(project_dir, 'bin', '%s-debug-unaligned.apk' % project_name)

        #TODO detect if the application is installed before running this
        self._run_cmd("adb uninstall \"%s\"" % self.package)
        self._run_cmd("adb install \"%s\"" % apk_path)

    def run(self, argv, dependencies):
        self.parse_args(argv)
        self.install_android()

