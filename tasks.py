from invoke import run, config, task, Collection
import os
import shutil

from configparser import *
import git
from git import *


BUILD_PATH = 'Debug'
PROJECT_NAME = 'li_can_slv_demo_stm32_nucleo_f103rb_cubemx'


@task
def env(ctx):
    os.environ["PATH"] = os.pathsep.join(ctx.path.values()) + os.pathsep + os.environ["PATH"]


@task
def add_submodules(ctx):
    for section, path, url, branch in get_submodule_from_base():
        if branch and url and path is not None:
            cmd = "git submodule add --force -b {0} {1} {2}".format(branch, url, path)
            print(cmd)
            ctx.run(cmd, warn=True)
            print("{} added\n".format(section))
        else:
            print("could not add {}\n".format(section))


@task
def remove_submodules(ctx):
    for section, path, url, branch in get_submodule_from_base():
        if branch and url and path is not None:
            cmd = "git submodule deinit -f -- {}".format(path)
            print(cmd)
            ctx.run(cmd, warn=True)
            cmd = "git rm -f {}".format(path)
            print(cmd)
            ctx.run(cmd, warn=True)

            cmd = "rm -rf .git/modules/{}".format(path)
            print(cmd)
            ctx.run(cmd, warn=True)

            print("{} removed\n".format(section))
        else:
            print("could not remove {}\n".format(section))


@task
def remove_all_submodules(ctx):
    repo = Repo(".")
    sub_modules = repo.submodules
    print("\n")
    print(sub_modules)
    print("\n")
    for sm in sub_modules:
        print("remove: {}".format(sm.name))
        sm.remove(True, force=True)


@task
def show_all_submodules(ctx):
    repo = Repo(".")
    sub_modules = repo.submodules
    print(sub_modules)


@task(env)
def all(ctx):
    with ctx.cd(BUILD_PATH):
        ctx.run('"{}" -j8 all'.format(ctx.make.gnu_arm_make))
        ctx.run('"{}" -j8 {}.bin'.format(ctx.make.gnu_arm_make, PROJECT_NAME))
        ctx.run('"{}" -j8 {}.hex'.format(ctx.make.gnu_arm_make, PROJECT_NAME))


@task(all)
def make(ctx):
    print("make...")


@task(env)
def clean(ctx):
    print("clean...")
    with ctx.cd(BUILD_PATH):
        ctx.run('"{}" clean'.format(ctx.make.gnu_arm_make))


@task
def clean_all(ctx):
    if os.path.isdir(BUILD_PATH):
        shutil.rmtree(BUILD_PATH, ignore_errors=True)


@task
def flash(ctx):
    print("not implemented...")


@task
def diff(ctx):
    ctx.run("git difftool --dir-diff")
    ctx.run("git submodule foreach git difftool -d")


@task
def check(ctx):
    ctx.run("git submodule foreach git status")


@task(env)
def configure(ctx):
    shutil.rmtree(BUILD_PATH, ignore_errors=True)
    os.mkdir(BUILD_PATH)
    with ctx.cd(BUILD_PATH):
        ctx.run('cmake.exe -DCMAKE_SH="CMAKE_SH-NOTFOUND" -G"MinGW Makefiles" -C ../build_settings.cmake -DCMAKE_BUILD_TYPE=Debug ..')


@task(all)
def build(ctx):
    pass


@task(pre=[clean, all])
def rebuild(ctx):
    pass


@task(pre=[clean_all, configure, all])
def rebuild_all(ctx):
    pass


@task(pre=[clean, all, flash])
def bfa(ctx):
    print("not implemented...")


def get_submodule_from_base():
    config = ConfigParser()
    config.read('gitmodules_base')
    for section in config.sections():
        _path = get_value_with_default(config, section, 'path', None)
        _url = get_value_with_default(config, section, 'url', None)
        _branch = get_value_with_default(config, section, 'branch', None)
        yield section, _path, _url, _branch


def get_value_with_default(config, section, name, default):
    if config.has_option(section, name):
        return config.get(section, name)
    else:
        return default
