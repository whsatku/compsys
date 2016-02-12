fp = open("init.reg", "w")

for i in range(32):
	fp.write("{0} {0}\n".format(i))
