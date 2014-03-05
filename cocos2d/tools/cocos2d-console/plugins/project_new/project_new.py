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
import json
import shutil
import cocos
import re


#
# Plugins should be a sublass of CCJSPlugin
#
class CCPluginNew(cocos.CCPlugin):

    DEFAULT_PROJ_NAME = {
        cocos.Project.CPP : 'MyCppGame',
        cocos.Project.LUA : 'MyLuaGame',
        cocos.Project.JS : 'MyJSGame'
    }

    DEFAULT_PKG_NAME = {
        cocos.Project.CPP : 'org.cocos2dx.hellocpp',
        cocos.Project.LUA : 'org.cocos2dx.hellolua',
        cocos.Project.JS : 'org.cocos2dx.hellojavascript'
    }


    @staticmethod
    def plugin_category():
      return "project"

    @staticmethod
    def plugin_name():
      return "new"

    @staticmethod
    def brief_description():
        return "creates a new project"

    def init(self, opts):
        self._projname = opts.projname
        self._projdir = os.path.abspath(os.path.join(opts.directory, self._projname))
        self._lang = opts.language
        self._package = opts.package
        self._tpname = opts.template
        self._cocosroot, self._templates_root = self._parse_cfg(self._lang)
        self._templates = self._scan_templates_dir() 
        self._other_opts = opts

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
        parser.add_option("-t", "--template", metavar="TEMPLATE_NAME",help="Set the template name you want create from")
        parser.add_option("--gui", action="store_true", help="Start GUI")
        parser.add_option("--has-native", action="store_true", dest="has_native", help="Has native support.")

        # parse the params
        (opts, args) = parser.parse_args(argv)

        if not opts.language:
            parser.error("-l or --language is not specified")

        if len(args) == 0:
            opts.projname = CCPluginNew.DEFAULT_PROJ_NAME[opts.language]
        else:
            opts.projname = args[0]

        if not opts.package:
            opts.package = CCPluginNew.DEFAULT_PKG_NAME[opts.language]

        if not opts.directory:
            opts.directory = os.getcwd();

        if not opts.template:
            opts.template = 'default'

        self.init(opts)

        return opts

    def _create_from_ui(self):
            cocos.Logging.info("Not avalible now.")

    def _create_from_cmd(self):

        #check the dst project dir exists
        if os.path.exists(self._projdir):
            message = "Fatal: %s folder is already exist" % self._projdir
            raise cocos.CCPluginError(message)

        # read the template cfg
        tp_dir = os.path.join(self._templates_root,self._templates[self._tpname])
        tp_cfgname = '%s.json' % self._templates[self._tpname]
        template_json = os.path.join(tp_dir, tp_cfgname)
        if not os.path.exists(template_json):
            message = "Fatal: template '%s' not found" % self._tpname
            raise cocos.CCPluginError(message)

        f = open(template_json)
        # keep the key order
        from collections import OrderedDict
        template_info = json.load(f, encoding='utf8', object_pairs_hook=OrderedDict)

        creator = TPCreator(self._cocosroot, self._projname, self._projdir, self._tpname, tp_dir, template_info, self._package)
        # do the default creating step
        creator.do_default_step()
        if self._other_opts.has_native:
            creator.do_other_step('do_add_native_support')

    def _scan_templates_dir(self):
        templates_root = self._templates_root
        dirs =  [ name for name in os.listdir(templates_root) if os.path.isdir(os.path.join(templates_root, name)) ]
        template_pattern = {
                "cpp" : 'cpp-template-(.+)',
                "lua" : 'lua-template-(.+)',
                "javascript" : 'js-template-(.+)',
                }
        pattern = template_pattern[self._lang]
        valid_dirs = [ name for name in dirs if re.search(pattern, name) is not None]
        template_names = [re.search(pattern, name).group(1) for name in valid_dirs]

        tpls = {k : v for k in template_names for v in valid_dirs}
        return tpls


    def _parse_cfg(self, language):
        self.script_dir= os.path.abspath(os.path.dirname(__file__))
        self.create_cfg_file = os.path.join(self.script_dir, "env.json")
        
        f = open(self.create_cfg_file)
        create_cfg = json.load(f)
        f.close()
        langcfg = create_cfg[language]
        langcfg['COCOS_ROOT'] = os.path.abspath(os.path.join(self.script_dir,langcfg["COCOS_ROOT"]))
        cocos_root = langcfg['COCOS_ROOT']
        
        # replace SDK_ROOT to real path
        for k, v in langcfg.iteritems():
            if 'COCOS_ROOT' in v:
                v = v.replace('COCOS_ROOT', cocos_root)
                langcfg[k] = v
        
        #get the real json cfgs
        templates_root = langcfg['templates_root']

        return cocos_root, templates_root

    # main entry point
    def run(self, argv, dependencies):
        opts = self.parse_args(argv);
        if opts.gui:
            self._create_from_ui()
        else:
            self._create_from_cmd()


# ignore files function generator
def _ignorePath(root, ignore_files):
    def __ignoref(p, files):
        ignore_list = []
        for f in files:
            for igf in ignore_files:
                f1 = os.path.abspath(os.path.join(p, f))
                f2 = os.path.abspath(os.path.join(root, igf))
                if f1 == f2:
                    ignore_list.append(f)
        return ignore_list
    return __ignoref


# copy the whole things from one dir into a exists dir
def copytree(src, dst, symlinks=False, ignore=None):
    # make sure dst is exists
    if not os.path.exists(dst):
         os.makedirs(dst)

    root_ignorefiles = []
    if ignore is not None:
        root_ignorefiles = ignore(src, os.listdir(src))
    for item in os.listdir(src):
        if item in root_ignorefiles:
            continue
        s = os.path.join(src, item)
        d = os.path.join(dst, item)
        if os.path.isdir(s):
            shutil.copytree(s, d, symlinks, ignore)
        else:
            shutil.copy2(s, d)

def replace_string(filepath, src_string, dst_string):
    """ From file's content replace specified string
    Arg:
        filepath: Specify a file contains the path
        src_string: old string
        dst_string: new string
    """
    if src_string is None or dst_string is None:
        raise TypeError

    content = ""
    f1 = open(filepath, "rb")
    for line in f1:
        strline = line.decode('utf8')
        if src_string in strline:
            content += strline.replace(src_string, dst_string)
        else:
            content += strline
    f1.close()
    f2 = open(filepath, "wb")
    f2.write(content.encode('utf8'))
    f2.close()
#end of replace_string

class TPCreator(object):
    def __init__(self, cocos_root, project_name, project_dir, tp_name, tp_dir, tpinfo, project_package):
        self.cocos_root = cocos_root
        self.project_dir = project_dir
        self.project_name = project_name
        self.package_name = project_package

        self.tp_name = tp_name
        self.tp_dir = tp_dir

        # read the default creating step
        if not tpinfo.has_key('do_default'):
            message = "The '%s' template dosen't has 'default' creating step" % self.tp_name
            raise cocos.CCPluginError(message)
        self.tp_default_step = tpinfo.pop('do_default')
        self.tp_other_step = tpinfo

    def cp_self(self, project_dir, exclude_files):
        cocos.Logging.info('> Copy template files into %s' % project_dir)
        shutil.copytree(self.tp_dir, self.project_dir, True,
                ignore = _ignorePath(self.tp_dir, exclude_files) )


    def do_default_step(self):
        default_cmds = self.tp_default_step
        exclude_files = []
        if default_cmds.has_key("exclude_from_template"):
            exclude_files = default_cmds['exclude_from_template']
            default_cmds.pop('exclude_from_template')

        self.cp_self(self.project_dir, exclude_files)
        self.do_cmds(default_cmds)
    
    def do_other_step(self, step):
        if step in self.tp_other_step:
            cmds = self.tp_other_step[step]
            self.do_cmds(cmds)

    def do_cmds(self, cmds):
        for k, v in cmds.iteritems():
            # call cmd method by method/cmd name
            # get from http://stackoverflow.com/questions/3951840/python-how-to-invoke-an-function-on-an-object-dynamically-by-name
            try:
                cmd = getattr(self, k)
            except AttributeError:
                raise cocos.CCPluginError("cmd = %s is not found" % k)

            try:
                cmd(v)
            except Exception as e:
                raise cocos.CCPluginError(str(e))

## cmd methods below
    def append_h5_engine(self, v):
        cocos.Logging.info( '> append_h5_engine')
        src = os.path.join(self.cocos_root, v['from'])
        dst = os.path.join(self.project_dir, v['to'])
        # check cocos engine exist
        moudle_cfg = os.path.join(src, 'moduleConfig.json')
        if not os.path.exists(moudle_cfg):
            message ="Fatal: %s doesn't exist." % moudle_cfg
            raise cocos.CCPluginError(message)

        f = open(moudle_cfg)
        data = json.load(f, 'utf8')
        f.close()
        modules = data['module'] 
        file_list = []
        for k, v in modules.iteritems():
            module = modules[k]
            for f in module:
                if f[-2:] == 'js':
                    file_list.append(f)

        #begin copy engine
        cocos.Logging.info(">> Copying cocos2d-html5 files...")
        for index in range(len(file_list)):
            srcfile = os.path.join(src,file_list[index])
            dstfile = os.path.join(dst,file_list[index])
            if not os.path.exists(os.path.dirname(dstfile)):
                os.makedirs(os.path.dirname(dstfile))

            #copy file or folder
            if os.path.exists(srcfile):
                if os.path.isdir(srcfile):
                    if os.path.exists(dstfile):
                        shutil.rmtree(dstfile)
                    shutil.copytree(srcfile, dstfile)
                else:
                    if os.path.exists(dstfile):
                        os.remove(dstfile)
                    shutil.copy2(srcfile, dstfile)


    def append_x_engine(self, v):
        cocos.Logging.info('> append_x_engine')
        src = os.path.join(self.cocos_root, v['from'])
        dst = os.path.join(self.project_dir, v['to'])

        # check cocos engine exist
        cocosx_files_json = os.path.join(src, 'templates', 'cocos2dx_files.json')
        if not os.path.exists(cocosx_files_json):
            message = "Fatal: %s doesn\'t exist." % cocosx_files_json
            raise cocos.CCPluginError(message)

        f = open(cocosx_files_json)
        fileList = json.load(f)
        f.close()

        #begin copy engine
        cocos.Logging.info(">> Copying cocos2d-x files...")
        for index in range(len(fileList)):
            srcfile = os.path.join(src,fileList[index])
            dstfile = os.path.join(dst,fileList[index])
            if not os.path.exists(os.path.dirname(dstfile)):
                os.makedirs(os.path.dirname(dstfile))

            #copy file or folder
            if os.path.exists(srcfile):
                if os.path.isdir(srcfile):
                    if os.path.exists(dstfile):
                        shutil.rmtree(dstfile)
                    shutil.copytree(srcfile, dstfile)
                else:
                    if os.path.exists(dstfile):
                        os.remove(dstfile)
                    shutil.copy2(srcfile, dstfile)


    def append_from_template(self, v):
        cocos.Logging.info('> append_from_template')
        src = os.path.join(self.tp_dir, v['from'])
        dst = os.path.join(self.project_dir, v['to'])
        exclude_files = v['exclude']
        shutil.copytree(src, dst, True,
                ignore = _ignorePath(src, exclude_files) )


    def append_dir(self, v):
        cocos.Logging.info('> append_dir')
        src = os.path.join(self.cocos_root, v['from'])
        dst = os.path.join(self.project_dir, v['to'])
        exclude_files = v['exclude']
        copytree(src, dst, True, ignore = _ignorePath(src, exclude_files))

    def append_file(self, v):
        cocos.Logging.info('> append_file')
        for item in v:
            src = os.path.join(self.cocos_root, item['from'])
            dst = os.path.join(self.project_dir, item['to'])
            shutil.copy2(src, dst)

## project cmd
    def project_rename(self, v):
        cocos.Logging.info('> project_rename')
        src_project_name = v['src_project_name']
        files = v['files']
        for f in files:
            src = f.replace("PROJECT_NAME", src_project_name)
            dst = f.replace("PROJECT_NAME", self.project_name)
            if os.path.exists(os.path.join(self.project_dir, src)):
                os.rename(os.path.join(self.project_dir, src), os.path.join(self.project_dir, dst))

    def project_replace_project_name(self, v):
        cocos.Logging.info('> project_replace_project_name')
        src_project_name = v['src_project_name']
        files = v['files']
        for f in files:
            dst = f.replace("PROJECT_NAME", self.project_name)
            if os.path.exists(os.path.join(self.project_dir, dst)):
                replace_string(os.path.join(self.project_dir, dst), src_project_name, self.project_name)

    def project_replace_package_name(self, v):
        cocos.Logging.info('> project_replace_package_name')
        src_package_name = v['src_package_name']
        files = v['files']
        if not self.package_name:
            raise cocos.CCPluginError('package name not specified')
        for f in files:
            dst = f.replace("PROJECT_NAME", self.project_name)
            if os.path.exists(os.path.join(self.project_dir, dst)):
                replace_string(os.path.join(self.project_dir, dst), src_package_name, self.package_name)


