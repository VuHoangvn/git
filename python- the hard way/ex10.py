tabby_cat = "\tI'm tabbed in."
persian_cat = "I'm split\non a line"
backslash_cat = "I'm \\ a \\ cat.\v"

fat_cat = """
I'll do a list:\r
\t* Cat food\b
\t* Fishes\f
\t* Catnip\n\t* Grass\a
"""

print tabby_cat
print persian_cat
print backslash_cat
print fat_cat

while True:
	for i in ["/", "-", "|", "\\", "|"]:
		print "%s\r" % i,