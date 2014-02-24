#!/usr/bin/python
# ----------------------------------------------------------------------------
# cocos "new" plugin
#
# Copyright 2013 (C) cocos2d-x.org
#
# License: MIT
# ----------------------------------------------------------------------------
'''
"new" plugin for cocos command line tool
'''

__docformat__ = 'restructuredtext'

# python
import os
import sys
import getopt
import ConfigParser

import cocos


def help():
    sys.exit(-1)


#
# Plugins should be a sublass of CCJSPlugin
#
class CCPluginNew(cocos.CCPlugin):

    @staticmethod
    def plugin_category():
      return "project"

    @staticmethod
    def plugin_name():
      return "new"

    @staticmethod
    def brief_description():
        return "creates a new project"

    # parse arguments
    def parse_args(self, argv):
        """Custom and check param list.
        """
        from optparse import OptionParser
        # set the parser to parse input params
        # the correspond variable name of "-x, --xxx" is parser.xxx
        name = CCPluginNew.plugin_name()
        category = CCPluginNew.plugin_category()
        parser = OptionParser(
            usage=
            "\n\t%%prog %s %s, start GUI version."
            "\n\t%%prog %s %s <PROJECT_NAME> -p <PACKAGE_NAME> -l <cpp|lua|javascript> -d <PROJECT_DIR>"
            "\nSample:"
            "\n\t%%prog %s %s MyGame -p com.MyCompany.AwesomeGame -l javascript -d c:/mycompany" \
                    % (category, name, category, name, category, name)
        )
        parser.add_option("-p", "--package", metavar="PACKAGE_NAME",help="Set a package name for project")
        parser.add_option("-l", "--language",metavar="PROGRAMMING_NAME",
                            type="choice",
                            choices=["cpp", "lua", "javascript"],
                            help="Major programming language you want to use, should be [cpp | lua | javascript]")
        parser.add_option("-d", "--directory", metavar="DIRECTORY",help="Set generate project directory for project")

        # parse the params
        (opts, args) = parser.parse_args(argv)
        if len(args) == 0:
            parser.error("project name is not specified")

        if not opts.package:
            parser.error("-p or --package is not specified")

        if not opts.language:
            parser.error("-l or --language is not specified")

        # use current dir as default
        project_path = os.getcwd()
        if opts.directory:
            project_path = opts.directory

        project_name = args[0]
        return project_name, opts.package, opts.language, project_path


    # create from command
    def commandCreate(self, argv):
        name, package, language, directory = self.parse_args(argv);
        from core import CocosProject
        project = CocosProject()
        project.createPlatformProjects(name, package, language, directory)

    # main entry point
    def run(self, argv, dependencies):
        # use gui
        if len(argv) == 0:
            try:
                from ui import createTkCocosDialog
                createTkCocosDialog()
            except ImportError:
                self.commandCreate(argv)
        else:
            self.commandCreate(argv)

