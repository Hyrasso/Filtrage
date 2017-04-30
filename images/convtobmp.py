import sys, os
from PIL import Image

os.system("cls")
files = sys.argv[1:]
for f in files:
	try:
		print("Converting ", f.split(os.sep)[-1], "to bitmap")
		im = Image.open(f)
		im.save(im.filename[:-3]+"bmp")
	except BaseException as e:
		print(e)
	
	
input("Press any key to quit.")