Import("env", "projenv")
from shutil import copyfile
print "Post build scripts"


def after_build(source, target, env):
    print "post_build_actions"
    # do some actions
    #print(env.Dump())
    source_filename = env['PROJECTBUILD_DIR'] + "/" + env['PIOENV'] + "/" + env['PROGNAME'] + ".bin"
    dst_filename = env['PROJECT_DIR'] + "/buildroot/SDCARD/" + env['PROGNAME'] + ".bin"
    copyfile(source_filename, dst_filename)
    

env.AddPostAction("buildprog", after_build)