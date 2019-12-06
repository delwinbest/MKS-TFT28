Import("env")
from distutils.dir_util import copy_tree

# access to global construction environment
print(env)
print(env.Dump())
# Get Arduino Variant Path for STM32 Platform
FRAMEWORK_DIR = env.PioPlatform().get_package_dir("framework-arduinoststm32")
VARIANT_DIR = FRAMEWORK_DIR + "/variants"
VARIANT_SRC_DIR = env['PROJECT_DIR'] + "/buildroot/arduino_variant"

# Copy variant in this repo to platformion variant folder
copy_tree(VARIANT_SRC_DIR, VARIANT_DIR)

