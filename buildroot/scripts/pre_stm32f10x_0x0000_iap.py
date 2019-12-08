Import("env")
import shutil 

print "Copying Linker Scripts"

# Copy the correct link script based on use case
dst_filename = env['PROJECT_DIR'] + "/buildroot/arduino_variant/MKSTFT_F107VC/ldscript.ld"
source_filename = env['PROJECT_DIR'] + "/buildroot/ldscripts/ldscript_vect_0x0000.ld"
shutil.copyfile(source_filename, dst_filename)